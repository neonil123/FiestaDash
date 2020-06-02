#include <FastLED.h>
#define NUM_LEDS 23
#define DATA_PIN 4
CRGB leds[NUM_LEDS];



#include <Adafruit_TiCoServo.h>
Adafruit_TiCoServo rpm;  
Adafruit_TiCoServo speed0; 
//Servo fuel; //you can use this sevros with other board that support more servos with the Adafruit_TiCoServo.h
//Servo Wtemp;   


#define ABSLED 17
#define TCLED  15
#define FUELLED 0
#define UPSHIFTLED 13


void setup() { 
   
	Serial.begin(9600);
  LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	LEDS.setBrightness(84);

  rpm.attach(10,600,2500);
  speed0.attach(9,600,2500); 
  //fuel.attach(8);
  //Wtemp.attach(6);

   rpm.write(2500); 
   speed0.write(2500); 
   //fuel.write(0);
  // Wtemp.write(180);
    
int i1=20;
for(int i=0; i<11; i++){
  leds[i] = CRGB( 0, 0, 255);
  leds[i1] = CRGB( 0, 0, 255);
  FastLED.show(); 
  delay(150);
  i1--;
}

for(int i=0; i<23; i++){
  leds[i] = CRGB( 20,20,20);
  FastLED.show(); 
}
delay(1000);
 leds[5] = CRGB( 255, 0, 0);
    FastLED.show(); 
}

char inc;
int val;
void loop() { 

while (Serial.available()) 
  { 
    inc = Serial.read();
    if (inc >= '0' && inc <= '9') 
    {
      val = 10*val + (inc-'0');
    } 
    
   else
   {
      switch (toupper(inc)) {
      case 'A':
       // Serial.print("Case A got ");
       rpmm(val);
        break;

      case 'B':
        //Serial.print("Case B got ");
        speedo(val);
        break;
        
      case 'C':

       upshift (val);
        break;
        
     case 'D':
        tc1(val);
        break;

     case 'E':
       abs1(val);
      break;  

       case 'F':
       fuel(val);
      break;
        
      default :
        ; 
      }
      val = 0;  
    }
  }

  //leds[0] = CRGB( 0, 255, 0);
   // FastLED.show(); 

}

void upshift (int spee)
{
  if(spee == 1){
    leds[UPSHIFTLED] = CRGB( 0, 255, 0);
    FastLED.show(); 
  }

   if(spee == 0){
    leds[UPSHIFTLED] = CRGB( 30, 30, 30);
    FastLED.show(); 
  }
    
}

void speedo(int sp)
{
 sp = map(sp,10,170,2500,600 );
 sp=constrain(sp,600,2500);
 speed0.write(sp); 

}


void rpmm (int rp)
{
 rp = map(rp,0,5500,2500,600 );
 rp=constrain(rp,600,2500);
 rpm.write(rp); 

}

void tc1(int tc)
{
  if(tc >50 ){
    leds[TCLED] = CRGB( 0, 255, 0);
    FastLED.show(); 
  }
else{
  leds[TCLED] = CRGB( 30, 30, 30);
    FastLED.show(); 
}
 
}

void abs1(int ab)
{
  if(ab >50 ){
    leds[ABSLED] = CRGB( 0, 255, 0);
    FastLED.show(); 
  }
else{
  leds[ABSLED] = CRGB(30,30,30);
    FastLED.show(); 
}
 
}

void fuel(int data)
{
   if(data >40 && data < 100){
    leds[FUELLED] = CRGB( 255,0,0);
    FastLED.show(); 
   }
   if(data >10 && data <40){
    leds[FUELLED] = CRGB( 0,0,255);
    FastLED.show(); 
   }
  if(data < 10){
    leds[FUELLED] = CRGB( 0,255,0);
    FastLED.show(); 
   }
}
