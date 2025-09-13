#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdio> // per remove()

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

int main() {
    HWND hwnd = GetConsoleWindow();
    KeepWindowOnTop(hwnd);
    setupConsole();

    // 🔥 Elimina eventuale file precedente
    std::remove("codess.txt");

    std::string codess;
    while (codess.length() < 4) {
        system("cls");
        std::cout << "Codice inserito: " << codess << "\n\n";
        std::cout << R"(
 [7] [8] [9]
 [4] [5] [6]
 [1] [2] [3]
     [0]
)" << std::endl;

        std::cout << "\nDigita un numero (0-9): ";
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
