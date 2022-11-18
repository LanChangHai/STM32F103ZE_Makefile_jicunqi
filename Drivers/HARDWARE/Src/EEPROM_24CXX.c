#include "EEPROM_24CXX.h"

u8 AT24CXX_RcvOneByte(u16 xinhao,u8 qjdz,u16 Addr)
{				  
	u8 temp=0;		  	    																 
  IIC_Start();                                     //启动总线
	if(xinhao>C16)
	{
		IIC_Send_Byte(qjdz);	   //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(Addr>>8);//发送高地址	    
	}
	else 
	IIC_Send_Byte(qjdz+((Addr/256)<<1));            //发送器件地址,写数据 
  IIC_Wait_Ack();	                                 //等待应答
  IIC_Send_Byte(Addr%256);                        //发送低地址
	IIC_Wait_Ack();	                                 //等待应答	
  
	IIC_Start();  	 	                               //重新启动总线
	IIC_Send_Byte(0xa1);                            //设置为读模式			   
	IIC_Wait_Ack();		                               //等待应答 
  temp=IIC_Read_Byte(0);	                       //读字节，非应答		   
  IIC_Stop();                                      //结束总线    
	return temp;
}

void AT24CXX_SendOneByte(u16 xinhao,u8 qjdz,u16 Addr,u8 Data)
{				   	  	    																 
  IIC_Start();                                     //启动总线
  if(xinhao>C16)
	{
		IIC_Send_Byte(qjdz);	    //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(Addr>>8);//发送高地址	  
	}
	else 
  IIC_Send_Byte(qjdz+((Addr/256)<<1));             //发送器件地址,写数据 	
	IIC_Wait_Ack();	                                 //等待应答
	IIC_Send_Byte(Addr%256);                         //发送低地址
	IIC_Wait_Ack();		                               //等待应答   
  IIC_Send_Byte(Data);                             //发送字节数据
	IIC_Wait_Ack();		                               //等待应答
  		    	   
  IIC_Stop();                                      //结束总线
	delay_ms(10);	                               //该延时保证连续发送字节的稳定性
}

