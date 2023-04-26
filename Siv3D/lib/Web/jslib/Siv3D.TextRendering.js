mergeInto(LibraryManager.library, {
    $siv3dTextRenderingCanvas: null,
    $siv3dTextRenderingCanvasContext: null,

    siv3dRenderText: function(utf32CodePoint, data) {
        if (!siv3dTextRenderingCanvas) {
            siv3dTextRenderingCanvas = document.createElement('canvas');
            siv3dTextRenderingCanvasContext = siv3dTextRenderingCanvas.getContext("2d");
        }

        const text = String.fromCodePoint(utf32CodePoint);
        const fontSize = 64;
        const fontName = "sans-serif";

        siv3dTextRenderingCanvasContext.fillStyle = "0x0";
        siv3dTextRenderingCanvasContext.font = `${fontSize}px '${fontName}'`;
        siv3dTextRenderingCanvasContext.textBaseline = "bottom";

        const textMetrix = siv3dTextRenderingCanvasContext.measureText(text);
        const fontWidth = Math.ceil(Math.abs(textMetrix.actualBoundingBoxLeft) + Math.abs(textMetrix.actualBoundingBoxRight)) || 1;
        const fontHeight = Math.ceil(Math.abs(textMetrix.actualBoundingBoxAscent) + Math.abs(textMetrix.actualBoundingBoxDescent)) || 1;
        const fontXAdvance = textMetrix.width;

        siv3dTextRenderingCanvasContext.clearRect(0, 0, siv3dTextRenderingCanvas.width, siv3dTextRenderingCanvas.height);
        siv3dTextRenderingCanvasContext.fillText(text, Math.abs(textMetrix.actualBoundingBoxLeft), fontHeight);

        const textBitmap = siv3dTextRenderingCanvasContext.getImageData(0, 0, fontWidth, fontHeight).data;
        const dataBuffer = Module["_malloc"](textBitmap.length);

        HEAPU8.set(textBitmap, dataBuffer);

        HEAPU32[data>>2] = utf32CodePoint; data += 4;                       // glyphIndex
        HEAP32[data>>2] = dataBuffer; data += 4;                            // buffer
        HEAP16[data>>1] = textMetrix.actualBoundingBoxLeft; data += 2;      // left
        HEAP16[data>>1] = fontHeight; data += 2;                            // top
        HEAP16[data>>1] = fontWidth; data += 2;                             // width
        HEAP16[data>>1] = fontHeight; data += 2;                            // height
        HEAP16[data>>1] = fontSize; data += 2;                              // ascender
        HEAP16[data>>1] = 0; data += 2;                                     // descender
        data += 4;                                                          // padding
        HEAPF64[data>>3] = fontXAdvance; data += 8;                         // xAdvance
        HEAPF64[data>>3] = 0; data += 8;                                    // yAdvance
    },
    siv3dRenderText__sig: "vii",
    siv3dRenderText__proxy: "sync",
    siv3dRenderText__deps: [ "$siv3dTextRenderingCanvas", "$siv3dTextRenderingCanvasContext" ],
});
