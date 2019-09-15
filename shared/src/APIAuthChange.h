#pragma once

#include "API.h"
#include "Processor.h"

class APIAuthChange : public API {
public:
    APIAuthChange() { header_ = HEADER_AUTH_CHANGE; }

private:
    virtual void load(Packet &packet) override { (void)packet; };
    virtual bool process(Information &info, Processor &proc) override { return proc.handle_api_auth_change(info, *this); };
    virtual void finish() override {};
};