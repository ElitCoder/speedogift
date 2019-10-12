#pragma once

#include "API.h"
#include "Boilerplate.h"
#include "Processor.h"

class APIAuthChangeReply : public API {
public:
    APIAuthChangeReply() { header_ = HEADER_AUTH_CHANGE_REPLY; }
    SET_GET_MACRO(allowed, bool)
    SET_GET_MACRO(error, ErrorCode)

private:
    virtual void load(ncnet::Packet &packet) override;
    virtual bool process(ncnet::Transfer &info, Processor &proc) override { (void)info; return proc.handle_api_auth_change_reply(*this); };
    virtual void finish() override;

    bool allowed_;
    ErrorCode error_ = NO_ERROR;
};