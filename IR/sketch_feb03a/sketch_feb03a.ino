int i;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(10,INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  i=digitalRead(10);
  Serial.println(i);
}
