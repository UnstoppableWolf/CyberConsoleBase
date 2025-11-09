#include "pch.h"
#include <Windows.h>
#include "Aeyth8/ProxyTypes.h"
#include <iostream>
#include <thread>
#include "ConsoleStructure.h"
#include <string>

void SetConsoleCodePage(UINT codePage) {
    SetConsoleOutputCP(codePage);
}

void CyberConsoleBase_Initialize()
{
    SetConsoleCodePage(CP_UTF8);
    Sleep(5000);
    AllocConsole();
    FILE* nullFile;
    freopen_s(&nullFile, "NUL", "w", stdout);
    system("mode con: cols=200 lines=60");
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX csbi;
    csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hOut, &csbi);
    csbi.dwSize.X = 200;
    csbi.dwSize.Y = 200;
    SetConsoleScreenBufferInfoEx(hOut, &csbi);
    FILE* consoleFile;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    freopen_s(&consoleFile, "CONOUT$", "w", stderr);
    consolestruct::PrintBox("CyberConsole Base V1 by Cyb3rW01f");
    std::cerr <<
        "                                                                                     \n"
        "   ▄▄▄         █                      ▄▄▄                              ▀▀█           \n"
        " ▄▀   ▀ ▄   ▄  █▄▄▄    ▄▄▄    ▄ ▄▄  ▄▀   ▀  ▄▄▄   ▄ ▄▄    ▄▄▄    ▄▄▄     █     ▄▄▄  \n"
        " █      ▀▄ ▄▀  █▀ ▀█  █▀  █   █▀  ▀ █      █▀ ▀█  █▀  █  █   ▀  █▀ ▀█    █    █▀  █ \n"
        " █       █▄█   █   █  █▀▀▀▀   █     █      █   █  █   █   ▀▀▀▄  █   █    █    █▀▀▀▀ \n"
        "  ▀▄▄▄▀  ▀█    ██▄█▀  ▀█▄▄▀   █      ▀▄▄▄▀ ▀█▄█▀  █   █  ▀▄▄▄▀  ▀█▄█▀    ▀▄▄  ▀█▄▄▀ \n"
        "         ▄▀                                                                          \n"
        "        ▀▀                                                                           \n"
        "\n";

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    const std::vector<std::string> replies = {
    "CyberConsole Base by Cyb3rW01f | github.com/UnstoppableWolf",
    "DXGI Proxy by Aeyth8 | github.com/Aeyth8",
    };
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int randomIndex = std::rand() % replies.size();
    std::cerr << replies[randomIndex] << std::endl;
    Sleep(4000);
    system("mode con: cols=122 lines=29");
    system("cls");
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    system("title CyberConsole Base v1");
    consolestruct::PrintBox("CyberConsole Base V1 by Cyb3rW01f");
    consolestruct::PrintBox("DXGI Proxy Created by Aeyth8");
    consolestruct::PrintBox("Type 'help' for a list of commands.");
    std::cerr << "\n\n" << std::endl;
    std::thread commandThread(); {
        consolestruct::CommandLoop();
    };
}

int __stdcall DllMain(HMODULE hModule, DWORD ulReasonForCall, LPVOID lpReserved) {
    DisableThreadLibraryCalls(hModule);

    if (ulReasonForCall == DLL_PROCESS_ATTACH)
    {
        if (Proxy::Attach(hModule))
            CreateThread(0, 0, (LPTHREAD_START_ROUTINE)CyberConsoleBase_Initialize, 0, 0, 0);
    }
    return 1;
}


