#pragma once
#include "GameState.h"

#include <vector>
#include <iostream>

enum loadFunction {
	PUSH = 0,
	CHANGE = 1,
	POP = 2,
	NOSTATE = 3,
	MENUSTATE = 4,
	PLAYSTATE = 5,
	PAUSESTATE = 6
};

class GameStateMachine
{
public:

	void update();
	void render();

	void loadStateChange(int State, int loadFunction);
	void updateState();
	
	
private:

	struct newState {		
		int state;
		int loadfunction;

		//constructor
		newState(int State, int loadFunction);
	};
	
	bool stateUpdateDue = false;

	GameState* createGameState(int State);

	void pushState(GameState* pState);
	void changeState(GameState* pState);
	void popState();

	std::vector<GameState*> m_gameStates;
	std::vector<newState*> m_stateChanges;
};
