#include "APIAuthReply.h"

void APIAuthReply::set_allowed(bool allowed) {
    allowed_ = allowed;
}

void APIAuthReply::finish() {
    packet_.addHeader(HEADER_AUTH_REPLY);
    packet_.addInt(allowed_);
    packet_.finalize();
}