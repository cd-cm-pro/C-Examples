// =====
// Please Read:
// This code is using mmsystem.h
// You must add option to '-lwinmm'
//
// Command:
//   ./run.bat "Play Sound (Windows)" "-lwinmm"
// =====
#include <windows.h>
#include <mmsystem.h>

int main(void) {
    mciSendStringA(
        "open \"files/vibe-boom.mp3\" type mpegvideo alias music",
        NULL,
        0,
        NULL
    );

    mciSendStringA(
        "play music wait",
        NULL,
        0,
        NULL
    );

    mciSendStringA(
        "close music",
        NULL,
        0,
        NULL
    );
    return 0;
}