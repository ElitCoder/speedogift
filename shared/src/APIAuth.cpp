#include "APIAuth.h"

using namespace std;

void APIAuth::set_client_type(ClientType type) {
    type_ = type;
}

void APIAuth::set_client_name(const string &name) {
    name_ = name;
}

void APIAuth::load(Packet &packet) {
    type_ = static_cast<ClientType>(packet.getInt());
}

void APIAuth::finish() {
    packet_.addHeader(HEADER_AUTH);
    packet_.addInt(type_);
}