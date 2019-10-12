#pragma once

#include "Processor.h"
#include "Client.h"

#include <ncnet/Server.h>

#include <vector>

using Clients = std::vector<Client>;

class ServerProcessor : public Processor {
public:
    ServerProcessor(ncnet::Server &server) : server_(server) {}

    virtual bool handle_api_auth(ncnet::Transfer &info, const APIAuth &api) override;
    virtual bool handle_api_list(ncnet::Transfer &info, const APIList &api) override;

private:
    bool client_is_valid(const APIAuth &api);

    ncnet::Server &server_;
    Clients clients_;
};