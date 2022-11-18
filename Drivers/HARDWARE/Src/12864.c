#include "12864.h"

uint8_t LCD_addr[4][8]={
	{0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87},  		//第一行
	{0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97},		//第二行
	{0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F},		//第三行
	{0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F}		//第四行
	};


void SendByte(u8 byte)
{
     u8 i; 
	  for(i = 0;i < 8;i++)
    {
        if((byte << i) & 0x80)  //0x80(1000 0000)  只会保留最高位
		{
		    RW = 1;           // 引脚输出高电平，代表发送1
		}
		else
		{
			RW = 0;         // 引脚输出低电平，代表发送0
		}
		E = 0;   //时钟线置低  允许SID变化
		delay_us(5); //延时使数据写入
		E = 1;    //拉高时钟，让从机读SID
	}   
}

/*
   下面gpio初始化函数根据选择的io改变
*/

void lcd_GPIO_init(void)
{
	 RCC->APB2ENR|=(1<<2);//使能gpioA
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
    delay_ms(50);   	//等待液晶自检（延时>40ms）
	Lcd_WriteCmd(0x30);        //功能设定:选择基本指令集  ，选择8bit数据流
    delay_ms(1);//延时>137us 
    Lcd_WriteCmd(0x0c);        //开显示
    delay_ms(1);	//延时>100us
    Lcd_WriteCmd(0x01);        //清除显示，并且设定地址指针为00H
    delay_ms(30);	//延时>10ms
	Lcd_WriteCmd(0x06);        //每次地址自动+1，初始化完成
}


void LCD_Display_Words(uint8_t x,uint8_t y,uint8_t*str)
{ 
	Lcd_WriteCmd(LCD_addr[x][y]); //写初始光标位置
	while(*str>0)
    { 
      Lcd_WriteData(*str);    //写数据
      str++;     
    }
}

void LCD_Danzijie(uint8_t x,uint8_t y,u8 zi)
{
	Lcd_WriteCmd(LCD_addr[x][y]); //写初始光标位置
	Lcd_WriteData(zi);    //写数据
}

void LCD_Clear(void)
{
	Lcd_WriteCmd(0x01);			//清屏指令
	delay_ms(2);				//延时以待液晶稳定【至少1.6ms】
}

void LCD_Display_Picture(uint8_t *img)
{
		uint8_t x,y,i;
		Lcd_WriteCmd(0x34);		//切换到扩充指令
		Lcd_WriteCmd(0x34);		//关闭图形显示
		for(i = 0; i < 1; i++)   //上下屏写入
		{
			for(y=0;y<32;y++)   //垂直Y写32次
			{  
				for(x=0;x<8;x++)   //横向X写8次
				{
					Lcd_WriteCmd(0x80 + y);		//行地址
					Lcd_WriteCmd(0x80 + x+i);		//列地址
					Lcd_WriteData(*img ++);		//写高位字节数据 D15－D8   
					Lcd_WriteData(*img ++);		//写低位字节数据 D7－D0
				}
			}
		}
		Lcd_WriteCmd(0x36);//打开图形显示		
		Lcd_WriteCmd(0x30);        //切换回基本指令
}

