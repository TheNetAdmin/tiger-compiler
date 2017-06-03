//
// Created by CHEGE on 2017/5/25.
//

#include "absyntree.h"

namespace AST
{
// Var-------------------------------------

    Var::Var(Tiger::location loc, VariableType classType) : ASTNode(loc), classType(classType)
    {}

    VariableType Var::getClassType() const
    {
        return classType;
    }

// Exp-------------------------------------

    Exp::Exp(Tiger::location loc, ExpressionType classType) : ASTNode(loc), classType(classType)
    {}


    ExpressionType Exp::getClassType()
    {
        return classType;
    }

// Dec---------------------------------------
    Dec::Dec(Tiger::location loc, DeclarationType classType) : ASTNode(loc), classType(classType)
    {}


    DeclarationType Dec::getClassType()
    {
        return classType;
    }

// Ty---------------------------------------
    Ty::Ty(Tiger::location loc, TypeType classType) : ASTNode(loc), classType(classType)
    {}


    TypeType Ty::getClassType()
    {
        return classType;
    }

// Field------------------------------------
    Field::Field(Tiger::location loc, const string &name, const string &typ, bool escape)
            : ASTNode(loc), name(name), typ(typ), escape(escape)
    {}


    const string &Field::getName() const
    {
        return name;
    }

    const string &Field::getTyp() const
    {
        return typ;
    }

    bool Field::isEscape() const
    {
        return escape;
    }

    void Field::setEscape(bool escape)
    {
        Field::escape = escape;
    }

// EField--------------------------------------
    EField::EField(const string &name, const shared_ptr<Exp> &exp) : name(name), exp(exp)
    {}

    const string &EField::getName() const
    {
        return name;
    }

    const shared_ptr<Exp> &EField::getExp() const
    {
        return exp;
    }

// FunDec----------------------------------------
    FunDec::FunDec(Tiger::location loc, const string &name, const string &result, const shared_ptr<FieldList> &params,
                   const shared_ptr<Exp> &body) : ASTNode(loc), name(name), result(result), params(params),
                                                  body(body)
    {}


    const string &FunDec::getName() const
    {
        return name;
    }

    const string &FunDec::getResult() const
    {
        return result;
    }

    const shared_ptr<FieldList> &FunDec::getParams() const
    {
        return params;
    }

    const shared_ptr<Exp> &FunDec::getBody() const
    {
        return body;
    }

// TypeTy------------------------------------------
    TypeTy::TypeTy(const string &name, const shared_ptr<Ty> &ty) : name(name), ty(ty)
    {}

    const string &TypeTy::getName() const
    {
        return name;
    }

    const shared_ptr<Ty> &TypeTy::getTy() const
    {
        return ty;
    }

// SimpleVar----------------------------------------------

    SimpleVar::SimpleVar(Tiger::location loc, const string &simple) : Var(loc, SIMPLE_VAR), simple(simple)
    {}

    const string &SimpleVar::getSimple() const
    {
        return simple;
    }

// FieldVar----------------------------------------------

    FieldVar::FieldVar(Tiger::location loc, const shared_ptr<Var> &var, const string &sym) : Var(loc, FIELD_VAR),
                                                                                             var(var),
                                                                                             sym(sym)
    {}

    const shared_ptr<Var> FieldVar::getVar() const
    {
        return var;
    }

    const string &FieldVar::getSym() const
    {
        return sym;
    }

// SubscriptVar-------------------------------------------

    SubscriptVar::SubscriptVar(Tiger::location loc, const shared_ptr<Var> &var,
                               const shared_ptr<Exp> &exp) : Var(loc, SUBSCRIPT_VAR), var(var), exp(exp)
    {}

    const shared_ptr<Var> &SubscriptVar::getVar() const
    {
        return var;
    }

    const shared_ptr<Exp> &SubscriptVar::getExp() const
    {
        return exp;
    }

// VarExp------------------------------------------------
    VarExp::VarExp(Tiger::location loc, const shared_ptr<Var> &var) : Exp(loc, VAR_EXP),
                                                                      var(var)
    {}

    const shared_ptr<Var> &VarExp::getVar() const
    {
        return var;
    }

// NilExp-----------------------------------------------
    NilExp::NilExp(Tiger::location loc) : Exp(loc, NIL_EXP)
    {}

// IntExp----------------------------------------------
    IntExp::IntExp(Tiger::location loc, int intt) : Exp(loc, INT_EXP), intt(intt)
    {}

    int IntExp::getInt() const
    {
        return intt;
    }

// StringExp------------------------------------------
    StringExp::StringExp(Tiger::location loc, const string &stringg) : Exp(loc, STRING_EXP),
                                                                       str(stringg)
    {}

