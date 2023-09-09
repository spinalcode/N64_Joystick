#define xPin  A2    // select the input pin for the potentiometer
#define yPin  A1    // select the input pin for the potentiometer

#define XA 6
#define XB 7
#define YA 8
#define YB 9

// offset data for n64 analog stick
byte offset[73]={
0,0,0,
1,1,1,1,1,
2,2,2,2,2,
3,3,3,3,3,
4,4,4,4,4,
5,5,5,5,5,
6,6,6,6,6,
7,7,7,7,7,
8,8,8,8,8,
9,9,9,9,9,
10,10,10,10,10,
11,11,11,11,11,
12,12,12,12,12,
13,13,13,13,13,
14,14,14,14,14
};


int xVal;
int yVal;
int xValOld;
int yValOld;

int wheelData[]={0,1,3,2};
int xOffset=0;
int yOffset=0;

void setup() {
  
  pinMode(XA, OUTPUT); // XA
  pinMode(XB, OUTPUT); // XB
  pinMode(YA, OUTPUT); // YA
  pinMode(YB, OUTPUT); // YB

  // declare the ledPin as an OUTPUT:
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  delay(250); // let the stick settle
  // Get centre position of stick
  xVal = analogRead(xPin)/6;
  yVal = (1024-analogRead(yPin))/6;

  signed char tX = (xVal > 84) ? (xVal - 84) : (84 - xVal);
  signed char tY = (yVal > 84) ? (yVal - 84) : (84 - yVal);
  // then clip them
  if(tX>72){tX=72;}
  if(tY>72){tY=72;}

  // clamp the values to 100% max of n64 values
  yVal = (yVal < offset[tX]) ? offset[tX] : ((yVal > 168 - offset[tX]) ? 168 - offset[tX] : yVal);
  xVal = (xVal < offset[tY]) ? offset[tY] : ((xVal > 168 - offset[tY]) ? 168 - offset[tY] : xVal);  
  xValOld = xVal;
  yValOld = yVal;

}


void loop() {

  // read the value from the sensor:
  xVal = analogRead(xPin)/6;
  yVal = (1024-analogRead(yPin))/6;

  signed char tX = (xVal > 84) ? (xVal - 84) : (84 - xVal);
  signed char tY = (yVal > 84) ? (yVal - 84) : (84 - yVal);
  // then clip them
  if(tX>72){tX=72;}
  if(tY>72){tY=72;}

  // clamp the values to 100% max of n64 values
  yVal = (yVal < offset[tX]) ? offset[tX] : ((yVal > 168 - offset[tX]) ? 168 - offset[tX] : yVal);
  xVal = (xVal < offset[tY]) ? offset[tY] : ((xVal > 168 - offset[tY]) ? 168 - offset[tY] : xVal);  

  // move a point around based on the x and y values
  while(xValOld != xVal || yValOld != yVal){
    if(xValOld > xVal){
      xValOld--;
      xOffset--;
      if(xOffset<0)xOffset=3;
    }
    if(xVal > xValOld){
      xValOld++;
      xOffset++;
      if(xOffset>3)xOffset=0;
    }
    if(yValOld > yVal){
      yValOld--;
      yOffset--;
      if(yOffset<0)yOffset=3;
    }
    if(yVal > yValOld){
      yValOld++;
      yOffset++;
      if(yOffset>3)yOffset=0;
    }

  // emulate the wheel-mouse based joystick of the real n64 controller
    switch(wheelData[xOffset]){
      case 0:
        digitalWrite(XB, LOW);
        digitalWrite(XA, LOW);
      break;
      case 1:
        digitalWrite(XB, HIGH);
        digitalWrite(XA, LOW);
      break;
      case 3:
        digitalWrite(XB, HIGH);
        digitalWrite(XA, HIGH);
      break;
      case 2:
        digitalWrite(XB, LOW);
        digitalWrite(XA, HIGH);
      break;
    }
    switch(wheelData[yOffset]){
      case 0:
        digitalWrite(YB, LOW);
        digitalWrite(YA, LOW);
      break;
      case 1:
        digitalWrite(YB, HIGH);
        digitalWrite(YA, LOW);
      break;
      case 3:
        digitalWrite(YB, HIGH);
        digitalWrite(YA, HIGH);
      break;
      case 2:
        digitalWrite(YB, LOW);
        digitalWrite(YA, HIGH);
      break;
    }
  }

}
