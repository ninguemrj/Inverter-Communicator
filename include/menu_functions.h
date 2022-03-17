void menu1()
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

void menu2()
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

void menu3()
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

void menu4()
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