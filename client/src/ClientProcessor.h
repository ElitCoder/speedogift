#pragma once

#include "Processor.h"
#include "Boilerplate.h"

#include <cxxopts.hpp>
#include <ncnet/Client.h>

class API;

class ClientProcessor : public Processor {
public:
    ClientProcessor(Client &client) : client_(client) {}
    SET_GET_MACRO(direct_port, int)
    void process_options(cxxopts::ParseResult &options);

private:
    Client &client_;
    int direct_port_;
};