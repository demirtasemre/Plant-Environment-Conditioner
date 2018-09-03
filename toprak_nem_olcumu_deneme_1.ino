#include <Wire.h>
#include <FaBoLCD_PCF8574.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "TSL2561.h"


/*
A0>EKRAN1-1>POT
A1>EKRAN1-2>SECME BUTONU
------------------------------------
D5>ISITICI
D6>LED
D7>POMPA
D8>VALF
------------------------------------
A2>SICAKLIK SENS.
A3>TOPRAK NEM SENS.
A6>DEPO SENS.
------------------------------------
A4>SDA
A5>SCL
SC5>REAL TIME CLOCK-SCL
SD5>REAL TIME CLOCK-SDA
SC6>ISIK SENS.-1>ISIK SENS.-SCL
SD6>ISIK SENS.-2>ISIK SENS.-SDA
SC7>EKRAN2-3>EKRAN-SCL
SD7>EKRAN2-4>EKRAN-SDA
------------------------------------
D9>KABLOSUZ-CE(3)
D10>KABLOSUZ-CSN(4)
D11>KABLOSUZ-MOSI(6)
D12>KABLOSUZ-MISO(7)
D13>KABLOSUZ-SCK(5)
A2>KABLOSUZ-IRQ(8)
*/

/*
1234567890123456
   ***MENU***   

  TOPRAK  NEMI  
****************

OLCULEN >MAX:XXX
 %XXX    MIN:XXX
                              
TOPRAK SICAKLIGI
****************
                              
OLCULEN  >MAX:XX
  XXOC    MIN:XX

   ISIK AKISI   
****************
                              
OLCULEN  >MAX:XXX
 XXXlx    MIN:XXX
                              
  DEPO SEVIYESI 
****************
                              
OLCULEN >MAX:XXX
 XXXlt   MIN:XXX
 */

int olcum=0; //Nem ölçümü
float t=0; //Sıcaklık ölçümü
float h=0; //Depo su seviyesi ölçümü
float seviye=0; //Depo su seviyesi ilk değer

FaBoLCD_PCF8574 lcd; //LCD ekran başlatma
OneWire oneWire(16); //Termokopl başlatma
DallasTemperature temp(&oneWire); //Termokopl başlatma
DeviceAddress temp_ad; //Termokopl başlatma


int basilan_tus=0;
int okunan_deger=0;

#define menu    0
#define yukari  1
#define asagi   -1
#define geri    3
#define sec     4
#define yok     5

byte buton_bul()
{
  okunan_deger = analogRead(A1);
  if (okunan_deger > 1000)
    return menu;
  if (okunan_deger < 50)
    return sag;
  if (okunan_deger < 195)
    return yukari;
  if (okunan_deger < 380)
    return asagi;
  if (okunan_deger < 555)
    return sol;
  if (okunan_deger < 790)
    return sec;
}


void setup()
{
  Serial.begin(9600);
  
  lcd.begin(16, 2);

  temp.begin();
  temp.getAddress(temp_ad, 0);
  temp.setResolution(temp_ad, 12);
  
}

void loop()
{
  basilan_tus = buton_bul();
  switch (basilan_tus)
  {
    case menu:
      {
        menu_ekran = 0
        
        break;
      }
    case asagi:
      {
        menu_ekran = menu_ekran + 1
        break;
      }
    case yukari:
      {
        menu_ekran = menu_ekran - 1
        break;
      }
    case asagi:
      {
        ekran.print("asagi ");
        break;
      }
    case sec:
      {
        ekran.print("sec   ");
        break;
      }
    case yok:
      {
        ekran.print("yok   ");
        break;
  
  //Toprak nem ölçümü
  olcum=analogRead(A3);
  lcd.setCursor(x_nem1, y_nem1);
  lcd.print("Nem%");
  lcd.setCursor(x_nem2, y_nem2);
  olcum=map(olcum,300,1021,0,100);
  olcum=(100-olcum);
  lcd.print(olcum);

  //Su deposu ölçümü
  h=analogRead(A6);
  seviye=0.0007624*exp(0.01239*h);
  lcd.setCursor(x_depo1, y_depo1);
  lcd.print("Depo");
  lcd.setCursor(x_depo2, y_depo2);
  lcd.print(seviye);

  //Sıcaklı ölçümü
  temp.requestTemperatures(); 
  t=temp.getTempC(temp_ad);
  lcd.setCursor(x_sicak1, y_sicak1);
  lcd.print("Sic.");
  lcd.setCursor(x_sicak2, y_sicak2);
  lcd.print(t);

  //Işık akısı ölçümü
  
  
  
  delay(500);
  lcd.clear();
  
}
