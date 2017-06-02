//
// Created by PrinceXuan on 2017/5/30.
//

#include "Env.h"
#include "Types.h"
#include "Debug.h"

namespace Env{

    Entry::Entry()
    {
        name = "NotDefined";
    }

    Entry::Entry(const std::string &name)
            : name(name)
    {}

    void Entry::setName(const std::string &name)
    {
        Entry::name = name;
    }

    VarEntry::VarEntry()
    {}

    VarEntry::VarEntry(const std::string &name, const std::shared_ptr <Type::Type> &type)
            : Entry(name), type(type)
    {}

    std::shared_ptr <Type::Type> VarEntry::getType() const
    {
        return type;
    }

    FuncEntry::FuncEntry()
    {}

    FuncEntry::FuncEntry(const std::string &name, const std::shared_ptr <Type::Type> &argType,
                         const std::shared_ptr <Type::Type> &resultType)
            : Entry(name), result(resultType)
    {
        ArgList arg;
        arg.push_back(argType);
        args = std::make_shared<ArgList>(arg);
    }

    FuncEntry::FuncEntry(const std::string &name, const std::shared_ptr <Type::Type> &result)
            : Entry(name), result(result)
    {}

    void FuncEntry::addArg(std::shared_ptr <Type::Type> arg)
    {
        args->push_back(arg);
    }

    const std::shared_ptr <ArgList> FuncEntry::getArgs() const
    {
        return args;
    }

    const std::shared_ptr <Type::Type> FuncEntry::getResultType() const
    {
        return result;
    }

    FuncEntry::FuncEntry(const std::string &name, const std::initializer_list <std::shared_ptr<Type::Type>> &argTypes,
                         const std::shared_ptr <Type::Type> &resultType)
            : Entry(name), result(resultType)
    {
        args = std::make_shared<ArgList>(argTypes);
    }

    Env::Env()
    {}

    Env::~Env()
    {}

    EntryNotFound::EntryNotFound(const std::string &msg)
            : std::runtime_error(msg)
    {}

    VarEnv::VarEnv()
    {}

    void VarEnv::setDefaultEnv()
    {
        VarEntry intVar("int", Type::INT);
        enter(intVar);
        VarEntry stringVar("string", Type::STRING);
        enter(stringVar);
    }

    void VarEnv::enter(VarEntry &entry)
    {
        bindList.push_back(entry);
    }

    std::shared_ptr <VarEntry> VarEnv::find(const std::string &name)
    {
        // TODO: refactor with std::find
        for (auto r_iter = bindList.crbegin(); r_iter != bindList.crend(); r_iter++)
        {
            if (r_iter->name == name)
            {
                debugStart(r_iter->name);
                std::cout << r_iter->type << std::endl;
                return std::make_shared<VarEntry>(*r_iter);
            }
        }
        throw EntryNotFound("Var Entry with name " + name + " not found");
    }

    void VarEnv::beginScope()
    {
        scope.push_back(bindList.size());
    }

    void VarEnv::endScope()
    {
        auto s = scope.back();
        scope.pop_back();
        bindList.resize(s);
    }

    FuncEnv::FuncEnv()
    {}

    void FuncEnv::setDefaultEnv()
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

    void FuncEnv::enter(FuncEntry &entry)
    {
        this->bindList.push_back(entry);
    }

    std::shared_ptr <FuncEntry> FuncEnv::find(const std::string &funcName)
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

    void FuncEnv::beginScope()
    {
        scope.push_back(bindList.size());
    }

    void FuncEnv::endScope()
    {
        auto s = scope.back();
        scope.pop_back();
        bindList.resize(s);
    }
}