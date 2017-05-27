#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <FlexLexer.h>
#include "parser.tab.hh"
#include "location.hh"

namespace Tiger
{
class Scanner : public yyFlexLexer
{
  public:
    Scanner(std::istream *in) : yyFlexLexer(in){};
    virtual ~Scanner(){};
    using FlexLexer::yylex;
    virtual int yylex(Tiger::Parser::semantic_type *const lval,
                      Tiger::Parser::location_type *location);

  private:
    Tiger::Parser::semantic_type *yylval = nullptr;
}
}

#endif // ! __SCANNER_H__