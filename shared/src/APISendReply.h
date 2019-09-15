#pragma once

#include "API.h"
#include "Processor.h"

class APISendReply : public API {
public:
    APISendReply() { header_ = HEADER_SEND_REPLY; }

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override { (void)info; return proc.handle_api_send_reply(*this); }
    virtual void finish() override;
};