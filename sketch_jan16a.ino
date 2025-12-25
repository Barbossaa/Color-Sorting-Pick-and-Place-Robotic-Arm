#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
#define s0 10         //Bağladığımız pinlere göre tanımlamalar
#define s1 11
#define s2 8
#define s3 7
#define sensorOut 9
int renk, K, Y, M = 0;
LiquidCrystal_I2C lcd(0x27,16,2);

/*
int value1;
int value2;
int value3;
int value4;
int degree1;
int degree2;
int degree3;
int degree4;
int Push_Button1 = 12;
int Push_Button2 = 13;
int button_State = 0;
*/

void setup() 
{
//Servoların kurulumu
servo2.attach(2);     //Aşağı - yukarı servo motoru
servo3.attach(3);     //İleri - geri servo motoru
servo4.attach(4);     //Zemin servo motoru
servo5.attach(5);     //Kıskaç servo motoru
//Renk sensörünün kurulumu
pinMode(s0, OUTPUT); //S0, S1, S2 ve S3 pinlerini OUTPUT olarak tanımlıyoruz
pinMode(s1, OUTPUT);
pinMode(s2, OUTPUT);
pinMode(s3, OUTPUT);
pinMode(sensorOut, INPUT); //OUT pinini INPUT olarak tanımlıyoruz
digitalWrite(s1, LOW); //Frekans ölçeğimizi %20 olarak tanımlıyoruz
digitalWrite(s0, HIGH);
Serial.begin(9600);
//16x2 LCD Ekranın Kurulumu
lcd.begin();
//Joystickin Kurulumu
/*
pinMode (Push_Button1, INPUT_PULLUP );
pinMode (Push_Button2, INPUT_PULLUP );
*/
}

void loop()
{
/*
servo2.write(x);        //100 ---> Kutuların seviyesi  /  20 ---> Renk sensörünün seviyesi
servo3.write(x);
servo4.write(x);        //25 ---> 3. kutunun seviyesi  /   60 ---> 2. kutunun seviyesi / 125 ---> 1. kutunun seviyesi  /  95 ---> Renk sensörünün seviyesi
servo5.write(x);
*/

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Renk");
lcd.setCursor(0,1);
lcd.print("Tanimlaniyor...");

while(1){
  servo3.write(180);
  delay(1000);
  servo2.write(20);
  delay(1000);
  servo5.write(90);

  //Manuel Moda (Joystick ile kontrol) geçildiği sırada uygulanacak işlem
  /*
  button_State = !digitalRead (Push_Button1);
  button_State = !digitalRead (Push_Button2);
  if(button_State==0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Manuel Moda");
    lcd.setCursor(0,1);
    lcd.print("Gecildi");
    while(1){
      button_State = !digitalRead (Push_Button1);
      button_State = !digitalRead (Push_Button2);

      if(button_State==1){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Renk");
        lcd.setCursor(0,1);
        lcd.print("Tanimlaniyor...");
        break;
      }
      value1 = analogRead(A0);
      value2 = analogRead(A1);
      value3 = analogRead(A2);
      value4 = analogRead(A3);
      
      degree1 = map(value1, 0, 1023, 45, 135);
      degree2 = map(value2, 0, 1023, 45, 135);
      degree3 = map(value3, 0, 1023, 0, 180);
      degree4 = map(value4, 0, 1023, 35, 115);

      //servo2.write(100);
      servo3.write(180);
      servo5.write(degree3);
      delay(100);
      //servo2.write(degree2);
      servo4.write(degree4);
      delay(500);
    }
  }
*/

  digitalWrite(s2, LOW);        //Kırmızıyı filtrelemek için
  digitalWrite(s3, LOW);
  K = pulseIn(sensorOut, LOW);  //OUT pini üzerindeki LOW süresini okur
  Serial.print("Kırmızı= ");
  Serial.print(K); //Kırmızı için aldığımız değeri serial monitöre yazdır
  Serial.print("  ");
  delay(50);                    //50 milisaniye bekler
  digitalWrite(s2, HIGH);       //Yeşili filtrelemek için
  digitalWrite(s3, HIGH);
  Y = pulseIn(sensorOut, LOW);  //OUT pini üzerindeki LOW süresini okur
  Serial.print("Yeşil= ");
  Serial.print(Y); //Yeşil için aldığımız değeri serial monitöre yazdır
  Serial.print("   ");
  delay(50);                    //50 milisaniye bekler
  digitalWrite(s2, LOW);        //Maviyi filtrelemek için
  digitalWrite(s3, HIGH);
  M = pulseIn(sensorOut, LOW);  //OUT pini üzerindeki LOW süresini okur
  M = pulseIn(sensorOut, LOW); //OUT pini üzerindeki LOW süresini okur
  Serial.print("Mavi= ");
  Serial.print(M); //Mavi için aldığımız değeri serial monitöre yazdır
  Serial.println();
  delay(50); //50 milisaniye bekle
  
  //Tüm yukarıdaki işlemler sonunda en düşük değer alan renk değişkeni seçilir ve ona göre işlem yapılır. LCD ekran rengin tanımlandığı bildirilir ve ürün kola yerleştirilir
  
  if(K < M && K < Y &&  K < 200){       //Kırmızı renk algılanması durumunda:
    renk = 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Kirmizi renk");
    lcd.setCursor(0,1);
    lcd.print("Algilandi - 3");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Algilandi - 2");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Algilandi - 1");
    delay(1000);
    break;
  }

  else if(M < K && M < Y &&  M < 200){  //Mavi renk algılanması durumunda:
    renk = 2;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Mavi renk");
    lcd.setCursor(0,1);
    lcd.print("Algilandi - 3");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Algilandi - 2");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Algilandi - 1");
    delay(1000);
    break;
  }
  //Y < M && Y < K && 
  else if( Y < 300){  //Yeşil renk algılanması durumunda:
    renk = 3;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Yesil renk");
    lcd.setCursor(0,1);
    lcd.print("Algilandi - 3");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Algilandi - 2");
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("Algilandi - 1");
    delay(1000);
    break;
  }
}

