#pragma once

#include "API.h"
#include "Processor.h"

struct Send {
    std::string path;
    std::string name;
    size_t size;
    std::string hash;
};

class APISend : public API {
public:
    APISend() { header_ = HEADER_SEND; }
    void add_file(Send &file) { files_.push_back(file); }
    const std::vector<Send> &get_files() const { return files_; }

private:
    virtual void load(ncnet::Packet &packet) override;
    virtual bool process(ncnet::Transfer &info, Processor &proc) override { return proc.handle_api_send(info, *this); }
    virtual void finish() override;

    std::string to_name_;
    std::vector<Send> files_;
};