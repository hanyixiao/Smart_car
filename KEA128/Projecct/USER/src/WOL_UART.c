#include "headfile.h"

float OutData[6] = {0,50,100,150,0,0};

void WOL_SendWare(void *wareaddr, uint32_t waresize)
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //串口调试 使用的前命令
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //串口调试 使用的后命令

    uart_putbuff(WARE_UART, cmdf, sizeof(cmdf));    //先发送前命令
    uart_putbuff(WARE_UART, (uint8_t *)wareaddr, waresize);    //发送数据
    uart_putbuff(WARE_UART, cmdr, sizeof(cmdr));    //发送后命令
}