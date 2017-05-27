#include "driver.h"
#include "parser.hh"
#include <cerrno>

Tiger::Driver::Driver()
    : trace_scanning(false), trace_parsing(false)
{
}

Tiger::Driver::~Driver() {};

int Tiger::Driver::parse(const std::string & filename){
    this->filename = filename;
    scan_begin();
    Tiger::Parser parser(*this);
    parser.set_debug_level(trce_parsing);
    int res = parser.parse();
    scan_end();
    return res;
}


void Tiger::Driver::error(const location_type & loc, const std::string & msg)
{
    std::cerr << "Error at " << loc << " : " << msg << std::endl;
}

void Tiger::Driver::scan_begin(void){
    yy_flex_debug = trace_scanning;
    if (filename.empty() || filename == "-"){
        yyin = stdin;
    } else if (!(yyin = fopen(filename.c_str(), "r"))) {
        cerr << "Cannot open file : " << filename << " " << strerror(errno) << endl;
        exit (EXIT_FAILURE);
    }
}

void Tiger::Driver::scan_end(void){
    fclose(yyin);
}