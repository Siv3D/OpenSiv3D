mergeInto(LibraryManager.library, {
    siv3dSetClipboardText: function(ctext) {
        const text = UTF8ToString(ctext);
        
        siv3dRegisterUserAction(function () {
            navigator.clipboard.writeText(text);
        });
    },
    siv3dSetClipboardText__sig: "vi",
    siv3dSetClipboardText__proxy: "sync",
    siv3dSetClipboardText__deps: [ "$siv3dRegisterUserAction" ],

    $siv3dGetClipboardTextImpl: function(wakeUp) {
        siv3dRegisterUserAction(function () {
            if (!navigator.clipboard.readText) {
                err("Reading clipboard is not allowed in this browser.");
                resolve(0);
                return;
            }

            navigator.clipboard.readText()
                .then(function(str) {
                    const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);       
                    resolve(strPtr);
                })
                .catch(function(_) {
                    resolve(0);
                });
        });
    },
    $siv3dGetClipboardTextImpl__deps: [ "$siv3dRegisterUserAction" ],

#if ASYNCIFY
    siv3dGetClipboardText: function() {
        return Asyncify.handleSleep(siv3dGetClipboardTextImpl);
    },
    siv3dGetClipboardText__sig: "iv",
    siv3dGetClipboardText__deps: [ "$siv3dGetClipboardTextImpl", "$Asyncify" ],
#elif PROXY_TO_PTHREAD
    siv3dGetClipboardText: function(ctx) {
        siv3dGetClipboardTextImpl(function () {
            Module["_emscripten_proxy_finish"](ctx);
        });
    },
    siv3dGetClipboardText__sig: "ii",
    siv3dGetClipboardText__proxy: "sync",
    siv3dGetClipboardText__deps: [ "$siv3dGetClipboardTextImpl" ],
#else
    siv3dGetClipboardText: function() {
        return 0;
    },
    siv3dGetClipboardText__sig: "iv",
#endif

    siv3dGetClipboardTextAsync: function(callback, promise) {
        siv3dRegisterUserAction(function () {
            if (!navigator.clipboard.readText) {
                err("Reading clipboard is not allowed in this browser.");
                {{{ makeDynCall('vii', 'callback') }}}(0, promise);
                return;
            }

            navigator.clipboard.readText()
            .then(function(str) {
                const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);       
                {{{ makeDynCall('vii', 'callback') }}}(strPtr, promise);
                Module["_free"](strPtr);
            })
            .catch(function (e) {
                {{{ makeDynCall('vii', 'callback') }}}(0, promise);
            });
        });
    },
    siv3dGetClipboardTextAsync__sig: "vii",
    siv3dGetClipboardTextAsync__proxy: "sync",
    siv3dGetClipboardTextAsync__deps: [ "$siv3dRegisterUserAction" ],
});