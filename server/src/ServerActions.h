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
    void add_client(size_t id, const std::string &name, const std::string &version);
    Client *get_client(const std::string &name);
    Client *get_client_id(size_t id);

    void handle_api_auth();
    void handle_api_list();
    void handle_api_send();
    void handle_api_send_reply();
    void handle_api_change_active();

    ncnet::Server &server_;
    std::vector<Client> clients_;

    // Current request being processed
    ncnet::Packet *current_packet_original_;
    ncnet::Packet current_packet_;
    size_t current_id_;
};