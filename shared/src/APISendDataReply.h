#pragma once

#include "API.h"
#include "Processor.h"

class APISendDataReply : public API {
public:
    APISendDataReply() { header_ = HEADER_SEND_DATA_REPLY; }

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override { (void)info; return proc.handle_api_send_data_reply(info, *this); }
    virtual void finish() override;
};