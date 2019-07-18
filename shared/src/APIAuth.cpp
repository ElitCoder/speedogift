#include "APIAuth.h"

using namespace std;

void APIAuth::set_client_type(ClientType type) {
    type_ = type;
}

void APIAuth::set_client_name(const string &name) {
    name_ = name;
}

void APIAuth::finish() {
    packet_.addHeader(HEADER_AUTH);
    packet_.addInt(type_);
    //packet_.addString(name);
    packet_.finalize();
}