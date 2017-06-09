//
// Created by Chege on 2017/6/2.
//

#include "Translate.h"

namespace Translate
{


    Level::Level(const std::shared_ptr<Level> &parent, const std::shared_ptr<Temporary::Label> &name,
                 const std::shared_ptr<Frame::Frame> &frame, const std::shared_ptr<AccessList> &formals) : parent(
            parent), name(name), frame(frame), formals(formals)
    {}

    const std::shared_ptr<Level> Level::getParent() const
    {
        return parent;
    }

    const std::shared_ptr<Temporary::Label> Level::getName() const
    {
        return name;
    }

    const std::shared_ptr<Frame::Frame> Level::getFrame() const
    {
        return frame;
    }

    const std::shared_ptr<AccessList> Level::getFormals() const
    {
        return formals;
    }

    void Level::setFormals(const std::shared_ptr<AccessList> &formals)
    {

        Level::formals = formals;

    }

    Access::Access(const std::shared_ptr<Level> &level, const std::shared_ptr<Frame::Access> &access) : level(level),
                                                                                                        access(access)
    {}

    const std::shared_ptr<Level> Access::getLevel() const
    {
        return level;
    }

    const std::shared_ptr<Frame::Access> Access::getAccess() const
    {
        return access;
    }

    Exp::Exp(ExpType kind) : kind(kind)
    {}

    Exp::~Exp()
    {

    }

    ExpType Exp::getKind() const
    {
        return kind;
    }

    Ex::Ex(const std::shared_ptr<IR::Exp> &ex) : Exp(EX), ex(ex)
    {}

    const std::shared_ptr<IR::Exp> Ex::getEx() const
    {
        return ex;
    }

    Nx::Nx(const std::shared_ptr<IR::Stm> &nx) : Exp(NX), nx(nx)
    {}

    const std::shared_ptr<IR::Stm> Nx::getNx() const
    {
        return nx;
    }

    Cx::Cx(const std::shared_ptr<PatchList> &patchList, const std::shared_ptr<IR::Stm> &stm)
            : Exp(CX), patchList(patchList), stm(stm)
    {}

    const std::shared_ptr<PatchList> Cx::getPatchList() const
    {
        return patchList;
    }

    const std::shared_ptr<IR::Stm> Cx::getStm() const
    {
        return stm;
    }

    std::shared_ptr<AccessList> makeFormalAccessList(std::shared_ptr<Level> l)
    {
        std::shared_ptr<AccessList> accessList = std::make_shared<AccessList>();
        auto frame = l->getFrame();
        auto formals = frame->getFormals();
        for (auto formal = ++(formals->begin()); formal != formals->end(); formal++)
        {
            auto access = std::make_shared<Access>(l, *formal);
            accessList->push_back(access);
        }
        return accessList;
    }

    /* STACK - FRAME */



    static std::shared_ptr<Level> globalLevel = makeNewLevel(nullptr, Temporary::makeLabel(),
                                                             std::make_shared<BoolList>());

    std::shared_ptr<Level> getGlobalLevel(void)
    {
        return globalLevel;
    }


    std::shared_ptr<Level> makeNewLevel(std::shared_ptr<Level> parent, std::shared_ptr<Temporary::Label> name,
                                        std::shared_ptr<BoolList> formals)
    {
        formals->push_front(true);
        auto l = std::make_shared<Level>(parent, name, Frame::makeFrame(name, formals), nullptr);
        l->setFormals(makeFormalAccessList(l));
        return l;
    }


    std::shared_ptr<Access> allocLocal(std::shared_ptr<Level> level, bool escape)
    {
        return std::make_shared<Access>(level, Frame::allocLocalVariable(level->getFrame(), escape));
    }


    /* IR */
    std::shared_ptr<Exp> makeEx(const std::shared_ptr<IR::Exp> &exp)
    {
        return std::make_shared<Ex>(exp);
    }

    std::shared_ptr<Exp> makeNx(std::shared_ptr<IR::Stm> stm)
    {
        return std::make_shared<Nx>(stm);
    }

    std::shared_ptr<Exp>
    makeCx(std::shared_ptr<PatchList> patchList, std::shared_ptr<IR::Stm> stm)
    {
        return std::make_shared<Cx>(patchList, stm);
    }

