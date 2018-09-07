JS-WebAssembly port of [XLNT library](https://github.com/tfussell/xlnt)

## Demo
[Simple test](http://codeisc.com/xlnt/)

```html
<script src="./xlnt.js"></script>
<script>
    load_xlnt().then(function(xlnt)
    {
        book = new xlnt.workbook();
        sheet = book.active_sheet();

        sheet.cell("B2").value_str("asd");

        book.download("demo.xlsx");
    });
</script>
```
