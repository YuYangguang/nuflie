#include <stdio.h>
#include <nuflie_common/sonarMsg.h>

namespace nuflie{
class SonarInfo
{
public:
    SonarInfo();
    ~SonarInfo();
    nuflie_common::sonarMsg sonarMsg;
    void sonarProcess();
};


}

