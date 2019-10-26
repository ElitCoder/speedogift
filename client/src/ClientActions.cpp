#include "ClientActions.h"
#include "APIFactory.h"

#include "spdlog/spdlog.h"

using namespace std;

static void print_status_code(APIStatusCode code) {
    switch (code) {
        case API_STATUS_CODE_ALREADY_ACTIVE:
            spdlog::error("Endpoint already active in another transaction");
            break;

        case API_STATUS_CODE_INVALID_REQUEST:
            spdlog::error("This client supplied invalid information, old version?");
            break;

        case API_STATUS_CODE_NAME_ALREADY_TAKEN:
            spdlog::error("Supplied name is already taken");
            break;

        case API_STATUS_CODE_NOT_CONNECTED:
            spdlog::error("Endpoint is not connected");
            break;
    }
}

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

void ClientActions::process_request(ncnet::Transfer &transfer) {
    auto header = transfer.get_packet().read_byte();
    switch (header) {
        case API_HEADER_SEND:
            handle_api_send(transfer);
            break;
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

    auto reply = APIFactory::send(name_, name, api_files).send_get_reply(client_);
    string from, to;
    int error;
    reply >> from >> to >> error;
    if (error != API_STATUS_CODE_OK) {
        print_status_code((APIStatusCode)error);
        throw runtime_error("Sending exception");
    }

    // All OK, let's start sending
    spdlog::info("Everything OK, starting sending to {}", to);
}

void ClientActions::set_active(bool active) {
    auto reply = APIFactory::change_active(active).send_get_reply(client_);
    int code;
    reply >> code;
    if (code != API_STATUS_CODE_OK) {
        print_status_code((APIStatusCode)code);
        throw runtime_error("Failed to change active status");
    }
    spdlog::debug("Changed active status to inactive, aka monitoring");
}

void ClientActions::handle_api_send(ncnet::Transfer &transfer) {
    string from, to;
    transfer.get_packet() >> from >> to;
    // TODO: Always accept until smarter solution
    spdlog::info("Accepting send request, preparing transfer");
    spdlog::debug("Sending from {} to {}", from, to);
    client_.send_packet(APIFactory::send_reply(from, to, API_STATUS_CODE_OK).get_packet());
}