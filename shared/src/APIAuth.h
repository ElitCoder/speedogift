#pragma once

#include "API.h"

class APIAuth : public API {
public:
    void set_client_type(ClientType type);
    void set_client_name(const std::string &name);
    virtual void load(Packet &packet);

private:
    virtual void finish();

    ClientType type_;
    std::string name_;
};