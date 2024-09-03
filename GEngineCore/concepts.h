#pragma once

#include <iostream>

namespace GEngine
{

	template<typename T>
	concept Object_t = std::is_base_of_v<class Object, T>;

	template<typename T>
	concept Component_t = std::is_base_of_v<class Component, T>;

	template<typename T>
	concept Scene_t = std::is_base_of_v<class Scene, T>;
}