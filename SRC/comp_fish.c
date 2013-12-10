
#include <stdio.h>
#include "config.h"
#include "system.h"
#include "version.h"
#include "comp_uart.h"
#include "comp_fish.h"

//extern valiable
extern FISH_CMD_t fish_command_list[FISH_MAX_CMD_SUPPORT];
unsigned char now_allocked = 0;//已经申请掉的code command号码

unsigned char fishAllocCmdCode()
{
    return now_allocked;//新申请的command依次放在fish_command_list数组中，用now_allocked来记录当前已被申请的号码
}

FUNC help_main(void *arg)
{
    unsigned char i;
    printf("support command:\r\n");
    i=0;
    while(fish_command_list[i].name != NULL)
    {
        printf("%s\t%s\r\n",fish_command_list[i].name, fish_command_list[i].description);
        i++;
    }
    return 0;
    
}


//Fish version description
FUNC version_main(void *arg)
{
    printf("%s\r\n", VERSTR);
    return 0;
}

FUNC board_main(void *arg)
{
    arg =arg;//to avoid compile warnning
	printf("This is bootloader for stm32 \r\n");
    return 0;
}


//update firm by serial port.
FUNC olupd_main(void *arg)
{
    updFirmware();
    return 0;
}

//found history command
FUNC boot_main()
{
    srvLoadApp();
    return 0;
}


//====================================================
char fish_command_register(FISH_CMD_t *pcmd)
{
    if(pcmd == NULL)
        return 0;
    fish_command_list[pcmd->code].code = pcmd->code;
    fish_command_list[pcmd->code].name = pcmd->name;
    fish_command_list[pcmd->code].exec = pcmd->exec;
    fish_command_list[pcmd->code].description = pcmd->description;
    now_allocked ++;
    return 0;
}
//Fish component
void fish_init(void)
{

    FISH_CMD_t cmd;
    p_uart_produce = uart_cache;
    p_uart_custom = uart_cache;
    cmd_counter = 0;
    now_allocked = 0;
    memset(uart_cache, 0x0, sizeof(uart_cache));
    memset(uart_buffer, 0x0, sizeof(uart_buffer));
    memset(fish_command_list, 0x0, sizeof(fish_command_list));

    //!!some system command must register at startup time.
    // register command "help"
    cmd.code          = 0;
    cmd.name          = "help";
    cmd.exec          = help_main;
    cmd.description   = "Print help message";
    fish_command_register(&cmd);
     
    cmd.code          = fishAllocCmdCode();
    cmd.name          = "board";
    cmd.exec          = board_main;
    cmd.description   = "This is stBootloader";
    fish_command_register(&cmd);


    cmd.code          = fishAllocCmdCode();
    cmd.name          = "olupd";
    cmd.exec          = olupd_main;
    cmd.description   = "OnLine UPDate STM32 fireware";
    fish_command_register(&cmd);
    
    cmd.code          = fishAllocCmdCode();
    cmd.name          = "boot";
    cmd.exec          = boot_main;
    cmd.description   = "Boot the system";
    fish_command_register(&cmd);

    
    cmd.code          = fishAllocCmdCode();
    cmd.name          = "version";
    cmd.exec          = version_main;
    cmd.description   = "Check out stBooter Version";
    fish_command_register(&cmd);
    
}



unsigned char fish_find_possible_command()
{
    unsigned char i, j, print_all_cmd;
    unsigned char possible_cmd[64];//possible_cmd数组中记录了,tab键补全可能的命令。其中第一个字节为可能命令的总数。用于打印这些命令时用作引导。因此，无需初始化该数组
    possible_cmd[0] = 0;
    j=1;print_all_cmd = 0;
    for(i = 0; i < FISH_MAX_CMD_SUPPORT; i++)
    {
        if(cmd_counter == 0)
        {
            //mark all
            print_all_cmd = 1;
            break;
        }
         //比较某个命令的钱cmd_counter个字符，如果符合，则将该命令置为可能被选命令
         if(memcmp(uart_buffer, fish_command_list[i].name, cmd_counter) == 0)//cmd_counter记录了当前uart_buffer中某个命令的部分字节
         {
              possible_cmd[0] += 1;
              possible_cmd[j]  =  i;
         }
    }
    //做完这些后，打印他们
    printf("\r\nDo you want to find these command?\r\n");
    if(print_all_cmd)
    {
        for(i = 0; i < now_allocked; i++)
            printf("%s\r\n", fish_command_list[i].name);
    }
    else
    {
        for(i = 1; i <= possible_cmd[0]; i++)//i从1开始，因为0被用作计数了
        {
            j = possible_cmd[i];
            printf("%s\r\n", fish_command_list[j].name);
        }
    }
    return 0;
}

unsigned char fish_print_possible_command()
{
    return 0;
}

char fish_echo()
{
    unsigned char i;
    char ret;
    int tmp;
    //check if p_uart_produce not equal to p_uart_custom
    while(p_uart_custom != p_uart_produce)//something new
    {
        if(*p_uart_custom == FISH_KEYBOARD_RETURN)//we got an return, find & execute command
        {
            put('\r');put('\n');
            putstr(IPMC_DEVSCRIPTION);
            if(cmd_counter)//if we really got a command
            {
            //search command in fish_command_list & execute  it
            for(i=0; i<FISH_MAX_CMD_SUPPORT; i++)
            {
                 if(memcmp(uart_buffer, fish_command_list[i].name, strlen(fish_command_list[i].name)+1) == 0)//+1 mainly because of comparing \0
                 {
                      //do the execute
                      
                      put('\r');
                      fish_command_list[i].exec(NULL);
                      put('\r');put('\n');
                      putstr(IPMC_DEVSCRIPTION);
                      break;
                 }
            }
            }
            
			memset(uart_buffer, 0x0, cmd_counter);
			cmd_counter = 0;
            ret = FISH_KEYBOARD_RETURN;
          }//end if(*p_uart_custom == FISH_KEYBOARD_RETURN)
          else if(*p_uart_custom == FISH_KEYBOARD_TABLE)
          {//print the possible command
               fish_find_possible_command();
               *p_uart_custom = 0;
             ///  p_uart_custom = p_uart_produce ;
               putstr(IPMC_DEVSCRIPTION);

               printf("%s", uart_buffer);
             // fish_print_possible_command();
              ret = FISH_KEYBOARD_TABLE;
                
          }
          else if(*p_uart_custom == FISH_KEYBOARD_BACKSPACE)//
          {
              if(cmd_counter > 0)
              {
                  cmd_counter--;
                  uart_buffer[cmd_counter]=0; 
                  put('\b');
                  put(' ');
                  put('\b');
                  
              }
          ret = FISH_KEYBOARD_BACKSPACE;
          }
          else if(*p_uart_custom == FISH_KEYBOARD_UP)//found history command
          {
              ret = FISH_KEYBOARD_UP;
          }
          else if(*p_uart_custom == FISH_KEYBOARD_DOWN)
          {
              ret = FISH_KEYBOARD_DOWN;
          }
          else//other char, just echo it
          {
              if((*p_uart_custom >='a')&&(*p_uart_custom <='z'))//we only support character a~z
              {
                   ret = *p_uart_custom;
                   put(*p_uart_custom);
                   uart_buffer[cmd_counter] = *p_uart_custom;//IN ORDER TO remember the command
                   cmd_counter ++;
                   cmd_counter %= sizeof(uart_buffer);
              }
          }
          
        if(p_uart_custom == &uart_cache[31])
            p_uart_custom = uart_cache;
        else
            p_uart_custom++;
        
    }
    return ret;
}

