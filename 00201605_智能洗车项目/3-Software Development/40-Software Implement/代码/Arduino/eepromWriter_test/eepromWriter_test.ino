// 高效的写入eeprom
#include <EEPROM.h>
#define EEPROM_write(address, p) {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) EEPROM.write(address+i, pp[i]);}
#define EEPROM_read(address, p)  {int i = 0; byte *pp = (byte*)&(p);for(; i < sizeof(p); i++) pp[i]=EEPROM.read(address+i);}
 
// 定义一个包含char[] 等各种类别的 config_type 结构
struct config_type
{
   char ID[64];
};

  String sourceCode; //写入的ID
 
// 测试EEPROM_writeAnything()与测试EEPROM_readAnything()两个命令
void eeprom_setID(String sourceCode)
{
  // 1) 定义结构变量config，并定义config的内容
  config_type config;
//  strcpy(config.md5, sourceCode);
   sourceCode.toCharArray(config.ID,64);
  // 2) 把变量config存储到EEPROM，从地址0开始写入。
  EEPROM_write(0, config);
 
  // 3) 从EEPROM地址0开始读取，结果存储在config_readback
   config_type config_readback;
   EEPROM_read(0, config_readback);
 
  // 4) 通过串口输出读取回来的资料
   Serial.println(config_readback.ID);  
}  
 
void setup()
{
  // 开启Serial port，设置波特率为9600
  Serial.begin(9600);
 
  // 运行测试程序
 // eeprom_setID();  
}
 
void loop()
{
  // do nothing  
}
