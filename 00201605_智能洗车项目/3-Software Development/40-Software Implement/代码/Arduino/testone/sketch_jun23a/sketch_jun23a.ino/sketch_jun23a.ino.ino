#include <MD5.h>
#include <EEPROM.h>
#define EEPROM_read(address, p)  {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) pp[i]=EEPROM.read(address+i);}

// 控制命令
#define OPEN_SWITCH 0000102
#define GET_ID 0000101

// 定义一个包含char[] 等各种类别的 config_type 结构
struct config_type
{
  char ID[64];
};

char *md5ID;  //设备ID -- 已经转为MD5码
volatile int waterSwitchState = LOW;    //控制阀门开关，当0时，阀门打开; -1时,阀门关闭
int pbIn = 0;     // 定义中断引脚为0，也就是D2引脚，紧急关闭打开水阀
volatile int state = LOW;      // 定义默认紧急关闭状态，

String inputString = "";         // a string to hold incoming data
// boolean stringComplete = false;  // whether the string is complete

int action = 0; //当前命令

void setup() {
  Serial.begin(9600);  // 开启Serial port，设置波特率为9600
  inputString.reserve(200);  // reserve 200 bytes for the inputString:

  pinMode(13, OUTPUT);  //水阀控制开关。
  pinMode(12, INPUT); //如果取水杆查好，有信号输入。
  // 监视中断输入引脚的变化，紧急关闭水阀
  attachInterrupt(pbIn, stateChange, RISING);
}

void loop() {
  serialEvent();
  
}

// 获取ID的MD5码。
void getMyID2MD5() {
  config_type config_readback;
  EEPROM_read(0, config_readback);
  delay(100);
  //generate the MD5 hash for our string   config_readback.ID
  unsigned char* hash = MD5::make_hash(config_readback.ID);
  //generate the digest (hex encoding) of our hash
  char *md5str = MD5::make_digest(hash, 16);
  free(hash);
  //反馈MD5码
  Serial.println(md5str);
}

//通读取串口命令，打开水阀开关（未测试）
void openSwitch() {
  if (waterSwitchState) {
    digitalWrite(13, HIGH);   //Open switch.
    delay(5000);
  } else {
    digitalWrite(13, LOW);    //Close switch.
    delay(500);
  }
}

//中断响应(need change)，紧急关闭,再按一次打开，再一次按下解除中断。(未测试）
void stateChange()
{
  Serial.end();
  state = !state;
  while (state) {
    digitalWrite(13, LOW);
    delay(500);
  }
  Serial.begin(9600);
}

//相迎串口数据  (未测试）
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {     
    //命令响应
  switch(inputString.toInt()){
    case OPEN_SWITCH:
        openSwitch();    //通过判断状态控制水阀开关，半秒延迟
        Serial.println("OK!");
        break;
    case  GET_ID:
        getMyID2MD5();  //开启时，读入设备ID码，以MD5码反馈 
        Serial.println("OK!");
        break; 
    default: 
        Serial.println("invalid order!");   //返回出错
   }
      inputString = "";  //输入字符串清零 
      Serial.flush();   //串口缓存清空 
    } else {
      if(isDigit(inChar))
      inputString += inChar; //inputString中没有回车符
      else 
      inputString = "";  //输入字符串清零  
    }  
   }
}

