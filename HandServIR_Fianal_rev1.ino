//Arduino sketch to control MeArm from IR controller
//All HEX codes should be changed to codes, that you recives from IR controller
//Tested on Arduino Uno
#include <IRremote.h>
#include <Servo.h>

IRrecv irrecv(11);
decode_results results;
//setuping servo
Servo left;
Servo right;
Servo claw;
Servo rot;
//setuping starting servo poz
int clawServPoz = 0;
int rightServPoz = 90;
int leftServPoz = 90;
int rotServPoz = 90;
int LastPoz = 0;
int i = 0;

void setup()
{
  {
  Serial.begin(9600);
  irrecv.enableIRIn(); 
  leftServPoz = constrain (leftServPoz, 0, 180);
  left.attach(10);
  left.write(leftServPoz);
  right.attach(9);
  right.write(rightServPoz);
  claw.attach(8);
  claw.write(clawServPoz);
  rot.attach(7);
  rot.write(rotServPoz);
  }
}
void loop()
{
  if (irrecv.decode(&results))
  {
    int res = results.value;
    Serial.println(res, HEX);
////////////////////////////////////////////////////
    //left +
    if (res==0x000020DF)
    {
      LastPoz=res;
      leftServPoz++;
      leftServPoz = constrain (leftServPoz, 0, 180);
      left.write(leftServPoz);
      i=0;
      Serial.println(leftServPoz);
    }
    //left -
    else if (res==0x0000609F)
    {
      LastPoz=res;
      leftServPoz--;
      leftServPoz = constrain (leftServPoz, 0, 180);
      left.write(leftServPoz);
      i=0;
      Serial.println(leftServPoz);
    }
//////////////////////////////////////////
    //right +
    else if (res==0xffff807f)
    {
      LastPoz=res;
      rightServPoz++;
      rightServPoz = constrain (rightServPoz, 0, 180);
      right.write(rightServPoz);
      i=0;
      Serial.println(rightServPoz);
    }
    //right -
    else if (res==0xffff906f)
    {
      LastPoz=res;
      rightServPoz--;
      rightServPoz = constrain (rightServPoz, 0, 180);
      right.write(rightServPoz);
      i=0;
      Serial.println(rightServPoz);
    }
//////////////////////////////////////////
    //claw +
    else if (res==0xFFFFb04f)
    {
      LastPoz=res;
      clawServPoz++;
      clawServPoz = constrain (clawServPoz, 0, 180);
      claw.write(clawServPoz);
      i=0;
      Serial.println(clawServPoz);
    }
    //claw -
    else if (res==0x0000708f)
    {
      LastPoz=res;
      clawServPoz--;
      clawServPoz = constrain (clawServPoz, 0, 180);
      claw.write(clawServPoz);
      i=0;
      Serial.println(clawServPoz);
    }
//////////////////////////////////////////
    //rot +
    else if (res==0x000010ef)
    {
      LastPoz=res;
      rotServPoz++;
      rotServPoz = constrain (rotServPoz, 0, 180);
      rot.write(rotServPoz);
      i=0;
      Serial.println(rotServPoz);
    }
    //rot -
    else if (res==0x000050af)
    {
      LastPoz=res;
      rotServPoz--;
      rotServPoz = constrain (rotServPoz, 0, 180);
      rot.write(rotServPoz);
      i=0;
      Serial.println(rotServPoz);
    }
/////////////////////////////////////////////    
    //Return arm to start position
    else if (res==0xFFFFA05f)
    {
     leftServPoz = 90;
     rightServPoz = 90;
     clawServPoz = 0;
     rotServPoz = 90;
     left.write(leftServPoz);
     right.write(rightServPoz);
     claw.write(clawServPoz);
     rot.write(rotServPoz);
     LastPoz = 0;
     res = 0;
    }
    //holding
    else if(res==0xffffffff)
    {
      i+=1;
      //left +
      if (LastPoz==0x000020df) 
      {
        leftServPoz+=i;
        leftServPoz = constrain (leftServPoz, 0, 180);
        left.write(leftServPoz);
      }
      //left -
      else if (LastPoz==0x0000609f) 
      {
        leftServPoz-=i;
        leftServPoz = constrain (leftServPoz, 0, 180);
        left.write(leftServPoz);
      }
      //right +
      else if (LastPoz==0xffff807f) 
      {
        rightServPoz+=i;
        rightServPoz = constrain (rightServPoz, 0, 180);
        right.write(rightServPoz);
      }
      //right -
      else if (LastPoz==0xffff906f) 
      {
        rightServPoz-=i;
        rightServPoz = constrain (rightServPoz, 0, 180);
        right.write(rightServPoz);
      }
      //claw +
      else if (LastPoz==0xffffb04f) 
      {
        clawServPoz+=i;
        clawServPoz = constrain (clawServPoz, 0, 180);
        claw.write(clawServPoz);
      }
      //claw -
      else if (LastPoz==0x0000708f) 
      {
        clawServPoz-=i;
        clawServPoz = constrain (clawServPoz, 0, 180);
        claw.write(clawServPoz);
      }
      //rot +
      else if (LastPoz==0x000010ef) 
      {
        rotServPoz+=i;
        rotServPoz = constrain (rotServPoz, 0, 180);
        rot.write(rotServPoz);
      }
      //rot -
      else if (LastPoz==0x000050af) 
      {
        rotServPoz-=i;
        rotServPoz = constrain (rotServPoz, 0, 180);
        rot.write(rotServPoz);
      }
    }
    else LastPoz=0;
    irrecv.resume();
    delay(10);
  }
}
