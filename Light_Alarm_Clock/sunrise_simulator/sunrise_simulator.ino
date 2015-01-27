int i=0;
int direction = 1;
const int RPin = 3;
const int BPin = 4;
const int GPin = 5;
int RState;
int GState;
int BState;
unsigned long previousMicros=0;
unsigned long previousMillis=0;

int lookupRed[64] = {1,2,4,6,9,12,16,20,25,30,36,
42,49,56,64,72,81,90,100,110,121,132,
144,156,169,182,196,210,225,240,256,272,289,
306,324,342,361,380,400,420,441,462,484,506,
529,552,576,600,625,650,676,702,729,756,784,
812,841,870,900,930,961,992,992,992};

int lookupGreen[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,1,3,6,10,14,19,25,32,40,
48,57,67,78,90,102,115,129,144,
160,176,193,211,230,250,270,291,
313,336,360,384,409,435,462,490,
518,547,577,608,640,672,705,739,
774,810,846,883,921,921,921};

int lookupBlue[64] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,
3,7,12,20,28,39,51,64,80,96,
115,135,156,180,204,231,259,
288,320,352,387,423,460,500,
540,583,627,672,720,768,819,
871,924,924,924};

unsigned long lampOnMinutes = 0;        //length of time the lamp will be on since sunrise ended
unsigned long lampOnMilliSeconds = (lampOnMinutes*60*1000);

int dutyR;                       //high time in microseconds
int dutyG;                       //high time in microseconds
int dutyB;                       //high time in microseconds
long sunriseMin = 1;           //length of sunrise in minutes
long stepMillis = sunriseMin*60*1000/64;

long pulsePeriodMicros = 5000; //pulse period in microseconds



void setup()
{
  pinMode(RPin, OUTPUT);
  pinMode(GPin, OUTPUT);
  pinMode(BPin, OUTPUT);
//  Serial.begin(9600);
}

void loop()
{  
	//
	//
	//
	//insert code here
	//
	//
	unsigned long currentMicros = micros();
	unsigned long currentMillis = millis();
	dutyR = lookupRed[i]*5;
	dutyG = lookupGreen[i]*5;
	dutyB = lookupBlue[i]*5;
  

	if (i<64){
		if(currentMicros - previousMicros >pulsePeriodMicros){
		  previousMicros=currentMicros; //Reset Timer if larger than pulse period.
		}
		//### Check Red Duty ###
		if(currentMicros - previousMicros < dutyR){
		  RState=HIGH;
		}
		if(currentMicros - previousMicros > dutyR){
		  RState = LOW;
		}

		//### Check Green Duty ###
		if(currentMicros - previousMicros < dutyG){
		  GState=HIGH;
		}
		if(currentMicros - previousMicros > dutyG){
		  GState = LOW;
		}

		//### Check Blue Duty ###
		if(currentMicros - previousMicros < dutyB){
		  BState=HIGH;
		}
		if(currentMicros - previousMicros > dutyB){
		  BState = LOW;
		}
		
		// Check if I should switch to next brightness, then reset timer for that.
		if(currentMillis - previousMillis >stepMillis){
		  previousMillis = currentMillis;
		  i += direction;
		//      Serial.print("i=");
		//      Serial.println(i); 
		}
   }
   
	if(i==64){
		//###	Keep light on for some minutes ###
		if (currentMillis - previousMillis  < lampOnMilliSeconds){
		RState = HIGH;
		GState = HIGH;
		BState = HIGH;
		//       Serial.print("Time elapsed since sunrise=");
		//       Serial.println(currentMillis - previousMillis);
		//       delay(10000);
		}
		
		//### Start Dimming Lights ###
		if (currentMillis - previousMillis > lampOnMilliSeconds){ 
		direction = -1;
		i = 63;
		//     RState = LOW;
		//     GState = LOW;
		//     BState = LOW;
		//       Serial.print(lampOnMinutes)
		//       Serial.println(" minutes is up! Lamp is off.");
		//       delay(10000);
		}
	
   }
   
   enlighten();
}

void enlighten(){
	if(i==0 && direction==-1){
		digitalWrite(RPin, LOW);
		digitalWrite(GPin, LOW);
		digitalWrite(BPin, LOW);		
		direction=0;
	}
	else{
		digitalWrite(RPin, RState);
		digitalWrite(GPin, GState);
		digitalWrite(BPin, BState);
	}
}