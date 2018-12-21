#pragma once
#include "Vector.h"
#include "SDL.h"

#include <vector>

enum mouse_buttons {
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputManager
{
public:
	static InputManager* getInstance();

	//handle keyboard events:
	void onKeyDown();
	void onKeyUp();

	//handle mouse events:
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	//Check input states:
	bool getMouseButtonState(int buttonNumber);
	bool isKeyDown(SDL_Scancode key);
	Vector2D* getMousePosition();

	bool getRunning();
	
	void update();
	void clean();
	void reset();
	
private:

	bool m_brunning = true;

	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;
	const Uint8* m_keystates;

	//Singleton Implementation:
	InputManager();
	static InputManager* s_pInstance;
};

