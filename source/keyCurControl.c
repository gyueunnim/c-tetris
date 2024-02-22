// 커서, 키보드 컨트롤 함수들 정의

#include <conio.h>
#include <Windows.h>
#include "point.h"


// 깜빡 거리는 커서 제거
void RemoveCursor(void) {
	CONSOLE_CURSOR_INFO curInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// 현재 커서 위치 정보를 담은 구조체 변수 반환
point GetCurrentCursorPos(void) {
	point curPoint;
	CONSOLE_SCREEN_BUFFER_INFO curInfo;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
	curPoint.x = curInfo.dwCursorPosition.X;
	curPoint.y = curInfo.dwCursorPosition.Y;

	return curPoint;
}

// 커서 위치 설정
void SetCurrentCursorPos(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 키 입력 처리
void ProcessKeyInput(void) {
	int i;
	int key;

	for (i = 0; i < KEY_SENSITIVE; i++) {
		if (_kbhit() != 0) {
			key = _getch();

			switch (key) {
			case LEFT:
				ShiftLeft();
				break;
			case RIGHT:
				ShiftRight();
				break;
			case UP:
				RotateBlock();
				break;
			}
		}
		if (i % keyDelayRate == 0)
			Sleep(SYS_DELAY);
	}
}

// 
void InitKeyDelayRate(int rate) {
	if (rate < 1)
		return;
	keyDelayRate = rate;
}