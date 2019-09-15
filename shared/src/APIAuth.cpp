#include "APIAuth.h"
#include "Processor.h"

using namespace std;

void APIAuth::load(Packet &packet) {
    name_ = packet.getString();
}

bool APIAuth::process(Information &info, Processor &proc) {
    return proc.handle_api_auth(info, *this);
}

void APIAuth::finish() {
    packet_.addHeader(HEADER_AUTH);
    packet_.addString(name_);
}