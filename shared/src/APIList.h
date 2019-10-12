#pragma once

#include "API.h"
#include "Processor.h"

class APIList : public API {
public:
    APIList() { header_ = HEADER_LIST; }

private:
    virtual void load(ncnet::Packet &packet) override { (void)packet; };
    virtual bool process(ncnet::Transfer &info, Processor &proc) override { return proc.handle_api_list(info, *this); };
    virtual void finish() override {};
};