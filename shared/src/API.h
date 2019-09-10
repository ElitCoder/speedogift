#pragma once

#include <ncnet/Packet.h>

class Network;
class Processor;
class Information;

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
    virtual void send(Network &network, size_t peer = 0) final;

    // API factory from packet
    static bool make_and_process(Information &info, Processor &proc);

protected:
    Packet packet_; // Final packet
    bool finished_ = false; // If the API has been packed before sending

private:
    // Force implement by sub-classes
    virtual void load(Packet &packet) = 0; // Load into API form
    virtual bool process(Information &info, Processor &proc) = 0; // Call corresponding API processor
    virtual void finish() = 0; // Called automatically before sending
};