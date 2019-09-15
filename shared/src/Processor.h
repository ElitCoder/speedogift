#pragma once

#define SERVER_API_DEFAULT { (void)api; (void)info; return true; }
#define CLIENT_API_DEFAULT { (void)api; return true; }

class Information;
class APIAuth;
class APIAuthReply;
class APIList;
class APIListReply;

// Interface to be implemented by both server and client to describe how to
// handle different API requests
class Processor {
public:
    // Implement all API handles no-op and override them if they are used

    // Server callbacks
    virtual bool handle_api_auth(Information &info, const APIAuth &api)     SERVER_API_DEFAULT
    virtual bool handle_api_list(Information &info, const APIList &api)     SERVER_API_DEFAULT

    // Client callbacks
    virtual bool handle_api_auth_reply(const APIAuthReply &api)             CLIENT_API_DEFAULT
    virtual bool handle_api_list_reply(const APIListReply &api)             CLIENT_API_DEFAULT
};