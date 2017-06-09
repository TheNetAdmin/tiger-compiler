//
// Created by PrinceXuan on 2017/6/4.
//

#include "PrintIRTree.h"

PrintIRTree::PrintIRTree(const std::shared_ptr<Frame::FragList> &fragList) : fragList(fragList)
{}

static char bin_oper[][12] = {
        "PLUS", "MINUS", "TIMES", "DIVIDE"};

static char rel_oper[][12] = {
        "EQ", "NE", "LT", "GT", "LE", "GE"};

void printBlank(int i, std::ostream &out)
{
    out << std::string(i, ' ');
}

void PrintIRTree::printStm(std::shared_ptr<IR::Stm> stm, std::ostream &outFile, int i)
{
    switch (stm->getStmType())
    {
        case IR::SEQ:
        {
            auto seq = std::dynamic_pointer_cast<IR::Seq>(stm);
            /*   这是用来占位的   */outFile << "| — SEQ" << std::endl;
            printBlank(i, outFile);
            outFile << "      ";
            printStm(seq->getLeft(), outFile, i + 5);
            printBlank(i, outFile);
            outFile << "      ";
            printStm(seq->getRight(), outFile, i + 5);
            outFile << std::endl;
            break;
        }

        case IR::LABEL:
        {
            auto label = std::dynamic_pointer_cast<IR::Label>(stm);
            /*   这是用来占位的   */outFile << "| — LABEL" << std::endl;
            printBlank(i, outFile);
            outFile << "       | — " << label->getLabel()->getLabelName();
            outFile << std::endl;
            break;
        }

        case IR::JUMP:
        {
            auto jump = std::dynamic_pointer_cast<IR::Jump>(stm);
            /*   这是用来占位的   */outFile << "| — JUMP" << std::endl;
            printBlank(i, outFile);
            outFile << "      ";
            printExp(jump->getExp(), outFile, i + 6);
            outFile << std::endl;
            break;
        }

        case IR::CJUMP:
        {
            auto cjump = std::dynamic_pointer_cast<IR::CJump>(stm);
            /*   这是用来占位的   */outFile << "| — CJUMP" << std::endl;
            printBlank(i, outFile);
            outFile << "       | — " << rel_oper[cjump->getOp()] << std::endl;
            printBlank(i, outFile);
            outFile << "       ";
            printStm(cjump->getLeft(), outFile, i + 7);
            printBlank(i, outFile);
            outFile << "       ";
            printStm(cjump->getRight(), outFile, i + 7);
            printBlank(i, outFile);
            outFile << "       | — " << (cjump->getLabelTrue() ? cjump->getLabelTrue()->getLabelName() : "NULL");
            outFile << std::endl;
            printBlank(i, outFile);
            outFile << "       | — " << (cjump->getLabelTrue() ? cjump->getLabelFalse()->getLabelName() : "NULL");
            outFile << std::endl;
            break;
        }

        case IR::MOVE:
        {
            auto move = std::dynamic_pointer_cast<IR::Move>(stm);
            /*   这是用来占位的   */outFile << "| — MOVE" << std::endl;
            printBlank(i, outFile);
            outFile << "      ";
            printStm(move->getDst(), outFile, i + 5);
            printBlank(i, outFile);
            outFile << "      ";
            printStm(move->getSrc(), outFile, i + 5);
            outFile << std::endl;
            break;
        }

        case IR::EXP:
        {
            auto exp = std::dynamic_pointer_cast<IR::Exp>(stm);
            /*   这是用来占位的   */outFile << "| — EXP" << std::endl;
            printBlank(i, outFile);
            outFile << "      ";
            printExp(exp, outFile, i + 6);
            outFile << std::endl;
            break;
        }
    }
}

