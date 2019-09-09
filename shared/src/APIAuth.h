#pragma once

#include "API.h"

class APIAuth : public API {
public:
    void set_client_type(ClientType type);
    ClientType get_client_type() const;
    void set_client_name(const std::string &name);
    const std::string& get_client_name() const;
    virtual void load(Packet &packet);

private:
    virtual void finish();

    ClientType type_;
    std::string name_;
};