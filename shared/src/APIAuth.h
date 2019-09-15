#pragma once

#include "API.h"
#include "Boilerplate.h"

class APIAuth : public API {
public:
    APIAuth() { header_ = HEADER_AUTH; }
    // APIAuth specific methods
    SET_GET_MACRO(name, const std::string &)

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override;
    virtual void finish() override;

    std::string name_;
};