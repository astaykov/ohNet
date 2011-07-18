#include <C/DvServerUpnp.h>
#include <DvServerUpnp.h>
#include <C/DviDeviceC.h>

using namespace OpenHome;
using namespace OpenHome::Net;

THandle STDCALL DvServerUpnpCreate()
{
    return new DvServerUpnp();
}

void STDCALL DvServerUpnpDestroy(THandle aServer)
{
    DvServerUpnp* server = reinterpret_cast<DvServerUpnp*>(aServer);
    delete server;
}

void STDCALL DvServerUpnpAddDevice(THandle aServer, DvDeviceC aDevice)
{
    DvServerUpnp* server = reinterpret_cast<DvServerUpnp*>(aServer);
    ASSERT(server != NULL);
    DvDevice* device = DviDeviceC::DeviceFromHandle(aDevice);
    ASSERT(device != NULL);
    server->AddDevice(*device);
}
