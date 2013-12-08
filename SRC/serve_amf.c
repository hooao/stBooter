
#include "config.h"
#include "system.h"
#include "version.h"

void srvAmfEarlyInit()
{
    usartBufferInit();

}





int srvBoardInit()
{
    srvAmfEarlyInit();
    bootloader_stage1();
    fish_init();
}