    std::shared_ptr<PatchList> patchList(std::shared_ptr<IR::CJump> head, std::shared_ptr<PatchList> tail)
    {
        if (tail == nullptr)
        {
            tail = std::make_shared<PatchList>();
        }
        tail->push_front(head);
        return tail;
    }

    void doPatch(std::shared_ptr<PatchList> patchList, std::shared_ptr<Temporary::Label> trueLabel,
                 std::shared_ptr<Temporary::Label> falseLabel)
    {
        auto iter = patchList->begin();
        for (; iter != patchList->end(); iter++)
        {
            (*iter)->setLabelTrue(trueLabel);
            (*iter)->setLabelFalse(falseLabel);
        }
    }


    std::shared_ptr<IR::Exp> unEx(std::shared_ptr<Exp> exp)
    {
        switch (exp->getKind())
        {
            case EX:
                return std::dynamic_pointer_cast<Ex>(exp)->getEx();
            case NX:
                return IR::makeEseq(std::dynamic_pointer_cast<Nx>(exp)->getNx(), IR::makeConst(0));
            case CX:
            {
                auto r = Temporary::makeTemp();
                auto t = Temporary::makeLabel();
                auto f = Temporary::makeLabel();
                auto cx = std::dynamic_pointer_cast<Cx>(exp);
                doPatch(cx->getPatchList(), t, f);
                return IR::makeEseq(IR::makeMove(IR::makeTemp(r), IR::makeConst(1)),
                                    IR::makeEseq(cx->getStm(),
                                                 IR::makeEseq(IR::makeLabel(f),
                                                              IR::makeEseq(IR::makeMove(
                                                                      IR::makeTemp(r),
                                                                      IR::makeConst(0)),
                                                                           IR::makeEseq(
                                                                                   IR::makeLabel(t),
                                                                                   IR::makeTemp(
                                                                                           r))))));
            }
            default:
                Tiger::Error error("something wrong in Translate::unEx");
        }
    }

    std::shared_ptr<IR::Stm> unNx(std::shared_ptr<Exp> exp)
    {
        switch (exp->getKind())
        {
            case EX:
                return IR::makeExp(std::dynamic_pointer_cast<Ex>(exp)->getEx());
            case NX:
                return std::dynamic_pointer_cast<Nx>(exp)->getNx();
            case CX:
                return IR::makeExp(unEx(exp));
            default:
                Tiger::Error error("something wrong in Translate::unNx");
        }
    }

    std::shared_ptr<Cx> unCx(std::shared_ptr<Exp> exp)
    {
        switch (exp->getKind())
        {
            case EX:
            {
                auto patchList = std::make_shared<PatchList>();
                auto ex = std::dynamic_pointer_cast<Ex>(exp);
                auto stm = IR::makeCJump(IR::EQ, ex->getEx(), IR::makeConst(1), nullptr, nullptr);
                patchList->push_front(std::dynamic_pointer_cast<IR::CJump>(stm));
                return std::make_shared<Cx>(patchList, stm);
            }
            case CX:
            {
                return std::dynamic_pointer_cast<Cx>(exp);
            }
            default:
            {
                Tiger::Error error("In unCx: exp should not be NX");
            }
        }
    }

    std::shared_ptr<Exp> getStaticLink(std::shared_ptr<Level> now, std::shared_ptr<Level> def)
    {
        std::shared_ptr<IR::Exp> addr = IR::makeTemp(Frame::getFP());
        auto nnow = now;
        while (nnow && (nnow != def->getParent()))
        {
            addr = Frame::getVariable(nnow->getFrame()->getFormals()->front(), addr);
            nnow = nnow->getParent();
        }
        return makeEx(addr);
    }

    std::shared_ptr<Exp> makeSimpleVar(std::shared_ptr<Access> access, std::shared_ptr<Level> level)
    {
        auto temp = Frame::getFP();
        auto addr = IR::makeTemp(temp);
        while (level != access->getLevel()->getParent())
        {
            auto frame = level->getFrame();
            auto formals = frame->getFormals();
            addr = Frame::getVariable(formals->front(), addr);
            level = level->getParent();
        }
        auto result = Frame::getVariable(access->getAccess(), addr);
        return makeEx(result);
    }