    const string &StringExp::getString() const
    {
        return str;
    }

// CallExp------------------------------------------

    CallExp::CallExp(Tiger::location loc, const string &func, const shared_ptr<ExpList> &args) : Exp(loc, CALL_EXP),
                                                                                                 func(func),
                                                                                                 args(args)
    {}

    const string &CallExp::getFunc() const
    {
        return func;
    }

    const shared_ptr<ExpList> &CallExp::getArgs() const
    {
        return args;
    }

// OpExp--------------------------------------------

    OpExp::OpExp(Tiger::location loc, Operator op, const shared_ptr<Exp> &left,
                 const shared_ptr<Exp> &right) : Exp(loc, OP_EXP), op(op), left(left), right(right)
    {}

    Operator OpExp::getOp() const
    {
        return op;
    }

    const shared_ptr<Exp> &OpExp::getLeft() const
    {
        return left;
    }

    const shared_ptr<Exp> &OpExp::getRight() const
    {
        return right;
    }

// RecordExp----------------------------------------

    RecordExp::RecordExp(Tiger::location loc, const string &typ, const shared_ptr<EFieldList> &fields) : Exp(
            loc, RECORD_EXP), typ(typ), fields(fields)
    {}

    const string &RecordExp::getTyp() const
    {
        return typ;
    }

    const shared_ptr<EFieldList> &RecordExp::getFields() const
    {
        return fields;
    }

// SeqExp------------------------------------------

    SeqExp::SeqExp(Tiger::location loc, const shared_ptr<ExpList> &seq) : Exp(loc, SEQ_EXP), seq(seq)
    {}

    const shared_ptr<ExpList> &SeqExp::getSeq() const
    {
        return seq;
    }

// AssignExp--------------------------------------

    AssignExp::AssignExp(Tiger::location loc, const shared_ptr<Var> &var,
                         const shared_ptr<Exp> &exp) : Exp(loc, ASSIGN_EXP), var(var), exp(exp)
    {}

    const shared_ptr<Var> &AssignExp::getVar() const
    {
        return var;
    }

    const shared_ptr<Exp> &AssignExp::getExp() const
    {
        return exp;
    }

// IfExp-----------------------------------------

    IfExp::IfExp(Tiger::location loc, const shared_ptr<Exp> &test, const shared_ptr<Exp> &then,
                 const shared_ptr<Exp> &elsee) : Exp(loc, IF_EXP), test(test), then(then), elsee(elsee)
    {}

    const shared_ptr<Exp> &IfExp::getTest() const
    {
        return test;
    }

    const shared_ptr<Exp> &IfExp::getThen() const
    {
        return then;
    }

    const shared_ptr<Exp> &IfExp::getElsee() const
    {
        return elsee;
    }

// WhileExp-------------------------------------

    WhileExp::WhileExp(Tiger::location loc, const shared_ptr<Exp> &test,
                       const shared_ptr<Exp> &body) : Exp(loc, WHILE_EXP), test(test), body(body)
    {}

    const shared_ptr<Exp> &WhileExp::getTest() const
    {
        return test;
    }

    const shared_ptr<Exp> &WhileExp::getBody() const
    {
        return body;
    }

// BreakExp------------------------------------

    BreakExp::BreakExp(Tiger::location loc) : Exp(loc, BREAK_EXP)
    {}

// ForExp--------------------------------------


    ForExp::ForExp(Tiger::location loc, const string &var, const shared_ptr<Exp> &lo, const shared_ptr<Exp> &hi,
                   const shared_ptr<Exp> &body, bool escape) : Exp(loc, FOR_EXP), var(var), lo(lo), hi(hi),
                                                               body(body), escape(escape)
    {}

    const string &ForExp::getVar() const
    {
        return var;
    }

    const shared_ptr<Exp> &ForExp::getLo() const
    {
        return lo;
    }

    const shared_ptr<Exp> &ForExp::getHi() const
    {
        return hi;
    }

    const shared_ptr<Exp> &ForExp::getBody() const
    {
        return body;
    }

    bool ForExp::isEscape() const
    {
        return escape;
    }

    void ForExp::setEscape(bool escape)
    {
        ForExp::escape = escape;
    }


// LetExp--------------------------------------

    LetExp::LetExp(Tiger::location loc, const shared_ptr<DecList> &decs, const shared_ptr<Exp> &body)
            : Exp(loc, LET_EXP), decs(decs), body(body)
    {}

    const shared_ptr<DecList> &LetExp::getDecs() const
    {
        return decs;
    }

    const shared_ptr<Exp> &LetExp::getBody() const
    {
        return body;
    }


// ArrayExp-----------------------------------

