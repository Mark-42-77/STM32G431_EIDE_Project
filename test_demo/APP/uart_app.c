#include "uart_app.h"


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
    printf("dma recv: %s\n", uart_rx_dma_buffer);
    memset(uart_rx_dma_buffer, 0, sizeof(uart_rx_dma_buffer));
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
}





