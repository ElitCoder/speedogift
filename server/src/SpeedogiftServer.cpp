#include <ncnet/Server.h>
#include <ncconf/Log.h>

int main() {
    Server server;
    if (!server.start("", 12001)) {
        Log(ERR) << "Failed to start server, exiting";
        return -1;
    }

    // Enter waiting loop
    while (true) {
        auto info = server.get();
        // Process data
    }

    // Probably won't get here
    server.stop();
    return 0;
}