    ArrayExp::ArrayExp(Tiger::location loc, const string &typ, const shared_ptr<Exp> &size,
                       const shared_ptr<Exp> &init) : Exp(loc, ARRAY_EXP), typ(typ), size(size), init(init)
    {}

    const string &ArrayExp::getTyp() const
    {
        return typ;
    }

    const shared_ptr<Exp> &ArrayExp::getSize() const
    {
        return size;
    }

    const shared_ptr<Exp> &ArrayExp::getInit() const
    {
        return init;
    }


// FunctionDec-------------------------------

    FunctionDec::FunctionDec(Tiger::location loc, const shared_ptr<FunDecList> function) : Dec(loc, FUNCTION_DEC),
                                                                                           function(function)
    {}

    const shared_ptr<FunDecList> &FunctionDec::getFunction() const
    {
        return function;
    }


// VarDec-----------------------------------

    VarDec::VarDec(Tiger::location loc, const string &var, const string &typ, const shared_ptr<Exp> &init, bool escape)
            : Dec(loc, VAR_DEC), var(var), typ(typ), init(init), escape(escape)
    {}

    const string &VarDec::getVar() const
    {
        return var;
    }

    const string &VarDec::getTyp() const
    {
        return typ;
    }

    const shared_ptr<Exp> &VarDec::getInit() const
    {
        return init;
    }

    bool VarDec::isEscape() const
    {
        return escape;
    }

    void VarDec::setEscape(bool escape)
    {
        VarDec::escape = escape;
    }


// TypeDec--------------------------------

    TypeDec::TypeDec(Tiger::location loc, const shared_ptr<TypeTyList> &type) : Dec(loc, TYPE_DEC), type(type)
    {}

    const shared_ptr<TypeTyList> &TypeDec::getType() const
    {
        return type;
    }


// NameTy----------------------------------

    NameTy::NameTy(Tiger::location loc, const string &name) : Ty(loc, NAME_TYPE), name(name)
    {}

    const string &NameTy::getName() const
    {
        return name;
    }


// RecordTy--------------------------------

    RecordTy::RecordTy(Tiger::location loc, const shared_ptr<FieldList> &record) : Ty(loc, RECORD_TYPE), record(record)
    {}

    const shared_ptr<FieldList> &RecordTy::getRecord() const
    {
        return record;
    }


// ArrayTy---------------------------------

    ArrayTy::ArrayTy(Tiger::location loc, const string &array) : Ty(loc, ARRAY_TYPE), array(array)
    {}

    const string &ArrayTy::getArray() const
    {
        return array;
    }


// Function used in parser(bison)

    shared_ptr<Var> MakeSimpleVar(Tiger::location loc, string &sym)
    {
        return make_shared<SimpleVar>(loc, sym);
    }

    shared_ptr<Var> MakeFieldVar(Tiger::location loc, shared_ptr<Var> var, string &sym)
    {
        return make_shared<FieldVar>(loc, var, sym);
    }

    shared_ptr<Var> MakeSubscriptVar(Tiger::location loc, shared_ptr<Var> var, shared_ptr<Exp> exp)
    {
        return make_shared<SubscriptVar>(loc, var, exp);
    }

    shared_ptr<Exp> MakeVarExp(Tiger::location loc, shared_ptr<Var> sym)
    {
        return make_shared<VarExp>(loc, sym);
    }

    shared_ptr<Exp> MakeNilExp(Tiger::location loc)
    {
        return make_shared<NilExp>(loc);
    }

    shared_ptr<Exp> MakeIntExp(Tiger::location loc, int i)
    {
        return make_shared<IntExp>(loc, i);
    }

    shared_ptr<Exp> MakeStringExp(Tiger::location loc, string &s)
    {
        return make_shared<StringExp>(loc, s);
    }

    shared_ptr<Exp> MakeCallExp(Tiger::location loc, string &func, shared_ptr<ExpList> args)
    {
        return make_shared<CallExp>(loc, func, args);
    }

    shared_ptr<Exp> MakeOpExp(Tiger::location loc, Operator oper, shared_ptr<Exp> left, shared_ptr<Exp> right)
    {
        return make_shared<OpExp>(loc, oper, left, right);
    }

    shared_ptr<Exp> MakeRecordExp(Tiger::location loc, string &typ, shared_ptr<EFieldList> fields)
    {
        return make_shared<RecordExp>(loc, typ, fields);
    }

    shared_ptr<Exp> MakeSeqExp(Tiger::location loc, shared_ptr<ExpList> seq)
    {
        return make_shared<SeqExp>(loc, seq);
    }

    shared_ptr<Exp> MakeAssignExp(Tiger::location loc, shared_ptr<Var> var, shared_ptr<Exp> exp)
    {
        return make_shared<AssignExp>(loc, var, exp);
    }

