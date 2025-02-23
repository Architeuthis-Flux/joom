





#include "RotaryEncoderStuff.h"
#include "pico/stdlib.h"
#include "quadrature.pio.h"
#include "hardware/pio.h"
#include <stdio.h>
#include <stdlib.h>

// #include "pico/types.h"

#define QUADRATURE_A_PIN 12
#define QUADRATURE_B_PIN 13
#define BUTTON_ENC 11


PIO pioEnc = pio1;

uint smEnc = 0;
uint offsetEnc = 0;
uint PIN_AB = 12;

int newPositionEncoder = 0;
int lastPositionEncoder = 0;
int encoderRaw = 0;
int lastPosition = 0;
int position = 0;
volatile bool resetPosition = false;

int lastButtonState = 0;




void initRotaryEncoder(void) {
    // pinMode(BUTTON_ENC, INPUT);
    //   pinMode(QUADRATURE_A_PIN, INPUT_PULLUP);
    //   pinMode(QUADRATURE_B_PIN, INPUT_PULLUP);
   // gpio_pull_up(BUTTON_ENC);
    gpio_set_dir(BUTTON_ENC, GPIO_IN);
    gpio_init(BUTTON_ENC);

    gpio_pull_up(QUADRATURE_A_PIN);
    gpio_pull_up(QUADRATURE_B_PIN);
    gpio_set_dir(QUADRATURE_A_PIN, GPIO_IN);
    gpio_set_dir(QUADRATURE_B_PIN, GPIO_IN);
    gpio_init(QUADRATURE_A_PIN);
    gpio_init(QUADRATURE_B_PIN);

    // stdio_init_all();
    //pio_claim_free_sm_and_add_program( &quadrature_encoder_program);
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&quadrature_encoder_program, &pioEnc, &smEnc, &offsetEnc, QUADRATURE_A_PIN, 2, true);
    // //pio_add_program(pioEnc, &quadrature_encoder_program);
    quadrature_encoder_program_init(pioEnc, smEnc, PIN_AB, 0);

    hard_assert(success);
    }

unsigned long buttonHoldTimer = 0;
unsigned long buttonHoldLength = 500;

unsigned long doubleClickTimer = 0;
unsigned long doubleClickLength = 250;

unsigned long buttonDebounceTimer = 0;
unsigned long buttonDebounceTimer2 = 0;
unsigned long debounceTime = 2000;

int encoderReleased = 0;

int encoderStepsToChangePosition = 1;

int buttonState = 1;
int lastRotaryDivider = 8;
int rotaryDivider = 1;
int rotState = 0;
int encoderWasPressed = 1;
int encoderIsPressed = 0;
volatile int numberOfSteps = 0;

volatile encoderDirectionStates encoderDirectionState = NONE;
volatile encoderButtonStates encoderButtonState = IDLE;

volatile encoderButtonStates lastButtonEncoderState = IDLE;

volatile encoderDirectionStates lastDirectionState = NONE;


int getEncoderRaw(void) {
    encoderRaw = quadrature_encoder_get_count(pioEnc, smEnc);
    return encoderRaw;
    }

int getEncoderPosition(void) {
    rotaryEncoderStuff();
    return position;
    }

void setEncoderPosition(int pos) {
    lastPositionEncoder = pos;
    position = pos;
    }


    int lastClick = 1;
    unsigned long lastClickTime = 0;
int getAllEncoderValues(void) {
    int held = 0;
    int click = 1;

    int released = 0;
    //gpio_set_pulls(BUTTON_ENC, true, false);

    gpio_set_input_enabled(BUTTON_ENC, true);  // rp2350 errata hack: setting it to input
    // right before reading and back fixes it
    click = gpio_get(BUTTON_ENC);

    gpio_set_input_enabled(BUTTON_ENC, false);

    if (click == 0) {

        }

        if (click == 0 && lastClick == 1) {
            lastClickTime = to_ms_since_boot(get_absolute_time());
            lastClick = click;
            }

        if (click == 0 && lastClick == 0) {
            if (to_ms_since_boot(get_absolute_time()) - lastClickTime > 800) {
                held = 1;
                lastClick = 1;
                //return 50;
                }
            }
            // if (click == 1 && lastClick == 0) {
            //     released = 1;
            //     }

           // lastClick = click;





    rotaryEncoderStuff();
    if (encoderDirectionState == UP) {
        encoderDirectionState = NONE;
        if (click == 0) {
            return 51;
            } else {
            return 1;
            }
        } else if (encoderDirectionState == DOWN) {
            encoderDirectionState = NONE;
            if (click == 0) {
                return -51;
                } else {
                return -1;
                }
        } else {
            if (held == 1) {
                return 50;
                }

                // if (released == 1) {
                if (click == 0) {
                    return 20;
                    }

            return 0;
            }


    }


