#pragma once

// Client 2D에 필요한 기능을 모아둠
#include "Engine.h"
#include "resource.h"

// Engine의 lib파일을 참조함
#ifdef _DEBUG

#pragma comment(lib, "AR41Engine_Debug.lib")

#else

#pragma comment(lib, "AR41Engine.lib")

#endif // _DEBUG
