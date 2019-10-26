#include "ServerActions.h"
#include "APIFactory.h"

#include "spdlog/spdlog.h"

using namespace std;
using namespace ncnet;

ServerActions::ServerActions(Server &server) : server_(server) {}

void ServerActions::process_request(Transfer &transfer) {
    auto header = transfer.get_packet().read_byte();
    switch (header) {
        case API_HEADER_AUTH:
            handle_api_auth(transfer);
            break;

        case API_HEADER_LIST:
            handle_api_list(transfer);
            break;

        case API_HEADER_SEND:
            handle_api_send(transfer);
            break;

        default:
            spdlog::warn("Unknown API header {}, disconnecting client {}", header, transfer.get_connection_id());
            server_.disconnect(transfer.get_connection_id());
    }
}

void ServerActions::remove_client(size_t id) {
    // TODO: Remove client with id
    spdlog::debug("Removing client {}", id);
}

void ServerActions::handle_api_auth(Transfer &transfer) {
    auto &packet = transfer.get_packet();
    string api_version;
    string name;
    packet >> api_version >> name;
    spdlog::debug("Got authentication attempt from {} with API version {}", name, api_version);
    // Always say OK for now
    server_.send_packet(APIFactory::auth_reply(API_STATUS_CODE_OK).get_packet(), transfer.get_connection_id());
}

void ServerActions::handle_api_list(Transfer &transfer) {
    spdlog::debug("Got list command");
    vector<APIFactory::ListReply> list;
    for (auto &client : clients_) {
        APIFactory::ListReply reply;
        reply.version = client.get_version();
        reply.name = client.get_name();
        reply.active = client.get_active();
        list.push_back(reply);
    }
    server_.send_packet(APIFactory::list_reply(list).get_packet(), transfer.get_connection_id());
}

void ServerActions::handle_api_send(Transfer &transfer) {
    spdlog::debug("Got send command");
    auto &packet = transfer.get_packet();
    string to;
    packet >> to;
    int nbr_files;
    packet >> nbr_files;
    for (int i = 0; i < nbr_files; i++) {
        string path;
        size_t size;
        string hash;
        packet >> path >> size >> hash;
        spdlog::debug("Request to send file {}", path);
    }
    server_.send_packet(APIFactory::send_reply(API_STATUS_CODE_OK).get_packet(), transfer.get_connection_id());
}