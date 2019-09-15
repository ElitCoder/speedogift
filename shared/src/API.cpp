#include "API.h"
#include "APIAuth.h"
#include "APIAuthReply.h"

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
void API::send_and_wait_for_reply(Network &network, Processor &proc, API &reply, size_t peer) {
    send(network, peer);
    // Wait forever for response
    while (true) {
        auto info = network.get();
        auto api = make(info);
        spdlog::debug("Got answer");
        if (api->is_api(reply)) {
            // Replied
            spdlog::debug("Matching API, returning");
            reply = *api;
            break;
        } else {
            spdlog::debug("Processing API generally..");
            process(info, proc);
        }
    }
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
    }

    if (api == nullptr) {
        spdlog::warn("Unknown API header 0x{0:b}", header);
        return nullptr;
    }

    api->load(packet);
    return api;
}

bool API::process(Information &info, Processor &proc, shared_ptr<API> api) {
    return api->process(info, proc);
}

bool API::make_and_process(Information &info, Processor &proc) {
    return process(info, proc, make(info));
}

bool API::is_api(API &api) {
    spdlog::debug("Mine {} theirs {}", header_, api.header_);
    return api.header_ == header_;
}