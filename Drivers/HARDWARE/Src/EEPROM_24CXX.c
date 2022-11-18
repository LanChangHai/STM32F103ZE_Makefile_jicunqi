#include "EEPROM_24CXX.h"

u8 AT24CXX_RcvOneByte(u16 xinhao,u8 qjdz,u16 Addr)
{				  
	u8 temp=0;		  	    																 
  IIC_Start();                                     //��������
	if(xinhao>C16)
	{
		IIC_Send_Byte(qjdz);	   //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(Addr>>8);//���͸ߵ�ַ	    
	}
	else 
	IIC_Send_Byte(qjdz+((Addr/256)<<1));            //����������ַ,д���� 
  IIC_Wait_Ack();	                                 //�ȴ�Ӧ��
  IIC_Send_Byte(Addr%256);                        //���͵͵�ַ
	IIC_Wait_Ack();	                                 //�ȴ�Ӧ��	
  
	IIC_Start();  	 	                               //������������
	IIC_Send_Byte(0xa1);                            //����Ϊ��ģʽ			   
	IIC_Wait_Ack();		                               //�ȴ�Ӧ�� 
  temp=IIC_Read_Byte(0);	                       //���ֽڣ���Ӧ��		   
  IIC_Stop();                                      //��������    
	return temp;
}

void AT24CXX_SendOneByte(u16 xinhao,u8 qjdz,u16 Addr,u8 Data)
{				   	  	    																 
  IIC_Start();                                     //��������
  if(xinhao>C16)
	{
		IIC_Send_Byte(qjdz);	    //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(Addr>>8);//���͸ߵ�ַ	  
	}
	else 
  IIC_Send_Byte(qjdz+((Addr/256)<<1));             //����������ַ,д���� 	
	IIC_Wait_Ack();	                                 //�ȴ�Ӧ��
	IIC_Send_Byte(Addr%256);                         //���͵͵�ַ
	IIC_Wait_Ack();		                               //�ȴ�Ӧ��   
  IIC_Send_Byte(Data);                             //�����ֽ�����
	IIC_Wait_Ack();		                               //�ȴ�Ӧ��
  		    	   
  IIC_Stop();                                      //��������
	delay_ms(10);	                               //����ʱ��֤���������ֽڵ��ȶ���
}

