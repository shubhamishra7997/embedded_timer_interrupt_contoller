//https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html#gad28590624d422cdf30d626e0a506255f
//add code here.

void init_port(void); //SET A0 as OUTPUT
void init_timer(void); //SET the Timer

void setup() 
{
  // put your setup code here, to run once:
  volatile long i;
  int j=0;
  init_port();
  init_timer();
    Serial.begin(9600);
  while(1)
  {
    for(i=0; i<1000000; i++);
    Serial.println(j,DEC);
    j++;
  }

}


void init_timer() //SET the Timer
{
// USE datasheet
// make use of 16 bit timer, becuase compare is till 60000.
// Use register TCCR1A and TCCR1B (control registers) to set the CNC mode and prescaler to 256.
// TCNT1 to count for delay via interrupt's own clock.
// OCR1 to compare the cnt value with the given value of delay.
// use TIMSK1 (mask register) for setting the OCIE1A (bit 1).

volatile char *Timer_TCCR1A = 0x80;
volatile char *Timer_TCCR1B = 0x81;
volatile short *Timer_TCNT1 = 0x84;
volatile short  *Timer_OCR1A = 0x88;
volatile char *Timer_TIMSK1 = 0x6F;

*Timer_TCCR1A = 0;
*Timer_TCCR1B = 0;
*Timer_TCNT1 = 0;

*Timer_OCR1A = 60000; //the delay value.
*Timer_TCCR1B = 0x0C; //CTC mode and prescaler at 256.
*Timer_TIMSK1 = 0x02; //enable timer compare interrupt. 
}

void init_port()
{
  //FROM DATASHEET, volatile so that the compiler does not assign any value to the variable.
  volatile char *dir_f = (volatile char *) 0x30; 
   *dir_f = 0x01;  //only A0 OUTPUT.
}

ISR(TIMER1_COMPA_vect)
{
  volatile char *port_f = (volatile char *) 0x31; 
   *port_f ^= 0x01;  //toggle bit with XOR. 
}


void loop() 
{
  // put your main code here, to run repeatedly:
}


/*EXTRA CODE WITH TIMER0
//Create a 8bit timer, count till 255 (LED blink not visible)
void init_port(void);
void init_eight_bit_timer(void);


void setup() 
{
  // put your setup code here, to run once:
  volatile long i;
  int j=0;
  init_port();
  init_eight_bit_timer();
    Serial.begin(9600);
  while(1)
  {
    //for(i=0; i<1; i++);
    Serial.println(j,DEC);
    j++;
  }

}

void init_port()
{
  volatile char *dir_f = (volatile char *)0x30;
  *dir_f = 0x01;
}

void init_eight_bit_timer()
{
volatile char *T_TCCR0A = 0x24;
volatile char *T_TCCR0B = 0x25;
volatile char *T_TCNT0 = 0x26;
volatile char *T_OCR0A = 0x27;
volatile char* T_TIMSK0 = 0x6E;


*T_TCCR0A = 0;
*T_TCCR0B = 0;
*T_TCNT0 = 0;
*T_OCR0A = 25500; //interupt A
*T_TCCR0A = 0x02;
*T_TCCR0B = 0x04; //prescaler
*T_TIMSK0 = 0x02; //enable interrupt when compare A is matched.

}

ISR(TIMER0_COMPA_vect)
{
  volatile int j = 0x00;
  //volatile char *port_f = (volatile char *)0x31;
  //*port_f ^= 0x01;
    j = j ^ 0x01;
    Serial.println(j, HEX);
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
*/
