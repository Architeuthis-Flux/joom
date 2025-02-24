
#include <stdlib.h>
#include <stdio.h>

#include "pico/stdlib.h"





extern int rotaryDivider;
extern int encoderRaw;
extern volatile int numberOfSteps;
extern volatile bool resetPosition;



enum encoderDirectionStates { NONE,UP,DOWN };

enum encoderButtonStates { IDLE, PRESSED, HELD, RELEASED, DOUBLECLICKED};

typedef enum encoderDirectionStates encoderDirectionStates;
typedef enum encoderButtonStates encoderButtonStates;

extern volatile encoderDirectionStates encoderDirectionState;
extern volatile encoderButtonStates encoderButtonState;
extern volatile encoderButtonStates lastButtonEncoderState;
extern volatile encoderDirectionStates lastDirectionState;


 void initRotaryEncoder(void);
int getEncoderRaw(void);
int getEncoderPosition(void);
void resetEncoderPosition(int pos);
int getAllEncoderValues(void);

void rotaryEncoderStuff(void);