#include "APISend.h"

void APISend::load(Packet &packet) {
    to_name_ = packet.getString();
    auto size = packet.getInt();
    for (int i = 0; i < size; i++) {
        Send file;
        file.path = packet.getString();
        file.name = packet.getString();
        file.size = packet.getInt();
        file.hash = packet.getString();
        add_file(file);
    }
}

void APISend::finish() {
    packet_.addString(to_name_);
    packet_.addInt(files_.size());
    for (auto &file : files_) {
        packet_.addString(file.path);
        packet_.addString(file.name);
        packet_.addInt(file.size);
        packet_.addString(file.hash);
    }
}