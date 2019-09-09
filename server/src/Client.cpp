#include "Client.h"

using namespace std;

Client::Client(const APIAuth &api, size_t id) {
    id_ = id;
    type_ = api.get_client_type();
    name_ = api.get_client_name();
}

bool Client::has_id(size_t id) const {
    return id_ == id;
}

bool Client::has_name(const string &name) const {
    return name_ == name;
}

bool Client::has_type(ClientType type) const {
    return type_ == type;
}