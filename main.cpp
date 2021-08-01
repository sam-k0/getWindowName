
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>

#define GMEXPORT extern "C" __declspec(dllexport)

HWND resolveHandle(const char* _passedHandle)
{
    std::string hstr(_passedHandle);
    HWND parentHwnd = (HWND)std::stoull(hstr);

    return parentHwnd;
}



GMEXPORT int checkWindowName(const char* windowName) {
    // Checks if a window with a certain title exists

    // get handle to the searched window name
    HWND winHandle = FindWindow(NULL,windowName);
    // check if handle is null...
    if(winHandle == NULL)
    {
        return -1;
    }
    return 1;
}

GMEXPORT char* getWindowNameC() {
    // Shows the title of the currently focused window
    char title[500]; // get the
    GetWindowText(GetForegroundWindow(), title, 500);
    // typecast to char
    char* titleptr = title;
    return titleptr;
}

GMEXPORT int showMessageboxOk(const char* passedHandle, const char* headline, const char* bodytext)
{
    // Takes game maker window handle, headline, body text
    // returns whatever the msgbox id is.
    int msgboxID = MessageBox(
        resolveHandle(passedHandle),
        (LPCSTR)bodytext,
        (LPCSTR)headline,
        MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2
    );

    return msgboxID;
}


GMEXPORT int showMessageboxTest(const char* passedHandle)
{
    // Takes game maker window handle, headline, body text
    // returns whatever the msgbox id is.


    int msgboxID = MessageBox(
        resolveHandle(passedHandle),
        (LPCSTR)L"AAA",
        (LPCSTR)L"OWO",
        MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2
    );

    return msgboxID;
}

GMEXPORT int showMessageboxCTC(const char* passedHandle, const char* headline, const char* bodytext)
{
    // this will show a messagebox with a continue, try again and cancel button.
    int returnVal = 0; // Normalized button output value 0-2
    int msgboxID = MessageBox(
        resolveHandle(passedHandle),
        (LPCSTR)bodytext,
        (LPCSTR)headline,
        MB_ICONWARNING | MB_CANCELTRYCONTINUE | MB_DEFBUTTON2
    );

    switch (msgboxID)
    {
    case IDCANCEL:
        // TODO: add code
        returnVal = 0;
        break;
    case IDTRYAGAIN:
        // TODO: add code
        returnVal = 1;
        break;
    case IDCONTINUE:
        // TODO: add code
        returnVal = 2;
        break;
    }

    return returnVal;
}


GMEXPORT int showMessageboxYN(const char* passedHandle, const char* headline, const char* bodytext)
{   // shows a messagebox with yes and no button, returns 0 for no and 1 for yes
    int returnVal = 0;
    int msgboxID = MessageBox(
        resolveHandle(passedHandle),
        (LPCSTR)bodytext,
        (LPCSTR)headline,
        MB_ICONEXCLAMATION | MB_YESNO
    );

    if (msgboxID == IDYES)
    {
        // TODO: add code
        returnVal = 1;
    }

    return returnVal;
}

GMEXPORT int setWindowIcon(const char* passedHandle, const char* icopath)
{   // sets an icon to the game window. Returns 1 if success and <0 if not
    // Reference: http://www.cplusplus.com/forum/windows/188709/
    HWND handle = resolveHandle(passedHandle);

    HICON hWindowIcon=NULL;
    HICON hWindowIconBig=NULL;
    std::string stricon = icopath;

    // If icon exists, destroy it

    if(hWindowIcon!=NULL)
        DestroyIcon(hWindowIcon);
    if(hWindowIconBig!=NULL)
        DestroyIcon(hWindowIconBig);
    // set new
    if(stricon=="")
    {
        return -1; // Stricon is empty. return.
    }
    else
    {
        hWindowIcon =(HICON)LoadImage(NULL, stricon.c_str(), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
        hWindowIconBig =(HICON)LoadImage(NULL, stricon.c_str(), IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
        SendMessage( HWND(handle), WM_SETICON, ICON_SMALL, (LPARAM)hWindowIcon );
        SendMessage( HWND(handle), WM_SETICON, ICON_BIG, (LPARAM)hWindowIconBig );
    }
    return 1;
}

GMEXPORT int shellExec(const char* passedHandle, const char* lpOperation, const char* lpFile, const char* lpParameters, const char* lpDirectory, int nShowCmd)
{
    //Executes a shell command with parameters given.
    // https://docs.microsoft.com/en-us/windows/win32/api/shellapi/nf-shellapi-shellexecutea?redirectedfrom=MSDN
    ShellExecuteA(
                    resolveHandle(passedHandle),
                    (LPCSTR)lpOperation,
                    (LPCSTR)lpFile,
                    (LPCSTR)lpParameters,
                    (LPCSTR)lpDirectory,
                    (INT)nShowCmd
                  );
    return 1;
}

GMEXPORT int setFlashing(const char* passedHandle, int flashCount, int flashRateMillis)
{
    HWND hHandle = resolveHandle(passedHandle); // Set handle to passed handle
    FLASHWINFO pf;                     // instanciate a struct of type flash window info
    pf.cbSize = sizeof(FLASHWINFO);
    pf.hwnd = hHandle;
    pf.dwFlags = FLASHW_TIMER|FLASHW_TRAY; // (or FLASHW_ALL to flash and if it is not minimized)
    pf.uCount = flashCount;
    pf.dwTimeout = flashRateMillis;

    FlashWindowEx(&pf);
    return 1;
}

GMEXPORT int setFlashingDef(const char* windowName, int cnt, int rate)
{
    HWND hHandle = FindWindow(NULL,windowName); // Set handle to passed handle
    FLASHWINFO pf;                     // instanciate a struct of type flash window info
    pf.cbSize = sizeof(FLASHWINFO);
    pf.hwnd = hHandle;
    pf.dwFlags = FLASHW_TIMER|FLASHW_TRAY; // (or FLASHW_ALL to flash and if it is not minimized)
    pf.uCount = 8;
    pf.dwTimeout = 80;

    FlashWindowEx(&pf);
    return 1;
}


GMEXPORT int setFlashingT(const char* windowName)
{
    HWND hHandle = FindWindow(NULL,windowName); // Set handle to passed handle
    FLASHWINFO pf;                     // instanciate a struct of type flash window info
    pf.cbSize = sizeof(FLASHWINFO);
    pf.hwnd = hHandle;
    pf.dwFlags = FLASHW_TIMER|FLASHW_TRAY; // (or FLASHW_ALL to flash and if it is not minimized)
    pf.uCount = 8;
    pf.dwTimeout = 2000;

    FlashWindowEx(&pf);
    return 1;
}



