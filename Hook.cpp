#include <iostream>
#include <Windows.h>

using namespace std;

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
    {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;
        cout << "Key pressed: " << p->vkCode << endl;
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main()
{
    HHOOK hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);
    if (hookHandle == NULL)
    {
        cerr << "Failed to set keyboard hook" << endl;
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hookHandle);
    return 0;
}
