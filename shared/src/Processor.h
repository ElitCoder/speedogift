#pragma once

#define SERVER_API_DEFAULT { (void)api; (void)info; return true; }
#define CLIENT_API_DEFAULT { (void)api; return true; }

class Information;
class APIAuth;
class APIAuthReply;
class APIAuthChange;
class APIAuthChangeReply;
class APIList;
class APIListReply;
class APISend;
class APISendReply;
class APISendData;
class APISendDataReply;

// Interface to be implemented by both server and client to describe how to
// handle different API requests
class Processor {
public:
    // Implement all API handles no-op and override them if they are used

    // Server callbacks
    virtual bool handle_api_auth(Information &info, const APIAuth &api)                     SERVER_API_DEFAULT
    virtual bool handle_api_auth_change(Information &info, const APIAuthChange &api)        SERVER_API_DEFAULT
    virtual bool handle_api_list(Information &info, const APIList &api)                     SERVER_API_DEFAULT
    virtual bool handle_api_send(Information &info, const APISend &api)                     SERVER_API_DEFAULT

    // Client callbacks
    virtual bool handle_api_auth_reply(const APIAuthReply &api)                             CLIENT_API_DEFAULT
    virtual bool handle_api_auth_change_reply(const APIAuthChangeReply &api)                CLIENT_API_DEFAULT
    virtual bool handle_api_list_reply(const APIListReply &api)                             CLIENT_API_DEFAULT
    virtual bool handle_api_send_reply(const APISendReply &api)                             CLIENT_API_DEFAULT

    // Both
    virtual bool handle_api_send_data(Information &info, const APISendData &api)            SERVER_API_DEFAULT
    virtual bool handle_api_send_data_reply(Information &info, const APISendDataReply &api) SERVER_API_DEFAULT
};