// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "src/parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.h"

// User implementation prologue.

#line 51 "src/parser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 28 "src/bison/parser.yy" // lalr1.cc:413

#include "driver.h"
    using namespace AST;
shared_ptr<AST::Exp> absyn_root;

#line 60 "src/parser.cpp" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 4 "src/bison/parser.yy" // lalr1.cc:479
namespace Tiger {
#line 146 "src/parser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Tiger::Driver & driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 5: // INT
        value.move< int > (that.value);
        break;

      case 55: // dec
      case 56: // tydecs
      case 60: // vardec
      case 61: // fundecs
        value.move< shared_ptr<AST::Dec> > (that.value);
        break;

      case 54: // decs
        value.move< shared_ptr<AST::DecList> > (that.value);
        break;

      case 52: // refields
        value.move< shared_ptr<AST::EFieldList> > (that.value);
        break;

      case 48: // program
      case 49: // exp
      case 50: // seq
      case 51: // record
      case 53: // array
      case 65: // funcall
        value.move< shared_ptr<AST::Exp> > (that.value);
        break;

      case 63: // explist
      case 66: // args
        value.move< shared_ptr<AST::ExpList> > (that.value);
        break;

      case 59: // typefields
        value.move< shared_ptr<AST::FieldList> > (that.value);
        break;

      case 62: // fundec
        value.move< shared_ptr<AST::FunDec> > (that.value);
        break;

      case 58: // ty
        value.move< shared_ptr<AST::Ty> > (that.value);
        break;

      case 57: // tydec
        value.move< shared_ptr<AST::TypeTy> > (that.value);
        break;

      case 64: // lvalue
        value.move< shared_ptr<AST::Var> > (that.value);
        break;

      case 3: // ID
      case 4: // STRING
      case 67: // id
        value.move< string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 5: // INT
        value.copy< int > (that.value);
        break;

      case 55: // dec
      case 56: // tydecs
      case 60: // vardec
      case 61: // fundecs
        value.copy< shared_ptr<AST::Dec> > (that.value);
        break;

      case 54: // decs
        value.copy< shared_ptr<AST::DecList> > (that.value);
        break;

      case 52: // refields
        value.copy< shared_ptr<AST::EFieldList> > (that.value);
        break;

      case 48: // program
      case 49: // exp
      case 50: // seq
      case 51: // record
      case 53: // array
      case 65: // funcall
        value.copy< shared_ptr<AST::Exp> > (that.value);
        break;

      case 63: // explist
      case 66: // args
        value.copy< shared_ptr<AST::ExpList> > (that.value);
        break;

      case 59: // typefields
        value.copy< shared_ptr<AST::FieldList> > (that.value);
        break;

      case 62: // fundec
        value.copy< shared_ptr<AST::FunDec> > (that.value);
        break;

      case 58: // ty
        value.copy< shared_ptr<AST::Ty> > (that.value);
        break;

      case 57: // tydec
        value.copy< shared_ptr<AST::TypeTy> > (that.value);
        break;

      case 64: // lvalue
        value.copy< shared_ptr<AST::Var> > (that.value);
        break;

      case 3: // ID
      case 4: // STRING
      case 67: // id
        value.copy< string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 13 "src/bison/parser.yy" // lalr1.cc:741
{
    yyla.location.begin.filename = yyla.location.end.filename = &driver.filename;
}

#line 537 "src/parser.cpp" // lalr1.cc:741

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 5: // INT
        yylhs.value.build< int > ();
        break;

      case 55: // dec
      case 56: // tydecs
      case 60: // vardec
      case 61: // fundecs
        yylhs.value.build< shared_ptr<AST::Dec> > ();
        break;

      case 54: // decs
        yylhs.value.build< shared_ptr<AST::DecList> > ();
        break;

      case 52: // refields
        yylhs.value.build< shared_ptr<AST::EFieldList> > ();
        break;

      case 48: // program
      case 49: // exp
      case 50: // seq
      case 51: // record
      case 53: // array
      case 65: // funcall
        yylhs.value.build< shared_ptr<AST::Exp> > ();
        break;

      case 63: // explist
      case 66: // args
        yylhs.value.build< shared_ptr<AST::ExpList> > ();
        break;

