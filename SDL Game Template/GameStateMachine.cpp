#include "GameStateMachine.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MainMenuState.h"
#include "MultiState.h"
#include "GameOverState.h"

void GameStateMachine::pushState(GameState* pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::changeState(GameState* pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
		{
			//Do nothing as the states are the same
			return; 
		}

		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}	
	//push back our new state
	m_gameStates.push_back(pState);

	//initialise it
	m_gameStates.back()->onEnter();
}

GameStateMachine::newState::newState(int State, int loadFunction):
	state(State), loadfunction(loadFunction) {}

void GameStateMachine::loadStateChange(int State, int loadFunction)
{
	m_stateChanges.push_back(new newState(State, loadFunction));
	
	if (!stateUpdateDue)
	{
		stateUpdateDue = true;
	}
}

//Include new States Here:
GameState* GameStateMachine::createGameState(int State)
{
	switch (State)
	{
	case PLAYSTATE:
		return new PlayState;
		break;
		
	case MENUSTATE:
		return new MainMenuState;
		break;
		
	case PAUSESTATE:
		return new PauseState;
		break;
		//State cases go here:

	case MAINMENU:
		return new MainMenuState;
		break;

	case MULTISTATE:
		return new MultiState;
		break;

	case GAMEOVERSTATE:
		return new GameOverState;
		break;


	default:
		return new MainMenuState;
		break;
	}
}

void GameStateMachine::updateState()
{
	if (stateUpdateDue)
	{
		for (int i = 0; i < m_stateChanges.size(); i++)
		{
			switch (m_stateChanges[i]->loadfunction)
			{
			case PUSH:
				pushState(createGameState(m_stateChanges[i]->state));
				break;
			case CHANGE:
				changeState(createGameState(m_stateChanges[i]->state));
				break;
			case POP:
				popState();
				break;
			}
		}


		m_stateChanges.clear();
		stateUpdateDue = false;
	}
}


void GameStateMachine::update() {
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}
}

void GameStateMachine::render() {
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}

	updateState();
}


