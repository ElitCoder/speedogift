#include "ServerProcessor.h"

#include <ncnet/Information.h>
#include <ncnet/Log.h>
#include <algorithm>

bool ServerProcessor::handle_api_auth(Information &info, const APIAuth &api) {
    (void)api;
    Log(DEBUG) << "Got APIAuth from " << info.getId();
    return true;
}