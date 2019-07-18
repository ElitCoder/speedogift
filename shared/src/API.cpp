#include "API.h"

void API::send(Network &network, size_t peer) {
    network.send(packet_, peer);
}