void PrintIRTree::printExp(std::shared_ptr<IR::Exp> exp, std::ostream &outFile, int i)
{
    switch (exp->getExpType())
    {
        case IR::BINOP:
        {
            auto binop = std::dynamic_pointer_cast<IR::Binop>(exp);
            /*   这是用来占位的   */outFile << "| — BINOP" << std::endl;
            printBlank(i, outFile);
            outFile << "       | — " << bin_oper[binop->getOp()] << std::endl;
            printBlank(i, outFile);
            outFile << "       ";
            printStm(binop->getLeft(), outFile, i + 6);
            printBlank(i, outFile);
            outFile << "       ";
            printStm(binop->getRight(), outFile, i + 6);
            outFile << std::endl;
            break;
        }

        case IR::MEM:
        {
            auto mem = std::dynamic_pointer_cast<IR::Mem>(exp);
            /*   这是用来占位的   */outFile << "| — MEM" << std::endl;
            printBlank(i, outFile);
            outFile << "      ";
            printExp(mem->getExp(), outFile, i + 6);
            outFile << std::endl;
            break;
        }

        case IR::TEMP:
        {
            auto temp = std::dynamic_pointer_cast<IR::Temp>(exp);
            /*   这是用来占位的   */outFile << "| — TEMP " << temp->getTemp()->getTempName() << std::endl;
            break;
        }

        case IR::ESEQ:
        {
            auto eseq = std::dynamic_pointer_cast<IR::Eseq>(exp);
            /*   这是用来占位的   */outFile << "| — ESEQ" << std::endl;
            printBlank(i, outFile);
            outFile << "      ";
            printStm(eseq->getStm(), outFile, i + 5);
            printBlank(i, outFile);
            outFile << "      ";
            printExp(eseq->getExp(), outFile, i + 5);
            outFile << std::endl;
            break;
        }

        case IR::NAME:
        {
            auto name = std::dynamic_pointer_cast<IR::Name>(exp);
            /*   这是用来占位的   */outFile << "| — NAME " << name->getLabel()->getLabelName() << std::endl;
            break;
        }

        case IR::CONST:
        {
            auto constt = std::dynamic_pointer_cast<IR::Const>(exp);
            /*   这是用来占位的   */outFile << "| — CONST " << constt->getConstt() << std::endl;
            break;
        }

        case IR::CALL:
        {
            auto call = std::dynamic_pointer_cast<IR::Call>(exp);
            /*   这是用来占位的   */outFile << "| — CALL" << std::endl;
            printBlank(i, outFile);
            outFile << "      ";
            printExp(call->getFun(), outFile, i + 6);
            for (auto args = call->getArgs()->begin(); args != call->getArgs()->end(); args++)
            {
                printBlank(i, outFile);
                outFile << "      ";
                printExp((*args), outFile, i + 6);
            }
            outFile << std::endl;
            break;
        }
    }
}


void PrintIRTree::printIRTreeInFile(std::ostream &outFile)
{
    if (fragList == nullptr)
    {
        outFile << "FragList is empty" << std::endl;
    }
    else
    {
        for (auto iter = fragList->begin(); iter != fragList->end(); iter++)
        {
            switch ((*iter)->getKind())
            {
                case Frame::STRING_FRAG:
                {
                    auto stringFrag = std::dynamic_pointer_cast<Frame::StringFrag>((*iter));
                    printExp(IR::makeName(stringFrag->getLabel()), outFile, 0);
                    outFile << std::endl;
                    break;
                }
                case Frame::PROC_FRAG:
                {
                    auto procFrag = std::dynamic_pointer_cast<Frame::ProcFrag>((*iter));
                    printStm(procFrag->getBody(), outFile, 0);
                    outFile << std::endl;
                    break;
                }
                default:
                {
                    Tiger::Error error("frag-kind is error");
                }
            }
        }
    }
}

static int nodeNum = 0;

int PrintIRTree::printStmDot(std::shared_ptr<IR::Stm> stm, std::ostream &outFile)
{
    switch (stm->getStmType())
    {
        case IR::SEQ:
        {
            auto seq = std::dynamic_pointer_cast<IR::Seq>(stm);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> SEQ |<f2>\"]" << std::endl;
            int leftNum = printStmDot(seq->getLeft(), outFile);
            int rightNum = printStmDot(seq->getRight(), outFile);
            outFile << "\"node" << mynode << "\":f0 -> \"node" << leftNum << "\":f1" << std::endl;
            outFile << "\"node" << mynode << "\":f2 -> \"node" << rightNum << "\":f1" << std::endl;
            return mynode;
        }

        case IR::LABEL:
        {
            auto label = std::dynamic_pointer_cast<IR::Label>(stm);
            int mynode = ++nodeNum;
            int childnode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> LABEL |<f2>\"]" << std::endl;
            outFile << "node" << childnode << "[label = \"<f0>|<f1> " << label->getLabel()->getLabelName() << "|<f2>\"]"
                    << std::endl;
            outFile << "\"node" << mynode << "\":f1 -> \"node" << childnode << "\":f1" << std::endl;
            return mynode;
        }

        case IR::JUMP:
        {
            auto jump = std::dynamic_pointer_cast<IR::Jump>(stm);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> JUMP |<f2>\"]" << std::endl;
            int childnode = printExpDot(jump->getExp(), outFile);
            outFile << "\"node" << mynode << "\":f1 -> \"node" << childnode << "\":f1" << std::endl;
            return mynode;
        }

        case IR::CJUMP:
        {
            auto cjump = std::dynamic_pointer_cast<IR::CJump>(stm);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>"
                    << (cjump->getLabelTrue() ? cjump->getLabelTrue()->getLabelName() : "NULL")
                    << "|<f1> CJUMP: " << rel_oper[cjump->getOp()] << " |<f2>"
                    << (cjump->getLabelTrue() ? cjump->getLabelFalse()->getLabelName() : "NULL")
                    << "\"]" << std::endl;
            int leftNum = printStmDot(cjump->getLeft(), outFile);
            int rightNum = printStmDot(cjump->getRight(), outFile);
            outFile << "\"node" << mynode << "\":f0 -> \"node" << leftNum << "\":f1" << std::endl;
            outFile << "\"node" << mynode << "\":f2 -> \"node" << rightNum << "\":f1" << std::endl;
            return mynode;
        }

        case IR::MOVE:
        {
            auto move = std::dynamic_pointer_cast<IR::Move>(stm);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> MOVE |<f2>\"]" << std::endl;
            int leftNum = printStmDot(move->getDst(), outFile);
            int rightNum = printStmDot(move->getSrc(), outFile);
            outFile << "\"node" << mynode << "\":f0 -> \"node" << leftNum << "\":f1" << std::endl;
            outFile << "\"node" << mynode << "\":f2 -> \"node" << rightNum << "\":f1" << std::endl;
            return mynode;
        }

        case IR::EXP:
        {
            auto exp = std::dynamic_pointer_cast<IR::Exp>(stm);
            return printExpDot(exp, outFile);
            break;
        }
    }
}

