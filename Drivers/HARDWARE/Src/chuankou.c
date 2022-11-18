#include "chuankou.h"
int chuankou2_huoqu(char *save)
{
 u8 t;//循环变量
 u16 len;//存储获取的字节数
 if(USART2_RX_STA&0x8000)//判断是否有输入，有输入的话，USART_RX_STA最高位被置1,通过按位与判断是否接受到数据；
 {
  len=USART2_RX_STA&0x3fff;//获取接受到的字符长度，0x3fff是因为一次最大接受长度为14位，即2^14字节;
  for(t=0;t<len;t++)
   {
	   save[t]=USART2_RX_BUF[t];
   }
   USART2_RX_STA=0;//清除标志位
	 return 1;
 }
 else
 return 0;
}
int chuankou1_huoqu(char *save)
{
 u8 t;//循环变量
 u16 len;//存储获取的字节数
 if(USART1_RX_STA&0x8000)//判断是否有输入，有输入的话，USART_RX_STA最高位被置1,通过按位与判断是否接受到数据；
 {
  len=USART1_RX_STA&0x3fff;//获取接受到的字符长度，0x3fff是因为一次最大接受长度为14位，即2^14字节;
  for(t=0;t<len;t++)
   {
	   save[t]=USART1_RX_BUF[t];
   }
   USART1_RX_STA=0;//清除标志位
	 return 1;
 }
 else
 return 0;
}
int chuankou3_huoqu(char *save)
{
 u8 t;//循环变量
 u16 len;//存储获取的字节数
 if(USART3_RX_STA&0x8000)//判断是否有输入，有输入的话，USART_RX_STA最高位被置1,通过按位与判断是否接受到数据；
 {
  len=USART3_RX_STA&0x3fff;//获取接受到的字符长度，0x3fff是因为一次最大接受长度为14位，即2^14字节;
  for(t=0;t<len;t++)
   {
	   save[t]=USART3_RX_BUF[t];
   }
   USART3_RX_STA=0;//清除标志位
	 return 1;
 }
 else
 return 0;
}
