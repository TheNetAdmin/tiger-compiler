//
// Created by PrinceXuan on 2017/5/29.
//

#include "Semantic.h"
#include "Error.h"

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

    switch (exp->getClassType()) {
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

// TODO: make venv and fenv const?
ExpTy transVar(Env::VarEnv venv, Env::FuncEnv fenv, const shared_ptr<VarAST> &var) {
    ExpTy result;
    Tiger::Error err;
    switch (var->getClassType()) {
        // TODO: construct result in each case
        case SIMPLE_VAR:
            try {
                auto simpleVar = dynamic_pointer_cast<SimpleVarAST>(var);
                auto queryResult = venv.find(simpleVar->getSimple());
            } catch (Env::EntryNotFound &e) {
                err.setLoc(var->getLoc());
                err.setMessage("Variable not defined");
            }
            break;
        case FIELD_VAR:
            auto fieldVar = dynamic_pointer_cast<FieldVarAST>(var);
            auto varOfFieldVar = fieldVar->getVar();
            ExpTy resultTransField = transVar(venv, fenv, varOfFieldVar);
            if (!Type::isRecord(resultTransField.type)) {
                err.setLoc(var->getLoc());
                err.setMessage("Variable not defined");
            } else {
                auto recordVar = dynamic_pointer_cast<Type::Record>(resultTransField.type);
//                for (auto record = recordVar->recordList)
            }
            break;
        case SUBSCRIPT_VAR:
            break;
        default:
            break;
    }
    return ExpTy();
}
