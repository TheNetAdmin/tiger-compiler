#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <string>
#include "parser.hh"

#define YY_DECL \
    Tiger::Parser::symbol_type yylex(Driver & driver)
YY_DECL;

namespace Tiger{
class Driver{
    bool trace_scanning;
    std::string filename;
    bool trace_parsing;
public:
    Driver();
    virtual ~Driver();
    void scan_begin();
    void scan_end();
    int parse(const std::string& filename);
    void error(const location_type & loc, const std::string & msg);
};

}

#endif // ! __DRIVER_H__