    shared_ptr<Exp> MakeIfExp(Tiger::location loc, shared_ptr<Exp> test, shared_ptr<Exp> then, shared_ptr<Exp> elsee)
    {
        return make_shared<IfExp>(loc, test, then, elsee);
    }

    shared_ptr<Exp> MakeWhileExp(Tiger::location loc, shared_ptr<Exp> test, shared_ptr<Exp> body)
    {
        return make_shared<WhileExp>(loc, test, body);
    }

    shared_ptr<Exp>
    MakeForExp(Tiger::location loc, string &var, shared_ptr<Exp> lo, shared_ptr<Exp> hi, shared_ptr<Exp> body)
    {
        return make_shared<ForExp>(loc, var, lo, hi, body, true);
    }

    shared_ptr<Exp> MakeBreakExp(Tiger::location loc)
    {
        return make_shared<BreakExp>(loc);
    }

    shared_ptr<Exp> MakeLetExp(Tiger::location loc, shared_ptr<DecList> decs, shared_ptr<Exp> body)
    {
        return make_shared<LetExp>(loc, decs, body);
    }

    shared_ptr<Exp> MakeArrayExp(Tiger::location loc, string &typ, shared_ptr<Exp> size, shared_ptr<Exp> init)
    {
        return make_shared<ArrayExp>(loc, typ, size, init);
    }

    shared_ptr<Dec> MakeFunctionDec(Tiger::location loc, shared_ptr<FunDecList> function)
    {
        auto func = make_shared<FunctionDec>(loc, function);
        return func;
    }

    shared_ptr<Dec> MakeVarDec(Tiger::location loc, const string &var, const string &typ, shared_ptr<Exp> init)
    {
        return make_shared<VarDec>(loc, var, typ, init, true);
    }

    shared_ptr<Dec> MakeTypeDec(Tiger::location loc, shared_ptr<TypeTyList> type)
    {
        return make_shared<TypeDec>(loc, type);
    }

    shared_ptr<Ty> MakeNameTy(Tiger::location loc, string &name)
    {
        return make_shared<NameTy>(loc, name);
    }

    shared_ptr<Ty> MakeRecordTy(Tiger::location loc, shared_ptr<FieldList> record)
    {
        return make_shared<RecordTy>(loc, record);
    }

    shared_ptr<Ty> MakeArrayTy(Tiger::location loc, string &array)
    {
        return make_shared<ArrayTy>(loc, array);
    }

    shared_ptr<Field> MakeField(Tiger::location loc, string &name, string &typ)
    {
        return make_shared<Field>(loc, name, typ, true);
    }

    shared_ptr<FieldList> MakeFieldList(shared_ptr<Field> head, shared_ptr<FieldList> tail)
    {
        if (tail == nullptr)
            tail = make_shared<FieldList>();
        tail->push_front(head);
        return tail;
    }

    shared_ptr<ExpList> MakeExpList(shared_ptr<Exp> head, shared_ptr<ExpList> tail)
    {
        if (tail == nullptr)
            tail = make_shared<ExpList>();
        tail->push_front(head);
        return tail;
    }

    shared_ptr<FunDec>
    MakeFunDec(Tiger::location loc, string &name, string &result, shared_ptr<FieldList> params, shared_ptr<Exp> body)
    {
        return make_shared<FunDec>(loc, name, result, params, body);
    }

    shared_ptr<FunDecList> MakeFunDecList(shared_ptr<FunDec> head, shared_ptr<FunDecList> tail)
    {
        if (tail == nullptr)
            tail = make_shared<FunDecList>();
        tail->push_front(head);
        return tail;
    }

    shared_ptr<DecList> MakeDecList(shared_ptr<Dec> head, shared_ptr<DecList> tail)
    {
        if (tail == nullptr)
            tail = make_shared<DecList>();
        tail->push_front(head);
        return tail;
    }


    shared_ptr<TypeTy> MakeTypeTy(string &name, shared_ptr<Ty> ty)
    {
        return make_shared<TypeTy>(name, ty);
    }

    shared_ptr<TypeTyList> MakeTypeTyList(shared_ptr<TypeTy> head, shared_ptr<TypeTyList> tail)
    {
        if (tail == nullptr)
            tail = make_shared<TypeTyList>();
        tail->push_front(head);
        return tail;
    }

    shared_ptr<EField> MakeEField(string &name, shared_ptr<Exp> exp)
    {
        return make_shared<EField>(name, exp);
    }

    shared_ptr<EFieldList> MakeEFieldList(shared_ptr<EField> head, shared_ptr<EFieldList> tail)
    {
        if (tail == nullptr)
            tail = make_shared<EFieldList>();
        tail->push_front(head);
        return tail;
    }


}