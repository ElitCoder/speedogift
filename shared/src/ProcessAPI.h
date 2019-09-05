#pragma once

class Information;
class Processor;

class ProcessAPI {
public:
    static bool match_api(Information &info, Processor& processor);
};