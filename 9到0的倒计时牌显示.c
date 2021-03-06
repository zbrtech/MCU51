#include<reg52.h>

sbit ADDR0 = P1^0;
sbit ADDR1 = P1^1;
sbit ADDR2 = P1^2;
sbit ADDR3 = P1^3;
sbit ENLED = P1^4;

unsigned char code image[10][8] = {
    {0xFF,0xE7,0xDB,0xDB,0xC3,0xDF,0xDB,0xE7},
	{0xFF,0xE7,0xDB,0xDB,0xE7,0xDB,0xDB,0xE7},
	{0xFF,0xC3,0xDF,0xDF,0xDF,0xDF,0xDF,0xFF},
	{0xFF,0xE7,0xFB,0xFB,0xE3,0xDB,0xDB,0xE7},
	{0xFF,0xC3,0xFB,0xFB,0xE3,0xDF,0xDF,0xE3},
	{0xFF,0xDF,0xCF,0xD7,0xDB,0x83,0xDF,0xDF},
	{0xFF,0xE3,0xDF,0xDF,0xE3,0xDF,0xDF,0xE3},
	{0xFF,0xE7,0xDB,0xDF,0xEF,0xF7,0xC3,0xFF},
	{0xFF,0xEF,0xE7,0xEF,0xEF,0xEF,0xEF,0xC7},
	{0xFF,0xE7,0xDB,0xDB,0xDB,0xDB,0xE7,0xFF},
};

void main()
{
	EA = 1;
	ENLED = 0;
	ADDR3 = 0;
	TMOD = 0x01;
	TH0 = 0xFC;
	TL0 = 0x67;
	ET0 = 1;
	TR0 =1;
    while(1);
}

void InterrptTimer0() interrupt 1
{
    static unsigned char i = 0;
	static unsigned int cnt = 0;
	static unsigned char sec =0; 

	TH0 = 0xFC;
	TL0 = 0x67;
	cnt++;
	P0 = 0xFF;
	switch(i)
	{
	   case 0:ADDR2=0;ADDR1=0;ADDR0=0;i++;P0=image[sec][0];break;
	   case 1:ADDR2=0;ADDR1=0;ADDR0=1;i++;P0=image[sec][1];break;
	   case 2:ADDR2=0;ADDR1=1;ADDR0=0;i++;P0=image[sec][2];break;
	   case 3:ADDR2=0;ADDR1=1;ADDR0=1;i++;P0=image[sec][3];break;
	   case 4:ADDR2=1;ADDR1=0;ADDR0=0;i++;P0=image[sec][4];break;
	   case 5:ADDR2=1;ADDR1=0;ADDR0=1;i++;P0=image[sec][5];break;
	   case 6:ADDR2=1;ADDR1=1;ADDR0=0;i++;P0=image[sec][6];break;
	   case 7:ADDR2=1;ADDR1=1;ADDR0=1;i=0;P0=image[sec][7];break;
	   default:break;
	}
	  if(cnt >= 1000)
	   {
	   	  cnt = 0;
		  if(sec == 9)
		  sec = 0;
		  else
		  sec++;
		  }
}