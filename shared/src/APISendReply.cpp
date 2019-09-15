#include "APISendReply.h"

void APISendReply::load(Packet &packet) {
    allowed_ = packet.getBool();
    if (!allowed_) {
        error_ = static_cast<ErrorCode>(packet.getInt());
        return;
    }
    auto size = packet.getInt();
    for (int i = 0; i < size; i++) {
        ips_.push_back(packet.getString());
    }
}

void APISendReply::finish() {
    packet_.addBool(allowed_);
    if (!allowed_) {
        packet_.addInt(error_);
        return;
    }
    packet_.addInt(ips_.size());
    for (auto &ip : ips_) {
        packet_.addString(ip);
    }
}