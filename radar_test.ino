
const int r1 = PE0;
const int r3 = PE2;
const int r2 = PE1;
long int sensorval1, sensorval2, sensorval3;
void scan ()
{ Serial.begin(9600);
  pinMode(r1, INPUT);
  pinMode(r2, INPUT);
  pinMode(r3, INPUT);


  sensorval1 = digitalRead(r1);
  sensorval2 = digitalRead(r2);
  sensorval3 = digitalRead(r3);


}
void setup() {


}

void loop() {
  scan();
  Serial.println(sensorval1);
  Serial.println(sensorval2);
  Serial.println(sensorval3);
}
