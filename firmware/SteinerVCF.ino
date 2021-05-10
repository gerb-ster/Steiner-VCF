#define LP 0
#define BP 1
#define HP 2
#define LP_HP 3
#define LP_BP 4
#define BP_HP 5

#define MODE_COUNT 6

#define BTN_PORT 0
#define LP_PORT 1
#define BP_PORT 2
#define HP_PORT 3

int button_state;
int last_button_state = LOW;

unsigned long last_debounce_time = 0;
unsigned long debounce_delay = 50;

int current_mode = 0;

int enable_mode(int mode)
{
  // set all to low
  digitalWrite(LP_PORT, LOW);
  digitalWrite(BP_PORT, LOW);
  digitalWrite(HP_PORT, LOW);

  // set selected mode
  switch(mode)
  {
    case LP:
      digitalWrite(LP_PORT, HIGH);
    break;

    case BP:
      digitalWrite(BP_PORT, HIGH);
    break;

    case HP:
      digitalWrite(HP_PORT, HIGH);
    break;

    case LP_HP:
      digitalWrite(LP_PORT, HIGH);
      digitalWrite(HP_PORT, HIGH);
    break;

    case LP_BP:
      digitalWrite(LP_PORT, HIGH);
      digitalWrite(BP_PORT, HIGH);
    break;

    case BP_HP:
      digitalWrite(BP_PORT, HIGH);
      digitalWrite(HP_PORT, HIGH);
    break;
  }
}

void setup() 
{
  // button port
  pinMode(BTN_PORT, INPUT);

  // output port
  pinMode(LP_PORT, OUTPUT);
  pinMode(BP_PORT, OUTPUT);
  pinMode(HP_PORT, OUTPUT);

  // start
  enable_mode(current_mode);
}

void loop() 
{
  int reading = digitalRead(0);

  if (reading != last_button_state)
  {
    last_debounce_time = millis();
  }
  
  if ((millis() - last_debounce_time) > debounce_delay) 
  {
    if (reading != button_state)
    {
      button_state = reading;

      if (button_state == HIGH) 
      {
        current_mode++;

        if(current_mode == MODE_COUNT)
        {
          current_mode = 0;
        }
        
        enable_mode(current_mode);
      }
    }
  }

  last_button_state = reading;
}
