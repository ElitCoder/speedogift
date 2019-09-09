#include "APIAuthReply.h"

void APIAuthReply::set_allowed(bool allowed) {
    allowed_ = allowed;
}

bool APIAuthReply::get_allowed() const {
    return allowed_;
}

void APIAuthReply::load(Packet &packet) {
    allowed_ = packet.getBool();
}

void APIAuthReply::finish() {
    packet_.addHeader(HEADER_AUTH_REPLY);
    packet_.addBool(allowed_);
}