#pragma once

#include "Processor.h"
#include "Client.h"

#include <vector>

using Clients = std::vector<Client>;

class ServerProcessor : public Processor {
public:
    virtual bool handle_api_auth(Information &info, const APIAuth &api) override;

private:
    bool client_exists(size_t id);

    Clients clients_;
};