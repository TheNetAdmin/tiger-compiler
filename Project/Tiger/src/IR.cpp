#include "IR.h"

//
// Created by Chege on 2017/6/1.
//
namespace IR
{
    Stm::Stm(StmType type)
            : stmType(type)
    {
    }

    StmType Stm::getStmType() const
    {
        return stmType;
    }

    Exp::Exp(ExpType expType)
            : Stm(EXP), expType(expType)
    {
    }

    ExpType Exp::getExpType() const
    {
        return expType;
    }

    Seq::Seq(const std::shared_ptr<Stm> &left, const std::shared_ptr<Stm> &right)
            : Stm(SEQ), left(left), right(right)
    {
    }

    const std::shared_ptr<Stm> Seq::getLeft() const
    {
        return left;
    }

    const std::shared_ptr<Stm> Seq::getRight() const
    {
        return right;
    }

    Label::Label(const std::shared_ptr<Temporary::Label> &label)
            : Stm(LABEL), label(label)
    {
    }

    const std::shared_ptr<Temporary::Label> Label::getLabel() const
    {
        return label;
    }

    Jump::Jump(const std::shared_ptr<Exp> &exp, const std::shared_ptr<LabelList> &labels)
            : Stm(JUMP), exp(exp), labels(labels)
    {
    }

    const std::shared_ptr<Exp> Jump::getExp() const
    {
        return exp;
    }

    const std::shared_ptr<LabelList> Jump::getLabels() const
    {
        return labels;
    }

    CJump::CJump(ComparisonOp op, const std::shared_ptr<Exp> &left,
                 const std::shared_ptr<Exp> &right, const std::shared_ptr<Temporary::Label> &labelTrue,
                 const std::shared_ptr<Temporary::Label> &labelFalse)
            : Stm(CJUMP), op(op), left(left), right(right),
              labelTrue(labelTrue), labelFalse(labelFalse)
    {
    }

    ComparisonOp CJump::getOp() const
    {
        return op;
    }

    const std::shared_ptr<Exp> CJump::getLeft() const
    {
        return left;
    }

    const std::shared_ptr<Exp> CJump::getRight() const
    {
        return right;
    }

    const std::shared_ptr<Temporary::Label> CJump::getLabelTrue() const
    {
        return labelTrue;
    }

    const std::shared_ptr<Temporary::Label> CJump::getLabelFalse() const
    {
        return labelFalse;
    }

    void CJump::setLabelTrue(const std::shared_ptr<Temporary::Label> &labelTrue)
    {
        CJump::labelTrue = labelTrue;
    }

    void CJump::setLabelFalse(const std::shared_ptr<Temporary::Label> &labelFalse)
    {
        CJump::labelFalse = labelFalse;
    }

    Move::Move(const std::shared_ptr<Exp> &dst,
               const std::shared_ptr<Exp> &src) : Stm(MOVE), dst(dst), src(src)
    {
    }

    const std::shared_ptr<Exp> Move::getDst() const
    {
        return dst;
    }

    const std::shared_ptr<Exp> Move::getSrc() const
    {
        return src;
    }

    Binop::Binop(ArithmeticOp op, const std::shared_ptr<Exp> &left, const std::shared_ptr<Exp> &right)
            : Exp(BINOP), op(op), left(left), right(right)
    {
    }

    ArithmeticOp Binop::getOp() const
    {
        return op;
    }

    const std::shared_ptr<Exp> Binop::getLeft() const
    {
        return left;
    }

    const std::shared_ptr<Exp> Binop::getRight() const
    {
        return right;
    }

    Mem::Mem(const std::shared_ptr<Exp> &exp) : Exp(MEM), exp(exp)
    {
    }

    const std::shared_ptr<Exp> Mem::getExp() const
    {
        return exp;
    }

    Temp::Temp(const std::shared_ptr<Temporary::Temp> &temp)
            : Exp(TEMP), temp(temp)
    {
    }

