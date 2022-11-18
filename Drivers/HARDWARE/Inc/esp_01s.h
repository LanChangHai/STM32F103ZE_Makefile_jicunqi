#ifndef __ESP_01S_H
#define __ESP_01S_H

#include <stdio.h>
#include "usart.h"
#include "chuankou.h"
#include <string.h>

void Esp_Init(void);
void __attribute__((weak)) Esp_Usart_Init(void);
u8 Hand(char *duibi);
u8 Hand_Save(char *Enter_save,char *duibi);;
char *Seek_Save(char *zhiling,char *Enter_save,char *duibi);
void intercept_sava(char *zhiling,char *Enter_save,char *duibi,int n);
void Direct_Hand(char *zhiling,char *duibi);
	
#endif

