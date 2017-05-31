//
// Created by PrinceXuan on 2017/5/30.
//

#ifndef SRC_TYPES_H
#define SRC_TYPES_H

#include <iostream>
#include <memory>
#include <list>
#include <list>

namespace Type
{

    class Field
    { // similar to Ty_field
    public:
        std::string name;
        std::shared_ptr<Type> type;

        Field(const std::string &name, const std::shared_ptr<Type> &type)
                : name(name), type(type)
        {}
    };

    class EntryNotFound : public std::runtime_error
    {
    public:
        explicit EntryNotFound(const std::string &msg)
                : std::runtime_error(msg)
        {}
    };

    class Type
    {
    public:

        Type()
        {}

        virtual ~Type()
        {}
    };

    class Nil : public Type
    {
    public:

        Nil()
        {}
    };

    class Int : public Type
    {
    public:

        Int()
        {}
    };

    class String : public Type
    {
    public:

        String()
        {}
    };

    class Void : public Type
    {
    public:

        Void()
        {}
    };

    class Record : public Type
    {
    public:
        // similar to Ty_fieldList record
        using FieldList = std::list<std::shared_ptr<Field>>;
        std::shared_ptr<FieldList> fields;

        Record()
        {}

        Record(std::initializer_list<std::shared_ptr<Field>> fields)
        {
            this->fields = std::make_shared<FieldList>(fields);
        }

        std::shared_ptr<Field> find(std::string name)
        {
            for (auto iter = fields->begin(); iter != fields->end(); iter++)
            {
                if ((*iter)->name == name)
                {
                    return *iter;
                }
            }
            throw EntryNotFound("No such field with name : " + name);
        }

        const std::shared_ptr<FieldList> getFields() const
        {
            return fields;
        }
    };

    class Array : public Type
    {
    public:
        std::shared_ptr<Type> array;

        Array()
        {}

        Array(const std::shared_ptr<Type> &array)
                : array(array)
        {}
    };

    class Name : public Type
    {
    public:
        std::string name;
        std::shared_ptr<Type> type;

        Name(const std::string &name, const std::shared_ptr<Type> &type)
                : name(name), type(type)
        {}
    };

    // Default types

    namespace
    {
        // Make these static to save space
        std::shared_ptr<Nil> NIL;
        std::shared_ptr<Int> INT;
        std::shared_ptr<String> STRING;
        std::shared_ptr<Void> VOID;
        std::shared_ptr<Record> RECORD;
        std::shared_ptr<Array> ARRAY;
    }

    bool isNil(const std::shared_ptr<Type> &t) const
    {
        return typeid(*t) == typeid(Nil);
    }

    bool isInt(const std::shared_ptr<Type> &t) const
    {
        return typeid(*t) == typeid(Int);
    }

    bool isString(const std::shared_ptr<Type> &t) const
    {
        return typeid(*t) == typeid(String);
    }

    bool isVoid(const std::shared_ptr<Type> &t) const
    {
        return typeid(*t) == typeid(Void);
    }

    bool isRecord(const std::shared_ptr<Type> &t) const
    {
        return typeid(*t) == typeid(Record);
    }

    bool isArray(const std::shared_ptr<Type> &t) const
    {
        return typeid(*t) == typeid(Array);
    }

    bool isName(const std::shared_ptr<Type> &t) const
    {
        return typeid(*t) == typeid(Name);
    }

    bool match(const std::shared_ptr<Type> &t1,
               const std::shared_ptr<Type> &t2) const
    {
        return typeid(t1) == typeid(t2);
    }

    // Get type name
    const std::string getName(std::shared_ptr<Type> &t)
    {
        std::string name;
        if (isNil(t))
        { name = "nil"; }
        else if (isInt(t))
        { name = "int"; }
        else if (isString(t))
        { name = "string"; }
        else if (isVoid(t))
        { name = "void"; }
        else if (isRecord(t))
        { name = "record"; }
        else if (isName(t))
        { name = "name"; }
        return name;
    }
};

#endif //SRC_TYPES_H
