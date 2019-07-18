#pragma once

#include <ncnet/Packet.h>
#include <ncnet/Network.h>

enum ClientType {
    CLIENT_TYPE_MONITOR,
    CLIENT_TYPE_NORMAL
};

enum Header {
    HEADER_AUTH,
    HEADER_AUTH_REPLY
};

class API {
public:
    virtual void finish() = 0; // Force implement by sub-classes
    virtual void send(Network &network, size_t peer = 0) final;

protected:
    Packet packet_; // Final packet
};