//
// Created by CHEGE on 2017/6/1.
//

#ifndef SRC_FRAME_H
#define SRC_FRAME_H

#include <memory>
#include <list>
#include <string>
#include "Temporary.h"
#include "IR.h"
#include "BoolList.h"

namespace Frame
{

    class Access;

    using AccessList= std::list<std::shared_ptr<Access>>;

    class Frame
    {
        std::shared_ptr<Temporary::Label> name;
        std::shared_ptr<AccessList> formals;
        int local_count;
    public:
        Frame(const std::shared_ptr<Temporary::Label> &name, const std::shared_ptr<AccessList> &formals,
              int local_count);

        const std::shared_ptr<Temporary::Label> getName() const;

        const std::shared_ptr<AccessList> getFormals() const;

        int getLocal_count() const;

        void increaseLocalCount();
    };


    enum AccessType
    {
        INFRAME, INREG
    };

    class Access
    {
        AccessType accessType;
    public:
        Access(AccessType accessType);

        virtual ~Access();

        AccessType getAccessType() const;
    };


    class AccessFrame : public Access
    {
        int offset;
    public:
        AccessFrame(int offset);

        int getOffset() const;
    };


    class AccessReg : public Access
    {
        std::shared_ptr<Temporary::Temp> reg;
    public:
        AccessReg(const std::shared_ptr<Temporary::Temp> &reg);

        const std::shared_ptr<Temporary::Temp> getReg() const;
    };


    std::shared_ptr<Frame> makeFrame(std::shared_ptr<Temporary::Label> name, std::shared_ptr<BoolList> formals);

    std::shared_ptr<Access> allocLocalVarible(std::shared_ptr<Frame> f, bool escape);

    /* IR */
    enum FragType
    {
        F_STRING_FRAG, F_PROC_FRAG
    };

    class Frag
    {
        FragType kind;
    public:
        Frag(FragType kind);

        virtual ~Frag();;

        FragType getKind() const;
    };

    class StringFrag : public Frag
    {
        std::shared_ptr<Temporary::Label> label;
        std::string str;
    public:
        StringFrag(const std::shared_ptr<Temporary::Label> &label, const std::string &str);

        const std::shared_ptr<Temporary::Label> getLabel() const;

        const std::string getStr() const;
    };

    class ProcFrag : public Frag
    {
        std::shared_ptr<IR::Stm> body;
        std::shared_ptr<Frame> frame;
    public:
        ProcFrag(const std::shared_ptr<IR::Stm> &body, const std::shared_ptr<Frame> &frame);

        const std::shared_ptr<IR::Stm> getBody() const;

        const std::shared_ptr<Frame> getFrame() const;
    };

    using FragList = std::list<std::shared_ptr<Frag>>;


    namespace
    {
        const int WORD_SIZE = 4;
        const int MAX_REG = 6;
    }

    std::shared_ptr<Frag> makeStringFrag(std::shared_ptr<Temporary::Label> label, const std::string &str);

    std::shared_ptr<Frag> makeProcFrag(std::shared_ptr<IR::Stm> body, std::shared_ptr<Frame> frame);

    std::shared_ptr<FragList> makeFragList(std::shared_ptr<Frag> head, std::shared_ptr<FragList> tail);

    std::shared_ptr<Temporary::Temp> getFP();

    std::shared_ptr<IR::Exp> getVariable(std::shared_ptr<Access> access, std::shared_ptr<IR::Exp> framePtr);

    std::shared_ptr<IR::Exp> makeExternalCall(std::string str, std::shared_ptr<IR::ExpList> args);

}


#endif //SRC_FRAME_H
