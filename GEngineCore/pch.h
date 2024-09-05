// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H


#define G_ENGINE_CORE_EXPORTS
#define NOMINMAX


// add headers that you want to pre-compile here
#include "framework.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <winnt.h>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <typeindex>
#include <typeinfo>



#include "CoreMacro.h"
#include "concepts.h"
#include "Types.h"


/*********** Types ****************/
#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector2Int.h"
#include "Vector4.h"
#include "Rect.h"

/*********** Core ****************/
#include "GTime.h"
#include "Input.h"
#include "Object.h"
#include "GameObject.h"
#include "Layer.h"

//#include "Component.h"
//#include "Transform.h"
//
//#include "Scene.h"
//#include "Scene2D.h"
//#include "SceneManager.h"


//#include "Collector.h"


#endif //PCH_H
