#ifndef MYDEFINE_H
#define MYDEFINE_H

#include "main.h"
#include "gpio.h"
#include "dma.h"
#include "usart.h"
#include "rtc.h"

#include "lcd.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include <stdlib.h>

#include "system.h"
#include "scheduler.h"
#include "led_app.h"
#include "key_app.h"
#include "lcd_app.h"
#include "uart_app.h"
#include "ringbuffer.h"
#include "adc_app.h"
#include "i2c_hal.h"
#include "rtc_app.h"

extern uint8_t ucled[8];
extern uint8_t uckey[4];

extern uint16_t uart_rx_index;
extern uint16_t uart_rx_ticks;
extern uint8_t uart_rx_buffer[128];
extern uint8_t uart_rx_dma_buffer[128];
extern uint8_t usart_read_buffer[128];

extern uint16_t uart2_rx_index;
extern uint16_t uart2_rx_ticks;
extern uint8_t uart2_rx_buffer[128];
extern uint8_t uart2_rx_dma_buffer[128];
extern uint8_t usart2_read_buffer[128];

extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart2_rx;

extern uint32_t dma_buff[2][30];
extern float adc_value[2];

extern uint8_t eeprom_test[4];

extern RTC_TimeTypeDef time; //定义时间结构体
extern RTC_DateTypeDef date; //定义日期结构体

#endif //  MYDEFINE_H






