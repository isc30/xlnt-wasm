#pragma once

#include <emscripten.h>
#include <emscripten/bind.h>

#include <xlnt/xlnt.hpp>

EMSCRIPTEN_BINDINGS(worksheet)
{
    emscripten::class_<xlnt::worksheet>("worksheet")

        .function("using_cell", emscripten::optional_override([](
            xlnt::worksheet& worksheet,
            uint32_t col,
            uint32_t row,
            emscripten::val action)
        {
            xlnt::cell cell = worksheet.cell(col, row);
            auto* cell_ptr = &cell;

            return action(cell_ptr);
        }))

        .function("using_cell", emscripten::optional_override([](
            xlnt::worksheet& worksheet,
            const std::string& cell_reference,
            emscripten::val action)
        {
            xlnt::cell cell = worksheet.cell(cell_reference);
            auto* cell_ptr = &cell;

            return action(cell_ptr);
        }))

        .function("merge_cells",
            static_cast<void(xlnt::worksheet::*)(const std::string&)>(
                &xlnt::worksheet::merge_cells))

        .function("merge_cells", emscripten::optional_override([](
            xlnt::worksheet& worksheet,
            const std::string& cell0,
            const std::string& cell1)
        {
            worksheet.merge_cells(xlnt::range_reference{ cell0, cell1 });
        }))

        .function("merge_cells", emscripten::optional_override([](
            xlnt::worksheet& worksheet,
            std::uint32_t startCol, std::uint32_t startRow,
            std::uint32_t endCol, std::uint32_t endRow)
        {
            worksheet.merge_cells(xlnt::range_reference{ startCol, startRow, endCol, endRow });
        }))

        /*.function("freeze_panes",
            static_cast<void(xlnt::worksheet::*)(xlnt::cell)>(
                &xlnt::worksheet::freeze_panes))*/
    ;
}
