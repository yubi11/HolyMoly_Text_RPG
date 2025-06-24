#include "StartGame.h"

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GameManager gm;
	StartGame(gm);
	return 0;
}