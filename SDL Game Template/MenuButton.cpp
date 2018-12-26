#pragma once
#include "MenuButton.h"
#include "InputManager.h"

MenuButton::MenuButton() :
	SDLGameObject()
{
	m_currentFrame = MOUSE_OUT; 
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::update() 
{
	Vector2D * pMousePos = InputManager::getInstance()->getMousePosition();

	if (pMousePos -> getX() < (m_position.getX() + m_width)
		&& pMousePos -> getX() > m_position.getX()
		&& pMousePos -> getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		m_currentFrame = MOUSE_OVER;

		if (InputManager::getInstance()->getMouseButtonState(LEFT)
			&& m_bReleased)
		{
			m_currentFrame = CLICKED;

			m_callback(); 

			m_bReleased = false;
		}
		else if (!InputManager::getInstance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::load(const LoaderParams *pParams)
{
	SDLGameObject::load(pParams);
	m_callBackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT;
}

void MenuButton::setCallback(void(*callback)())
{
	m_callback = callback;
}

int MenuButton::getCallbackID()
{
	return m_callBackID;
}