delay(100);
servo3.write(180);
delay(100);
servo5.write(90);

switch (renk) {

case 1:
{
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Islem");
  lcd.setCursor(0,1); 
  lcd.print("Yapiliyor");

  for(int i=90;i>0;i--) {
  servo5.write(i);
  delay(10);
  }

  delay(1000);
  
  for(int i=20;i<100;i++) {
  servo2.write(i);
  delay(10);
  }
  
  servo3.write(180);

  for(int i=95;i<125;i++) {
  servo4.write(i);     
  delay(10);
  }
  delay(500);
  servo5.write(90);
  delay(1000);

  for(int i=125;i>95;i--) {
  servo4.write(i);
  delay(10);  
}

  break;
  
}


case 2:
{
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Islem");
  lcd.setCursor(0,1); 
  lcd.print("Yapiliyor");

  for(int i=90;i>0;i--) {
  servo5.write(i);
  delay(10);
  }
  delay(1000);
  
  for(int i=20;i<100;i++) {
  servo2.write(i);
  delay(10);
  }
  
  servo3.write(180);

  for(int i=95;i>60;i--) {
  servo4.write(i);     
  delay(10);
  }
  delay(500);
  servo5.write(90);
  delay(1000);

  for(int i=60;i<95;i++) {
  servo4.write(i);
  delay(10);  
}
  break;
}

case 3:
{
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Islem");
  lcd.setCursor(0,1); 
  lcd.print("Yapiliyor");

  for(int i=90;i>0;i--) {
  servo5.write(i);
  delay(10);
  }
  delay(1000);
  
  for(int i=20;i<100;i++) {
  servo2.write(i);
  delay(10);
  }
  
  servo3.write(180);

  for(int i=95;i>25;i--) {
  servo4.write(i);     
  delay(10);
  }
  delay(500);
  servo5.write(90);
  delay(1000);

  for(int i=25;i<95;i++) {
  servo4.write(i);
  delay(10);  
}
  break;
}

}
}

