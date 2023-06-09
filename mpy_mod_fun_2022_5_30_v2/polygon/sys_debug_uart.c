/*
 * Copyright (C) 2022 Polygon Zone Open Source Organization .
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http:// www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 *
 * limitations under the License.
 */






#include <stdio.h>
#include "sys_debug_uart.h"

#if SYS_DEBUG_ENABLE==1
void Sys_Debug_Uart_Init(int baud) {
	hi_uart_deinit(2);
	IoTGpioInit(11);//使用GPIO，都需要调用该接口 
	IoTGpioInit(12);//使用GPIO，都需要调用该接口 
	hi_io_set_func(11,2);
	hi_io_set_func(12,2);
	IotUartAttribute g_uart_cfg = {115200, 8, 1, IOT_UART_PARITY_NONE, 0, 0, 0}; 
    IoTUartInit(2, &g_uart_cfg); 
}

void Sys_Debug_Uart_DeInit(void){
	hi_uart_deinit(2);
	IoTGpioDeinit(11);//使用GPIO，都需要调用该接口 
	IoTGpioDeinit(12);//使用GPIO，都需要调用该接口 
	hi_io_set_func(11,0);
	hi_io_set_func(12,0);
	IoTUartDeinit(2); 
}


int Sys_Debug_Uart_Send(uint8_t*data, uint32_t len){
	return IoTUartWrite(2,data,len);
}



int Sys_Debug_Uart_Recv( uint8_t *data, uint32_t len){
	return IoTUartRead(2,data,len);
}





int Sys_Debug_Uart_Putchar(char ch){
	return Sys_Debug_Uart_Send((uint8_t*)(&ch),1);
}

#endif

