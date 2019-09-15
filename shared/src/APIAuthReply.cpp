#include "APIAuthReply.h"
#include "Processor.h"

void APIAuthReply::load(Packet &packet) {
    allowed_ = packet.getBool();
    error_ = static_cast<ErrorCode>(packet.getInt());
}

bool APIAuthReply::process(Information &info, Processor &proc) {
    return proc.handle_api_auth_reply(info, *this);
}

void APIAuthReply::finish() {
    packet_.addBool(allowed_);
    packet_.addInt(error_);
}