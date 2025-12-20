#ifndef __I2C_HAL_H
#define __I2C_HAL_H

#include "mydefine.h"
#include "stm32g4xx_hal.h"

void I2CStart(void);
void I2CStop(void);
unsigned char I2CWaitAck(void);
void I2CSendAck(void);
void I2CSendNotAck(void);
void I2CSendByte(unsigned char cSendByte);
unsigned char I2CReceiveByte(void);
void I2CInit(void);
void mcp4017_write(uint8_t data);
void mcp4017_read(uint8_t *data);
void eeprom_write(uint8_t *EEPROM_String, uint8_t addr, uint8_t num);
void eeprom_read(uint8_t *EEPROM_String, uint8_t addr, uint8_t num);

#endif
