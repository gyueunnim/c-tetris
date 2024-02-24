// 블록, 게임화면 컨트롤 함수들의 정의

#include <time.h>
#include "common.h"
#include "point.h"
#include "blockInfo.h"
#include "keyCurControl.h"
#include "scoreLevelControl.h"

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2

static int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { 0, };

static int currentBlockModel;
static int curPosX, curPosY;
static int rotateSte;

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
	return currentBlockModel + rotateSte;
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

// 블록을 왼쪽으로 한칸 이동
void ShiftLeft(void) {
	if (!DetectCollision(curPosX - 2, curPosY, blockModel[GetCurrentBlockIdx()]))
		return;

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX -= 2;

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

// 블록을 오른쪽으로 한칸 이동
void ShiftRight(void) {
	if (!DetectCollision(curPosX + 2, curPosY, blockModel[GetCurrentBlockIdx()]))
		return;

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosX += 2;

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

// 블록을 90도 회전
void RotateBlock(void) {
	int nextRotSte;
	int beforeRotSte = rotateSte;

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);

	nextRotSte = (rotateSte + 1) % 4;
	rotateSte = nextRotSte;

	if (!DetectCollision(curPosX, curPosY + 1, blockModel[GetCurrentBlockIdx()])) {
		rotateSte = beforeRotSte;
		return;
	}
		
	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);
}

//블록의 이동 및 회전 가능 여부 판단
int DetectCollision(int posX, int posY, char blockModel[][4]) {
	int x, y;

	int arrX = (posX - GBOARD_ORIGIN_X) / 2;
	int arrY = posY - GBOARD_ORIGIN_Y;

	for (x = 0; x < 4; x++) {
		for (y = 0; y < 4; y++) {
			if (blockModel[y][x] == 1 && gameBoardInfo[arrY + y][arrX + x] == 1)
				return 0;
		}
	}
	return 1;
}

// 게임 판의 경계
void DrawGameBoard(void) {
	int x, y;

	for (y = 0; y <= GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
		
		if (y == GBOARD_HEIGHT)
			printf("└");
		else
			printf("│");
	}

	for (y = 0; y <= GBOARD_HEIGHT; y++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);

		if (y == GBOARD_HEIGHT)
			printf("┘");
		else
			printf("│");
	}

	for (x = 1; x < GBOARD_WIDTH + 1; x++) {
		SetCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		printf("─");
	}
	
	SetCurrentCursorPos(0, 0);

	for (y = 0; y < GBOARD_HEIGHT; y++) {
		gameBoardInfo[y][0] = 1;
		gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
	}

	for (x = 0; x < GBOARD_WIDTH + 2; x++) {
		gameBoardInfo[GBOARD_HEIGHT][x] = 1;
	}
}

// 배열에 현재 블록 정보 추가
void AddCurrentBlockInfoToBoard(void) {
	int x, y;

	int arrCurX;
	int arrCurY;

	for (y = 0; y < 4; y++) {
		for (x = 0; x < 4; x++) {
			arrCurX = (curPosX - GBOARD_ORIGIN_X) / 2;
			arrCurY = curPosY - GBOARD_ORIGIN_Y;

			if (blockModel[GetCurrentBlockIdx()][y][x] == 1)
				gameBoardInfo[arrCurY + y][arrCurX + x] = 1;
		}
	}
}

// 게임 종료 체크 함수
int IsGameOver(void) {
	if (!DetectCollision(curPosX, curPosY, blockModel[GetCurrentBlockIdx()]))
		return 1;
	else
		return 0;
}

// 굳어진 블록
void DrawSolidBlocks(void) {
	int x, y;
	int cursX, cursY;

	for (y = 0; y < GBOARD_HEIGHT; y++) {
		for (x = 1; x < GBOARD_WIDTH + 1; x++) {
			cursX = x * 2 + GBOARD_ORIGIN_X;
			cursY = y + GBOARD_ORIGIN_Y;
			SetCurrentCursorPos(cursX, cursY);

			if (gameBoardInfo[y][x] == 1)
				printf("■");
			else
				printf("  ");
		}
	}
}

// 블록 삭제
void RemoveFillUpLine(void) {
	int x, y;
	int line;

	for (y = GBOARD_HEIGHT - 1; y > 0; y--) {
		for (x = 1; x < GBOARD_WIDTH + 1; x++) {
			if (gameBoardInfo[y][x] != 1)
				break;
		}
		if (x == (GBOARD_WIDTH + 1)) {
			for (line = 0; y - line > 0; line++) {
				memcpy(&gameBoardInfo[y - line][1], &gameBoardInfo[(y - line) - 1][1], GBOARD_WIDTH * sizeof(int));
			}

			y++;
			AddGameScore(10);
			ShowCurrentScoreAndLevel();
		}
	}
	DrawSolidBlocks();
}

void SolidCurrentBlock(void) {
	while (BlockDown());
}


// 모니터에 그려진 블록을 아래로 한 칸 내림
int BlockDown(void) {
	if (!DetectCollision(curPosX, curPosY + 1, blockModel[GetCurrentBlockIdx()])) {
		AddCurrentBlockInfoToBoard();
		RemoveFillUpLine();
		return 0;
	}

	DeleteBlock(blockModel[GetCurrentBlockIdx()]);
	curPosY += 1;

	SetCurrentCursorPos(curPosX, curPosY);
	ShowBlock(blockModel[GetCurrentBlockIdx()]);

	return 1;
} 