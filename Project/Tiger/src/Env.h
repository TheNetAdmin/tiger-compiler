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

        virtual ~Entry();

        void setName(const std::string &name);
    };

    class TypeEntry : public Entry
    {
    public:
        std::shared_ptr<Type::Type> type;

        TypeEntry(const std::string &name, const std::shared_ptr<Type::Type> type);

        const std::shared_ptr<Type::Type> getType() const;
    };

    class VarEntry : public Entry
    {
    public:
        std::shared_ptr<Type::Type> type;
        std::shared_ptr<Translate::Access> access;

        VarEntry();

        VarEntry(const std::string &name,
                 const std::shared_ptr<Type::Type> type,
                 const std::shared_ptr<Translate::Access> access);

        std::shared_ptr<Type::Type> getType() const;

        void dumpInfo();
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

        FuncEntry(const std::shared_ptr<Translate::Level> level,
                  const std::shared_ptr<Temporary::Label> label,
                  const std::string &name,
                  const std::shared_ptr<ArgList> argTypeList,
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

        void dumpInfo()
        {
            std::cerr << "Func Entry Dump Info" << std::endl;
            std::cerr << "Func Name : " << name << std::endl;
            std::cerr << "Args : ";
            for (auto arg = args->begin(); arg != args->end(); arg++)
            {
                std::cerr << Type::getName(*arg) << " - ";
            }
            std::cerr << std::endl;
            std::cerr << "Return : " << Type::getName(result) << std::endl;
            std::cerr << std::endl;
        }
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

    class TypeEnv : public Env
    { // same as "tenv"
    public:
        std::vector<std::shared_ptr<TypeEntry>> bindList;
        std::vector<unsigned int> scope;

        TypeEnv();

        void setDefaultEnv() override;

        void enter(std::shared_ptr<TypeEntry> entry);

        void enterType(TypeEntry typeEntry);

        std::shared_ptr<TypeEntry> find(const std::string &name);

        void beginScope() override;

        void endScope() override;
    };

    class VarEnv : public Env
    {
    public:
        std::vector<std::shared_ptr<Entry>> bindList;
        std::vector<unsigned int> scope;

        VarEnv();

        void setDefaultEnv();

        void enter(std::shared_ptr<Entry> entry);

        void enterFunc(FuncEntry funcEntry);

        void enterVar(VarEntry varEntry);

        std::shared_ptr<Entry> find(const std::string &entryName);

        std::shared_ptr<VarEntry> findVar(const std::string &varName);

        std::shared_ptr<FuncEntry> findFunc(const std::string &funcName);

        void beginScope() override;

        void endScope() override;
    };

    std::shared_ptr<ArgList> makeArgList();
}
#endif //SRC_ENV_H
