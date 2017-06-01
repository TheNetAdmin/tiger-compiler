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

        ExpTy()
        {}

        ExpTy(const shared_ptr<Translate::Exp> &exp, const shared_ptr<Type::Type> &type)
                : exp(exp), type(type)
        {}

        void setExp(const shared_ptr<Translate::Exp> &exp)
        {
            this->exp = exp;
        }

        void setType(const shared_ptr<Type::Type> &type)
        {
            this->type = type;
        }
    };

    class SemanticError : public std::runtime_error
    {
    public:
        Tiger::location loc;

        explicit SemanticError(const Tiger::location &loc, const string &msg)
                : std::runtime_error(msg), loc(loc)
        {}
    };

    class TypeError : public SemanticError
    {
    public:
        string declareName;
        string expectTypeName;
        string actualTypeName;

        explicit TypeError(const Tiger::location &loc,
                           const string &msg)
                : SemanticError(loc, msg)
        {}
    };

    class TypeNotMatchError : public TypeError
    {
    public:

        explicit TypeNotMatchError(const string &etName,
                                   const string &atName,
                                   const string &declareName,
                                   const Tiger::location &loc)
                : TypeError(loc,
                            "Type mismatch : " + declareName
                            + " . Except " + etName
                            + " , but get " + atName)
        {
        }

        explicit TypeNotMatchError(const string &etName,
                                   const string &atName,
                                   const Tiger::location &loc)
                : TypeError(loc,
                            "Type mismatch. Except " + etName
                            + " , but get " + atName)
        {}
    };

    class TypeMatchError : public TypeError
    {
    public:
        explicit TypeMatchError(const string &actualTypeName,
                                const Tiger::location &loc)
                : TypeError(loc,
                            "Type should not be " + actualTypeName)
        {}
    };

    class MatchError : public SemanticError
    {
    public:
        explicit MatchError(const Tiger::location &loc, const string &msg)
                : SemanticError(loc, msg)
        {}
    };

    class ArgMatchError : public MatchError
    {
    public:
        Tiger::location loc;

        explicit ArgMatchError(const Tiger::location &loc, const string &msg)
                : MatchError(loc, msg)
        {}

    };

    class ArgTypeNotMatch : public ArgMatchError
    {
    public:
        explicit ArgTypeNotMatch(const Tiger::location &loc,
                                 const string &expectArgType,
                                 const string &usageArgType)
                : ArgMatchError(loc,
                                "Unmatched argument type. Expected " + expectArgType
                                + " but get " + usageArgType)
        {}
    };

    class ArgNumNotMatch : public ArgMatchError
    {
    public:
        explicit ArgNumNotMatch(const Tiger::location &loc,
                                const int &expectArgNum, const int &usageArgNum)
                : ArgMatchError(loc,
                                "Unmatched argument num. Expected " + std::to_string(expectArgNum)
                                + " but get " + std::to_string(usageArgNum))
        {}

    };

    class RecordMatchError : public MatchError
    {
    public:
        explicit RecordMatchError(const Tiger::location &loc, const string &msg)
                : MatchError(loc, msg)
        {}
    };

    class RecordFieldNumNotMatch : public RecordMatchError
    {
    public:
        explicit RecordFieldNumNotMatch(const Tiger::location &loc,
                                        const int &expectFieldNum, const int &usageFieldNum)
                : RecordMatchError(loc,
                                   "Unmatched field num. Expected " + std::to_string(expectFieldNum)
                                   + " but get " + std::to_string(usageFieldNum))
        {}
    };

    class RecordTypeNotMatch : public RecordMatchError
    {
    public:
        explicit RecordTypeNotMatch(const Tiger::location &loc,
                                    const std::string &expectType,
                                    const std::string &usageType)
                : RecordMatchError(loc,
                                   "Unmatched field type. Expected " + expectType
                                   + " but get " + usageType)
        {}
    };

    void trasProg(std::shared_ptr<ExpAST> exp);

    ExpTy transExp(Env::VarEnv &venv, Env::FuncEnv &fenv, shared_ptr<ExpAST> exp) noexcept(true);

    ExpTy transVar(Env::VarEnv &venv, Env::FuncEnv &fenv, const shared_ptr<VarAST> var) noexcept(true);


    void checkCallArgs(Env::VarEnv &venv, Env::FuncEnv &fenv,
                       const shared_ptr<CallExpAST> usage,
                       const shared_ptr<Env::FuncEntry> def);


    void checkRecordEfields(Env::VarEnv &venv, Env::FuncEnv &fenv,
                            shared_ptr<RecordExpAST> usage,
                            shared_ptr<Env::VarEntry> def);

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

    void transDec(Env::VarEnv &venv, Env::FuncEnv &fenv, const shared_ptr<DecAST> dec);

    shared_ptr<Type::Type> transTy(Env::VarEnv &venv, const shared_ptr<TyAST> &ty);
};

#endif //_TIGER_SEMANTIC_H
