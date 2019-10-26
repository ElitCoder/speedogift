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
    static API send(const std::string &name, const std::vector<Send> &files);
    static API send_reply(APIStatusCode code);
};