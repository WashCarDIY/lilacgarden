
// volatile bool isOpen = true;
String comdata = "";
String startCode = "li";
String endCode = "44";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  //  pinMode(12,OUTPUT);
   while (!Serial) {;}
}

void loop() {

  if (Serial.available() > 0)
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

void openSwitch() {
  digitalWrite(13, HIGH);   //Open switch.
  delay(6000);
  digitalWrite(13, LOW);    //Close switch.
  delay(500);
}

