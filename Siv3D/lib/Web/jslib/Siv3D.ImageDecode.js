mergeInto(LibraryManager.library, {
    $siv3dDecodeCanvas: null,
    $siv3dDecodeCanvasContext: null,

    $siv3dDecodeImageFromFileImpl: function(wakeUp, src, size, data) {
        if (!siv3dDecodeCanvas) {
            siv3dDecodeCanvas = document.createElement('canvas');
            siv3dDecodeCanvasContext = siv3dDecodeCanvas.getContext("2d");
        }

        const imageData = new Uint8ClampedArray(HEAPU8.buffer, src, size);
        const imageBlob = new Blob([ imageData ]);
        const image = new Image();

        image.onload = function() {
            siv3dDecodeCanvas.width = image.width;
            siv3dDecodeCanvas.height = image.height;
            siv3dDecodeCanvasContext.drawImage(image, 0, 0);

            const decodedImageData = siv3dDecodeCanvasContext.getImageData(0, 0, image.width, image.height).data;
            const dataBuffer = Module["_malloc"](decodedImageData.length);

            HEAPU8.set(decodedImageData, dataBuffer);

            HEAPU32[(data>>2)+0] = dataBuffer;
            HEAPU32[(data>>2)+1] = decodedImageData.length;
            HEAPU32[(data>>2)+2] = image.width;
            HEAPU32[(data>>2)+3] = image.height;

            URL.revokeObjectURL(image.src);
            wakeUp();
        };
        image.onerror = function() {
            URL.revokeObjectURL(image.src);
            wakeUp();
        };
        image.src = URL.createObjectURL(imageBlob);
    },
    $siv3dDecodeImageFromFileImpl__deps: [ "$siv3dDecodeCanvas", "$siv3dDecodeCanvasContext" ],

#if ASYNCIFY
    siv3dDecodeImageFromFile: function(src, size, data) {
        return Asyncify.handleSleep(function (wakeUp) {
            siv3dDecodeImageFromFileImpl(wakeUp, src, size, data);
        });
    },
    siv3dDecodeImageFromFile__sig: "viii",
    siv3dDecodeImageFromFile__proxy: "sync",
    siv3dDecodeImageFromFile__deps: ["$siv3dDecodeImageFromFileImpl", "$Asyncify"],
#elif PROXY_TO_PTHREAD
    siv3dDecodeImageFromFile: function(ctx, src, size, data) {
        siv3dDecodeImageFromFileImpl(function () {
            Module["_emscripten_proxy_finish"](ctx);
        }, src, size, data);
    },
    siv3dDecodeImageFromFile__sig: "viiii",
    siv3dDecodeImageFromFile__proxy: "sync",
    siv3dDecodeImageFromFile__deps: ["$siv3dDecodeImageFromFileImpl"],
#else
    siv3dDecodeImageFromFile: function(_, _, arg) {
        HEAP32[(arg>>2)+0] = 0;
        HEAP32[(arg>>2)+1] = 0;
        HEAPU32[(arg>>2)+2] = 0;
        HEAPU32[(arg>>2)+3] = 0;
    },
    siv3dDecodeImageFromFile__sig: "viii",
    siv3dDecodeImageFromFile__proxy: "sync",
#endif
});
