//
// Created by PrinceXuan on 2017/5/29.
//

#include "Semantic.h"
#include "Debug.h"

namespace Semantic
{

    void transProg(std::shared_ptr<AST::Exp> exp)
    {
        Debugger d("Trans prog");
        ExpTy expType;
        // create default environments
        Env::VarEnv venv;
        venv.setDefaultEnv();
        Env::FuncEnv fenv;
        fenv.setDefaultEnv();
        // traverse program's root exp
        expType = transExp(Translate::getGlobalLevel(), nullptr, venv, fenv, exp);
    }

    ExpTy transVar(shared_ptr<Translate::Level> level, shared_ptr<Translate::Exp> breakExp, Env::VarEnv &venv,
                   Env::FuncEnv &fenv, const shared_ptr<AST::Var> &var)
    {
        Debugger d("Trans var");
        if (var == nullptr)
        {
            return ExpTy(Translate::makeNonValueExp(), Type::VOID);
        }
        // TODO: construct result in each case
        switch (var->getClassType())
        {
            case AST::SIMPLE_VAR:
            {
                /*
                 * Format: var var-id (a);
                 */
                auto nonValue = Translate::makeNonValueExp();
                try
                {
                    auto simpleVar = dynamic_pointer_cast<AST::SimpleVar>(var);
                    auto queryResult = venv.find(simpleVar->getSimple());
                    return ExpTy(nonValue, queryResult->type);
                }
                catch (Env::EntryNotFound &e)
                {
                    Tiger::Error err(var->getLoc(), "Variable not defined");
                    return ExpTy(nonValue, Type::INT);
                }
                break;
            }
            case AST::FIELD_VAR:
            {
                /*
                 * Format: var record (a.b)
                 */
                auto nonValue = Translate::makeNonValueExp();
                auto fieldVar = dynamic_pointer_cast<AST::FieldVar>(var);
                ExpTy resultTransField = transVar(level, breakExp, venv, fenv, fieldVar->getVar());
                if (!Type::isRecord(resultTransField.type))
                {
                    Tiger::Error err(var->getLoc(), "Not a record variable");
                    return ExpTy(nonValue, Type::RECORD);
                }
                else
                {
                    auto recordVar = dynamic_pointer_cast<Type::Record>(resultTransField.type);
                    try
                    {
                        int offset = 0;
                        auto field = recordVar->find(fieldVar->getSym(), offset);
                        auto newFieldVar = Translate::makeFieldVar(resultTransField.exp, offset);
                        return ExpTy(newFieldVar, field->type);
                    }
                    catch (Type::EntryNotFound &e)
                    {
                        Tiger::Error err(var->getLoc(), "No such field in record : " + fieldVar->getSym());
                        return ExpTy(nonValue, Type::RECORD);
                    }
                }
                break;
            }
            case AST::SUBSCRIPT_VAR:
            {
                auto nonValue = Translate::makeNonValueExp();
                auto subscriptVar = dynamic_pointer_cast<AST::SubscriptVar>(var);
                ExpTy resultTransSubscript = transVar(<#initializer#>, <#initializer#>, venv, fenv,
                                                      subscriptVar->getVar());
                if (!Type::isArray(resultTransSubscript.type))
                {
                    Tiger::Error err(var->getLoc(), "Not an array variable");
                    return ExpTy(nonValue, Type::ARRAY);
                }
                else
                {
                    ExpTy resultTransExp = transExp(level, breakExp, venv, fenv, subscriptVar->getExp());
                    if (!Type::isInt(resultTransExp.type))
                    {
                        Tiger::Error err(var->getLoc(), "Int required in subscription");
                        return ExpTy(nonValue, Type::ARRAY);
                    }
                    else
                    {
                        // TODO: actual type?
                        auto newSubscriptVar = Translate::makeSubscriptVar(resultTransSubscript.exp,
                                                                           resultTransExp.exp);
                        return ExpTy(newSubscriptVar, resultTransExp.type);
                    }
                }
            }
                break;
            default:
            {
                Tiger::Error err(var->getLoc(), "Unknown type of variable");
                exit(1);
            }
                break;
        }
    }

