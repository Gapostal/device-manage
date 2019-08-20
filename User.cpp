#include "stdafx.h"
#include "User.h"
#include <iostream>

using std::cout;
using std::endl;

namespace dms
{
    User::User(string user_name):
        user_name_(user_name)
    {
        user_id_ = 0;
        device_mac_ = "NULL";
    }

    User::~User()
    {
    }

    const int User::getUserID()
    {
        return user_id_;
    }

    const string User::getUserName()
    {
        return user_name_;
    }

    int User::setUserID(int user_id)
    {
        user_id_ = user_id;
        return 1;
    }

    void User::userInfo()
    {
        cout << "[Info]:user name is " << user_name_.c_str() << endl;
        if ("NULL" != device_mac_)
        {
            cout << "[Info]:user in device's mac is " << device_mac_.c_str() << endl;
        }
    }

    int User::setDeviceMac(string device_mac)
    {
        device_mac_ = device_mac;
        return 1;
    }

    const string User::getDeviceMac()
    {
        return device_mac_;
    }
}
