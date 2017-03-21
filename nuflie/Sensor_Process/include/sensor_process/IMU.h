#include <stdio.h>
#include <nuflie_common/IMUMsg.h>
namespace nuflie {
class IMUInfo
{
public:
    IMUInfo();
    ~IMUInfo();
    nuflie_common::IMUMsg IMUData;
    void IMUProcess();
};

}


