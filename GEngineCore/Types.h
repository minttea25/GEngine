#pragma once

#include <string>
#include <map>
#include <functional>
#include <vector>


namespace GEngine
{
	// TODO
	// warning C4251
	// STL container needs to have dll-interface to be used by clients of class ~

	using String = std::wstring;

	template<typename _Kty, typename _Ty>
	using Map = std::map<_Kty, _Ty>;

	template<typename _Ty>
	using Vector = std::vector<_Ty>;


	template<typename T>
	using Delegate = std::function<void(T)>;

	template<typename T0, typename T1>
	using Delegate2 = std::function<void(T0, T1)>;
}
