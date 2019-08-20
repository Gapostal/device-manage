#include "stdafx.h"
#include "Device.h"
#include <iostream>

namespace dms
{
    using std::cout;
    using std::endl;

    Device::Device(string device_mac, UINT32_T max_volume) :
        device_mac_(device_mac),
        max_volume_(max_volume),
        is_online_(false)
    {
        current_volume_ = 0;
    }


    Device::~Device()
    {
        user_vector_.clear();
    }

    const string Device::getDeviceMac()
    {
        return device_mac_;
    }

    const UINT32_T Device::getMaxVolume()
    {
        return max_volume_;
    }

    const UINT32_T Device::getCurrentVolume()
    {
        return current_volume_;
    }

    int Device::addOneUser(User* user)
    {
        user_vector_.push_back(user);
        current_volume_++;
        user->setUserID(current_volume_);
        return 1;
    }

    int Device::deleteOneUser(User* user)
    {
        vector<User*>::iterator itr = user_vector_.begin();
        while (itr != user_vector_.end())
        {
            if ((*itr)->getUserID() == user->getUserID())
            {
                user->setUserID(-1);
                user->setDeviceMac("NULL");
                itr = user_vector_.erase(itr);
                current_volume_--;
                return 1;
            }
            ++itr;
        }

        return 1;
    }

    bool Device::getStatus()
    {
        return is_online_;
    }

    int Device::setStatus(bool is_online)
    {
        is_online_ = is_online;
        return 1;
    }

    void Device::deviceInfo()
    {
        cout << "##################### Device info ###############" << endl;
        cout << "##########  device mac is " << device_mac_.c_str() << endl;
        cout << "##########  max volume is " << max_volume_ << endl;
        cout << "##########  current volume is " << current_volume_ << endl;
        cout << "#################################################" << endl;
    }
}