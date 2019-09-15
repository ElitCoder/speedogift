#include "APISendDataReply.h"

void APISendDataReply::load(Packet &packet) {
    allowed_ = packet.getBool();
    if (!allowed_) {
        error_ = static_cast<ErrorCode>(packet.getInt());
    }
}

void APISendDataReply::finish() {
    packet_.addBool(allowed_);
    if (!allowed_) {
        packet_.addInt(error_);
    }
}