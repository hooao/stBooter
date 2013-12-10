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
        printf("\rtype Enter in %d seconds to active bare environment", timeout);
        srvSleep(1);
	}
	switch(ch)
	{
	    case 0x0d:
			while(1)
			    fish_echo();
        default:break;
	}
	printf("\r\n\r\n");
	srvLoadApp();
    return 0;
}

/*EOF*/

