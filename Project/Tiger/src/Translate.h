//
// Created by Chege on 2017/6/2.
//

#ifndef SRC_TRANSLATE_H
#define SRC_TRANSLATE_H

#include <memory>
#include <list>
#include "IR.h"
#include "Temporary.h"
#include "Frame.h"
#include "BoolList.h"
#include "Error.h"

namespace Translate
{

    class Access;

    typedef std::list<std::shared_ptr<Access>> AccessList;

    class Level
    {
        std::shared_ptr<Level> parent;
        std::shared_ptr<Temporary::Label> name;
        std::shared_ptr<Frame::Frame> frame;
        std::shared_ptr<AccessList> formals;
    public:
        Level(const std::shared_ptr<Level> &parent, const std::shared_ptr<Temporary::Label> &name,
              const std::shared_ptr<Frame::Frame> &frame, const std::shared_ptr<AccessList> &formals);

        const std::shared_ptr<Level> getParent() const;

        const std::shared_ptr<Temporary::Label> getName() const;

        const std::shared_ptr<Frame::Frame> getFrame() const;

        const std::shared_ptr<AccessList> getFormals() const;

        void Level::setFormals(const std::shared_ptr<AccessList> &formals);
    };

    class Access
    {
        std::shared_ptr<Level> level;
        std::shared_ptr<Frame::Access> access;
    public:
        Access(const std::shared_ptr<Level> &level, const std::shared_ptr<Frame::Access> &access);

        const std::shared_ptr<Level> getLevel() const;

        const std::shared_ptr<Frame::Access> getAccess() const;
    };


    std::shared_ptr<Level> getGlobalLevel(void);

    std::shared_ptr<Level> makeNewLevel(std::shared_ptr<Level> parent, std::shared_ptr<Temporary::Label> name,
                                        std::shared_ptr<BoolList> formals);

    std::shared_ptr<Access> allocLocal(std::shared_ptr<Level> level, bool escape);

    /* ----------------IR------------------ */

    enum ExpType
    {
        EX, NX, CX
    };

    class Exp
    {
        ExpType kind;
    public:
        Exp(ExpType kind);

        virtual ~Exp();

        ExpType getKind() const;
    };

    class Ex : public Exp
    {
        std::shared_ptr<IR::Exp> ex;
    public:
        Ex(const std::shared_ptr<IR::Exp> &ex);

        const std::shared_ptr<IR::Exp> getEx() const;
    };

    class Nx : public Exp
    {
        std::shared_ptr<IR::Stm> nx;
    public:
        Nx(const std::shared_ptr<IR::Stm> &nx);

        const std::shared_ptr<IR::Stm> getNx() const;
    };

    typedef std::list<std::shared_ptr<IR::CJump>> PatchList;

    class Cx : public Exp
    {
        std::shared_ptr<PatchList> patchList;
        std::shared_ptr<IR::Stm> stm;
    public:

        Cx(const std::shared_ptr<PatchList> &patchList, const std::shared_ptr<IR::Stm> &stm);

        const std::shared_ptr<PatchList> getPatchList() const;

        const std::shared_ptr<IR::Stm> getStm() const;
    };

    typedef std::list<std::shared_ptr<Exp>> ExpList;

    // ----------------------------------------------------------

    std::shared_ptr<Exp> makeSimpleVar(std::shared_ptr<Access> access, std::shared_ptr<Level> level);

    std::shared_ptr<Exp> makeFieldVar(std::shared_ptr<Exp> base, int offset);

    std::shared_ptr<Exp> makeSubscriptVar(std::shared_ptr<Exp> base, std::shared_ptr<Exp> index);

    std::shared_ptr<Exp> makeStringExp(const std::string &s);

    std::shared_ptr<Exp> makeIntExp(int i);

    std::shared_ptr<Exp> makeNonValueExp();

    std::shared_ptr<Exp>
    makeCallExp(std::shared_ptr<Temporary::Label> label, std::shared_ptr<Level> fun, std::shared_ptr<Level> call,
                std::shared_ptr<ExpList> l);

    std::shared_ptr<Exp> makeNilExp();

    std::shared_ptr<Exp> makeRecordExp(int n, std::shared_ptr<ExpList> l);

    std::shared_ptr<Exp> makeArrayExp(std::shared_ptr<Exp> size, std::shared_ptr<Exp> init);

    std::shared_ptr<Exp> makeSeqExp(std::shared_ptr<ExpList> l);

    std::shared_ptr<Exp> makeDoneExp();

    // ----------------------------------------------------------

    std::shared_ptr<Exp> makeWhileExp(std::shared_ptr<Exp> test, std::shared_ptr<Exp> body, std::shared_ptr<Exp> done);

    std::shared_ptr<Exp> makeAssignExp(std::shared_ptr<Exp> lval, std::shared_ptr<Exp> exp);

    std::shared_ptr<Exp> makeBreakExp(std::shared_ptr<Exp> b);

    std::shared_ptr<Exp>
    makeArithmeticExp(IR::ArithmeticOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right);

    std::shared_ptr<Exp>
    makeIntComparisonExp(IR::ComparisonOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right);

    std::shared_ptr<Exp>
    makeStringComparisonExp(IR::ComparisonOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right);

    std::shared_ptr<Exp>
    makeReferenceComparisonExp(IR::ComparisonOp op, std::shared_ptr<Exp> left, std::shared_ptr<Exp> right);


    std::shared_ptr<Exp> makeIfExp(std::shared_ptr<Exp> test, std::shared_ptr<Exp> then, std::shared_ptr<Exp> elsee);

    std::shared_ptr<ExpList> makeExpList();

    void procEntyExit(std::shared_ptr<Level>, std::shared_ptr<Exp>);

    std::shared_ptr<Frame::FragList> getResult();

    std::shared_ptr<Exp> makeEx(const std::shared_ptr<IR::Exp> &ex);
}

#endif //SRC_TRANSLATE_H
