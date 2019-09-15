#pragma once

#include "Processor.h"

#include <ncnet/Server.h>

#include <vector>

class ServerProcessor : public Processor {
public:
    ServerProcessor(Server &server);

    virtual bool handle_api_auth(Information &info, const APIAuth &api) override;

private:
    bool client_is_valid(const APIAuth &api);

    Server &server_;
};