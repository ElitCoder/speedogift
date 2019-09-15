#include "ServerProcessor.h"
#include "APIAuth.h"
#include "APIAuthReply.h"

#include <ncnet/Information.h>
#include <spdlog/spdlog.h>

#include <algorithm>

using namespace std;

bool ServerProcessor::handle_api_auth(Information &info, const APIAuth &api) {
    // Accept everyone for now
    APIAuthReply reply;
    reply.set_allowed(true);
    reply.send(server_, info.getId());
    spdlog::info("Authenticated ID {}", info.getId());

    // Add new client
    Client client;
    client.set_api_version(api.get_api_version());
    client.set_id(info.getId());
    client.set_name(api.get_name());

    // Add to client list
    clients_.push_back(client);

    // Return OK so reply is sent
    return true;
}