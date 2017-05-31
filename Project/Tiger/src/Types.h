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

        Type() {}

        virtual ~Type() {}
    };

    class Nil : public Type {
        Nil() {}
    };

    class Int : public Type {
        Int() {}
    };

    class String : public Type {
        String() {}
    };

    class Void : public Type {
        Void() {}
    };

    class Field { // similar to Ty_field
    public:
        std::string name;
        std::shared_ptr<Type> type;

        Field(const std::string &name, const std::shared_ptr<Type> &type)
                : name(name), type(type) {}
    };

    class Record : public Type {
    public:
        // similar to Ty_fieldList record
        std::list<std::shared_ptr<Field>> recordList;

        //TODO: need a simpler constructor to simplify init of recordList
        //      consider using initializer_list
        Record(std::initializer_list<std::shared_ptr<Field>> fields) {
            for (auto field : fields) {
                recordList.push_back(field);
            }
        }
    };

    class Array : public Type {
    public:
        std::shared_ptr<Type> array;

        Array(const std::shared_ptr<Type> &array)
                : array(array) {}
    };

    class Name : public Type {
    public:
        std::string name;
        std::shared_ptr<Type> type;

        Name(const std::string &name, const std::shared_ptr<Type> &type)
                : name(name), type(type) {}
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

    bool isNil(const std::shared_ptr<Type> &t) const {
        return typeid(*t) == typeid(Nil);
    }

    bool isInt(const std::shared_ptr<Type> &t) const {
        return typeid(*t) == typeid(Int);
    }

    bool isString(const std::shared_ptr<Type> &t) const {
        return typeid(*t) == typeid(String);
    }

    bool isVoid(const std::shared_ptr<Type> &t) const {
        return typeid(*t) == typeid(Void);
    }

    bool isRecord(const std::shared_ptr<Type> &t) const {
        return typeid(*t) == typeid(Record);
    }

    bool isArray(const std::shared_ptr<Type> &t) const {
        return typeid(*t) == typeid(Array);
    }

    bool isName(const std::shared_ptr<Type> &t) const {
        return typeid(*t) == typeid(Name);
    }
};

#endif //SRC_TYPES_H
