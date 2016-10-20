volatile bool isOpen = false;
String comdata = "";

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {

  //  isOpen = false;
  if (Serial.available())
  {
    comdata += char(Serial.read());
    delay(2);
    Serial.println(comdata);
    
    if (comdata.endsWith("x"))
    {
    isOpen = true;
    }
//    comdata.remove(0);
  }

  if (isOpen) {
    digitalWrite(13, HIGH);   //Open switch.
    delay(5000);
    digitalWrite(13, LOW);    //Close switch.
    delay(500);
    isOpen = false;
  }

}

