#pragma once

#include <ncnet/Packet.h>

class Network;

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
    virtual void load(Packet &packet) = 0; // Load into API form
    virtual void send(Network &network, size_t peer = 0) final;

protected:
    Packet packet_; // Final packet
    bool finished_ = false; // If the API has been packed before sending

private:
    virtual void finish() = 0; // Force implement by sub-classes
};