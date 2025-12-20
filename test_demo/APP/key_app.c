#include "key_app.h"

uint8_t key_val = 0;
uint8_t key_down = 0;
uint8_t key_old = 0;
uint8_t key_up = 0;

uint8_t eeprom_test[4] = {5,6,0,0};

// ========== 调试用变量 ==========
// 这些变量用于GDB调试演示
volatile uint32_t debug_counter = 0;       // 按键处理函数调用次数
volatile uint8_t debug_key_pressed = 0;    // 最后一次按下的按键值
volatile uint8_t debug_led_state = 0;      // LED状态位图
volatile uint32_t debug_key1_count = 0;    // KEY1按下次数
volatile uint32_t debug_key2_count = 0;    // KEY2按下次数
volatile uint32_t debug_key3_count = 0;    // KEY3按下次数
volatile uint32_t debug_key4_count = 0;    // KEY4按下次数
// ================================


uint8_t key()
{
    uint8_t temp = 0;
    if(HAL_GPIO_ReadPin(GPIOB,KEY1_Pin) == GPIO_PIN_RESET)
        temp = 1;
    if(HAL_GPIO_ReadPin(GPIOB,KEY2_Pin) == GPIO_PIN_RESET)
        temp = 2;
    if(HAL_GPIO_ReadPin(GPIOB,KEY3_Pin) == GPIO_PIN_RESET)
        temp = 3;    
    if(HAL_GPIO_ReadPin(GPIOA,KEY4_Pin) == GPIO_PIN_RESET)
        temp = 4;
    return temp;
}

uint8_t uckey[4] = {0,0,0,0};

void key_proc()
{
    // 调试计数器递增（每次调用此函数时+1）
    debug_counter++;
    
    key_val = key();
    key_down = key_val & (key_val ^ key_old);
    key_up = ~key_val & (key_val ^ key_old);
    key_old = key_val;
    
    // 记录按键状态（用于调试）
    if(key_down != 0) {
        debug_key_pressed = key_down;
    }
    
    // 更新LED状态位图（用于调试）
    debug_led_state = 0;
    for(int i = 0; i < 8; i++) {
        if(ucled[i]) {
            debug_led_state |= (1 << i);
        }
    }

    switch (key_down)
    {
        case 1:
            debug_key1_count++;   // 调试：记录KEY1按下次数
            ucled[1] = 1;         // 点亮LED2
            uckey[0] = key_down;
            eeprom_write(&eeprom_test[0], 0, 1);
            eeprom_write(&eeprom_test[1], 8, 1);
            break;
        case 2:
            debug_key2_count++;   // 调试：记录KEY2按下次数
            ucled[0] = 0;
            uckey[1] = key_down;
            eeprom_read(&eeprom_test[2],0,1);
            eeprom_read(&eeprom_test[3],8,1);
            break;
        case 3:
            debug_key3_count++;   // 调试：记录KEY3按下次数
            ucled[5] = 1;         // 点亮LED6
            uckey[2] = key_down;
            eeprom_test[0]  = 7;
            eeprom_test[1]  = 8;            
            break;
        case 4:
            debug_key4_count++;   // 调试：记录KEY4按下次数
            ucled[7] = 1;         // 点亮LED8
            uckey[3] = key_down;
            break;
    }

    switch (key_up)
    {
        case 1:
            uckey[0] = 0;
            break;
        case 2:
            uckey[1] = 0;
            break;
        case 3:
            uckey[2] = 0;
            break;
        case 4:
            uckey[3] = 0;
            break;
    }
}

