#include "APIListReply.h"

using namespace ncnet;

void APIListReply::load(Packet &packet) {
    size_t size;
    packet >> size;
    for (size_t i = 0; i < size; i++) {
        ListReply reply;
        packet >> reply.api_version;
        packet >> reply.name;
        packet >> reply.idle;
        add_reply(reply);
    }
}

void APIListReply::finish() {
    packet_ << replies_.size();
    for (auto& reply : replies_) {
        packet_ << reply.api_version << reply.name << reply.idle;
    }
}