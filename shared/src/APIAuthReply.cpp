#include "APIAuthReply.h"
#include "Processor.h"

void APIAuthReply::load(Packet &packet) {
    allowed_ = packet.getBool();
}

bool APIAuthReply::process(Information &info, Processor &proc) {
    return proc.handle_api_auth_reply(info, *this);
}

void APIAuthReply::finish() {
    packet_.addHeader(HEADER_AUTH_REPLY);
    packet_.addBool(allowed_);
}