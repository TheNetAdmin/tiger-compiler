//
// Created by PrinceXuan on 2017/5/29.
//

#ifndef _TIGER_SEMANTIC_H
#define _TIGER_SEMANTIC_H

#include <memory>
#include "absyntree.h"
#include "Translate.h"
#include "Types.h"
#include "Env.h"
#include <sstream>

namespace Semantic
{
    class ExpTy
    {
    public:
        std::shared_ptr<Translate::Exp> exp;
        std::shared_ptr<Type::Type> type;

        ExpTy();

        ExpTy(const shared_ptr<Translate::Exp> &exp, const shared_ptr<Type::Type> &type);

        void setExp(const shared_ptr<Translate::Exp> &exp);

        void setType(const shared_ptr<Type::Type> &type);
    };

    class SemanticError : public std::runtime_error
    {
    public:
        Tiger::location loc;

        explicit SemanticError(const Tiger::location &loc, const string &msg);
    };

    class TypeError : public SemanticError
    {
    public:
        string declareName;
        string expectTypeName;
        string actualTypeName;

        explicit TypeError(const Tiger::location &loc,
                           const string &msg);
    };

    class TypeNotMatchError : public TypeError
    {
    public:

        explicit TypeNotMatchError(const string &etName,
                                   const string &atName,
                                   const string &declareName,
                                   const Tiger::location &loc);

        explicit TypeNotMatchError(const string &etName,
                                   const string &atName,
                                   const Tiger::location &loc);
    };

    class TypeMatchError : public TypeError
    {
    public:
        explicit TypeMatchError(const string &actualTypeName,
                                const Tiger::location &loc);
    };

    class MatchError : public SemanticError
    {
    public:
        explicit MatchError(const Tiger::location &loc, const string &msg);
    };

    class ArgMatchError : public MatchError
    {
    public:
        Tiger::location loc;

        explicit ArgMatchError(const Tiger::location &loc, const string &msg);

    };

    class ArgTypeNotMatch : public ArgMatchError
    {
    public:
        explicit ArgTypeNotMatch(const Tiger::location &loc,
                                 const string &expectArgType,
                                 const string &usageArgType);
    };

    class ArgNumNotMatch : public ArgMatchError
    {
    public:
        explicit ArgNumNotMatch(const Tiger::location &loc,
                                const int &expectArgNum, const int &usageArgNum);

    };

    class RecordMatchError : public MatchError
    {
    public:
        explicit RecordMatchError(const Tiger::location &loc, const string &msg);
    };

    class RecordFieldNumNotMatch : public RecordMatchError
    {
    public:
        explicit RecordFieldNumNotMatch(const Tiger::location &loc,
                                        const int &expectFieldNum, const int &usageFieldNum);
    };

    class RecordTypeNotMatch : public RecordMatchError
    {
    public:
        explicit RecordTypeNotMatch(const Tiger::location &loc,
                                    const std::string &expectType,
                                    const std::string &usageType);
    };

    shared_ptr<Frame::FragList> transProg(std::shared_ptr<AST::Exp> exp);

    ExpTy transExp(shared_ptr<Translate::Level> level, shared_ptr<Translate::Exp> breakExp, Env::TypeEnv &typeEnv,
                   Env::VarEnv &varEnv, shared_ptr<AST::Exp> exp) noexcept(true);

    ExpTy transVar(shared_ptr<Translate::Level> level, shared_ptr<Translate::Exp> breakExp, Env::TypeEnv &typeEnv,
                   Env::VarEnv &varEnv, const shared_ptr<AST::Var> &var) noexcept(true);


    void checkCallArgs(shared_ptr<Translate::Level> level,
                       shared_ptr<Translate::Exp> breakExp,
                       Env::TypeEnv &typeEnv,
                       Env::VarEnv &varEnv,
                       const shared_ptr<AST::CallExp> usage,
                       const shared_ptr<Env::FuncEntry> def);


    void checkRecordEfields(shared_ptr<Translate::Level> level,
                            shared_ptr<Translate::Exp> breakExp,
                            Env::TypeEnv &typeEnv,
                            Env::VarEnv &varEnv,
                            shared_ptr<AST::RecordExp> usage,
                            shared_ptr<Env::TypeEntry> def);

    void assertTypeMatch(const shared_ptr<Type::Type> check,
                         const shared_ptr<Type::Type> base,
                         const std::string &declareName,
                         const Tiger::location &loc);

    void assertTypeMatch(const shared_ptr<Type::Type> check,
                         const shared_ptr<Type::Type> base,
                         const Tiger::location &loc);

    void assertTypeNotMatch(const shared_ptr<Type::Type> actualType,
                            const shared_ptr<Type::Type> assertType,
                            const Tiger::location &loc);

    shared_ptr<Translate::Exp> transDec(const shared_ptr<Translate::Level> level,
                                        const shared_ptr<Translate::Exp> breakExp,
                                        Env::TypeEnv &typeEnv,
                                        Env::VarEnv &varEnv,
                                        const shared_ptr<AST::Dec> dec);

    shared_ptr<Type::Type> transTy(Env::TypeEnv &typeEnv, const shared_ptr<AST::Ty> &ty);
};

#endif //_TIGER_SEMANTIC_H
