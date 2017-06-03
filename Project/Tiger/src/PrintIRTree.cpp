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

void PrintIRTree::printStm(std::shared_ptr<IR::Stm> stm, std::ofstream &outFile, int i)
{
    switch (stm->getStmType())
    {
        case IR::SEQ:
        {
            auto seq = std::dynamic_pointer_cast<IR::Seq>(stm);
            outFile << std::string(" ", i) << "SEQ(" << std::endl;
            printStm(seq->getLeft(), outFile, i + 1);
            outFile << std::endl;
            printStm(seq->getRight(), outFile, i + 1);
            outFile << std::string(" ", i) << ")";
            break;
        }

        case IR::LABEL:
        {
            auto label = std::dynamic_pointer_cast<IR::Label>(stm);
            outFile << std::string(" ", i) << "LABEL " << label->getLabel()->getLabelName();
            break;
        }

        case IR::JUMP:
        {
            auto jump = std::dynamic_pointer_cast<IR::Jump>(stm);
            outFile << std::string(" ", i) << "JUMP(" << std::endl;
            printExp(jump->getExp(), outFile, i + 1);
            outFile << std::string(" ", i) << ")";
            break;
        }

        case IR::CJUMP:
        {
            auto cjump = std::dynamic_pointer_cast<IR::CJump>(stm);
            outFile << std::string(" ", i) << "CJUMP(" << rel_oper[cjump->getOp()] << std::endl;
            printStm(cjump->getLeft(), outFile, i + 1);
            outFile << "," << std::endl;
            printStm(cjump->getRight(), outFile, i + 1);
            outFile << "," << std::endl;
            outFile << std::string(" ", i);
            if (cjump->getLabelTrue())
            {
                outFile << cjump->getLabelTrue()->getLabelName();
            }
            else
            {
                outFile << "NULL";
            }
            outFile << ",";

            if (cjump->getLabelFalse())
            {
                outFile << cjump->getLabelFalse()->getLabelName();
            }
            else
            {
                outFile << "NULL";
            }
            outFile << ")";
            break;
        }

        case IR::MOVE:
        {
            auto move = std::dynamic_pointer_cast<IR::Move>(stm);
            outFile << std::string(" ", i) << "MOVE(" << std::endl;
            printExp(move->getDst(), outFile, i + 1);
            outFile << "," << std::endl;
            printExp(move->getSrc(), outFile, i + 1);
            break;
        }

        case IR::EXP:
        {
            auto exp = std::dynamic_pointer_cast<IR::Exp>(stm);
            outFile << std::string(" ", i) << "EXP(" << std::endl;
            printExp(exp, outFile, i + 1);
            outFile << ")";
            break;
        }
    }
}

void PrintIRTree::printExp(std::shared_ptr<IR::Exp> exp, std::ofstream &outFile, int i)
{
    switch (exp->getExpType())
    {
        case IR::BINOP:
        {
            auto binop = std::dynamic_pointer_cast<IR::Binop>(exp);
            outFile << std::string(" ", i) << "BINOP(" << bin_oper[binop->getOp()] << std::endl;
            printExp(binop->getLeft(), outFile, i + 1);
            outFile << "," << std::endl;
            printExp(binop->getRight(), outFile, i + 1);
            outFile << ")";
            break;
        }

        case IR::MEM:
        {
            auto mem = std::dynamic_pointer_cast<IR::Mem>(exp);
            outFile << std::string(" ", i) << "MEM(" << std::endl;
            printExp(mem->getExp(), outFile, i + 1);
            outFile << ")";
            break;
        }

        case IR::TEMP:
        {
            auto temp = std::dynamic_pointer_cast<IR::Temp>(exp);
            outFile << std::string(" ", i) << "TEMP " << temp->getTemp()->getTempName();
            break;
        }

        case IR::ESEQ:
        {
            auto eseq = std::dynamic_pointer_cast<IR::Eseq>(exp);
            outFile << std::string(" ", i) << "ESEQ(" << std::endl;
            printStm(eseq->getStm(), outFile, i + 1);
            outFile << "," << std::endl;
            printExp(eseq->getExp(), outFile, i + 1);
            outFile << ")";
            break;
        }

        case IR::NAME:
        {
            auto name = std::dynamic_pointer_cast<IR::Name>(exp);
            outFile << std::string(" ", i) << "NAME " << name->getLabel()->getLabelName();
            break;
        }

        case IR::CONST:
        {
            auto constt = std::dynamic_pointer_cast<IR::Const>(exp);
            outFile << std::string(" ", i) << "CONST " << constt->getConstt();
            break;
        }

        case IR::CALL:
        {
            auto call = std::dynamic_pointer_cast<IR::Call>(exp);
            outFile << std::string(" ", i) << "CALL(" << std::endl;
            printExp(call->getFun(), outFile, i + 1);
            for (auto args = call->getArgs()->begin(); args != call->getArgs()->end(); args++)
            {
                outFile << "," << std::endl;
                printExp((*args), outFile, i + 1);
            }
            outFile << ")";
            break;
        }
    }
}


void PrintIRTree::printIRTreeInFile(std::ofstream &outFile)
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
                case Frame::F_STRING_FRAG:
                {
                    auto stringFrag = std::dynamic_pointer_cast<Frame::StringFrag>((*iter));
                    printExp(IR::makeName(stringFrag->getLabel()), outFile, 0);
                    outFile << std::endl;
                    break;
                }
                case Frame::F_PROC_FRAG:
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
