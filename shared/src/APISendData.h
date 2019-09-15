#pragma once

#include "API.h"
#include "Processor.h"

class APISendData : public API {
public:
    APISendData() { header_ = HEADER_SEND_DATA; }

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override { return proc.handle_api_send_data(info, *this); }
    virtual void finish() override;
};