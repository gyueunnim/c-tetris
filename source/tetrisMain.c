#include <Windows.h>
#include "common.h"
#include "keyCurControl.h"
#include "blockStageControl.h"
#include "scoreLevelControl.h"

#define START_CURPOS_X (5 * 2)
#define START_CURPOS_Y (0)

int main(void) {
	RemoveCursor();

	InitKeyDelayRate(10); // 게임 속도 설정

	DrawGameBoard();

	ShowCurrentScoreAndLevel() ;

	while (1) {
		InitNewBlockPos(START_CURPOS_X, START_CURPOS_Y);
		   
		ChooseBlock();

		if (IsGameOver())
			break; 

		while (1) { 
			if (BlockDown() == 0) {
				// AddCurrentBlockInfoToBoard();
				break;
			}
			if (ProcessKeyInput())
				break;
		}
	}
	 
	SetCurrentCursorPos(10, 10);
	puts("GAME OVER ^^");

	return 0;
}