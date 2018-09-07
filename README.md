JS-WebAssembly port of [XLNT library](https://github.com/tfussell/xlnt)

# Explanation

I'm writing a series of posts in my blog about this topic:

- why does this project exist?
- small proof of concepts
- how to create proper bindings
- etc etc

You can take a look here: [Excel-ent experiment with WebAssembly](https://blog.codeisc.com/2018/08/28/xlnt-wasm-intro.html)

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
