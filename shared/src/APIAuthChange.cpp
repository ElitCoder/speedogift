#include "APIAuthChange.h"

using namespace ncnet;

void APIAuthChange::load(Packet &packet) {
    int mode;
    packet >> mode;
    mode_ = (ClientMode)mode;
}

void APIAuthChange::finish() {
    packet_ << (int)mode_;
}