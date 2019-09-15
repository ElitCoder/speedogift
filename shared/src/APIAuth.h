#pragma once

#include "API.h"
#include "Boilerplate.h"

class APIAuth : public API {
public:
    APIAuth() { header_ = HEADER_AUTH; }
    // APIAuth specific methods
    SET_GET_MACRO(name, const std::string &)
    GET_MACRO(api_version, const std::string &)

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override;
    virtual void finish() override;

    std::string name_;
    std::string api_version_;
};