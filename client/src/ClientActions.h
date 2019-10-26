#pragma once

#include "Actions.h"

#include <ncnet/Client.h>

class ClientActions : public Actions {
public:
    explicit ClientActions(ncnet::Client &client, const std::string &name);
    void list_clients();
    void send_files(const std::string &name, const std::vector<std::string> &files);

private:
    ncnet::Client &client_;
    std::string name_;
};