      case 59: // typefields
        yylhs.value.build< shared_ptr<AST::FieldList> > ();
        break;

      case 62: // fundec
        yylhs.value.build< shared_ptr<AST::FunDec> > ();
        break;

      case 58: // ty
        yylhs.value.build< shared_ptr<AST::Ty> > ();
        break;

      case 57: // tydec
        yylhs.value.build< shared_ptr<AST::TypeTy> > ();
        break;

      case 64: // lvalue
        yylhs.value.build< shared_ptr<AST::Var> > ();
        break;

      case 3: // ID
      case 4: // STRING
      case 67: // id
        yylhs.value.build< string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 75 "src/bison/parser.yy" // lalr1.cc:859
    {absyn_root = yystack_[0].value.as< shared_ptr<AST::Exp> > (); driver.result = absyn_root;}
#line 706 "src/parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 77 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeVarExp(yylhs.location, yystack_[0].value.as< shared_ptr<AST::Var> > ());}
#line 712 "src/parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 78 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = yystack_[0].value.as< shared_ptr<AST::Exp> > ();}
#line 718 "src/parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 79 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeAssignExp(yylhs.location, yystack_[2].value.as< shared_ptr<AST::Var> > (), yystack_[0].value.as< shared_ptr<AST::Exp> > ());}
#line 724 "src/parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 80 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeNilExp(yylhs.location);}
#line 730 "src/parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 81 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = yystack_[0].value.as< shared_ptr<AST::Exp> > ();}
#line 736 "src/parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 82 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeIntExp(yylhs.location, yystack_[0].value.as< int > ());}
#line 742 "src/parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 83 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeStringExp(yylhs.location, yystack_[0].value.as< string > ());}
#line 748 "src/parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 84 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeLetExp(yylhs.location, yystack_[3].value.as< shared_ptr<AST::DecList> > (), MakeSeqExp(yylhs.location, yystack_[1].value.as< shared_ptr<AST::ExpList> > ()));}
#line 754 "src/parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 85 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeIfExp(yylhs.location, yystack_[4].value.as< shared_ptr<AST::Exp> > (), yystack_[2].value.as< shared_ptr<AST::Exp> > (), yystack_[0].value.as< shared_ptr<AST::Exp> > ());}
#line 760 "src/parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 86 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeIfExp(yylhs.location, yystack_[2].value.as< shared_ptr<AST::Exp> > (), yystack_[0].value.as< shared_ptr<AST::Exp> > (), nullptr);}
#line 766 "src/parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 87 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, PLUS,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 772 "src/parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 88 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, MINUS,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 778 "src/parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 89 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, TIMES,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 784 "src/parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 90 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, DIVIDE,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 790 "src/parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 91 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, EQ,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 796 "src/parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 92 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, MINUS,
                                                                      MakeIntExp(yylhs.location, 0),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 802 "src/parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 93 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, NEQ,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 808 "src/parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 94 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, GT,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 814 "src/parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 95 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, LT,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 820 "src/parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 96 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, GE,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 826 "src/parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 97 "src/bison/parser.yy" // lalr1.cc:859
              {
                  yylhs.value.as<shared_ptr<AST::Exp> >() = MakeOpExp(yylhs.location, LE,
                                                                      yystack_[2].value.as<shared_ptr<AST::Exp> >(),
                                                                      yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 832 "src/parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 98 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeIfExp(yylhs.location, yystack_[2].value.as< shared_ptr<AST::Exp> > (), yystack_[0].value.as< shared_ptr<AST::Exp> > (), MakeIntExp(yylhs.location, 0));}
#line 838 "src/parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 99 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeIfExp(yylhs.location, yystack_[2].value.as< shared_ptr<AST::Exp> > (), MakeIntExp(yylhs.location,1), yystack_[0].value.as< shared_ptr<AST::Exp> > ());}
#line 844 "src/parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 100 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = yystack_[0].value.as< shared_ptr<AST::Exp> > ();}
#line 850 "src/parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 101 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = yystack_[0].value.as< shared_ptr<AST::Exp> > ();}
#line 856 "src/parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 102 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeWhileExp(yylhs.location, yystack_[2].value.as< shared_ptr<AST::Exp> > (), yystack_[0].value.as< shared_ptr<AST::Exp> > ());}
#line 862 "src/parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 103 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeForExp(yylhs.location, yystack_[6].value.as< string > (), yystack_[4].value.as< shared_ptr<AST::Exp> > (), yystack_[2].value.as< shared_ptr<AST::Exp> > (), yystack_[0].value.as< shared_ptr<AST::Exp> > ());}
#line 868 "src/parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 104 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeBreakExp(yylhs.location);}
#line 874 "src/parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 106 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeSeqExp(yylhs.location, yystack_[1].value.as< shared_ptr<AST::ExpList> > ());}
#line 880 "src/parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 108 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeRecordExp(yylhs.location, yystack_[3].value.as< string > (), yystack_[1].value.as< shared_ptr<AST::EFieldList> > ());}
#line 886 "src/parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 110 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::EFieldList> > () = MakeEFieldList(MakeEField(yystack_[4].value.as< string > (), yystack_[2].value.as< shared_ptr<AST::Exp> > ()), yystack_[0].value.as< shared_ptr<AST::EFieldList> > ());}
#line 892 "src/parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 111 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::EFieldList> > () = MakeEFieldList(MakeEField(yystack_[2].value.as< string > (), yystack_[0].value.as< shared_ptr<AST::Exp> > ()), nullptr);}
#line 898 "src/parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 112 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::EFieldList> > () = nullptr;}
#line 904 "src/parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 114 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeArrayExp(yylhs.location, yystack_[5].value.as< string > (), yystack_[3].value.as< shared_ptr<AST::Exp> > (), yystack_[0].value.as< shared_ptr<AST::Exp> > ());}
#line 910 "src/parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 117 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::DecList> > () = MakeDecList(yystack_[1].value.as< shared_ptr<AST::Dec> > (), yystack_[0].value.as< shared_ptr<AST::DecList> > ());}
#line 916 "src/parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 118 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::DecList> > () = nullptr;}
#line 922 "src/parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 120 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Dec> > () = yystack_[0].value.as< shared_ptr<AST::Dec> > ();}
#line 928 "src/parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 121 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Dec> > () = yystack_[0].value.as< shared_ptr<AST::Dec> > ();}
#line 934 "src/parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 122 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Dec> > () = yystack_[0].value.as< shared_ptr<AST::Dec> > ();}
#line 940 "src/parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 124 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Dec> > () = MakeTypeDec(yylhs.location, MakeTypeTyList(yystack_[1].value.as< shared_ptr<AST::TypeTy> > (), dynamic_pointer_cast<TypeDec>(yystack_[0].value.as< shared_ptr<AST::Dec> > ())->getType()));}
#line 946 "src/parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 125 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Dec> > () = MakeTypeDec(yylhs.location, MakeTypeTyList(yystack_[0].value.as< shared_ptr<AST::TypeTy> > (), nullptr));}
#line 952 "src/parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 127 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::TypeTy> > () = MakeTypeTy(yystack_[2].value.as< string > (), yystack_[0].value.as< shared_ptr<AST::Ty> > ());}
#line 958 "src/parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 129 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Ty> > () = MakeNameTy(yylhs.location, yystack_[0].value.as< string > ());}
#line 964 "src/parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 130 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Ty> > () = MakeRecordTy(yylhs.location, yystack_[1].value.as< shared_ptr<AST::FieldList> > ());}
#line 970 "src/parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 131 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Ty> > () = MakeArrayTy(yylhs.location, yystack_[0].value.as< string > ());}
#line 976 "src/parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 133 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::FieldList> > () = MakeFieldList(MakeField(yylhs.location, yystack_[4].value.as< string > (), yystack_[2].value.as< string > ()), yystack_[0].value.as< shared_ptr<AST::FieldList> > ());}
#line 982 "src/parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 134 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::FieldList> > () = MakeFieldList(MakeField(yylhs.location, yystack_[2].value.as< string > (), yystack_[0].value.as< string > ()), nullptr);}
#line 988 "src/parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 135 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::FieldList> > () = nullptr;}
#line 994 "src/parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 137 "src/bison/parser.yy" // lalr1.cc:859
              {
                  string s = "";
                  yylhs.value.as<shared_ptr<AST::Dec> >() = MakeVarDec(yylhs.location, yystack_[2].value.as<string>(),
                                                                       s,
                                                                       yystack_[0].value.as<shared_ptr<AST::Exp> >());
              }
#line 1000 "src/parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 138 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Dec> > () = MakeVarDec(yylhs.location, yystack_[4].value.as< string > (), yystack_[2].value.as< string > (), yystack_[0].value.as< shared_ptr<AST::Exp> > ());}
#line 1006 "src/parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 140 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Dec> > () = MakeFunctionDec(yylhs.location, MakeFunDecList(yystack_[1].value.as< shared_ptr<AST::FunDec> > (), dynamic_pointer_cast<FunctionDec>(yystack_[0].value.as< shared_ptr<AST::Dec> > ())->getFunction()));}
#line 1012 "src/parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 141 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Dec> > () = MakeFunctionDec(yylhs.location, MakeFunDecList(yystack_[0].value.as< shared_ptr<AST::FunDec> > (), nullptr));}
#line 1018 "src/parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 143 "src/bison/parser.yy" // lalr1.cc:859
    {string v = "void"; yylhs.value.as< shared_ptr<AST::FunDec> > () = MakeFunDec(yylhs.location, yystack_[5].value.as< string > (), v, yystack_[3].value.as< shared_ptr<AST::FieldList> > (), yystack_[0].value.as< shared_ptr<AST::Exp> > ());}
#line 1024 "src/parser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 144 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::FunDec> > () = MakeFunDec(yylhs.location, yystack_[7].value.as< string > (), yystack_[2].value.as< string > (), yystack_[5].value.as< shared_ptr<AST::FieldList> > (), yystack_[0].value.as< shared_ptr<AST::Exp> > ());}
#line 1030 "src/parser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 146 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::ExpList> > () = MakeExpList(yystack_[2].value.as< shared_ptr<AST::Exp> > (), yystack_[0].value.as< shared_ptr<AST::ExpList> > ());}
#line 1036 "src/parser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 147 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::ExpList> > () = MakeExpList(yystack_[0].value.as< shared_ptr<AST::Exp> > (), nullptr);}
#line 1042 "src/parser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 148 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::ExpList> > () = nullptr;}
#line 1048 "src/parser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 150 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Var> > () = MakeSimpleVar(yylhs.location, yystack_[0].value.as< string > ());}
#line 1054 "src/parser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 151 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Var> > () = MakeFieldVar(yylhs.location, yystack_[2].value.as< shared_ptr<AST::Var> > (), yystack_[0].value.as< string > ());}
#line 1060 "src/parser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 152 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Var> > () = MakeSubscriptVar(yylhs.location, MakeSimpleVar(yylhs.location, yystack_[3].value.as< string > ()), yystack_[1].value.as< shared_ptr<AST::Exp> > ());}
#line 1066 "src/parser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 153 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Var> > () = MakeSubscriptVar(yylhs.location, yystack_[3].value.as< shared_ptr<AST::Var> > (), yystack_[1].value.as< shared_ptr<AST::Exp> > ());}
#line 1072 "src/parser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 155 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::Exp> > () = MakeCallExp(yylhs.location, yystack_[3].value.as< string > (), yystack_[1].value.as< shared_ptr<AST::ExpList> > ());}
#line 1078 "src/parser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 157 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::ExpList> > () = MakeExpList(yystack_[2].value.as< shared_ptr<AST::Exp> > (), yystack_[0].value.as< shared_ptr<AST::ExpList> > ());}
#line 1084 "src/parser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 158 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::ExpList> > () = MakeExpList(yystack_[0].value.as< shared_ptr<AST::Exp> > (), nullptr);}
#line 1090 "src/parser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 159 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< shared_ptr<AST::ExpList> > () = nullptr;}
#line 1096 "src/parser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 161 "src/bison/parser.yy" // lalr1.cc:859
    {yylhs.value.as< string > () =yystack_[0].value.as< string > ();}
#line 1102 "src/parser.cpp" // lalr1.cc:859
    break;


#line 1106 "src/parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -53;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      57,   -53,   -53,   -53,    57,    57,    57,    57,     6,   -31,
     -53,   -53,    18,   310,   -53,   -53,   -53,    58,   -53,   -18,
     -53,   216,   -11,   158,   284,    59,     6,     6,     6,    23,
     -31,   -53,    20,   -53,   -53,    24,   -53,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,     6,    57,    57,     6,    57,   -53,    57,    57,    57,
      43,    -5,    61,    57,   -53,   -53,   -53,    95,    95,   203,
     203,   203,   203,   203,   203,    16,    16,   -53,   -53,   310,
     170,   -53,   235,    44,   193,    41,    65,   -53,   269,   -53,
      13,     6,    57,     6,     2,    34,   -53,    57,   -53,    56,
     -53,    57,    57,    57,    50,    54,   310,    74,     6,    64,
     -53,   -53,   -53,   -53,    57,   252,   -53,   297,    -7,     6,
      57,    67,     6,   -53,     6,    57,    57,     6,    62,   310,
     -53,   -53,   -53,   -53,   310,    72,     6,    57,   -53,   310
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,    68,     9,     8,     0,    59,     0,     0,     0,    38,
      30,     6,     0,     2,     7,    26,    27,     3,     4,    60,
      18,    58,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    43,    40,    41,    54,     1,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    67,     0,    35,    59,    31,     0,     0,     0,
       0,     0,     0,    59,    37,    42,    53,    24,    25,    17,
      19,    21,    23,    20,    22,    13,    14,    15,    16,     5,
       0,    61,    66,     0,     0,     0,     0,    57,    12,    28,
       0,    50,     0,     0,     0,     0,    63,    67,    64,    62,
      32,     0,     0,     0,     0,     0,    51,     0,    50,     0,
      44,    45,    10,    65,     0,    34,    11,     0,     0,     0,
       0,     0,     0,    36,    35,     0,     0,     0,    49,    52,
      46,    47,    33,    29,    55,     0,    50,     0,    48,    56
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -53,   -53,     0,   -53,   -53,   -37,   -53,    85,   -53,    84,
     -53,   -53,   -41,   -53,    53,   -53,   -52,   -53,   -53,    -8,
      28
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,    12,    21,    14,    15,    85,    16,    29,    30,    31,
      32,   110,   104,    33,    34,    35,    22,    17,    18,    83,
      19
  };

  const short int
  Parser::yytable_[] =
  {
      13,    92,   126,    87,    20,     1,    23,    24,    52,     1,
      53,    95,    54,    26,    27,    28,    56,   127,    36,    93,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,   108,    47,    48,   109,    25,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,   103,    82,    84,    60,    61,    62,    88,    89,    90,
       1,     2,     3,    63,    49,    59,    28,   121,    26,    91,
      94,    98,   100,     4,   101,   112,   114,   118,   119,    81,
     120,   137,    86,     5,   122,   136,    50,   132,    66,   113,
      51,     6,   106,     7,     8,   138,     9,    82,   130,    10,
      11,   115,   116,   117,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,   123,    64,    65,     0,     0,   105,
     129,   107,   111,     0,     0,   133,   134,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   139,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,     0,     0,
     131,     0,    86,     0,     0,   135,     0,     0,     0,     0,
       0,     0,     0,     0,   105,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,     0,
       0,     0,     0,    57,     0,     0,     0,     0,     0,    96,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,
      47,    48,    99,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,     0,     0,     0,     0,     0,
       0,    55,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,     0,     0,     0,     0,    97,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,     0,     0,     0,     0,   124,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,     0,     0,
     102,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    58,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,   125,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48
  };

  const short int
  Parser::yycheck_[] =
  {
       0,     6,     9,    55,     4,     3,     6,     7,    26,     3,
      28,    63,    30,    44,    45,    46,    27,    24,     0,    24,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    30,    17,    18,    33,     8,    37,    38,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    38,    52,    53,    26,    27,    28,    57,    58,    59,
       3,     4,     5,    40,     6,     6,    46,   108,    44,    26,
       9,    27,    31,    16,     9,    41,    20,    27,    24,    51,
       6,     9,    54,    26,    20,    23,    28,   124,    35,    97,
      32,    34,    92,    36,    37,   136,    39,    97,    31,    42,
      43,   101,   102,   103,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,   114,    30,    32,    -1,    -1,    91,
     120,    93,    94,    -1,    -1,   125,   126,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   108,   137,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   119,    -1,    -1,
     122,    -1,   124,    -1,    -1,   127,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   136,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    -1,
      -1,    -1,    -1,    35,    -1,    -1,    -1,    -1,    -1,    29,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    29,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    25,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    -1,    -1,    -1,    -1,    23,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    -1,    -1,    -1,    -1,    23,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    -1,    -1,
      21,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,     4,     5,    16,    26,    34,    36,    37,    39,
      42,    43,    48,    49,    50,    51,    53,    64,    65,    67,
      49,    49,    63,    49,    49,    67,    44,    45,    46,    54,
      55,    56,    57,    60,    61,    62,     0,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,     6,
      28,    32,    26,    28,    30,    25,    27,    35,    19,     6,
      67,    67,    67,    40,    54,    56,    61,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    67,    49,    66,    49,    52,    67,    63,    49,    49,
      49,    26,     6,    24,     9,    63,    29,    23,    27,    29,
      31,     9,    21,    38,    59,    67,    49,    67,    30,    33,
      58,    67,    41,    66,    20,    49,    49,    49,    27,    24,
       6,    59,    20,    49,    23,    19,     9,    24,    67,    49,
      31,    67,    52,    49,    49,    67,    23,     9,    59,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    47,    48,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    50,    51,    52,    52,    52,    53,    54,    54,    55,
      55,    55,    56,    56,    57,    58,    58,    58,    59,    59,
      59,    60,    60,    61,    61,    62,    62,    63,    63,    63,
      64,    64,    64,    64,    65,    66,    66,    66,    67
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     1,     1,     3,     1,     1,     1,     1,
       5,     6,     4,     3,     3,     3,     3,     3,     2,     3,
       3,     3,     3,     3,     3,     3,     1,     1,     4,     8,
       1,     3,     4,     5,     3,     0,     6,     2,     0,     1,
       1,     1,     2,     1,     4,     1,     3,     3,     5,     3,
       0,     4,     6,     2,     1,     7,     9,     3,     1,     0,
       1,     3,     4,     4,     4,     3,     1,     0,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"END OF FILE\"", "error", "$undefined", "ID", "STRING", "INT",
  "ASSIGN", "AND", "OR", "EQ", "NEQ", "LT", "LE", "GT", "GE", "PLUS",
  "MINUS", "TIMES", "DIVIDE", "DO", "OF", "ELSE", "UMINUS", "COMMA",
  "COLON", "SEMICOLON", "LPAREN", "RPAREN", "LBRACK", "RBRACK", "LBRACE",
  "RBRACE", "DOT", "ARRAY", "IF", "THEN", "WHILE", "FOR", "TO", "LET",
  "IN", "END", "BREAK", "NIL", "FUNCTION", "VAR", "TYPE", "$accept",
  "program", "exp", "seq", "record", "refields", "array", "decs", "dec",
  "tydecs", "tydec", "ty", "typefields", "vardec", "fundecs", "fundec",
  "explist", "lvalue", "funcall", "args", "id", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
          0, 75, 75, 77, 78, 79, 80, 81, 82, 83,
          84, 85, 86, 87, 88, 89, 90, 91, 92, 93,
          94, 95, 96, 97, 98, 99, 100, 101, 102, 103,
          104, 106, 108, 110, 111, 112, 114, 117, 118, 120,
          121, 122, 124, 125, 127, 129, 130, 131, 133, 134,
          135, 137, 138, 140, 141, 143, 144, 146, 147, 148,
          150, 151, 152, 153, 155, 157, 158, 159, 161
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 4 "src/bison/parser.yy" // lalr1.cc:1167
} // Tiger
#line 1601 "src/parser.cpp" // lalr1.cc:1167
#line 163 "src/bison/parser.yy" // lalr1.cc:1168

void Tiger::Parser::error (const location_type & l, const string & m)
{
    driver.error(l, m);
}
