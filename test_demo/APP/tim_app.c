#include "tim_app.h"

uint16_t count_1000ms = 0;
uint16_t count_pwm = 0;
uint8_t flag_up = 1;

// 输入捕获变量
uint32_t ic_value1 = 0;     // 第一次捕获值
uint32_t ic_value2 = 0;     // 第二次捕获值
uint32_t ic_diff = 0;       // 两次捕获差值
float frequency = 0;        // 计算得到的频率
uint8_t ic_flag = 0;        // 捕获状态标志

// 输入捕获回调函数
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3 && htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        if(ic_flag == 0)
        {
            // 第一次捕获，记录第一个上升沿时刻
            ic_value1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            ic_flag = 1;
        }
        else
        {
            // 第二次捕获，记录第二个上升沿时刻
            ic_value2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
            
            // 计算两次上升沿的时间差
            if(ic_value2 > ic_value1)
            {
                ic_diff = ic_value2 - ic_value1;
            }
            else
            {
                // 处理计数器溢出情况
                ic_diff = (65535 - ic_value1) + ic_value2 + 1;
            }
            
            // 计算频率
            // TIM3时钟=80MHz, 预分频=8000, 计数频率=10kHz
            // 频率 = 计数频率 / 捕获差值
            frequency = 10000.0f / ic_diff;
            
            ic_flag = 0;  // 复位，准备下次捕获
            ucled[3] ^= 1;  // LED闪烁表示捕获成功
        }
    }
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM2)
    {
        if(++count_1000ms >= 100)
        {
            count_1000ms = 0;
            // ucled[2] ^= 1;
            if(flag_up)
                count_pwm += 10;
            else
                count_pwm -= 10;
            if(count_pwm >= 65530)
            {
                flag_up = 1;
                count_pwm = 0;
            }
            if(count_pwm >= 999)
            {
                flag_up = 0;
                count_pwm = 999;
            }            
        }
    }

    __HAL_TIM_SetCompare(&htim2, TIM_CHANNEL_1, count_pwm);
}





