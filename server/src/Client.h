#pragma once

#include <APIAuth.h>

#include <cstddef>
#include <string>

class Client {
public:
    explicit Client(const APIAuth &api, size_t id);

    bool has_name(const std::string &name) const;
    bool has_type(ClientType type) const;
    bool has_id(size_t id) const;

private:
    std::string name_;
    ClientType type_;
    size_t id_;
};