//
// Created by PrinceXuan on 2017/5/31.
//

#ifndef SRC_ERROR_H
#define SRC_ERROR_H

#include "location.hh"
#include <string>

namespace Tiger {
    class Error {
        location loc;
        std::string message;
        bool hasError;
    public:
        Error() : hasError(false)
        {}

        Error(const location &loc, const std::string &message)
                : loc(loc), message(message), hasError(true)
        {}

        void set(const location &loc, const std::string &message) {
            this->loc = loc;
            this->message = message;
            hasError = true;
        }

    };
}

#endif //SRC_ERROR_H
