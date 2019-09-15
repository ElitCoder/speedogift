#pragma once

#include "API.h"
#include "Processor.h"

class APISend : public API {
public:
    APISend() { header_ = HEADER_SEND; }

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override { return proc.handle_api_send(info, *this); }
    virtual void finish() override;
};