    std::shared_ptr<Exp> makeFieldVar(std::shared_ptr<Exp> base, int offset)
    {
        auto left = unEx(base);
        auto right = IR::makeConst(offset * Frame::WORD_SIZE);
        auto binop = IR::makeBinop(IR::PLUS, left, right);
        auto mem = IR::makeMem(binop);
        return makeEx(mem);
    }

    std::shared_ptr<Exp> makeSubscriptVar(std::shared_ptr<Exp> base, std::shared_ptr<Exp> index)
    {
        auto right = IR::makeConst(Frame::WORD_SIZE);
        auto left = unEx(index);
        auto right2 = IR::makeBinop(IR::PLUS, left, right);
        auto left2 = unEx(base);
        auto binop = IR::makeBinop(IR::PLUS, left2, right2);
        auto mem = IR::makeMem(binop);
        return makeEx(mem);
    }

    namespace
    {
        std::shared_ptr<Frame::FragList> stringFragList = std::make_shared<Frame::FragList>();
        std::shared_ptr<Frame::FragList> procFragList = std::make_shared<Frame::FragList>();
        std::shared_ptr<Temporary::Temp> nilTemp;
    }

    void procEntryExit(std::shared_ptr<Level> level, std::shared_ptr<Exp> body)
    {
        auto procBody = unNx(body);
        auto procFrame = level->getFrame();
        auto procFrag = Frame::makeProcFrag(procBody, procFrame);
        procFragList->push_front(procFrag);
    }

    std::shared_ptr<Exp> makeStringExp(const std::string &s)
    {
        auto label = Temporary::makeLabel();
        auto frag = Frame::makeStringFrag(label, s);
        stringFragList->push_front(frag);
        auto name = IR::makeName(label);
        return makeEx(name);
    }

    std::shared_ptr<Exp> makeIntExp(int i)
    {
        auto c = IR::makeConst(i);
        return makeEx(c);
    }

    std::shared_ptr<Exp> makeNilExp()
    {
        if (nullptr == nilTemp)
        {
            nilTemp = Temporary::makeTemp();
            auto dst = IR::makeTemp(nilTemp);
            auto src = Frame::makeExternalCall("initRecord", IR::makeExpList(IR::makeConst(0), nullptr));
            auto alloc = IR::makeMove(dst, src);
            auto eseq = IR::makeEseq(alloc, IR::makeTemp(nilTemp));
            return makeEx(eseq);
        }
        return makeEx(IR::makeTemp(nilTemp));
    }

    std::shared_ptr<Exp>
    makeCallExp(std::shared_ptr<Temporary::Label> label, std::shared_ptr<Level> usageLevel,
                std::shared_ptr<Level> defLevel,
                std::shared_ptr<ExpList> l)
    {
        auto entry = getStaticLink(usageLevel, defLevel);
        l->push_front(entry);
        IR::ExpList arglist;
        for (auto exp = l->begin(); exp != l->end(); exp++)
        {
            arglist.push_back(unEx(*exp));
        }
        auto args = std::make_shared<IR::ExpList>(arglist);
        auto name = IR::makeName(label);
        auto call2 = IR::makeCall(name, args);
        return makeEx(call2);
    }

    std::shared_ptr<Exp> makeRecordExp(int n, std::shared_ptr<ExpList> l)
    {
        auto r = Temporary::makeTemp();
        auto alloc = IR::makeMove(IR::makeTemp(r),
                                  Frame::makeExternalCall("initRecord", IR::makeExpList(
                                          IR::makeConst(n * Frame::WORD_SIZE), nullptr)));
        int i = n - 1;
        auto seq = IR::makeMove(
                IR::makeMem(IR::makeBinop(IR::PLUS, IR::makeTemp(r),
                                          IR::makeConst(i * Frame::WORD_SIZE))),
                unEx(l->front()));
        i--;
        for (auto exp = l->begin(); exp != l->end(); exp++, i--)
        {
            auto move = IR::makeMove(IR::makeMem(IR::makeBinop(IR::PLUS, IR::makeTemp(r),
                                                               IR::makeConst(i * Frame::WORD_SIZE))),
                                     unEx(*exp));
            seq = IR::makeSeq(move, seq);
        }
        auto eseq = IR::makeEseq(IR::makeSeq(alloc, seq), IR::makeTemp(r));
        return makeEx(eseq);
    }

