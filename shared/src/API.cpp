#include "API.h"

void API::send(Network &network, size_t peer) {
    if (!finished_) {
        finish(); // Pack API call
        packet_.finalize(); // Pack data into buffers
        finished_ = true;
    }

    network.send(packet_, peer);
}