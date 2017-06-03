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

namespace AST
{
// some class predefine
    class Field;

    class Exp;

    class EField;

    class Dec;

    class FunDec;

    class NameTy;

    class TypeTy;

// some type definition

    using FieldList = list<shared_ptr<Field>>;
    using ExpList = list<shared_ptr<Exp>>;
    using EFieldList = list<shared_ptr<EField>>;
    using DecList = list<shared_ptr<Dec>>;
    using FunDecList = list<shared_ptr<FunDec>>;
    using TypeTyList = list<shared_ptr<TypeTy>>;

// Base class
    class ASTNode
    {
        Tiger::location loc;
    public:
        ASTNode(Tiger::location &loc)
        {
            this->loc = loc;
        }

        const Tiger::location &getLoc() const
        {
            return loc;
        }
    };

// Base class definition

// Var - Base class for all varible nodes
    enum VariableType
    {
        SIMPLE_VAR, FIELD_VAR, SUBSCRIPT_VAR
    };

    class Var : public ASTNode
    {
        VariableType classType;

    public:
        Var(Tiger::location loc, VariableType classType);

        virtual ~Var()
        {
        };

        VariableType getClassType() const;
    };


// Exp - Base class for all expression nodes
    enum ExpressionType
    {
        VAR_EXP, NIL_EXP, INT_EXP, STRING_EXP,
        CALL_EXP, OP_EXP, RECORD_EXP, SEQ_EXP, ASSIGN_EXP,
        IF_EXP, WHILE_EXP, FOR_EXP, BREAK_EXP, LET_EXP, ARRAY_EXP
    };

    class Exp : public ASTNode
    {
        ExpressionType classType;

    public:
        Exp(Tiger::location loc, ExpressionType classType);

        virtual ~Exp()
        {};


        ExpressionType getClassType();
    };


// Dec - Base class for all declaration nodes
    enum DeclarationType
    {
        FUNCTION_DEC, VAR_DEC, TYPE_DEC
    };

    class Dec : public ASTNode
    {
        DeclarationType classType;

    public:
        Dec(Tiger::location loc, DeclarationType classType);

        virtual ~Dec()
        {};


        DeclarationType getClassType();
    };

// Ty - Base class for all type nodes
    enum TypeType
    {
        NAME_TYPE, RECORD_TYPE, ARRAY_TYPE
    };

    class Ty : public ASTNode
    {
        TypeType classType;

    public:
        Ty(Tiger::location loc, TypeType classType);

        virtual ~Ty()
        {};


        TypeType getClassType();
    };

//===----------------------------------------------------------------------===//

// Some class used in extend class

// Field - Class used in RecordTy
    class Field : public ASTNode
    {
        string name, typ;
        bool escape;

    public:
        Field(Tiger::location loc, const string &name, const string &typ, bool escape);


        const string &getName() const;

        const string &getTyp() const;

        bool isEscape() const;

        void setEscape(bool escape);
    };

// EField - Class used in RecordExp
    class EField
    {
        string name;
        shared_ptr<Exp> exp;

    public:
        EField(const string &name, const shared_ptr<Exp> &exp);

        const string &getName() const;

        const shared_ptr<Exp> &getExp() const;

    };

// FunDec - Class used in FunctionDec
    class FunDec : public ASTNode
    {
        string name, result;
        shared_ptr<FieldList> params;
        shared_ptr<Exp> body;

    public:
        FunDec(Tiger::location loc, const string &name, const string &result, const shared_ptr<FieldList> &params,
               const shared_ptr<Exp> &body);

        const string &getName() const;

        const string &getResult() const;

        const shared_ptr<FieldList> &getParams() const;

        const shared_ptr<Exp> &getBody() const;
    };


// TypeTy - Class used in / TYPE type-id = ty / to create a full type (TYPE type-id = ty) as a node
    class TypeTy
    {
        string name;
        shared_ptr<Ty> ty;

    public:
        TypeTy(const string &name, const shared_ptr<Ty> &ty);

        const string &getName() const;

