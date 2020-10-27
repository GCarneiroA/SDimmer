
#ifndef MENU_H
#define MENU_H

#define MAX_MENU_DEPTH 10
typedef void (*FP_MENU)(void);

typedef struct
{
    FP_MENU menu[MAX_MENU_DEPTH];   // Menu function buffer
    unsigned int cur;                    // Current menu index in buffer
} MENU;

extern MENU infoMenu;

#endif
