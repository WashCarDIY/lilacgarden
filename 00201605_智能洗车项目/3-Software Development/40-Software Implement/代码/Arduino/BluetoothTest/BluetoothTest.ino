void setup()
{
 Serial.begin(9600);
  Serial.write(45); // send a byte with the value 45
  int bytesSent = Serial.write("hello");
  Serial.println(bytesSent);
}
 
void loop()
{

}
