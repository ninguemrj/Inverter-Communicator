//20x4 LCD
#include <LiquidCrystal_I2C.h> //SDA = B7[A4], SCL = B6[A5] STM32/[Arduino]
LiquidCrystal_I2C lcd(0x27, 20, 4);

int menuCounter = 0; //counts the clicks of the rotary encoder between menu items (0-3 in this case)

int menu1_Value = 0; //value within menu 1
int menu2_Value = 0; //value within menu 2
int menu3_Value = 0; //value within menu 3
int menu4_Value = 0; //value within menu 4

bool menu1_selected = false; //enable/disable to change the value of menu item
bool menu2_selected = false;
bool menu3_selected = false;
bool menu4_selected = false;
//Note: if a menu is selected ">" becomes "X".

//Defining pins
//Arduino interrupt pins: 2, 3.
const int RotaryCLK = PB3; //CLK pin on the rotary encoder
const int RotaryDT = PB4; //DT pin on the rotary encoder
const int PushButton = PB5; //Button to enter/exit menu

//Statuses for the rotary encoder
int CLKNow;
int CLKPrevious;

int DTNow;
int DTPrevious;

bool refreshLCD = true; //refreshes values
bool refreshSelection = false; //refreshes selection (> / X)

void setup() 
{
  pinMode(PB3, INPUT_PULLUP); //RotaryCLK
  pinMode(PB4, INPUT_PULLUP); //RotaryDT
  pinMode(PB5, INPUT_PULLUP); //Button

  //------------------------------------------------------
  lcd.begin();                      // initialize the lcd   
  lcd.backlight();
  //------------------------------------------------------
  lcd.setCursor(0,0); //Defining positon to write from first row, first column .
  lcd.print("Menu demo");
  lcd.setCursor(0,1); //Second row, first column
  lcd.print("Rotary encoder"); 
  lcd.setCursor(0,2); //Second row, first column
  lcd.print("Improved version"); 
  delay(5000); //wait 2 sec
  
  lcd.clear(); //clear the whole LCD
  
  printLCD(); //print the stationary parts on the screen
  //------------------------------------------------------
  //Store states of the rotary encoder
  CLKPrevious = digitalRead(RotaryCLK);
  DTPrevious = digitalRead(RotaryDT);
      
  attachInterrupt(digitalPinToInterrupt(RotaryCLK), rotate, CHANGE); //CLK pin is an interrupt pin
  attachInterrupt(digitalPinToInterrupt(PushButton), pushButton, FALLING); //PushButton pin is an interrupt pin

}

void loop() 
{
  if(refreshLCD == true) //If we are allowed to update the LCD ...
  {
    updateLCD(); // ... we update the LCD ...

    //... also, if one of the menus are already selected...
    if(menu1_selected == true || menu2_selected == true || menu3_selected == true || menu4_selected == true)
    {
     // do nothing
    }
    else
    {
      updateCursorPosition(); //update the position
    }
    
    refreshLCD = false; //reset the variable - wait for a new trigger
  }

  if(refreshSelection == true) //if the selection is changed
  {
    updateSelection(); //update the selection on the LCD
    refreshSelection = false; // reset the variable - wait for a new trigger
  }
}

void rotate()
{  
  //-----MENU1--------------------------------------------------------------
  if(menu1_selected == true)
  {
  CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menu1_Value < 100) //we do not go above 100
      {
        menu1_Value++;  
      }
      else
      {
        menu1_Value = 0;  
      }      
    } 
    else 
    {
      if(menu1_Value < 1) //we do not go below 0
      {
          menu1_Value = 100;
      }
      else
      {
      // Encoder is rotating B direction so decrease
      menu1_Value--;      
      }      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
  }
  //---MENU2---------------------------------------------------------------
  else if(menu2_selected == true)
  {
    CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menu2_Value < 100) //we do not go above 100
      {
        menu2_Value++;  
      }
      else
      {
        menu2_Value = 0;  
      }      
    } 
    else 
    {
      if(menu2_Value < 1) //we do not go below 0
      {
          menu2_Value = 100;
      }
      else
      {
      // Encoder is rotating in B direction, so decrease
      menu2_Value--;      
      }      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
  }
  //---MENU3---------------------------------------------------------------
  else if(menu3_selected == true)
  {
    CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menu3_Value < 100) //we do not go above 100
      {
        menu3_Value++;  
      }
      else
      {
        menu3_Value = 0;  
      }      
    } 
    else 
    {
      if(menu3_Value < 1) //we do not go below 0
      {
          menu3_Value = 100;
      }
      else
      {
      // Encoder is rotating B direction so decrease
      menu3_Value--;      
      }      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
  }
  //---MENU4----------------------------------------------------------------
  else if(menu4_selected == true)
  {
    CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menu4_Value < 100) //we do not go above 100
      {
        menu4_Value++;  
      }
      else
      {
        menu4_Value = 0;  
      }      
    } 
    else 
    {
      if(menu4_Value < 1) //we do not go below 0
      {
          menu4_Value = 100;
      }
      else
      {
      // Encoder is rotating in B direction, so decrease
      menu4_Value--;      
      }      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
  }
  else //MENU COUNTER----------------------------------------------------------------------------
  {
  CLKNow = digitalRead(RotaryCLK); //Read the state of the CLK pin
  // If last and current state of CLK are different, then a pulse occurred  
  if (CLKNow != CLKPrevious  && CLKNow == 1)
  {
    // If the DT state is different than the CLK state then
    // the encoder is rotating in A direction, so we increase
    if (digitalRead(RotaryDT) != CLKNow) 
    {
      if(menuCounter < 3) //we do not go above 3
      {
        menuCounter++;  
      }
      else
      {
        menuCounter = 0;  
      }      
    } 
    else 
    {
      if(menuCounter < 1) //we do not go below 0
      {
          menuCounter = 3;
      }
      else
      {
      // Encoder is rotating CW so decrease
      menuCounter--;      
      }      
    }    
  }
  CLKPrevious = CLKNow;  // Store last CLK state
  }

  //Refresh LCD after changing the counter's value
  refreshLCD = true;
}

