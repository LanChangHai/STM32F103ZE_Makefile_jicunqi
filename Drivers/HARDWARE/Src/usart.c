#include "usart.h"

#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定向fputc函数
//printf的输出，指向fputc，由fputc输出到串口
//这里使用串口1(USART1)输出printf信息
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//等待上一次串口数据发送完成  
	USART3->DR = (u8) ch;      	//写DR,串口1将发送数据
	return ch;
}
#endif 
//end


//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART1_RX_BUF[USART_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.
u8 USART2_RX_BUF[USART_REC_LEN];
u8 USART3_RX_BUF[USART_REC_LEN];
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;
u16 USART2_RX_STA=0;//接收状态标记
u16 USART3_RX_STA=0;


void usart1_init(u32 pclk2,u32 bound)
{
	float temp;
	u16 zhenshuzhi,xiaoshuzhi;   //波特率配置整数值与小数值
	temp=(float)(pclk2*1000000)/(16*bound);
	zhenshuzhi=temp;
	xiaoshuzhi=(temp-zhenshuzhi)*16;
	zhenshuzhi<<=4;
	RCC->APB2ENR|=1<<2;  //使能gpioa时钟
	RCC->APB2ENR|=1<<14;  //使能串口1
	/********配置gpioa,先初始化***********/
	GPIOA->CRH&=0xFFFFF00F;  
	GPIOA->CRH|=0x000008B0;  
	/*TXD=A9,RXD=A10,TXD要设置为复用推挽输出，RXD要设置为浮空或上拉输入这里是上拉(ODR默认为1)*/
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位
	USART1->BRR=zhenshuzhi+xiaoshuzhi; // 波特率设置	 
	USART1->CR1|=0X200C;  //1位停止,无校验位,使能UE,TE,RE;
	USART1->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	NVIC_Init(3,3,USART1_IRQn,2);//组2，最低优先级 
}

void usart2_init(u32 pclk1,u32 bound)
{
	float temp;
	u16 zhenshuzhi,xiaoshuzhi;   //波特率配置整数值与小数值
	temp=(float)(pclk1*1000000)/(16*bound);
	zhenshuzhi=temp;
	xiaoshuzhi=(temp-zhenshuzhi)*16;
	zhenshuzhi<<=4;
	RCC->APB2ENR|=1<<2;  //使能gpioa时钟
	RCC->APB1ENR|=1<<17;  //使能串口2
	/********配置gpioa,先初始化***********/
	GPIOA->CRL&=0xFFFF00FF;  
	GPIOA->CRL|=0x00008B00;
	/*TXD=A2,RXD=A3,TXD要设置为复用推挽输出，RXD要设置为浮空或上拉输入这里是上拉(ODR默认为1)*/
	RCC->APB1RSTR|=1<<17;   //复位串口1
	RCC->APB1RSTR&=~(1<<17);//停止复位
	USART2->BRR=zhenshuzhi+xiaoshuzhi; // 波特率设置	 
	USART2->CR1|=0X200C;  //1位停止,无校验位,使能UE,TE,RE;
	USART2->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	NVIC_Init(3,2,USART2_IRQn,2);//组2，次低优先级 
}

void usart3_init(u32 pclk1,u32 bound)
{
	float temp;
	u16 zhenshuzhi,xiaoshuzhi;   //波特率配置整数值与小数值
	temp=(float)(pclk1*1000000)/(16*bound);
	zhenshuzhi=temp;
	xiaoshuzhi=(temp-zhenshuzhi)*16;
	zhenshuzhi<<=4;
	RCC->APB2ENR|=1<<3;  //使能gpiob时钟
	RCC->APB1ENR|=1<<18;  //使能串口3
	/********配置gpiob,先初始化***********/
	GPIOB->CRH&=0xFFFF00FF;  
	GPIOB->CRH|=0x00008B00;
	/*TXD=B10,RXD=B11,TXD要设置为复用推挽输出，RXD要设置为浮空或上拉输入这里是上拉(ODR默认为1)*/
	RCC->APB1RSTR|=1<<18;   //复位串口1
	RCC->APB1RSTR&=~(1<<18);//停止复位
	USART3->BRR=zhenshuzhi+xiaoshuzhi; // 波特率设置	 
	USART3->CR1|=0X200C;  //1位停止,无校验位,使能UE,TE,RE;
	USART3->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	NVIC_Init(3,1,USART3_IRQn,2);//组2 
}

void USART1_IRQHandler(void)
{
	u8 res;	
	if(USART1->SR&(1<<5))	//接收到数据
	{	 
		res=USART1->DR;
		if((USART1_RX_STA&0x8000)==0)//接收未完成
		{
				if(res==0x0d)
				  USART1_RX_STA|=0x8000;
				else{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=res;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
	  }		
	}
} 

void USART2_IRQHandler(void)
{
	u8 res;	
	if(USART2->SR&(1<<5))	//接收到数据
	{	 
		res=USART2->DR; 
		if((USART2_RX_STA&0x8000)==0)//接收未完成
		{
			
				if(res==0x0d)USART2_RX_STA|=0x8000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=res;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}  		 									     
	}
}
void USART3_IRQHandler(void)
{
	u8 res;	
	if(USART3->SR&(1<<5))	//接收到数据
	{	 	
		res=USART3->DR; 
//		if((USART3_RX_STA&0x8000)==0)//接收未完成
//		{
			
				if(res==0x0d){
					USART3_RX_BUF[USART3_RX_STA&0X3FFF]=res;
					USART3_RX_STA++;
					USART3_RX_STA|=0x8000;
				}
				else
				{
					USART3_RX_BUF[USART3_RX_STA&0X3FFF]=res;
					USART3_RX_STA++;
					if(USART3_RX_STA>(USART_REC_LEN-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
//		}	
	}
}

void Send_char(USART_TypeDef *Usart,char c){  //发送一个字符
	while((Usart->SR&0X40)==0);//等待上一次串口数据发送完成  
	Usart->DR = c;      	//写DR,串口1将发送数据
    return;
}

void Send_string(USART_TypeDef *Usart,char string[]){
	
	int size=strlen(string);
	for(int i=0;i<size;i++){
	  Send_char(Usart,string[i]);
	}
	return;
}
