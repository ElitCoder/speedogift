#pragma once

#include "API.h"
#include "Boilerplate.h"
#include "Processor.h"

class APISendData : public API {
public:
    APISendData() { header_ = HEADER_SEND_DATA; }
    SET_GET_MACRO(path, const std::string &)
    SET_GET_MACRO(name, const std::string &)
    SET_GET_MACRO(data, std::shared_ptr<unsigned char*>)

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override { return proc.handle_api_send_data(info, *this); }
    virtual void finish() override;

    std::string path_;
    std::string name_;
    std::shared_ptr<unsigned char*> data_;
};