#include "ProcessAPI.h"
#include "API.h"

#include <ncconf/Log.h>

bool ProcessAPI::process(Information &information) {
    auto header = information.getPacket().getHeader();

    switch (header) {
        case HEADER_AUTH: return handle_auth(information);
        default: Log(WARN) << "Unknown header " << header << " received";
            return false;
    }
}

bool ProcessAPI::handle_auth(Information &information) {
    return false;
}