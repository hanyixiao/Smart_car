#ifndef _WOL_UART_H_
#define _WOL_UART_H_

extern float OutData[6];

void WOL_SendWare(void *wareaddr, uint32_t waresize);

#endif //_WOL_UART_H_