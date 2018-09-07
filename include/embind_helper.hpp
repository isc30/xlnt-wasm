#pragma once

#include <iostream>
#include <emscripten.h>
#include <emscripten/val.h>

struct JsType
{
    static constexpr const char* Object = "object";
    static constexpr const char* Number = "number";
    static constexpr const char* String = "string";
    static constexpr const char* Bool = "boolean";
};

std::string typeOf(emscripten::val value);
void throwError(const std::string& msg);
void throwTypeError(const std::string& msg);
