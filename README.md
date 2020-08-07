WebAssembly bindings for the [XLNT library](https://github.com/tfussell/xlnt)

## NPM

https://www.npmjs.com/package/xlnt

## Blog posts

I'm writing a series of posts in my blog about porting C++ to WASM.<br/>
You can take a look here: [Excel-ent experiment with WebAssembly](https://blog.codeisc.com/2018/08/28/xlnt-wasm-intro.html)

## Demo
[Simple test and proof of concept in JavaScript that exports a HTML table to excel (with rowspan and colspan)](http://isc30.github.io/xlnt-wasm/demo.html)

```html
<script src="./xlnt.js"></script>
<script>
    load_xlnt().then(function(xlnt)
    {
        book = new xlnt.workbook();
        sheet = book.active_sheet();

        sheet.using_cell("B2", c => c.set_value("asd"));

        book.download("demo.xlsx");
        
        sheet.delete();
        book.delete();
    });
</script>
```
