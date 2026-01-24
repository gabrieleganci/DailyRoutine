#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdio> 

void ZoomTerminal(int times) {
    Sleep(300); // Aspetta che il terminale sia pronto
    
    for (int i = 0; i < times; i++) {
        // Simula Ctrl + + per zoommare
        keybd_event(VK_CONTROL, 0, 0, 0);
        keybd_event(VK_ADD, 0, 0, 0);  // Tasto + del numpad
        keybd_event(VK_ADD, 0, KEYEVENTF_KEYUP, 0);
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
        Sleep(100);
    }
}

void setupConsole() {
    HWND hwnd = GetConsoleWindow();
    MoveWindow(hwnd, 300, 300, 420, 420, TRUE);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 18;
    cfi.dwFontSize.Y = 24;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_BOLD;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void KeepWindowOnTop(HWND hwnd) {
    // lo rende topmost E lo attiva in primo piano
    SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
        SWP_NOMOVE | SWP_NOSIZE);
    SetForegroundWindow(hwnd); // prende il focus
}

void SnapToBottomLeft(HWND hwnd) {
    // Prima attiva la finestra
    SetForegroundWindow(hwnd);
    Sleep(200);
    
    // Simula Win + Freccia Sinistra per snap a sinistra
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event(VK_LEFT, 0, 0, 0);
    keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    
    Sleep(300);
    
    // Premi ESC per uscire dal menu di snap
    keybd_event(VK_ESCAPE, 0, 0, 0);
    keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
    
    Sleep(200);
    
    // Simula Win + Freccia Giù per snap in basso
    keybd_event(VK_LWIN, 0, 0, 0);
    keybd_event(VK_DOWN, 0, 0, 0);
    keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);
    
    Sleep(300);
    
    // Premi ESC finale per chiudere eventuali menu
    keybd_event(VK_ESCAPE, 0, 0, 0);
    keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HWND hwnd = GetConsoleWindow();
    KeepWindowOnTop(hwnd);
    setupConsole();
    
    // Snap la finestra in basso a sinistra
    SnapToBottomLeft(hwnd);
    ZoomTerminal(6); // Zoomma 4 volte
    // 🔥 Elimina eventuale file precedente
    std::remove("codess.txt");

    std::string codess;
    while (codess.length() < 6) {
        system("cls");
        std::cout << R"(
    ╔═══╦═══╦═══╗
    ║ 7 ║ 8 ║ 9 ║
    ╠═══╬═══╬═══╣
    ║ 4 ║ 5 ║ 6 ║
    ╠═══╬═══╬═══╣
    ║ 1 ║ 2 ║ 3 ║
    ╠═══╩═══╩═══╣
    ║     0     ║
    ╚═══════════╝
)" << std::endl;

        std::cout << "\nInsert a code:";
        char ch;
        std::cin >> ch;

        if (ch >= '0' && ch <= '9') {
            codess += ch;
        }
    }

    // 💾 Sovrascrive sempre con nuovo codice
    std::ofstream file("codess.txt", std::ios::trunc);
    file << codess;
    file.close();

    return 0; // chiusura automatica
}