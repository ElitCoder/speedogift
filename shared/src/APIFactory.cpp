#include "APIFactory.h"
#include "API.h"

using namespace std;
using namespace ncnet;

static API create_api_wrapper(Packet &packet, APIHeader reply) {
    API api;
    api.set_packet(packet);
    api.set_reply_header(reply);
    return api;
}

static API create_generic(APIHeader header, APIHeader reply) {
    Packet packet;
    packet.add_byte(header);
    return create_api_wrapper(packet, reply);
}

static API create_generic_reply(APIHeader header, APIStatusCode code) {
    Packet packet;
    packet.add_byte(header);
    packet << code;
    return create_api_wrapper(packet, API_HEADER_NONE);
}

API APIFactory::auth(const string &name) {
    Packet packet;
    packet.add_byte(API_HEADER_AUTH);
    packet << API_VERSION;
    packet << name;
    return create_api_wrapper(packet, API_HEADER_AUTH_REPLY);
}

API APIFactory::auth_reply(APIStatusCode code) {
    return create_generic_reply(API_HEADER_AUTH_REPLY, code);
}

API APIFactory::list() {
    return create_generic(API_HEADER_LIST, API_HEADER_LIST_REPLY);
}

API APIFactory::list_reply(const vector<APIFactory::ListReply> &clients) {
    Packet packet;
    packet.add_byte(API_HEADER_LIST_REPLY);
    packet << clients.size();
    for (auto &client : clients) {
        packet << client.version << client.name << client.active;
    }
    return create_api_wrapper(packet, API_HEADER_NONE);
}

API APIFactory::send(const string &name, const vector<APIFactory::Send> &files) {
    Packet packet;
    packet.add_byte(API_HEADER_SEND);
    packet << name;
    packet << files.size();
    for (auto &file : files) {
        packet << file.path << file.size << file.hash;
    }
    return create_api_wrapper(packet, API_HEADER_SEND_REPLY);
}

API APIFactory::send_reply(APIStatusCode code) {
    return create_generic_reply(API_HEADER_SEND_REPLY, code);
}