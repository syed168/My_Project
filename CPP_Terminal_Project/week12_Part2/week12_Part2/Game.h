#pragma once
#include "GameStateMachine.h"

class Game {

	GameStateMachine* m_pStateMachine;

public:

	Game();
	void Initialize(GameStateMachine* pStateMachine);
	void RunGameLoop();
	void Deintialize();

private:

	bool Update(bool processInput = true);
	void Draw();

};