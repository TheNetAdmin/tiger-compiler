# Tiger is a toy language

> This Project Just A practice-item, My Other Item is also Nice, check it, muhaha :) 

# Include

* nesting function
* hidden pointer as record
* array
* int/string
* kinds of control struct

### Lexical

* include: Identifiers, Comments, Integer literal, String literal
* reserved words: `while, break, let, in, end, function, var, type, array, if, then, else, do, of, nil`
* interpunction: `, : ; ( ) { } [ ] . + - * / = <> >= <= < > & | :=`
* comment(can be nested): `/* here  /* is */ content */`

### Provision

* `xxx` means strong reserved words xxx
*  `{x}`  means probility empty
*   `E`   means empty string
*  `//`   means about note
*   `$`  means such that
    
### Declare

#### declare sequence

    decs -> {dec}
    dec  -> tydec
	     -> vardec
	     -> fundec
	     
#### type declare
    
       typedec -> `type` type_id = ty
            ty -> type_id
               -> {typefields}
               -> array of type_id
    
    typefields -> E
               -> id: type_id{, id: type_id}
    
        //bulit-in type: `int`, `string`
        //record type: type Node = {key: int, next: Node}
        //array type: type intArray = array of int

#### variable
    
    vardec -> `var` id := expr
           -> `var` id: type_id := expr
           
       //if short type_id then id's type decided by invalid expr's type
       
#### function
    
    funcdec -> function id(params) = expr
            -> function id(params): type_id = expr
    
    //if short type_id then return void

### Scope Rules

* `let ...vardec | typedec | funcdec... in expr end` begin vardec end in `end`
* function params only live in function-body
* nest scope: Tiger allow visit outer scope var if def
* namespace: 1. Type's($ Node.int) 2. Var | Function ($ Node(), Node+1)
* rename: the lastest def always worked
    
### Var & Left Value

    lvalue -> id
           -> lvalue.id
           -> lvalue[int-expr]
    // lvalue is a memory addr
    // var, params, record-filed, array-index can be lvalue

### Exression

* lvalue:
when a lvalue in a expr, eval is the value in the mem-addr
* void:
some expr no eval $ process call, :=, if-then, while, break,
e.g. (a := b) + c is mistake semant
* nil:
nil is specilly belongs record type value.
if record v is nil, $ v.a is a running-time error.
it requeried nil must be assigned in a certain type.
* sequence:
like this (expr; expr; expr)
eval all the expr in order and choose the last expr(if there is) as the whole expr's value.
specially, () means void, `let ... in %nothing% end` also void
* literal:
decimal const int value
string  const 
negative const there is a minus sign before the number
* arithmetic:
int-expr op int-expr $ op [+, -, *, /] eval a int expr
* compare:
expr op expr $ op [=, <>, <, >, >=, <=] 
true => 1, false => 0.
= and <> op can also apply in record and array.(cmp them refrence)
string also can be cmp
* bool expr:
expr op expr $ op [&, |]
0 means false, not zero means ture
* operotor proprity:
proprity is uncertain due to comliter's uncertain
but ((`expr`) op expr) certain first eval nest-in expr
* record new:
record_type_id{filed_id = expr, ...}
or nil alloc memory but no init
* array new:
array_type_id[int-expr] of ii-expr
ii-expr is the init value
* assign:
when record or array assign they are equally point a same mem.
$ they are alloc in heap. alive all the program

### Lib

* function print(s: string) //print s to the stdout
* function flush() //empty the stdout cache
* function getchar(): string //from stdin read a char, if EOF return '\0'
* function ord(s: string): int //print the first char ascii number in s, if s is empty return -1
* function chr(i: int): string //inverse the prior function.
* function size(s: string): int // return length of s
* function substring(s: string, begin: int, length: int): string //sub from begin and length 's string
* function concat(s1: string, s2: string): string //link s1 and s2 get a new string
* function not(i: int): int // eval logic reverse
* function exit(i: int) // exit the program by status code i

### TEST

in the test/ dir there are 50s tig file you can test and refer
    
### About

* blog: https://github.com/whps/whps.github.io/issues/5
* book: Modern Compiler Implement in C
