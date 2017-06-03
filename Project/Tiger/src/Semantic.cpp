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
                    checkCallArgs(level, breakExp, venv, fenv,
                                  funcUsage, funcDefine);
                    // Form the arg list for translate
                    auto funcArgList = Translate::makeExpList();
                    auto funcArgUsage = funcUsage->getArgs();
                    for (auto arg = funcArgUsage->begin(); arg != funcArgUsage->end(); arg++)
                    {
                        auto argTrans = transExp(level, breakExp, venv, fenv, (*arg));
                        funcArgList->push_front(argTrans.exp);
                    }
                    // Form the call exp for translate
                    auto func = Translate::makeCallExp(funcDefine->getLabel(),
                                                       funcDefine->getLevel(), level, funcArgList);
                    return ExpTy(func, funcDefine->getResultType());
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
                auto nonValue = Translate::makeNonValueExp();
                return ExpTy(nonValue, Type::VOID);
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
                    checkRecordEfields(level, breakExp, venv, fenv, recordUsage, recordDefine);
                    // Check pass
                    int n = 0;
                    auto fieldList = Translate::makeExpList();
                    auto recordUsageField = recordUsage->getFields();
                    for (auto field = recordUsageField->begin(); field != recordUsageField->end(); field++, n++)
                    {
                        auto f = transExp(level, breakExp, venv, fenv, (*field)->getExp());
                        fieldList->push_front(f.exp);
                    }
                    auto record = Translate::makeRecordExp(n, fieldList);
                    return ExpTy(record, recordDefine->getType());
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
                auto nonValue = Translate::makeNonValueExp();
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
                    auto array = Translate::makeArrayExp(arraySize.exp, arrayInit.exp);
                    return ExpTy(array, arrayDefine->getType());
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
                auto nonValue = Translate::makeNonValueExp();
                return ExpTy(nonValue, Type::ARRAY);
            }
                break;
            case AST::SEQ_EXP:
            {
                auto exps = dynamic_pointer_cast<AST::SeqExp>(exp);
                // TODO: why need a * ?
                auto expList = exps->getSeq();
                // Check num of exps
                if (expList->size() == 0)
                {
                    auto nonValue = Translate::makeNonValueExp();
                    return ExpTy(nonValue, Type::VOID);
                }
                // Check each exp and return last exp's return value
                auto trExpList = Translate::makeExpList();
                ExpTy result;
                for (auto iter = expList->begin(); iter != expList->end(); iter++)
                {
                    result = transExp(level, breakExp, venv, fenv, (*iter));
                    trExpList->push_front(result.exp);
                }
                auto seq = Translate::makeSeqExp(trExpList);
                return ExpTy(seq, result.type);
                break;
            }
            case AST::WHILE_EXP:
            {
                auto whileUsage = dynamic_pointer_cast<AST::WhileExp>(exp);
                try
                {
                    // Check while's test condition
                    auto whileTest = transExp(level, breakExp, venv, fenv, whileUsage->getTest());
                    assertTypeMatch(whileTest.type, Type::INT, defaultLoc);
                    // Check while's body
                    auto whileBody = transExp(level, breakExp, venv, fenv, whileUsage->getBody());
                    auto done = Translate::makeDoneExp();
                    auto whileExp = Translate::makeWhileExp(whileTest.exp, whileBody.exp, done);
                    return ExpTy(whileExp, Type::VOID);
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error(e.loc, e.what());
                }
                auto nonValue = Translate::makeNonValueExp();
                return ExpTy(nonValue, Type::VOID);
                break;
            }
            case AST::ASSIGN_EXP:
            {
                auto assignUsage = dynamic_pointer_cast<AST::AssignExp>(exp);
                // Check assign's var
                auto assignVar = assignUsage->getVar();
                auto assignVarResult = transVar(level, breakExp, venv, fenv, assignVar);
                // Check assign's exp
                auto assignExp = assignUsage->getExp();
                auto assignExpResult = transExp(level, breakExp, venv, fenv, assignExp);
                // Check type
                try
                {
                    assertTypeMatch(assignVarResult.type, assignExpResult.type, defaultLoc);
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error err(e.loc, e.what());
                }
                auto assign = Translate::makeAssignExp(assignVarResult.exp, assignExpResult.exp);
                return ExpTy(assign, Type::VOID);
                break;
            }
            case AST::BREAK_EXP:
            {
                if (breakExp != nullptr)
                {
                    return ExpTy(Translate::makeNonValueExp(), Type::VOID);
                }
                else
                {
                    return ExpTy(Translate::makeBreakExp(breakExp), Type::VOID)
                }
                break;
            }
            case AST::FOR_EXP:
            {
                // TODO: convert to while inside a let expression
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
                transDec(shared_ptr<Translate::Level>(), shared_ptr<Temporary::Label>(), venv, fenv,
                         forDec);
                // Check body
                auto forBody = transExp(<#initializer#>, <#initializer#>, venv, fenv, forUsage->getBody());
                fenv.endScope();
                return ExpTy(nullptr, Type::VOID);
                break;
            }
            case AST::LET_EXP:
            {
                // Begin scope
                fenv.beginScope();
                venv.beginScope();
                // Check each exp decs
                auto letUsage = dynamic_pointer_cast<AST::LetExp>(exp);
                auto letDecs = letUsage->getDecs();
                auto expList = Translate::makeExpList();
                for (auto dec = letDecs->begin(); dec != letDecs->end(); dec++)
                {
                    auto result = transDec(shared_ptr<Translate::Level>(), shared_ptr<Temporary::Label>(), venv, fenv,
                                           *dec);
                    expList->push_front(result);
                }
                // Check let exp body
                auto letBody = letUsage->getBody();
                auto result = transExp(level, breakExp, venv, fenv, letBody);
                expList->push_front(result.exp);
                // End scope
                venv.endScope();
                fenv.endScope();
                return ExpTy(Translate::makeSeqExp(expList), result.type);
                break;
            }
            case AST::OP_EXP:
            {
                auto opUsage = dynamic_pointer_cast<AST::OpExp>(exp);
                // Check both side of op exp
                auto opLeft = transExp(level, breakExp, venv, fenv, opUsage->getLeft());
                auto opRight = transExp(level, breakExp, venv, fenv, opUsage->getRight());
                // Check type
                try
                {
                    assertTypeMatch(opLeft.type, opRight.type, opUsage->getLeft()->getLoc());
                    IR::ArithmeticOp arithOP;
                    IR::ComparisonOp compOP;
                    auto opLeftExp = opLeft.exp;
                    auto opRightExp = opRight.exp;
                    if (Type::isInt(opLeft.type))
                    {
                        /*
                         * Op exp type
                         * 0 : Arithmetic exp
                         * 1 : Comparison exp
                         */
                        int expType = 0;
                        switch (opUsage->getOp())
                        {
                            case AST::PLUS:
                                arithOP = IR::PLUS;
                                break;
                            case AST::MINUS:
                                arithOP = IR::MINUS;
                                break;
                            case AST::TIMES:
                                arithOP = IR::MUL;
                                break;
                            case AST::DIVIDE:
                                arithOP = IR::DIV;
                                break;
                            case AST::EQ:
                                expType = 1;
                                compOP = IR::EQ;
                                break;
                            case AST::NEQ:
                                expType = 1;
                                compOP = IR::NE;
                                break;
                            case AST::LT:
                                expType = 1;
                                compOP = IR::LT;
                                break;
                            case AST::LE:
                                expType = 1;
                                compOP = IR::LE;
                                break;
                            case AST::GT:
                                expType = 1;
                                compOP = IR::GT;
                                break;
                            case AST::GE:
                                expType = 1;
                                compOP = IR::GE;
                                break;
                            default:
                                expType = 2;
                                break;
                        }
                        if (expType == 0)
                        {
                            auto arithExp = Translate::makeArithmeticExp(arithOP, opLeftExp, opRightExp);
                            return ExpTy(arithExp, Type::INT);
                        }
                        else if (expType == 1)
                        {
                            auto compExp = Translate::makeIntComparisonExp(compOP, opLeftExp, opRightExp);
                            return ExpTy(compExp, Type::INT);
                        }
                        else
                        {
                            Tiger::Error err(opUsage->getLoc(), "Invalid binary operation for int");
                        }
                    }
                    else if (Type::isString(opLeft.type))
                    {
                        bool validOP = true;
                        switch (opUsage->getOp())
                        {
                            case AST::EQ:
                                compOP = IR::EQ;
                                break;
                            case AST::NEQ:
                                compOP = IR::NE;
                                break;
                            case AST::LT:
                                compOP = IR::LT;
                                break;
                            case AST::LE:
                                compOP = IR::LE;
                                break;
                            case AST::GT:
                                compOP = IR::GT;
                                break;
                            case AST::GE:
                                compOP = IR::GE;
                                break;
                            default:
                                validOP = false;
                                break;
                        }
                        if (validOP)
                        {
                            auto compExp = Translate::makeStringComparisonExp(compOP, opLeftExp, opRightExp);
                            return ExpTy(compExp, Type::INT);
                        }
                        else
                        {
                            Tiger::Error err(opUsage->getLoc(), "Invalid binary operation for string");
                        }
                    }
                    else if (Type::isRecord(opLeft.type) || Type::isArray(opLeft.type))
                    {
                        bool validOP = true;
                        switch (opUsage->getOp())
                        {
                            case AST::EQ:
                                compOP = IR::EQ;
                                break;
                            case AST::NEQ:
                                compOP = IR::NE;
                                break;
                            default:
                                validOP = false;
                                break;
                        }
                        if (validOP)
                        {
                            auto compExp = Translate::makeReferenceComparisonExp(compOP, opLeftExp, opRightExp);
                            return ExpTy(compExp, Type::INT);
                        }
                        else
                        {
                            Tiger::Error err(opUsage->getLoc(), "Invalid binary operation for reference");
                        }
                    }
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error err(e.loc, e.what());
                }
                return ExpTy(Translate::makeNonValueExp(), Type::INT);
                break;
            }
            case AST::IF_EXP:
            {
                auto ifUsage = dynamic_pointer_cast<AST::IfExp>(exp);
                auto ifTestPtr = ifUsage->getTest();
                auto ifThenPtr = ifUsage->getThen();
                auto ifElsePtr = ifUsage->getElsee();
                try
                {
                    // Check if's test condition
                    auto ifTest = transExp(level, breakExp, venv, fenv, ifTestPtr);
                    assertTypeMatch(ifTest.type, Type::INT, ifTestPtr->getLoc());
                    // Check if's then body
                    auto ifThen = transExp(level, breakExp, venv, fenv, ifThenPtr);
                    // Check if's else body
                    shared_ptr<Translate::Exp> ifExp;
                    if (ifElsePtr != nullptr)
                    {
                        auto ifElse = transExp(level, breakExp, venv, fenv, ifElsePtr);
                        assertTypeMatch(ifThen.type, ifElse.type, ifThenPtr->getLoc());
                        ifExp = Translate::makeIfExp(ifTest.exp, ifThen.exp, ifElse.exp);
                    }
                    else
                    {
                        ifExp = Translate::makeIfExp(ifTest.exp, ifThen.exp, nullptr);
                    }
                    return ExpTy(ifExp, ifThen.type);
                }
                catch (TypeNotMatchError &e)
                {
                    Tiger::Error err(e.loc, e.what());
                }
                return ExpTy(nullptr, Type::VOID);
            }
                break;
            case AST::STRING_EXP:
            {
                auto stringUsage = dynamic_pointer_cast<AST::StringExp>(exp);
                auto stringExp = Translate::makeStringExp(stringUsage->getString());
                return ExpTy(stringExp, Type::STRING);
            }
            case AST::INT_EXP:
            {
                auto intUsage = dynamic_pointer_cast<AST::IntExp>(exp);
                auto intExp = Translate::makeIntExp(intUsage->getInt());
                return ExpTy(intExp, Type::INT);
            }
            default:
            {
                // TODO: handle default case
                break;
            }
        }

        return ExpTy(nullptr, Type::VOID);
    }


    shared_ptr<Translate::Exp> transDec(const shared_ptr<Translate::Level> level,
                                        const shared_ptr<Translate::Exp> breakExp,
                                        Env::VarEnv &venv,
                                        Env::FuncEnv &fenv,
                                        const shared_ptr<AST::Dec> dec)
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
                auto varInit = transExp(level, breakExp, venv, fenv, varUsage->getInit());
                auto varAlloc = Translate::allocLocal(level, varUsage->isEscape());
                // If type name is empty
                auto varType = make_shared<Type::Type>();
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
                auto simpleVar = Translate::makeSimpleVar(varAlloc, level);
                return Translate::makeAssignExp(simpleVar, varInit.exp);
                break;
            }
            case AST::FUNCTION_DEC:
            {
                auto funcUsage = dynamic_pointer_cast<AST::FunctionDec>(dec);
                auto funcList = funcUsage->getFunction();
                // Add functions' declaration
                for (auto func = funcList->begin(); func != funcList->end(); func++)
                {
                    // Check func return type
                    auto returnTypeName = (*func)->getResult();
                    auto returnType = make_shared<Type::Type>();
                    // No return type specified, use void instead
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
                            // Return type not defined
                            Tiger::Error err(defaultLoc, e.what());
                            returnType = Type::VOID;
                        }
                    }
                    Env::FuncEntry funcEntry(level, Temporary::makeLabel(), (*func)->getName(), returnType);
                    // Check and add args to new function entry
                    auto args = (*func)->getParams();
                    for (auto arg = args->begin(); arg != args->end(); arg++)
                    {
                        auto argType = make_shared<Type::Type>();
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
                        funcEntry.addArg(argType);
                    }
                    // Add func into func environment
                    fenv.enter(funcEntry);
                }
                // Traverse all functions' body to check `return type`
                // Need to form function environment first, then traverse their body
                for (auto func = funcList->begin(); func != funcList->end(); func++)
                {
                    fenv.beginScope();
                    auto funcEntry = fenv.find((*func)->getName());
                    auto args = funcEntry->getArgs();
                    // Add args into var environment
                    for (auto arg = args->begin(); arg != args->end(); arg++)
                    {
                        auto argName = Type::getName(*arg);
                        auto argType = *arg;
                        Env::VarEntry argEntry(argName, argType, shared_ptr<Translate::Access>());
                        venv.enter(argEntry);
                    }
                    // Traverse func body
                    auto funcExp = transExp(level, breakExp, venv, fenv, (*func)->getBody());
                    try
                    {
                        auto returnType = fenv.find((*func)->getName())->getResultType();
                        assertTypeMatch(funcExp.type, returnType, (*func)->getLoc());
                    }
                    catch (Env::EntryNotFound &e)
                    {
                        Tiger::Error err((*func)->getLoc(), e.what());
                    }
                    catch (TypeNotMatchError &e)
                    {
                        Tiger::Error err((*func)->getLoc(), e.what());
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

    void checkRecordEfields(shared_ptr<Translate::Level> level,
                            shared_ptr<Translate::Exp> breakExp,
                            Env::VarEnv venv,
                            Env::FuncEnv fenv,
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
            auto t = transExp(level, breakExp, venv, fenv, (*uIter)->getExp());
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


    void checkCallArgs(shared_ptr<Translate::Level> level,
                       shared_ptr<Translate::Exp> breakExp,
                       Env::VarEnv &venv,
                       Env::FuncEnv &fenv
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
            auto t = transExp(level, breakExp, venv, fenv, (*uIter));
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