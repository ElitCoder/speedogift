#include "ServerActions.h"

#include <ncnet/Server.h>

#include "spdlog/spdlog.h"

int main() {
    ncnet::Server server;
    auto port = 12001;
    if (!server.start("", port)) {
        spdlog::error("Failed to start server, exiting");
        return -1;
    }

    // Set debug level during development
    spdlog::set_level(spdlog::level::debug);

    // Main server context
    ServerActions actions(server);

    // Register disconnecting function
    server.set_disconnect_callback([&actions] (auto id) {
        actions.remove_client(id);
    });

    // Enter waiting loop
    server.run_transfer_loop([&actions] (auto &transfer) {
        actions.process_request(transfer);
    });

    // Probably won't get here
    server.stop();
}