    ExpTy transExp(shared_ptr<Translate::Level> level, shared_ptr<Translate::Exp> breakExp, Env::VarEnv &venv,
                   Env::FuncEnv &fenv, shared_ptr<AST::Exp> exp)
    {
        // DEBUG
        Debugger d("Trans exp");
        auto defaultLoc = exp->getLoc();
        if (nullptr == exp)
        {
            return ExpTy(Translate::makeNonValueExp(), Type::VOID);
        }
        switch (exp->getClassType())
        {
            case AST::VAR_EXP:
            {
                auto var = dynamic_pointer_cast<AST::VarExp>(exp);
                return transVar(level, breakExp, venv, fenv, var->getVar());
            }
                break;
            case AST::NIL_EXP:
            {
                auto nil = Translate::makeNilExp();
                return ExpTy(nil, Type::NIL);
            }
                break;
            case AST::CALL_EXP:
            {
                auto funcUsage = dynamic_pointer_cast<AST::CallExp>(exp);
                string funcName = funcUsage->getFunc();
                try
                {
                    // Find the definition of the func
                    auto funcDefine = fenv.find(funcName);
                    // Check if the args used match the defined
                    checkCallArgs(venv, fenv, funcUsage, funcDefine);
                    // Form the arg list for translate
                    auto funcArgList = Translate::makeExpList();
                    auto funcArgUsage = funcUsage->getArgs();
                    for (auto arg = funcArgUsage->begin(); arg != funcArgUsage->end(); arg++)
                    {
                        auto argTrans = transExp(level, breakExp, venv, fenv, (*arg));
                        funcArgList->push_front(argTrans.exp);
                    }
                    // Form the call exp for translate
                    // TODO: modify FuncEntry & VarEntry
//                    auto func = Translate::makeCallExp(funcDefine->)
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
            }
                break;
            case AST::RECORD_EXP:
            {
                auto recordUsage = dynamic_pointer_cast<AST::RecordExp>(exp);
                string recordName = recordUsage->getTyp();
                try
                {
                    // Check definition
                    auto recordDefine = venv.find(recordName);
                    assertTypeMatch(recordDefine->getType(), Type::RECORD, recordName, defaultLoc);
                    // Check efields
                    checkRecordEfields(venv, fenv, recordUsage, recordDefine);
                    // Check pass
                    return ExpTy(nullptr, recordDefine->getType());
                }
                catch (Env::EntryNotFound &e)
                {
                    Tiger::Error(defaultLoc, "Record not defined : " + recordName);
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error(e.loc, e.what());
                }
                catch (RecordMatchError &e)
                {
                    Tiger::Error(e.loc, e.what());
                }
                // default return with error
                return ExpTy(nullptr, Type::RECORD);
            }
                break;
            case AST::ARRAY_EXP:
            {
                auto arrayUsage = dynamic_pointer_cast<AST::ArrayExp>(exp);
                string arrayName = arrayUsage->getTyp();
                try
                {
                    // Check definition
                    auto arrayDefine = venv.find(arrayName);
                    assertTypeMatch(arrayDefine->getType(), Type::ARRAY, arrayName, defaultLoc);
                    // Check size
                    auto arraySize = transExp(<#initializer#>, <#initializer#>, venv, fenv, arrayUsage->getSize());
                    assertTypeMatch(arraySize.type, Type::INT, defaultLoc);
                    // Check init
                    auto arrayInit = transExp(<#initializer#>, <#initializer#>, venv, fenv, arrayUsage->getInit());
                    assertTypeMatch(arrayInit.type, Type::ARRAY, defaultLoc);
                    // Check pass
                    return ExpTy(nullptr, arrayDefine->getType());
                }
                catch (Env::EntryNotFound &e)
                {
                    Tiger::Error(defaultLoc, "Array not defined : " + arrayName);
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error(e.loc, e.what());
                }
                // default return with error
                return ExpTy(nullptr, Type::ARRAY);
            }
                break;
            case AST::SEQ_EXP:
            {
                auto exps = dynamic_pointer_cast<AST::SeqExp>(exp);
                const std::list<shared_ptr<AST::Exp>> expList = *(exps->getSeq());
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
                    auto result = transExp(<#initializer#>, <#initializer#>, venv, fenv, (*iter));
                    if (iter == last_iter)
                    {
                        return result;
                    }
                }
            }
                // run here into error?
                break;
            case AST::WHILE_EXP:
            {
                auto whileUsage = dynamic_pointer_cast<AST::WhileExp>(exp);
                // Check while's test condition
                auto whileTest = transExp(<#initializer#>, <#initializer#>, venv, fenv, whileUsage->getTest());
                try
                {
                    assertTypeMatch(whileTest.type, Type::INT, defaultLoc);
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error(e.loc, e.what());
                }
                // Trans while's body
                auto whileBody = transExp(<#initializer#>, <#initializer#>, venv, fenv, whileUsage->getBody());
                return ExpTy(nullptr, Type::VOID);
            }
                break;
            case AST::ASSIGN_EXP:
            {
                auto assignUsage = dynamic_pointer_cast<AST::AssignExp>(exp);
                // Check assign's var
                auto assignVar = assignUsage->getVar();
                auto assignVarResult = transVar(<#initializer#>, <#initializer#>, venv, fenv, assignVar);
                // Check assign's exp
                auto assignExp = assignUsage->getExp();
                auto assignExpResult = transExp(<#initializer#>, <#initializer#>, venv, fenv, assignExp);
                // Check type
                try
                {
                    assertTypeMatch(assignVarResult.type, assignExpResult.type, defaultLoc);
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error err(e.loc, e.what());
                }
                return ExpTy(nullptr, Type::VOID);
            }
                break;
            case AST::BREAK_EXP:
            {
                return ExpTy(nullptr, Type::VOID);
            }
                break;
            case AST::FOR_EXP:
            {
                auto forUsage = dynamic_pointer_cast<AST::ForExp>(exp);
                // Check low and high range
                auto forLo = forUsage->getLo();
                auto forHi = forUsage->getHi();
                try
                {
                    auto forLoResult = transExp(<#initializer#>, <#initializer#>, venv, fenv, forLo);
                    auto forHiResult = transExp(<#initializer#>, <#initializer#>, venv, fenv, forHi);
                    assertTypeMatch(forLoResult.type, Type::INT, forLo->getLoc());
                    assertTypeMatch(forHiResult.type, Type::INT, forHi->getLoc());
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error err(e.loc, e.what());
                }
                fenv.beginScope();
                // Check declaration
                auto forDec = AST::MakeVarDec(defaultLoc, forUsage->getVar(),
                                              Type::getName(Type::INT), forLo);
                transDec(venv, fenv, forDec);
                // Check body
                auto forBody = transExp(<#initializer#>, <#initializer#>, venv, fenv, forUsage->getBody());
                fenv.endScope();
                // TODO: Handle error?
                return ExpTy(nullptr, Type::VOID);
            }
            case AST::LET_EXP:
            {
                fenv.beginScope();
                venv.beginScope();
                // Check each exp decs
                auto letUsage = dynamic_pointer_cast<AST::LetExp>(exp);
                auto letDecs = letUsage->getDecs();
                for (auto dec = letDecs->begin(); dec != letDecs->end(); dec++)
                {
                    transDec(venv, fenv, *dec);
                }
                // Check let exp body
                auto letBody = letUsage->getBody();
                auto result = transExp(<#initializer#>, <#initializer#>, venv, fenv, letBody);
                venv.endScope();
                fenv.endScope();
                return result;
            }
                break;
            case AST::OP_EXP:
            {
                auto opUsage = dynamic_pointer_cast<AST::OpExp>(exp);
                // Check both side of op exp
                auto opLeft = transExp(<#initializer#>, <#initializer#>, venv, fenv, opUsage->getLeft());
                auto opRight = transExp(<#initializer#>, <#initializer#>, venv, fenv, opUsage->getRight());
                // Check type
                // TODO: need implementation with translate
                try
                {
                    switch (opUsage->getOp())
                    {
                        case AST::PLUSOP:
                        case AST::MINUSOP:
                        case AST::TIMESOP:
                        case AST::DIVIDEOP:
                            assertTypeMatch(opLeft.type, Type::INT, opUsage->getLeft()->getLoc());
                            assertTypeMatch(opRight.type, Type::INT, opUsage->getRight()->getLoc());
                            return ExpTy(nullptr, Type::INT);
                            break;
                        case AST::EQOP:
                        case AST::NEQOP:
                            if (Type::isNil(opLeft.type) && Type::isRecord(opRight.type))
                            {
                                return ExpTy(nullptr, Type::INT);
                            }
                            else if (Type::isRecord(opLeft.type) && Type::isNil(opRight.type))
                            {
                                return ExpTy(nullptr, Type::INT);
                            }
                            break;
                        case AST::LTOP:
                            break;
                        case AST::LEOP:
                            break;
                        case AST::GTOP:
                            break;
                        case AST::GEOP:
                            break;
                    }
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error(e.loc, e.what());
                }
            }
                break;
            case AST::IF_EXP:
            {
                auto ifUsage = dynamic_pointer_cast<AST::IfExp>(exp);
                auto ifTestPtr = ifUsage->getTest();
                auto ifThenPtr = ifUsage->getThen();
                auto ifElsePtr = ifUsage->getElsee();
                // Check if's test condition
                auto ifTest = transExp(<#initializer#>, <#initializer#>, venv, fenv, ifTestPtr);
                try
                {
                    assertTypeMatch(ifTest.type, Type::INT, ifTestPtr->getLoc());
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error err(e.loc, e.what());
                }
                // Check if's then body
                auto ifThen = transExp(<#initializer#>, <#initializer#>, venv, fenv, ifThenPtr);
                // Check if's else body
                if (ifElsePtr != nullptr)
                {
                    auto ifElse = transExp(<#initializer#>, <#initializer#>, venv, fenv, ifElsePtr);
                    try
                    {
                        assertTypeMatch(ifThen.type, ifElse.type, ifThenPtr->getLoc());
                    }
                    catch (TypeNotMatchError &e)
                    {
                        Tiger::Error err(e.loc, e.what());
                    }
                }
                // TODO: use which return?
                return ExpTy(nullptr, ifThen.type);
            }
                break;
            case AST::STRING_EXP:
            {
                return ExpTy(nullptr, Type::STRING);
            }
            case AST::INT_EXP:
            {
                return ExpTy(nullptr, Type::INT);
            }
            default:
            {
                // TODO: handle default case
            }
                break;
        }

        return ExpTy();
    }


    void transDec(Env::VarEnv &venv, Env::FuncEnv &fenv, const shared_ptr<AST::Dec> dec)
    {
        // DEBUG
        Debugger d("Trans dec");
        auto defaultLoc = dec->getLoc();
        switch (dec->getClassType())
        {
            case AST::VAR_DEC:
            {

                auto varUsage = dynamic_pointer_cast<AST::VarDec>(dec);
                auto varName = varUsage->getVar();
                // Check var init
                auto varInit = transExp(<#initializer#>, <#initializer#>, venv, fenv, varUsage->getInit());
                // If type name is empty
                shared_ptr<Type::Type> varType = make_shared<Type::Type>();
                if (0 != varUsage->getTyp().size())
                {
                    try
                    {
                        assertTypeNotMatch(varInit.type, Type::NIL, defaultLoc);
                        assertTypeNotMatch(varInit.type, Type::VOID, defaultLoc);
                        varType = varInit.type;
                    }
                    catch (TypeMatchError &e)
                    {
                        Tiger::Error err(e.loc, e.what());
                    }
                }
                else
                {
                    // TODO: reconsider the logic
                    try
                    {
                        auto varResult = fenv.find(varUsage->getTyp());
                        assertTypeMatch(varResult->getResultType(), varInit.type, defaultLoc);
                        varType = varResult->getResultType();
                    }
                    catch (Env::EntryNotFound &e)
                    {
                        Tiger::Error err(defaultLoc, e.what());
                    }
                    catch (TypeNotMatchError &e)
                    {
                        Tiger::Error err(e.loc, e.what());
                    }
                }
                Env::VarEntry ve(varName, varType, shared_ptr<Translate::Access>());
                venv.enter(ve);
            }
                break;
            case AST::FUNCTION_DEC:
            {
                auto funcUsage = dynamic_pointer_cast<AST::FunctionDec>(dec);
                auto funcList = funcUsage->getFunction();
                // Add functions' declaration
                for (auto f = funcList->begin(); f != funcList->end(); f++)
                {
                    // Check func return type
                    auto returnTypeName = (*f)->getResult();
                    shared_ptr<Type::Type> returnType = make_shared<Type::Type>();
                    if (returnTypeName.size() == 0)
                    {
                        returnType = Type::VOID;
                    }
                    else
                    {
                        try
                        {
                            returnType = venv.find(returnTypeName)->getType();
                        }
                        catch (Env::EntryNotFound &e)
                        {
                            Tiger::Error err(defaultLoc, e.what());
                            returnType = Type::VOID;
                        }
                    }
                    Env::FuncEntry fe(shared_ptr<Translate::Level>(), shared_ptr<Temporary::Label>(),(*f)->getName(),
                            returnType);
                    // Check and add args
                    auto args = (*f)->getParams();
                    for (auto arg = args->begin(); arg != args->end(); arg++)
                    {
                        shared_ptr<Type::Type> argType = make_shared<Type::Type>();
                        try
                        {
                            // TODO: getTyp? getName?
                            argType = venv.find((*arg)->getTyp())->getType();
                        }
                        catch (Env::EntryNotFound &e)
                        {
                            Tiger::Error err((*arg)->getLoc(), e.what());
                            argType = Type::INT;
                        }
                        fe.addArg(argType);
                    }
                    // Add func into func environment
                    fenv.enter(fe);
                }
                // Traverse all functions' body to check `return type`
                // Need to form function environment first, then traverse their body
                for (auto f = funcList->begin(); f != funcList->end(); f++)
                {
                    // TODO: venv scope?
                    fenv.beginScope();
                    auto args = (*f)->getParams();
                    // Add args into var environment
                    for (auto arg = args->begin(); arg != args->end(); arg++)
                    {
                        auto argName = (*arg)->getName();
                        shared_ptr<Type::Type> argType = make_shared<Type::Type>();
                        try
                        {
                            argType = venv.find(argName)->getType();
                        }
                        catch (Env::EntryNotFound &e)
                        {
                            Tiger::Error err((*arg)->getLoc(), e.what());
                            argType = Type::INT;
                        }
                        Env::VarEntry argEntry(argName, argType, shared_ptr<Translate::Access>());
                        venv.enter(argEntry);
                    }
                    // Traverse func body
                    auto func = transExp(<#initializer#>, <#initializer#>, venv, fenv, (*f)->getBody());
                    try
                    {
                        auto returnType = fenv.find((*f)->getName())->getResultType();
                        assertTypeMatch(func.type, returnType, (*f)->getLoc());
                    }
                    catch (Env::EntryNotFound &e)
                    {
                        Tiger::Error err((*f)->getLoc(), e.what());
                    }
                    catch (TypeNotMatchError &e)
                    {
                        Tiger::Error err((*f)->getLoc(), e.what());
                    }
                    fenv.endScope();
                }
            }
                break;
            case AST::TYPE_DEC:
            {
                auto typeUsage = std::dynamic_pointer_cast<AST::TypeDec>(dec);
                auto types = typeUsage->getType();
                for (auto t = types->begin(); t != types->end(); t++)
                {
                    // TODO: why nullptr?
                    Type::Name n((*t)->getName(), nullptr);
                    Env::VarEntry nameVarEntry((*t)->getName(), make_shared<Type::Name>(n),
                                               shared_ptr<Translate::Access>());
                    venv.enter(nameVarEntry);
                }
                bool isCycle = true;
                for (auto t = types->begin(); t != types->end(); t++)
                {
                    // TODO: wild pointer
                    shared_ptr<Type::Type> result = transTy(venv, (*t)->getTy());
                }
                break;
            }
            default:
            {

            }
                break;
        }
    }

    shared_ptr<Type::Type> transTy(Env::VarEnv &venv, const shared_ptr<AST::Ty> &ty)
    {
        // DEBUG
        switch (ty->getClassType())
        {
            case AST::NAME_TYPE:
            {
                auto nameTy = dynamic_pointer_cast<AST::NameTy>(ty);
                try
                {
                    auto t = venv.find(nameTy->getName());
                    return t->getType();
                }
                catch (Env::EntryNotFound &e)
                {
                    Tiger::Error err(nameTy->getLoc(), e.what());
                }
                return Type::INT;
            }
                break;
            case AST::RECORD_TYPE:
            {
                auto recordTy = dynamic_pointer_cast<AST::RecordTy>(ty);
                auto fields = recordTy->getRecord();
                shared_ptr<Type::Record> record = make_shared<Type::Record>();
                for (auto field = fields->begin(); field != fields->end(); field++)
                {
                    try
                    {
                        auto fieldType = venv.find((*field)->getTyp());
                        record->addField((*field)->getName(), fieldType->getType());
                    }
                    catch (Env::EntryNotFound &e)
                    {
                        Tiger::Error err(recordTy->getLoc(), e.what());
                        record->addField((*field)->getName(), Type::NIL);
                    }


                }
                return record;
            }
                break;
            case AST::ARRAY_TYPE:
            {
                shared_ptr<Type::Array> array = make_shared<Type::Array>();
                auto arrayTy = dynamic_pointer_cast<AST::ArrayTy>(ty);
                try
                {
                    auto t = venv.find(arrayTy->getArray());
                    auto type = t->getType();
                    array->setArray(type);
                }
                catch (Env::EntryNotFound &e)
                {
                    Tiger::Error err(arrayTy->getLoc(), e.what());
                }
                return array;
            }
                break;
            default:
                break;
        }
    }


    void assertTypeNotMatch(const shared_ptr<Type::Type> actualType,
                            const shared_ptr<Type::Type> assertType,
                            const Tiger::location &loc)
    {
        if (typeid(actualType) == typeid(assertType))
        {
            throw TypeMatchError(Type::getName(actualType), loc);
        }
    }

    void assertTypeMatch(const shared_ptr<Type::Type> check,
                         const shared_ptr<Type::Type> base,
                         const std::string &declareName,
                         const Tiger::location &loc)
    {
        if (typeid(check) != typeid(base))
        {
            throw TypeNotMatchError(Type::getName(check), Type::getName(base), declareName, loc);
        }
    }

    void assertTypeMatch(const shared_ptr<Type::Type> check,
                         const shared_ptr<Type::Type> base,
                         const Tiger::location &loc)
    {
        if (typeid(check) != typeid(base))
        {
            throw TypeNotMatchError(Type::getName(check), Type::getName(base), loc);
        }
    }

    void checkRecordEfields(Env::VarEnv &venv, Env::FuncEnv &fenv,
                            shared_ptr<AST::RecordExp> usage,
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
            auto t = transExp(<#initializer#>, <#initializer#>, venv, fenv, (*uIter)->getExp());
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
                       const shared_ptr<AST::CallExp> usage,
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
            auto t = transExp(<#initializer#>, <#initializer#>, venv, fenv, (*uIter));
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

    ExpTy::ExpTy()
    {}

    ExpTy::ExpTy(const shared_ptr<Translate::Exp> &exp, const shared_ptr<Type::Type> &type)
            : exp(exp), type(type)
    {}

    void ExpTy::setExp(const shared_ptr<Translate::Exp> &exp)
    {
        this->exp = exp;
    }

    void ExpTy::setType(const shared_ptr<Type::Type> &type)
    {
        this->type = type;
    }

    SemanticError::SemanticError(const Tiger::location &loc, const string &msg)
            : std::runtime_error(msg), loc(loc)
    {}

    TypeError::TypeError(const Tiger::location &loc, const string &msg)
            : SemanticError(loc, msg)
    {}

    TypeNotMatchError::TypeNotMatchError(const string &etName, const string &atName, const string &declareName,
                                         const Tiger::location &loc)
            : TypeError(loc,
                        "Type mismatch : " + declareName
                        + " . Except " + etName
                        + " , but get " + atName)
    {
    }

    TypeNotMatchError::TypeNotMatchError(const string &etName, const string &atName, const Tiger::location &loc)
            : TypeError(loc,
                        "Type mismatch. Except " + etName
                        + " , but get " + atName)
    {}

    TypeMatchError::TypeMatchError(const string &actualTypeName, const Tiger::location &loc)
            : TypeError(loc,
                        "Type should not be " + actualTypeName)
    {}

    MatchError::MatchError(const Tiger::location &loc, const string &msg)
            : SemanticError(loc, msg)
    {}

    ArgMatchError::ArgMatchError(const Tiger::location &loc, const string &msg)
            : MatchError(loc, msg)
    {}

    ArgTypeNotMatch::ArgTypeNotMatch(const Tiger::location &loc, const string &expectArgType,
                                     const string &usageArgType)
            : ArgMatchError(loc,
                            "Unmatched argument type. Expected " + expectArgType
                            + " but get " + usageArgType)
    {}

    ArgNumNotMatch::ArgNumNotMatch(const Tiger::location &loc, const int &expectArgNum, const int &usageArgNum)
            : ArgMatchError(loc,
                            "Unmatched argument num. Expected " + std::to_string(expectArgNum)
                            + " but get " + std::to_string(usageArgNum))
    {}

    RecordMatchError::RecordMatchError(const Tiger::location &loc, const string &msg)
            : MatchError(loc, msg)
    {}

    RecordFieldNumNotMatch::RecordFieldNumNotMatch(const Tiger::location &loc, const int &expectFieldNum,
                                                   const int &usageFieldNum)
            : RecordMatchError(loc,
                               "Unmatched field num. Expected " + std::to_string(expectFieldNum)
                               + " but get " + std::to_string(usageFieldNum))
    {}

    RecordTypeNotMatch::RecordTypeNotMatch(const Tiger::location &loc, const std::string &expectType,
                                           const std::string &usageType)
            : RecordMatchError(loc,
                               "Unmatched field type. Expected " + expectType
                               + " but get " + usageType)
    {}
}