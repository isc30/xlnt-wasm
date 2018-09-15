#pragma once

#include <emscripten.h>
#include <emscripten/bind.h>

#include <xlnt/xlnt.hpp>
#include <variant>

#include "../embind_helper.hpp"

EMSCRIPTEN_BINDINGS(cell)
{
    emscripten::class_<xlnt::cell>("cell")

        .function("has_value",
            &xlnt::cell::has_value)

        .function("get_value_str",
            &xlnt::cell::to_string)

        .function("get_value_bool",
            &xlnt::cell::value<bool>)

        .function("get_value_number",
            &xlnt::cell::value<double>)

        .function("get_value", emscripten::optional_override([](
            xlnt::cell& cell)
        {
            switch (cell.data_type())
            {                
                case xlnt::cell_type::boolean:
                    return emscripten::val(cell.value<bool>());

                case xlnt::cell_type::number:
                    return emscripten::val(cell.value<double>());
                
                case xlnt::cell_type::inline_string:
                case xlnt::cell_type::shared_string:
                    return emscripten::val(cell.value<std::string>());

                default:
                    return emscripten::val::undefined();
            }
        }))

        .function("set_value", emscripten::optional_override([](
            xlnt::cell& cell,
            emscripten::val value)
        {
            auto type = typeOf(value);

            if (type == JsType::Number)
            {
                return cell.value(value.as<double>());
            }
            else if (type == JsType::String)
            {
                return cell.value(value.as<std::string>());
            }
            else if (type == JsType::Bool)
            {
                return cell.value(value.as<bool>());
            }
            else if (value.isNull() || value.isUndefined())
            {
                return cell.value(std::nullptr_t{});
            }

            throwTypeError("Invalid type for cell content: " + type);
        }))

        .function("clear_value",
            &xlnt::cell::clear_value)

        .function("column", emscripten::optional_override([](
            xlnt::cell& cell)
        {
            return static_cast<uint32_t>(cell.column().index);
        }))

        .function("row", emscripten::optional_override([](
            xlnt::cell& cell)
        {
            return static_cast<uint32_t>(cell.row());
        }))

        .function("has_hyperlink",
            static_cast<bool(xlnt::cell::*)() const>(&xlnt::cell::has_hyperlink))

        .function("set_hyperlink", emscripten::optional_override([](
            xlnt::cell& cell,
            const std::string& url)
        {
            cell.hyperlink(url);
        }))

        .function("set_hyperlink", emscripten::optional_override([](
            xlnt::cell& cell,
            const std::string& url,
            const std::string& display)
        {
            cell.hyperlink(url, display);
        }))

        // set_format
        // clear_format

        .function("get_formula",
            static_cast<std::string(xlnt::cell::*)() const>(
                &xlnt::cell::formula))

        .function("set_formula",
            static_cast<void(xlnt::cell::*)(const std::string&)>(
                &xlnt::cell::formula))

        .function("clear_formula",
            &xlnt::cell::clear_formula)
    ;
}
