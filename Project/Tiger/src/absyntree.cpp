//
// Created by CHEGE on 2017/5/25.
//

#include "absyntree.h"

// VarAST-------------------------------------

VarAST::VarAST(int pos, VaribleType classType) : pos(pos), classType(classType) {}

int VarAST::getPos() const {
    return pos;
}

VaribleType VarAST::getClassType() const {
    return classType;
}

// ExpAST-------------------------------------

ExpAST::ExpAST(int pos, ExpressionType classType) : pos(pos), classType(classType) {}

int ExpAST::getPos() const {
    return pos;
}

ExpressionType ExpAST::getClassType() {
    return classType;
}

// DecAST---------------------------------------
DecAST::DecAST(int pos, DeclarationType classType) : pos(pos), classType(classType) {}

int DecAST::getPos() const {
    return pos;
}

DeclarationType DecAST::getClassType() {
    return classType;
}

// TyAST---------------------------------------
TyAST::TyAST(int pos, TypeType classType) : pos(pos), classType(classType) {}

int TyAST::getPos() const {
    return pos;
}

TypeType TyAST::getClassType() {
    return classType;
}

// FieldAST------------------------------------
FieldAST::FieldAST(int pos, const string &name, const string &typ, bool escape) : pos(pos), name(name), typ(typ),
                                                                                  escape(escape) {}

int FieldAST::getPos() const {
    return pos;
}

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
FunDecAST::FunDecAST(int pos, const string &name, const string &result, const shared_ptr<FieldListAST> &params,
                     const shared_ptr<ExpAST> &body) : pos(pos), name(name), result(result), params(params),
                                                       body(body) {}

int FunDecAST::getPos() const {
    return pos;
}

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

SimpleVarAST::SimpleVarAST(int pos, const string &simple) : VarAST(pos, SIMPLE_VAR), simple(simple) {}

const string &SimpleVarAST::getSimple() const {
    return simple;
}

// FieldVarAST----------------------------------------------

FieldVarAST::FieldVarAST(int pos, const shared_ptr<VarAST> &var, const string &sym) : VarAST(pos, FIELD_VAR), var(var),
                                                                                      sym(sym) {}

const shared_ptr<VarAST> &FieldVarAST::getVar() const {
    return var;
}

const string &FieldVarAST::getSym() const {
    return sym;
}

// SubscriptVarAST-------------------------------------------

SubscriptVarAST::SubscriptVarAST(int pos, const shared_ptr<VarAST> &var,
                                 const shared_ptr<ExpAST> &exp) : VarAST(pos, SUBSCRIPT_VAR), var(var), exp(exp) {}

const shared_ptr<VarAST> &SubscriptVarAST::getVar() const {
    return var;
}

const shared_ptr<ExpAST> &SubscriptVarAST::getExp() const {
    return exp;
}

// VarExpAST------------------------------------------------
VarExpAST::VarExpAST(int pos, const shared_ptr<VarAST> &var) : ExpAST(pos, VAR_EXP),
                                                               var(var) {}

const shared_ptr<VarAST> &VarExpAST::getVar() const {
    return var;
}

// NilExpAST-----------------------------------------------
NilExpAST::NilExpAST(int pos) : ExpAST(pos, NIL_EXP) {}

// IntExpAST----------------------------------------------
IntExpAST::IntExpAST(int pos, int intt) : ExpAST(pos, INT_EXP), intt(intt) {}

int IntExpAST::getIntt() const {
    return intt;
}

// StringExpAST------------------------------------------
StringExpAST::StringExpAST(int pos, const string &stringg) : ExpAST(pos, STRING_EXP),
                                                             stringg(stringg) {}

const string &StringExpAST::getStringg() const {
    return stringg;
}

// CallExpAST------------------------------------------

CallExpAST::CallExpAST(int pos, const string &func, const shared_ptr<ExpListAST> &args) : ExpAST(pos, CALL_EXP), func(func),
                                                                              args(args) {}

const string &CallExpAST::getFunc() const {
    return func;
}

const shared_ptr<ExpListAST> &CallExpAST::getArgs() const {
    return args;
}

// OpExpAST--------------------------------------------

OpExpAST::OpExpAST(int pos, Operator op, const shared_ptr<ExpAST> &left,
                   const shared_ptr<ExpAST> &right) : ExpAST(pos, OP_EXP), op(op), left(left), right(right) {}

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

RecordExpAST::RecordExpAST(int pos, const string &typ, const shared_ptr<EFieldListAST> &fields) : ExpAST(
        pos, RECORD_EXP), typ(typ), fields(fields) {}

const string &RecordExpAST::getTyp() const {
    return typ;
}

const shared_ptr<EFieldListAST> &RecordExpAST::getFields() const {
    return fields;
}

// SeqExpAST------------------------------------------

