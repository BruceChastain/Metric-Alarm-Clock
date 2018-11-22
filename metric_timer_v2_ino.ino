/*
Need to do:
-Add snooze function
- need to find a way for the alarm to remeber it's last setting, I don't want to have to reset the alarm each time it's turned off
*/

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); //works for the intervolmeter and metric clock
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // another common config

// constants won't change. They're used here to 
// set pin numbers:
const int button0Pin = 0;     // the number of the pushbutton pin
const int button1Pin = 1;     // the number of the pushbutton pin
const int button2Pin = 13;     // the number of the pushbutton pin
const int button4Pin = 2;     // the number of the pushbutton pin

// variables will change:
int button0State = 0;         // variable for reading the pushbutton status
int lastbutton0State = 0;     //previous state of the button
int button1State = 0;
int lastbutton1State = 0;
int button2State = 0;
int button4State = 0;
int lastbutton4State = 0;
int alarm_is_set = 0;
int clock_is_running = 1;
int temp_hour; // temporary holder for the hour value
int temp_minute; // temporary holder for the minute value
int numberselect = 0;                     // setting the start variable for the numberselect value
int sethour(long hour_c);  // the real time which will be used for interval
int setminute(long setminute);  // the real time which will be used for interval
int set_day(long day);
int clock(long hour_c);
long hour_c = -5;
long minute_c = -5;
int second_c = 0; 
int alarmhour;
int alarmminute;
int LCDlight = 3; // Give the LCD backlight a number
int day;
int temperaturePin = 5; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade 
                        //(500 mV offset) to make negative temperatures an option
int led = 4;


//************************************
//*****Setup**************************
//************************************
void setup() { 
  int led = 4; // give the led a name and number
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.  
  // initialize the pushbutton pin as an input:
  pinMode(button0Pin, INPUT); 
  pinMode(button1Pin, INPUT); 
  pinMode(button2Pin, INPUT);
  pinMode(button4Pin, INPUT);
  pinMode(led, OUTPUT);
  pinMode(LCDlight, OUTPUT);  
  pinMode(6, OUTPUT);
  pinMode(led, OUTPUT);
}


