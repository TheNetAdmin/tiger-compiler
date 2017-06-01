//
// Created by CHEGE on 2017/5/25.
//

#include "absyntree.h"

// VarAST-------------------------------------

VarAST::VarAST(Tiger::location loc, VariableType classType) : AST(loc), classType(classType) {}

VariableType VarAST::getClassType() const {
    return classType;
}

// ExpAST-------------------------------------

ExpAST::ExpAST(Tiger::location loc, ExpressionType classType) : AST(loc), classType(classType) {}


ExpressionType ExpAST::getClassType() {
    return classType;
}

// DecAST---------------------------------------
DecAST::DecAST(Tiger::location loc, DeclarationType classType) : AST(loc), classType(classType) {}


DeclarationType DecAST::getClassType() {
    return classType;
}

// TyAST---------------------------------------
TyAST::TyAST(Tiger::location loc, TypeType classType) : AST(loc), classType(classType) {}


TypeType TyAST::getClassType() {
    return classType;
}

// FieldAST------------------------------------
FieldAST::FieldAST(Tiger::location loc, const string &name, const string &typ, bool escape)
        : AST(loc), name(name), typ(typ), escape(escape){}


const string &FieldAST::getName() const {
    return name;
}

const string &FieldAST::getTyp() const {
    return typ;
}

bool FieldAST::isEscape() const {
    return escape;
}

void FieldAST::setEscape(bool escape) {
    FieldAST::escape = escape;
}

// EFieldAST--------------------------------------
EFieldAST::EFieldAST(const string &name, const shared_ptr<ExpAST> &exp) : name(name), exp(exp) {}

const string &EFieldAST::getName() const {
    return name;
}

const shared_ptr<ExpAST> &EFieldAST::getExp() const {
    return exp;
}

// FunDecAST----------------------------------------
FunDecAST::FunDecAST(Tiger::location loc, const string &name, const string &result, const shared_ptr<FieldListAST> &params,
                     const shared_ptr<ExpAST> &body) : AST(loc), name(name), result(result), params(params),
                                                       body(body) {}


const string &FunDecAST::getName() const {
    return name;
}

const string &FunDecAST::getResult() const {
    return result;
}

const shared_ptr<FieldListAST> &FunDecAST::getParams() const {
    return params;
}

const shared_ptr<ExpAST> &FunDecAST::getBody() const {
    return body;
}

// TypeTyAST------------------------------------------
TypeTyAST::TypeTyAST(const string &name, const shared_ptr<TyAST> &ty) : name(name), ty(ty) {}

const string &TypeTyAST::getName() const {
    return name;
}

const shared_ptr<TyAST> &TypeTyAST::getTy() const {
    return ty;
}

// SimpleVarAST----------------------------------------------

SimpleVarAST::SimpleVarAST(Tiger::location loc, const string &simple) : VarAST(loc, SIMPLE_VAR), simple(simple) {}

const string &SimpleVarAST::getSimple() const {
    return simple;
}

// FieldVarAST----------------------------------------------

FieldVarAST::FieldVarAST(Tiger::location loc, const shared_ptr<VarAST> &var, const string &sym) : VarAST(loc, FIELD_VAR), var(var),
                                                                                      sym(sym) {}

const shared_ptr<VarAST> FieldVarAST::getVar() const {
    return var;
}

const string &FieldVarAST::getSym() const {
    return sym;
}

// SubscriptVarAST-------------------------------------------

SubscriptVarAST::SubscriptVarAST(Tiger::location loc, const shared_ptr<VarAST> &var,
                                 const shared_ptr<ExpAST> &exp) : VarAST(loc, SUBSCRIPT_VAR), var(var), exp(exp) {}

const shared_ptr<VarAST> &SubscriptVarAST::getVar() const {
    return var;
}

const shared_ptr<ExpAST> &SubscriptVarAST::getExp() const {
    return exp;
}

