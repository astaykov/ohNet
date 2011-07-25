#ifndef HEADER_CPDEVICEUPNP
#define HEADER_CPDEVICEUPNP

#include <OhNetTypes.h>
#include <Buffer.h>
#include <Core/CpDevice.h>
#include <Core/FunctorCpDevice.h>

namespace OpenHome {
namespace Net {

/**
 * CpDevice::GetAttribute supports the following keys for devices created by
 * one of the lists below:
 *  location     - host portion of uri to the device
 *  deviceXml    - copy of the device XML
 *  friendlyName - user displayable name for the device
 *
 * All key names are case sensitive
 */

/**
 * List of all UPnP devices on the current subnet
 *
 * @see CpDeviceList
 * @ingroup ControlPoint
 */
class DllExportClass CpDeviceListUpnpAll : public CpDeviceList
{
public:
    DllExport CpDeviceListUpnpAll(FunctorCpDevice aAdded, FunctorCpDevice aRemoved);
};

/**
 * List of all root UPnP devices on the current subnet
 * @ingroup ControlPoint
 */
class DllExportClass CpDeviceListUpnpRoot : public CpDeviceList
{
public:
    DllExport CpDeviceListUpnpRoot(FunctorCpDevice aAdded, FunctorCpDevice aRemoved);
};

/**
 * List of all UPnP devices with a given uuid (udn) on the current subnet
 * @ingroup ControlPoint
 */
class DllExportClass CpDeviceListUpnpUuid : public CpDeviceList
{
public:
    DllExport CpDeviceListUpnpUuid(const Brx& aUuid, FunctorCpDevice aAdded, FunctorCpDevice aRemoved);
};

/**
 * List of all UPnP devices of a given device type on the current subnet
 * @ingroup ControlPoint
 */
class DllExportClass CpDeviceListUpnpDeviceType : public CpDeviceList
{
public:
    DllExport CpDeviceListUpnpDeviceType(const Brx& aDomainName, const Brx& aDeviceType, TUint aVersion,
                                         FunctorCpDevice aAdded, FunctorCpDevice aRemoved);
};

/**
 * List of all UPnP devices of a given service type on the current subnet
 * @ingroup ControlPoint
 */
class DllExportClass CpDeviceListUpnpServiceType : public CpDeviceList
{
public:
    DllExport CpDeviceListUpnpServiceType(const Brx& aDomainName, const Brx& aServiceType, TUint aVersion,
                                          FunctorCpDevice aAdded, FunctorCpDevice aRemoved);
};

} // namespace Net
} // namespace OpenHome

#endif // HEADER_CPDEVICEUPNP