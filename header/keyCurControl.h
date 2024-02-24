// 커서 위치 표현

#ifndef __KEY_CUR_CONTROL_H_
#define __KEY_CUR_CONTROL_H_

#include "point.h"

void RemoveCursor(void);
point GetCurrentCursorPos(void);
void SetCurrentCursorPos(int x, int y);
int ProcessKeyInput(void);
void InitKeyDelayRate(int rate);
void KeyDelaySpeedCtl(int addSpeed);

#endif