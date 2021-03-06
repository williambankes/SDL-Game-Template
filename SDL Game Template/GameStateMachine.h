#pragma once
#include "GameState.h"

#include <vector>
#include <iostream>


//Include new state enum's here:
enum loadFunction {
	//Loading functions:
	PUSH = 0,
	CHANGE = 1,
	POP = 2,

	//GameStates:
	NOSTATE = 3,
	MENUSTATE = 4,
	PLAYSTATE = 5,
	PAUSESTATE = 6,
	MAINMENU = 7,
	MULTISTATE = 8,
	GAMEOVERSTATE= 9
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
