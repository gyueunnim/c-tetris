// 블록, 게임화면 컨트롤 함수들의 정의

#include <time.h>
#include "common.h"
#include "point.h"
#include "blockInfo.h"
#include "keyCurControl.h"

static int currentBlockModel;
static int curPosX, curPosY;

// 블록의 첫 위치 지정
void InitNewBlockPos(int x, int y) {
	if (x < 0 || y < 0)
		return;

	curPosX = x;
	curPosY = y;

	SetCurrentCursorPos(x, y);
}

// 출력할 블록을 무작위 선택
void ChooseBlock(void) {
	srand((unsigned int)time(NULL));
	currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;
}

// 현재 출력해야 하는 블록의 index 반환
int GetCurrentBlockIdx(void) {
	return currentBlockModel;
}

// 블록 출력
void ShowBlock(char blockInfo[][4]) {
	int y, x;
	point curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);
			if (blockInfo[y][x] == 1)
				printf("■");
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);
}

// 현재 위치의 블록 삭제
void DeleteBlock(char blockInfo[][4]) {
	int y, x;
	point curPos = GetCurrentCursorPos();

	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			SetCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);
			if (blockInfo[y][x] == 1)
				printf("  ");
		}
	}
	SetCurrentCursorPos(curPos.x, curPos.y);
}

// 모니터에 그려진 블록을 아래로 한 칸 내림
void BlockDown(void) {
	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosY += 1;

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

// 블록을 왼쪽으로 한칸 이동
void ShiftLeft(void) {
	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX -= 2;

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

// 블록을 오른쪽으로 한칸 이동
void ShiftRight(void) {
	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX += 2;

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

// 블록을 90도 회전
void RotateBlock(void) {
	int nextRotSte;

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);

	nextRotSte = (rotateSte + 1) % 4;
	rotateSte = nextRotSte;

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}