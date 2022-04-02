void menuSelected(int menuPoint)   
{
 if (menu_selected[menuPoint])
      {
      switch (menuPoint)   
        {
         /*
          * write your menus loops in the cases. 
          * 1st menupoint always 0. 
          * you have to exetend cases to maxemnucases-1.
          * e.g. maxemenuitems = 14 then your last case is 13
          */
        case 0 :
        //lcd.clear();
        if (LCDupdate)         // "pragma once run"
          {
          lcd.clear();
          
          inverter_LCD_base(QPIGS);
          LCDupdate=false;
          }
        invereter_receive(QPIGS);
         break;
        
        case 1 :
        if (LCDupdate)          // "pragma once run"
          {
          lcd.clear();
          LCDupdate=false;
            lcd.setCursor(0,0);
        lcd.print(inverter_send("QID"));
          }
          invereter_receive();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print(String(pipVals.deviceStatus));
        delay(500);
        yield();
        //delay(1000);

        break;
    
        case 2 :
        break;
        
        case 3 :
        break;
        }
      }
}