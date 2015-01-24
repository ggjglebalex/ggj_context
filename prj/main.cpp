#define WIN32_LEAN_AND_MEAN           
#include <windows.h>

#include <tchar.h>

// C RunTime Header Files
#include "platform/CCStdC.h"
#include "platform/CCPlatformMacros.h"
#include "platform/CCPlatformDefine.h"

#include "appdelegate.h"

//--------------------------------------------------------------

USING_NS_CC;

//--------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    AppDelegate app;
    return Application::getInstance()->run();
}

//--------------------------------------------------------------
