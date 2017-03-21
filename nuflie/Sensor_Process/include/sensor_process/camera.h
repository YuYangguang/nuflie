#include <stdio.h>
#include <stdlib.h>
#include <nuflie_common/cameraMsg.h>
namespace nuflie {
class cameraInfo
{
    public:
    cameraInfo();
    ~cameraInfo();
    nuflie_common::cameraMsg cameraData;
    void imageProcess();
};

}

