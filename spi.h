#ifndef _FLAUSCH_SPI_H
#define _FLAUSCH_SPI_H

#include "platform_config.h"

void spi_sd_init();
unsigned char spi_sd_xmit(const unsigned char in);
void sd_init();

#endif // _FLAUSCH_SPI_H
