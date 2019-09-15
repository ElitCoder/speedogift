#include "APIAuth.h"
#include "Processor.h"

using namespace std;

void APIAuth::load(Packet &packet) {
    api_version_ = packet.getString();
    name_ = packet.getString();
}

void APIAuth::finish() {
    packet_.addString(API_VERSION);
    packet_.addString(name_);
}