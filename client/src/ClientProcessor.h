#pragma once

#include "Processor.h"

#define SET_GET_MACRO(var, type)    void set_##var(type var) { var##_ = var; }  \
                                    type get_##var() const { return var##_; }

class ClientProcessor : public Processor {
public:
    SET_GET_MACRO(direct_port, int)

private:
    int direct_port_;
};