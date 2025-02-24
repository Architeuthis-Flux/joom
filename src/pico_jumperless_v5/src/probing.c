
#include "probing.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico/time.h"


#define probeRev 4 //3 is the one the beta testers have



#define BUTTON_PIN 9
#define PROBE_PIN 10

volatile int checkingButton = 0;

void probeInit(void) {
  gpio_init(BUTTON_PIN);
  gpio_init(PROBE_PIN);
  gpio_set_dir(BUTTON_PIN, GPIO_IN);
  gpio_set_dir(PROBE_PIN, GPIO_OUT);
  // gpio_put(BUTTON_PIN, 0);
  gpio_put(PROBE_PIN, 1);
  }


int checkProbeButton(void) {
  //return 0;

  int buttonState = 0;
  int buttonState2 = 0;
  int buttonState3 = 0;
  checkingButton = 1;



  sleep_us(200);
 //gpio_put(PROBE_PIN, 1);



  gpio_set_pulls(BUTTON_PIN, false, true);

   sleep_us(2000);

  gpio_set_input_enabled(BUTTON_PIN, true);  // rp2350 errata hack: setting it to input
  buttonState = gpio_get(BUTTON_PIN);// right before reading and back fixes it
  gpio_set_input_enabled(BUTTON_PIN, false);

    

  gpio_set_pulls(BUTTON_PIN, true, false);

 
sleep_us(2000);
  gpio_set_input_enabled(BUTTON_PIN, true);
  buttonState2 = gpio_get(BUTTON_PIN);
  gpio_set_input_enabled(BUTTON_PIN, false);


   


  gpio_set_pulls(BUTTON_PIN, false, true);
sleep_us(2000);
  gpio_set_input_enabled(BUTTON_PIN, true);
  buttonState3 = gpio_get(BUTTON_PIN);
  gpio_set_input_enabled(BUTTON_PIN, false);

  //gpio_set_pulls(BUTTON_PIN, false, false);


  //gpio_set_function(2, GPIO_FUNC_PIO0);

  //checkingButton = 0;


  if (buttonState == 1 && buttonState2 == 1 &&
      buttonState3 == 1) { // disconnect Button
    // Serial.print("buttonState ");
    // Serial.print(buttonState);
    // Serial.print("buttonState2 ");
    // Serial.println(buttonState2);
    // Serial.println(" ");
    // Serial.println("disconnect button");
if (probeRev >= 4) {
    return 1;
    } else {
    return 2;
    }
  

    // return 1;
    } else if (buttonState == 0 && buttonState2 == 0 &&
               buttonState3 == 0) { // connect Button
    // Serial.print("buttonState ");
    // Serial.println(buttonState);
    // Serial.print("buttonState2 ");
    // Serial.println(buttonState2);
    // Serial.println(" ");
    // Serial.println("connect button");

    if (probeRev >= 4) {
    return 2;
    } else {
    return 1;
    }

    // return 2;
    }
  //   Serial.print("buttonState ");
  // Serial.println(buttonState);
  // Serial.print("buttonState2 ");
  // Serial.println(buttonState2);
  // Serial.println(" ");

  return 0;
  }