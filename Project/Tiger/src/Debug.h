//
// Created by MATRIX on 2017/6/2.
//

#ifndef SRC_DEBUG_H
#define SRC_DEBUG_H
#include <string>

void debugStart(const std::string &  msg);
void debugEnd(const std::string & msg);

namespace
{
    bool debugOutput = false;
}

class Debugger {
public:
    std::string name;

    Debugger(const std::string &name);

    virtual ~Debugger();
};
#endif //SRC_DEBUG_H
