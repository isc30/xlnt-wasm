#pragma once

#include <emscripten.h>
#include <emscripten/bind.h>

#include <xlnt/xlnt.hpp>

void download(xlnt::workbook& workbook, const std::string& fileName)
{
    workbook.save(fileName);

    EM_ASM_({
        fileName = Pointer_stringify($0);
        fileContent = [FS.readFile(fileName)];

        mime = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
        file = new Blob(fileContent, { type: mime });
        downloadUrl = URL.createObjectURL(file);

        // Download the Blob
        anchor = document.createElement('a');
        anchor.download = fileName;
        anchor.href = downloadUrl;
        anchor.dataset.downloadurl = mime + ":" + fileName + ":" + downloadUrl;
        document.body.appendChild(anchor);
        anchor.click();
        document.body.removeChild(anchor);
    }, fileName.c_str());
}

EMSCRIPTEN_BINDINGS(workbook)
{
    emscripten::class_<xlnt::workbook>("workbook")

        .class_function("empty", &xlnt::workbook::empty)

        .constructor<>()

        // create_sheet
        // create_sheet(index)
        // copy_sheet(sheet)
        // copy_sheet(sheet, index)

        .function("active_sheet",
            &xlnt::workbook::active_sheet)

        // sheet(index)

        // remove_sheet(sheet)
        // remove_sheet(index)

        // apply_to_cells
        // sheet_count

        // has_title
        // get_title
        // set_title

        .function("save",
            static_cast<void(xlnt::workbook::*)(const std::string&) const>(
                &xlnt::workbook::save))

        .function("download",
            &download)
    ;
}
