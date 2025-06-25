#include "StartGame.h"

// 사운드 관련
#include "common.h"// sound 관련 헤더는 common.h에 포함되어 있음


int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 사운드 실행 - BGM
	FnPlayBGM();

	GameManager gm;
	StartGame(gm);

	// 사운드 정지 - BGM
	FnStopBGM();

	return 0;
}