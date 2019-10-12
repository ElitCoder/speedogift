#include "API.h"
#include "APIAuth.h"
#include "APIAuthReply.h"
#include "APIAuthChange.h"
#include "APIAuthChangeReply.h"
#include "APIList.h"
#include "APIListReply.h"
#include "APISend.h"
#include "APISendReply.h"
#include "APISendData.h"
#include "APISendDataReply.h"

#include <ncnet/Network.h>
#include <spdlog/spdlog.h>

using namespace ncnet;
using namespace std;

void API::send(Network &network, size_t peer) {
    if (!finished_) {
        // Add header
        packet_.add_byte(header_);
        finish(); // Pack API call
        finished_ = true;
    }

    network.send_packet(packet_, peer);
}

// This will probably only be a client function
PeerAPIPair API::wait_for_reply(Network &network, Processor &proc, API &type, size_t peer) {
    // Wait forever for response
    while (true) {
        auto info = network.get_packet();
        auto api = make(info);
        if (api->is_api(type) && info.get_connection_id() == peer) {
            // Replied
            return { info.get_connection_id(), api };
        } else {
            api->process(info, proc);
        }
    }
}

bool API::send_and_process_reply(Network &network, Processor &proc, API &reply, size_t peer) {
    send(network, peer);
    auto peer_reply = wait_for_reply(network, proc, reply, peer);
    auto api_ref = peer_reply.second;
    Transfer info;
    info.set_connection_id(peer_reply.first);
    return api_ref->process(info, proc);
}

shared_ptr<API> API::make(Transfer &info) {
    shared_ptr<API> api = nullptr;
    auto &packet = info.get_packet();
    auto header = packet.read_byte();

    switch (header) {
        case HEADER_AUTH: api = make_shared<APIAuth>();
            break;
        case HEADER_AUTH_REPLY: api = make_shared<APIAuthReply>();
            break;
        case HEADER_AUTH_CHANGE: api = make_shared<APIAuthChange>();
            break;
        case HEADER_AUTH_CHANGE_REPLY: api = make_shared<APIAuthChangeReply>();
            break;
        case HEADER_LIST: api = make_shared<APIList>();
            break;
        case HEADER_LIST_REPLY: api = make_shared<APIListReply>();
            break;
        case HEADER_SEND: api = make_shared<APISend>();
            break;
        case HEADER_SEND_REPLY: api = make_shared<APISendReply>();
            break;
        case HEADER_SEND_DATA: api = make_shared<APISendData>();
            break;
        case HEADER_SEND_DATA_REPLY: api = make_shared<APISendDataReply>();
            break;
    }

    if (api == nullptr) {
        spdlog::warn("Unknown API header 0x{0:b}", header);
        return nullptr;
    }

    api->load(packet);
    return api;
}

bool API::process_api(Transfer &info, Processor &proc, shared_ptr<API> api) {
    if (api == nullptr) {
        // Probably unknown API header, disconnect client
        return false;
    }

    return api->process(info, proc);
}

bool API::make_and_process(Transfer &info, Processor &proc) {
    return process_api(info, proc, make(info));
}

bool API::is_api(API &api) {
    return api.header_ == header_;
}