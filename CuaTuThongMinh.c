#include <16f877a.h>
#FUSES NOWDT, HS, NOPROTECT
#USE DELAY (CLOCK = 20M)
#define  LCD_RS_PIN Pin_D0
#define  LCD_RW_PIN Pin_D1
#define  LCD_ENABLE_PIN  Pin_D2
#define  LCD_DATA4   pin_D4
#define  LCD_DATA5   pin_D5
#define  LCD_DATA6   pin_D6
#define  LCD_DATA7   pin_D7
#include <LCD.C>
#use rs232(baud=9600,xmit=PIN_C6,rcv=PIN_C7)
char  str[9], num[3];
unsigned char code[13] = {' ','1','4','7','*','2','5','8','0','3','6','9','#'};
Int stt, sc=0, cnt, slide=1, key=13;
Int8  i=0, j=0;

#INT_RDA
Void Ngat ()
{
   for(j=1;j<=12;j++)
   {
       str[j] = getc();
   }
   If (stt==6) stt=4;
   setup_uart(FALSE);
}

Void Screen1 ()
{
   If(stt==4)                  //them the
   {
      LCD_GOTOXY(5,2);
      For (i=2;i<=12;i++)
      {
         lCD_PUTC(str[i]);
      }
   }

   if(stt==0)                 //kiem tra mat khau
   {
      If (j>=12)              //quet the
      {
         LCD_GOTOXY(8,2);
         lCD_PUTC("****");
         Delay_ms(700);
      }
      else                    //nhap mat khau
      lCD_PUTC('*');
   }

   If(stt==2)                 //doi mk
   {
      lCD_PUTC(num[i]);
   }
}

Void Save ()
{
   if (stt==5)                                //xoa the
   {
/////////////////////////////////////////////      slide 1
      if (sc==1)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x10 + i,' ');
         }
      }
      if (sc==2)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x20 + i,' ');
         }
      }
      if (sc==3)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x30 + i,' ');
         }
      }
/////////////////////////////////////////////      slide 2
      if (sc==4)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x40 + i,' ');
         }
      }
      if (sc==5)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x50 + i,' ');
         }
      }
      if (sc==6)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x60 + i,' ');
         }
      }
/////////////////////////////////////////////////      slide 3
      if (sc==7)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x70 + i,' ');
         }
      }
      if (sc==8)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x80 + i,' ');
         }
      }
      if (sc==9)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x90 + i,' ');
         }
      }
      lcd_putc('\f');
      LCD_GOTOXY(25,1);
      lCD_PUTC("DELETING...");
      Goto A;
   }
   
   if (stt==2)                               //luu mk moi
   {
      for (i=1;i<=4;)
      {
         if (i==1)   
         {
            write_eeprom(0x00 + i,num[i]);
         }
         if (i==2)   
         {
            write_eeprom(0x00 + i,num[i]);
         }
         if (i==3)   
         {
            write_eeprom(0x00 + i,num[i]);
         }
         if (i==4)   
         {
            write_eeprom(0x00 + i,num[i]);
         }
         I++;
      }
   }
   
   if (stt==4)                                //them the
   {
/////////////////////////////////////////////      slide 1
      if (sc==1)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x10 + i,str[i]);
         }
      }
      if (sc==2)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x20 + i,str[i]);
         }
      }
      if (sc==3)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x30 + i,str[i]);
         }
      }
/////////////////////////////////////////////      slide 2
      if (sc==4)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x40 + i,str[i]);
         }
      }
      if (sc==5)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x50 + i,str[i]);
         }
      }
      if (sc==6)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x60 + i,str[i]);
         }
      }
/////////////////////////////////////////////////      slide 3
      if (sc==7)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x70 + i,str[i]);
         }
      }
      if (sc==8)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x80 + i,str[i]);
         }
      }
      if (sc==9)
      {
         for (i=1;i<=12;i++)
         {
            write_eeprom(0x90 + i,str[i]);
         }
      }
      Screen1 ();
   }

      LCD_GOTOXY(27,1);
      lCD_PUTC("SAVING...");
A:    Output_high(Pin_A1);
      Output_high(Pin_A2);
      Delay_ms(1500);
      Output_low(Pin_A1);
      Output_low(Pin_A2);
      Stt=0;
      write_eeprom(0x08, stt);
      reset_cpu();
}

