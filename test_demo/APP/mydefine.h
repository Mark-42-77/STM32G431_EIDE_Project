#ifndef MYDEFINE_H
#define MYDEFINE_H

#include "main.h"
#include "gpio.h"
#include "dma.h"
#include "usart.h"

#include "lcd.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"


#include "system.h"
#include "scheduler.h"
#include "led_app.h"
#include "key_app.h"
#include "lcd_app.h"
#include "uart_app.h"



extern uint8_t ucled[8];
extern uint8_t uckey[4];

extern uint16_t uart_rx_index;
extern uint16_t uart_rx_ticks;
extern uint8_t uart_rx_buffer[128];
extern uint8_t uart_rx_dma_buffer[128];


#endif //  MYDEFINE_H






