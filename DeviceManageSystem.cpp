#include "stdafx.h"
#include "DeviceManageSystem.h"

#include <iostream>

using std::cout;
using std::endl;

namespace dms
{
    DeviceManageSystem::DeviceManageSystem()
    {
    }


    DeviceManageSystem::~DeviceManageSystem()
    {
    }

    int DeviceManageSystem::init()
    {
        cout << "[Info]:Enter DeviceManageSystem::init." << endl;

        device_map_.erase(device_map_.begin(), device_map_.end());
        online_device_map_.erase(online_device_map_.begin(), online_device_map_.end());

        return 1;
    }

    int DeviceManageSystem::addDevice(Device & device)
    {
        cout << "[Info]:Enter DeviceManageSystem::addDevice." << endl;

        string device_mac = device.getDeviceMac();
        if(device_map_.find(device_mac) == device_map_.end())
        {
            device_map_[device_mac] = &device;
            return 1;
        }
        else
        {
            cout << "[Warnning]:The device " << device_mac << " is exit." << endl;
            return 0;
        }
    }

    int DeviceManageSystem::deleteDevice(string device_mac)
    {
        cout << "[Info]:Enter DeviceManageSystem::deleteDevice." << endl;

        if (device_map_.find(device_mac) != device_map_.end())
        {
            device_map_.erase(device_mac);
            return 1;
        }
        else
        {
            cout << "[Warnning]:" << device_mac << " is not exit." << endl;
            return 0;
        }
    }

    Device* DeviceManageSystem::getDeviceByMac(string device_mac)
    {
        cout << "[Info]:Enter DeviceManageSystem::getDeviceByMac." << endl;

        if (device_map_.find(device_mac) == device_map_.end())
        {
            cout << "[Warnning]:" << device_mac << " is not exit." << endl;
            return nullptr;
        }

        return device_map_[device_mac];
    }

    const unsigned int DeviceManageSystem::getDeviceNum()
    {
        cout << "[Info]:Enter DeviceManageSystem::getDeviceNum." << endl;

        return device_map_.size();
    }

    Device* DeviceManageSystem::getOneUsableDevice()
    {
        cout << "[Info]:Enter DeviceManageSystem::getOneUsableDevice." << endl;

        // first: get device from online_device_map_
        for (auto iter = online_device_map_.begin(); iter != online_device_map_.end(); iter++) {
            Device* device_tmp = iter->second;
            if (device_tmp->getCurrentVolume() <= device_tmp->getMaxVolume()) {
                return device_tmp;
            }
        }

        // second: can not get device from online_device_map_,trye to get device from device_map_
        for (auto iter = device_map_.begin(); iter != device_map_.end(); iter++) {
            Device* device_tmp = iter->second;
            if (false == device_tmp->getStatus()) {
                device_tmp->setStatus(true);
                online_device_map_[device_tmp->getDeviceMac()] = device_tmp;
                return device_tmp;
            }
        }

        cout << "[Error]:There is no usable device" << endl;

        return nullptr;
    }

    int DeviceManageSystem::addOneUser(User* user)
    {
        cout << "[Info]:Enter DeviceManageSystem::addOneUser." << endl;

        Device* usable_device = getOneUsableDevice();
        if (nullptr == usable_device)
        {
            return 0;
        }
        else
        {
            int result = usable_device->addOneUser(user);
            if (1 == result)
            {
                user->setDeviceMac(usable_device->getDeviceMac());
                cout << "[Info]:Add one user success." << endl;
            }
            else
            {
                cout << "[Error]:Add one user failed." << endl;
            }
        }
        return 1;
    }

    int DeviceManageSystem::deleteOneUser(User* user)
    {
        cout << "[Info]:Enter DeviceManageSystem::deleteOneUser." << endl;

        if (online_device_map_.find(user->getDeviceMac()) == online_device_map_.end()) {
            cout << "[Warnning]:User not exist." << endl;
        }

        Device* user_device = online_device_map_[user->getDeviceMac()];
        if (1 == user_device->deleteOneUser(user)) {
            if (0 == user_device->getCurrentVolume()) {
                user_device->setStatus(false);
                online_device_map_.erase(user_device->getDeviceMac());
            }
            return 1;
        }

        return 0;
    }

    int DeviceManageSystem::getAllVolumeNum()
    {
        cout << "[Info]:Enter DeviceManageSystem::getAllVolumeNum." << endl;

        int all_volume_num = 0;
        for (auto iter = device_map_.begin(); iter != device_map_.end(); iter++)
        {
            Device* device_tmp = iter->second;
            all_volume_num += device_tmp->getMaxVolume();
        }
        return all_volume_num;
    }

    int DeviceManageSystem::getAllCurrentNum()
    {
        cout << "[Info]:Enter DeviceManageSystem::getAllCurrentNum." << endl;

        int cur_volume_num = 0;
        for (auto iter = online_device_map_.begin(); iter != online_device_map_.end(); iter++) {
            Device* device_tmp = iter->second;
            cur_volume_num += device_tmp->getCurrentVolume();
        }

        return cur_volume_num;
    }
}