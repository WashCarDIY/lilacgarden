
#include <EEPROM.h>
#define EEPROM_write(address, p) {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) EEPROM.write(address+i, pp[i]);}
#define EEPROM_read(address, p)  {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) pp[i]=EEPROM.read(address+i);}

// 定义一个包含char[] 等各种类别的 config_type 结构
struct config_type
{
  String md5;
}

//设备ID 设置成静态是为了初始化以后就不改变。
static String ID ; 

int pbIn = 0;                  // 定义中断引脚为0，也就是D2引脚
int ledOut = A0;                // 定义输出指示灯引脚
volatile int state = LOW;      // 定义默认输入状态
int comtemp; //定义一个变量来存储串口收到的数据。

volatile int switchState = LOW;    //控制阀门开关，当0时，阀门打开; -1时,阀门关闭
String comdata = "";
String endCode = "44";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);  //水阀控制开关。
  pinMode(12,INPUT);  //如果取水杆查好，有信号输入。

  //  从EEPROM地址0开始读取，结果存储在config_readback,读取设备ID。
  config_type config_readback;
  EEPROM_read(0, config_readback);
  ID = (String)config_readback.md5;

  // 置ledOut引脚为输出状态
  pinMode(ledOut, OUTPUT);
 // 监视中断输入引脚的变化
  attachInterrupt(pbIn, stateChange, CHANGE);
}

void loop() {

   while (Serial.available())
  {
    
    comdata += char(Serial.read());
    delay(2);
    Serial.println(comdata);
  if (comdata.endsWith(endCode))
    {
     comdata = "";
      openSwitch();
    }
  }
  delay(100);    
}

void openSwitch(){
    digitalWrite(13, HIGH);   //Open switch.
    delay(5000);
    digitalWrite(13, LOW);    //Close switch.
    delay(500);
}

//中断响应(need change)
 void stateChange()
{
  state = !state;
  digitalWrite(ledOut, state);  
}

// 设置设备的ID
unsigned long getID(){
 char inChar = 0;
 int bitCounts = 0; //数据位数结果
 unsigned long result = 0; //结果
  // Read serial input:
  while (Serial.available()) {
    inChar = Serial.read();
    delay(2);
//    if('\n' == inchar){
      return result;
//  }
    if (isDigit(inChar)) {
    // convert the incoming byte to a char
    // and add it to the string:
    comdata += (char)inChar;
  }else{
    Serial.flush();
    return -1;
  }
  
  }
}
