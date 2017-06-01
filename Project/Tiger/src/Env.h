//
// Created by PrinceXuan on 2017/5/30.
//

#ifndef SRC_ENV_H
#define SRC_ENV_H

#include <memory>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include "Types.h"

namespace Env
{
    class Entry
    {
    public:
        std::string name;

        Entry()
        {
            name = "NotDefined";
        }

        Entry(const std::string &name)
                : name(name)
        {}
    };

    class VarEntry : public Entry
    {
    public:
        std::shared_ptr<Type::Type> type;

        VarEntry(const std::string &name,
                 const std::shared_ptr<Type::Type> &type)
                : Entry(name), type(type)
        {}

        const std::shared_ptr<Type::Type> getType() const
        {
            return type;
        }
    };

    class FuncEntry : public Entry
    {
    public:
        using ArgList = std::list<std::shared_ptr<Type::Type>>;
        std::shared_ptr<ArgList> args;
        std::shared_ptr<Type::Type> result;

        // Multiple arguments
        // @name:       function name
        // @argTypes:   function arguments' types list
        // @resultType: function return type
        FuncEntry(const std::string &name,
                  const std::initializer_list<std::shared_ptr<Type::Type>> &argTypes,
                  const std::shared_ptr<Type::Type> &resultType)
                : Entry(name), result(resultType)
        {
            args = std::make_shared<ArgList>(argTypes);
        }


        // Only one argument
        // @name:       function name
        // @argType:    function argument type list
        // @resultType: function return type
        FuncEntry(const std::string &name,
                  const std::shared_ptr<Type::Type> &argType,
                  const std::shared_ptr<Type::Type> &resultType)
                : Entry(name), result(resultType)
        {
            ArgList arg;
            arg.push_back(argType);
            args = std::make_shared<ArgList>(arg);
        }

        // No argument
        // @name:       function name
        // @resultType: function return type
        FuncEntry(const std::string &name,
                  const std::shared_ptr<Type::Type> &result)
                : Entry(name), result(result)
        {}

        void addArg(std::shared_ptr<Type::Type> arg)
        {
            args->push_back(arg);
        }

        const std::shared_ptr<ArgList> getArgs() const
        {
            return args;
        }

        const std::shared_ptr<Type::Type> getResultType() const
        {
            return result;
        }
    };

    virtual class Env
    {
    public:

        Env()
        {}

        virtual ~Env()
        {}

        virtual void setDefaultEnv() = 0;

        virtual void beginScope() =0;

        virtual void endScope() = 0;
    };

    class EntryNotFound : public std::runtime_error
    {
    public:
        explicit EntryNotFound(const std::string &msg)
                : std::runtime_error(msg)
        {}
    };

    class VarEnv : public Env
    { // same as "tenv"
    public:
        std::vector<VarEntry> bindList;
        std::vector<unsigned int> scope;

        VarEnv()
        {}

        void setDefaultEnv() override
        {
            VarEntry intVar("int", Type::INT);
            enter(intVar);
            VarEntry stringVar("string", Type::STRING);
            enter(stringVar);
        }

        void enter(VarEntry &entry)
        {
            bindList.push_back(entry);
        }

        std::shared_ptr<VarEntry> find(const std::string &name)
        {
            // TODO: refactor with std::find
            for (auto r_iter = bindList.crbegin(); r_iter != bindList.crend(); r_iter++)
            {
                if (r_iter->name == name)
                {
                    return std::make_shared<VarEntry>(*r_iter);
                }
            }
            throw EntryNotFound("Var Entry with name " + name + " not found");
        }

        void beginScope() override
        {
            scope.push_back(bindList.size());
        }

        void endScope() override
        {
            auto s = scope.back();
            scope.pop_back();
            bindList.resize(s);
        }
    };

    class FuncEnv : public Env
    {
    public:
        std::vector<FuncEntry> bindList;
        std::vector<unsigned int> scope;

        FuncEnv()
        {}

        void setDefaultEnv()
        {
            // print
            FuncEntry print("print", Type::STRING, Type::VOID);
            enter(print);
            // flush
            FuncEntry flush("flush", Type::VOID);
            enter(flush);
            // getchar
            FuncEntry getchar("getchar", Type::VOID);
            enter(getchar);
            // ord
            FuncEntry ord("ord", Type::STRING, Type::INT);
            enter(ord);
            // chr
            FuncEntry chr("chr", Type::INT, Type::STRING);
            enter(chr);
            // size
            FuncEntry size("size", Type::STRING, Type::INT);
            enter(size);
            // substring
            FuncEntry substring("substring", {Type::STRING, Type::INT, Type::INT}, Type::STRING);
            enter(substring);
            // concat
            FuncEntry concat("concat", {Type::STRING, Type::STRING}, Type::STRING);
            enter(concat);
            // not
            FuncEntry notFunc("not", Type::INT, Type::INT);
            enter(notFunc);
            // exit
            FuncEntry exit("exit", Type::INT, Type::VOID);
            enter(exit);
        }

        void enter(FuncEntry &entry)
        {
            this->bindList.push_back(entry);
        }

        std::shared_ptr<FuncEntry> find(const std::string &funcName)
        {
            for (auto r_iter = bindList.crbegin(); r_iter != bindList.crend(); r_iter++)
            {
                if (r_iter->name == funcName)
                {
                    return std::make_shared<FuncEntry>(*r_iter);
                }
            }
            throw EntryNotFound("Func entry with name " + funcName + " not found");
        }

        void beginScope() override
        {
            scope.push_back(bindList.size());
        }

        void endScope() override
        {
            auto s = scope.back();
            scope.pop_back();
            bindList.resize(s);
        }
    };

}
#endif //SRC_ENV_H
