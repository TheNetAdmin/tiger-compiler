//
// Created by PrinceXuan on 2017/5/29.
//

#include "Semantic.h"

using namespace Semantic;

ExpTy transExp(Env::VarEnv venv, Env::FuncEnv fenv, shared_ptr<ExpAST> exp);

ExpTy transVar(Env::VarEnv venv, Env::FuncEnv fenv, const shared_ptr<VarAST> &var);

void trasProg(std::shared_ptr<ExpAST> exp) {
    ExpTy expType;
    // create default environments
    Env::VarEnv venv;
    venv.setDefaultEnv();
    Env::FuncEnv fenv;
    fenv.setDefaultEnv();
    // traverse program's root exp
    expType = transExp(venv, fenv, exp);
}

ExpTy transExp(Env::VarEnv venv, Env::FuncEnv fenv, shared_ptr<ExpAST> exp) {
    ExpTy result;

    switch (exp->getClassType()){
        case VAR_EXP:
            auto var = dynamic_pointer_cast<VarExpAST>(exp);
            result = transVar(venv, fenv, var->getVar());
            break;
        case NIL_EXP:
            // TODO: safe to use nullptr?
            result = ExpTy(nullptr, Type::NIL);
            break;
            // TODO: other cases
        default:
            break;
    }

    return ExpTy();
}

ExpTy transVar(Env::VarEnv venv, Env::FuncEnv fenv, const shared_ptr<VarAST> &var) {
    switch (var->getClassType()){
        case SIMPLE_VAR:
            break;
        case FIELD_VAR:
            break;
        case SUBSCRIPT_VAR:
            break;
        default:
            break;
    }
    return ExpTy();
}