        const shared_ptr<Ty> &getTy() const;
    };

//===----------------------------------------------------------------------===//

// Extend class definition

// Extend Var---------------------------
// SimpleVar - Extend class for all simple varible nodes
    class SimpleVar : public Var
    {
        string simple;
    public:
        SimpleVar(Tiger::location loc, const string &simple);

        const string &getSimple() const;
    };

// FieldVar - Extend class for all field varible nodes
    class FieldVar : public Var
    {
        shared_ptr<Var> var;
        string sym;
    public:
        FieldVar(Tiger::location loc, const shared_ptr<Var> &var, const string &sym);

        const shared_ptr<Var> getVar() const;

        const string &getSym() const;
    };

// SubscriptVar - Extend class for all subscript varible nodes
    class SubscriptVar : public Var
    {
        shared_ptr<Var> var;
        shared_ptr<Exp> exp;
    public:
        SubscriptVar(Tiger::location loc, const shared_ptr<Var> &var, const shared_ptr<Exp> &exp);

        const shared_ptr<Var> &getVar() const;

        const shared_ptr<Exp> &getExp() const;
    };


// Extend Exp-------------------------
// VarExp - Extend class for all varible expression nodes
    class VarExp : public Exp
    {
        shared_ptr<Var> var;
    public:
        VarExp(Tiger::location loc, const shared_ptr<Var> &var);

        const shared_ptr<Var> &getVar() const;
    };

// NilExp - Extend class for all nil expression nodes
    class NilExp : public Exp
    {
    public:
        NilExp(Tiger::location loc);
    };

// IntExp - Extend class for all int expression nodes
    class IntExp : public Exp
    {
        int intt;
    public:
        IntExp(Tiger::location loc, int intt);

        int getInt() const;
    };

// StringExp - Extend class for all string expression nodes
    class StringExp : public Exp
    {
        string str;

    public:
        StringExp(Tiger::location loc, const string &stringg);

        const string &getString() const;
    };

// CallExp - Extend class for all call expression
    class CallExp : public Exp
    {
        string func;
        shared_ptr<ExpList> args;

    public:
        CallExp(Tiger::location loc, const string &func, const shared_ptr<ExpList> &args);

        const string &getFunc() const;

        const shared_ptr<ExpList> &getArgs() const;
    };

// OpExp - Extend class for all operation expression
    enum Operator
    {
        PLUS, MINUS, TIMES, DIVIDE,
        EQ, NEQ, LT, LE, GT, GE
    };

    class OpExp : public Exp
    {
        Operator op;
        shared_ptr<Exp> left;
        shared_ptr<Exp> right;
    public:
        OpExp(Tiger::location loc, Operator op, const shared_ptr<Exp> &left,
              const shared_ptr<Exp> &right);

        Operator getOp() const;

        const shared_ptr<Exp> &getLeft() const;

        const shared_ptr<Exp> &getRight() const;
    };

// RecordExp - Extend class for all record expression
    class RecordExp : public Exp
    {
        string typ;
        shared_ptr<EFieldList> fields;

    public:
        RecordExp(Tiger::location loc, const string &typ, const shared_ptr<EFieldList> &fields);

        const string &getTyp() const;

        const shared_ptr<EFieldList> &getFields() const;
    };

// SeqExp - Extend class for all sequence expression
    class SeqExp : public Exp
    {
        shared_ptr<ExpList> seq;
    public:
        SeqExp(Tiger::location loc, const shared_ptr<ExpList> &seq);

        const shared_ptr<ExpList> &getSeq() const;
    };

// AssignExp - Extend class for all assign expression
    class AssignExp : public Exp
    {
        shared_ptr<Var> var;
        shared_ptr<Exp> exp;
    public:
        AssignExp(Tiger::location loc, const shared_ptr<Var> &var, const shared_ptr<Exp> &exp);

        const shared_ptr<Var> &getVar() const;

        const shared_ptr<Exp> &getExp() const;
    };

// IfExp - Extend class for all if expression
    class IfExp : public Exp
    {
        shared_ptr<Exp> test, then, elsee;
    public:
        IfExp(Tiger::location loc, const shared_ptr<Exp> &test, const shared_ptr<Exp> &then,
              const shared_ptr<Exp> &elsee);

        const shared_ptr<Exp> &getTest() const;