// VarExpAST------------------------------------------------
VarExpAST::VarExpAST(Tiger::location loc, const shared_ptr<VarAST> &var) : ExpAST(loc, VAR_EXP),
                                                               var(var) {}

const shared_ptr<VarAST> &VarExpAST::getVar() const {
    return var;
}

// NilExpAST-----------------------------------------------
NilExpAST::NilExpAST(Tiger::location loc) : ExpAST(loc, NIL_EXP) {}

// IntExpAST----------------------------------------------
IntExpAST::IntExpAST(Tiger::location loc, int intt) : ExpAST(loc, INT_EXP), intt(intt) {}

int IntExpAST::getIntt() const {
    return intt;
}

// StringExpAST------------------------------------------
StringExpAST::StringExpAST(Tiger::location loc, const string &stringg) : ExpAST(loc, STRING_EXP),
                                                             stringg(stringg) {}

const string &StringExpAST::getStringg() const {
    return stringg;
}

// CallExpAST------------------------------------------

CallExpAST::CallExpAST(Tiger::location loc, const string &func, const shared_ptr<ExpListAST> &args) : ExpAST(loc, CALL_EXP), func(func),
                                                                              args(args) {}

const string &CallExpAST::getFunc() const {
    return func;
}

const shared_ptr<ExpListAST> &CallExpAST::getArgs() const {
    return args;
}

// OpExpAST--------------------------------------------

OpExpAST::OpExpAST(Tiger::location loc, Operator op, const shared_ptr<ExpAST> &left,
                   const shared_ptr<ExpAST> &right) : ExpAST(loc, OP_EXP), op(op), left(left), right(right) {}

Operator OpExpAST::getOp() const {
    return op;
}

const shared_ptr<ExpAST> &OpExpAST::getLeft() const {
    return left;
}

const shared_ptr<ExpAST> &OpExpAST::getRight() const {
    return right;
}

// RecordExpAST----------------------------------------

RecordExpAST::RecordExpAST(Tiger::location loc, const string &typ, const shared_ptr<EFieldListAST> &fields) : ExpAST(
        loc, RECORD_EXP), typ(typ), fields(fields) {}

const string &RecordExpAST::getTyp() const {
    return typ;
}

const shared_ptr<EFieldListAST> &RecordExpAST::getFields() const {
    return fields;
}

// SeqExpAST------------------------------------------

SeqExpAST::SeqExpAST(Tiger::location loc, const shared_ptr<ExpListAST> &seq) : ExpAST(loc, SEQ_EXP), seq(seq) {}

const shared_ptr<ExpListAST> &SeqExpAST::getSeq() const {
    return seq;
}

// AssignExpAST--------------------------------------

AssignExpAST::AssignExpAST(Tiger::location loc, const shared_ptr<VarAST> &var,
                           const shared_ptr<ExpAST> &exp) : ExpAST(loc, ASSIGN_EXP), var(var), exp(exp) {}

const shared_ptr<VarAST> &AssignExpAST::getVar() const {
    return var;
}

const shared_ptr<ExpAST> &AssignExpAST::getExp() const {
    return exp;
}

// IfExpAST-----------------------------------------

IfExpAST::IfExpAST(Tiger::location loc, const shared_ptr<ExpAST> &test, const shared_ptr<ExpAST> &then,
                   const shared_ptr<ExpAST> &elsee) : ExpAST(loc, IF_EXP), test(test), then(then), elsee(elsee) {}

const shared_ptr<ExpAST> &IfExpAST::getTest() const {
    return test;
}

const shared_ptr<ExpAST> &IfExpAST::getThen() const {
    return then;
}

const shared_ptr<ExpAST> &IfExpAST::getElsee() const {
    return elsee;
}

// WhileExpAST-------------------------------------

WhileExpAST::WhileExpAST(Tiger::location loc, const shared_ptr<ExpAST> &test,
                         const shared_ptr<ExpAST> &body) : ExpAST(loc, WHILE_EXP), test(test), body(body) {}

