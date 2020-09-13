#include <Servo.h>
#include <HardwareSerial.h>//HardwareSerialでないとサーボが動作不良を起こす可能性
#include"Inv.h"

#define MYRX PA10 //serial_RX
#define MYTX PA9 //serial_TX

HardwareSerial mySerial(MYRX, MYTX);

unsigned char c[8];
unsigned long chksum;


void setup() {
  mySerial.begin(2400);//SBDBTとArduinoは2400bps
  Serial.begin(19200);//シリアルモニター表示
  c[0] = 0x80; //SBDBTからのシリアル信号の１個目は固定。
}

void loop() {
  //まずは無線からシリアルを読み込む。c[1]とc[2]にキー入力が格納される。
  int i;
  if (mySerial.available() >= 8) { //8byte以上あるかチェック
    if (mySerial.read() == 0x80) { //１byte読み込んで0x80のスタートビットかチェック
      Serial.print(c[0], HEX); //１６進数で数値を表示。
      Serial.print(",");//コンマで区切る。
      for (chksum = c[0], i = 1; i < 8; i++) { //スタートビットは読み込み済みなので、次の７個のデータを読み込む。
        c[i] = mySerial.read();
        if (i < 7) chksum += c[i];
        Serial.print(c[i], HEX); //１６進数で数値を表示。
        Serial.print(",");//}//コンマで区切る。
      }
      if (c[7] == (chksum & 0x7F)) { //ボタン部分のみのチェックサムを簡易計算してみる。
        Serial.println("check sum OK !");//チェックサムOKを表示。
      }
      else {
        Serial.println("check sum * * ERROR * *");//ダメならエラーを表示。
      }
    }
      String leftstickx =  String(c[3], DEC); //左のアナログスティックライトの左右の値を16→10進数へ
      String leftsticky =  String(c[4], DEC); //左のアナログスティックライトの上下の値を16→10進数へ
      String rightstickx =  String(c[5], DEC); //右のアナログスティックライトの左右の値を16→10進数へ
      String rightsticky =  String(c[6], DEC); //右のアナログスティックライトの上下の値を16→10進数へ
      Serial.print(leftstickx);
      Serial.print(leftsticky);
      Serial.print(rightstickx);
      Serial.println(rightsticky);
       Serial.print("\t");

       double Leftstickx = leftstickx.toDouble();
       double Leftsticky = leftsticky.toDouble();
      //θ計算
       double sheta = atan2(Leftstickx,Leftsticky);
       //度に変換
       double deg = sheta * 180.0 / (atan(1.0) * 4.0);


       //power
       double power = sqrt(pow(Leftstickx,2)+pow(Leftsticky,2));
     if ((c[2] & 0x01) == 0x01 && (c[2] & 0x02) == 0x02) {
        //if ((c[2] & 0x03 ) == 0x03 ) { //Start(上下同時押しはないと言う前提で書いてるので、注意！）
        Serial.println("Start");

      } else  if ((c[2] & 0x04) == 0x04 && (c[2] & 0x08) == 0x08) {//左右同時押しはないと言う前提で書いてるので、注意！）
        // if ((c[2] & 0x0C ) == 0x0C ) { //Select
        Serial.println("Select");

      } else if ((c[2] & 0x01) == 0x01 ) { //上
          Serial.println("↑Up"); 
          
      } else if ((c[2] & 0x02) == 0x02 ) { //下
          Serial.println("↓Down");
         
      }else if ((c[2] & 0x03 ) == 0x03 ) { //Start
          Serial.println("Start");
        }else if ((c[2] & 0x04 ) == 0x04 ) { //右
          Serial.println("→Right");
          
        }else if ((c[2] & 0x08 ) == 0x08 ) { //左
          Serial.println("←Left");
         
        }else if ((c[2] & 0x10 ) == 0x10 ) { //三角
          Serial.println("Triangle△");
         
        }else if ((c[2] & 0x20 ) == 0x20 ) { //バツ
          Serial.println("×Cross");
         
        }else if ((c[2] & 0x40 ) == 0x40 ) { //マル
          Serial.println("○Circle");
         
          
        }else if ((c[1] & 0x01 ) == 0x01 ) { //四角
          Serial.println("□Square");
         
        }else if ((c[1] & 0x02 ) == 0x02 ) { //L1
          Serial.println("L1");
          
        }else if ((c[1] & 0x04 ) == 0x04 ) { //L2
          Serial.println("L2");

        }else if ((c[1] & 0x08 ) == 0x08 ) { //R1
          Serial.println("R1");
         
        }else if ((c[1] & 0x10 ) == 0x10 ) { //R2
          Serial.println("R2");
     
        }else{
  
      }
    }
  }


void patern(double degree, double power){
 double  patern = degree + 45;
  if(patern >= 0 && patern <= 90){
    
  } else if(patern > 90 && patern <= 180){
    
  } else if(patern > 180 && patern <= 270){
    
  } else if(patern > 270 && patern <= 360){
    
  }
}
