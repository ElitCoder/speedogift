#include "APISendReply.h"

using namespace ncnet;

void APISendReply::load(Packet &packet) {
    packet >> allowed_;
    if (!allowed_) {
        int error;
        packet >> error;
        error_ = (ErrorCode)error;
    }
}

void APISendReply::finish() {
    packet_ << allowed_;
    if (!allowed_) {
        packet_ << (int)error_;
    }
}