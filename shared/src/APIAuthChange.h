#pragma once

#include "API.h"
#include "Boilerplate.h"
#include "Processor.h"

class APIAuthChange : public API {
public:
    APIAuthChange() { header_ = HEADER_AUTH_CHANGE; }
    SET_GET_MACRO(mode, ClientMode)

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override { return proc.handle_api_auth_change(info, *this); };
    virtual void finish() override;

    ClientMode mode_;
};