// =====
// Please Read:
// This code is using windows.h
// You must add option to '-lgdi32'
// 
// Command:
//   ./run.bat "Window Create & Add Menu (CreateMenu) (Windows)" "-lgdi32"
// =====
#include <windows.h>

#define MENU_TEST1 1001
#define MENU_TEST2 1002
#define MENU_TEST2_TEST1 1003
#define MENU_TEST2_TEST2 1004
#define MENU_TEST2_TEST3 1005
#define MENU_TEST3 1006

HMENU test1_menu;
HMENU test3_menu;

// 32bit: WPARAM wParam -> UINT wParam
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_INITMENUPOPUP: {
            HMENU clickedMenu = (HMENU)wParam;
            
            if (clickedMenu == test1_menu) {
                MessageBoxA(hwnd, "You are clicked a 'Test 1' Menu", "Message", MB_OK);
            } else if (clickedMenu == test3_menu) {
                MessageBoxA(hwnd, "You are clicked a 'Test 3' Menu", "Message", MB_OK);
            }
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case MENU_TEST2_TEST1:
                    MessageBoxA(hwnd, "You are clicked a 'Test 1' in 'Test 2' Menu", "Message", MB_OK);
                    break;
                case MENU_TEST2_TEST2:
                    MessageBoxA(hwnd, "You are clicked a 'Test 2' in 'Test 2' Menu", "Message", MB_OK);
                    break;
                case MENU_TEST2_TEST3:
                    MessageBoxA(hwnd, "You are clicked a 'Test 3' in 'Test 2' Menu", "Message", MB_OK);
                    break;
                
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

    HMENU menu_bar = CreateMenu();
    
    test1_menu = CreatePopupMenu();
    HMENU test2_menu = CreatePopupMenu();
    test3_menu = CreatePopupMenu();

    AppendMenuA(test2_menu, MF_STRING, MENU_TEST2_TEST1, "Test 1");
    AppendMenuA(test2_menu, MF_SEPARATOR, 0, NULL); // this is a separator
    AppendMenuA(test2_menu, MF_STRING, MENU_TEST2_TEST2, "Test 2");
    AppendMenuA(test2_menu, MF_STRING, MENU_TEST2_TEST3, "Test 3");

    AppendMenuA(menu_bar, MF_POPUP, (UINT_PTR)test1_menu, "Test 1");
    AppendMenuA(menu_bar, MF_POPUP, (UINT_PTR)test2_menu, "Test 2");
    AppendMenuA(menu_bar, MF_POPUP, (UINT_PTR)test3_menu, "Test 3");

    HWND hwnd;
    hwnd = CreateWindowA(
        CLASS_NAME, "My title", // Class Name and Window Title
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, // x, y
        500, 500, // width, height
        0,
        menu_bar, // <-- HMENU
        hInstance, 0
    );
    ShowWindow(hwnd, 1);

    MSG msg;
    while (GetMessageA(&msg, 0, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return 0;
}