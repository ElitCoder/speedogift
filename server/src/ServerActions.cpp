#include "ServerActions.h"
#include "APIFactory.h"

#include "spdlog/spdlog.h"

#include <algorithm>

using namespace std;

ServerActions::ServerActions(ncnet::Server &server) : server_(server) {}

void ServerActions::process_request(ncnet::Transfer &transfer) {
    current_packet_original_ = &transfer.get_packet();
    current_packet_ = transfer.get_packet();
    current_id_ = transfer.get_connection_id();

    auto header = current_packet_.read_byte();
    switch (header) {
        case API_HEADER_AUTH:
            handle_api_auth();
            break;

        case API_HEADER_LIST:
            handle_api_list();
            break;

        case API_HEADER_SEND:
            handle_api_send();
            break;

        case API_HEADER_SEND_REPLY:
            handle_api_send_reply();
            break;

        case API_HEADER_CHANGE_ACTIVE:
            handle_api_change_active();
            break;

        default:
            spdlog::warn("Unknown API header {}, disconnecting client {}", header, current_id_);
            server_.disconnect(current_id_);
    }
}

Client *ServerActions::get_client_id(size_t id) {
    auto iterator = find_if(clients_.begin(), clients_.end(), [&id] (auto &client) {
        return id == client.get_id();
    });

    if (iterator != clients_.end()) {
        return &*iterator;
    } else {
        return nullptr;
    }
}

Client *ServerActions::get_client(const string &name) {
    auto iterator = find_if(clients_.begin(), clients_.end(), [&name] (auto &client) {
        return name == client.get_name();
    });

    if (iterator != clients_.end()) {
        return &*iterator;
    } else {
        return nullptr;
    }
}

void ServerActions::add_client(size_t id, const string &name, const string &version) {
    // Check that there's no client with the same name
    if (get_client(name) != nullptr) {
        throw logic_error("Client already exists");
    }

    Client client;
    client.set_name(name);
    client.set_version(version);
    client.set_active(true); // Active by default until monitor mode
    client.set_id(id);

    clients_.push_back(client);
}

void ServerActions::remove_client(size_t id) {
    spdlog::debug("Removing client {}", id);
    clients_.erase(remove_if(clients_.begin(), clients_.end(), [&id] (auto &client) {
        return id == client.get_id();
    }), clients_.end());
}

void ServerActions::handle_api_auth() {
    string api_version;
    string name;
    current_packet_ >> api_version >> name;
    spdlog::debug("Got authentication attempt from {} {} with API version {}", current_id_, name, api_version);

    try {
        add_client(current_id_, name, api_version);
        server_.send_packet(APIFactory::auth_reply(API_STATUS_CODE_OK).get_packet(), current_id_);
    } catch (std::logic_error &e) {
        spdlog::warn("Adding client failed with {}", e.what());
        server_.send_packet(APIFactory::auth_reply(API_STATUS_CODE_NAME_ALREADY_TAKEN).get_packet(), current_id_);
    }
}

void ServerActions::handle_api_list() {
    spdlog::debug("Got list command");
    vector<APIFactory::ListReply> list;
    for (auto &client : clients_) {
        APIFactory::ListReply reply;
        reply.version = client.get_version();
        reply.name = client.get_name();
        reply.active = client.get_active();
        list.push_back(reply);
    }
    server_.send_packet(APIFactory::list_reply(list).get_packet(), current_id_);
}

void ServerActions::handle_api_send() {
    spdlog::debug("Got send command");
    string from;
    string to;
    current_packet_ >> from >> to;
    int nbr_files;
    current_packet_ >> nbr_files;
    for (int i = 0; i < nbr_files; i++) {
        string path;
        size_t size;
        string hash;
        current_packet_ >> path >> size >> hash;
        spdlog::debug("Request to send file {}", path);
    }

    APIStatusCode error = API_STATUS_CODE_OK;

    // Check that supplied name is same as authenticated name
    auto *from_client = get_client(from);
    if (from_client == nullptr || from_client->get_id() != current_id_) {
        spdlog::warn("Client requesting send command provides invalid information");
        error = API_STATUS_CODE_INVALID_REQUEST;
    }

    // Check if endpoint is connected and not active
    auto *to_client = get_client(to);
    if (to_client == nullptr) {
        error = API_STATUS_CODE_NOT_CONNECTED;
    } else if (to_client->get_active()) {
        error = API_STATUS_CODE_ALREADY_ACTIVE;
    }

    if (error != API_STATUS_CODE_OK) {
        // Not okay, man
        server_.send_packet(APIFactory::send_reply(from, to, error).get_packet(), current_id_);
        return;
    }

    // Ask endpoint if this is okay
    server_.send_packet(*current_packet_original_, to_client->get_id());
}

void ServerActions::handle_api_send_reply() {
    // Find client and relay answer
    // TODO: Add some sort of ticket system so new clients with the same does not receieve this response
    string from, to;
    current_packet_ >> from >> to;
    auto *client = get_client(from);
    if (client == nullptr) {
        spdlog::warn("Failed to return send request from {} to {}, client is not connected", from, to);
        return;
    }
    server_.send_packet(*current_packet_original_, client->get_id());
}

void ServerActions::handle_api_change_active() {
    bool active;
    current_packet_ >> active;
    auto *client = get_client_id(current_id_);
    if (client == nullptr) {
        spdlog::warn("Client is not connected");
        server_.send_packet(APIFactory::change_active_reply(API_STATUS_CODE_INVALID_REQUEST).get_packet(), current_id_);
        return;
    }
    client->set_active(active);
    spdlog::debug("Setting client to {}", active ? "active" : "inactive");
    server_.send_packet(APIFactory::change_active_reply(API_STATUS_CODE_OK).get_packet(), current_id_);
}