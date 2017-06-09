//
// Created by CHEGE on 2017/6/1.
//

#include "Frame.h"


namespace Frame
{

    Frame::Frame(const std::shared_ptr<Temporary::Label> &name, const std::shared_ptr<AccessList> &formals,
                 int local_count)
            : name(name), formals(formals), local_count(local_count)
    {}

    const std::shared_ptr<Temporary::Label> Frame::getName() const
    {
        return name;
    }

    const std::shared_ptr<AccessList> Frame::getFormals() const
    {
        return formals;
    }

    int Frame::getLocal_count() const
    {
        return local_count;
    }

    void Frame::increaseLocalCount()
    {
        local_count += 1;
    }

    Access::Access(AccessType accessType)
            : accessType(accessType)
    {}

    AccessType Access::getAccessType() const
    {
        return accessType;
    }

    Access::~Access()
    {}


    AccessFrame::AccessFrame(int offset)
            : Access(IN_FRAME), offset(offset)
    {}

    int AccessFrame::getOffset() const
    {
        return offset;
    }

    AccessReg::AccessReg(const std::shared_ptr<Temporary::Temp> &reg)
            : Access(IN_REG), reg(reg)
    {}

    const std::shared_ptr<Temporary::Temp> AccessReg::getReg() const
    {
        return reg;
    }


    std::shared_ptr<Access> MakeFAccessFrame(int offset)
    {
        return std::make_shared<AccessFrame>(offset);
    }

    std::shared_ptr<Access> MakeFAccessReg(std::shared_ptr<Temporary::Temp> reg)
    {
        return std::make_shared<AccessReg>(reg);
    }


    std::shared_ptr<AccessList> MakeFormalAccessList(std::shared_ptr<BoolList> formals)
    {
        std::list<bool>::iterator iter = formals->begin();
        std::shared_ptr<AccessList> accessList = std::make_shared<AccessList>();

        for (int i = 0; iter != formals->end(); i++, iter++)
        {
            std::shared_ptr<Access> access;
            if (i < MAX_REG && !formals->front())
            {
                access = MakeFAccessReg(Temporary::makeTemp());
            }
            else
            {
                access = MakeFAccessFrame(i * WORD_SIZE);
            }
            accessList->push_back(access);
        }

        return accessList;
    }

    std::shared_ptr<Frame> makeFrame(std::shared_ptr<Temporary::Label> name, std::shared_ptr<BoolList> formals)
    {
        return std::make_shared<Frame>(name, MakeFormalAccessList(formals), 0);
    }

    std::shared_ptr<Access> allocLocalVariable(std::shared_ptr<Frame> f, bool escape)
    {
        f->increaseLocalCount();
        if (escape)
        {
            return MakeFAccessFrame(-1 * WORD_SIZE * f->getLocal_count());
        }
        return MakeFAccessReg(Temporary::makeTemp());
    }

    /* IR */


    std::shared_ptr<Frag> makeStringFrag(std::shared_ptr<Temporary::Label> label, const std::string &str)
    {
        return std::make_shared<StringFrag>(label, str);
    }

    std::shared_ptr<Frag> makeProcFrag(std::shared_ptr<IR::Stm> body, std::shared_ptr<Frame> frame)
    {
        return std::make_shared<ProcFrag>(body, frame);
    }

    std::shared_ptr<FragList> makeFragList(std::shared_ptr<Frag> head, std::shared_ptr<FragList> tail)
    {
        if (tail == nullptr)
        {
            tail = std::make_shared<FragList>();
        }
        tail->push_front(head);
        return tail;
    }

    static std::shared_ptr<Temporary::Temp> fp = nullptr;

    std::shared_ptr<Temporary::Temp> getFP()
    {
        if (fp == nullptr)
        {
            fp = Temporary::makeTemp();
        }
        return fp;
    }

    std::shared_ptr<IR::Exp> getVariable(std::shared_ptr<Access> access, std::shared_ptr<IR::Exp> framePtr)
    {
        if (access->getAccessType() == IN_FRAME)
        {
            return IR::makeMem(
                    IR::makeBinop(
                            IR::PLUS, framePtr, IR::makeConst(
                                    std::dynamic_pointer_cast<AccessFrame>(access)->getOffset()
                            )
                    )
            );
        }
        else
        {
            return IR::makeTemp(
                    std::dynamic_pointer_cast<AccessReg>(access)->getReg()
            );
        }
    }

    std::shared_ptr<IR::Exp> makeExternalCall(std::string str, std::shared_ptr<IR::ExpList> args)
    {
        return IR::makeCall(IR::makeName(Temporary::makeLabel(str)), args);
    }


    Frag::Frag(FragType kind) : kind(kind)
    {}

    Frag::~Frag()
    {}

    FragType Frag::getKind() const
    {
        return kind;
    }

    StringFrag::StringFrag(const std::shared_ptr<Temporary::Label> &label, const std::string &str)
            : Frag(STRING_FRAG), label(label), str(str)
    {}

    const std::shared_ptr<Temporary::Label> StringFrag::getLabel() const
    {
        return label;
    }

    const std::string StringFrag::getStr() const
    {
        return str;
    }

    ProcFrag::ProcFrag(const std::shared_ptr<IR::Stm> &body, const std::shared_ptr<Frame> &frame)
            : Frag(PROC_FRAG), body(body), frame(frame)
    {}

    const std::shared_ptr<IR::Stm> ProcFrag::getBody() const
    {
        return body;
    }

    const std::shared_ptr<Frame> ProcFrag::getFrame() const
    {
        return frame;
    }


}
