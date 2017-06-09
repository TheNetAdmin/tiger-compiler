//
// Created by Chege on 2017/6/1.
//

#ifndef SRC_IRTree_H
#define SRC_IRTree_H

#include <memory>
#include <list>
#include <string>
#include "Temporary.h"

namespace IR
{

    class Stm;

    class Exp;

    typedef std::list<std::shared_ptr<Stm>> StmList;
    typedef std::list<std::shared_ptr<Exp>> ExpList;
    typedef std::list<std::shared_ptr<Temporary::Label>> LabelList;

    enum ArithmeticOp
    {
        PLUS, MINUS, MUL, DIV
    };
    enum ComparisonOp
    {
        EQ, NE, LT, GT, LE, GE
    };

    // Base class
    enum StmType
    {
        SEQ, LABEL, JUMP, CJUMP, MOVE, EXP
    };

    class Stm
    {
        StmType stmType;
    public:
        Stm(StmType type);

        virtual ~Stm()
        {};

        StmType getStmType() const;
    };

    enum ExpType
    {
        BINOP, MEM, TEMP, ESEQ, NAME, CONST, CALL, DOUBLE
    };

    class Exp : public Stm
    {
        ExpType expType;
    public:
        Exp(ExpType expType);

        virtual ~Exp()
        {}

        ExpType getExpType() const;
    };


    // extend class

    class Seq : public Stm
    {
        std::shared_ptr<Stm> left, right;
    public:
        Seq(const std::shared_ptr<Stm> &left, const std::shared_ptr<Stm> &right);

        const std::shared_ptr<Stm> getLeft() const;

        const std::shared_ptr<Stm> getRight() const;
    };

    class Label : public Stm
    {
        std::shared_ptr<Temporary::Label> label;
    public:
        Label(const std::shared_ptr<Temporary::Label> &label);

        const std::shared_ptr<Temporary::Label> getLabel() const;
    };

    class Jump : public Stm
    {
        std::shared_ptr<Exp> exp;
        std::shared_ptr<LabelList> labels;
    public:
        Jump(const std::shared_ptr<Exp> &exp, const std::shared_ptr<LabelList> &labels);

        const std::shared_ptr<Exp> getExp() const;

        const std::shared_ptr<LabelList> getLabels() const;
    };

    class CJump : public Stm
    {
        ComparisonOp op;
        std::shared_ptr<Exp> left, right;
        std::shared_ptr<Temporary::Label> labelTrue, labelFalse;
    public:
        CJump(ComparisonOp op, const std::shared_ptr<Exp> &left, const std::shared_ptr<Exp> &right,
              const std::shared_ptr<Temporary::Label> &labelTrue, const std::shared_ptr<Temporary::Label> &labelFalse);

        ComparisonOp getOp() const;

        const std::shared_ptr<Exp> getLeft() const;

        const std::shared_ptr<Exp> getRight() const;

        const std::shared_ptr<Temporary::Label> getLabelTrue() const;

        const std::shared_ptr<Temporary::Label> getLabelFalse() const;

        void setLabelTrue(const std::shared_ptr<Temporary::Label> &labelTrue);

        void setLabelFalse(const std::shared_ptr<Temporary::Label> &labelFalse);
    };

    class Move : public Stm
    {
        std::shared_ptr<Exp> dst, src;
    public:
        Move(const std::shared_ptr<Exp> &dst, const std::shared_ptr<Exp> &src);

        const std::shared_ptr<Exp> getDst() const;

        const std::shared_ptr<Exp> getSrc() const;
    };

    class Binop : public Exp
    {
        ArithmeticOp op;
        std::shared_ptr<Exp> left, right;
    public:
        Binop(ArithmeticOp op, const std::shared_ptr<Exp> &left, const std::shared_ptr<Exp> &right);

        ArithmeticOp getOp() const;

        const std::shared_ptr<Exp> getLeft() const;

        const std::shared_ptr<Exp> getRight() const;
    };

    class Mem : public Exp
    {
        std::shared_ptr<Exp> exp;
    public:
        Mem(const std::shared_ptr<Exp> &exp);

        const std::shared_ptr<Exp> getExp() const;
    };

    class Temp : public Exp
    {
        std::shared_ptr<Temporary::Temp> temp;
    public:
        Temp(const std::shared_ptr<Temporary::Temp> &temp);

        const std::shared_ptr<Temporary::Temp> getTemp() const;
    };

    class Eseq : public Exp
    {
        std::shared_ptr<Stm> stm;
        std::shared_ptr<Exp> exp;
    public:
        Eseq(const std::shared_ptr<Stm> &stm, const std::shared_ptr<Exp> &exp);

        const std::shared_ptr<Stm> getStm() const;

        const std::shared_ptr<Exp> getExp() const;
    };

    class Name : public Exp
    {
        std::shared_ptr<Temporary::Label> label;
    public:
        Name(const std::shared_ptr<Temporary::Label> &label);

        const std::shared_ptr<Temporary::Label> getLabel() const;
    };

    class Const : public Exp
    {
        int constt;
    public:
        Const(int constt);

        int getConstt() const;
    };

    class Call : public Exp
    {
        std::shared_ptr<Exp> fun;
        std::shared_ptr<ExpList> args;
    public:
        Call(const std::shared_ptr<Exp> &fun, const std::shared_ptr<ExpList> &args);

        const std::shared_ptr<Exp> getFun() const;

        const std::shared_ptr<ExpList> getArgs() const;
    };

    // 各种函数
    std::shared_ptr<ExpList> makeExpList(std::shared_ptr<Exp> head, std::shared_ptr<ExpList> tail);
    //MakestmList MakeStmList(Makestm head, MakestmList tail);

    std::shared_ptr<Stm> makeSeq(std::shared_ptr<Stm> left, std::shared_ptr<Stm> right);

    std::shared_ptr<Stm> makeLabel(std::shared_ptr<Temporary::Label> label);

    std::shared_ptr<Stm> makeJump(std::shared_ptr<Exp> exp, std::shared_ptr<LabelList> labels);

    std::shared_ptr<Stm> makeCJump(ComparisonOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right,
                                   std::shared_ptr<Temporary::Label> labelTrue,
                                   std::shared_ptr<Temporary::Label> labelFalse);

    std::shared_ptr<Stm> makeMove(std::shared_ptr<Exp> dst, std::shared_ptr<Exp> src);

    std::shared_ptr<Stm> makeExp(std::shared_ptr<Exp> exp);

    std::shared_ptr<Exp> makeBinop(ArithmeticOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right);

    std::shared_ptr<Exp> makeMem(std::shared_ptr<Exp> exp);

    std::shared_ptr<Exp> makeTemp(std::shared_ptr<Temporary::Temp> temp);

    std::shared_ptr<Exp> makeEseq(std::shared_ptr<Stm> stm, std::shared_ptr<Exp> exp);

    std::shared_ptr<Exp> makeName(std::shared_ptr<Temporary::Label> label);

    std::shared_ptr<Exp> makeConst(int constt);

    std::shared_ptr<Exp> makeCall(std::shared_ptr<Exp> fun, std::shared_ptr<ExpList> args);
}


#endif //SRC_IRTree_H