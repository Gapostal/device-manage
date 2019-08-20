#include "stdafx.h"
#include "DMSTest.h"

#include <iostream>

#include "DMS/Device.h"
#include "DMS/DeviceManageSystem.h"
#include "DMS/User.h"

using dms::Device;
using dms::DeviceManageSystem;
using dms::User;

using std::cout;
using std::endl;

DMSTest::DMSTest()
{
}


DMSTest::~DMSTest()
{
}

void string_replace(string&s1, const string&s2, const string&s3)
{
    string::size_type pos = 0;
    string::size_type a = s2.size();
    string::size_type b = s3.size();
    while ((pos = s1.find(s2, pos)) != string::npos)
    {
        s1.replace(pos, a, s3);
        pos += b;
    }
}

int main()
{
    DeviceManageSystem device_manage_system;
    device_manage_system.init();

    // test1:add one device
    cout << "----[Test1]----" << endl;
    const string device_mac = "aaa";
    const UINT32_T max_volume = 100;
    Device device(device_mac, max_volume);

    device_manage_system.addDevice(device);

    cout << device_manage_system.getDeviceNum() << endl;

    // test2:get device by mac
    cout << "----[Test2]----" << endl;
    Device* device_one = device_manage_system.getDeviceByMac(device_mac);
    device_one->deviceInfo();

    // test3:get one usable device
    cout << "----[Test3]----" << endl;
    User* user = new User("AAA");
    device_manage_system.addOneUser(user);

    Device* one_use_device = device_manage_system.getOneUsableDevice();
    one_use_device->deviceInfo();

    // test4:delete one user
    cout << "----[Test4]----" << endl;
    user->userInfo();

    device_manage_system.deleteOneUser(user);
    user->userInfo();
    one_use_device->deviceInfo();

    // test5:get all and current num
    cout << "----[Test5]----" << endl;
    cout << device_manage_system.getAllCurrentNum() << endl;
    cout << device_manage_system.getAllVolumeNum() << endl;

    // test6 add one user
    cout << "----[Test6]----" << endl;
    User* user1 = new User("AAA");
    device_manage_system.addOneUser(user1);

    //string s1 = "aaa/bbb/ccc";
    //string s2 = "/";
    //string s3 = "_";
    //string_replace(s1, s2, s3);
    //cout << s1 << endl;


    system("pause");
    return 0;
}
