//
// Created by PrinceXuan on 2017/5/31.
//

#include "Error.h"

namespace Tiger{

    Error::Error() : hasError(false) {}

    Error::Error(const location &loc, const std::string &message)
            : loc(loc), message(message), hasError(true) {}

    void Error::set(const location &loc, const std::string &message)
    {
        this->loc = loc;
        this->message = message;
        hasError = true;
    }

    void Error::print()
    {
        std::cerr << "Error at " << loc << " : " << message << std::endl;
    }
}