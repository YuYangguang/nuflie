#include <stdio.h>
#include <nuflie_common/GPSMsg.h>
namespace nuflie {
class GPSInfo
{
public:
    GPSInfo();
    ~GPSInfo();
    nuflie_common::GPSMsg GPSData;
    void GPSProcess();



};
}

