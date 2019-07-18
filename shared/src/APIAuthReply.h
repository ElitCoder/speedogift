#pragma once

#include "API.h"

class APIAuthReply : public API {
public:
    void set_allowed(bool allowed);
    virtual void finish();

private:
    bool allowed_;
};