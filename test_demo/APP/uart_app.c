#include "uart_app.h"

ringbuffer_t usart_rb;
uint8_t usart_read_buffer[128];

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
// {
//     if(huart->Instance == USART1)
//     {
//         uart_rx_ticks = HAL_GetTick(); // 记录接收时间戳
//         // 处理接收到的数据
//         uart_rx_index++;      
//         // 继续接收下一个字节
//         HAL_UART_Receive_IT(&huart1, &uart_rx_buffer[uart_rx_index], 1);

       
//     }
// }


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart->Instance == USART1)
    {
        if(!ringbuffer_is_full(&usart_rb))
        {
            ringbuffer_write(&usart_rb, uart_rx_dma_buffer, Size);
        }
        memset(uart_rx_dma_buffer, 0, sizeof(uart_rx_dma_buffer));
        ucled[0] ^= 1;
        
        // 【关键】重新启动DMA接收，否则只能收一次
        HAL_UARTEx_ReceiveToIdle_DMA(&huart1, uart_rx_dma_buffer, sizeof(uart_rx_dma_buffer));
        __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT); // 禁用半传输中断
    }
}


void uart_proc(void)
{
    // if(uart_rx_index == 0)
    //     return;
    // // 检查是否有数据接收完成
    // if(uwTick - uart_rx_ticks > 100)
    // {
    //     printf("uart recv: %s\n", uart_rx_buffer);
    //     memset(uart_rx_buffer, 0, uart_rx_index); // 清空接收缓冲区
    //     uart_rx_index = 0;
    //     huart1.pRxBuffPtr = uart_rx_buffer;
    // }

    if(ringbuffer_is_empty(&usart_rb)) return;
    ringbuffer_read(&usart_rb, usart_read_buffer, usart_rb.itemCount);
    /*********具体解析过程写在下方**********/
    printf("ringbuffer data: %s\n", usart_read_buffer);



    memset(usart_read_buffer, 0 ,sizeof(uint8_t) * 128);
}






