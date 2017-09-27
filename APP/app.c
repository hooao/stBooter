#include <config.h>
#include "system.h"
#include "version.h"
#include "Ymodem.h"
#include "flash_if.h"

extern void srvAmfPayloadOff(void);

int main()
{
    char ch = 0x00; 
    int timeout;

    srvBoardInit();
    printf("stBooter Loader\r\n");
    printf("Version :%s\r\n", VERSTR);
    printf("Press Enter to active console\r\n");
    timeout = 3;
    put('\n');
    
 //    if((GPIOE->IDR | 0xFFFE) == 0xFFFE)//check out if pow button is pressed.
 //    {
 //        srvSleep10Ms(2);//delay 20 ms
 //        if((GPIOE->IDR | 0xFFFE) == 0xFFFE)
 //        {
 //            srvAmfDC12vIpmcUpCtrOn();
 //            srvAmfDC12vOn();
 //            while(1)
 //                fish_echo();
 //        }
	// }

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


	boot_main();
    return 0;
}

/*EOF*/

