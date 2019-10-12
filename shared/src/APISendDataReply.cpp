#include "APISendDataReply.h"

using namespace ncnet;

void APISendDataReply::load(Packet &packet) {
    packet >> allowed_;
    if (!allowed_) {
        int error;
        packet >> error;
        error_ = (ErrorCode)error;
    }
}

void APISendDataReply::finish() {
    packet_ << allowed_;
    if (!allowed_) {
        packet_ << (int)error_;
    }
}