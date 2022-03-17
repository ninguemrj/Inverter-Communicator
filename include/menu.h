
#define rotary_CLK 4
#define rotary_DT  15
#define rotary_SW  27
/*
int menuitems = 8;   // how many items you wan in your main menu

char menu_selected [menuitems-1];  // create "boolean" array with downshifted numbers od menuitems
char *menu_labels [menuitems-1] =   // create menu labels
                  {
                    "Info page 1",
                    "Menu 2",
                    "Menu 3",
                    "Menu 4",
                    "Menu 5",
                    "Menu 6",
                    "Menu 7",
                    "Lastmenu"
                  };

*/
// original values
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
// 

const int RotaryCLK = rotary_CLK; //CLK pin on the rotary encoder
const int RotaryDT = rotary_DT; //DT pin on the rotary encoder
const int PushButton = rotary_SW; //Button to enter/exit menu

//Statuses for the rotary encoder
int CLKNow;
int CLKPrevious;

int DTNow;
int DTPrevious;

bool refreshLCD = true; //refreshes values
bool refreshSelection = false; //refreshes selection (> / X)

#include <menu_functions.h>

void rotate()
{  
  //-----MENU1--------------------------------------------------------------
  if(menu1_selected == true)
  {
  menu1();
  }
  //---MENU2---------------------------------------------------------------
  else if(menu2_selected == true)
  {
  menu2();
  }
  //---MENU3---------------------------------------------------------------
  else if(menu3_selected == true)
  {
  menu3();
  }
  //---MENU4----------------------------------------------------------------
  else if(menu4_selected == true)
  {
  menu4();
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
  
  lcdsetCursor(1,0); //1st line, 2nd block
  lcdprint("Menu 1"); //text
  //----------------------
  lcdsetCursor(1,1); //2nd line, 2nd block
  lcdprint("Menu 2"); //text
  //----------------------
  lcdsetCursor(1,2); //3rd line, 2nd block
  lcdprint("Menu 3"); //text
  //----------------------
  lcdsetCursor(1,3); //4th line, 2nd block
  lcdprint("Menu 4"); //text
  //----------------------
  lcdsetCursor(13,0); //1st line, 14th block
  lcdprint("cnt: "); //counts - text
}

void updateLCD()
{  
  lcdsetCursor(17,0); //1st line, 18th block
  lcdprint(menuCounter); //counter (0 to 3)

  lcdsetCursor(9,0); //1st line, 10th block
  lcdprint("   "); //erase the content by printing space over it
  lcdsetCursor(9,0); //1st line, 10th block
  lcdprint(menu1_Value); //print the value of menu1_Value variable

  lcdsetCursor(9,1);
  lcdprint("   ");
  lcdsetCursor(9,1);
  lcdprint(menu2_Value); //
  
  lcdsetCursor(9,2);
  lcdprint("   ");
  lcdsetCursor(9,2);
  lcdprint(menu3_Value); //

  lcdsetCursor(9,3);
  lcdprint("   ");
  lcdsetCursor(9,3);
  lcdprint(menu4_Value); //  
}

void updateCursorPosition()
{
  //Clear display's ">" parts 
  lcdsetCursor(0,0); //1st line, 1st block
  lcdprint(" "); //erase by printing a space
  lcdsetCursor(0,1);
  lcdprint(" "); 
  lcdsetCursor(0,2);
  lcdprint(" "); 
  lcdsetCursor(0,3);
  lcdprint(" "); 
     
  //Place cursor to the new position
  switch(menuCounter) //this checks the value of the counter (0, 1, 2 or 3)
  {
    case 0:
    lcdsetCursor(0,0); //1st line, 1st block
    lcdprint(">"); 
    break;
    //-------------------------------
    case 1:
    lcdsetCursor(0,1); //2nd line, 1st block
    lcdprint(">"); 
    break;
    //-------------------------------    
    case 2:
    lcdsetCursor(0,2); //3rd line, 1st block
    lcdprint(">"); 
    break;
    //-------------------------------    
    case 3:
    lcdsetCursor(0,3); //4th line, 1st block
    lcdprint(">"); 
    break;
  }
}

void updateSelection()
{
  //When a menu is selected ">" becomes "X"

  if(menu1_selected == true)
  {
    lcdsetCursor(0,0); //1st line, 1st block
    lcdprint("X"); 
  }
  //-------------------
   if(menu2_selected == true)
  {
    lcdsetCursor(0,1); //2nd line, 1st block
    lcdprint("X"); 
  }
  //-------------------
  if(menu3_selected == true)
  {
    lcdsetCursor(0,2); //3rd line, 1st block
    lcdprint("X"); 
  }
  //-------------------
  if(menu4_selected == true)
  {
    lcdsetCursor(0,3); //4th line, 1st block
    lcdprint("X"); 
  }
}

void setup_rotary() 
{
  pinMode(rotary_CLK, INPUT_PULLUP); //RotaryCLK
  pinMode(rotary_DT, INPUT_PULLUP); //RotaryDT
  pinMode(rotary_SW, INPUT_PULLUP); //Button
  //------------------------------------------------------
  //Store states of the rotary encoder
  CLKPrevious = digitalRead(RotaryCLK);
  DTPrevious = digitalRead(RotaryDT);
      
  attachInterrupt(digitalPinToInterrupt(RotaryCLK), rotate, CHANGE); //CLK pin is an interrupt pin
  attachInterrupt(digitalPinToInterrupt(PushButton), pushButton, FALLING); //PushButton pin is an interrupt pin
}

void loop_menu() 
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