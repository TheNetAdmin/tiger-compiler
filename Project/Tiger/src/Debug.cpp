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
