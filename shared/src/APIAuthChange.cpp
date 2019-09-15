#include "APIAuthChange.h"

void APIAuthChange::load(Packet &packet) {
    mode_ = static_cast<ClientMode>(packet.getInt());
}

void APIAuthChange::finish() {
    packet_.addInt(mode_);
}