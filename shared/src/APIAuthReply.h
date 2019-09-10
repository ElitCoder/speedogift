#pragma once

#include "API.h"

class APIAuthReply : public API {
public:
    void set_allowed(bool allowed);
    bool get_allowed() const;

private:
    virtual void load(Packet &packet) override;
    virtual bool process(Information &info, Processor &proc) override;
    virtual void finish() override;

    bool allowed_;
};