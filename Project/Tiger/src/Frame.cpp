//
// Created by CHEGE on 2017/6/1.
//

#include "Frame.h"


namespace Frame
{
    const int F_WORD_SIZE = 4;  /* 4byte */
    static const int F_MAX_REG = 6;  /* paras in regs number */

    FFrame::FFrame(const std::shared_ptr<Temporary::Label> &name, const std::shared_ptr<FAccessList> &formals,
                   int local_count) : name(name), formals(formals), local_count(local_count)
    {}

    const std::shared_ptr<Temporary::Label> FFrame::getName() const
    {
        return name;
    }

    const std::shared_ptr<FAccessList> FFrame::getFormals() const
    {
        return formals;
    }

    int FFrame::getLocal_count() const
    {
        return local_count;
    }

    void FFrame::increaseLocalCount()
    {
        local_count += 1;
    }

    FAccess::FAccess(FAccessType accessType) : accessType(accessType)
    {}

    FAccessType FAccess::getAccessType() const
    {
        return accessType;
    }

    FAccess::~FAccess()
    {}


    FAccessFrame::FAccessFrame(int offset) : FAccess(INFRAME), offset(offset)
    {}

    int FAccessFrame::getOffset() const
    {
        return offset;
    }

    FAccessReg::FAccessReg(const std::shared_ptr<Temporary::Temp> &reg) : FAccess(INREG), reg(reg)
    {}

    const std::shared_ptr<Temporary::Temp> FAccessReg::getReg() const
    {
        return reg;
    }


    std::shared_ptr<FAccess> MakeFAccessFrame(int offset)
    {
        return std::make_shared<FAccessFrame>(offset);
    }

    std::shared_ptr<FAccess> MakeFAccessReg(std::shared_ptr<Temporary::Temp> reg)
    {
        return std::make_shared<FAccessReg>(reg);
    }


    std::shared_ptr<FAccessList> MakeFormalAccessList(std::shared_ptr<BoolList> formals)
    {
        std::list<bool>::iterator iter = formals->begin();
        std::shared_ptr<FAccessList> accessList = std::make_shared<FAccessList>();

        for (int i = 0; iter != formals->end(); i++, iter++)
        {
            std::shared_ptr<FAccess> access;
            if (i < F_MAX_REG && !formals->front())
            {
                access = MakeFAccessReg(Temporary::makeTemp());
            }
            else
            {
                access = MakeFAccessFrame(i * F_WORD_SIZE);
            }
            accessList->push_back(access);
        }

        return accessList;
    }

    std::shared_ptr<FFrame> makeFrame(std::shared_ptr<Temporary::Label> name, std::shared_ptr<BoolList> formals)
    {
        return std::make_shared<FFrame>(name, MakeFormalAccessList(formals), 0);
    }

    std::shared_ptr<FAccess> allocLocalVarible(std::shared_ptr<FFrame> f, bool escape)
    {
        f->increaseLocalCount();
        if (escape)
        {
            return MakeFAccessFrame(-1 * F_WORD_SIZE * f->getLocal_count());
        }
        return MakeFAccessReg(Temporary::makeTemp());
    }

    /* IR */


    std::shared_ptr<FFrag> makeFStringFrag(std::shared_ptr<Temporary::Label> label, std::string &str)
    {
        return std::make_shared<FStringFrag>(label, str);
    }

    std::shared_ptr<FFrag> makeFProcFrag(std::shared_ptr<IRTree::Stm> body, std::shared_ptr<FFrame> frame)
    {
        return std::make_shared<FProcFrag>(body, frame);
    }

    std::shared_ptr<FFragList> makeFFragList(std::shared_ptr<FFrag> head, std::shared_ptr<FFragList> tail)
    {
        if (tail == nullptr)
        {
            tail = std::make_shared<FFragList>();
        }
        tail->push_front(head);
        return tail;
    }

    static std::shared_ptr<Temporary::Temp> fp = nullptr;

    std::shared_ptr<Temporary::Temp> getFFP()
    {
        if (fp == nullptr)
        {
            fp = Temporary::makeTemp();
        }
        return fp;
    }

    std::shared_ptr<IRTree::Exp> getFVarible(std::shared_ptr<FAccess> access, std::shared_ptr<IRTree::Exp> framePtr)
    {
        if (access->getAccessType() == INFRAME)
        {
            return IRTree::makeMem(
                    IRTree::makeBinop(
                            IRTree::PLUS, framePtr, IRTree::makeConst(
                                    std::dynamic_pointer_cast<FAccessFrame>(access)->getOffset()
                            )
                    )
            );
        }
        else
        {
            return IRTree::makeTemp(
                    std::dynamic_pointer_cast<FAccessReg>(access)->getReg()
            );
        }
    }

    std::shared_ptr<IRTree::Exp> makeFExternalCall(std::string str, std::shared_ptr<IRTree::ExpList> args)
    {
        return IRTree::makeCall(IRTree::makeName(Temporary::makeLabel(str)), args);
    }


    FFrag::FFrag(FFragType kind) : kind(kind)
    {}

    FFrag::~FFrag()
    {}

    FFragType FFrag::getKind() const
    {
        return kind;
    }

    FStringFrag::FStringFrag(const std::shared_ptr<Temporary::Label> &label, const std::string &str) : FFrag(
            F_STRING_FRAG),
                                                                                                       label(label),
                                                                                                       str(str)
    {}

    const std::shared_ptr<Temporary::Label> FStringFrag::getLabel() const
    {
        return label;
    }

    const std::string FStringFrag::getStr() const
    {
        return str;
    }

    FProcFrag::FProcFrag(const std::shared_ptr<IRTree::Stm> &body, const std::shared_ptr<FFrame> &frame)
            : FFrag(F_PROC_FRAG), body(body), frame(frame)
    {}

    const std::shared_ptr<IRTree::Stm> FProcFrag::getBody() const
    {
        return body;
    }

    const std::shared_ptr<FFrame> FProcFrag::getFrame() const
    {
        return frame;
    }


}
