#pragma once

#include <ncnet/Information.h>

class ProcessAPI {
public:
    static bool process(Information &information);

private:
    static bool handle_auth(Information &information);
};