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
 
 
 
 
/* Define to prevent recursive inclusion ----------------------------*/
#ifndef __FRAME_H
#define __FRAME_H

 

/* Includes  == 文件包含 --------------------------------------------*/
#include "ohos_types.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Private typedef    ==  私有类型 ----------------------------------*/
/* Private define     ==  私有定义 ----------------------------------*/
typedef uint16(*FRAME_VALIDATE)(uint8 *frame_buf, uint16 remaining_length);

typedef  struct
{
	uint8 *buffer;
	uint16 head;
	uint16 count;
	uint16 BUFFERLENGTH;
	FRAME_VALIDATE ValidateFrame;
} FrameBufferStr;


/* Private macro      ==  私有宏 ------------------------------------*/
/* Private variables  ==  私有变量 ----------------------------------*/



/* Private function prototypes  ==  私有函数声明 --------------------*/
void Init_Frame_Buffer(FrameBufferStr *frame, uint16 buffer_length, FRAME_VALIDATE validate_proc);
void Deinit_Frame_Buffer(FrameBufferStr *frame);
void Append_Frame_Buffer(FrameBufferStr *frame, uint8 *input, uint16 length);
void Append_Frame_Clean(FrameBufferStr *frame);


/* Define to prevent recursive inclusion ----------------------------*/
#endif /* __FRAME_H */




/*********************************  COPYRIGHT 2015 --------  *********  END OF FILE  **********************************/
