declare interface module_configuration
{
    locateFile(url: string): string;
}

declare interface xlnt
{
    workbook: workbook_constructor;
}

declare interface deletable
{
    delete();
}

declare class workbook implements deletable
{
    static empty(): workbook;

    constructor();
    delete();
    active_sheet(): worksheet;
    save(fileName: string): void;
    download(fileName: string): void;
}

declare interface worksheet extends deletable
{
    using_cell<T>(col: number, row: number, action: (c: cell) => T): T;
    using_cell<T>(cell_reference: string, action: (c: cell) => T): T;

    merge_cells(cell_range: string): void;
    merge_cells(cell_reference0: string, cell_reference1: string): void;
    merge_cells(startCol: number, startRow: number, endCol: number, endRow: number): void;
}

declare interface cell
{
    has_value(): boolean;
    get_value(): string;
    get_value_bool(): boolean;
    get_value_number(): number;
    set_value(value: number | string | boolean | null | undefined): void;
    clear_value(): void;

    column(): number;
    row(): number;

    has_hyperlink(): boolean;
    set_hyperlink(url: string): void;
    set_hyperlink(url: string, display: string): void;

    get_formula(): string;
    set_formula(formula: string): void;
    clear_formula(): void;
}

type workbook_constructor = new() => workbook;

declare function load_xlnt(x: module_configuration): PromiseLike<xlnt>;
