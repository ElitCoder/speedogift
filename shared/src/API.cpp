#include "API.h"
#include "APIAuth.h"
#include "APIAuthReply.h"
#include "APIList.h"
#include "APIListReply.h"

#include <ncnet/Network.h>
#include <spdlog/spdlog.h>

using namespace std;

void API::send(Network &network, size_t peer) {
    if (!finished_) {
        // Add header
        packet_.addHeader(header_);
        finish(); // Pack API call
        packet_.finalize(); // Pack data into buffers
        finished_ = true;
    }

    network.send(packet_, peer);
}

// This will probably only be a client function
PeerAPIPair API::wait_for_reply(Network &network, Processor &proc, API &type, size_t peer) {
    // Wait forever for response
    while (true) {
        auto info = network.get();
        auto api = make(info);
        if (api->is_api(type) && info.getId() == peer) {
            // Replied
            return { info.getId(), api };
        } else {
            api->process(info, proc);
        }
    }
}

bool API::send_and_process_reply(Network &network, Processor &proc, API &reply, size_t peer) {
    send(network, peer);
    auto peer_reply = wait_for_reply(network, proc, reply, peer);
    auto api_ref = peer_reply.second;
    Information info;
    info.setId(peer_reply.first);
    return api_ref->process(info, proc);
}

shared_ptr<API> API::make(Information &info) {
    shared_ptr<API> api = nullptr;
    auto &packet = info.getPacket();
    auto header = packet.getHeader();

    switch (header) {
        case HEADER_AUTH: api = make_shared<APIAuth>();
            break;
        case HEADER_AUTH_REPLY: api = make_shared<APIAuthReply>();
            break;
        case HEADER_LIST: api = make_shared<APIList>();
            break;
        case HEADER_LIST_REPLY: api = make_shared<APIListReply>();
            break;
    }

    if (api == nullptr) {
        spdlog::warn("Unknown API header 0x{0:b}", header);
        return nullptr;
    }

    api->load(packet);
    return api;
}

bool API::process_api(Information &info, Processor &proc, shared_ptr<API> api) {
    if (api == nullptr) {
        // Probably unknown API header, disconnect client
        return false;
    }

    return api->process(info, proc);
}

bool API::make_and_process(Information &info, Processor &proc) {
    return process_api(info, proc, make(info));
}

bool API::is_api(API &api) {
    return api.header_ == header_;
}