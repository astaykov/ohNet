#include <DviServer.h>
#include <OhNetTypes.h>
#include <Network.h>
#include <Thread.h>
#include <Stack.h>
#include <NetworkInterfaceList.h>
#include <OhNet.h>

using namespace OpenHome;
using namespace OpenHome::Net;

// DviServer

DviServer::~DviServer()
{
    iLock.Wait();
    Stack::NetworkInterfaceList().RemoveSubnetListChangeListener(iSubnetListChangeListenerId);
    for (TUint i=0; i<iServers.size(); i++) {
        delete iServers[i];
    }
    iServers.clear();
    iLock.Signal();
}

TUint DviServer::Port(TIpAddress aInterface)
{
    AutoMutex a(iLock);
    for (TUint i=0; i<iServers.size(); i++) {
        DviServer::Server* server = iServers[i];
        if (server->Interface() == aInterface) {
            return server->Port();
        }
    }
    return 0;
}

DviServer::DviServer()
    : iLock("DSUM")
    , iSubnetListChangeListenerId(NetworkInterfaceList::kListenerIdNull)
{
}

void DviServer::Initialise()
{
    Functor functor = MakeFunctor(*this, &DviServer::SubnetListChanged);
    NetworkInterfaceList& nifList = Stack::NetworkInterfaceList();
    iSubnetListChangeListenerId = nifList.AddSubnetListChangeListener(functor);
    iLock.Wait();
    std::vector<NetworkInterface*>* subnetList = nifList.CreateSubnetList();
    for (TUint i=0; i<subnetList->size(); i++) {
        AddServer(*(*subnetList)[i]);
    }
    NetworkInterfaceList::DestroySubnetList(subnetList);
    iLock.Signal();
}

void DviServer::AddServer(NetworkInterface& aNif)
{
    SocketTcpServer* tcpServer = CreateServer(aNif);
    DviServer::Server* server = new DviServer::Server(tcpServer, aNif);
    iServers.push_back(server);
}

void DviServer::SubnetListChanged()
{
    /* DviDeviceUpnp relies on servers being available on all appropriate interfaces.
       We assume this happens through DviServer being created before any devices
       so registering for subnet change notification earlier.  Assuming NetworkInterfaceList
       always runs its listeners in the order they registered, we'll have updated before
       any device listeners are run. */

    iLock.Wait();
    NetworkInterfaceList& interfaceList = Stack::NetworkInterfaceList();
    std::vector<NetworkInterface*>* subnetList = interfaceList.CreateSubnetList();
    const std::vector<NetworkInterface*>& nifList = interfaceList.List();
    TUint i;
    // remove servers whose interface is no longer available
    for (i=0; i<iServers.size(); i++) {
        DviServer::Server* server = iServers[i];
        if (FindInterface(server->Interface(), nifList) == -1) {
            delete server;
            iServers.erase(iServers.begin() + i);
        }
    }
    // add servers for new subnets
    for (i=0; i<subnetList->size(); i++) {
        NetworkInterface* subnet = (*subnetList)[i];
        if (FindServer(subnet->Subnet()) == -1) {
            AddServer(*subnet);
        }
    }

    iLock.Signal();
    NetworkInterfaceList::DestroySubnetList(subnetList);
}

TInt DviServer::FindInterface(TIpAddress aInterface, const std::vector<NetworkInterface*>& aNifList)
{
    for (TUint i=0; i<aNifList.size(); i++) {
        if (aNifList[i]->Address() == aInterface) {
            return i;
        }
    }
    return -1;
}

TInt DviServer::FindServer(TIpAddress aSubnet)
{
    for (TUint i=0; i<iServers.size(); i++) {
        if (iServers[i]->Subnet() == aSubnet) {
            return i;
        }
    }
    return -1;
}


//  DviServer::Server

DviServer::Server::Server(SocketTcpServer* aTcpServer, NetworkInterface& aNif)
    : iNif(aNif)
{
    iServer = aTcpServer;
    iNif.AddRef();
}

DviServer::Server::~Server()
{
    delete iServer;
    iNif.RemoveRef();
}
