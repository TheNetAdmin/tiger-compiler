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
    public:
        Error() {}

        Error(const location &loc, const std::string &message)
                : loc(loc), message(message) {}

        void set(const location &loc, const std::string &message) {
            this->loc = loc;
            this->message = message;
        }

        void setLoc(const location &loc) {
            Error::loc = loc;
        }

        void setMessage(const std::string &message) {
            Error::message = message;
        }
    };
}

#endif //SRC_ERROR_H
