#include "API.h"

#include "spdlog/spdlog.h"

using namespace std;
using namespace ncnet;

Packet API::send_get_reply(Client &client) {
    client.send_packet(packet_);
    // Wait for reply
    while (true) {
        auto transfer = client.get_packet();
        if (transfer.get_is_exit()) {
            throw runtime_error("Disconnected from server");
        }

        // Check matching header
        auto header = transfer.get_packet().read_byte();
        if (header != reply_header_) {
            spdlog::warn("Got unwanted header {} while waiting for {}, ignoring", header, reply_header_);
            continue;
        }

        // Correct reply
        return transfer.get_packet();
    }
}