const shared_ptr<ExpAST> &WhileExpAST::getTest() const {
    return test;
}

const shared_ptr<ExpAST> &WhileExpAST::getBody() const {
    return body;
}

// BreakExpAST------------------------------------

BreakExpAST::BreakExpAST(Tiger::location loc) : ExpAST(loc, BREAK_EXP) {}

// ForExpAST--------------------------------------


ForExpAST::ForExpAST(Tiger::location loc, const string &var, const shared_ptr<ExpAST> &lo, const shared_ptr<ExpAST> &hi,
                     const shared_ptr<ExpAST> &body, bool escape) : ExpAST(loc, FOR_EXP), var(var), lo(lo), hi(hi),
                                                                    body(body), escape(escape) {}

const string &ForExpAST::getVar() const {
    return var;
}

const shared_ptr<ExpAST> &ForExpAST::getLo() const {
    return lo;
}

const shared_ptr<ExpAST> &ForExpAST::getHi() const {
    return hi;
}

const shared_ptr<ExpAST> &ForExpAST::getBody() const {
    return body;
}

bool ForExpAST::isEscape() const {
    return escape;
}

void ForExpAST::setEscape(bool escape) {
    ForExpAST::escape = escape;
}


// LetExpAST--------------------------------------

LetExpAST::LetExpAST(Tiger::location loc, const shared_ptr<DecListAST> &decs, const shared_ptr<ExpAST> &body)
        : ExpAST(loc, LET_EXP), decs(decs), body(body) {}

const shared_ptr<DecListAST> &LetExpAST::getDecs() const {
    return decs;
}

const shared_ptr<ExpAST> &LetExpAST::getBody() const {
    return body;
}


// ArrayExpAST-----------------------------------

ArrayExpAST::ArrayExpAST(Tiger::location loc, const string &typ, const shared_ptr<ExpAST> &size,
                         const shared_ptr<ExpAST> &init) : ExpAST(loc, ARRAY_EXP), typ(typ), size(size), init(init) {}

const string &ArrayExpAST::getTyp() const {
    return typ;
}

const shared_ptr<ExpAST> &ArrayExpAST::getSize() const {
    return size;
}

const shared_ptr<ExpAST> &ArrayExpAST::getInit() const {
    return init;
}


// FunctionDecAST-------------------------------

FunctionDecAST::FunctionDecAST(Tiger::location loc, const shared_ptr<FunDecListAST> &function) : DecAST(loc, FUNCTION_DEC),
                                                                         function(function) {}

const shared_ptr<FunDecListAST> &FunctionDecAST::getFunction() const {
    return function;
}


// VarDecAST-----------------------------------

VarDecAST::VarDecAST(Tiger::location loc, const string &var, const string &typ, const shared_ptr<ExpAST> &init, bool escape)
        : DecAST(loc, VAR_DEC), var(var), typ(typ), init(init), escape(escape) {}

const string &VarDecAST::getVar() const {
    return var;
}

const string &VarDecAST::getTyp() const {
    return typ;
}

const shared_ptr<ExpAST> &VarDecAST::getInit() const {
    return init;
}

bool VarDecAST::isEscape() const {
    return escape;
}

void VarDecAST::setEscape(bool escape) {
    VarDecAST::escape = escape;
}


// TypeDecAST--------------------------------

TypeDecAST::TypeDecAST(Tiger::location loc, const shared_ptr<TypeTyListAST> &type) : DecAST(loc, TYPE_DEC), type(type) {}

const shared_ptr<TypeTyListAST> &TypeDecAST::getType() const {
    return type;
}


// NameTyAST----------------------------------

NameTyAST::NameTyAST(Tiger::location loc, const string &name) : TyAST(loc, NAME_TYPE), name(name) {}

const string &NameTyAST::getName() const {
    return name;
}


// RecordTyAST--------------------------------

