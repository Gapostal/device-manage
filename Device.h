#pragma once
#ifndef DMS_DEVICE
#define DMS_DEVICE

#include <string>
#include <vector>

#include "DMS/User.h"

using std::string;
using std::vector;

namespace dms
{
#define UINT32_T unsigned int

    class Device
    {
    public:
        Device(string device_mac, UINT32_T max_volume);
        ~Device();
        const string getDeviceMac();
        const UINT32_T getMaxVolume();
        const UINT32_T getCurrentVolume();
        int addOneUser(User* user);
        void deviceInfo();
        int deleteOneUser(User* user);
        bool getStatus();
        int setStatus(bool is_online);
    private:
        string device_mac_;
        UINT32_T max_volume_;
        UINT32_T current_volume_;
        vector<User*> user_vector_;
        bool is_online_;
    };
}
#endif //DMS_DEVICE