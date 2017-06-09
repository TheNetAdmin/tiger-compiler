#include <iostream>
#include <fstream>
#include "src/driver.h"
#include "src/Semantic.h"
#include "src/PrintIRTree.h"
#include "src/cmdline.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "Tiger Compiler" << std::endl;
    Tiger::Driver driver;

    // Make arguments
    cmdline::parser cmd;
    cmd.add<std::string>("out_file_name", 'o', "output file name", false, "a.ir");
    cmd.add<std::string>("compile_file_name", 'c', "filename of the file to compile", false, "tiger.tig");
    cmd.add("trace_parsing", 'p', "trace parsing process");
    cmd.add("trace_scanning", 's', "trace scanning process");
    cmd.add("graph_viz", 'g', "use GraphViz's dot language as output");

    // Check arguments
    cmd.parse_check(argc, argv);
    if (cmd.exist("trace_parsing"))
    {
        driver.trace_parsing = true;
    }
    if (cmd.exist("trace_scanning"))
    {
        driver.trace_scanning = true;
    }
    std::string out_file_name = cmd.get<std::string>("out_file_name");
    std::string compile_file_name = cmd.get<std::string>("compile_file_name");

    // Start to compile
    driver.parse(compile_file_name);
    auto result = driver.result;
    if (driver.syntaxError)
    {
        std::cerr << "Tiger compiler exit with syntax error." << std::endl;
        exit(1);
    }
    auto fragList = Semantic::transProg(result);
    ofstream fo(out_file_name, ios::out);
    PrintIRTree printer(fragList);
    if(cmd.exist("graph_viz"))
    {
        printer.makeDotFile(fo);
    }
    else
    {
        printer.printIRTreeInFile(fo);
    }
    fo.close();

    return 0;
}