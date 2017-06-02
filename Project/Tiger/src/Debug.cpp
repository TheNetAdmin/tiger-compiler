//
// Created by MATRIX on 2017/6/2.
//

#include "Debug.h"
#include <iostream>
void debugStart(const std::string &msg)
{
    std::cout << "DEBUG: [" << msg << "] start" << std::endl;
}

void debugEnd(const std::string &msg)
{
    std::cout << "DEBUG: [" << msg << "] end" << std::endl;
}

Debugger::Debugger(const std::string &name) : name(name)
{
    std::cerr << "Debugger [ " << name << " ] start" << std::endl;
}

Debugger::~Debugger()
{
    std::cerr << "Debugger [ " << name << " ] end" << std::endl;
}
