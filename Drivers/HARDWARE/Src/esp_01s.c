#include "esp_01s.h"

char save[100];

void __attribute__((weak)) Esp_Usart_Init(void){
	usart3_init(36,115200);
}

void Esp_Init(){

	Esp_Usart_Init();

}

u8 Hand(char *duibi){  //对比符合子字符串
	memset(save,0,sizeof(save));
	if(chuankou3_huoqu(save)){
	  if(strstr(save,duibi)){
		 Send_string(USART1,"esp_01s:");
		 Send_string(USART1,save);
		 return 1;
	  }
	  else
	  return 0;
	}else
	 return 0;
}

u8 Hand_Save(char *Enter_save,char *duibi){  //对比符合子字符串，并储存
	if(chuankou3_huoqu(Enter_save)){
	  if(strstr(Enter_save,duibi)){
		 Send_string(USART1,"esp_01s:");
		 Send_string(USART1,Enter_save);
		 return 1;
	  }
	  else
	  return 0;
	}else
	  return 0;
}

void Direct_Hand(char *zhiling,char *duibi){
	while(1){
		printf("%s",zhiling);
		if(Hand(duibi)){ 
			return;
		}
	}
}

char *Seek_Save(char *zhiling,char *Enter_save,char *duibi){ //执行指令，对比符合子字符串，并储存，返回查找到的指针
	while(1){
		printf("%s",zhiling);
		if(Hand_Save(Enter_save,duibi)){ 
			return strstr(Enter_save,duibi);
		}
	}
}

void intercept_sava(char *zhiling,char *Enter_save,char *duibi,int n){ //执行指令，对比符合子字符串，截取需要的子字符串，并储存
	while(1){
		memset(save,0,sizeof(save));
		printf("%s",zhiling);
		if(Hand_Save(save,duibi)){ 
			strncpy(Enter_save,strstr(save,duibi)+strlen(duibi),n);
			return;
		}
	}
}









