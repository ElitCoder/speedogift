#include "APIAuthChangeReply.h"

using namespace ncnet;

void APIAuthChangeReply::load(Packet &packet) {
    packet >> allowed_;
    if (!allowed_) {
        int error;
        packet >> error;
        error_ = (ErrorCode)error;
    }
}

void APIAuthChangeReply::finish() {
    packet_ << allowed_;
    if (!allowed_) {
        packet_ << (int)error_;
    }
}