Void Keypad ()
{
      key=13;
      // quet cot 1
      output_high(pin_b5);
      Output_low(pin_b6);
      Output_low(pin_b7);
      while(input(pin_b1)==1) key=1;
      while(input(pin_b2)==1) key=2;
      while(input(pin_b3)==1) key=3;
      while(input(pin_b4)==1) key=4;
      // quet cot 2
      output_high(pin_b6);
      Output_low(pin_b5);
      Output_low(pin_b7);
      while(input(pin_b1)==1) key=5;
      while(input(pin_b2)==1) key=6;
      while(input(pin_b3)==1) key=7;
      while(input(pin_b4)==1) key=8;
      // quet cot 3
      output_high(pin_b7);
      Output_low(pin_b5);
      Output_low(pin_b6);
      while(input(pin_b1)==1) key=9;
      while(input(pin_b2)==1) key=10;
      while(input(pin_b3)==1) key=11;
      while(input(pin_b4)==1) key=12;
         
      If (key==12)
      {
         If (slide>=3)  slide=1;
         else  Slide++;
      }
}

Void Screen_Select ()
{
   lcd_putc('\f');
   LCD_GOTOXY(1,1);
   lCD_PUTC("1: ADD CARD");
   LCD_GOTOXY(1,2);
   lCD_PUTC("2: CHANGE PASS");
   LCD_GOTOXY(21,1);
   lCD_PUTC("3: REMOVE CARD");
   LCD_GOTOXY(21,2);
   lCD_PUTC("BACK (*)");
   for (i=0;i<1;)
   {
      Keypad ();
      if (key==1)
      {
         stt=1;
         write_eeprom(0x08, stt);
         i++;
      }
      If (key==4)
      {
         stt=0;
         write_eeprom(0x08, stt);
         i++;
      }
      if (key==5)
      {
         stt=2;
         write_eeprom(0x08, stt);
         i++;
      }
      if (key==9)
      {
         stt=3;
         write_eeprom(0x08, stt);
         i++;
      }
   }
}

Void Mo_Cua ()
{
   Cnt=0;
   write_eeprom(0x09, cnt);
   stt=0;
   write_eeprom(0x08, stt);
   for (i=0;i<10;i++)
   {
      keypad();
      If (key==4) break;
      Output_high(Pin_A0);
      Output_high(Pin_A1);
      Output_high(Pin_A2);
      Delay_ms(10);
   }
   for (i=0;i<10;i++)
   {
      keypad();
      If (key==4) break;
      Output_low(Pin_A1);
      Delay_ms(10);
   }
   for (i=0;i<10;i++)
   {
      keypad();
      If (key==4) break;
      Output_high(Pin_A1);
      Delay_ms(10);
   }
   for (i=0;i<100;i++)
   {
      keypad();
      If (key==4) break;
      Output_low(Pin_A1);
      Delay_ms(27);
   }
   Output_low(Pin_A0);
   Output_low(Pin_A2);
}

Void Khoa_Cua ()
{
   Output_low(Pin_A0);
   Output_high(Pin_A1);
   Output_high(Pin_A2);
   Delay_ms(1000);
   Output_low(Pin_A1);
   Output_low(Pin_A2);
   if (cnt!=3) Cnt++;
   stt=0;
   write_eeprom(0x08, stt);
   write_eeprom(0x09, cnt);
}

Void  test ()
{
   lcd_putc('\f');
   if (j>=12)
   {
            For (j=1;j<=12;)
            {
               if (str[j] == read_eeprom(0x10 + j))  j++;
               else  Break;
            }
            If (j==13) Goto A;
            For (j=1;j<=12;)
            {
               if (str[j] == read_eeprom(0x20 + j))  j++;
               else  break;
            }
            If (j==13) Goto A;
            For (j=1;j<=12;)
            {
               if (str[j] == read_eeprom(0x30 + j))  j++;
               else  Break;
            }
            If (j==13) Goto A;

            For (j=1;j<=12;)
            {
               if (str[j] == read_eeprom(0x40 + j))  j++;
               else  break;
            }
            If (j==13) Goto A;
            For (j=1;j<=12;)
            {
               if (str[j] == read_eeprom(0x50 + j))  j++;
               else  Break;
            }
            If (j==13) Goto A;
            For (j=1;j<=12;)
            {
               if (str[j] == read_eeprom(0x60 + j))  j++;
               else  break;
            }
            If (j==13) Goto A;
            For (j=1;j<=12;)
            {
               if (str[j] == read_eeprom(0x70 + j))  j++;
               else  Break;
            }
            If (j==13) Goto A;

            For (j=1;j<=12;)
            {
               if (str[j] == read_eeprom(0x80 + j))  j++;
               else  break;
            }
            If (j==13) Goto A;
            For (j=1;j<=12;)
            {
               if (str[j] == read_eeprom(0x90 + j))  j++;
               else 
               {
                  LCD_GOTOXY(4,1);
                  lCD_PUTC("WRONG PASSWORD");
                  LCD_GOTOXY(25,1);
                  lCD_PUTC("DOOR LOCKED...");
                  Khoa_Cua ();
                  Goto B;
               }
            }
            If (j==13) Goto A;
            
   }
   else if (i>=4)
   {
      for (i=1;i<=4;)
      {
         if (num[i] == read_eeprom(0x00 + i))
         {
            i++;
         }
         else 
         {
            LCD_GOTOXY(4,1);
            lCD_PUTC("WRONG PASSWORD");
            LCD_GOTOXY(25,1);
            lCD_PUTC("DOOR LOCKED...");
            Khoa_Cua ();
            GOTO B;
         }
      }
   }
A:    LCD_GOTOXY(7,1);
      lCD_PUTC("WELLCOME");
      LCD_GOTOXY(25,1);
      lCD_PUTC("DOOR OPENED...");
      LCD_GOTOXY(21,2);
      lCD_PUTC("PRESS (*) TO SETTING");
      Mo_Cua ();
      If (key==4) Screen_Select ();
B:    I=0;
      J=0;
      reset_cpu();
}

