#include "ClientActions.h"
#include "APIFactory.h"

#include "spdlog/spdlog.h"

using namespace std;

ClientActions::ClientActions(ncnet::Client &client, const string &name) : Actions(), client_(client), name_(name) {
    // Authenticate
    auto reply = APIFactory::auth(name_).send_get_reply(client_);
    int status_code;
    reply >> status_code;
    if (status_code == API_STATUS_CODE_OK) {
        spdlog::debug("Authenticated as '{}' at server", name_);
    } else if (status_code == API_STATUS_CODE_NAME_ALREADY_TAKEN) {
        spdlog::error("Authentication failed, name '{}' already taken", name_);
        throw runtime_error("Authentication failed");
    }
}

void ClientActions::list_clients() {
    auto reply = APIFactory::list().send_get_reply(client_);
    int nbr_clients;
    reply >> nbr_clients;
    for (int i = 0; i < nbr_clients; i++) {
        string version;
        string name;
        bool active;
        reply >> version >> name >> active;
        if (name == name_) {
            // Ignore myself as usual
            continue;
        }
        spdlog::info("Client '{}' API version '{}' active '{}'", name, version, active);
    }

    if (nbr_clients == 0) {
        spdlog::info("No clients are connected");
    }
}

void ClientActions::send_files(const string &name, const vector<string> &files) {
    spdlog::debug("Request to send to {}", name);
    if (name == name_) {
        spdlog::error("You can't send files to yourself");
        throw runtime_error("Sending exception");
    } else if (name == "") {
        spdlog::error("You need to specifiy an endpoint");
        throw runtime_error("Sending exception");
    }

    vector<APIFactory::Send> api_files;
    for (auto &file : files) {
        spdlog::info("Sending file '{}'", file);
        APIFactory::Send api_file;
        api_file.path = file;
        api_file.size = 0; // TODO
        api_file.hash = ""; // TOOD
    }

    auto reply = APIFactory::send(name, api_files).send_get_reply(client_);
}