#pragma once

#include "API.h"

class APIAuthReply : public API {
public:
    void set_allowed(bool allowed);
    bool get_allowed() const;
    virtual void load(Packet &packet);

private:
    virtual void finish();

    bool allowed_;
};