RecordTyAST::RecordTyAST(Tiger::location loc, const shared_ptr<FieldListAST> &record) : TyAST(loc, RECORD_TYPE), record(record) {}

const shared_ptr<FieldListAST> &RecordTyAST::getRecord() const {
    return record;
}


// ArrayTyAST---------------------------------

ArrayTyAST::ArrayTyAST(Tiger::location loc, const string &array) : TyAST(loc, ARRAY_TYPE), array(array) {}

const string &ArrayTyAST::getArray() const {
    return array;
}


// Function used in parser(bison)

shared_ptr<VarAST> MakeSimpleVarAST(Tiger::location loc, string &sym) {
    return make_shared<SimpleVarAST>(loc, sym);
}

shared_ptr<VarAST> MakeFieldVarAST(Tiger::location loc, shared_ptr<VarAST> var, string &sym) {
    return make_shared<FieldVarAST>(loc, var, sym);
}

shared_ptr<VarAST> MakeSubscriptVarAST(Tiger::location loc, shared_ptr<VarAST> var, shared_ptr<ExpAST> exp) {
    return make_shared<SubscriptVarAST>(loc, var, exp);
}

shared_ptr<ExpAST> MakeVarExpAST(Tiger::location loc, shared_ptr<VarAST> sym) {
    return make_shared<VarExpAST>(loc, sym);
}

shared_ptr<ExpAST> MakeNilExpAST(Tiger::location loc) {
    return make_shared<NilExpAST>(loc);
}

shared_ptr<ExpAST> MakeIntExpAST(Tiger::location loc, int i) {
    return make_shared<IntExpAST>(loc, i);
}

shared_ptr<ExpAST> MakeStringExpAST(Tiger::location loc, string &s) {
    return make_shared<StringExpAST>(loc, s);
}

shared_ptr<ExpAST> MakeCallExpAST(Tiger::location loc, string &func, shared_ptr<ExpListAST> args) {
    return make_shared<CallExpAST>(loc, func, args);
}

shared_ptr<ExpAST> MakeOpExpAST(Tiger::location loc, Operator oper, shared_ptr<ExpAST> left, shared_ptr<ExpAST> right) {
    return make_shared<OpExpAST>(loc, oper, left, right);
}

shared_ptr<ExpAST> MakeRecordExpAST(Tiger::location loc, string &typ, shared_ptr<EFieldListAST> fields) {
    return make_shared<RecordExpAST>(loc, typ, fields);
}

shared_ptr<ExpAST> MakeSeqExpAST(Tiger::location loc, shared_ptr<ExpListAST> seq) {
    return make_shared<SeqExpAST>(loc, seq);
}

shared_ptr<ExpAST> MakeAssignExpAST(Tiger::location loc, shared_ptr<VarAST> var, shared_ptr<ExpAST> exp) {
    return make_shared<AssignExpAST>(loc, var, exp);
}

shared_ptr<ExpAST> MakeIfExpAST(Tiger::location loc, shared_ptr<ExpAST> test, shared_ptr<ExpAST> then, shared_ptr<ExpAST> elsee) {
    return make_shared<IfExpAST>(loc, test, then, elsee);
}

shared_ptr<ExpAST> MakeWhileExpAST(Tiger::location loc, shared_ptr<ExpAST> test, shared_ptr<ExpAST> body) {
    return make_shared<WhileExpAST>(loc, test, body);
}

shared_ptr<ExpAST>
MakeForExpAST(Tiger::location loc, string &var, shared_ptr<ExpAST> lo, shared_ptr<ExpAST> hi, shared_ptr<ExpAST> body) {
    return make_shared<ForExpAST>(loc, var, lo, hi, body, true);
}

shared_ptr<ExpAST> MakeBreakExpAST(Tiger::location loc) {
    return make_shared<BreakExpAST>(loc);
}

shared_ptr<ExpAST> MakeLetExpAST(Tiger::location loc, shared_ptr<DecListAST> decs, shared_ptr<ExpAST> body) {
    return make_shared<LetExpAST>(loc, decs, body);
}

