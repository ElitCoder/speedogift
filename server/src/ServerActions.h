#pragma once

#include <ncnet/Server.h>

#include "Actions.h"
#include "Client.h"

class ServerActions : public Actions {
public:
    explicit ServerActions(ncnet::Server &server);
    void process_request(ncnet::Transfer &transfer);
    void remove_client(size_t id);

private:
    void handle_api_auth(ncnet::Transfer &transfer);
    void handle_api_list(ncnet::Transfer &transfer);
    void handle_api_send(ncnet::Transfer &transfer);

    ncnet::Server &server_;
    std::vector<Client> clients_;
};