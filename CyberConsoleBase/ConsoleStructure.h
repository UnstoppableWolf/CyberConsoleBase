#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include "Aeyth8/ProxyTypes.h"
#include <conio.h>
#include "pch.h"
#include <thread>
#include <atomic>
#include <functional>
using namespace std;

/*
CyberConsole Base 1.0
Written by Cyb3rW01f
Copyright (C) 2025 Cyb3rW01f
https://github.com/UnstoppableWolf/
*/

namespace consolestruct
{
    // function declarations go here.
    std::vector<std::string> WrapText(const std::string& text, size_t width);
    void DisplayHelp();
    void AboutPage();
    void ConsoleLog(const std::string& msg);
    void PrintBox(const std::string& text);
	void CommandLoop();
    void SetConsoleTextColor(WORD color);
	
    
    
};
