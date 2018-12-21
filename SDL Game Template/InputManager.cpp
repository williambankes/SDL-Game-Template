#include "InputManager.h"

//handle keyboard events:
void InputManager::onKeyDown() {
	m_keystates = SDL_GetKeyboardState(0);
}
void InputManager::onKeyUp() {
	m_keystates = SDL_GetKeyboardState(0);
}

//handle mouse events:
void InputManager::onMouseMove(SDL_Event& event) {
	m_mousePosition->setX(event.motion.x);
	m_mousePosition->setY(event.motion.y);
}

void InputManager::onMouseButtonDown(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}

	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}

	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}
}

void InputManager::onMouseButtonUp(SDL_Event& event) {
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}


//Check input States:

bool InputManager::getMouseButtonState(int buttonNumber)
{
	return m_mouseButtonStates[buttonNumber];
}

bool InputManager::isKeyDown(SDL_Scancode key)
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return false;
}

Vector2D* InputManager::getMousePosition() 
{
	return m_mousePosition;
}

void InputManager::update() {
	
	SDL_Event event;

	//Event loop:
	while (SDL_PollEvent(&event))
	{

		switch (event.type)
		{
		case SDL_QUIT:
			m_brunning = false;
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;

		default:
			break;

		}
	}
}

void InputManager::clean() {
	std::cout << "cleaning Input Handler" << std::endl;
}

bool InputManager::getRunning() {
	return m_brunning;
}

void InputManager::reset()
{
	for (int i = 0; i < m_mouseButtonStates.size(); i++)
	{
		m_mouseButtonStates[i] = false;
	}
}


//Singleton Implementation:

InputManager* InputManager::s_pInstance = 0;

InputManager::InputManager() {

	m_mousePosition = new Vector2D(0,0);

	//Handling mouse events:
	for (int i = 0; i < 3; i++) {
		m_mouseButtonStates.push_back(false);
	}
}

InputManager* InputManager::getInstance() {
	if (s_pInstance == 0)
	{
		s_pInstance = new InputManager();
		return s_pInstance;
	}

	return s_pInstance;
}

