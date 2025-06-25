#include "StartGame.h"

#include "common.h"// sound 관련 헤더는 common.h에 포함되어 있음

int main() 
{
	//_CrtSetBreakAlloc(605);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// 사운드 실행 - BGM
	FnPlayBGM();

	GameManager gm;
	StartGame(gm);

	// TODO : 메모리 누수 : 싱글톤 인스턴스 파괴 메서드
	gm.destroyPlayer();

	// 사운드 정지 - BGM
	FnStopBGM();

	return 0;
}