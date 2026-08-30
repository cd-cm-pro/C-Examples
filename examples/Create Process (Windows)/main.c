#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    SECURITY_ATTRIBUTES sa = {
        .nLength = sizeof(SECURITY_ATTRIBUTES),
        .lpSecurityDescriptor = NULL,
        .bInheritHandle = TRUE
    };

    HANDLE hread;
    HANDLE hwrite;
    WINBOOL create_pipe_result = CreatePipe(&hread, &hwrite, &sa, 0); // create pipe
    if (!create_pipe_result) {
        printf("CreatePipe failed: %lu\n", GetLastError());
        return 1;
    }
    SetHandleInformation(hread, HANDLE_FLAG_INHERIT, 0);

    STARTUPINFOA si = {0};
    PROCESS_INFORMATION pi = {0};
    si.cb = sizeof(si);

    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = hwrite;
    si.hStdError = hwrite;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

    char command[] = "cmd.exe /c \"node -v\""; // command
    BOOL result = CreateProcessA( // Create process
        NULL, command,
        NULL, NULL,
        TRUE, CREATE_NO_WINDOW,
        NULL, NULL, &si, &pi
    );
    if (!result) {
        printf("CreateProcess failed: %lu\n", GetLastError());
        CloseHandle(hread);
        CloseHandle(hwrite);
        return 1;
    }

    CloseHandle(hwrite);

    char buffer[128]; // stdout, stderr
    DWORD b_read;

    while (ReadFile(hread, buffer, sizeof(buffer)-1, &b_read, NULL)) {
        if (b_read == 0) break;
        buffer[b_read] = '\0';
    }
    CloseHandle(hread);

    DWORD exit_code;
    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &exit_code);

    if (exit_code != 0) {
        printf("Node.js not installed.\n");
    } else {
        char filtered_buf[128];
        int len = strlen(buffer);
        int j = 0;
        for (int i = 0; i < len; i++) {
            char ch = buffer[i];
            if (ch == '\n') {
                filtered_buf[j] = 0;
            } else if (ch == 'v') {
                continue;
            } else {
                filtered_buf[j] = ch;
            }
            j++;
        }
        printf("Version: %s\n", filtered_buf);
    }

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    return 0;
}