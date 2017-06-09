//
// Created by PrinceXuan on 2017/5/30.
//

#include "Types.h"

namespace Type
{
    EntryNotFound::EntryNotFound(const std::string &msg) : std::runtime_error(msg)
    {}

    Type::Type()
    {}

    Type::~Type()
    {}

    Nil::Nil()
    {}

    Int::Int()
    {}

    String::String()
    {}

    Void::Void()
    {}

    Field::Field(const std::string &name, const std::shared_ptr<Type> &type)
            : name(name), type(type)
    {}

    Record::Record()
            : fields(std::make_shared<FieldList>())
    {}

    Record::Record(std::initializer_list<std::shared_ptr<Field>> fields)
    {
        this->fields = std::make_shared<FieldList>(fields);
    }

    std::shared_ptr<Field> Record::find(std::string name, int &offset)
    {
        offset = 0;
        for (auto iter = fields->begin(); iter != fields->end(); iter++, offset++)
        {
            if ((*iter)->name == name)
            {
                return *iter;
            }
        }
        throw EntryNotFound("No such field with name : " + name);
    }

    const std::shared_ptr<FieldList> Record::getFields() const
    { return fields; }

    void Record::addField(const std::string &name, const std::shared_ptr<Type> type)
    {
        Field field(name, type);
        fields->push_back(std::make_shared<Field>(field));
    }

    Array::Array()
            : array(std::make_shared<Type>())
    {}

    Array::Array(const std::shared_ptr<Type> &array) : array(array)
    {}

    void Array::setArray(const std::shared_ptr<Type> &array)
    { this->array = array; }

    Name::Name(const std::string &name, const std::shared_ptr<Type> &type)
            : name(name), type(type)
    {}

    Name::Name()
            : type(std::make_shared<Type>())
    {}

    bool isNil(const std::shared_ptr<Type> &t)
    {
        return typeid(*t) == typeid(Nil);
    }

    bool isInt(const std::shared_ptr<Type> &t)
    {
        return typeid(*t) == typeid(Int);
    }

    bool isString(const std::shared_ptr<Type> &t)
    {
        return typeid(*t) == typeid(String);
    }

    bool isRecord(const std::shared_ptr<Type> &t)
    {
        return typeid(*t) == typeid(Record);
    }

    bool isVoid(const std::shared_ptr<Type> &t)
    {
        return typeid(*t) == typeid(Void);
    }

    bool isName(const std::shared_ptr<Type> &t)
    {
        return typeid(*t) == typeid(Name);
    }

    bool match(const std::shared_ptr<Type> &t1, const std::shared_ptr<Type> &t2)
    {
        return typeid(t1) == typeid(t2);
    }

    const std::string getName(const std::shared_ptr<Type> &t)
    {
        std::string name = "Unknown";
        if (isNil(t))
        {
            name = "nil";
        }
        else if (isInt(t))
        {
            name = "int";
        }
        else if (isString(t))
        {
            name = "string";
        }
        else if (isVoid(t))
        {
            name = "void";
        }
        else if (isRecord(t))
        {
            name = "record";
        }
        else if (isName(t))
        {
            name = "name";
        }
        else if (isArray(t))
        {
            name = "array";
        }
        return name;
    }

    bool isArray(const std::shared_ptr<Type> &t)
    {
        return typeid(*t) == typeid(Array);
    }
}
