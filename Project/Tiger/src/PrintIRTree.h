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

class PrintIRTree
{
    std::shared_ptr<Frame::FragList> fragList;

    void printStm(std::shared_ptr<IR::Stm> exp, std::ofstream &outFile, int i);

    void printExp(std::shared_ptr<IR::Exp> exp, std::ofstream &outFile, int i);

public:
    PrintIRTree(const std::shared_ptr<Frame::FragList> &fragList);

    void printIRTreeInFile(std::ofstream &outFile);
};

#endif //SRC_PRINTIRTREE_H