shared_ptr<ExpAST> MakeArrayExpAST(Tiger::location loc, string &typ, shared_ptr<ExpAST> size, shared_ptr<ExpAST> init) {
    return make_shared<ArrayExpAST>(loc, typ, size, init);
}

shared_ptr<DecAST> MakeFunctionDecAST(Tiger::location loc, shared_ptr<FunDecListAST> function) {
    return make_shared<FunctionDecAST>(loc, function);
}

shared_ptr<DecAST> MakeVarDecAST(Tiger::location loc, const string &var, const string &typ, shared_ptr<ExpAST> init)
{
    return make_shared<VarDecAST>(loc, var, typ, init, true);
}

shared_ptr<DecAST> MakeTypeDecAST(Tiger::location loc, shared_ptr<TypeTyListAST> type) {
    return make_shared<TypeDecAST>(loc, type);
}

shared_ptr<TyAST> MakeNameTyAST(Tiger::location loc, string &name) {
    return make_shared<NameTyAST>(loc, name);
}

shared_ptr<TyAST> MakeRecordTyAST(Tiger::location loc, shared_ptr<FieldListAST> record) {
    return make_shared<RecordTyAST>(loc, record);
}

shared_ptr<TyAST> MakeArrayTyAST(Tiger::location loc, string &array) {
    return make_shared<ArrayTyAST>(loc, array);
}

shared_ptr<FieldAST> MakeFieldAST(Tiger::location loc, string &name, string &typ) {
    return make_shared<FieldAST>(loc, name, typ, true);
}

shared_ptr<FieldListAST> MakeFieldListAST(shared_ptr<FieldAST> head, shared_ptr<FieldListAST> tail) {
    if (tail == nullptr)
        tail = make_shared<FieldListAST>();
    tail->push_front(head);
    return tail;
}

shared_ptr<ExpListAST> MakeExpListAST(shared_ptr<ExpAST> head, shared_ptr<ExpListAST> tail) {
    if (tail == nullptr)
        tail = make_shared<ExpListAST>();
    tail->push_front(head);
    return tail;
}

shared_ptr<FunDecAST>
MakeFunDecAST(Tiger::location loc, string &name, string &result, shared_ptr<FieldListAST> params, shared_ptr<ExpAST> body) {
    return make_shared<FunDecAST>(loc, name, result, params, body);
}

shared_ptr<FunDecListAST> MakeFunDecListAST(shared_ptr<FunDecAST> head, shared_ptr<FunDecListAST> tail) {
    if (tail == nullptr)
        tail = make_shared<FunDecListAST>();
    tail->push_front(head);
    return tail;
}

shared_ptr<DecListAST> MakeDecListAST(shared_ptr<DecAST> head, shared_ptr<DecListAST> tail) {
    if (tail == nullptr)
        tail = make_shared<DecListAST>();
    tail->push_front(head);
    return tail;
}


shared_ptr<TypeTyAST> MakeTypeTyAST(string &name, shared_ptr<TyAST> ty) {
   return make_shared<TypeTyAST>(name, ty);
}

shared_ptr<TypeTyListAST> MakeTypeTyListAST(shared_ptr<TypeTyAST> head, shared_ptr<TypeTyListAST> tail) {
    if (tail == nullptr)
        tail = make_shared<TypeTyListAST>();
    tail->push_front(head);
    return tail;
}

shared_ptr<EFieldAST> MakeEFieldAST(string &name, shared_ptr<ExpAST> exp) {
    return make_shared<EFieldAST>(name, exp);
}

shared_ptr<EFieldListAST> MakeEFieldListAST(shared_ptr<EFieldAST> head, shared_ptr<EFieldListAST> tail) {
    if (tail == nullptr)
        tail = make_shared<EFieldListAST>();
    tail->push_front(head);
    return tail;
}


