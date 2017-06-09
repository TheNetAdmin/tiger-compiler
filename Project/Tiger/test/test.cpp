#include <iostream>
#include "../src/driver.h"

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
        }
    }
    return 0;
}