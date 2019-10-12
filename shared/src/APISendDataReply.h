#pragma once

#include "API.h"
#include "Boilerplate.h"
#include "Processor.h"

class APISendDataReply : public API {
public:
    APISendDataReply() { header_ = HEADER_SEND_DATA_REPLY; }
    SET_GET_MACRO(allowed, bool)
    SET_GET_MACRO(error, ErrorCode)

private:
    virtual void load(ncnet::Packet &packet) override;
    virtual bool process(ncnet::Transfer &info, Processor &proc) override { (void)info; return proc.handle_api_send_data_reply(info, *this); }
    virtual void finish() override;

    bool allowed_;
    ErrorCode error_ = NO_ERROR;
};