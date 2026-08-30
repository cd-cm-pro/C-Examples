// =====
// Please Read:
// This code is using windows.h
// You must add option to '-lgdi32'
// 
// Command:
//   ./run.bat "Window Create & WM_PAINT Use (Windows)" "-lgdi32"
// =====
#include <windows.h>

// 32bit: WPARAM wParam -> UINT wParam
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps); // begin paint

            // Draw Line
            MoveToEx(hdc, 50, 50, NULL);
            LineTo(hdc, 60, 180);

            // Many Lines
            POINT points1[] = {
                {70, 50},
                {80, 90},
                {95, 55},
                {110, 90},
            };
            // 4 is point item count
            Polyline(hdc, points1, 4);

            // Rectangle
            // HDC, x1, y1, x2, y2
            Rectangle(hdc, 70, 100, 70 + 50, 100 + 50);

            // RoundRect
            // HDC, x1, y1, x2, y2, Round Width Size, Round Height Size
            RoundRect(hdc, 70, 160, 70 + 50, 160 + 50, 10, 10);

            // Circle
            // HDC, x1, y1, x2, y2
            Ellipse(hdc, 70, 220, 70 + 50, 220 + 50);

            // Arc
            // HDC, x1, y1, x2, y2, x3, y3, x4, y4
            Arc(hdc, 70, 280, 70 + 50, 280 + 50, 70, 280 + 25, 70 + 50, 280 + 25);

            // Pie
            // HDC, x1, y1, x2, y2, x3, y3, x4, y4
            Pie(hdc, 70, 340, 70 + 50, 340 + 50, 70, 340 + 25, 70 + 50, 340 + 25);

            // Polygon
            POINT points2[] = {
                {130 + 25, 100},
                {130, 100 + 50},
                {130 + 50, 100 + 50}
            };
            // 3 is point item count
            Polygon(hdc, points2, 3);

            // FillRect
            RECT rect1 = {
                130, 160,
                130 + 50, 160 + 50
            };
            HBRUSH brush1 = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &rect1, brush1);
            DeleteObject(brush1);
            
            // FrameRect
            RECT rect2 = {
                130, 220,
                130 + 50, 220 + 50
            };
            HBRUSH brush2 = CreateSolidBrush(RGB(0, 0, 0));
            FrameRect(hdc, &rect2, brush2);
            DeleteObject(brush2);
            
            // Apply Color
            RECT rect3 = {
                130, 280,
                130 + 50, 280 + 50
            };
            HBRUSH brush3 = CreateSolidBrush(RGB(255, 0, 0)); // color
            FillRect(hdc, &rect3, brush3);
            DeleteObject(brush3);

            // Draw Text
            char text1[6] = "Hello";
            TextOutA(hdc, 130, 340, text1, lstrlen(text1));

            // Draw Text (Styled)
            HFONT hfont = CreateFontA(
                21, // Font size (height)
                0, // Font Width
                0, // Rotate
                0, // Charactor Rotate
                FW_NORMAL, // Font Weight (FW_BOLD is bold)
                FALSE, // Italic
                FALSE, // underline
                FALSE, // Strokeline
                DEFAULT_CHARSET, // Charset
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                CLEARTYPE_QUALITY, // Quality
                DEFAULT_PITCH | FF_DONTCARE,
                "Arial" // Font name
            );
            HFONT holdfont = (HFONT)SelectObject(hdc, hfont); // Apply Font
            SetTextColor(hdc, RGB(0, 0, 255)); // Text Color
            SetBkMode(hdc, TRANSPARENT); // Transparent
            // If you Add Background color
            // , you should this code:
            // SetBkMode(hdc, OPAQUE);
            // SetBkColor(hdc, RGB(255, 0, 0)); // Background color
            char text2[6] = "World";
            TextOutA(hdc, 190, 100, text2, lstrlen(text2));

            EndPaint(hwnd, &ps); // end paint
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