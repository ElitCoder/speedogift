#include "APIAuth.h"
#include "Processor.h"

using namespace ncnet;

void APIAuth::load(Packet &packet) {
    packet >> api_version_;
    packet >> name_;
}

void APIAuth::finish() {
    packet_ << API_VERSION << name_;
}