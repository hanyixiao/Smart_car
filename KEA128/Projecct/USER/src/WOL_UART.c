#include "headfile.h"

float OutData[6] = {0,50,100,150,0,0};

void WOL_SendWare(void *wareaddr, uint32_t waresize)
{
#define CMD_WARE     3
    uint8_t cmdf[2] = {CMD_WARE, ~CMD_WARE};    //���ڵ��� ʹ�õ�ǰ����
    uint8_t cmdr[2] = {~CMD_WARE, CMD_WARE};    //���ڵ��� ʹ�õĺ�����

    uart_putbuff(WARE_UART, cmdf, sizeof(cmdf));    //�ȷ���ǰ����
    uart_putbuff(WARE_UART, (uint8_t *)wareaddr, waresize);    //��������
    uart_putbuff(WARE_UART, cmdr, sizeof(cmdr));    //���ͺ�����
}