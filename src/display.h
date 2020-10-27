
#ifndef DISP_H
#define DISP_H

#include <WString.h>

struct display_t
{
    String line1;
    String line2;
};

void initializeDisplay();
void refreshDisplay();

#endif
