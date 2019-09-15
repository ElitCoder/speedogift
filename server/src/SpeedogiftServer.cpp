#include "ServerProcessor.h"

#include <ncnet/Server.h>
#include <spdlog/spdlog.h>

int main() {
    Server server;
    if (!server.start("", 12001)) {
        spdlog::error("Failed to start server, exiting");
        return -1;
    }

    // Enter waiting loop
    ServerProcessor processor(server);
    while (true) {
        auto info = server.get();
        // Process data
        // Disconnect if processing returns false
        auto disconnect = !API::make_and_process(info, processor);
        if (disconnect) {
            // TODO: Remove client
        }
    }

    // Probably won't get here
    server.stop();
    return 0;
}