SeqExpAST::SeqExpAST(int pos, const shared_ptr<ExpListAST> &seq) : ExpAST(pos, SEQ_EXP), seq(seq) {}

const shared_ptr<ExpListAST> &SeqExpAST::getSeq() const {
    return seq;
}

// AssignExpAST--------------------------------------

AssignExpAST::AssignExpAST(int pos, const shared_ptr<VarAST> &var,
                           const shared_ptr<ExpAST> &exp) : ExpAST(pos, ASSING_EXP), var(var), exp(exp) {}

const shared_ptr<VarAST> &AssignExpAST::getVar() const {
    return var;
}

const shared_ptr<ExpAST> &AssignExpAST::getExp() const {
    return exp;
}

// IfExpAST-----------------------------------------

IfExpAST::IfExpAST(int pos, const shared_ptr<ExpAST> &test, const shared_ptr<ExpAST> &then,
                   const shared_ptr<ExpAST> &elsee) : ExpAST(pos, IF_EXP), test(test), then(then), elsee(elsee) {}

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

WhileExpAST::WhileExpAST(int pos, const shared_ptr<ExpAST> &test,
                         const shared_ptr<ExpAST> &body) : ExpAST(pos, WHILE_EXP), test(test), body(body) {}

const shared_ptr<ExpAST> &WhileExpAST::getTest() const {
    return test;
}

const shared_ptr<ExpAST> &WhileExpAST::getBody() const {
    return body;
}

// BreakExpAST------------------------------------

BreakExpAST::BreakExpAST(int pos) : ExpAST(pos, BREAK_EXP) {}

// ForExpAST--------------------------------------


ForExpAST::ForExpAST(int pos, const string &var, const shared_ptr<ExpAST> &lo, const shared_ptr<ExpAST> &hi,
                     const shared_ptr<ExpAST> &body, bool escape) : ExpAST(pos, FOR_EXP), var(var), lo(lo), hi(hi),
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

LetExpAST::LetExpAST(int pos, const shared_ptr<DecListAST> &decs, const shared_ptr<ExpAST> &body)
        : ExpAST(pos, LET_EXP), decs(decs), body(body) {}

const shared_ptr<DecListAST> &LetExpAST::getDecs() const {
    return decs;
}

const shared_ptr<ExpAST> &LetExpAST::getBody() const {
    return body;
}


// ArrayExpAST-----------------------------------

ArrayExpAST::ArrayExpAST(int pos, const string &typ, const shared_ptr<ExpAST> &size,
                         const shared_ptr<ExpAST> &init) : ExpAST(pos, ARRAY_EXP), typ(typ), size(size), init(init) {}

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

FunctionDecAST::FunctionDecAST(int pos, const shared_ptr<FunDecListAST> &function) : DecAST(pos, FUNCTION_DEC),
                                                                         function(function) {}

const shared_ptr<FunDecListAST> &FunctionDecAST::getFunction() const {
    return function;
}


// VarDecAST-----------------------------------

VarDecAST::VarDecAST(int pos, const string &var, const string &typ, const shared_ptr<ExpAST> &init, bool escape)
        : DecAST(pos, VAR_DEC), var(var), typ(typ), init(init), escape(escape) {}

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

TypeDecAST::TypeDecAST(int pos, const shared_ptr<TypeTyListAST> &type) : DecAST(pos, TYPE_DEC), type(type) {}

const shared_ptr<TypeTyListAST> &TypeDecAST::getType() const {
    return type;
}


// NameTyAST----------------------------------

NameTyAST::NameTyAST(int pos, const string &name) : TyAST(pos, NAME_TYPE), name(name) {}

const string &NameTyAST::getName() const {
    return name;
}


// RecordTyAST--------------------------------

RecordTyAST::RecordTyAST(int pos, const shared_ptr<FieldListAST> &record) : TyAST(pos, RECORD_TYPE), record(record) {}

const shared_ptr<FieldListAST> &RecordTyAST::getRecord() const {
    return record;
}


// ArrayTyAST---------------------------------

ArrayTyAST::ArrayTyAST(int pos, const string &array) : TyAST(pos, ARRAY_TYPE), array(array) {}

const string &ArrayTyAST::getArray() const {
    return array;
}


// Function used in parser(bison)

shared_ptr<VarAST> MakeSimpleVarAST(int pos, string &sym) {
    return make_shared<SimpleVarAST>(pos, sym);
}

shared_ptr<VarAST> MakeFieldVarAST(int pos, shared_ptr<VarAST> var, string &sym) {
    return make_shared<FieldVarAST>(pos, var, sym);
}

shared_ptr<VarAST> MakeSubscriptVarAST(int pos, shared_ptr<VarAST> var, shared_ptr<ExpAST> exp) {
    return make_shared<SubscriptVarAST>(pos, var, exp);
}

