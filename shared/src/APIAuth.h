#pragma once

#include "API.h"

class APIAuth : public API {
public:
    // APIAuth specific methods
    void set_client_type(ClientType type);
    ClientType get_client_type() const;
    void set_client_name(const std::string &name);
    const std::string& get_client_name() const;

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override;
    virtual void finish() override;

    ClientType type_;
    std::string name_;
};