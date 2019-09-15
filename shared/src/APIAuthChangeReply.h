#pragma once

#include "API.h"
#include "Processor.h"

class APIAuthChangeReply : public API {
public:
    APIAuthChangeReply() { header_ = HEADER_AUTH_CHANGE_REPLY; }

private:
    virtual void load(Packet &packet) override { (void)packet; };
    virtual bool process(Information &info, Processor &proc) override { (void)info; return proc.handle_api_auth_change_reply(*this); };
    virtual void finish() override {};
};