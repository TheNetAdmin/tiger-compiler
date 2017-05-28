#include "driver.h"
#include "parser.h"
#include <cerrno>
#include <cstdlib>
#include <climits>
#include <cstring>

extern FILE* yyin;
extern int yy_flex_debug;

Tiger::Driver::Driver()
    : trace_scanning(false), trace_parsing(false)
{
}

Tiger::Driver::~Driver() {};

int Tiger::Driver::parse(const std::string & filename){
    this->filename = filename;
    scan_begin();
    Tiger::Parser parser(*this);
    parser.set_debug_level(trace_parsing);
    int res = parser.parse();
    scan_end();
    return res;
}


void Tiger::Driver::scan_begin(void){
    yy_flex_debug = trace_scanning;
    if (filename.empty() || filename == "-"){
        yyin = stdin;
    } else if (!(yyin = fopen(filename.c_str(), "r"))) {
        std::cerr << "Cannot open file : " << filename << " " << strerror(errno) << std::endl;
        exit (EXIT_FAILURE);
    }
}

void Tiger::Driver::scan_end(void){
    fclose(yyin);
}