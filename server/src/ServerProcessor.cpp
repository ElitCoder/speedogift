#include "ServerProcessor.h"
#include "APIAuth.h"
#include "APIAuthReply.h"
#include "APIListReply.h"

#include <ncnet/Transfer.h>
#include <spdlog/spdlog.h>

#include <algorithm>

using namespace ncnet;
using namespace std;

bool ServerProcessor::handle_api_list(Transfer &info, const APIList &api) {
    (void)api;
    // List all users
    APIListReply reply;
    for (auto &client : clients_) {
        ListReply client_reply;
        client_reply.api_version = client.get_api_version();
        client_reply.name = client.get_name();
        client_reply.idle = client.get_idle();
        reply.add_reply(client_reply);
        spdlog::info("ADDED CLIENT");
    }
    reply.send(server_, info.get_connection_id());
    return true;
}

bool ServerProcessor::handle_api_auth(Transfer &info, const APIAuth &api) {
    // Accept everyone for now
    APIAuthReply reply;
    reply.set_allowed(true);
    reply.send(server_, info.get_connection_id());
    spdlog::info("Authenticated ID {}", info.get_connection_id());

    // Add new client
    Client client;
    client.set_api_version(api.get_api_version());
    client.set_id(info.get_connection_id());
    client.set_name(api.get_name());

    // Add to client list
    clients_.push_back(client);

    // Return OK so reply is sent
    return true;
}