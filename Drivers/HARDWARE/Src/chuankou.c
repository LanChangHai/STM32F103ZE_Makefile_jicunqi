#include "chuankou.h"
int chuankou2_huoqu(char *save)
{
 u8 t;//ѭ������
 u16 len;//�洢��ȡ���ֽ���
 if(USART2_RX_STA&0x8000)//�ж��Ƿ������룬������Ļ���USART_RX_STA���λ����1,ͨ����λ���ж��Ƿ���ܵ����ݣ�
 {
  len=USART2_RX_STA&0x3fff;//��ȡ���ܵ����ַ����ȣ�0x3fff����Ϊһ�������ܳ���Ϊ14λ����2^14�ֽ�;
  for(t=0;t<len;t++)
   {
	   save[t]=USART2_RX_BUF[t];
   }
   USART2_RX_STA=0;//�����־λ
	 return 1;
 }
 else
 return 0;
}
int chuankou1_huoqu(char *save)
{
 u8 t;//ѭ������
 u16 len;//�洢��ȡ���ֽ���
 if(USART1_RX_STA&0x8000)//�ж��Ƿ������룬������Ļ���USART_RX_STA���λ����1,ͨ����λ���ж��Ƿ���ܵ����ݣ�
 {
  len=USART1_RX_STA&0x3fff;//��ȡ���ܵ����ַ����ȣ�0x3fff����Ϊһ�������ܳ���Ϊ14λ����2^14�ֽ�;
  for(t=0;t<len;t++)
   {
	   save[t]=USART1_RX_BUF[t];
   }
   USART1_RX_STA=0;//�����־λ
	 return 1;
 }
 else
 return 0;
}
int chuankou3_huoqu(char *save)
{
 u8 t;//ѭ������
 u16 len;//�洢��ȡ���ֽ���
 if(USART3_RX_STA&0x8000)//�ж��Ƿ������룬������Ļ���USART_RX_STA���λ����1,ͨ����λ���ж��Ƿ���ܵ����ݣ�
 {
  len=USART3_RX_STA&0x3fff;//��ȡ���ܵ����ַ����ȣ�0x3fff����Ϊһ�������ܳ���Ϊ14λ����2^14�ֽ�;
  for(t=0;t<len;t++)
   {
	   save[t]=USART3_RX_BUF[t];
   }
   USART3_RX_STA=0;//�����־λ
	 return 1;
 }
 else
 return 0;
}
