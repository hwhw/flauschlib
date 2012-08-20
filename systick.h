#ifndef _FLAUSCH_SYSTICK_H
#define _FLAUSCH_SYSTICK_H

#include "platform_config.h"

static volatile unsigned int systick;

void systick_init();
void delay100usec(const unsigned int times);

#endif // _FLAUSCH_SYSTICK_H

