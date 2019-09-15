#include "APIListReply.h"

void APIListReply::load(Packet &packet) {
    auto size = packet.getInt();
    for (int i = 0; i < size; i++) {
        ListReply reply;
        reply.api_version = packet.getString();
        reply.name = packet.getString();
        reply.idle = packet.getBool();
        add_reply(reply);
    }
}

void APIListReply::finish() {
    packet_.addInt(replies_.size());
    for (auto& reply : replies_) {
        packet_.addString(reply.api_version);
        packet_.addString(reply.name);
        packet_.addBool(reply.idle);
    }
}