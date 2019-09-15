#pragma once

#include <string>

#include "Boilerplate.h"

class Client {
public:
    SET_GET_MACRO(name, const std::string &)
    SET_GET_MACRO(id, size_t)
    SET_GET_MACRO(api_version, const std::string &)

private:
    std::string name_;
    size_t id_;
    std::string api_version_;
};