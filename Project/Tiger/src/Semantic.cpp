//
// Created by PrinceXuan on 2017/5/29.
//

#include "Semantic.h"
#include "Error.h"

using namespace Semantic;

// TODO: use reference for shared_ptr?
ExpTy transExp(Env::VarEnv &venv, Env::FuncEnv &fenv, shared_ptr<ExpAST> exp) noexcept(true);

ExpTy transVar(Env::VarEnv &venv, Env::FuncEnv &fenv, const shared_ptr<VarAST> var) noexcept(true);


void checkCallArgs(Env::VarEnv &venv, Env::FuncEnv &fenv,
                   const shared_ptr<CallExpAST> usage,
                   const shared_ptr<Env::FuncEntry> def);


void checkRecordEfields(Env::VarEnv &venv, Env::FuncEnv &fenv,
                        shared_ptr<RecordExpAST> usage,
                        shared_ptr<Env::VarEntry> def);

void checkType(shared_ptr<Type::Type> check,
               shared_ptr<Type::Type> base,
               std::string &declareName,
               Tiger::location &loc);

void checkType(shared_ptr<Type::Type> check,
               shared_ptr<Type::Type> base,
               Tiger::location &loc);

void trasProg(std::shared_ptr<ExpAST> exp)
{
    ExpTy expType;
    // create default environments
    Env::VarEnv venv;
    venv.setDefaultEnv();
    Env::FuncEnv fenv;
    fenv.setDefaultEnv();
    // traverse program's root exp
    expType = transExp(venv, fenv, exp);
}

// TODO: make venv and fenv const?
ExpTy transVar(Env::VarEnv &venv, Env::FuncEnv &fenv, const shared_ptr<VarAST> var) noexcept(true)
{
    switch (var->getClassType())
    {
        // TODO: construct result in each case
        case SIMPLE_VAR:
            try
            {
                auto simpleVar = dynamic_pointer_cast<SimpleVarAST>(var);
                auto queryResult = venv.find(simpleVar->getSimple());
                return ExpTy(nullptr, queryResult->type);
            }
            catch (Env::EntryNotFound &e)
            {
                Tiger::Error err(var->getLoc(), "Variable not defined");
                return ExpTy(nullptr, Type::INT);
            }
            break;
        case FIELD_VAR:
            auto fieldVar = dynamic_pointer_cast<FieldVarAST>(var);
            ExpTy resultTransField = transVar(venv, fenv, fieldVar->getVar());
            if (!Type::isRecord(resultTransField.type))
            {
                Tiger::Error err(var->getLoc(), "Not a record variable");
                return ExpTy(nullptr, Type::RECORD);
            }
            else
            {
                auto recordVar = dynamic_pointer_cast<Type::Record>(resultTransField.type);
                try
                {
                    auto field = recordVar->find(fieldVar->getSym());
                    // TODO: actual type?
                    return ExpTy(nullptr, field->type);
                }
                catch (Type::EntryNotFound &e)
                {
                    Tiger::Error err(var->getLoc(), "No such field in record : " + fieldVar->getSym());
                    return ExpTy(nullptr, Type::RECORD);
                }
            }
            break;
        case SUBSCRIPT_VAR:
            auto subscriptVar = dynamic_pointer_cast<SubscriptVarAST>(var);
            ExpTy resultTransSubscript = transVar(venv, fenv, subscriptVar->getVar());
            if (!Type::isArray(resultTransSubscript.type))
            {
                Tiger::Error err(var->getLoc(), "Not an array variable");
                return ExpTy(nullptr, Type::ARRAY);
            }
            else
            {
                ExpTy resultTransExp = transExp(venv, fenv, subscriptVar->getExp());
                if (!Type::isInt(resultTransExp.type))
                {
                    Tiger::Error err(var->getLoc(), "Int required in subscription");
                    return ExpTy(nullptr, Type::ARRAY);
                }
                else
                {
                    // TODO: actual type?
                    return ExpTy(nullptr, resultTransExp.type);
                }
            }
            break;
        default:
            Tiger::Error err(var->getLoc(), "Unknown type of variable");
            exit(1);
            break;
    }
}

