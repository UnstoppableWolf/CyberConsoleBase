#include "ConsoleStructure.h"

/*
CyberConsole Base 1.0
Written by Cyb3rW01f
Copyright (C) 2025 Cyb3rW01f
https://github.com/UnstoppableWolf/
*/

/*
* Out of the box this console will do nothing, but will successfully compile and run when added to your games directory and renaming the dll to dxgi.dll

  To use this console for its intended purpose. You need to dump your own SDK of a game made in Unreal Engine, implement the SDK with this console, Then you can add your own commands in the CommandLoop function
  after you make your own functions for the console to call. 
  
  yes i am aware this code is messy, its a crude console after all.

  The console is made to be a base for your own Unreal Engine reverse engineering projects, so feel free to modify it as you see fit.
*/





// ---- SetConsoleTextColor ---- Simple function to set console text color.
void consolestruct::SetConsoleTextColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
// ---- AboutPage ---- About page function called in CommandLoop.
void consolestruct::AboutPage() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE);
    system("cls");
    std::cerr << "-About-\n\n\n\n\n" << std::endl;
    SetConsoleTextColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); 
    SetConsoleTextColor(FOREGROUND_GREEN);
    std::cerr << "CyberConsole Base"; SetConsoleTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE); 
    std::cerr << " made by"; SetConsoleTextColor(FOREGROUND_RED);
	std::cerr << " Cyb3rW01f\n\n"; SetConsoleTextColor(FOREGROUND_GREEN);
    std::cerr << "DXGI Proxy"; SetConsoleTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE); 
    std::cerr << " made by"; SetConsoleTextColor(FOREGROUND_RED);
	std::cerr << " Aeyth8\n\n\n" << std::endl; SetConsoleTextColor(FOREGROUND_GREEN);
}
// ---- DisplayHelp ---- Help menu function called in CommandLoop.
void consolestruct::DisplayHelp() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    system("mode con: cols=155 lines=45");
    std::cerr << "\n\n\n" << std::endl;
    SetConsoleTextColor(FOREGROUND_GREEN);
    consolestruct::PrintBox(" - CyberConsole Console Commands - ");
    std::cerr << "\n" << std::endl;
    SetConsoleTextColor(FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cerr << "Help menu, Customise to your liking.\n\n" << std::endl;
    std::cerr << "help " << "- Displays the help menu. (wow!)\n\n" << std::endl;
    std::cerr << "about " << "- Displays the about page.\n\n" << std::endl;
	std::cerr << "clear/cls " << "- Clears the console screen.\n\n" << std::endl;
	std::cerr << "example " << "- An example command, replace with your own functionality.\n\n" << std::endl;
    
    SetConsoleTextColor(FOREGROUND_GREEN);
    SetConsoleTextColor(FOREGROUND_GREEN);
}

// ---- WrapText ---- Text wrapping function for PrintBox.
std::vector<std::string> consolestruct::WrapText(const std::string& text, size_t width) {
    std::vector<std::string> lines;
    size_t start = 0;
    while (start < text.length()) {
        size_t end = start + width;
        if (end > text.length()) end = text.length();
        lines.push_back(text.substr(start, end - start));
        start = end;
    }
    return lines;
}

// ---- ConsoleLog ---- Simple Logging function
void consolestruct::ConsoleLog(const std::string& msg) {
    try {
        static std::ofstream logFile;

        if (!logFile.is_open()) {
            char exePath[MAX_PATH];
            GetModuleFileNameA(nullptr, exePath, MAX_PATH);
            std::filesystem::path dirPath = std::filesystem::path(exePath).parent_path();
            std::filesystem::path logPath = dirPath / "CyberConsoleLog.txt";

            int counter = 2;
            while (std::filesystem::exists(logPath)) {
                logPath = dirPath / ("CyberConsoleLog" + std::to_string(counter) + ".txt");
                counter++;
            }

            logFile.open(logPath, std::ios::out);
        }

        logFile << msg << std::endl;
    }
    catch (...) {
      
    }
}

// ---- PrintBox ---- (mostly) well-formatted box printing
void consolestruct::PrintBox(const std::string& text) {
    try {
		const size_t minWidth = 45; // Adjust the width here, the text will wrap but the box will maintain at least this width.
        const size_t padding = 2;

        std::vector<std::string> lines = WrapText(text, minWidth - 2 - padding * 2);
        size_t maxWidth = minWidth;

        std::cerr << "+" << std::string(maxWidth - 2, '-') << "+" << std::endl;

        for (const std::string& line : lines) {
            std::cerr << "| " << line << std::string(maxWidth - line.length() - 3, ' ') << "|" << std::endl;
        }

        std::cerr << "+" << std::string(maxWidth - 2, '-') << "+" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
    }
}
void Example() {
	std::cerr << "This is an example command. Replace it with your own functionality." << std::endl;
}
// ---- CommandLoop ---- What hosts the console commands to be called, you can add your own here.
void consolestruct::CommandLoop() {
    std::unordered_map<std::string, std::function<void()>> commands;

    commands["help"] = [] { DisplayHelp(); };
    commands["about"] = [] { AboutPage(); };
    commands["cls"] = commands["clear"];
    commands["exit"] = [] { exit(0x00000001); }; //Add any additional commands below this line.
	commands["example"] = [] { Example();}; //Example command, replace with a functioning one of your own.
    commands["clear"] = [] {
        system("cls");
        system("mode con: cols=125 lines=30");
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        consolestruct::PrintBox("CyberConsole Base V1");
        };
    
    std::string input;
    char ch;

    while (true) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        std::cerr << "CC> ";
        input.clear();

        while (true) {
            ch = _getch();
            if (ch == '\r') {
                std::cerr << std::endl;
                break;
            }
            else if (ch == '\b') {
                if (!input.empty()) {
                    input.pop_back();
                    std::cerr << "\b \b";
                }
            }
            else if (ch >= 32 && ch < 127) {
                input += ch;
                std::cerr << ch;
            }
        }

        std::transform(input.begin(), input.end(), input.begin(), ::tolower);

        auto cmd = commands.find(input);
        if (cmd != commands.end()) {
            cmd->second();
        }
        else {
            std::cerr << "Unknown command: " << input << std::endl;
        }
    }
}