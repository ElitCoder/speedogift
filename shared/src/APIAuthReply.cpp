#include "APIAuthReply.h"

void APIAuthReply::set_allowed(bool allowed) {
    allowed_ = allowed;
}

void APIAuthReply::load(Packet &packet) {
    allowed_ = packet.getInt();
}

void APIAuthReply::finish() {
    packet_.addHeader(HEADER_AUTH_REPLY);
    packet_.addInt(allowed_);
}