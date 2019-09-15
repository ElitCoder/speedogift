#include "ServerProcessor.h"
#include "APIAuth.h"
#include "APIAuthReply.h"

#include <ncnet/Information.h>

#include <algorithm>

using namespace std;

ServerProcessor::ServerProcessor(Server &server) : server_(server) {}

bool ServerProcessor::client_is_valid(const APIAuth &api) {
#if 0
    // See if there's no client connected with the same name
    auto found = find_if(clients_.begin(), clients_.end(), [&api] (auto &client) {
        return client.has_name(api.get_client_name()) && client.has_type(api.get_client_type());
    });

    return found == clients_.end();
#endif
}

bool ServerProcessor::handle_api_auth(Information &info, const APIAuth &api) {
#if 0
    auto allowed = client_is_valid(api);

    if (allowed) {
        // Add client
        clients_.emplace_back(api, info.getId());
    }

    APIAuthReply reply;
    reply.set_allowed(allowed);
    reply.send(server_, info.getId());
    Log(DEBUG) << "Got APIAuth from " << info.getId() << " with name " << api.get_client_name() << endl;
#endif
    // Return OK so reply is sent
    return true;
}