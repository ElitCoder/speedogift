#include "API.h"
#include "APIAuth.h"
#include "APIAuthReply.h"

#include <ncnet/Network.h>
#include <ncnet/Log.h>

using namespace std;

void API::send(Network &network, size_t peer) {
    if (!finished_) {
        finish(); // Pack API call
        packet_.finalize(); // Pack data into buffers
        finished_ = true;
    }

    network.send(packet_, peer);
}

bool API::make_and_process(Information &info, Processor &proc) {
    shared_ptr<API> api = nullptr;
    auto &packet = info.getPacket();
    auto header = packet.getHeader();

    switch (header) {
        case HEADER_AUTH: api = make_shared<APIAuth>();
            break;
        case HEADER_AUTH_REPLY: api = make_shared<APIAuthReply>();
            break;
    }

    if (api == nullptr) {
        Log(WARNING) << "Unknown API " << header << " received\n";
        return false;
    }

    api->load(packet);
    return api->process(info, proc);
}