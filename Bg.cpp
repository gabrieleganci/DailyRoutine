#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <vector>
#include <sstream>
using namespace std;
namespace fs = std::filesystem;

bool EnableVTMode()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
    {
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode))
    {
        return false;
    }
    return true;
}

void ScrollToTop() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hConsole, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hConsole, dwMode);

    std::cout << "\x1b[H";
    std::cout.flush();
}

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

void LockConsoleWindowSize() {
    HWND hwnd = GetConsoleWindow();
    if (!hwnd) return;
    
    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);
    style &= ~(WS_THICKFRAME | WS_MAXIMIZEBOX);
    SetWindowLongPtr(hwnd, GWL_STYLE, style);
    SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}

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
        
        keybd_event(VK_LWIN, 0, 0, 0);
        Sleep(40);
        keybd_event(VK_LEFT, 0, 0, 0);
        Sleep(40);
        keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
        Sleep(40);
        keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
        Sleep(200);
        
        if (hwndMother && IsWindow(hwndMother)) {
            SetForegroundWindow(hwndMother);
            SetFocus(hwndMother);
        }
    }
};

// --- Funzione per cambiare i colori ---
void cambiaColoreSfondo(int coloreSfondo, int coloreTesto) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    int attributoColore = (coloreSfondo << 4) | coloreTesto;
    SetConsoleTextAttribute(console, attributoColore);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(console, &csbi);
    DWORD scritto;
    DWORD dimensioneConsole = csbi.dwSize.X * csbi.dwSize.Y;
    COORD homeCoords = {0, 0};
    FillConsoleOutputAttribute(console, attributoColore, dimensioneConsole, homeCoords, &scritto);
    FillConsoleOutputCharacter(console, ' ', dimensioneConsole, homeCoords, &scritto);
}

class AsciiViewer {
private:
    std::string ultimoComando;
    bool windowSnapped = false;

    void impostaZoom(int percentuale) {
        HWND hwndEyes = GetConsoleWindow();
        if (!hwndEyes || !IsWindow(hwndEyes)) return;

        HWND originalFocusWindow = GetForegroundWindow();

        SetForegroundWindow(hwndEyes);
        SetFocus(hwndEyes);
        Sleep(200);

        keybd_event(VK_CONTROL, 0, 0, 0);
        Sleep(50);
        keybd_event('0', 0, 0, 0);
        Sleep(50);
        keybd_event('0', 0, KEYEVENTF_KEYUP, 0);
        Sleep(50);
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
        Sleep(200);

        int diff = percentuale - 100;
        int numSteps = diff / 10;
        if (numSteps != 0) {
            keybd_event(VK_CONTROL, 0, 0, 0);
            Sleep(60);
            bool zoomIn = (numSteps > 0);
            int steps = abs(numSteps);
            WORD vkKey = zoomIn ? VK_OEM_PLUS : VK_OEM_MINUS;
            for (int i = 0; i < steps; ++i) {
                keybd_event(vkKey, 0, 0, 0);
                Sleep(40);
                keybd_event(vkKey, 0, KEYEVENTF_KEYUP, 0);
                Sleep(120);
            }
            keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
        }

        if (originalFocusWindow && IsWindow(originalFocusWindow)) {
            SetForegroundWindow(originalFocusWindow);
            SetFocus(originalFocusWindow);
        }
    }

    void caricaEMostra(const std::string& nomeFile, int zoom = 100, int coloreBg = -1, int coloreFg = -1) {
        // Pulisci schermo
        system("cls");

        // Cambia zoom PRIMA di stampare
        if (zoom != 100) {
            impostaZoom(zoom);
        }

        // Cambia colori SE specificati
        if (coloreBg >= 0 && coloreFg >= 0) {
            cambiaColoreSfondo(coloreBg, coloreFg);
        }

        // Leggi file
        std::ifstream file("bgs/" + nomeFile + ".txt");
        if (!file) return;

        std::vector<std::string> righe;
        std::string linea;
        while (std::getline(file, linea)) {
            righe.push_back(linea);
        }


        // Riposiziona cursore in alto
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hConsole != INVALID_HANDLE_VALUE) {
            COORD topLeft = {0,0};
            SetConsoleCursorPosition(hConsole, topLeft);
        }

        // Stampa tutto dall'inizio
        for (const auto& r : righe) {
            std::cout << r << "\n";
        }

        // Nascondi cursore
        if (hConsole != INVALID_HANDLE_VALUE) {
            CONSOLE_CURSOR_INFO cursorInfo;
            if (GetConsoleCursorInfo(hConsole, &cursorInfo)) {
                cursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(hConsole, &cursorInfo);
            }
        }
    }

public:
    void avvia() {
        cout<<"\n*";
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
                    // Parsing: nomeFile;zoom;coloreBg;coloreFg
                    std::string nomeFile = comando;
                    int zoom = 100;
                    int coloreBg = -1;
                    int coloreFg = -1;

                    std::stringstream ss(comando);
                    std::string token;
                    std::vector<std::string> tokens;
                    
                    while (std::getline(ss, token, ';')) {
                        tokens.push_back(token);
                    }

                    if (tokens.size() >= 1) {
                        nomeFile = tokens[0];
                    }
                    if (tokens.size() >= 2) {
                        try {
                            zoom = std::stoi(tokens[1]);
                        } catch (...) {
                            zoom = 100;
                        }
                    }
                    if (tokens.size() >= 3) {
                        try {
                            coloreBg = std::stoi(tokens[2]);
                        } catch (...) {
                            coloreBg = -1;
                        }
                    }
                    if (tokens.size() >= 4) {
                        try {
                            coloreFg = std::stoi(tokens[3]);
                        } catch (...) {
                            coloreFg = -1;
                        }
                    }

                    caricaEMostra(nomeFile, zoom, coloreBg, coloreFg);
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
    bool fSuccess = EnableVTMode();
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
