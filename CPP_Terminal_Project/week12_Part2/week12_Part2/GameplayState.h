#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include <windows.h>
#include <Vector>
#include <string>

class StateMachineExampleGame;

class GameplayState : public GameState
{

	StateMachineExampleGame* m_pOwner;

	Player m_player;
	Level* m_pLevel;

	bool m_beatLevel;
	int m_skipFrameCount;
	static constexpr int kFrameToSkip = 2;

	int m_currenLevel;
	std::vector<std::string> m_LevelNames;

public:
	GameplayState(StateMachineExampleGame* m_pOwner);
	~GameplayState();
	virtual void Enter() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;

private:
	bool Load();
	void HandleCollision(int newPlayerX, int newPlayerY);
	void DrawHUD(const HANDLE& console);
};

