//
// Created by PrinceXuan on 2017/5/30.
//

#include "Env.h"

namespace Env
{

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
            : type(std::make_shared<Type::Type>()),
              access(std::make_shared<Translate::Access>())
    {}

    VarEntry::VarEntry(const std::string &name, const std::shared_ptr<Type::Type> type,
                       const std::shared_ptr<Translate::Access> access)
            : Entry(name), type(type), access(access)
    {}

    std::shared_ptr<Type::Type> VarEntry::getType() const
    {
        return type;
    }

    FuncEntry::FuncEntry()
            : args(std::make_shared<ArgList>()),
              result(std::make_shared<Type::Type>()),
              level(std::make_shared<Translate::Level>()),
              label(std::make_shared<Temporary::Label>())
    {}

    FuncEntry::FuncEntry(const std::shared_ptr<Translate::Level> level,
                         const std::shared_ptr<Temporary::Label> label,
                         const std::string &name,
                         const std::shared_ptr<Type::Type> argType,
                         const std::shared_ptr<Type::Type> resultType)
            : Entry(name), level(level), label(label), result(resultType)
    {
        ArgList arg;
        arg.push_back(argType);
        args = std::make_shared<ArgList>(arg);
    }

    FuncEntry::FuncEntry(const std::shared_ptr<Translate::Level> level,
                         const std::shared_ptr<Temporary::Label> label,
                         const std::string &name,
                         const std::shared_ptr<Type::Type> result)
            : Entry(name), level(level), label(label), result(result), args(std::make_shared<ArgList>())
    {}

    void FuncEntry::addArg(std::shared_ptr<Type::Type> arg)
    {
        args->push_back(arg);
    }

    const std::shared_ptr<ArgList> FuncEntry::getArgs() const
    {
        return args;
    }

    const std::shared_ptr<Type::Type> FuncEntry::getResultType() const
    {
        return result;
    }

    FuncEntry::FuncEntry(const std::shared_ptr<Translate::Level> level,
                         const std::shared_ptr<Temporary::Label> label,
                         const std::string &name,
                         const std::initializer_list<std::shared_ptr<Type::Type>> &argTypes,
                         const std::shared_ptr<Type::Type> resultType)
            : Entry(name), level(level), label(label), result(resultType)
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
        VarEntry intVar("int", Type::INT, std::shared_ptr<Translate::Access>());
        enter(intVar);
        VarEntry stringVar("string", Type::STRING, std::shared_ptr<Translate::Access>());
        enter(stringVar);
    }

    void VarEnv::enter(VarEntry &entry)
    {
        bindList.push_back(entry);
    }

    std::shared_ptr<VarEntry> VarEnv::find(const std::string &name)
    {
        for (auto r_iter = bindList.crbegin(); r_iter != bindList.crend(); r_iter++)
        {
            if (r_iter->name == name)
            {
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
        FuncEntry print(Translate::getGlobalLevel(), Temporary::makeLabel(),
                        "print", Type::STRING, Type::VOID);
        enter(print);
        // flush
        FuncEntry flush(Translate::getGlobalLevel(), Temporary::makeLabel(),
                        "flush", Type::VOID);
        enter(flush);
        // getchar
        FuncEntry getchar(Translate::getGlobalLevel(), Temporary::makeLabel(),
                          "getchar", Type::VOID);
        enter(getchar);
        // ord
        FuncEntry ord(Translate::getGlobalLevel(), Temporary::makeLabel(),
                      "ord", Type::STRING, Type::INT);
        enter(ord);
        // chr
        FuncEntry chr(Translate::getGlobalLevel(), Temporary::makeLabel(),
                      "chr", Type::INT, Type::STRING);
        enter(chr);
        // size
        FuncEntry size(Translate::getGlobalLevel(), Temporary::makeLabel(),
                       "size", Type::STRING, Type::INT);
        enter(size);
        // substring
        FuncEntry substring(Translate::getGlobalLevel(), Temporary::makeLabel(),
                            "substring", {Type::STRING, Type::INT, Type::INT}, Type::STRING);
        enter(substring);
        // concat
        FuncEntry concat(Translate::getGlobalLevel(), Temporary::makeLabel(),
                         "concat", {Type::STRING, Type::STRING}, Type::STRING);
        enter(concat);
        // not
        FuncEntry notFunc(Translate::getGlobalLevel(), Temporary::makeLabel(),
                          "not", Type::INT, Type::INT);
        enter(notFunc);
        // exit
        FuncEntry exit(Translate::getGlobalLevel(), Temporary::makeLabel(),
                       "exit", Type::INT, Type::VOID);
        enter(exit);
    }

    void FuncEnv::enter(FuncEntry &entry)
    {
        this->bindList.push_back(entry);
    }

    std::shared_ptr<FuncEntry> FuncEnv::find(const std::string &funcName)
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