    std::shared_ptr<Exp> makeArrayExp(std::shared_ptr<Exp> size, std::shared_ptr<Exp> init)
    {
        auto call = Frame::makeExternalCall("initArray",
                                            IR::makeExpList(unEx(size), IR::makeExpList(unEx(init), NULL)));
        return makeEx(call);
    }

    std::shared_ptr<Exp> makeSeqExp(std::shared_ptr<ExpList> l)
    {
        auto resl = unEx(l->front());
        auto exp = l->begin();
        exp++;
        for (; exp != l->end(); exp++)
        {
            resl = IR::makeEseq(IR::makeExp(unEx(*exp)), resl);
        }
        return makeEx(resl);
    }

    std::shared_ptr<Exp> makeDoneExp()
    {
        auto name = IR::makeName(Temporary::makeLabel());
        return makeEx(name);
    }

    std::shared_ptr<Exp> makeNonValueExp()
    {
        return makeEx(IR::makeConst(0));
    }

    std::shared_ptr<Exp> makeWhileExp(std::shared_ptr<Exp> test, std::shared_ptr<Exp> body, std::shared_ptr<Exp> done)
    {
        auto testLabel = Temporary::makeLabel();
        auto bodyLabel = Temporary::makeLabel();
        auto labelList = std::make_shared<IR::LabelList>();
        labelList->push_front(testLabel);
        auto doneLabel = std::dynamic_pointer_cast<IR::Name>(unEx(done))->getLabel();
        return makeEx(IR::makeEseq(IR::makeJump(IR::makeName(testLabel), labelList),
                                   IR::makeEseq(IR::makeLabel(bodyLabel),
                                                IR::makeEseq(unNx(body),
                                                             IR::makeEseq(IR::makeLabel(testLabel),
                                                                          IR::makeEseq(
                                                                                  IR::makeCJump(
                                                                                          IR::EQ,
                                                                                          unEx(test),
                                                                                          IR::makeConst(0),
                                                                                          doneLabel,
                                                                                          bodyLabel),
                                                                                  IR::makeEseq(
                                                                                          IR::makeLabel(
                                                                                                  bodyLabel),
                                                                                          IR::makeConst(
                                                                                                  0))))))));
    }


    std::shared_ptr<Exp> makeAssignExp(std::shared_ptr<Exp> lval, std::shared_ptr<Exp> exp)
    {
        return makeNx(IR::makeMove(unEx(lval), unEx(exp)));
    }

    std::shared_ptr<Exp> makeBreakExp(std::shared_ptr<Exp> b)
    {
        auto breakLabel = std::dynamic_pointer_cast<IR::Name>(unEx(b))->getLabel();
        auto labelList = std::make_shared<IR::LabelList>();
        labelList->push_front(breakLabel);
        return makeNx(IR::makeJump(IR::makeName(breakLabel), labelList));
    }

    std::shared_ptr<Exp> makeArithmeticExp(IR::ArithmeticOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right)
    {
        return makeEx(IR::makeBinop(op, unEx(left), unEx(right)));
    }

    std::shared_ptr<Exp>
    makeIntComparisonExp(IR::ComparisonOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right)
    {
        auto cond = IR::makeCJump(op, unEx(left), unEx(right), nullptr, nullptr);
        auto patchList = std::make_shared<PatchList>();
        patchList->push_front(std::dynamic_pointer_cast<IR::CJump>(cond));
        return makeCx(patchList, cond);
    }

    std::shared_ptr<Exp>
    makeStringComparisonExp(IR::ComparisonOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right)
    {
        auto resl = Frame::makeExternalCall(std::string("strcmp"),
                                            IR::makeExpList(unEx(left),
                                                            IR::makeExpList(unEx(right), nullptr)));
        auto zero = IR::makeConst(0);
        auto cond = IR::makeCJump(op, resl, zero, nullptr, nullptr);
        auto patchList = std::make_shared<PatchList>();
        patchList->push_front(std::dynamic_pointer_cast<IR::CJump>(cond));
        return makeCx(patchList, cond);
    }