Void Mode1 ()
{
A: lcd_putc('\f');
   LCD_GOTOXY(1,1);
   lCD_PUTC("ENTER THE PASSWORD..");
   LCD_GOTOXY(21,1);
   Printf(lCD_PUTC,"ALLOWED: %d", 3-cnt);
   LCD_GOTOXY(21,2);
   lCD_PUTC("(#) CLEAR");
   LCD_GOTOXY(8,2);
   for (i=1;i<=4;)
   {
      Keypad ();
      If (key==12) 
      {
         i=1;
         Goto A;
      }
      else If (key!=13)
      {
         num[i]=code[key];
         Screen1 ();
         i++;
      }
      else If (j>=12)  
      {
         Screen1 ();
         break;
      }
      if (cnt == 3)
      {
         Output_low(Pin_A0);
         Output_high(Pin_A1);
         Output_low(Pin_A2);
         Delay_ms(50);
         Output_low(Pin_A1);
         Output_high(Pin_A2);
         Delay_ms(50);
      }
   }
   Delay_ms(300);
   test ();
}

Void Mode2 ()
{
   setup_uart(FALSE);
   lcd_putc('\f');
   LCD_GOTOXY(21,2);
   lCD_PUTC("BACK (*)      (#) >>");
   for (i=1;i<=1;)
   {
      Keypad ();
      If (key==4)
      {
         Screen_Select ();
         reset_cpu();
      }
      If (slide==1)
      {
         LCD_GOTOXY(1,1);
         lCD_PUTC("1: ADD CARD 1");
         LCD_GOTOXY(1,2);
         lCD_PUTC("2: ADD CARD 2");
         LCD_GOTOXY(21,1);
         lCD_PUTC("3: ADD CARD 3");
         if (key==1)
         {
            lcd_putc('\f');
            LCD_GOTOXY(1,1);
            lCD_PUTC("PLEASE SCAN CARD...");
            sc=1;
            i++;
         }
         if (key==5)
         {
            lcd_putc('\f');
            LCD_GOTOXY(1,1);
            lCD_PUTC("PLEASE SCAN CARD...");
            sc=2;
            i++;
         }
         if (key==9)
         {
            lcd_putc('\f');
            LCD_GOTOXY(1,1);
            lCD_PUTC("PLEASE SCAN CARD...");
            sc=3;
            i++;
         }
      }
      if (slide==2)
      {
         LCD_GOTOXY(1,1);
         lCD_PUTC("4: ADD CARD 4");
         LCD_GOTOXY(1,2);
         lCD_PUTC("5: ADD CARD 5");
         LCD_GOTOXY(21,1);
         lCD_PUTC("6: ADD CARD 6");
         if (key==2)
         {
            lcd_putc('\f');
            LCD_GOTOXY(1,1);
            lCD_PUTC("PLEASE SCAN CARD...");
            sc=4;
            i++;
         }
         if (key==6)
         {
            lcd_putc('\f');
            LCD_GOTOXY(1,1);
            lCD_PUTC("PLEASE SCAN CARD...");
            sc=5;
            i++;
         }
         if (key==10)
         {
            lcd_putc('\f');
            LCD_GOTOXY(1,1);
            lCD_PUTC("PLEASE SCAN CARD...");
            sc=6;
            i++;
         }
      }
      if (slide==3)
      {
         LCD_GOTOXY(1,1);
         lCD_PUTC("7: ADD CARD 7");
         LCD_GOTOXY(1,2);
         lCD_PUTC("8: ADD CARD 8");
         LCD_GOTOXY(21,1);
         lCD_PUTC("9: ADD CARD 9");
         if (key==3)
         {
            lcd_putc('\f');
            LCD_GOTOXY(1,1);
            lCD_PUTC("PLEASE SCAN CARD...");
            sc=7;
            i++;
         }
         if (key==7)
         {
            lcd_putc('\f');
            LCD_GOTOXY(1,1);
            lCD_PUTC("PLEASE SCAN CARD...");
            sc=8;
            i++;
         }
         if (key==11)
         {
            lcd_putc('\f');
            LCD_GOTOXY(1,1);
            lCD_PUTC("PLEASE SCAN CARD...");
            sc=9;
            i++;
         }
      }
   }
   Stt=6;
   setup_uart(TRUE);
}

