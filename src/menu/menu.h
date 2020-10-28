
#ifndef MENU_H
#define MENU_H

#define MAX_MENU_DEPTH 4
typedef void (*FP_MENU)(void);

enum
{
    MENU_WELCOME = 0,
    MENU_STATUS = 1,
    MENU_PRGCHS = 2,
    MENU_SAVING = 3
};

typedef struct
{
    FP_MENU menu[MAX_MENU_DEPTH];   // Menu function buffer
    unsigned int cur;                    // Current menu index in buffer
} MENU;

extern MENU infoMenu;

void loadMenuInfo();

#endif
