#pragma once

#include "API.h"

class APIFactory {
public:
    struct ListReply {
        std::string version;
        std::string name;
        bool active;
    };

    struct Send {
        std::string path;
        size_t size;
        std::string hash;
    };

    static API auth(const std::string &name);
    static API auth_reply(APIStatusCode code);
    static API list();
    static API list_reply(const std::vector<ListReply> &clients);
    static API send(const std::string &from, const std::string &to, const std::vector<Send> &files);
    static API send_reply(const std::string &from, const std::string &to, APIStatusCode code);
    static API change_active(bool active);
    static API change_active_reply(APIStatusCode code);
};