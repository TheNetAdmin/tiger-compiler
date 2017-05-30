//===----------------------------------------------------------------------===//
// Abstract Syntax Tree
// Created by CHEGE on 2017/5/25.
//===----------------------------------------------------------------------===//

#ifndef MYCOMPILER_ABSYNTREE_H
#define MYCOMPILER_ABSYNTREE_H

#include <string>
#include <iterator>
#include <list>
#include <memory>
#include <iostream>
#include "location.hh"

using namespace std;

// some class predefine
class FieldAST;

class ExpAST;

class EFieldAST;

class DecAST;

class FunDecAST;

class NameTyAST;

class TypeTyAST;

// some type definition

typedef list <shared_ptr<FieldAST>> FieldListAST;
typedef list <shared_ptr<ExpAST>> ExpListAST;
typedef list <shared_ptr<EFieldAST>> EFieldListAST;
typedef list <shared_ptr<DecAST>> DecListAST;
typedef list <shared_ptr<FunDecAST>> FunDecListAST;
typedef list <shared_ptr<TypeTyAST>> TypeTyListAST;

// Base class
class AST {
    Tiger::location loc;
public:
    AST(Tiger::location & loc) {
        this->loc = loc;
    }

    void printLoc() const{
        cout << this->loc;
    }
};

// Base class definition

// VarAST - Base class for all varible nodes
enum VariableType {
    SIMPLE_VAR, FIELD_VAR, SUBSCRIPT_VAR
};

class VarAST : public AST {
    VariableType classType;

public:
    VarAST(Tiger::location loc, VariableType classType);

    virtual ~VarAST() {
    };

    VariableType getClassType() const;
};


// ExpAST - Base class for all expression nodes
enum ExpressionType {
    VAR_EXP, NIL_EXP, INT_EXP, STRING_EXP,
    CALL_EXP, OP_EXP, RECORD_EXP, SEQ_EXP, ASSING_EXP,
    IF_EXP, WHILE_EXP, FOR_EXP, BREAK_EXP, LET_EXP, ARRAY_EXP
};

class ExpAST: public AST {
    ExpressionType classType;

public:
    ExpAST(Tiger::location loc, ExpressionType classType);

    virtual ~ExpAST() {};


    ExpressionType getClassType();
};


// DecAST - Base class for all declaration nodes
enum DeclarationType {
    FUNCTION_DEC, VAR_DEC, TYPE_DEC
};

class DecAST: public AST {
    DeclarationType classType;

public:
    DecAST(Tiger::location loc, DeclarationType classType);

    virtual ~DecAST() {};


    DeclarationType getClassType();
};

// TyAST - Base class for all type nodes
enum TypeType {
    NAME_TYPE, RECORD_TYPE, ARRAY_TYPE
};

class TyAST: public AST {
    TypeType classType;

public:
    TyAST(Tiger::location loc, TypeType classType);

    virtual ~TyAST() {};


    TypeType getClassType();
};

//===----------------------------------------------------------------------===//

// Some class used in extend class

// FieldAST - Class used in RecordTyAST
class FieldAST: public AST {
    string name, typ;
    bool escape;

public:
    FieldAST(Tiger::location loc, const string &name, const string &typ, bool escape);


    const string &getName() const;

    const string &getTyp() const;

    bool isEscape() const;

    void setEscape(bool escape);
};

// EFieldAST - Class used in RecordExpAST
class EFieldAST {
    string name;
    shared_ptr<ExpAST> exp;

public:
    EFieldAST(const string &name, const shared_ptr<ExpAST> &exp);

    const string &getName() const;

    const shared_ptr<ExpAST> &getExp() const;

};

// FunDecAST - Class used in FunctionDecAST
class FunDecAST: public AST {
    string name, result;
    shared_ptr<FieldListAST> params;
    shared_ptr<ExpAST> body;

public:
    FunDecAST(Tiger::location loc, const string &name, const string &result, const shared_ptr<FieldListAST> &params,
              const shared_ptr<ExpAST> &body);

    const string &getName() const;

    const string &getResult() const;

    const shared_ptr<FieldListAST> &getParams() const;

    const shared_ptr<ExpAST> &getBody() const;
};


// TypeTyAST - Class used in / TYPE type-id = ty / to create a full type (TYPE type-id = ty) as a node
class TypeTyAST {
    string name;
    shared_ptr<TyAST> ty;

public:
    TypeTyAST(const string &name, const shared_ptr<TyAST> &ty);

    const string &getName() const;

    const shared_ptr<TyAST> &getTy() const;
};