shared_ptr<ExpAST> MakeVarExpAST(int pos, shared_ptr<VarAST> sym) {
    return make_shared<VarExpAST>(pos, sym);
}

shared_ptr<ExpAST> MakeNilExpAST(int pos) {
    return make_shared<NilExpAST>(pos);
}

shared_ptr<ExpAST> MakeIntExpAST(int pos, int i) {
    return make_shared<IntExpAST>(pos, i);
}

shared_ptr<ExpAST> MakeStringExpAST(int pos, string &s) {
    return make_shared<StringExpAST>(pos, s);
}

shared_ptr<ExpAST> MakeCallExpAST(int pos, string &func, shared_ptr<ExpListAST> args) {
    return make_shared<CallExpAST>(pos, func, args);
}

shared_ptr<ExpAST> MakeOpExpAST(int pos, Operator oper, shared_ptr<ExpAST> left, shared_ptr<ExpAST> right) {
    return make_shared<OpExpAST>(pos, oper, left, right);
}

shared_ptr<ExpAST> MakeRecordExpAST(int pos, string &typ, shared_ptr<EFieldListAST> fields) {
    return make_shared<RecordExpAST>(pos, typ, fields);
}

shared_ptr<ExpAST> MakeSeqExpAST(int pos, shared_ptr<ExpListAST> seq) {
    return make_shared<SeqExpAST>(pos, seq);
}

shared_ptr<ExpAST> MakeAssignExpAST(int pos, shared_ptr<VarAST> var, shared_ptr<ExpAST> exp) {
    return make_shared<AssignExpAST>(pos, var, exp);
}

shared_ptr<ExpAST> MakeIfExpAST(int pos, shared_ptr<ExpAST> test, shared_ptr<ExpAST> then, shared_ptr<ExpAST> elsee) {
    return make_shared<IfExpAST>(pos, test, then, elsee);
}

shared_ptr<ExpAST> MakeWhileExpAST(int pos, shared_ptr<ExpAST> test, shared_ptr<ExpAST> body) {
    return make_shared<WhileExpAST>(pos, test, body);
}

shared_ptr<ExpAST>
MakeForExpAST(int pos, string &var, shared_ptr<ExpAST> lo, shared_ptr<ExpAST> hi, shared_ptr<ExpAST> body) {
    return make_shared<ForExpAST>(pos, var, lo, hi, body, true);
}

shared_ptr<ExpAST> MakeBreakExpAST(int pos) {
    return make_shared<BreakExpAST>(pos);
}

shared_ptr<ExpAST> MakeLetExpAST(int pos, shared_ptr<DecListAST> decs, shared_ptr<ExpAST> body) {
    return make_shared<LetExpAST>(pos, decs, body);
}

shared_ptr<ExpAST> MakeArrayExpAST(int pos, string &typ, shared_ptr<ExpAST> size, shared_ptr<ExpAST> init) {
    return make_shared<ArrayExpAST>(pos, typ, size, init);
}

shared_ptr<DecAST> MakeFunctionDecAST(int pos, shared_ptr<FunDecListAST> function) {
    return make_shared<FunctionDecAST>(pos, function);
}

shared_ptr<DecAST> MakeVarDecAST(int pos, string &var, string &typ, shared_ptr<ExpAST> init) {
    return make_shared<VarDecAST>(pos, var, typ, init, true);
}

shared_ptr<DecAST> MakeTypeDecAST(int pos, shared_ptr<TypeTyListAST> type) {
    return make_shared<TypeDecAST>(pos, type);
}

shared_ptr<TyAST> MakeNameTyAST(int pos, string &name) {
    return make_shared<NameTyAST>(pos, name);
}

shared_ptr<TyAST> MakeRecordTyAST(int pos, shared_ptr<FieldListAST> record) {
    return make_shared<RecordTyAST>(pos, record);
}

shared_ptr<TyAST> MakeArrayTyAST(int pos, string &array) {
    return make_shared<ArrayTyAST>(pos, array);
}

shared_ptr<FieldAST> MakeFieldAST(int pos, string &name, string &typ) {
    return make_shared<FieldAST>(pos, name, typ, true);
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
MakeFunDecAST(int pos, string &name, string &result, shared_ptr<FieldListAST> params, shared_ptr<ExpAST> body) {
    return make_shared<FunDecAST>(pos, name, result, params, body);
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

shared_ptr<EFieldAST> MakeEfieldAST(string &name, shared_ptr<ExpAST> exp) {
    return make_shared<EFieldAST>(name, exp);
}

shared_ptr<EFieldListAST> MakeEfieldListAST(shared_ptr<EFieldAST> head, shared_ptr<EFieldListAST> tail) {
    if (tail == nullptr)
        tail = make_shared<EFieldListAST>();
    tail->push_front(head);
    return tail;
}


