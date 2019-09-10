#include "APIAuth.h"

#include <ncnet/Client.h>
#include <ncnet/Server.h>
#include <ncconf/Log.h>

#include <thread>
#include <random>
#include <chrono>
#include <atomic>

using namespace std;

static atomic<bool> g_stop_threads;

void run_server_thread(Server &server) {
    while (true) {
        auto info = server.get();
        if (g_stop_threads.load()) {
            break;
        }
    }
}

void run_monitor_client_thread(Client &client) {
    // Auth
    APIAuth auth;
    auth.set_client_type(CLIENT_TYPE_MONITOR);
    auth.set_client_name("test");
    auth.send(client);

    while (true) {
        auto info = client.get();
        if (g_stop_threads.load()) {
            break;
        }
    }
}

int get_random_port() {
    random_device device;
    mt19937 mt(device());
    uniform_int_distribution<int> dist(13000, 14000);
    return dist(mt);
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    // Three things to do here
    // 1. Process possible parameters
    // 2. Start server thread for direct connections
    // 3. Run in monitor mode

    g_stop_threads.store(false);

    // Start server thread
    Server server;
    while (!server.start("", get_random_port())) {
        // Retry with different port
    }
    thread server_thread = thread(run_server_thread, ref(server));
    Log(DEBUG) << "Started server thread at port " << server.at_port();

    // Monitor mode
    Client monitor_client;
    while (!monitor_client.start("localhost", 12001)) {
        Log(WARN) << "Could not connect, retrying in 1 second\n";
        // Sleep to not spam connection calls
        using namespace chrono_literals;
        this_thread::sleep_for(1s);
    }
    thread monitor_client_thread = thread(run_monitor_client_thread, ref(monitor_client));
    Log(DEBUG) << "Started client monitor thread";

    // Finally process command arguments

    // When we're done processing command arguments, keep monitor alive until
    // there's a SIGABRT
    while (true) {
        using namespace chrono_literals;
        this_thread::sleep_for(100ms);
    }

    // Exiting
    g_stop_threads.store(true);
    server.stop();
    monitor_client.stop();
    server_thread.join();
    monitor_client_thread.join();

    return 0;
}