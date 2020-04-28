#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 7, 6, 5, 4);// initialize the library with the numbers of the interface pins

// incoming serial byte
int inByte = 0;         
int east [ 15 ];
int north [ 15 ];
int i;
int buzzer = PL1;
void setup() 
{
pinMode(PJ2,INPUT);
pinMode(PJ3,INPUT);
pinMode(PJ5,INPUT);


  lcd.begin(16, 2);
  lcd.print("Mine Detection Bot");
  lcd.setCursor(0, 1);
  lcd.print("Initialize ");
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
            while ( !Serial.available() );    
        } while ( 'G' != Serial.read() );
        while(!Serial.available());

    } while ( 'G' != Serial.read() );

//==================== searching for "GG" ===================//


//============== seeking for north cordinate ==============//

    do
    {
        while ( !Serial.available() );    
    } while ( ',' != Serial.read() );
    do
    {
        while ( !Serial.available() );    
    } while ( ',' != Serial.read() );

//============== seeking for north cordinate ==============//


//============== printing the north cordinate ===============//

//    Serial.print(" N: ");
    i = 0;
    do
    {
        while ( !Serial.available() ); 
        inByte = Serial.read();
        north [ i ] = inByte;
//        Serial.write ( inByte );
        i ++;
    } while ( ',' != inByte );
//============== printing the north cordinate ===============//

//============== seeking for east cordinate ==============//
    do
    {
        while ( !Serial.available() );    
    } while ( ',' != Serial.read() );
//============== seeking for east cordinate ==============//
//============== printing the east cordinate ===============//
//    Serial.print(" E: ");
    i = 0;
   do
    {
        while ( !Serial.available() ); 
        inByte = Serial.read();
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
      Serial.write ( north [ i ] );
    Serial.print( " E: " );    
    for ( i = 0; east [ i ] != ' '; i ++ )
      Serial.write ( east [ i ] );
    Serial.println();
    delay ( 500 );
    digitalWrite(buzzer, LOW);  
    exit;
}
void loop()
{
    int r1,r2,r3;
 Serial.begin(4800);
 
  Serial.print(r1=digitalRead(PJ2));
  Serial.print(r2=digitalRead(PJ3));
  Serial.print(r3=digitalRead(PJ5));
 
  if((r1>0 && r2>0)||(r1>0 && r3>0)||(r2>0 && r3>0))
  {
    lcd.print("Threat detected");
    gpstx();
    while(buzzer,LOW)
    {
      
    }
    }
}
