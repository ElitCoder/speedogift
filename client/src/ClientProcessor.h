#pragma once

#include "Processor.h"
#include "Boilerplate.h"

#include <cxxopts.hpp>
#include <ncnet/Client.h>

class API;

class ClientProcessor : public Processor {
public:
    ClientProcessor(ncnet::Client &client) : client_(client) {}
    SET_GET_MACRO(direct_port, int)
    bool process_options(cxxopts::ParseResult &options);

    // Processor functionality
    virtual bool handle_api_auth_reply(const APIAuthReply &reply) override;
    virtual bool handle_api_list_reply(const APIListReply &reply) override;

private:
    ncnet::Client &client_;
    int direct_port_;
};