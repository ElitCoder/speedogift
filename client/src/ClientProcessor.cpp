#include "ClientProcessor.h"
#include "APIAuth.h"
#include "APIAuthReply.h"

#include <spdlog/spdlog.h>

using namespace std;

void ClientProcessor::process_options(cxxopts::ParseResult &options) {
    // Authenticate
    APIAuth api_auth;
    api_auth.set_name("test");
    spdlog::info("Authenticating as {}", api_auth.get_name());

    APIAuthReply reply;
    api_auth.send_and_wait_for_reply(client_, *this, reply);
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