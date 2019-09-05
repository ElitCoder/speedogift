#pragma once

#include <cstddef>

class Client {
public:
    bool has_id(size_t id) const;

private:
    size_t id_;
};