#pragma once

#define API_DEFAULT { (void)api; (void)info; return true; }

class Information;
class APIAuth;
class APIAuthReply;

// Interface to be implemented by both server and client to describe how to
// handle different API requests
class Processor {
public:
    // Implement all API handles no-op and override them if they are used
    virtual bool handle_api_auth(Information &info, const APIAuth &api)                    API_DEFAULT
    virtual bool handle_api_auth_reply(Information &info, const APIAuthReply &api)         API_DEFAULT
};