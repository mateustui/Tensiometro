//https://howtomechatronics.com/tutorials/arduino/arduino-wireless-communication-nrf24l01-tutorial/
//https://how2electronics.com/esp8266-nrf24l01-gateway-arduino-node/
//http://donalmorrissey.blogspot.com/2010/04/sleeping-arduino-part-5-wake-up-via.html


#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
volatile int f_wdt = 1;
#include <SoftwareSerial.h>
SoftwareSerial loraSerial(2, 3); // TX, RX
long int cont = 0;
#define led 13
#define gate 11
#define M0 4
#define M1 5
const char text1[10] ;
const char text2[10] ;
const char bat[10] ;


ISR(WDT_vect)
{
  f_wdt++;
  /*if(f_wdt == 0)
    {
    f_wdt=1;
    }
    else
    {
    Serial.println("WDT Overrun!!!");
    }*/
}
void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_SAVE);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();

  /* Now enter sleep mode. */
  sleep_mode();

  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */

  /* Re-enable the peripherals. */
  power_all_enable();
}




void setup() {
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(gate, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(gate, HIGH);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  loraSerial.begin(9600);

  /* Clear the reset flag. */
  MCUSR &= ~(1 << WDRF);

  /* In order to change WDE or the prescaler, we need to
     set WDCE (This will allow updates for 4 clock cycles).
  */
  WDTCSR |= (1 << WDCE) | (1 << WDE);

  /* set new watchdog timeout prescaler value */
  WDTCSR = 1 << WDP0 | 1 << WDP3; /* 8.0 seconds */

  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);

  //Serial.println("Initialisation complete.");
  delay(100); //Allow for serial print to complete.
}

void loop() {
  if (f_wdt == 75)
  {
    PORTD = 0b00000000;
    //PORTB = 0b00010000;
    digitalWrite(gate, HIGH);
    delay(100);
    int adc_press1 = analogRead(A0);
    int adc_press2 = analogRead(A1);
    int adc_bat = analogRead(A2);
    float v_s = 1023.0;
    float k = 0.009;
    float offset=4.2;
    
    float v_out1 = 5.0 * adc_press1 / 1024.0;
    float pressao1 = (((adc_press1 / v_s) - 0.04) / k )+ offset;
    dtostrf(pressao1, 6, 2, text1);

    float v_out2 = 5.0 * adc_press2 / 1024.0;
    float pressao2 = (((adc_press2 / v_s) - 0.04) / k )+ offset;
    dtostrf(pressao2, 6, 2, text2);

    float v_out3 = 0.0046 * adc_bat - 0.0096;
    dtostrf(v_out3, 4, 2, bat);
    
    String msg = "#"+String(text1)+"*"+String(text2)+"*"+String(bat)+"#";
    
   
   Serial.println(msg);
    loraSerial.println(msg);
    delay(100);
    PORTD = 0b00110000;
    //PORTB = 0b00000000;
    digitalWrite(gate, LOW);
    /* Don't forget to clear the flag. */
    f_wdt = 0;

    /* Re-enter sleep mode. */
    enterSleep();
  }
  else
  {
    /* Do nothing. */
  }
}
