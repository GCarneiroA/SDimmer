
#include "menu/menu.h"
#include "includes.h"

MENU infoMenu;
bool menuUpdates;

void loadMenuInfo()
{
    infoMenu.cur = MENU_WELCOME;
    infoMenu.menu[infoMenu.cur] = infoMenuSelect;

    infoMenu.cur = MENU_STATUS;
    infoMenu.menu[infoMenu.cur] = menuStatus;

    infoMenu.cur = MENU_PRGCHS;
    infoMenu.menu[infoMenu.cur] = chprogram;

    infoMenu.cur = MENU_SAVING;
    infoMenu.menu[infoMenu.cur] = saveInfoMenu;
}