//===----------------------------------------------------------------------===//

// Extend class definition

// Extend VarAST---------------------------
// SimpleVarAST - Extend class for all simple varible nodes
class SimpleVarAST : public VarAST {
    string simple;
public:
    SimpleVarAST(Tiger::location loc, const string &simple);

    const string &getSimple() const;
};

// FieldVarAST - Extend class for all field varible nodes
class FieldVarAST : public VarAST {
    shared_ptr<VarAST> var;
    string sym;
public:
    FieldVarAST(Tiger::location loc, const shared_ptr<VarAST> &var, const string &sym);

    const shared_ptr<VarAST> &getVar() const;

    const string &getSym() const;
};

// SubscriptVarAST - Extend class for all subscript varible nodes
class SubscriptVarAST : public VarAST {
    shared_ptr<VarAST> var;
    shared_ptr<ExpAST> exp;
public:
    SubscriptVarAST(Tiger::location loc, const shared_ptr<VarAST> &var, const shared_ptr<ExpAST> &exp);

    const shared_ptr<VarAST> &getVar() const;

    const shared_ptr<ExpAST> &getExp() const;
};


// Extend ExpAST-------------------------
// VarExpAST - Extend class for all varible expression nodes
class VarExpAST : public ExpAST {
    shared_ptr<VarAST> var;
public:
    VarExpAST(Tiger::location loc, const shared_ptr<VarAST> &var);

    const shared_ptr<VarAST> &getVar() const;
};

// NilExpAST - Extend class for all nil expression nodes
class NilExpAST : public ExpAST {
public:
    NilExpAST(Tiger::location loc);
};

// IntExpAST - Extend class for all int expression nodes
class IntExpAST : public ExpAST {
    int intt;
public:
    IntExpAST(Tiger::location loc, int intt);

    int getIntt() const;
};

// StringExpAST - Extend class for all string expression nodes
class StringExpAST : public ExpAST {
    string stringg;

public:
    StringExpAST(Tiger::location loc, const string &stringg);

    const string &getStringg() const;
};

// CallExpAST - Extend class for all call expression
class CallExpAST : public ExpAST {
    string func;
    shared_ptr<ExpListAST> args;

public:
    CallExpAST(Tiger::location loc, const string &func, const shared_ptr<ExpListAST> &args);

    const string &getFunc() const;

    const shared_ptr<ExpListAST> &getArgs() const;
};

// OpExpAST - Extend class for all operation expression
enum Operator {
    PLUSOP, MINUSOP, TIMESOP, DIVIDEOP,
    EQOP, NEQOP, LTOP, LEOP, GTOP, GEOP
};

class OpExpAST : public ExpAST {
    Operator op;
    shared_ptr<ExpAST> left;
    shared_ptr<ExpAST> right;
public:
    OpExpAST(Tiger::location loc, Operator op, const shared_ptr<ExpAST> &left,
             const shared_ptr<ExpAST> &right);

    Operator getOp() const;

    const shared_ptr<ExpAST> &getLeft() const;

    const shared_ptr<ExpAST> &getRight() const;
};

// RecordExpAST - Extend class for all record expression
class RecordExpAST : public ExpAST {
    string typ;
    shared_ptr<EFieldListAST> fields;

public:
    RecordExpAST(Tiger::location loc, const string &typ, const shared_ptr<EFieldListAST> &fields);

    const string &getTyp() const;

    const shared_ptr<EFieldListAST> &getFields() const;
};

// SeqExpAST - Extend class for all sequence expression
class SeqExpAST : public ExpAST {
    shared_ptr<ExpListAST> seq;
public:
    SeqExpAST(Tiger::location loc, const shared_ptr<ExpListAST> &seq);

    const shared_ptr<ExpListAST> &getSeq() const;
};

// AssignExpAST - Extend class for all assign expression
class AssignExpAST : public ExpAST {
    shared_ptr<VarAST> var;
    shared_ptr<ExpAST> exp;
public:
    AssignExpAST(Tiger::location loc, const shared_ptr<VarAST> &var, const shared_ptr<ExpAST> &exp);

    const shared_ptr<VarAST> &getVar() const;

    const shared_ptr<ExpAST> &getExp() const;
};

// IfExpAST - Extend class for all if expression
class IfExpAST : public ExpAST {
    shared_ptr<ExpAST> test, then, elsee;
public:
    IfExpAST(Tiger::location loc, const shared_ptr<ExpAST> &test, const shared_ptr<ExpAST> &then,
             const shared_ptr<ExpAST> &elsee);

