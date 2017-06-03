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
#include "Translate.h"
#include "Temporary.h"

namespace Env
{
    class Entry
    {
    public:
        std::string name;

        Entry();

        Entry(const std::string &name);

        void setName(const std::string &name);
    };

    class VarEntry : public Entry
    {
    public:
        std::shared_ptr<Type::Type> type;
        std::shared_ptr<Translate::Access> access;

        VarEntry();

        VarEntry(const std::string &name, const std::shared_ptr<Type::Type> type,
                 const std::shared_ptr<Translate::Access> access);

        std::shared_ptr<Type::Type> getType() const;
    };

    using ArgList = std::list<std::shared_ptr<Type::Type>>;

    class FuncEntry : public Entry
    {
    public:
        std::shared_ptr<ArgList> args;
        std::shared_ptr<Type::Type> result;
        std::shared_ptr<Translate::Level> level;
        std::shared_ptr<Temporary::Label> label;

        const std::shared_ptr<Translate::Level> getLevel() const;

        const std::shared_ptr<Temporary::Label> getLabel() const;

        FuncEntry();

        // Multiple arguments
        // @name:       function name
        // @argTypes:   function arguments' types list
        // @resultType: function return type
        FuncEntry(const std::shared_ptr<Translate::Level> level,
                  const std::shared_ptr<Temporary::Label> label,
                  const std::string &name,
                  const std::initializer_list<std::shared_ptr<Type::Type>> &argTypes,
                  const std::shared_ptr<Type::Type> resultType);


        // Only one argument
        // @name:       function name
        // @argType:    function argument type list
        // @resultType: function return type
        FuncEntry(const std::shared_ptr<Translate::Level> level,
                  const std::shared_ptr<Temporary::Label> label,
                  const std::string &name,
                  const std::shared_ptr<Type::Type> argType,
                  const std::shared_ptr<Type::Type> resultType);

        // TODO: use args==nullptr is invalid, replace with args->size() == 0
        // No argument
        // @name:       function name
        // @resultType: function return type
        FuncEntry(const std::shared_ptr<Translate::Level> level,
                  const std::shared_ptr<Temporary::Label> label,
                  const std::string &name,
                  const std::shared_ptr<Type::Type> result);

        void addArg(std::shared_ptr<Type::Type> arg);

        const std::shared_ptr<ArgList> getArgs() const;

        const std::shared_ptr<Type::Type> getResultType() const;
    };

    class Env
    {
    public:

        Env();

        virtual ~Env();

        virtual void setDefaultEnv() = 0;

        virtual void beginScope() =0;

        virtual void endScope() = 0;
    };

    class EntryNotFound : public std::runtime_error
    {
    public:
        explicit EntryNotFound(const std::string &msg);
    };

    class VarEnv : public Env
    { // same as "tenv"
    public:
        std::vector<VarEntry> bindList;
        std::vector<unsigned int> scope;

        VarEnv();

        void setDefaultEnv() override;

        void enter(VarEntry &entry);

        std::shared_ptr<VarEntry> find(const std::string &name);

        void beginScope() override;

        void endScope() override;
    };

    class FuncEnv : public Env
    {
    public:
        std::vector<FuncEntry> bindList;
        std::vector<unsigned int> scope;

        FuncEnv();

        void setDefaultEnv();

        void enter(FuncEntry &entry);

        std::shared_ptr<FuncEntry> find(const std::string &funcName);

        void beginScope() override;

        void endScope() override;
    };

}
#endif //SRC_ENV_H
