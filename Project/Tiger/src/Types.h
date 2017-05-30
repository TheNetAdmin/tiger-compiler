//
// Created by PrinceXuan on 2017/5/30.
//

#ifndef SRC_TYPES_H
#define SRC_TYPES_H

#include <iostream>
#include <memory>
#include <list>
#include <list>

namespace Type {

    class Type {
    public:
        enum type {
            BASE = 0,
            NIL,
            INT,
            STRING,
            VOID,
            RECORD,
            ARRAY,
            NAME
        } type;

        Type(type type)
                : type(type) {}

        Type()
                : type(BASE) {}

        virtual ~Type() {}
    };

    class Nil : public Type {
        Nil()
                : Type(NIL) {}
    };

    class Int : public Type {
        Int()
                : Type(INT) {}
    };

    class String : public Type {
        String()
                : Type(STRING) {}
    };

    class Void : public Type {
        Void()
                : Type(VOID) {}
    };

    class Field { // similar to Ty_field
    public:
        std::string name;
        std::shared_ptr<Type> type;

        Field(const std::string &name, const std::shared_ptr<Type> &type)
                : name(name), type(type) {}
    };

    class FieldList {
    public:
        std::list<std::shared_ptr<Field>> fieldList;
        FieldList(){}
        FieldList(std::initializer_list<std::shared_ptr<Field>> fields){
            for ( auto field : fields){
                enter(field);
            }
        }
        FieldList(std::shared_ptr<Field> field){
            enter(field);
        }
        void enter(std::shared_ptr<Field> entry){
            this->fieldList.push_back(entry);
        }
    };

    class Record : public Type {
    public:
        // similar to Ty_fieldList record
        FieldList recordList;

        //TODO: need a simpler constructor to simplify init of recordList
        //      consider using initializer_list
        Record(const FieldList &recordList)
                : Type(RECORD), recordList(recordList) {}
    };

    class Array : public Type {
    public:
        std::shared_ptr<Type> array;

        Array(const std::shared_ptr<Type> &array)
                : Type(ARRAY), array(array) {}
    };

    class Name : public Type {
    public:
        std::string name;
        std::shared_ptr<Type> type;

        Name(const std::string &name, const std::shared_ptr<Type> &type)
                : Type(NAME), name(name), type(type) {}
    };

    namespace { // Make these static to save space
        std::shared_ptr<Nil> NIL;
        std::shared_ptr<Int> INT;
        std::shared_ptr<String> STRING;
        std::shared_ptr<Void> VOID;
    }

    std::shared_ptr<Nil> makeNil() {
        return NIL;
    }

    std::shared_ptr<Int> makeInt() {
        return INT;
    }

    std::shared_ptr<String> makeString() {
        return STRING;
    }

    std::shared_ptr<Void> makeVoid() {
        return VOID;
    }

    class TypeList {
    public:
        std::list<std::shared_ptr<Type>> typeList;

        TypeList() {}

        TypeList(std::initializer_list<std::shared_ptr<Type>> types) {
            for (auto type : types) {
                typeList.push_back(type);
            }
        }

        TypeList(std::shared_ptr<Type> type) {
            typeList.push_back(type);
        }
    };

};

#endif //SRC_TYPES_H
