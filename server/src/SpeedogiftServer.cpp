#include "ProcessAPI.h"
#include "ServerProcessor.h"

#include <ncnet/Server.h>
#include <ncconf/Log.h>

int main() {
    Server server;
    if (!server.start("", 12001)) {
        Log(ERR) << "Failed to start server, exiting";
        return -1;
    }

    // Enter waiting loop
    ServerProcessor processor(server);
    while (true) {
        auto info = server.get();
        // Process data
        auto disconnect = !ProcessAPI::match_api(info, processor);
        if (disconnect) {
            // TODO: Remove client
        }
    }

    // Probably won't get here
    server.stop();
    return 0;
}