    const std::shared_ptr<Temporary::Temp> Temp::getTemp() const
    {
        return temp;
    }

    Eseq::Eseq(const std::shared_ptr<Stm> &stm, const std::shared_ptr<Exp> &exp)
            : Exp(ESEQ), stm(stm), exp(exp)
    {
    }

    const std::shared_ptr<Stm> Eseq::getStm() const
    {
        return stm;
    }

    const std::shared_ptr<Exp> Eseq::getExp() const
    {
        return exp;
    }

    Name::Name(const std::shared_ptr<Temporary::Label> &label)
            : Exp(NAME), label(label)
    {
    }

    const std::shared_ptr<Temporary::Label> Name::getLabel() const
    {
        return label;
    }

    Const::Const(int constt) : Exp(CONST), constt(constt)
    {
    }

    int Const::getConstt() const
    {
        return constt;
    }

    Call::Call(const std::shared_ptr<Exp> &fun, const std::shared_ptr<ExpList> &args)
            : Exp(CALL), fun(fun), args(args)
    {

    }

    const std::shared_ptr<Exp> Call::getFun() const
    {
        return fun;
    }

    const std::shared_ptr<ExpList> Call::getArgs() const
    {
        return args;
    }

    std::shared_ptr<ExpList>
    makeExpList(std::shared_ptr<Exp> head, std::shared_ptr<ExpList> tail)
    {
        if (tail == nullptr)
        {
            tail = std::make_shared<ExpList>();
        }
        tail->push_front(head);
        return tail;
    }

    std::shared_ptr<Stm> makeSeq(std::shared_ptr<Stm> left, std::shared_ptr<Stm> right)
    {
        return std::make_shared<Seq>(left, right);
    }

    std::shared_ptr<Stm> makeLabel(std::shared_ptr<Temporary::Label> label)
    {
        return std::make_shared<Label>(label);
    }

    std::shared_ptr<Stm>
    makeJump(std::shared_ptr<Exp> exp, std::shared_ptr<LabelList> labels)
    {
        return std::make_shared<Jump>(exp, labels);
    }

    std::shared_ptr<Stm>
    makeCJump(ComparisonOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right,
              std::shared_ptr<Temporary::Label> labelTrue, std::shared_ptr<Temporary::Label> labelFalse)
    {
        return std::make_shared<CJump>(op, left, right, labelTrue, labelFalse);
    }

    std::shared_ptr<Stm> makeMove(std::shared_ptr<Exp> dst, std::shared_ptr<Exp> src)
    {
        return std::make_shared<Move>(dst, src);
    }

    std::shared_ptr<Stm> makeExp(std::shared_ptr<Exp> exp)
    {
        return exp;
    }

    std::shared_ptr<Exp>
    makeBinop(ArithmeticOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right)
    {
        return std::make_shared<Binop>(op, left, right);
    }

    std::shared_ptr<Exp> makeMem(std::shared_ptr<Exp> exp)
    {
        return std::make_shared<Mem>(exp);
    }

    std::shared_ptr<Exp> makeTemp(std::shared_ptr<Temporary::Temp> temp)
    {
        return std::make_shared<Temp>(temp);
    }

    std::shared_ptr<Exp> makeEseq(std::shared_ptr<Stm> stm, std::shared_ptr<Exp> exp)
    {
        return std::make_shared<Eseq>(stm, exp);
    }

    std::shared_ptr<Exp> makeName(std::shared_ptr<Temporary::Label> label)
    {
        return std::make_shared<Name>(label);
    }

    std::shared_ptr<Exp> makeConst(int constt)
    {
        return std::make_shared<Const>(constt);
    }

    std::shared_ptr<Exp> makeCall(std::shared_ptr<Exp> fun, std::shared_ptr<ExpList> args)
    {
        return std::make_shared<Call>(fun, args);
    }
}
