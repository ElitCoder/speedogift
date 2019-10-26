#include "ClientActions.h"

#include <ncnet/Client.h>

#include "cxxopts/cxxopts.hpp"
#include "spdlog/spdlog.h"

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
        ("l,list", "List connected clients and status")
        ("m,my-name", "Specifies this client's name", cxxopts::value<string>())
    ;

    // Set debug level during development
    spdlog::set_level(spdlog::level::debug);

    // Options
    shared_ptr<cxxopts::ParseResult> results;
    try {
        results = make_shared<cxxopts::ParseResult>(options.parse(argc, argv));
    } catch (...) {
        // Failed, print help text
        cout << options.help();
        return -1;
    }

    // Parse options
    auto &result = *results;

    string hostname = "localhost";
    if (result.count("hostname") > 0) {
        hostname = result["hostname"].as<string>();
    }

    auto port = 12001;
    if (result.count("port") > 0) {
        port = result["port"].as<int>();
    }

    string connect_client = "";
    if (result.count("connect") > 0) {
        connect_client = result["connect"].as<string>();
    }

    auto list_clients = result.count("list") > 0;
    auto no_monitor = result.count("no-monitor") > 0;

    vector<string> files;
    if (result.count("send") > 0) {
        files = result["send"].as<vector<string>>();
    }

    string my_name = "test";
    if (result.count("my-name") > 0) {
        my_name = result["my-name"].as<string>();
    } else {
        spdlog::warn("Using client test name '{}'", my_name);
    }

    // Connect to server
    ncnet::Client client;
    spdlog::info("Connecting to specified server ({}:{})", hostname, port);
    if (!client.start(hostname, port)) {
        spdlog::critical("Could not connect to server, exiting");
        return -1;
    }

    // Actions
    ClientActions actions(client, my_name);

    // List
    if (list_clients) {
        // List clients implicitly means no monitor
        no_monitor = true;
        actions.list_clients();
    } else if (!files.empty()) {
        actions.send_files(connect_client, files);
    }

    // Continue unless no-monitor is set
    if (!no_monitor) {
        // Change active mode to inactive
        actions.set_active(false);
        // Loop requests
        client.run_transfer_loop([&actions] (auto &transfer) {
            actions.process_request(transfer);
        });
        // Lost connection
        spdlog::error("Connection to server lost, exiting");
    }

    // Quit
    client.stop();
}