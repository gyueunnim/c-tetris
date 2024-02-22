// 커서, 키보드 컨트롤 함수들 정의

#ifndef __KEY_CUR_CONTROL_H_
#define __KEY_CUR_CONTROL_H_

#include "point.h"

void RemoveCursor(void);
point GetCurrentCursorPos(void);
void SetCurrentCursorPos(int x, int y);
void ProcessKeyInput(void);
void InitKeyDelayRate(int rate);

#endif