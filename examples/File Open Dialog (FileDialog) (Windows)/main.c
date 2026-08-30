// =====
// Please Read:
// This code is using windows.h
// You must add option to '-lcomdlg32'
// 
// Command:
//   ./run.bat "File Open Dialog (FileDialog) (Windows)" "-lcomdlg32"
// =====
#include <stdio.h>
#include <windows.h>

int main(void) {
    OPENFILENAMEA openfile = {0};
    char f_path[MAX_PATH] = "";
    openfile.lStructSize = sizeof(openfile);
    openfile.hwndOwner = NULL;
    openfile.lpstrFile = f_path;
    openfile.nMaxFile = sizeof(f_path);
    openfile.lpstrFilter = 
        "All File\0*.*\0"
        "C File\0*.c\0"
        "C++ File\0*.cpp\0"
        "Dart File\0*.dart\0"
        "Go File\0*.go\0"
        "Haskell File\0*.hs\0"
        "Java File\0*.java\0"
        "JavaScript File\0*.js\0"
        "Kotlin File\0*.kt\0"
        "Lua File\0*.lua\0"
        "Perl File\0*.pl\0"
        "PHP File\0*.php\0"
        "Python File\0*.py\0"
        "R File\0*.r\0"
        "Ruby File\0*.rb\0"
        "Rust File\0*.rs\0"
        "Swift File\0*.swift\0"
        "TypeScript File\0*.ts\0"
        "Visual Basic File\0*.vb\0"
        "Zig File\0*.zig\0";
    openfile.nFilterIndex = 1;
    openfile.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
    
    if (!GetOpenFileNameA(&openfile)) {
        printf("Select Canceled\n");
        return 1;
    }
    printf("Selected File: %s\n", f_path);
    return 0;
}