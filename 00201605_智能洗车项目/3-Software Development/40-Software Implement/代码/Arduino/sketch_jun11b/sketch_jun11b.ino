
// volatile bool isOpen = true;
String comdata = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
//  pinMode(12,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 // if (isOpen) {
 //   digitalWrite(13, HIGH);   //Open switch.
 //   delay(5000);
 //   digitalWrite(13, LOW);    //Close switch.
 //   delay(500);
 //   isOpen = false;
 // }
   if (Serial.available())
  {
    char onebit = char(Serial.read()) ;
    comdata += onebit;
    delay(2);
    Serial.println(comdata);
 //  if (onebit == '4')
 //   {
//      comdata = "";
//      lightOn();
//    }
  }
  delay(1000);    
}

void lightOn(){
    digitalWrite(13, HIGH);   //Open switch.
    delay(6000);
    digitalWrite(13, LOW);    //Close switch.
    delay(500);
}
