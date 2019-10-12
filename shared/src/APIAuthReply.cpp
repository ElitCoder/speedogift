#include "APIAuthReply.h"
#include "Processor.h"

using namespace ncnet;

void APIAuthReply::load(Packet &packet) {
    packet >> allowed_;
    if (!allowed_) {
        int error;
        packet >> error;
        error_ = (ErrorCode)error;
    }
}

void APIAuthReply::finish() {
    packet_ << allowed_;
    if (!allowed_) {
        packet_ << (int)error_;
    }
}