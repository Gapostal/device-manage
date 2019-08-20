#pragma once
#ifndef DMS_USER
#define DMS_USER

#include <string>

using std::string;
namespace dms
{
    class User
    {
    public:
        User(string user_name);
        ~User();
        const int getUserID();
        const string getUserName();
        int setUserID(int user_id);
        int setDeviceMac(string device_mac);
        void userInfo();
        const string getDeviceMac();
    private:
        int user_id_;
        string user_name_;
        string device_mac_;
    };
}

#endif //DMS_USER