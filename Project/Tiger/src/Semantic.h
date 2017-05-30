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

namespace Semantic {
    class ExpTy {
    public:
        std::shared_ptr<Translate::Exp> exp;
        std::shared_ptr<Type::Type> type;

        ExpTy() {}

        ExpTy(const shared_ptr<Translate::Exp> &exp, const shared_ptr<Type::Type> &type)
                : exp(exp), type(type) {}

    };

    void trasProg(std::shared_ptr<ExpAST> exp);
};

#endif //_TIGER_SEMANTIC_H
