#include "APIAuthChangeReply.h"

void APIAuthChangeReply::load(Packet &packet) {
    allowed_ = packet.getBool();
    if (!allowed_) {
        error_ = static_cast<ErrorCode>(packet.getInt());
    }
}

void APIAuthChangeReply::finish() {
    packet_.addBool(allowed_);
    if (!allowed_) {
        packet_.addInt(error_);
    }
}