#include "APIAuth.h"
#include "Processor.h"

using namespace std;

void APIAuth::set_client_type(ClientType type) {
    type_ = type;
}

ClientType APIAuth::get_client_type() const {
    return type_;
}

void APIAuth::set_client_name(const string &name) {
    name_ = name;
}

const string& APIAuth::get_client_name() const {
    return name_;
}

void APIAuth::load(Packet &packet) {
    type_ = static_cast<ClientType>(packet.getInt());
    name_ = packet.getString();
}

bool APIAuth::process(Information &info, Processor &proc) {
    return proc.handle_api_auth(info, *this);
}

void APIAuth::finish() {
    packet_.addHeader(HEADER_AUTH);
    packet_.addInt(type_);
    packet_.addString(name_);
}