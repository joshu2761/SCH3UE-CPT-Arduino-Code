/* Arduino Pomodoro Study Timer

Parts list and circuit diagram available at

www.sciencebuddies.org/science-fair-projects/project_ideas/Elec_p099.shtml

This program sets a timer for the "Pomodoro study method,"
which consists of 25-minute study periods followed by 5-minute breaks.
After every 4 study periods, you take a longer 15 minute break.
However, the duration of each period and the number of repetitions
are fully customizable in the code. 

The code uses an LCD screen and LEDs as outputs, but you can add
and customize your own hardware like buzzers and motors. For more Arduino
tutorials visit our website:

https://www.sciencebuddies.org/science-fair-projects/references/how-to-use-an-arduino

*/


// import the Liquid Crystal display library
// for LCD tutorial see 
// https://www.sciencebuddies.org/science-fair-projects/references/how-to-use-an-arduino#step21
#include <LiquidCrystal.h>

// declare variables for keeping track of time
// and the number of study sessions
int seconds = 0;
int minutes = 0;
int count = 0;

// declare variables for the length of each
// period and the number of sessions before
// a longer break. Change these to customize
// your timer!
const int study_minutes = 5;
const int short_break_minutes = 1;
const int long_break_minutes = 3;
const int repeats = 4;

// a variable used to time the breaks later
int break_duration;

// declare pins used for hardware
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int led1 = 6;
const int led2 = 7;
const int speaker = 8;
int sensor = 0;

void setup() // setup code that only runs once
{
  lcd.begin(16, 2); // Set up the number of columns and rows on the LCD.
  // set LED pins as outputs and button pin as input
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(speaker,OUTPUT);

  // display initial message to user
  lcd.print("Press button");
  lcd.setCursor(0,1);
  lcd.print("to start");

  Serial.begin(9600);
}

void loop()
{
  count = 0;  // set count to zero

  while(count<repeats){ // alternate timing between study and breaks
  
    // print message and set LEDs for study time
    lcd.clear();
    lcd.print("Study time!");
    digitalWrite(led1,HIGH);
    digitalWrite(led2,LOW);
    lcd.setCursor(0, 1);

    // this is a good place to add your own code to control
    // other hardware like buzzers or motors (make sure you
    // also set the appropriate pins in the setup function)

    // reset minutes and seconds to zero
    seconds = 0;
    minutes = 0;

    // count up and display the timer during study period
    while(minutes<study_minutes){ // keep counting until we've reached the time limit for a study session
      seconds = 0;
      // print out the timer value in mm:ss format 
      while(seconds<60){
        sensor = analogRead(A0);
        if (sensor > 40) {
          tone(8, 262);
        } else {
          noTone(8);
        }
        Serial.print("sensor = ");
        Serial.println(sensor);

        lcd.setCursor(0, 1);
        if(minutes<10){  // if minutes is less than 10, we need to print an extra 0 to the display
          lcd.print("0");
        }
        lcd.print(minutes);
        lcd.print(":");
        if(seconds<10){  // if seconds is less than 10, we need to print an extra 0 to the display
          lcd.print("0");
        }
        lcd.print(seconds);
        // wait for one second then increment the second counter
        delay(1000);
        seconds++;
      }
      // increment the minute counter after 60 seconds have elapsed
      minutes++;
  
    }
    
    // now repeat the process for a study break
    lcd.clear();
    lcd.setCursor(0, 0);
    digitalWrite(led1,LOW);
    digitalWrite(led2,HIGH);

    // this is a good place to add your own code to control
    // other hardware like buzzers or motors (make sure you
    // also set the appropriate pins in the setup function)
    
    if(count==(repeats-1)){ // do a long break on the last repetition
      break_duration = long_break_minutes;
      lcd.print("Long break!");
    }
    else{  // otherwise do a short break
      break_duration = short_break_minutes;
      lcd.print("Short break!");
    }

    lcd.setCursor(0, 1);
    seconds = 0;
    minutes = 0;

    while(minutes<break_duration){
      seconds = 0;
      while(seconds<60){
        lcd.setCursor(0, 1);
        if(minutes<10){
          lcd.print("0");
        }
        lcd.print(minutes);
        lcd.print(":");
        if(seconds<10){
          lcd.print("0");
        }
        lcd.print(seconds);
        delay(1000);
        seconds++;
      }
      minutes++;
    }
    count++;  // increment the counter for the number of study sessions
  }
}
