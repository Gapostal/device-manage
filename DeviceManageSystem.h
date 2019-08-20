#pragma once
#ifndef DMS_DEVICE_MANAGE_SYSTEM
#define DMS_DEVICE_MANAGE_SYSTEM

#include <map>

#include "DMS/Device.h"
#include "DMS/User.h"

using std::map;
using dms::Device;

namespace dms
{
    class DeviceManageSystem
    {
    public:
        DeviceManageSystem();
        ~DeviceManageSystem();
        int init();
        int addDevice(Device& device);
        int deleteDevice(string device_mac);
        Device* getDeviceByMac(string device_mac);
        const unsigned int getDeviceNum();
        Device* getOneUsableDevice();
        int addOneUser(User* user);
        int deleteOneUser(User* user);
        int getAllVolumeNum();
        int getAllCurrentNum();
    private:
        map<string, Device*> device_map_;
        map<string, Device*> online_device_map_;
    };
}
#endif //DMS_DEVICE_MANAGE_SYSTEM