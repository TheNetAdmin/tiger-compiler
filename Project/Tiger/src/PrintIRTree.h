//
// Created by PrinceXuan on 2017/6/4.
//

#ifndef SRC_PRINTIRTREE_H
#define SRC_PRINTIRTREE_H

#include <memory>
#include <fstream>
#include "IR.h"
#include "Frame.h"
#include "Translate.h"
#include "Error.h"
#include <string>
#include <iostream>

class PrintIRTree
{
    std::shared_ptr<Frame::FragList> fragList;

    void printStm(std::shared_ptr<IR::Stm> exp, std::ostream &outFile, int i);

    void printExp(std::shared_ptr<IR::Exp> exp, std::ostream &outFile, int i);

    int printStmDot(std::shared_ptr<IR::Stm> stm, std::ostream &outFile);

    int printExpDot(std::shared_ptr<IR::Exp> exp, std::ostream &outFile);

public:
    PrintIRTree(const std::shared_ptr<Frame::FragList> &fragList);

    void printIRTreeInFile(std::ostream &outFile);

    void makeDotFile(std::ostream &outFile);

};

#endif //SRC_PRINTIRTREE_H