        const shared_ptr<Exp> &getThen() const;

        const shared_ptr<Exp> &getElsee() const;
    };

// WhileExp - Extend class for all while expression
    class WhileExp : public Exp
    {
        shared_ptr<Exp> test, body;
    public:
        WhileExp(Tiger::location loc, const shared_ptr<Exp> &test, const shared_ptr<Exp> &body);

        const shared_ptr<Exp> &getTest() const;

        const shared_ptr<Exp> &getBody() const;
    };

// BreakExp - Extend class for all break expression
    class BreakExp : public Exp
    {
    public:
        BreakExp(Tiger::location loc);
    };

// ForExp - Extend class for all for expression
    class ForExp : public Exp
    {
        string var;
        shared_ptr<Exp> lo, hi, body;
        bool escape;
    public:
        ForExp(Tiger::location loc, const string &var, const shared_ptr<Exp> &lo,
               const shared_ptr<Exp> &hi, const shared_ptr<Exp> &body, bool escape);

        const string &getVar() const;

        const shared_ptr<Exp> &getLo() const;

        const shared_ptr<Exp> &getHi() const;

        const shared_ptr<Exp> &getBody() const;

        bool isEscape() const;

        void setEscape(bool escape);
    };

// LetExp - Extend class for all let expression
    class LetExp : public Exp
    {
        shared_ptr<DecList> decs;
        shared_ptr<Exp> body;
    public:
        LetExp(Tiger::location loc, const shared_ptr<DecList> &decs, const shared_ptr<Exp> &body);

        const shared_ptr<DecList> &getDecs() const;

        const shared_ptr<Exp> &getBody() const;
    };

// ArrayExp - Extend class for all array expression
    class ArrayExp : public Exp
    {
        string typ;
        shared_ptr<Exp> size, init;
    public:
        ArrayExp(Tiger::location loc, const string &typ, const shared_ptr<Exp> &size,
                 const shared_ptr<Exp> &init);

        const string &getTyp() const;

        const shared_ptr<Exp> &getSize() const;

        const shared_ptr<Exp> &getInit() const;
    };


// Extend Dec---------------------------------
// FunctionDec - Extend class for all function declaration
    class FunctionDec : public Dec
    {
        shared_ptr<FunDecList> function;
    public:
        FunctionDec(Tiger::location loc, const shared_ptr<FunDecList> &function);

        const shared_ptr<FunDecList> &getFunction() const;
    };

// VarDec - Extend class for all varible declaration
    class VarDec : public Dec
    {
        string var, typ;
        shared_ptr<Exp> init;
        bool escape;
    public:
        VarDec(Tiger::location loc, const string &var, const string &typ, const shared_ptr<Exp> &init,
               bool escape);

        const string &getVar() const;

        const string &getTyp() const;

        const shared_ptr<Exp> &getInit() const;

        bool isEscape() const;

        void setEscape(bool escape);
    };

// TypeDec - Extend class for all type declaration
    class TypeDec : public Dec
    {
        shared_ptr<TypeTyList> type;
    public:
        TypeDec(Tiger::location loc, const shared_ptr<TypeTyList> &type);

        const shared_ptr<TypeTyList> &getType() const;
    };


// Extend Ty---------------------------------
// NameTy - Extend class for all name type
    class NameTy : public Ty
    {
        string name;
    public:
        NameTy(Tiger::location loc, const string &name);

        const string &getName() const;
    };

// RecordTy - Extend class for all record type
    class RecordTy : public Ty
    {
        shared_ptr<FieldList> record;
    public:
        RecordTy(Tiger::location loc, const shared_ptr<FieldList> &record);

        const shared_ptr<FieldList> &getRecord() const;
    };

// ArrayTy - Extend class for all array type
    class ArrayTy : public Ty
    {
        string array;
    public:
        ArrayTy(Tiger::location loc, const string &array);

        const string &getArray() const;
    };


//===----------------------------------------------------------------------===//
// Function used in parser(bison)
// Var::
    shared_ptr<Var> MakeSimpleVar(Tiger::location loc, string &sym);

    shared_ptr<Var> MakeFieldVar(Tiger::location loc, shared_ptr<Var> var, string &sym);

