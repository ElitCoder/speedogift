#pragma once

// Boilerplate macros
#define SET_GET_MACRO(var, type)    void set_##var(type var) { var##_ = var; }  \
                                    type get_##var() const { return var##_; }
