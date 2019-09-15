#pragma once

#include "API.h"
#include "Boilerplate.h"
#include "Processor.h"

class APISendReply : public API {
public:
    APISendReply() { header_ = HEADER_SEND_REPLY; }
    SET_GET_MACRO(allowed, bool)
    SET_GET_MACRO(error, ErrorCode)
    void add_ip(const std::string &ip) { ips_.push_back(ip); }
    const std::vector<std::string> &get_ips() const { return ips_; }

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override { (void)info; return proc.handle_api_send_reply(*this); }
    virtual void finish() override;

    bool allowed_;
    ErrorCode error_ = NO_ERROR;
    std::vector<std::string> ips_;
};