    // TODO notice op must be EQ or NE
    std::shared_ptr<Exp>
    makeReferenceComparisonExp(IR::ComparisonOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right)
    {
        auto cond = IR::makeCJump(op, unEx(left), unEx(right), nullptr, nullptr);
        auto patchList = std::make_shared<PatchList>();
        patchList->push_front(std::dynamic_pointer_cast<IR::CJump>(cond));
        return makeCx(patchList, cond);
    }

    std::shared_ptr<Exp> makeIfExp(std::shared_ptr<Exp> test, std::shared_ptr<Exp> then, std::shared_ptr<Exp> elsee)
    {
        std::shared_ptr<Exp> result;
        auto t = Temporary::makeLabel();
        auto f = Temporary::makeLabel();
        auto cond = unCx(test);
        doPatch(cond->getPatchList(), t, f);
        if (elsee == nullptr)
        {
            switch (then->getKind())
            {
                case NX:
                    result = makeNx(IR::makeSeq(cond->getStm(),
                                                IR::makeSeq(IR::makeLabel(t),
                                                            IR::makeSeq(std::dynamic_pointer_cast<Nx>(
                                                                    then)->getNx(),
                                                                        IR::makeLabel(f)))));
                    break;
                case CX:
                    result = makeNx(IR::makeSeq(cond->getStm(),
                                                IR::makeSeq(IR::makeLabel(t),
                                                            IR::makeSeq(std::dynamic_pointer_cast<Cx>(
                                                                    then)->getStm(),
                                                                        IR::makeLabel(f)))));
                    break;
                case EX:
                    result = makeNx(IR::makeSeq(cond->getStm(),
                                                IR::makeSeq(IR::makeLabel(t),
                                                            IR::makeSeq(unEx(then),
                                                                        IR::makeLabel(f)))));
                    break;
                default:
                    Tiger::Error error("something wrong in [Translate::IfExp no else], type of [then] exp error");
            }
        }
        else
        {
            auto r = Temporary::makeTemp();
            auto join = Temporary::makeLabel();
            auto labelList = std::make_shared<IR::LabelList>();
            labelList->push_front(join);
            auto joinJump = IR::makeJump(IR::makeName(join), labelList);
            std::shared_ptr<IR::Stm> thenStm;
            switch (then->getKind())
            {
                case EX:
                    thenStm = IR::makeExp(std::dynamic_pointer_cast<Ex>(then)->getEx());
                    break;
                case NX:
                    thenStm = std::dynamic_pointer_cast<Nx>(then)->getNx();
                    break;
                case CX:
                    thenStm = std::dynamic_pointer_cast<Cx>(then)->getStm();
                    break;
                default:
                    Tiger::Error error("something wrong in Translate::IfExp in else in then");
            }

            std::shared_ptr<IR::Stm> elseeStm;
            switch (elsee->getKind())
            {
                case EX:
                    elseeStm = IR::makeExp(std::dynamic_pointer_cast<Ex>(elsee)->getEx());
                    break;
                case NX:
                    elseeStm = std::dynamic_pointer_cast<Nx>(elsee)->getNx();
                    break;
                case CX:
                    elseeStm = std::dynamic_pointer_cast<Cx>(elsee)->getStm();
                    break;
                default:
                    Tiger::Error error("something wrong in Translate::IfExp in else in elsee");
            }
            result = makeNx(IR::makeSeq(cond->getStm(),
                                        IR::makeSeq(IR::makeLabel(t),
                                                    IR::makeSeq(thenStm,
                                                                IR::makeSeq(joinJump,
                                                                            IR::makeSeq(
                                                                                    IR::makeLabel(
                                                                                            f),
                                                                                    IR::makeSeq(
                                                                                            elseeStm,
                                                                                            IR::makeSeq(
                                                                                                    joinJump,
                                                                                                    IR::makeLabel(
                                                                                                            join)))))))));
        }
        return result;
    }


    std::shared_ptr<Frame::FragList> getResult()
    {
        auto iter = procFragList->begin();
        for (; iter != procFragList->end(); iter++)
        {
            stringFragList->push_back(*iter);
        }
        return stringFragList;
    }

    std::shared_ptr<ExpList> makeExpList()
    {
        return std::make_shared<ExpList>();
    }


}
