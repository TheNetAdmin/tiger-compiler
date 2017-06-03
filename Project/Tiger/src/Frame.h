//
// Created by CHEGE on 2017/6/1.
//

#ifndef SRC_FRAME_H
#define SRC_FRAME_H

#include <memory>
#include <list>
#include <string>
#include "Temporary.h"
#include "IRTree.h"
#include "BoolList.h"

namespace Frame
{

    class FAccess;

    typedef std::list<std::shared_ptr<FAccess>> FAccessList;

    class FFrame
    {
        std::shared_ptr<Temporary::Label> name;
        std::shared_ptr<FAccessList> formals;
        int local_count;
    public:
        FFrame(const std::shared_ptr<Temporary::Label> &name, const std::shared_ptr<FAccessList> &formals,
               int local_count);

        const std::shared_ptr<Temporary::Label> getName() const;

        const std::shared_ptr<FAccessList> getFormals() const;

        int getLocal_count() const;

        void increaseLocalCount();
    };


    enum FAccessType
    {
        INFRAME, INREG
    };

    class FAccess
    {
        FAccessType accessType;
    public:
        FAccess(FAccessType accessType);

        virtual ~FAccess();

        FAccessType getAccessType() const;
    };


    class FAccessFrame : public FAccess
    {
        int offset;
    public:
        FAccessFrame(int offset);

        int getOffset() const;
    };


    class FAccessReg : public FAccess
    {
        std::shared_ptr<Temporary::Temp> reg;
    public:
        FAccessReg(const std::shared_ptr<Temporary::Temp> &reg);

        const std::shared_ptr<Temporary::Temp> getReg() const;
    };


    std::shared_ptr<FFrame> makeFrame(std::shared_ptr<Temporary::Label> name, std::shared_ptr<BoolList> formals);

    std::shared_ptr<FAccess> allocLocalVarible(std::shared_ptr<FFrame> f, bool escape);

    /* IR */
    enum FFragType
    {
        F_STRING_FRAG, F_PROC_FRAG
    };

    class FFrag
    {
        FFragType kind;
    public:
        FFrag(FFragType kind);

        virtual ~FFrag();;

        FFragType getKind() const;
    };

    class FStringFrag : public FFrag
    {
        std::shared_ptr<Temporary::Label> label;
        std::string str;
    public:
        FStringFrag(const std::shared_ptr<Temporary::Label> &label, const std::string &str);

        const std::shared_ptr<Temporary::Label> getLabel() const;

        const std::string getStr() const;
    };

    class FProcFrag : public FFrag
    {
        std::shared_ptr<IRTree::Stm> body;
        std::shared_ptr<FFrame> frame;
    public:
        FProcFrag(const std::shared_ptr<IRTree::Stm> &body, const std::shared_ptr<FFrame> &frame);

        const std::shared_ptr<IRTree::Stm> getBody() const;

        const std::shared_ptr<FFrame> getFrame() const;
    };

    typedef std::list<std::shared_ptr<FFrag>> FFragList;

    extern const int F_WORD_SIZE;

    std::shared_ptr<FFrag> makeFStringFrag(std::shared_ptr<Temporary::Label> label, std::string &str);

    std::shared_ptr<FFrag> makeFProcFrag(std::shared_ptr<IRTree::Stm> body, std::shared_ptr<FFrame> frame);

    std::shared_ptr<FFragList> makeFFragList(std::shared_ptr<FFrag> head, std::shared_ptr<FFragList> tail);

    std::shared_ptr<Temporary::Temp> getFFP();

    std::shared_ptr<IRTree::Exp> getFVarible(std::shared_ptr<FAccess> access, std::shared_ptr<IRTree::Exp> framePtr);

    std::shared_ptr<IRTree::Exp> makeFExternalCall(std::string str, std::shared_ptr<IRTree::ExpList> args);
//    std::shared_ptr<IRTree::Stm> FProcEntryExit

}


#endif //SRC_FRAME_H
