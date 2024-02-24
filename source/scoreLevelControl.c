#include "common.h"
#include "keyCurControl.h"

#define LEVEL_DIFF 2 // 단계별 속도 증가
#define LEVEL_UP_SCORE_DIFF 20 // 레벨 증가 스코어 간격

static int curGameLevel = 1;
static int curGameScore = 0;
 
// 점수와 레벨 출력 
void ShowCurrentScoreAndLevel(void) {
	SetCurrentCursorPos(30, 4);
	printf("★	현재 레벨 : %d	  ★", curGameLevel);

	SetCurrentCursorPos(30, 7);
	printf("☆	현재 점수 : %d	  ☆", curGameScore);
}

// 게임 레벨업
void GameLevelUp(void) {
	curGameLevel++;
	KeyDelaySpeedCtl(LEVEL_DIFF);
}

// 게임 점수
void AddGameScore(int score) {
	if (score < 1)
		return;

	curGameScore += score;

	if (curGameScore >= curGameLevel * LEVEL_UP_SCORE_DIFF)
		GameLevelUp();
}