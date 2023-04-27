mergeInto(LibraryManager.library, {
    //
    // System
    //
    siv3dCallOnAlert: function(textPtr) {
        const text = UTF8ToString(textPtr);
        Module["onAlert"] && Module["onAlert"](text);
    },
    siv3dCallOnAlert__sig: "vi",
    siv3dCallOnAlert__proxy: "sync",

    siv3dLocateFile: function() {
        if (Module["locateFile"]) {
            const origin = Module["locateFile"]("");
            return allocate(intArrayFromString(origin), ALLOC_NORMAL);
        } else {
            return 0;
        }
    },
    siv3dLocateFile__sig: "iv",
    siv3dLocateFile__proxy: "sync",

    siv3dSetCursorStyle: function(style) {
        const styleText = UTF8ToString(style);
        Module["canvas"]["style"]["cursor"] = styleText;
    },
    siv3dSetCursorStyle__sig: "vi",
    siv3dSetCursorStyle__proxy: "sync",

    siv3dRequestFullscreen: function() {
        siv3dRegisterUserAction(function () {
            Browser.requestFullscreen();
        });
    },
    siv3dRequestFullscreen__sig: "v",
    siv3dRequestFullscreen__proxy: "sync",
    siv3dRequestFullscreen__deps: [ "$siv3dRegisterUserAction", "$Browser" ],

    siv3dExitFullscreen: function() {
        siv3dRegisterUserAction(function () {
            Browser.exitFullscreen();
        });
    },
    siv3dExitFullscreen__sig: "v",
    siv3dExitFullscreen__proxy: "sync",
    siv3dExitFullscreen__deps: [ "$siv3dRegisterUserAction", "$Browser" ],

    //
    // MessageBox
    //
    siv3dShowMessageBox: function(messagePtr, type) {
        const message = UTF8ToString(messagePtr);

        if (type === 0) {
            /* MessageBoxButtons.OK */
            window.alert(message);
            return 0; /* MessageBoxResult.OK */
        } else if (type === 1) {
            /* MessageBoxButtons.OKCancel */
            return window.confirm(message) ? 0 /* MessageBoxResult.OK */ : 1 /* MessageBoxResult.Cancel */;
        }

        return 4; /* MessageBoxSelection.None */
    },
    siv3dShowMessageBox__sig: "iii",
    siv3dShowMessageBox__proxy: "sync",

    //
    // AngelScript Support
    //
    siv3dCallIndirect: function(funcPtr, funcTypes, retPtr, argsPtr) {
        let args = [];
        let funcTypeIndex = funcTypes;
        let argsPtrIndex = argsPtr;

        const retType = HEAPU8[funcTypeIndex++];

        while (true) {
            const funcType = HEAPU8[funcTypeIndex++];

            if (funcType === 0) break;

            switch (funcType) {
                case 105: // 'i':
                    args.push(HEAP32[argsPtrIndex >> 2]);
                    argsPtrIndex += 4;
                    break;
                case 102: // 'f':
                    args.push(HEAPF32[argsPtrIndex >> 2]);
                    argsPtrIndex += 4;
                    break;
                case 100: // 'd':
                    argsPtrIndex += (8 - argsPtrIndex % 8);
                    args.push(HEAPF64[argsPtrIndex >> 3]);
                    argsPtrIndex += 8;
                    break;
                default:
                    err("Unrecognized Function Type");
            }
        }

        const retValue = wasmTable.get(funcPtr).apply(null, args);

        switch (retType) {
            case 105: // 'i':
                HEAP32[retPtr >> 2] = retValue;
                break;
            case 102: // 'f':
                HEAPF32[retPtr >> 2] = retValue;
                break;
            case 100: // 'd':
                HEAPF64[retPtr >> 3] = retValue;
                break;
            case 118: // 'v':
                break;
            default:
                err("Unrecognized Function Type");
        }
    },
    siv3dCallIndirect__sig: "viiii",
    siv3dCallIndirect__proxy: "sync",

    //
    // Misc
    //
    siv3dLaunchBrowser: function(url) {
        const urlString = UTF8ToString(url);
        
        siv3dRegisterUserAction(function () {
            window.open(urlString, '_blank')
        });
    },
    siv3dLaunchBrowser__sig: "vi",
    siv3dLaunchBrowser__proxy: "sync",
    siv3dLaunchBrowser__deps: [ "$siv3dRegisterUserAction" ],

    siv3dGetURLParameters: function() {
        const params = new URL(document.location).searchParams.entries();
        const paramStrs = [];
        
        for (const param of params)
        {
            paramStrs.push(...param);
        }

        const dataPos = (Module["_malloc"](4 * (paramStrs.length + 1))) / 4;
        HEAPU32.fill(0, dataPos, dataPos + paramStrs.length + 1);

        for (var i = 0; i < paramStrs.length; i++)
        {
            HEAP32[dataPos + i] = allocate(intArrayFromString(paramStrs[i]), ALLOC_NORMAL);
        }

        return dataPos * 4; // dataPos * sizeof(uint32_t)
    },
    siv3dGetURLParameters__sig: "iv",
    siv3dGetURLParameters__proxy: "sync",

    //
    // Asyncify Support
    //
#if ASYNCIFY

    siv3dSleepUntilWaked: function() {
        Asyncify.handleSleep(function(wakeUp) {
            siv3dAwakeFunction = wakeUp;
        });
        return 0;
    },
    siv3dSleepUntilWaked__sig: "iv",
    siv3dSleepUntilWaked__proxy: "sync",
    siv3dSleepUntilWaked__deps: [ "$Asyncify", "$siv3dAwakeFunction" ],
    
    siv3dRequestAnimationFrame: function() {
        Asyncify.handleSleep(function(wakeUp) {
            siv3dAwakeFunction = wakeUp;
            requestAnimationFrame(siv3dMaybeAwake);
        });
    },
    siv3dRequestAnimationFrame__sig: "v",
    siv3dRequestAnimationFrame__proxy: "sync", 
    siv3dRequestAnimationFrame__deps: [ "$Asyncify", "$siv3dAwakeFunction" ],

#elif PROXY_TO_PTHREAD

    siv3dSleepUntilWaked: function(ctx, _) {
        siv3dAwakeFunction = function () {
            Module["_emscripten_proxy_finish"](ctx);
        };
    },
    siv3dSleepUntilWaked__sig: "vii",
    siv3dSleepUntilWaked__deps: [ "$siv3dAwakeFunction" ],

    siv3dRequestAnimationFrame: function(ctx, _) {
        siv3dAwakeFunction = function () {
            Module["_emscripten_proxy_finish"](ctx);
        };
        requestAnimationFrame(_siv3dMaybeAwake);
    },
    siv3dRequestAnimationFrame__sig: "v",
    siv3dRequestAnimationFrame__deps: [ "$siv3dAwakeFunction", "siv3dMaybeAwake" ],

#else

    siv3dSleepUntilWaked: function() {
        return -1;
    },
    siv3dSleepUntilWaked__sig: "iv",
    siv3dRequestAnimationFrame: function() {
        // nop
    },
    siv3dRequestAnimationFrame__sig: "v",

#endif

    $siv3dAwakeFunction: null,
    siv3dMaybeAwake: function() {
        if (siv3dAwakeFunction) {
            let awake = siv3dAwakeFunction;
            siv3dAwakeFunction = null;

            try {
                awake();
            } catch (e) {
                abort(e);
            } finally {
#if ASYNCIFY
                maybeExit();
#endif
            }
        }
    },
    siv3dMaybeAwake__sig: "v",
    siv3dMaybeAwake__proxy: "sync",
    siv3dMaybeAwake__deps: [ "$siv3dAwakeFunction", "$maybeExit", "abort" ],
});
