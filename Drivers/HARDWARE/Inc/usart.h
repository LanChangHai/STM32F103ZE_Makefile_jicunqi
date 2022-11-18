#ifndef __usart_H
#define __usart_H

#include "stdio.h"
#include "stm32f10x.h"
#include "zhongduan.h"
#include "string.h"

#define USART_REC_LEN  			200  	//�����������ֽ��� 200

extern u8  USART1_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART1_RX_STA;         		//����״̬���
extern u8  USART2_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART2_RX_STA;         		//����״̬���
extern u8  USART3_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         		//����״̬���

void usart3_init(u32 pclk1,u32 bound);
void usart2_init(u32 pclk1,u32 bound);
//����봮���жϽ��գ��벻Ҫע�����º궨��
void usart1_init(u32 pclk2,u32 bound);

void Send_char(USART_TypeDef *Usart,char c); //����һ���ַ�
void Send_string(USART_TypeDef *Usart,char string[]); //����һ���ַ���

#endif 