int PrintIRTree::printExpDot(std::shared_ptr<IR::Exp> exp, std::ostream &outFile)
{
    switch (exp->getExpType())
    {
        case IR::BINOP:
        {
            auto binop = std::dynamic_pointer_cast<IR::Binop>(exp);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> BINOP: " << bin_oper[binop->getOp()] << " |<f2>\"]"
                    << std::endl;
            int leftNum = printStmDot(binop->getLeft(), outFile);
            int rightNum = printStmDot(binop->getRight(), outFile);
            outFile << "\"node" << mynode << "\":f0 -> \"node" << leftNum << "\":f1" << std::endl;
            outFile << "\"node" << mynode << "\":f2 -> \"node" << rightNum << "\":f1" << std::endl;
            return mynode;
        }

        case IR::MEM:
        {
            auto mem = std::dynamic_pointer_cast<IR::Mem>(exp);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> MEM |<f2>\"]" << std::endl;
            int childnode = printExpDot(mem->getExp(), outFile);
            outFile << "\"node" << mynode << "\":f1 -> \"node" << childnode << "\":f1" << std::endl;
            return mynode;
        }

        case IR::TEMP:
        {
            auto temp = std::dynamic_pointer_cast<IR::Temp>(exp);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> TEMP: " << temp->getTemp()->getTempName() << "|<f2>\"]"
                    << std::endl;
            return mynode;
        }

        case IR::ESEQ:
        {
            auto eseq = std::dynamic_pointer_cast<IR::Eseq>(exp);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> ESEQ |<f2>\"]" << std::endl;
            int leftNum = printStmDot(eseq->getStm(), outFile);
            int rightNum = printExpDot(eseq->getExp(), outFile);
            outFile << "\"node" << mynode << "\":f0 -> \"node" << leftNum << "\":f1" << std::endl;
            outFile << "\"node" << mynode << "\":f2 -> \"node" << rightNum << "\":f1" << std::endl;
            return mynode;
        }

        case IR::NAME:
        {
            auto name = std::dynamic_pointer_cast<IR::Name>(exp);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> NAME: " << name->getLabel()->getLabelName()
                    << "|<f2>\"]" << std::endl;
            return mynode;
        }

        case IR::CONST:
        {
            auto constt = std::dynamic_pointer_cast<IR::Const>(exp);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> CONST: " << constt->getConstt() << "|<f2>\"]"
                    << std::endl;
            return mynode;
        }

        case IR::CALL:
        {
            auto call = std::dynamic_pointer_cast<IR::Call>(exp);
            int mynode = ++nodeNum;
            outFile << "node" << mynode << "[label = \"<f0>|<f1> CALL |<f2>\"]" << std::endl;
            int leftNum = printExpDot(call->getFun(), outFile);
            int rightNum = mynode;
            outFile << "\"node" << mynode << "\":f0 -> \"node" << leftNum << "\":f1" << std::endl;

            for (auto args = call->getArgs()->begin(); args != call->getArgs()->end(); args++)
            {
                int childnode = printExpDot((*args), outFile);
                outFile << "\"node" << mynode << "\":f2 -> \"node" << childnode << "\":f1" << std::endl;

            }
            return mynode;
        }
    }
}

void PrintIRTree::makeDotFile(std::ostream &outFile)
{
    if (fragList == nullptr)
    {
        outFile << "FragList is empty" << std::endl;
    }
    else
    {
        int gNum = 0;
        for (auto iter = fragList->begin(); iter != fragList->end(); iter++)
        {
            outFile << "digraph G" << gNum++ << "{" << std::endl;
            outFile << "node [shape = record, height = .1]" << std::endl;
            switch ((*iter)->getKind())
            {
                case Frame::STRING_FRAG:
                {
                    auto stringFrag = std::dynamic_pointer_cast<Frame::StringFrag>((*iter));
                    printExpDot(IR::makeName(stringFrag->getLabel()), outFile);
                    break;
                }
                case Frame::PROC_FRAG:
                {
                    auto procFrag = std::dynamic_pointer_cast<Frame::ProcFrag>((*iter));
                    printStmDot(procFrag->getBody(), outFile);
                    break;
                }
                default:
                {
                    Tiger::Error error("frag-kind is error");
                }
            }
            outFile << "}" << std::endl;
            outFile << "---" << std::endl;
        }
    }
}
