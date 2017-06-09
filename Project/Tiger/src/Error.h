//
// Created by PrinceXuan on 2017/5/31.
//

#ifndef SRC_ERROR_H
#define SRC_ERROR_H

#include <string>
#include <iostream>
#include "location.hh"

namespace Tiger {
class Error {
    location loc;
    std::string message;
    bool hasError;

   public:
    Error();

    Error(const std::string & message);

    Error(const location &loc, const std::string &message);

    void set(const location &loc, const std::string &message);

    void print();
};
}

#endif  // SRC_ERROR_H
