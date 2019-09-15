#include "ClientProcessor.h"
#include "APIAuth.h"
#include "APIAuthReply.h"

#include <spdlog/spdlog.h>

using namespace std;

void ClientProcessor::wait_for_api(API &api) {
    while (true) {
        auto info = client_.get();
        auto created_api = API::make(info);
        if (created_api->is_api(api)) {
            // Found our reply
             api = *created_api;
             break;
        } else {
            // Process until found
            API::process(info, *this, created_api);
        }
    }
}

void ClientProcessor::process_options(cxxopts::ParseResult &options) {
    // Authenticate
    APIAuth api_auth;
    api_auth.set_name("test");
    spdlog::info("Authenticating as {}", api_auth.get_name());
    api_auth.send(client_);

    APIAuthReply reply;
    wait_for_api(reply);
    if (reply.get_allowed()) {
        spdlog::info("Authenticated at server");
    } else {
        spdlog::error("Not accepted at server, exiting");
        return;
    }

    // Options
    if (options.count("connect") == 0) {
        if (options.count("no-monitor") == 0) {
            spdlog::error("No receiver specified, exiting");
        } else {
            spdlog::info("No receiver specified, going into monitor mode");
        }
        return;
    }
}