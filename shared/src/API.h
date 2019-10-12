#pragma once

#include <ncnet/Network.h>
#include <ncnet/Transfer.h>
#include <ncnet/Packet.h>

class Processor;
class API;

using PeerAPIPair = std::pair<size_t, std::shared_ptr<API>>;

enum Header {
    HEADER_AUTH = 0,
    HEADER_AUTH_REPLY,
    HEADER_AUTH_CHANGE,
    HEADER_AUTH_CHANGE_REPLY,
    HEADER_LIST,
    HEADER_LIST_REPLY,
    HEADER_SEND,
    HEADER_SEND_REPLY,
    HEADER_SEND_DATA,
    HEADER_SEND_DATA_REPLY
};

enum ErrorCode {
    NO_ERROR = 0,
    OUTDATED_API_VERSION,
    NAME_ALREADY_TAKEN
};

enum ClientMode {
    CLIENT_PROCESSING = 0,
    CLIENT_MONITOR
};

// API version
const std::string API_VERSION = "0.0.1";

class API {
public:
    virtual void send(ncnet::Network &network, size_t peer = 0) final;
    virtual PeerAPIPair wait_for_reply(ncnet::Network &network, Processor &proc, API &type, size_t peer = 0) final;
    // Send + wait + process
    virtual bool send_and_process_reply(ncnet::Network &network, Processor &proc, API &type, size_t peer = 0) final;

    // API factory from packet
    static std::shared_ptr<API> make(ncnet::Transfer &info);
    static bool process_api(ncnet::Transfer &info, Processor &proc, std::shared_ptr<API> api);
    static bool make_and_process(ncnet::Transfer &info, Processor &proc);

    // API is of type
    virtual bool is_api(API &api) final;

protected:
    ncnet::Packet packet_; // Final packet
    bool finished_ = false; // If the API has been packed before sending
    int header_ = -1; // enum Header

private:
    // Force implement by sub-classes
    virtual void load(ncnet::Packet &packet) = 0; // Load into API form
    virtual bool process(ncnet::Transfer &info, Processor &proc) = 0; // Call corresponding API processor
    virtual void finish() = 0; // Called automatically before sending
};