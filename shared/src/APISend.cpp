#include "APISend.h"

using namespace ncnet;

void APISend::load(Packet &packet) {
    packet >> to_name_;
    size_t size;
    packet >> size;
    for (size_t i = 0; i < size; i++) {
        Send file;
        packet >> file.path;
        packet >> file.name;
        packet >> file.size;
        packet >> file.hash;
        add_file(file);
    }
}

void APISend::finish() {
    packet_ << to_name_ << files_.size();
    for (auto &file : files_) {
        packet_ << file.path << file.name << file.size << file.hash;
    }
}