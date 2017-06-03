#include <iostream>
#include <fstream>
#include "../src/driver.h"
#include "../src/Semantic.h"
#include "../src/PrintIRTree.h"

using namespace std;

int main(int argc, char * argv[]){
    std::cout << "Tiger Compiler" << std::endl;
    Tiger::Driver driver;
    for (int i = 1; i < argc ; ++i) {
        if (argv[i] == std::string("-p"))
            driver.trace_parsing = true;
        else if (argv[i] == std::string("-s"))
            driver.trace_scanning = true;
        else{
            std::cout << "Openning file: " << argv[i] << std::endl;
            driver.parse(argv[i]);
            auto result = driver.result;
            auto fragList = Semantic::transProg(result);
            ofstream fo("tiger.txt", ios::out);
            PrintIRTree printer(fragList);
            printer.printIRTreeInFile(cout);
        }
    }
    return 0;
}