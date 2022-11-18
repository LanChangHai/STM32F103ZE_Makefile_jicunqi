#include "12864.h"

uint8_t LCD_addr[4][8]={
	{0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87},  		//��һ��
	{0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97},		//�ڶ���
	{0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F},		//������
	{0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F}		//������
	};


void SendByte(u8 byte)
{
     u8 i; 
	  for(i = 0;i < 8;i++)
    {
        if((byte << i) & 0x80)  //0x80(1000 0000)  ֻ�ᱣ�����λ
		{
		    RW = 1;           // ��������ߵ�ƽ��������1
		}
		else
		{
			RW = 0;         // ��������͵�ƽ��������0
		}
		E = 0;   //ʱ�����õ�  ����SID�仯
		delay_us(5); //��ʱʹ����д��
		E = 1;    //����ʱ�ӣ��ôӻ���SID
	}   
}

/*
   ����gpio��ʼ����������ѡ���io�ı�
*/

void lcd_GPIO_init(void)
{
	 RCC->APB2ENR|=(1<<2);//ʹ��gpioA
	 GPIOA->CRL=0X33000000;
//	 GPIOA->CRH=0X33333333;
	 RW=1;
	 E=1;
}


void Lcd_WriteCmd(u8 Cmd )
{
     delay_ms(1);    
     SendByte(WRITE_CMD);              
     SendByte(0xf0&Cmd);      
     SendByte(Cmd<<4);  
}


void Lcd_WriteData(u8 Dat )
{
     delay_ms(1);     
     SendByte(WRITE_DAT);            
     SendByte(0xf0&Dat);      
     SendByte(Dat<<4);   
}

void Lcd_Init(void)
{ 
	  lcd_GPIO_init();
    delay_ms(50);   	//�ȴ�Һ���Լ죨��ʱ>40ms��
	Lcd_WriteCmd(0x30);        //�����趨:ѡ�����ָ�  ��ѡ��8bit������
    delay_ms(1);//��ʱ>137us 
    Lcd_WriteCmd(0x0c);        //����ʾ
    delay_ms(1);	//��ʱ>100us
    Lcd_WriteCmd(0x01);        //�����ʾ�������趨��ַָ��Ϊ00H
    delay_ms(30);	//��ʱ>10ms
	Lcd_WriteCmd(0x06);        //ÿ�ε�ַ�Զ�+1����ʼ�����
}


void LCD_Display_Words(uint8_t x,uint8_t y,uint8_t*str)
{ 
	Lcd_WriteCmd(LCD_addr[x][y]); //д��ʼ���λ��
	while(*str>0)
    { 
      Lcd_WriteData(*str);    //д����
      str++;     
    }
}

void LCD_Danzijie(uint8_t x,uint8_t y,u8 zi)
{
	Lcd_WriteCmd(LCD_addr[x][y]); //д��ʼ���λ��
	Lcd_WriteData(zi);    //д����
}

void LCD_Clear(void)
{
	Lcd_WriteCmd(0x01);			//����ָ��
	delay_ms(2);				//��ʱ�Դ�Һ���ȶ�������1.6ms��
}

void LCD_Display_Picture(uint8_t *img)
{
		uint8_t x,y,i;
		Lcd_WriteCmd(0x34);		//�л�������ָ��
		Lcd_WriteCmd(0x34);		//�ر�ͼ����ʾ
		for(i = 0; i < 1; i++)   //������д��
		{
			for(y=0;y<32;y++)   //��ֱYд32��
			{  
				for(x=0;x<8;x++)   //����Xд8��
				{
					Lcd_WriteCmd(0x80 + y);		//�е�ַ
					Lcd_WriteCmd(0x80 + x+i);		//�е�ַ
					Lcd_WriteData(*img ++);		//д��λ�ֽ����� D15��D8   
					Lcd_WriteData(*img ++);		//д��λ�ֽ����� D7��D0
				}
			}
		}
		Lcd_WriteCmd(0x36);//��ͼ����ʾ		
		Lcd_WriteCmd(0x30);        //�л��ػ���ָ��
}

