#pragma once

#include <ncnet/Packet.h>

class Network;
class Processor;
class Information;

enum Header {
    HEADER_AUTH,
    HEADER_AUTH_REPLY
};

class API {
public:
    virtual void send(Network &network, size_t peer = 0) final;

    // API factory from packet
    static std::shared_ptr<API> make(Information &info);
    static bool process(Information &info, Processor &proc, std::shared_ptr<API> api);
    static bool make_and_process(Information &info, Processor &proc);

    // API is of type
    virtual bool is_api(API &api) final;

protected:
    Packet packet_; // Final packet
    bool finished_ = false; // If the API has been packed before sending
    int header_ = -1; // enum Header

private:
    // Force implement by sub-classes
    virtual void load(Packet &packet) = 0; // Load into API form
    virtual bool process(Information &info, Processor &proc) = 0; // Call corresponding API processor
    virtual void finish() = 0; // Called automatically before sending
};