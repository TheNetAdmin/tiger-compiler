//
// Created by PrinceXuan on 2017/5/30.
//

#ifndef SRC_TYPES_H
#define SRC_TYPES_H

#include <iostream>
#include <list>
#include <memory>

namespace Type
{

    class EntryNotFound : public std::runtime_error
    {
    public:
        explicit EntryNotFound(const std::string &msg);
    };

    class Type
    {
    public:
        Type();

        virtual ~Type();
    };

    class Nil : public Type
    {
    public:
        Nil();
    };

    class Int : public Type
    {
    public:
        Int();
    };

    class String : public Type
    {
    public:
        String();
    };

    class Void : public Type
    {
    public:
        Void();
    };

    class Field
    {  // similar to Ty_field
    public:
        std::string name;
        std::shared_ptr<Type> type;

        Field(const std::string &name, const std::shared_ptr<Type> &type);
    };

    using FieldList = std::list<std::shared_ptr<Field>>;

    class Record : public Type
    {
    public:
        // similar to Ty_fieldList record
        std::shared_ptr<FieldList> fields;

        Record();

        Record(std::initializer_list<std::shared_ptr<Field>> fields);

        std::shared_ptr<Field> find(std::string name, int &offset);

        const std::shared_ptr<FieldList> getFields() const;

        void addField(const std::string &name, const std::shared_ptr<Type> type);
    };

    class Array : public Type
    {
    public:
        std::shared_ptr<Type> array;

        Array();

        Array(const std::shared_ptr<Type> &array);

        void setArray(const std::shared_ptr<Type> &array);
    };

    class Name : public Type
    {
    public:
        std::string name;
        std::shared_ptr<Type> type;

        Name();

        Name(const std::string &name, const std::shared_ptr<Type> &type);
    };

// Default types

    namespace
    {
        // Make these static to save space
        std::shared_ptr<Nil> NIL = std::make_shared<Nil>();
        std::shared_ptr<Int> INT = std::make_shared<Int>();
        std::shared_ptr<String> STRING = std::make_shared<String>();
        std::shared_ptr<Void> VOID = std::make_shared<Void>();
        std::shared_ptr<Record> RECORD = std::make_shared<Record>();
        std::shared_ptr<Array> ARRAY = std::make_shared<Array>();
    }

    bool isNil(const std::shared_ptr<Type> &t);

    bool isInt(const std::shared_ptr<Type> &t);

    bool isString(const std::shared_ptr<Type> &t);

    bool isVoid(const std::shared_ptr<Type> &t);

    bool isRecord(const std::shared_ptr<Type> &t);

    bool isArray(const std::shared_ptr<Type> &t);

    bool isName(const std::shared_ptr<Type> &t);

    bool match(const std::shared_ptr<Type> &t1, const std::shared_ptr<Type> &t2);

    // Get type name
    const std::string getName(const std::shared_ptr<Type> &t);
};

#endif  // SRC_TYPES_H
