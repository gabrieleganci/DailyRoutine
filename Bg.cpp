// Eyes (Bg.cpp) - MSVC on Windows
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

// --- Kill mother when Eyes closes ---
BOOL WINAPI ConsoleHandler(DWORD signal) {
    if (signal == CTRL_CLOSE_EVENT || signal == CTRL_C_EVENT) {
        HWND hwndMotherToKill = FindWindowA(NULL, "DailyRoutine.exe");
        if (hwndMotherToKill && IsWindow(hwndMotherToKill)) {
            DWORD pid = 0;
            GetWindowThreadProcessId(hwndMotherToKill, &pid);
            if (pid) {
                HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
                if (hProcess) {
                    TerminateProcess(hProcess, 0);
                    CloseHandle(hProcess);
                }
            }
        }
    }
    return TRUE;
}

// --- Lock window resizing (call after snap) ---
void LockConsoleWindowSize() {
    HWND hwnd = GetConsoleWindow();
    if (!hwnd) return;
    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
    style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
    SetWindowLongPtr(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

// --- Snap left with Win+Left and refocus DailyRoutine ---
class WindowSnapper {
public:
    static void SnapCurrentWindowLeftAndRefocusMother() {
        HWND hwndEyes = GetConsoleWindow();
        HWND hwndMother = FindWindowA(NULL, "DailyRoutine.exe");
        if (!hwndEyes) return;

        ShowWindow(hwndEyes, SW_SHOW);
        Sleep(160);
        BringWindowToTop(hwndEyes);
        SetForegroundWindow(hwndEyes);
        SetFocus(hwndEyes);

        // Win + Left
        keybd_event(VK_LWIN, 0, 0, 0);
        Sleep(40);
        keybd_event(VK_LEFT, 0, 0, 0);
        Sleep(40);
        keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
        Sleep(40);
        keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);

        Sleep(200);

        // Refocus mother
        if (hwndMother && IsWindow(hwndMother)) {
            SetForegroundWindow(hwndMother);
            SetFocus(hwndMother);
        }
    }
};

// --- Viewer: load file and apply zoom/scroll on Eyes ---
class AsciiViewer {
private:
    std::string ultimoComando;
    bool windowSnapped = false;

    void impostaZoom(int percentuale) {
        HWND hwndEyes = GetConsoleWindow();
        if (!hwndEyes || !IsWindow(hwndEyes)) return;

        HWND originalFocusWindow = GetForegroundWindow();

        // Fresh geometry each run
        RECT rect;
        GetWindowRect(hwndEyes, &rect);
        int left   = rect.left;
        int top    = rect.top;
        int width  = rect.right  - rect.left;
        int height = rect.bottom - rect.top;

        // Focus Eyes
        SetForegroundWindow(hwndEyes);
        SetFocus(hwndEyes);
        Sleep(200);

        // Reset zoom
        keybd_event(VK_CONTROL, 0, 0, 0);
        Sleep(50);
        keybd_event('0', 0, 0, 0);
        Sleep(50);
        keybd_event('0', 0, KEYEVENTF_KEYUP, 0);
        Sleep(50);
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
        Sleep(200);

        // Restore position
        SetWindowPos(hwndEyes, NULL, left, top, width, height,
                     SWP_NOZORDER | SWP_NOACTIVATE);
        Sleep(100);

        // Zoom steps
        int diff = percentuale - 100;
        int numScroll = diff / 10;
        if (numScroll != 0) {
            keybd_event(VK_CONTROL, 0, 0, 0);
            Sleep(80);

            for (int i = 0; i < abs(numScroll); ++i) {
                INPUT in = {};
                in.type = INPUT_MOUSE;
                in.mi.dwFlags = MOUSEEVENTF_WHEEL;
                in.mi.mouseData = (numScroll > 0) ? WHEEL_DELTA : -WHEEL_DELTA;
                SendInput(1, &in, sizeof(in));
                Sleep(100);

                SetWindowPos(hwndEyes, NULL, left, top, width, height,
                             SWP_NOZORDER | SWP_NOACTIVATE);
            }

            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
            Sleep(150);
        }

        // Final restore
        SetWindowPos(hwndEyes, NULL, left, top, width, height,
                     SWP_NOZORDER | SWP_NOACTIVATE);

        // Scroll up 20 times
        for (int i = 0; i < 20; ++i) {
            INPUT in = {};
            in.type = INPUT_MOUSE;
            in.mi.dwFlags = MOUSEEVENTF_WHEEL;
            in.mi.mouseData = WHEEL_DELTA;
            SendInput(1, &in, sizeof(in));
            Sleep(40);
        }

        // Hide cursor
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coord = {0, 0};
        SetConsoleCursorPosition(hConsole, coord);
        CONSOLE_CURSOR_INFO ci;
        if (GetConsoleCursorInfo(hConsole, &ci)) {
            ci.bVisible = FALSE;
            SetConsoleCursorInfo(hConsole, &ci);
        }

        // Restore original focus
        if (originalFocusWindow && IsWindow(originalFocusWindow)) {
            SetForegroundWindow(originalFocusWindow);
            SetFocus(originalFocusWindow);
        }
    }

    void caricaEMostra(const std::string& nomeFile, int zoom = 100) {
        system("cls");
        std::ifstream file("bgs/" + nomeFile + ".txt");
        if (file) {
            std::string linea;
            while (std::getline(file, linea)) {
                std::cout << linea << std::endl;
            }
        }

        // Hide cursor before zoom
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE) {
            CONSOLE_CURSOR_INFO cursorInfo = {};
            if (GetConsoleCursorInfo(hConsole, &cursorInfo)) {
                cursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(hConsole, &cursorInfo);
            }
            COORD coord = {0, 0};
            SetConsoleCursorPosition(hConsole, coord);
        }

        if (zoom != 100) {
            impostaZoom(zoom);
        }
    }

public:
    void avvia() {
        std::cout << "*\n";

        if (!windowSnapped) {
            WindowSnapper::SnapCurrentWindowLeftAndRefocusMother();
            LockConsoleWindowSize();
            windowSnapped = true;
        }

        const fs::path cmdPath = "ascii_command.txt";

        while (true) {
            HWND hwndMother = FindWindowA(NULL, "DailyRoutine.exe");
            if (hwndMother == NULL || !IsWindow(hwndMother)) {
                exit(0);
            }

            std::error_code ec;
            if (fs::exists(cmdPath, ec) && !ec) {
                std::ifstream file(cmdPath);
                std::string comando;
                std::getline(file, comando);
                file.close();

                if (!comando.empty() && comando != ultimoComando) {
                    std::string nomeFile = comando;
                    int zoom = 100;
                    size_t pos = comando.find(';');
                    if (pos != std::string::npos) {
                        nomeFile = comando.substr(0, pos);
                        std::string zoomStr = comando.substr(pos + 1);
                        try { zoom = std::stoi(zoomStr); } catch (...) { zoom = 100; }
                    }

                    caricaEMostra(nomeFile, zoom);
                    ultimoComando = comando;

                    std::ofstream clear(cmdPath.string(), std::ios::trunc);
                    clear.close();
                }
            }
            Sleep(100);
        }
    }
};

int main() {
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);
    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SetConsoleTitleA("Eyes");

    Sleep(200);

    AsciiViewer viewer;
    viewer.avvia();
    return 0;
}