ExpTy transExp(Env::VarEnv &venv, Env::FuncEnv &fenv, shared_ptr<ExpAST> exp) noexcept(true)
{
    auto defaultLoc = exp->getLoc();
    switch (exp->getClassType())
    {
        case VAR_EXP:
            auto var = dynamic_pointer_cast<VarExpAST>(exp);
            return transVar(venv, fenv, var->getVar());
            break;
        case NIL_EXP:
            // TODO: replace nullptr with translate info
            return ExpTy(nullptr, Type::NIL);
            break;
        case CALL_EXP:
            auto funcUsage = dynamic_pointer_cast<CallExpAST>(exp);
            string funcName = funcUsage->getFunc();
            try
            {
                auto funcDefine = fenv.find(funcName);
                checkCallArgs(venv, fenv, funcUsage, funcDefine);
                return ExpTy(nullptr, funcDefine->getResultType());
            }
            catch (Env::EntryNotFound &e)
            {
                Tiger::Error(exp->getLoc(), "Function not defined : " + funcName);
            }
            catch (ArgMatchError &e)
            {
                Tiger::Error(e.loc, e.what());
            }
            // default return with error
            return ExpTy(nullptr, Type::VOID);
            break;
        case RECORD_EXP:
            auto recordUsage = dynamic_pointer_cast<RecordExpAST>(exp);
            string recordName = recordUsage->getTyp();
            try
            {
                // Check definition
                auto recordDefine = venv.find(recordName);
                checkType(recordDefine->getType(), Type::RECORD, recordName, defaultLoc);
                // Check efields
                checkRecordEfields(venv, fenv, recordUsage, recordDefine);
                // Check pass
                return ExpTy(nullptr, recordDefine->getType());
            }
            catch (Env::EntryNotFound &e)
            {
                Tiger::Error(defaultLoc, "Record not defined : " + recordName);
            }
            catch (TypeError &e)
            {
                Tiger::Error(e.loc, e.what());
            }
            catch (RecordMatchError &e)
            {
                Tiger::Error(e.loc, e.what());
            }
            // default return with error
            return ExpTy(nullptr, Type::RECORD);
            break;
        case ARRAY_EXP:
            auto arrayUsage = dynamic_pointer_cast<ArrayExpAST>(exp);
            string arrayName = arrayUsage->getTyp();
            try
            {
                // Check definition
                auto arrayDefine = venv.find(arrayName);
                checkType(arrayDefine->getType(), Type::ARRAY, arrayName, defaultLoc);
                // Check size
                auto arraySize = transExp(venv, fenv, arrayUsage->getSize());
                checkType(arraySize.type, Type::INT, defaultLoc);
                // Check init
                auto arrayInit = transExp(venv, fenv, arrayUsage->getInit());
                checkType(arrayInit.type, Type::ARRAY, defaultLoc);
                // Check pass
                return ExpTy(nullptr, arrayDefine->getType());
            }
            catch (Env::EntryNotFound &e)
            {
                Tiger::Error(defaultLoc, "Array not defined : " + arrayName);
            }
            catch (TypeError &e)
            {
                Tiger::Error(e.loc, e.what());
            }
            // default return with error
            return ExpTy(nullptr, Type::ARRAY);
            break;
        case SEQ_EXP:
            auto exps = dynamic_pointer_cast<SeqExpAST>(exp);
            const std::list<shared_ptr<ExpAST>> expList = *(exps->getSeq());
            // Check num of exps
            if (expList.size() == 0)
            {
                return ExpTy(nullptr, Type::VOID);
            }
            // Check each exp and return last exp's return value
            auto last_iter = expList.end();
            last_iter--;
            for (auto iter = expList.begin(); iter != expList.end(); iter++)
            {
                auto result = transExp(venv, fenv, e);
                if (iter == last_iter)
                {
                    return result;
                }
            }
            // run here into error?
            break;
        case WHILE_EXP:
            auto whileExp = dynamic_pointer_cast<WhileExpAST>(exp);
            // Check while's test condition
            auto whileTest = transExp(venv, fenv, whileExp->getTest());
            try
            {
                checkType(whileTest.type, Type::INT, defaultLoc);
            }
            catch (TypeError &e)
            {
                Tiger::Error(e.loc, e.what());
            }
            // Trans while's body
            auto whileBody = transExp(venv, fenv, whileExp->getBody());
            return ExpTy(nullptr, Type::VOID);
        default:
            break;
    }

    return ExpTy();
}

void checkType(shared_ptr<Type::Type> check, shared_ptr<Type::Type> base,
               std::string &declareName, Tiger::location &loc)
{
    if (typeid(check) != typeid(base))
    {
        throw TypeError(Type::getName(check), Type::getName(base), declareName, loc);
    }
}

void checkType(shared_ptr<Type::Type> check,
               shared_ptr<Type::Type> base,
               Tiger::location &loc)
{
    if (typeid(check) != typeid(base))
    {
        throw TypeError(Type::getName(check), Type::getName(base), loc);
    }
}

void checkRecordEfields(Env::VarEnv &venv, Env::FuncEnv &fenv,
                        shared_ptr<RecordExpAST> usage,
                        shared_ptr<Env::VarEntry> def)
{
    auto defTypePtr = def->getType();
    auto recordDefine = dynamic_pointer_cast<Type::Record>(defTypePtr);
    auto uEfields = usage->getFields();
    auto dEfields = recordDefine->getFields();

    // Check if field num matches
    auto uSize = uEfields->size();
    auto dSize = dEfields->size();
    if (uSize != dSize)
    {
        throw RecordFieldNumNotMatch(usage->getLoc(), dSize, uSize);
    }

    // Check if fields' types match
    auto uIter = uEfields->begin();
    auto dIter = dEfields->begin();
    for (; (uIter != uEfields->end()) && (dIter != dEfields->end());
           uIter++, dIter++)
    {
        auto t = transExp(venv, fenv, (*uIter)->getExp());
        auto dType = (*dIter)->type;
        auto uType = t.type;
        if (!Type::match(dType, uType))
        {
            throw RecordTypeNotMatch((*uIter)->getExp()->getLoc(),
                                     Type::getName(dType),
                                     Type::getName(uType));
        }
    }
    // Check pass
}


void checkCallArgs(Env::VarEnv &venv, Env::FuncEnv &fenv,
                   const shared_ptr<CallExpAST> usage,
                   const shared_ptr<Env::FuncEntry> def)
{
    auto uArgs = usage->getArgs();
    auto dArgs = def->getArgs();

    // Check if arg num matches
    auto uSize = uArgs->size();
    auto dSize = dArgs->size();
    if (uSize != dSize)
    {
        throw ArgNumNotMatch(usage->getLoc(), dSize, uSize);
    }

    // Check if args' types match
    auto uIter = uArgs->begin();
    auto dIter = dArgs->begin();
    for (; (uIter != uArgs->end()) && (dIter != dArgs->end());
           uIter++, dIter++)
    {
        auto t = transExp(venv, fenv, (*uIter));
        auto dType = (*dIter);
        auto uType = t.type;
        if (!Type::match(dType, uType))
        {
            // Throw the more precise location
            throw ArgTypeNotMatch((*uIter)->getLoc(),
                                  Type::getName(dType),
                                  Type::getName(uType));
        }
    }
    // Check pass
}

