#pragma once

#include "API.h"
#include "Boilerplate.h"
#include "Processor.h"

struct ListReply {
    std::string name;
    std::string api_version;
    bool idle;
};

class APIListReply : public API {
public:
    APIListReply() { header_ = HEADER_LIST_REPLY; }
    void add_reply(ListReply &reply) { replies_.push_back(reply); }
    const std::vector<ListReply>& get_replies() const { return replies_; }

private:
    virtual void load(ncnet::Packet &packet) override;
    virtual bool process(ncnet::Transfer &info, Processor &proc) override { (void)info; return proc.handle_api_list_reply(*this); }
    virtual void finish() override;

    std::vector<ListReply> replies_;
};