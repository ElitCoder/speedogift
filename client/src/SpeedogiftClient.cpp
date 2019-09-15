#include "ClientProcessor.h"

#include <cxxopts.hpp>
#include <spdlog/spdlog.h>
#include <ncnet/Client.h>
#include <ncnet/Server.h>

using namespace std;

int main(int argc, char **argv) {
    // Main things to do here
    // 1. Process options
    // 2. Setup local server for direct connections
    // 3. Connect to server and run in monitor mode after processing options

    // So we can either be a monitor client (default), or connect using send-to options and then go into monitor mode
    // Start of with processing options
    cxxopts::Options options("speedogift_client", "Client part of Speedogift - sending files simple, safe and fast");
    options.add_options()
        ("h,hostname", "Specify server hostname", cxxopts::value<string>())
        ("p,port", "Specify server port", cxxopts::value<int>())
        ("n,no-monitor", "Quit after processing and don't go into monitor mode")
        ("c,connect", "Connects to the client with the supplied name", cxxopts::value<string>())
        ("s,send", "Sends a (list of) file(s) to specified receiver", cxxopts::value<vector<string>>())
    ;

    // Options
    string hostname = "localhost";
    int port = 12000;

    try {
        auto result = options.parse(argc, argv);

        if (result.count("hostname") > 0) {
            hostname = result["hostname"].as<string>();
        }
        if (result.count("port") > 0) {
            port = result["port"].as<int>();
        }
    } catch (...) {
        // Failed, print help text
        cout << options.help();
        return -1;
    }

    // Client API processing
    ClientProcessor processor;

    // Connect to server
    spdlog::info("Connecting to specified server ({}:{})", hostname, port);
    Client client;
    if (!client.start(hostname, port)) {
        spdlog::critical("Could not connect to server, exiting");
        return -1;
    }

    // Spawn of client thread
    atomic<bool> stop_threads;
    auto client_thread = thread([&client, &stop_threads] () {
        while (true) {
            auto info = client.get();
            if (stop_threads.load()) {
                break;
            }
        }
    });

    stop_threads.store(true);
    client.stop();

    return 0;
}