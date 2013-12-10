



#ifndef __COMP_FISH_
#define __COMP_FISH_

#define MAX(a, b)  a>=b?a:b
#define MIN(a, b)  a<=b?a:b


#define FISH_MAX_CMD_SUPPORT      16
#define FISH_KEYBOARD_RETURN      0x0D
#define FISH_KEYBOARD_TABLE       0x09
#define FISH_KEYBOARD_UP          0x26
#define FISH_KEYBOARD_DOWN        0x28
#define FISH_KEYBOARD_LEFT        0x25
#define FISH_KEYBOARD_RIGHT       0x27
#define FISH_KEYBOARD_BACKSPACE  0x08



typedef struct hmif_fish {
    unsigned int connect_timeout;
    unsigned char connectted;
}HUIF_FISH_t;


typedef int (*FUNC)(void *); 



typedef struct fish_cmd {
    char *name;
    FUNC exec;
    char *description;
    unsigned char code;
}FISH_CMD_t;









#endif

/*EOF*/

