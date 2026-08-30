// =====
// Please Read:
// This code is using windows.h
// You must add option to '-lgdi32'
// 
// Command:
//   ./run.bat "Window Create & Use Controls (commctrl.h) (Windows)" "-lgdi32"
// =====
//
// Reference: https://learn.microsoft.com/ko-kr/windows/win32/controls/window-controls
//
#include <windows.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define ID_STATIC_TEXT 1001
#define ID_BUTTON 1002
HFONT font;

void CreateControl(LPCSTR class_name, LPCSTR text, DWORD dwStyle, int x, int y, int w, int h, HWND hwnd, HMENU hMenu, HINSTANCE hInstance) {
    HWND control = CreateWindowExA(
        0, class_name, 
        text,
        dwStyle,
        x, y, w, h, hwnd,
        hMenu, hInstance, NULL
    );
    SendMessageA(control, WM_SETFONT, (WPARAM)font, TRUE);
}

// 32bit: WPARAM wParam -> UINT wParam
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            HDC hdc = GetDC(hwnd);
            LPCREATESTRUCTA pcs = (LPCREATESTRUCTA)lParam;

            // Static Text
            char text[12] = "Static Text";

            HFONT oldFont = (HFONT)SelectObject(hdc, font);
            SIZE static_text_size;
            GetTextExtentPoint32A(hdc, text, lstrlenA(text), &static_text_size);

            SelectObject(hdc, oldFont);
            ReleaseDC(hwnd, hdc);

            // Button
            int button_x = 25 + 10 + static_text_size.cx;
            int button_height = 40;

            CreateControl(
                WC_STATICA, text, 
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                25, 25 + button_height / 2 - static_text_size.cy / 2, static_text_size.cx, static_text_size.cy, hwnd,
                (HMENU)ID_STATIC_TEXT, pcs->hInstance
            );
            CreateControl(
                WC_BUTTONA, "Button",
                WS_CHILD | WS_VISIBLE,
                button_x, 25, 100, button_height, hwnd,
                (HMENU)ID_BUTTON, pcs->hInstance
            );

            break;
        }

        case WM_COMMAND: {
            if (wParam == ID_BUTTON) {
                MessageBoxA(hwnd, "You clicked a button", "title", MB_ICONINFORMATION);
            }
            break;
        }
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

    font = CreateFontA(
        21, 0, 0, 0,
        FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY,
        DEFAULT_PITCH,
        "segoe ui"
    );

    HWND hwnd;
    hwnd = CreateWindowA(
        CLASS_NAME, "My title", // Class Name and Window Title
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, // x, y
        300, 40 + 25 + 25 + 40, // width, height
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