    shared_ptr<Var> MakeSubscriptVar(Tiger::location loc, shared_ptr<Var> var, shared_ptr<Exp> exp);


// Exp::
    shared_ptr<Exp> MakeVarExp(Tiger::location loc, shared_ptr<Var> sym);

    shared_ptr<Exp> MakeNilExp(Tiger::location loc);

    shared_ptr<Exp> MakeIntExp(Tiger::location loc, int i);

    shared_ptr<Exp> MakeStringExp(Tiger::location loc, string &s);

    shared_ptr<Exp> MakeCallExp(Tiger::location loc, string &func, shared_ptr<ExpList> args);

    shared_ptr<Exp> MakeOpExp(Tiger::location loc, Operator oper, shared_ptr<Exp> left, shared_ptr<Exp> right);

    shared_ptr<Exp> MakeRecordExp(Tiger::location loc, string &typ, shared_ptr<EFieldList> fields);

    shared_ptr<Exp> MakeSeqExp(Tiger::location loc, shared_ptr<ExpList> seq);

    shared_ptr<Exp> MakeAssignExp(Tiger::location loc, shared_ptr<Var> var, shared_ptr<Exp> exp);

    shared_ptr<Exp> MakeIfExp(Tiger::location loc, shared_ptr<Exp> test, shared_ptr<Exp> then, shared_ptr<Exp> elsee);

    shared_ptr<Exp> MakeWhileExp(Tiger::location loc, shared_ptr<Exp> test, shared_ptr<Exp> body);

    shared_ptr<Exp>
    MakeForExp(Tiger::location loc, string &var, shared_ptr<Exp> lo, shared_ptr<Exp> hi, shared_ptr<Exp> body);

    shared_ptr<Exp> MakeBreakExp(Tiger::location loc);

    shared_ptr<Exp> MakeLetExp(Tiger::location loc, shared_ptr<DecList> decs, shared_ptr<Exp> body);

    shared_ptr<Exp> MakeArrayExp(Tiger::location loc, string &typ, shared_ptr<Exp> size, shared_ptr<Exp> init);


// Dec::
    shared_ptr<Dec> MakeFunctionDec(Tiger::location loc, shared_ptr<FunDecList> function);

    shared_ptr<Dec> MakeVarDec(Tiger::location loc, const string &var, const string &typ, shared_ptr<Exp> init);

    shared_ptr<Dec> MakeTypeDec(Tiger::location loc, shared_ptr<TypeTyList> type);


// Ty::
    shared_ptr<Ty> MakeNameTy(Tiger::location loc, string &name);

    shared_ptr<Ty> MakeRecordTy(Tiger::location loc, shared_ptr<FieldList> record);

    shared_ptr<Ty> MakeArrayTy(Tiger::location loc, string &array);


// Make some struct used above
    shared_ptr<Field> MakeField(Tiger::location loc, string &name, string &typ);

    shared_ptr<FieldList> MakeFieldList(shared_ptr<Field> head, shared_ptr<FieldList> tail);

    shared_ptr<ExpList> MakeExpList(shared_ptr<Exp> head, shared_ptr<ExpList> tail);

    shared_ptr<FunDec>
    MakeFunDec(Tiger::location loc, string &name, string &result, shared_ptr<FieldList> params,
               shared_ptr<Exp> body);

    shared_ptr<FunDecList> MakeFunDecList(shared_ptr<FunDec> head, shared_ptr<FunDecList> tail);

    shared_ptr<DecList> MakeDecList(shared_ptr<Dec> head, shared_ptr<DecList> tail);

    shared_ptr<TypeTy> MakeTypeTy(string &name, shared_ptr<Ty> ty);

    shared_ptr<TypeTyList> MakeTypeTyList(shared_ptr<TypeTy> head, shared_ptr<TypeTyList> tail);

    shared_ptr<EField> MakeEField(string &name, shared_ptr<Exp> exp);

    shared_ptr<EFieldList> MakeEFieldList(shared_ptr<EField> head, shared_ptr<EFieldList> tail);
}

#endif //MYCOMPILER_ABSYNTREE_H