//************************************
//*****Main***************************
//************************************
void loop(){ 
digitalWrite(LCDlight, HIGH);
lcd.print("Metric Clock V.1");// intro
lcd.setCursor(0, 1);
lcd.print("Chas-Tec");
delay(1000);
lcd.clear();

  
sethour(button0State, button1State, lastbutton0State, lastbutton1State);  // calling function find hour 

setminute(button0State = 0, button1State = 0, lastbutton0State = 0, lastbutton1State = 0);  // calling function find minute
    
set_day(button0State = 0, button1State = 0, lastbutton0State = 0, lastbutton1State = 0);  // calling function to set date

//**********Run the clock**************

lcd.clear();
button0State = digitalRead(button0Pin);
button1State = digitalRead(button1Pin);
button2State = digitalRead(button2Pin);
button4State = digitalRead(button4Pin);
    
while(clock_is_running == 1){
button2State = digitalRead(button2Pin);
button1State = digitalRead(button1Pin);
button0State = digitalRead(button0Pin);
button4State = digitalRead(button4Pin);
 
lcd.setCursor(0, 0);
    if(hour_c < 10){
      lcd.print("0");
    }    
    lcd.print(hour_c);
    lcd.print(":");    
//-------------------   
    if(minute_c < 10){
      lcd.print("0");
    }   
    lcd.print(minute_c);     
    lcd.print(":");
//-------------------  
    if(second_c < 10){
      lcd.print("0");   
    }   
    lcd.print(second_c);
//-------------------
      lcd.setCursor(0, 1);
    if (day == 0) {
      lcd.print("Sunday");
    } 
//------------------- This section converts the day value from a number to the word and prints the word    
      lcd.setCursor(0, 1);
    if (day == 1) {
      lcd.print("Monday");
    } 
    
      lcd.setCursor(0, 1);
    if (day == 2) {
      lcd.print("Tuesday");
    } 
    
      lcd.setCursor(0, 1);
    if (day == 3) {
      lcd.print("Wednesday");
    } 
    
      lcd.setCursor(0, 1);
    if (day == 4) {
      lcd.print("Thursday");
    } 
    
      lcd.setCursor(0, 1);
    if (day == 5) {
      lcd.print("Friday");
    } 
    
      lcd.setCursor(0, 1);
    if (day == 6) {
      lcd.print("Saturday");
    }    
 

//-------------------

    delay(851); // 1 metric seconds = .864 regular seconds, take away for calibration
    delayMicroseconds(2000); //   
    second_c ++; //The real heart of this whole clock

   
        if (second_c == 100){  
/*          float getVoltage(int pin); // call function "getVoltage", every minute check the tempture                                   

          float temperature = getVoltage(temperaturePin);  //getting the voltage reading from the temperature sensor
          temperature = (temperature - .5) * 100;          //converting from 10 mv per degree wit 500 mV offset
  
          lcd.print(" ");                                                  //to degrees ((volatge - 500mV) times 100)
          lcd.print(temperature);
          lcd.print("C");
*/ 
          second_c = 0;
          minute_c ++;                             
                          }
                                                   
        if (minute_c == 100){      
          minute_c = 0;   
          hour_c ++;     
        }
        if (hour_c == 10){      
          hour_c = 0;   
          day ++;     
        } 
        
        if (day == 7){      
          day = 0;       
        }         

        if (button2State == 0){
          if (alarm_is_set == 0){            
          temp_hour = hour_c; //holding the hour value so it can be put back the same when leaving the IF
          temp_minute = minute_c; //holding the hour value so it can be put back the same when leaving the IF
          lcd.clear(); 
          lcd.print("Set alarm now");
          delay(1000);
          lcd.clear();  
          numberselect = 0; // sets the selected number for hours back to zero
          sethour(button0State, button1State, lastbutton0State, lastbutton1State);  // calling function find hour 

          lcd.clear();

          setminute(button0State = 0, button1State = 0, lastbutton0State = 0, lastbutton1State = 0);  // calling function find minute
            
          lcd.clear(); // telling user that the alarm is now set
          lcd.print("Alarm is set");
          delay(1000);
            
          alarmhour = hour_c;
          alarmminute = minute_c;
          hour_c = temp_hour; // putting the hour value back to what it was
          minute_c = temp_minute; // putting the minute value back to what it was
          alarm_is_set = 1;
          lcd.clear();
          }}
          
        if (button2State == 1){ // this turns the alarm off if the switch is off                       
          alarm_is_set = 0;
          }
        if (alarm_is_set == 1){  
            digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
        }
        if (alarm_is_set == 0){  
            digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
        }        
            
                  analogWrite(6, 0);
                  lcd.clear(); // clears out the "WAKE UP!!!" message                                  
        if (button2State == 0){
          if (alarm_is_set == 1){  // part that looks to kick off the actual alarm
            if (hour_c == alarmhour){
              if (minute_c == alarmminute){
                lcd.setCursor(0, 1);
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("          ALARM!");
                analogWrite(6, 2); // speaker, pin 6, tone 2
                

                  if (button4State == 1){

                  analogWrite(6, 0); // speaker, pin 6, tone 0  
                  lcd.setCursor(0, 1);
                  lcd.clear();         
                } 
                              
              }}}} 
       
        if (button1State == 0){ 
          minute_c = minute_c + 1;    
        }   
        
        if (button0State == 0){ 
          minute_c = minute_c - 1;    
        }    
         
}}
 

//************************************
//*****End of Main********************
//************************************



//************************************
//*****Functions**********************
//************************************

