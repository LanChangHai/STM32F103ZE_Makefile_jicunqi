#ifndef _oled_h
#define _oled_h

#include "stm32f10x.h"
#include "stm32f103_gpio.h"
#include "delay.h"
#include "SPI.h"
#include "stdio.h"

#define oled_dc PBout(5)
#define oled_cs PGout(4)
#define oled_res PGout(11)
#define oled_mosi SPI2_MOSI
#define oled_clk SPI2_CLK

#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void OLED_WR_Byte(u8 dat,u8 cmd);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y);
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_DrawCircle(u8 x,u8 y,u8 r);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);
void OLED_ShowNum(u8 x,u8 y,double num,u8 size1,u8 len);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void oled_Init(void);
void oled_gpioInit(void);

#endif

