// =====
// Please Read:
// This code is using windows.h
// You must add option to '-lgdi32'
// 
// Command:
//   ./run.bat "Create Window (Windows)" "-lgdi32"
// =====
#include <windows.h>

// 32bit: WPARAM wParam -> UINT wParam
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
    }
    return DefWindowProcA(hwnd, msg, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, char*, int) { // hInstance: handle id
    char CLASS_NAME[10] = "MY_WINDOW"; // class name required
    WNDCLASSEXA win = {0};
    win.cbSize = sizeof(win);
    win.style = CS_HREDRAW | CS_VREDRAW; // styles
    win.hInstance = hInstance;
    win.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1); // before background color
    win.lpszClassName = CLASS_NAME;
    win.lpfnWndProc = WndProc; // Message Process
    RegisterClassExA(&win);

    HWND hwnd;
    hwnd = CreateWindowA(
        CLASS_NAME, "My title", // Class Name and Window Title
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, // x, y
        500, 500, // width, height
        0, 0, hInstance, 0
    );
    ShowWindow(hwnd, 1);

    MSG msg;
    while (GetMessageA(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return 0;
}