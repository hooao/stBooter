#include <config.h>
#include "system.h"
#include "version.h"
#include "Ymodem.h"
#include "flash_if.h"


int main()
{
    char ch = 0x00; 
    int timeout;

    srvBoardInit();
    printf("stBooter Loader\r\n");
    printf("Version :%s\r\n", VERSTR);
    //printf("Press Enter to active console\r\n");
    timeout = 5;
    put('\n');
    while((timeout--) && ((ch = fish_echo()) != 0x0d))
    {
        printf("type Enter in %d second to active bare environment\r", timeout);
        srvSleep(1);
	}
	put('\n');
	switch(ch)
	{
	    case 0x0d:
	    put('\n');
			while(1)
			    fish_echo();
        default:break;
	}
	srvLoadApp();
    return 0;
}

/*EOF*/

