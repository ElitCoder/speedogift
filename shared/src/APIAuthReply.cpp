#include "APIAuthReply.h"
#include "Processor.h"

void APIAuthReply::load(Packet &packet) {
    allowed_ = packet.getBool();
    error_ = static_cast<ErrorCode>(packet.getInt());
}

void APIAuthReply::finish() {
    packet_.addBool(allowed_);
    packet_.addInt(error_);
}