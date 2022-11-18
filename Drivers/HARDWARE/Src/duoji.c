#include<reg52.h>
#include<intrins.h>

typedef unsigned char u8;

u8 num=0,sum=0;
bit key1=0,key2=1;

sbit pwm=P2^0;

void main(){
	pwm=0;
	TMOD = 0x02; 
	TH0 = 72;    
	TL0 = 72;    
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	while(1){
		if(sum<=((num+45)/18))
			pwm=1;
		else
			pwm=0;
		if(key1==1){
			key1=0;
			if(num==180||num==0)
			key2=!key2;
			if(key2)
				num--;
			else
				num++;
		}
	}
}

void Tim0() interrupt 1{
	if(sum<100)
	{
		sum++;
	}
	else
	{
		sum=0;
		key1=1;
	}
}