    const shared_ptr<ExpAST> &getTest() const;

    const shared_ptr<ExpAST> &getThen() const;

    const shared_ptr<ExpAST> &getElsee() const;
};

// WhileExpAST - Extend class for all while expression
class WhileExpAST : public ExpAST {
    shared_ptr<ExpAST> test, body;
public:
    WhileExpAST(Tiger::location loc, const shared_ptr<ExpAST> &test, const shared_ptr<ExpAST> &body);

    const shared_ptr<ExpAST> &getTest() const;

    const shared_ptr<ExpAST> &getBody() const;
};

// BreakExpAST - Extend class for all break expression
class BreakExpAST : public ExpAST {
public:
    BreakExpAST(Tiger::location loc);
};

// ForExpAST - Extend class for all for expression
class ForExpAST : public ExpAST {
    string var;
    shared_ptr<ExpAST> lo, hi, body;
    bool escape;
public:
    ForExpAST(Tiger::location loc, const string &var, const shared_ptr<ExpAST> &lo,
              const shared_ptr<ExpAST> &hi, const shared_ptr<ExpAST> &body, bool escape);

    const string &getVar() const;

    const shared_ptr<ExpAST> &getLo() const;

    const shared_ptr<ExpAST> &getHi() const;

    const shared_ptr<ExpAST> &getBody() const;

    bool isEscape() const;

    void setEscape(bool escape);
};

// LetExpAST - Extend class for all let expression
class LetExpAST : public ExpAST {
    shared_ptr<DecListAST> decs;
    shared_ptr<ExpAST> body;
public:
    LetExpAST(Tiger::location loc, const shared_ptr<DecListAST> &decs, const shared_ptr<ExpAST> &body);

    const shared_ptr<DecListAST> &getDecs() const;

    const shared_ptr<ExpAST> &getBody() const;
};

// ArrayExpAST - Extend class for all array expression
class ArrayExpAST : public ExpAST {
    string typ;
    shared_ptr<ExpAST> size, init;
public:
    ArrayExpAST(Tiger::location loc, const string &typ, const shared_ptr<ExpAST> &size,
                const shared_ptr<ExpAST> &init);

    const string &getTyp() const;

    const shared_ptr<ExpAST> &getSize() const;

    const shared_ptr<ExpAST> &getInit() const;
};


// Extend DecAST---------------------------------
// FunctionDecAST - Extend class for all function declaration
class FunctionDecAST : public DecAST {
    shared_ptr<FunDecListAST> function;
public:
    FunctionDecAST(Tiger::location loc, const shared_ptr<FunDecListAST> &function);

    const shared_ptr<FunDecListAST> &getFunction() const;
};

// VarDecAST - Extend class for all varible declaration
class VarDecAST : public DecAST {
    string var, typ;
    shared_ptr<ExpAST> init;
    bool escape;
public:
    VarDecAST(Tiger::location loc, const string &var, const string &typ, const shared_ptr<ExpAST> &init,
              bool escape);

    const string &getVar() const;

    const string &getTyp() const;

    const shared_ptr<ExpAST> &getInit() const;

    bool isEscape() const;

    void setEscape(bool escape);
};

// TypeDecAST - Extend class for all type declaration
class TypeDecAST : public DecAST {
    shared_ptr<TypeTyListAST> type;
public:
    TypeDecAST(Tiger::location loc, const shared_ptr<TypeTyListAST> &type);

    const shared_ptr<TypeTyListAST> &getType() const;
};


// Extend TyAST---------------------------------
// NameTyAST - Extend class for all name type
class NameTyAST : public TyAST {
    string name;
public:
    NameTyAST(Tiger::location loc, const string &name);

    const string &getName() const;
};

// RecordTyAST - Extend class for all record type
class RecordTyAST : public TyAST {
    shared_ptr<FieldListAST> record;
public:
    RecordTyAST(Tiger::location loc, const shared_ptr<FieldListAST> &record);

    const shared_ptr<FieldListAST> &getRecord() const;
};

// ArrayTyAST - Extend class for all array type
class ArrayTyAST : public TyAST {
    string array;
public:
    ArrayTyAST(Tiger::location loc, const string &array);

    const string &getArray() const;
};


//===----------------------------------------------------------------------===//
// Function used in parser(bison)
// VarAST::
shared_ptr<VarAST> MakeSimpleVarAST(Tiger::location loc, string &sym);

shared_ptr<VarAST> MakeFieldVarAST(Tiger::location loc, shared_ptr<VarAST> var, string &sym);