void pushButton()
{
  switch(menuCounter)
  {
     case 0:
     menu1_selected = !menu1_selected;  //we change the status of the variable to the opposite
     break;

     case 1:
     menu2_selected = !menu2_selected;
     break;

     case 2:
     menu3_selected = !menu3_selected;
     break;

     case 3:
     menu4_selected = !menu4_selected;
     break;
  } 
  
  refreshLCD = true; //Refresh LCD after changing the value of the menu
  refreshSelection = true; //refresh the selection ("X")
}

void printLCD()
{
  //These are the values which are not changing the operation
  
  lcd.setCursor(1,0); //1st line, 2nd block
  lcd.print("Menu 1"); //text
  //----------------------
  lcd.setCursor(1,1); //2nd line, 2nd block
  lcd.print("Menu 2"); //text
  //----------------------
  lcd.setCursor(1,2); //3rd line, 2nd block
  lcd.print("Menu 3"); //text
  //----------------------
  lcd.setCursor(1,3); //4th line, 2nd block
  lcd.print("Menu 4"); //text
  //----------------------
  lcd.setCursor(13,0); //1st line, 14th block
  lcd.print("cnt: "); //counts - text
}

void updateLCD()
{  
  lcd.setCursor(17,0); //1st line, 18th block
  lcd.print(menuCounter); //counter (0 to 3)

  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print("   "); //erase the content by printing space over it
  lcd.setCursor(9,0); //1st line, 10th block
  lcd.print(menu1_Value); //print the value of menu1_Value variable

  lcd.setCursor(9,1);
  lcd.print("   ");
  lcd.setCursor(9,1);
  lcd.print(menu2_Value); //
  
  lcd.setCursor(9,2);
  lcd.print("   ");
  lcd.setCursor(9,2);
  lcd.print(menu3_Value); //

  lcd.setCursor(9,3);
  lcd.print("   ");
  lcd.setCursor(9,3);
  lcd.print(menu4_Value); //  
}

void updateCursorPosition()
{
  //Clear display's ">" parts 
  lcd.setCursor(0,0); //1st line, 1st block
  lcd.print(" "); //erase by printing a space
  lcd.setCursor(0,1);
  lcd.print(" "); 
  lcd.setCursor(0,2);
  lcd.print(" "); 
  lcd.setCursor(0,3);
  lcd.print(" "); 
     
  //Place cursor to the new position
  switch(menuCounter) //this checks the value of the counter (0, 1, 2 or 3)
  {
    case 0:
    lcd.setCursor(0,0); //1st line, 1st block
    lcd.print(">"); 
    break;
    //-------------------------------
    case 1:
    lcd.setCursor(0,1); //2nd line, 1st block
    lcd.print(">"); 
    break;
    //-------------------------------    
    case 2:
    lcd.setCursor(0,2); //3rd line, 1st block
    lcd.print(">"); 
    break;
    //-------------------------------    
    case 3:
    lcd.setCursor(0,3); //4th line, 1st block
    lcd.print(">"); 
    break;
  }
}

void updateSelection()
{
  //When a menu is selected ">" becomes "X"

  if(menu1_selected == true)
  {
    lcd.setCursor(0,0); //1st line, 1st block
    lcd.print("X"); 
  }
  //-------------------
   if(menu2_selected == true)
  {
    lcd.setCursor(0,1); //2nd line, 1st block
    lcd.print("X"); 
  }
  //-------------------
  if(menu3_selected == true)
  {
    lcd.setCursor(0,2); //3rd line, 1st block
    lcd.print("X"); 
  }
  //-------------------
  if(menu4_selected == true)
  {
    lcd.setCursor(0,3); //4th line, 1st block
    lcd.print("X"); 
  }
}