// **********************************************  
//*****Set hour******************
// **********************************************  
int sethour(int button0State, int button1State,int lastbutton0State,int lastbutton1State){

  
lcd.print("Set hour");
hour_c = -5;
while(hour_c == -5){  
 
    button0State = digitalRead(button0Pin);
    button1State = digitalRead(button1Pin);
    
    if (button0State != lastbutton0State){       // the counter
        if (button0State == 1){
        numberselect = numberselect + 1;
        }
    }
    if (numberselect == 12){     // resets to 1 after reaching 11
        numberselect = 2;
   }

   // ************************ the selections ******

    if (numberselect == 2){
        lcd.clear();
        lcd.print("Set hour");
        lcd.setCursor(0, 1);
        lcd.print("0");
        if (button1State != lastbutton1State){
            if (button1State == 0){
            hour_c = 0;
      }}}    
  
    if (numberselect == 3){
        lcd.setCursor(0, 1);
        lcd.print("1");
        if (button1State != lastbutton1State){
            if (button1State == 0){
            hour_c = 1;
      }}}
  
    if (numberselect == 4){
        lcd.setCursor(0, 1);
        lcd.print("2");
        if (button1State != lastbutton1State){
            if (button1State == 0){ 
            hour_c = 2;
      }}}
  
    if (numberselect == 5){
        lcd.setCursor(0, 1);
        lcd.print("3");
        if (button1State != lastbutton1State){
            if (button1State == 0){ 
            hour_c = 3;
      }}}
  
    if (numberselect == 6){   
        lcd.setCursor(0, 1);
        lcd.print("4");
        if (button1State != lastbutton1State){
            if (button1State == 0){
            hour_c = 4;        
      }}}
  
     if (numberselect == 7){   
     lcd.setCursor(0, 1);
     lcd.print("5");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             hour_c = 5;        
      }}}
  
     if (numberselect == 8){   
     lcd.setCursor(0, 1);
     lcd.print("6");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             hour_c = 6;        
      }}}
  
     if (numberselect == 9){   
     lcd.setCursor(0, 1);
     lcd.print("7");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             hour_c = 7;        
      }}}
  
     if (numberselect == 10){   
     lcd.setCursor(0, 1);
     lcd.print("8");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             hour_c = 8;        
      }}}
      
           if (numberselect == 11){   
     lcd.setCursor(0, 1);
     lcd.print("9");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             hour_c = 9;        
      }}}
      
lastbutton0State = button0State;
lastbutton1State = button1State;
delay (200);
}
return hour_c;
}


// ***************************************** 
// ************************ setminute ******
// *****************************************   
  
int setminute(int button0State, int button1State,int lastbutton0State,int lastbutton1State){
lcd.clear(); 
numberselect = 0;
minute_c = -5;
while(minute_c == -5){

  
    button0State = digitalRead(button0Pin);
    button1State = digitalRead(button1Pin);
 
    if (button0State != lastbutton0State){       // the button push counter
        if (button0State == 1){
        numberselect = numberselect + 1;
        }
    }
    if (numberselect == 22){     // resets to 1 after reaching 11
        numberselect = 2;
   }
   
   // ************************ the selections ******
    if (numberselect == 1){
        lcd.clear();
        lcd.print("Set minute");                  
      } 
      
    if (numberselect == 2){
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("0");
        if (button1State != lastbutton1State){
            if (button1State == 0){
            minute_c = 0;
      }}} 
  
    if (numberselect == 3){
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("5");
        if (button1State != lastbutton1State){
            if (button1State == 0){ 
            minute_c = 5;
      }}}
  
    if (numberselect == 4){
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("10");
        if (button1State != lastbutton1State){
            if (button1State == 0){ 
            minute_c = 10;
      }}}
  
    if (numberselect == 5){
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("15");
        if (button1State != lastbutton1State){
            if (button1State == 0){ 
            minute_c = 15;
      }}}
  
    if (numberselect == 6){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("20");
        if (button1State != lastbutton1State){
            if (button1State == 0){
            minute_c = 20;        
      }}}
  
     if (numberselect == 7){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("25");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 25;        
      }}}
  
     if (numberselect == 8){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("30");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 30;        
      }}}
  
     if (numberselect == 9){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("35");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 35;        
      }}}
  
     if (numberselect == 10){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("40");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 40;        
      }}}
      
     if (numberselect == 11){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("45");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 45;        
      }}}
      
     if (numberselect == 12){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("50");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 50;        
      }}}
      
           if (numberselect == 13){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("55");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 55;        
      }}}
      
     if (numberselect == 14){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("60");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 60;        
      }}}   
   
     if (numberselect == 15){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("65");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 65;        
      }}}       
      
           if (numberselect == 16){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("70");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 70;        
      }}}       
      
           if (numberselect == 17){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("75");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 75;        
      }}}       
      
           if (numberselect == 18){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("80");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 80;        
      }}}       
      
           if (numberselect == 19){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("85");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 85;        
      }}}       
      
           if (numberselect == 20){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("90");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 90;        
      }}}       
      
           if (numberselect == 21){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("95");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 95;        
      }}}       
      
           if (numberselect == 22){   
        lcd.clear();
        lcd.print("Set minute");          
        lcd.setCursor(0, 1);
        lcd.print("100");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             minute_c = 100;        
      }}}       
      