shared_ptr<VarAST> MakeSubscriptVarAST(Tiger::location loc, shared_ptr<VarAST> var, shared_ptr<ExpAST> exp);


// ExpAST::
shared_ptr<ExpAST> MakeVarExpAST(Tiger::location loc, shared_ptr<VarAST> sym);

shared_ptr<ExpAST> MakeNilExpAST(Tiger::location loc);

shared_ptr<ExpAST> MakeIntExpAST(Tiger::location loc, int i);

shared_ptr<ExpAST> MakeStringExpAST(Tiger::location loc, string &s);

shared_ptr<ExpAST> MakeCallExpAST(Tiger::location loc, string &func, shared_ptr<ExpListAST> args);

shared_ptr<ExpAST> MakeOpExpAST(Tiger::location loc, Operator oper, shared_ptr<ExpAST> left, shared_ptr<ExpAST> right);

shared_ptr<ExpAST> MakeRecordExpAST(Tiger::location loc, string &typ, shared_ptr<EFieldListAST> fields);

shared_ptr<ExpAST> MakeSeqExpAST(Tiger::location loc, shared_ptr<ExpListAST> seq);

shared_ptr<ExpAST> MakeAssignExpAST(Tiger::location loc, shared_ptr<VarAST> var, shared_ptr<ExpAST> exp);

shared_ptr<ExpAST>
MakeIfExpAST(Tiger::location loc, shared_ptr<ExpAST> test, shared_ptr<ExpAST> then, shared_ptr<ExpAST> elsee);

shared_ptr<ExpAST> MakeWhileExpAST(Tiger::location loc, shared_ptr<ExpAST> test, shared_ptr<ExpAST> body);

shared_ptr<ExpAST>
MakeForExpAST(Tiger::location loc, string &var, shared_ptr<ExpAST> lo, shared_ptr<ExpAST> hi, shared_ptr<ExpAST> body);

shared_ptr<ExpAST> MakeBreakExpAST(Tiger::location loc);

shared_ptr<ExpAST> MakeLetExpAST(Tiger::location loc, shared_ptr<DecListAST> decs, shared_ptr<ExpAST> body);

shared_ptr<ExpAST> MakeArrayExpAST(Tiger::location loc, string &typ, shared_ptr<ExpAST> size, shared_ptr<ExpAST> init);


// DecAST::
shared_ptr<DecAST> MakeFunctionDecAST(Tiger::location loc, shared_ptr<FunDecListAST> function);

shared_ptr<DecAST> MakeVarDecAST(Tiger::location loc, string &var, string &typ, shared_ptr<ExpAST> init);

shared_ptr<DecAST> MakeTypeDecAST(Tiger::location loc, shared_ptr<TypeTyListAST> type);


// TyAST::
shared_ptr<TyAST> MakeNameTyAST(Tiger::location loc, string &name);

shared_ptr<TyAST> MakeRecordTyAST(Tiger::location loc, shared_ptr<FieldListAST> record);

shared_ptr<TyAST> MakeArrayTyAST(Tiger::location loc, string &array);


// Make some struct used above
shared_ptr<FieldAST> MakeFieldAST(Tiger::location loc, string &name, string &typ);

shared_ptr<FieldListAST> MakeFieldListAST(shared_ptr<FieldAST> head, shared_ptr<FieldListAST> tail);

shared_ptr<ExpListAST> MakeExpListAST(shared_ptr<ExpAST> head, shared_ptr<ExpListAST> tail);

shared_ptr<FunDecAST>
MakeFunDecAST(Tiger::location loc, string &name, string &result, shared_ptr<FieldListAST> params,
              shared_ptr<ExpAST> body);

shared_ptr<FunDecListAST> MakeFunDecListAST(shared_ptr<FunDecAST> head, shared_ptr<FunDecListAST> tail);

shared_ptr<DecListAST> MakeDecListAST(shared_ptr<DecAST> head, shared_ptr<DecListAST> tail);

shared_ptr<TypeTyAST> MakeTypeTyAST(string &name, shared_ptr<TyAST> ty);

shared_ptr<TypeTyListAST> MakeTypeTyListAST(shared_ptr<TypeTyAST> head, shared_ptr<TypeTyListAST> tail);

shared_ptr<EFieldAST> MakeEFieldAST(string &name, shared_ptr<ExpAST> exp);

shared_ptr<EFieldListAST> MakeEFieldListAST(shared_ptr<EFieldAST> head, shared_ptr<EFieldListAST> tail);


#endif //MYCOMPILER_ABSYNTREE_H
