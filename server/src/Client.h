#pragma once

#include "Boilerplate.h"

#include <string>

class Client {
public:
    SET_GET_MACRO(name, const std::string &)
    SET_GET_MACRO(version, const std::string &)
    SET_GET_MACRO(active, bool)

private:
    std::string name_;
    std::string version_;
    bool active_;
};