void rotaryEncoderStuff(void) {

    lastButtonEncoderState = encoderButtonState;

    // buttonState = gpio_get(BUTTON_ENC);
     // Serial.print("buttonState: ");
     // Serial.println(buttonState);

    // if (buttonState == 0) {
    //     encoderIsPressed = 1;
    //     //     Serial.print("pressed: ");
    //    //Serial.println(encoderIsPressed);
    //     } else {
    //     encoderIsPressed = 0;
    //     // Serial.print("pressed: ");
    //     // Serial.println(encoderIsPressed);
    //     }

    // if (encoderIsPressed == 0 && encoderWasPressed == 0) {
    //     encoderButtonState = IDLE;
    //     // lastButtonEncoderState = IDLE;
    //     }

    // if (encoderIsPressed == 0 && encoderWasPressed == 1) {
    //     encoderButtonState = RELEASED;
    //     // lastButtonEncoderState = PRESSED;
    //     encoderReleased = 1;
    //     doubleClickTimer = to_ms_since_boot(get_absolute_time());
    //     buttonDebounceTimer2 = get_absolute_time();


    //     encoderWasPressed = encoderIsPressed;
    //     }

    // if (encoderIsPressed == 1 && encoderWasPressed == 1) {
    //     if (to_ms_since_boot(get_absolute_time()) - buttonHoldTimer > buttonHoldLength) {
    //         // lastButtonEncoderState = PRESSED;
    //         encoderButtonState = HELD;
    //         }
    //     }

    // if (encoderIsPressed == 1 && encoderWasPressed == 0) {
    //     buttonHoldTimer = to_ms_since_boot(get_absolute_time());
    //     // lastButtonEncoderState = IDLE;
    //     //pio_sm_restart(pioEnc, smEnc);
    //     // encoderRaw = quadrature_encoder_get_count(pioEnc, smEnc);
    //     // lastPositionEncoder = encoderRaw;

    //     if ((get_absolute_time()) - doubleClickTimer < doubleClickLength) {
    //         encoderButtonState = DOUBLECLICKED;

    //         } else {
    //         encoderButtonState = PRESSED;
    //         }
    //     doubleClickTimer = to_ms_since_boot(get_absolute_time());
    //     // buttonHoldTimer = millis();

    //     encoderWasPressed = encoderIsPressed;
    //     }

    // lastButtonState = buttonState;
    // encoderWasPressed = encoderIsPressed;

    // if (lastRotaryDivider != rotaryDivider) {
    //     //pio_sm_restart(pioEnc, smEnc);
    //     lastRotaryDivider = rotaryDivider;
    //     encoderRaw = quadrature_encoder_get_count(pioEnc, smEnc);
    //     //encoderRaw -= positionOffset;
    //     encoderRaw = encoderRaw / rotaryDivider;
    //     lastPositionEncoder = encoderRaw;

    //     // quadrature_program_init(pioEnc, smEnc, offsetEnc, QUADRATURE_A_PIN,
    //     // QUADRATURE_B_PIN);
    //     }
    // if (resetPosition == true) {
    //  // quadrature_encoder_program_init(pioEnc, smEnc, PIN_AB, 0);
    //   //pio_sm_restart(pioEnc, smEnc);
    //   //pio_sm_clear_fifos(pioEnc, smEnc);
    //   //pio_sm_drain_tx_fifo(pioEnc, smEnc);

    //   positionOffset = quadrature_encoder_get_count(pioEnc, smEnc);
    //   positionOffset = positionOffset / rotaryDivider;
    //   Serial.print("\n\n\rencoderRaw: ");
    //   Serial.println(encoderRaw);
    //   Serial.print("positionOffset: ");
    //   Serial.println(positionOffset);


    //   // encoderRaw -= positionOffset;
    //   // encoderRaw = encoderRaw / rotaryDivider;
    //   //lastPositionEncoder = positionOffset/rotaryDivider;
    //   resetPosition = false;
    // }

    encoderRaw = quadrature_encoder_get_count(pioEnc, smEnc);

    // encoderRaw = encoderRaw / rotaryDivider;
     //encoderRaw -= positionOffset;
     //   if (encoderRaw > lastPositionEncoder)
    numberOfSteps = abs(lastPositionEncoder - encoderRaw);

    if ((lastPositionEncoder - encoderRaw > 1 || lastPositionEncoder - encoderRaw < -1) || (lastPositionEncoder != encoderRaw && rotaryDivider < 8)) {

        if (lastPositionEncoder > encoderRaw && encoderDirectionState != DOWN) {
            position++;
            encoderDirectionState = UP;
            //numberOfSteps = abs(lastPositionEncoder - encoderRaw);
            numberOfSteps = abs(lastPositionEncoder - encoderRaw);

            lastPositionEncoder = encoderRaw;

            } else if (lastPositionEncoder < encoderRaw &&
                      encoderDirectionState != UP) {
            position--;
            encoderDirectionState = DOWN;
            numberOfSteps = lastPositionEncoder - encoderRaw;
            lastPositionEncoder = encoderRaw;

            } else {
                //encoderDirectionState = NONE;
                }

            //}

        } else {
        // encoderDirectionState = NONE;
        }
    }