#include "ClientProcessor.h"
#include "APIAuth.h"
#include "APIAuthReply.h"
#include "APIList.h"
#include "APIListReply.h"

#include <spdlog/spdlog.h>

using namespace std;

bool ClientProcessor::handle_api_auth_reply(const APIAuthReply &reply) {
    if (reply.get_allowed()) {
        spdlog::info("Authenticated at server");
        return true; // OK
    } else {
        spdlog::error("Not accepted at server (error {}), exiting", reply.get_error());
        return false;
    }
}

bool ClientProcessor::handle_api_list_reply(const APIListReply &reply) {
    spdlog::info("List reply");
    auto clients = reply.get_replies();
    for (auto &client : clients) {
        spdlog::info("*** Clients connected ***");
        spdlog::info("(Name:{}) (API version:{}) (Idle:{})", client.name, client.api_version, client.idle ? "YES" : "NO");
    }
    return true;
}

bool ClientProcessor::process_options(cxxopts::ParseResult &options) {
    // Authenticate
    APIAuth auth;
    APIAuthReply auth_reply;
    auth.set_name("test");
    spdlog::info("Authenticating as {}", auth.get_name());
    if (!auth.send_and_process_reply(client_, *this, auth_reply)) {
        return false;
    }

    // Options
    if (options.count("l") > 0) {
        // List connected clients
        APIList list;
        APIListReply list_reply;
        list.send_and_process_reply(client_, *this, list_reply);
    }

    if (options.count("connect") == 0) {
        if (options.count("no-monitor") > 0) {
            spdlog::error("No receiver specified, exiting");
        } else {
            spdlog::info("No receiver specified, going into monitor mode");
        }
        return true;
    }

    return true;
}