Void Mode3 ()
{
   setup_uart(FALSE);
A: lcd_putc('\f');
   LCD_GOTOXY(1,1);
   lCD_PUTC("ENTER NEW PASSWORD");
   LCD_GOTOXY(21,2);
   lCD_PUTC("BACK (*)   (#) CLEAR");
   LCD_GOTOXY(8,2);
   for (i=1;i<5;)
   {
      Keypad ();
      If (key==4)
      {
         Screen_Select ();
         reset_cpu();
      }
      If (key==12) 
      {
         i=1;
         Goto A;
      }
      If (key!=13)
      {
         num[i]=code[key];
         Screen1 ();
         i++;
      }
   }
   Save ();
}

Void Mode4 ()
{
   setup_uart(FALSE);
   lcd_putc('\f');
   LCD_GOTOXY(21,2);
   lCD_PUTC("BACK (*)      (#) >>");
   for (i=1;i<=1;)
   {
      Keypad ();
      If (key==4)
      {
         Screen_Select ();
         reset_cpu();
      }
      If (slide==1)
      {
         LCD_GOTOXY(1,1);
         lCD_PUTC("1: REMOVE CARD 1");
         LCD_GOTOXY(1,2);
         lCD_PUTC("2: REMOVE CARD 2");
         LCD_GOTOXY(21,1);
         lCD_PUTC("3: REMOVE CARD 3");
         if (key==1)
         {
            sc=1;
            i++;
         }
         if (key==5)
         {
            sc=2;
            i++;
         }
         if (key==9)
         {
            sc=3;
            i++;
         }
      }
      if (slide==2)
      {
         LCD_GOTOXY(1,1);
         lCD_PUTC("4: REMOVE CARD 4");
         LCD_GOTOXY(1,2);
         lCD_PUTC("5: REMOVE CARD 5");
         LCD_GOTOXY(21,1);
         lCD_PUTC("6: REMOVE CARD 6");
         if (key==2)
         {
            sc=4;
            i++;
         }
         if (key==6)
         {
            sc=5;
            i++;
         }
         if (key==10)
         {
            sc=6;
            i++;
         }
      }
      if (slide==3)
      {
         LCD_GOTOXY(1,1);
         lCD_PUTC("7: REMOVE CARD 7");
         LCD_GOTOXY(1,2);
         lCD_PUTC("8: REMOVE CARD 8");
         LCD_GOTOXY(21,1);
         lCD_PUTC("9: REMOVE CARD 9");
         if (key==3)
         {
            sc=7;
            i++;
         }
         if (key==7)
         {
            sc=8;
            i++;
         }
         if (key==11)
         {
            sc=9;
            i++;
         }
      }
      stt=5;
   }
}

VOID MAIN ()
{
   set_tris_A(0x00);
   set_tris_B(0xF1);
   set_tris_D(0x00);
   Output_A(0x00);
   enable_interrupts(INT_RDA);
   enable_interrupts(GLOBAL);
   setup_uart(TRUE);
   stt = read_eeprom(0x08);
   cnt = read_eeprom(0x09);
   lcd_init();
   /* 01 => 04 pass: 0000
      08 => 00
      09 => 00
   */

   while (true)
   {
      if (stt==0)    Mode1 ();      //trang thai co ban
      If (stt==1)    Mode2 ();      //them the
      If (stt==2)    Mode3 ();      //them mk
      If (stt==3)    Mode4 ();      //xoa the     
      If (stt==4)    Save  ();      //luu the
      If (stt==5)    Save  ();      //xoa the
   }
}
