#include "pch.h"
#include "Input.h"
NAMESPACE_OPEN(GEngine)

Vector<Input::Key> Input::s_keys = {};

int ASCII[(uint32_t)KeyCode::End] =
{
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M',
	VK_LEFT, VK_RIGHT, VK_DOWN, VK_UP,
};

void Input::Init()
{
	for (auto i = 0; i < (size_t)KeyCode::End; ++i)
	{
		Key key
		{
			(KeyCode)i,
			KeyState::None,
			false
		};

		s_keys.push_back(key);
	}

}

void Input::Update()
{
	for (Key& key : s_keys)
	{
		// If the key is pressed now
		if (GetAsyncKeyState(ASCII[(int)key.keyCode]) & 0x8000)
		{
			// If the key was pressed at previous frame,
			if (key.pressed) key.state = KeyState::Pressed;
			// Otherwise
			else key.state = KeyState::Down;

			key.pressed = true;
		}
		else
		{
			if (key.pressed) key.state = KeyState::Up;
			else key.state = KeyState::None;

			key.pressed = false;
		}
	}
}

//bool Input::GetKeyDown(KeyCode key)
//{
//	return s_keys[(uint32_t)key].state == KeyState::Down;
//}
//
//bool Input::GetKeyUp(KeyCode key)
//{
//	return s_keys[(uint32_t)key].state == KeyState::Up;
//}
//
//bool Input::GetKey(KeyCode key)
//{
//	return s_keys[(uint32_t)key].state == KeyState::Pressed;
//}

bool Input::isKeyDown(KeyCode key)
{
	return GetAsyncKeyState(ASCII[(int)key]) & 0x8000;
}

void Input::updateKeys()
{
	for (Key& key : s_keys)
	{
		updateKey(key);
	}
}

void Input::updateKey(Key& key)
{
	// If the key is pressed now
	if (isKeyDown(key.keyCode))
	{
		updateKeyDown(key);
	}
	else
	{
		updateKeyUp(key);
	}
}

void Input::updateKeyUp(Key& key)
{
	// If the key was pressed at previous frame,
	if (key.pressed) key.state = KeyState::Pressed;
	// Otherwise
	else key.state = KeyState::Down;

	key.pressed = true;
}

void Input::updateKeyDown(Key& key)
{
	if (key.pressed) key.state = KeyState::Up;
	else key.state = KeyState::None;

	key.pressed = false;
}

NAMESPACE_CLOSE;