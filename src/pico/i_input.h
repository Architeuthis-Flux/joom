
#ifndef __I_INPUT__
#define __I_INPUT__

#include "doomtype.h"

#define MAX_MOUSE_BUTTONS 8

extern float mouse_acceleration;
extern int mouse_threshold;

void I_BindInputVariables(void);
void I_ReadMouse(void);

// I_StartTextInput begins text input, activating the on-screen keyboard
// (if one is used). The caller indicates that any entered text will be
// displayed in the rectangle given by the provided set of coordinates.
void I_StartTextInput(int x1, int y1, int x2, int y2);

// I_StopTextInput finishes text input, deactivating the on-screen keyboard
// (if one is used).
void I_StopTextInput(void);
#if DOOM_TINY
void I_GetEvent(void);
void I_GetEventTimeout(int);
int GetTypedChar(int scancode, boolean shiftdown);
#endif

#endif
