#pragma once

#include "Actions.h"

#include <ncnet/Client.h>

class ClientActions : public Actions {
public:
    explicit ClientActions(ncnet::Client &client, const std::string &name);
    void process_request(ncnet::Transfer &transfer);
    void list_clients();
    void send_files(const std::string &name, const std::vector<std::string> &files);
    void set_active(bool active);

private:
    void handle_api_send(ncnet::Transfer &transfer);

    ncnet::Client &client_;
    std::string name_;
};