lastbutton0State = button0State;
lastbutton1State = button1State;
delay (200);
}
return minute_c;
}


// **********************************************  
//*****Set Day******************
// **********************************************  
int set_day(int button0State, int button1State,int lastbutton0State,int lastbutton1State){
  
numberselect = 1;
lcd.clear();  
lcd.print("Set day of week");
day = -5;
while(day == -5){  
 
    button0State = digitalRead(button0Pin);
    button1State = digitalRead(button1Pin);
    
    if (button0State != lastbutton0State){       // the counter
        if (button0State == 1){
        numberselect = numberselect + 1;
        }
    }
    if (numberselect == 10){     // resets to 1 after reaching 11
        numberselect = 2;
   }

   // ************************ the selections ******

    if (numberselect == 2){
        lcd.clear();
        lcd.print("Set day of week");                  
      } 

    if (numberselect == 3){
        lcd.clear();
        lcd.print("Set day of week");
        lcd.setCursor(0, 1);
        lcd.print("Sunday");
        if (button1State != lastbutton1State){
            if (button1State == 0){
            day = 0;
      }}}    
  
    if (numberselect == 4){
        lcd.clear();
        lcd.print("Set day of week");
        lcd.setCursor(0, 1);
        lcd.print("Monday");
        if (button1State != lastbutton1State){
            if (button1State == 0){ 
            day = 1;
      }}}
  
    if (numberselect == 5){ 
        lcd.clear(); 
        lcd.print("Set day of week");  
        lcd.setCursor(0, 1);
        lcd.print("Tuesday");
        if (button1State != lastbutton1State){
            if (button1State == 0){ 
            day = 2;
      }}}
  
    if (numberselect == 6){
        lcd.clear();  
        lcd.print("Set day of week");   
        lcd.setCursor(0, 1);
        lcd.print("Wednesday");
        if (button1State != lastbutton1State){
            if (button1State == 0){
            day = 3;        
      }}}
  
     if (numberselect == 7){  
        lcd.clear();    
        lcd.print("Set day of week");
        lcd.setCursor(0, 1);
        lcd.print("Thursday");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             day = 4;        
      }}}
  
     if (numberselect == 8){ 
       lcd.clear();  
       lcd.print("Set day of week");
       lcd.setCursor(0, 1);
       lcd.print("Friday");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             day = 5;        
      }}}
  
     if (numberselect == 9){  
        lcd.clear(); 
        lcd.print("Set day of week");
        lcd.setCursor(0, 1);
        lcd.print("Saturday");
         if (button1State != lastbutton1State){
             if (button1State == 0){
             day = 6;        
      }}}
  
     
lastbutton0State = button0State;
lastbutton1State = button1State;
delay (200);
}
return day;
}







float getVoltage(int pin){
return (analogRead(pin) * .004882814); //converting from a 0 to 1023 digital range // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}

