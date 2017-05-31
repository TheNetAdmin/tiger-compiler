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

        explicit TypeError(const string &rtName,
                           const string &atName,
                           const string &declareName,
                           const Tiger::location &loc)
                : SemanticError(loc,
                                "Type mismatch : " + declareName
                                + " . Except " + expectTypeName
                                + " , but get " + actualTypeName),
                  declareName(declareName)
        {
        }

        explicit TypeError(const string &rtName,
                           const string &atName,
                           const Tiger::location &loc)
                : SemanticError(loc,
                                "Type mismatch. Except " + expectTypeName
                                + " , but get " + actualTypeName)
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
};

#endif //_TIGER_SEMANTIC_H
