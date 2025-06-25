#include "StartGame.h"

// 사운드 관련
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 사운드 - 백그라운드에서 비동기 재생, 루프
	PlaySound(TEXT("sound_HolyMoly.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	GameManager gm;
	StartGame(gm);

	// 사운드 정지
	PlaySound(NULL, 0, 0);

	return 0;
}