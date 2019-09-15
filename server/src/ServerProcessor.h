#pragma once

#include "Processor.h"
#include "Client.h"

#include <ncnet/Server.h>

#include <vector>

using Clients = std::vector<Client>;

class ServerProcessor : public Processor {
public:
    ServerProcessor(Server &server) : server_(server) {}

    virtual bool handle_api_auth(Information &info, const APIAuth &api) override;

private:
    bool client_is_valid(const APIAuth &api);

    Server &server_;
    Clients clients_;
};