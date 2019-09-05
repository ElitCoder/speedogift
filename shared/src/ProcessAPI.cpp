#include "ProcessAPI.h"
#include "APIAuth.h"
#include "APIAuthReply.h"
#include "Processor.h"

#include <ncnet/Information.h>

bool ProcessAPI::match_api(Information &info, Processor &processor) {
    // Switch packet header and load into API
    auto &packet = info.getPacket();
    auto header = packet.getHeader();
    if (header == HEADER_AUTH) {
        APIAuth api;
        api.load(packet);
        return processor.handle_api_auth(info, api);
    } else if (header == HEADER_AUTH_REPLY) {
        APIAuthReply api;
        api.load(packet);
        return processor.handle_api_auth_reply(info, api);
    }

    // Return bad result
    return false;
}