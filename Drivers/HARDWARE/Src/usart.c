#include "usart.h"

#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc����
//printf�������ָ��fputc����fputc���������
//����ʹ�ô���1(USART1)���printf��Ϣ
int fputc(int ch, FILE *f)
{      
	while((USART3->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
	USART3->DR = (u8) ch;      	//дDR,����1����������
	return ch;
}
#endif 
//end


//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART1_RX_BUF[USART_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.
u8 USART2_RX_BUF[USART_REC_LEN];
u8 USART3_RX_BUF[USART_REC_LEN];
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART1_RX_STA=0;
u16 USART2_RX_STA=0;//����״̬���
u16 USART3_RX_STA=0;


void usart1_init(u32 pclk2,u32 bound)
{
	float temp;
	u16 zhenshuzhi,xiaoshuzhi;   //��������������ֵ��С��ֵ
	temp=(float)(pclk2*1000000)/(16*bound);
	zhenshuzhi=temp;
	xiaoshuzhi=(temp-zhenshuzhi)*16;
	zhenshuzhi<<=4;
	RCC->APB2ENR|=1<<2;  //ʹ��gpioaʱ��
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���1
	/********����gpioa,�ȳ�ʼ��***********/
	GPIOA->CRH&=0xFFFFF00F;  
	GPIOA->CRH|=0x000008B0;  
	/*TXD=A9,RXD=A10,TXDҪ����Ϊ�������������RXDҪ����Ϊ���ջ�������������������(ODRĬ��Ϊ1)*/
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ
	USART1->BRR=zhenshuzhi+xiaoshuzhi; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ,ʹ��UE,TE,RE;
	USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
}

void usart2_init(u32 pclk1,u32 bound)
{
	float temp;
	u16 zhenshuzhi,xiaoshuzhi;   //��������������ֵ��С��ֵ
	temp=(float)(pclk1*1000000)/(16*bound);
	zhenshuzhi=temp;
	xiaoshuzhi=(temp-zhenshuzhi)*16;
	zhenshuzhi<<=4;
	RCC->APB2ENR|=1<<2;  //ʹ��gpioaʱ��
	RCC->APB1ENR|=1<<17;  //ʹ�ܴ���2
	/********����gpioa,�ȳ�ʼ��***********/
	GPIOA->CRL&=0xFFFF00FF;  
	GPIOA->CRL|=0x00008B00;
	/*TXD=A2,RXD=A3,TXDҪ����Ϊ�������������RXDҪ����Ϊ���ջ�������������������(ODRĬ��Ϊ1)*/
	RCC->APB1RSTR|=1<<17;   //��λ����1
	RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ
	USART2->BRR=zhenshuzhi+xiaoshuzhi; // ����������	 
	USART2->CR1|=0X200C;  //1λֹͣ,��У��λ,ʹ��UE,TE,RE;
	USART2->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	NVIC_Init(3,2,USART2_IRQn,2);//��2���ε����ȼ� 
}

void usart3_init(u32 pclk1,u32 bound)
{
	float temp;
	u16 zhenshuzhi,xiaoshuzhi;   //��������������ֵ��С��ֵ
	temp=(float)(pclk1*1000000)/(16*bound);
	zhenshuzhi=temp;
	xiaoshuzhi=(temp-zhenshuzhi)*16;
	zhenshuzhi<<=4;
	RCC->APB2ENR|=1<<3;  //ʹ��gpiobʱ��
	RCC->APB1ENR|=1<<18;  //ʹ�ܴ���3
	/********����gpiob,�ȳ�ʼ��***********/
	GPIOB->CRH&=0xFFFF00FF;  
	GPIOB->CRH|=0x00008B00;
	/*TXD=B10,RXD=B11,TXDҪ����Ϊ�������������RXDҪ����Ϊ���ջ�������������������(ODRĬ��Ϊ1)*/
	RCC->APB1RSTR|=1<<18;   //��λ����1
	RCC->APB1RSTR&=~(1<<18);//ֹͣ��λ
	USART3->BRR=zhenshuzhi+xiaoshuzhi; // ����������	 
	USART3->CR1|=0X200C;  //1λֹͣ,��У��λ,ʹ��UE,TE,RE;
	USART3->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	NVIC_Init(3,1,USART3_IRQn,2);//��2 
}

void USART1_IRQHandler(void)
{
	u8 res;	
	if(USART1->SR&(1<<5))	//���յ�����
	{	 
		res=USART1->DR;
		if((USART1_RX_STA&0x8000)==0)//����δ���
		{
				if(res==0x0d)
				  USART1_RX_STA|=0x8000;
				else{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=res;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
	  }		
	}
} 

void USART2_IRQHandler(void)
{
	u8 res;	
	if(USART2->SR&(1<<5))	//���յ�����
	{	 
		res=USART2->DR; 
		if((USART2_RX_STA&0x8000)==0)//����δ���
		{
			
				if(res==0x0d)USART2_RX_STA|=0x8000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=res;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}  		 									     
	}
}
void USART3_IRQHandler(void)
{
	u8 res;	
	if(USART3->SR&(1<<5))	//���յ�����
	{	 	
		res=USART3->DR; 
//		if((USART3_RX_STA&0x8000)==0)//����δ���
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
					if(USART3_RX_STA>(USART_REC_LEN-1))USART3_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
//		}	
	}
}

void Send_char(USART_TypeDef *Usart,char c){  //����һ���ַ�
	while((Usart->SR&0X40)==0);//�ȴ���һ�δ������ݷ������  
	Usart->DR = c;      	//дDR,����1����������
    return;
}

void Send_string(USART_TypeDef *Usart,char string[]){
	
	int size=strlen(string);
	for(int i=0;i<size;i++){
	  Send_char(Usart,string[i]);
	}
	return;
}
