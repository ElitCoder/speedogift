#pragma once

#include "Boilerplate.h"

#include <ncnet/Client.h>

constexpr auto API_VERSION = "0.0.2";

enum APIHeader {
    API_HEADER_NONE,
    API_HEADER_AUTH,
    API_HEADER_AUTH_REPLY,
    API_HEADER_LIST,
    API_HEADER_LIST_REPLY,
    API_HEADER_SEND,
    API_HEADER_SEND_REPLY,
    API_HEADER_CHANGE_ACTIVE,
    API_HEADER_CHANGE_ACTIVE_REPLY
};

enum APIStatusCode {
    API_STATUS_CODE_OK,
    API_STATUS_CODE_NAME_ALREADY_TAKEN,
    API_STATUS_CODE_INVALID_REQUEST,
    API_STATUS_CODE_NOT_CONNECTED,
    API_STATUS_CODE_ALREADY_ACTIVE
};

class API {
public:
    SET_GET_MACRO(packet, ncnet::Packet &)
    SET_GET_MACRO(reply_header, APIHeader)

    ncnet::Packet send_get_reply(ncnet::Client &client);

private:
    ncnet::Packet packet_;
    APIHeader reply_header_;
};