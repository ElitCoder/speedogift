#pragma once

// Boilerplate macros
#define GET_MACRO(var, type)        type get_##var() const { return var##_; }

#define SET_GET_MACRO(var, type)    void set_##var(type var) { var##_ = var; }  \
                                    type get_##var() const { return var##_; }
