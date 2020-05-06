#include <LiquidCrystal.h>

LiquidCrystal lcd(PC0, PC2, PC4, PC5, PC6, PC7); // initialize the library with the numbers of the interface pins
#define LEFTMOTOR_PIN1    PA0
#define LEFTMOTOR_PIN2    PA1
#define RIGHTMOTOR_PIN1   PA2
#define RIGHTMOTOR_PIN2   PA3
  int r1,r2, r3;

// incoming serial byte
int inByte = 0;
int east [ 15 ];
int north [ 15 ];
int i;
int buzzer = PC3;
void setup()
{
  pinMode(PJ2, INPUT);
  pinMode(PJ3, INPUT);
  pinMode(PJ5, INPUT);


  lcd.begin(16, 2);
  lcd.print("Mine Detection Bot");
  lcd.setCursor(0, 1);
  lcd.print("Initialize ");
}

void forward (void) //both wheels forward
{
  digitalWrite(LEFTMOTOR_PIN1, LOW);
  digitalWrite(LEFTMOTOR_PIN2, HIGH);
  digitalWrite(RIGHTMOTOR_PIN1, HIGH);
  digitalWrite(RIGHTMOTOR_PIN2, LOW);
}
void backward(void)//both wheels back
{
  digitalWrite(LEFTMOTOR_PIN1, HIGH);
  digitalWrite(LEFTMOTOR_PIN2, LOW);
  digitalWrite(RIGHTMOTOR_PIN1, LOW);
  digitalWrite(RIGHTMOTOR_PIN2, HIGH);
}
void left(void)//LEFT TURN
{
  digitalWrite(LEFTMOTOR_PIN1, HIGH);
  digitalWrite(LEFTMOTOR_PIN2, LOW);
  digitalWrite(RIGHTMOTOR_PIN1, HIGH);
  digitalWrite(RIGHTMOTOR_PIN2, LOW);
}
void right(void)//right turn
{
  digitalWrite(LEFTMOTOR_PIN1, LOW);
  digitalWrite(LEFTMOTOR_PIN2, HIGH);
  digitalWrite(RIGHTMOTOR_PIN1, LOW);
  digitalWrite(RIGHTMOTOR_PIN2, HIGH);
}
void stop(void)//STOP
{
  digitalWrite(LEFTMOTOR_PIN1, LOW);
  digitalWrite(LEFTMOTOR_PIN2, LOW);
  digitalWrite(RIGHTMOTOR_PIN1, LOW);
  digitalWrite(RIGHTMOTOR_PIN2, LOW);
}

void gpstx()
{

  Serial.begin(4800);
  delay(100);
  //==================== searching for "GG" ===================//
  do
  {
    do
    {
      while ( !Serial3.available() );
    } while ( 'G' != Serial3.read() );
    while (!Serial3.available());

  } while ( 'G' != Serial3.read() );

  //==================== searching for "GG" ===================//


  //============== seeking for north cordinate ==============//

  do
  {
    while ( !Serial3.available() );
  } while ( ',' != Serial3.read() );
  do
  {
    while ( !Serial3.available() );
  } while ( ',' != Serial3.read() );

  //============== seeking for north cordinate ==============//


  //============== printing the north cordinate ===============//

  //    Serial.print(" N: ");
  i = 0;
  do
  {
    while ( !Serial3.available() );
    inByte = Serial3.read();
    north [ i ] = inByte;
    //        Serial.write ( inByte );
    i ++;
  } while ( ',' != inByte );
  //============== printing the north cordinate ===============//

  //============== seeking for east cordinate ==============//
  do
  {
    while ( !Serial3.available() );
  } while ( ',' != Serial3.read() );
  //============== seeking for east cordinate ==============//
  //============== printing the east cordinate ===============//
  //    Serial.print(" E: ");
  i = 0;
  do
  {
    while ( !Serial3.available() );
    inByte = Serial3.read();
    east [ i ] = inByte;
    i ++;
    //        Serial.write ( inByte );
  } while ( ',' != inByte );
  //============== printing the east cordinate ===============//
  delay(500);
  digitalWrite(buzzer, HIGH);
  Serial.begin(9600);
  delay(100);
  Serial.write(" GEOGRAPHICAL CORDINATES");
  Serial.print( " N: " );
  for ( i = 0; north [ i ] != ' '; i ++ )
    Serial1.write ( north [ i ] );
  Serial.print( " E: " );
  for ( i = 0; east [ i ] != ' '; i ++ )
    Serial1.write ( east [ i ] );
  Serial.println();
  delay ( 500 );
  digitalWrite(buzzer, LOW);
  exit;
}
void motions(void)
{
  while (1)
  {
    forward(); //both wheels forward
    _delay_ms(40000);

    stop();
    _delay_ms(5000);
    left(); //Left wheel backward, Right wheel forward
    _delay_ms(12000);

    stop();
    _delay_ms(5000);
    forward(); //both wheels forward
    _delay_ms(5000);

    stop();
    _delay_ms(5000);
    left(); //Left wheel backward, Right wheel forward
    _delay_ms(12000);

    stop();
    _delay_ms(5000);
    forward(); //both wheels forward
    _delay_ms(40000);

    stop();
    _delay_ms(5000);
    stop();
    right(); //Left wheel backward, Right wheel forward
    _delay_ms(9000);
    forward(); //both wheels forward
    _delay_ms(5000);

    stop();
    _delay_ms(5000);

    stop();
    _delay_ms(5000);
    right(); //Left wheel backward, Right wheel forward
    _delay_ms(12000);
    if ((r1 > 0 && r2 > 0) || (r1 > 0 && r3 > 0) || (r2 > 0 && r3 > 0))
    {
      lcd.print("Threat detected");
      gpstx();// send GPS data to PC over Xbee
    }
  }
}
void loop()
{
  Serial.begin(9600);
  Serial.print(r1 = digitalRead(PJ2));
  Serial.print(r2 = digitalRead(PJ3));
  Serial.print(r3 = digitalRead(PJ5));
  //  while (1)
  //  {
  //    if ((r1 > 0 && r2 > 0) || (r1 > 0 && r3 > 0) || (r2 > 0 && r3 > 0))
  //    {
  //      lcd.print("Threat detected");
  //      gpstx();// send GPS data to PC over Xbee
  //    }
  //    else
  //    {
  //      lcd.print("NO THREAT DETECTED");
  //
  motions();


}
