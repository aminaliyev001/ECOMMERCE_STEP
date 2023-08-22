#pragma once
namespace Errors {
class Exception : public exception {
public:
    string message;
    Exception() = delete;
    Exception(string text, string line,  string source, string time) :
    message("Text: " + text + ", Line: " + line + ", Source: " + source + ", Time: " + time) {}

    const char * what() const noexcept override {
        return message.c_str();
    }
};
};
