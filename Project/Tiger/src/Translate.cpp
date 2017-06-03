//
// Created by Chege on 2017/6/2.
//

#include "Translate.h"
#include "IRTree.h"

namespace Translate
{


    Level::Level(const std::shared_ptr<Level> &parent, const std::shared_ptr<Temporary::Label> &name,
                 const std::shared_ptr<Frame::FFrame> &frame, const std::shared_ptr<AccessList> &formals) : parent(
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

    const std::shared_ptr<Frame::FFrame> Level::getFrame() const
    {
        return frame;
    }

    const std::shared_ptr<AccessList> Level::getFormals() const
    {
        return formals;
    }

    Access::Access(const std::shared_ptr<Level> &level, const std::shared_ptr<Frame::FAccess> &access) : level(level),
                                                                                                         access(access)
    {}

    const std::shared_ptr<Level> Access::getLevel() const
    {
        return level;
    }

    const std::shared_ptr<Frame::FAccess> Access::getAccess() const
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

    Ex::Ex(const std::shared_ptr<IRTree::Exp> &ex) : Exp(EX), ex(ex)
    {}

    const std::shared_ptr<IRTree::Exp> Ex::getEx() const
    {
        return ex;
    }

    Nx::Nx(const std::shared_ptr<IRTree::Stm> &nx) : Exp(NX), nx(nx)
    {}

    const std::shared_ptr<IRTree::Stm> Nx::getNx() const
    {
        return nx;
    }

    Cx::Cx(const std::shared_ptr<PatchList> &patchList, const std::shared_ptr<IRTree::Stm> &stm)
            : Exp(CX), patchList(patchList), stm(stm)
    {}

    const std::shared_ptr<PatchList> Cx::getPatchList() const
    {
        return patchList;
    }

    const std::shared_ptr<IRTree::Stm> Cx::getStm() const
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

    /* IR */
    std::shared_ptr<Exp> makeEx(const std::shared_ptr<IRTree::Exp> &exp)
    {
        return std::make_shared<Ex>(exp);
    }

    std::shared_ptr<Exp> makeNx(std::shared_ptr<IRTree::Stm> stm)
    {
        return std::make_shared<Nx>(stm);
    }

    std::shared_ptr<Exp>
    makeCx(std::shared_ptr<PatchList> patchList, std::shared_ptr<IRTree::Stm> stm)
    {
        return std::make_shared<Cx>(patchList, stm);
    }

    std::shared_ptr<PatchList> patchList(std::shared_ptr<IRTree::CJump> head, std::shared_ptr<PatchList> tail)
    {
        if (tail == nullptr)
        {
            tail = std::make_shared<PatchList>();
        }
        tail->push_front(head);
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


    std::shared_ptr<IRTree::Exp> unEx(std::shared_ptr<Exp> exp)
    {
        switch (exp->getKind())
        {
            case EX:
                return std::dynamic_pointer_cast<Ex>(exp)->getEx();
            case NX:
                return IRTree::makeEseq(std::dynamic_pointer_cast<Nx>(exp)->getNx(), IRTree::makeConst(0));
            case CX:
            {
                auto r = Temporary::makeTemp();
                auto t = Temporary::makeLabel();
                auto f = Temporary::makeLabel();
                auto cx = std::dynamic_pointer_cast<Cx>(exp);
                doPatch(cx->getPatchList(), t, f);
                return IRTree::makeEseq(IRTree::makeMove(IRTree::makeTemp(r), IRTree::makeConst(1)),
                                        IRTree::makeEseq(cx->getStm(),
                                                         IRTree::makeEseq(IRTree::makeLabel(f),
                                                                          IRTree::makeEseq(IRTree::makeMove(
                                                                                  IRTree::makeTemp(r),
                                                                                  IRTree::makeConst(0)),
                                                                                           IRTree::makeEseq(
                                                                                                   IRTree::makeLabel(t),
                                                                                                   IRTree::makeTemp(
                                                                                                           r))))));
            }
            default:
                Tiger::Error error("something wrong in Translate::unEx");
        }
    }

    std::shared_ptr<IRTree::Stm> unNx(std::shared_ptr<Exp> exp)
    {
        switch (exp->getKind())
        {
            case EX:
                return IRTree::makeExp(std::dynamic_pointer_cast<Ex>(exp)->getEx());
            case NX:
                return std::dynamic_pointer_cast<Nx>(exp)->getNx();
            case CX:
                return IRTree::makeExp(unEx(exp));
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
                auto stm = IRTree::makeCJump(IRTree::EQ, ex->getEx(), IRTree::makeConst(1), nullptr, nullptr);
                patchList->push_front(std::dynamic_pointer_cast<IRTree::CJump>(stm));
                return std::make_shared<Cx>(patchList, stm);
            }
            case CX:
            {
                return std::dynamic_pointer_cast<Cx>(exp);
            }
            default:
            {
                Tiger::Error error("something wrong in Translate::unCx");
            }
        }
    }

    std::shared_ptr<Exp> getStaticLink(std::shared_ptr<Level> now, std::shared_ptr<Level> def)
    {
        std::shared_ptr<IRTree::Exp> addr = IRTree::makeTemp(Frame::getFFP());
        auto nnow = now;
        while (nnow && (nnow != def->getParent()))
        {
            addr = Frame::getFVarible(nnow->getFrame()->getFormals()->front(), addr);
            nnow = nnow->getParent();
        }
        return makeEx(addr);
    }

    std::shared_ptr<Exp> makeSimpleVar(std::shared_ptr<Access> access, std::shared_ptr<Level> level)
    {
        auto temp = Frame::getFFP();
        auto addr = IRTree::makeTemp(temp);
        while (level != access->getLevel()->getParent())
        {
            auto frame = level->getFrame();
            auto formals = frame->getFormals();
            addr = Frame::getFVarible(formals->front(), addr);
            level = level->getParent();
        }
        auto result = Frame::getFVarible(access->getAccess(), addr);
        return makeEx(result);
    }

    std::shared_ptr<Exp> makeFieldVar(std::shared_ptr<Exp> base, int offset)
    {
        auto left = unEx(base);
        auto right = IRTree::makeConst(offset * Frame::F_WORD_SIZE);
        auto binop = IRTree::makeBinop(IRTree::PLUS, left, right);
        auto mem = IRTree::makeMem(binop);
        return makeEx(mem);
    }

    std::shared_ptr<Exp> makeSubscriptVar(std::shared_ptr<Exp> base, std::shared_ptr<Exp> index)
    {
        auto right = IRTree::makeConst(Frame::F_WORD_SIZE);
        auto left = unEx(index);
        auto right2 = IRTree::makeBinop(IRTree::PLUS, left, right);
        auto left2 = unEx(base);
        auto binop = IRTree::makeBinop(IRTree::PLUS, left2, right2);
        auto mem = IRTree::makeMem(binop);
        return makeEx(mem);
    }

    namespace
    {
        Frame::FFragList stringFragList;
        Frame::FFragList procFragList;
        std::shared_ptr<Temporary::Temp> nilTemp;
    }

    void procEntyExit(std::shared_ptr<Level> level, std::shared_ptr<Exp> body)
    {
        auto procBody = unNx(body);
        auto procFrame = level->getFrame();
        auto procFrag = Frame::makeFProcFrag(procBody, procFrame);
        procFragList.push_front(procFrag);
    }

    std::shared_ptr<Exp> makeStringExp(std::string &s)
    {
        auto label = Temporary::makeLabel();
        auto frag = Frame::makeFStringFrag(label, s);
        stringFragList.push_front(frag);
        auto name = IRTree::makeName(label);
        return makeEx(name);
    }

    std::shared_ptr<Exp> makeIntExp(int i)
    {
        auto c = IRTree::makeConst(i);
        return makeEx(c);
    }

    std::shared_ptr<Exp> makeNilExp()
    {
        if (nullptr == nilTemp)
        {
            nilTemp = Temporary::makeTemp();
            auto dst = IRTree::makeTemp(nilTemp);
            auto src = Frame::makeFExternalCall("initRecord", IRTree::makeExpList(IRTree::makeConst(0), nullptr));
            auto alloc = IRTree::makeMove(dst, src);
            auto eseq = IRTree::makeEseq(alloc, IRTree::makeTemp(nilTemp));
            return makeEx(eseq);
        }
    }

    std::shared_ptr<Exp>
    makeCallExp(std::shared_ptr<Temporary::Label> label, std::shared_ptr<Level> fun, std::shared_ptr<Level> call,
                std::shared_ptr<ExpList> l)
    {
        auto entry = getStaticLink(call, fun);
        l->push_front(entry);
        IRTree::ExpList arglist;
        for (auto exp = l->begin(); exp != l->end(); exp++)
        {
            arglist.push_back(unEx(*exp));
        }
        auto args = std::make_shared<IRTree::ExpList>(arglist);
        auto name = IRTree::makeName(label);
        auto call2 = IRTree::makeCall(name, args);
        return makeEx(call2);
    }

    std::shared_ptr<Exp> makeRecordExp(int n, std::shared_ptr<ExpList> l)
    {
        auto r = Temporary::makeTemp();
        auto alloc = IRTree::makeMove(IRTree::makeTemp(r),
                                      Frame::makeFExternalCall("initRecord", IRTree::makeExpList(
                                              IRTree::makeConst(n * Frame::F_WORD_SIZE), nullptr)));
        int i = n - 1;
        auto seq = IRTree::makeMove(
                IRTree::makeMem(IRTree::makeBinop(IRTree::PLUS, IRTree::makeTemp(r),
                                                  IRTree::makeConst(i * Frame::F_WORD_SIZE))),
                unEx(l->front()));
        i--;
        for (auto exp = l->begin(); exp != l->end(); exp++, i--)
        {
            auto move = IRTree::makeMove(IRTree::makeMem(IRTree::makeBinop(IRTree::PLUS, IRTree::makeTemp(r),
                                                                           IRTree::makeConst(i * Frame::F_WORD_SIZE))),
                                         unEx(*exp));
            seq = IRTree::makeSeq(move, seq);
        }
        auto eseq = IRTree::makeEseq(IRTree::makeSeq(alloc, seq), IRTree::makeTemp(r));
        return makeEx(eseq);
    }

    std::shared_ptr<Exp> makeArrayExp(std::shared_ptr<Exp> size, std::shared_ptr<Exp> init)
    {
        auto call = Frame::makeFExternalCall("initArray",
                                             IRTree::makeExpList(unEx(size), IRTree::makeExpList(unEx(init), NULL)));
        return makeEx(call);
    }

    std::shared_ptr<Exp> makeSeqExp(std::shared_ptr<ExpList> l)
    {
        auto resl = unEx(l->front());
        for (auto exp = l->begin(); exp != l->end(); exp++)
        {
            resl = IRTree::makeEseq(IRTree::makeExp(unEx(*exp)), resl);
        }
        return makeEx(resl);
    }

    std::shared_ptr<Exp> makeDoneExp()
    {
        auto name = IRTree::makeName(Temporary::makeLabel());
        return makeEx(name);
    }

    std::shared_ptr<Exp> makeNonValueExp()
    {
        return makeEx(IRTree::makeConst(0));
    }


}
