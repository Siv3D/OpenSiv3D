mergeInto(LibraryManager.library, {
    //
    // System
    //
    siv3dCallOnAlert: function(textPtr) {
        const text = UTF8ToString(textPtr);
        Module["onAlert"] && Module["onAlert"](text);
    },
    siv3dCallOnAlert__sig: "vi",

    siv3dLocateFile: function() {
        if (Module["locateFile"]) {
            const origin = Module["locateFile"]("");
            return allocate(intArrayFromString(origin), ALLOC_NORMAL);
        } else {
            return 0;
        }
    },
    siv3dLocateFile__sig: "iv",

    //
    // GamePads
    //
    siv3dGetJoystickInfo: function(joystickId) {
        return GLFW.joys[joystickId].id;
    },
    siv3dGetJoystickInfo__sig: "iiiii",

    glfwGetJoystickHats: function () {
        // Not supported.
        return 0;
    },
    glfwGetJoystickHats__sig: "iii",

    glfwGetKeysSiv3D: function (windowid) {
        const window = GLFW.WindowFromId(windowid);
        if (!window) return 0;
        if (!window.keysBuffer) {
            window.keysBuffer = Module["_malloc"](349 /* GLFW_KEY_LAST + 1 */)
            Module["HEAPU8"].fill(0, window.keysBuffer, window.keysBuffer + 348);
        }
        Module["HEAPU8"].set(window.keys, window.keysBuffer);
        return window.keysBuffer;
    },
    glfwGetKeysSiv3D__sig: "ii",

    //
    // Monitors
    //
    glfwGetMonitorInfo_Siv3D: function(handle, displayID, xpos, ypos, w, h) {
        setValue(displayID, 1, 'i32');
        setValue(xpos, 0, 'i32');
        setValue(ypos, 0, 'i32');
        setValue(w, window.screen.width, 'i32');
        setValue(h, window.screen.height, 'i32');
    },
    glfwGetMonitorInfo_Siv3D__sig: "viiiiiiiiiii",

    glfwGetMonitorWorkarea: function(handle, wx, wy, ww, wh) {
        setValue(wx, 0, 'i32');
        setValue(wy, 0, 'i32');
        setValue(ww, window.screen.availWidth, 'i32');
        setValue(wh, window.screen.availHeight, 'i32');
    },
    glfwGetMonitorWorkarea__sig: "viiiii",

    glfwGetMonitorContentScale: function(handle, xscale, yscale) {
        setValue(xscale, 1, 'float');
        setValue(yscale, 1, 'float'); 
    },
    glfwGetMonitorContentScale__sig: "viii",

    siv3dSetCursorStyle: function(style) {
        const styleText = UTF8ToString(style);
        Module["canvas"]["style"]["cursor"] = styleText;
    },
    siv3dSetCursorStyle__sig: "vi",

    siv3dRequestFullscreen: function() {
        siv3dRegisterUserAction(function () {
            Browser.requestFullscreen();
        });
    },
    siv3dRequestFullscreen__sig: "v",
    siv3dRequestFullscreen__deps: [ "$siv3dRegisterUserAction", "$Browser" ],

    siv3dExitFullscreen: function() {
        siv3dRegisterUserAction(function () {
            Browser.exitFullscreen();
        });
    },
    siv3dExitFullscreen__sig: "v",
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

    //
    // DragDrop Support
    //
    siv3dRegisterDragEnter: function(ptr) {
        Module["canvas"]["ondragenter"] = function (e) {
            e.preventDefault();

            const types = e.dataTransfer.types;

            if (types.length > 0) {
                const adusted = siv3dAdjustPoint(e.pageX, e.pageY);
                {{{ makeDynCall('vi', 'ptr') }}}(types[0] === 'Files' ? 1 : 0, adusted.x, adusted.y);
            }        
        };
    },
    siv3dRegisterDragEnter__sig: "vi",

    siv3dRegisterDragUpdate: function(ptr) {
        Module["canvas"]["ondragover"] = function (e) {
            e.preventDefault();
            const adusted = siv3dAdjustPoint(e.pageX, e.pageY);
            {{{ makeDynCall('vii', 'ptr') }}}(adusted.x, adusted.y);
        };
    },
    siv3dRegisterDragUpdate__sig: "vi",
    siv3dRegisterDragUpdate__deps: [ "$siv3dAdjustPoint" ],

    siv3dRegisterDragExit: function(ptr) {
        Module["canvas"]["ondragexit"] = function (e) {
            e.preventDefault();
            {{{ makeDynCall('v', 'ptr') }}}();
        };
    },
    siv3dRegisterDragExit__sig: "vi",

    $siv3dDragDropFileReader: null,
    siv3dRegisterDragDrop: function(ptr) {
        Module["canvas"]["ondrop"] = function (e) {
            e.preventDefault();

            const items = e.dataTransfer.items;
            const adusted = siv3dAdjustPoint(e.pageX, e.pageY);

            if (items.length == 0) {
                return;
            }

            if (items[0].kind === 'string') {
                items[0].getAsString(function(str) {
                    const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);
                    {{{ makeDynCall('vi', 'ptr') }}}(strPtr, adusted.x, adusted.y);
                    Module["_free"](strPtr);
                })            
            } else if (items[0].kind === 'file') {
                const file = items[0].getAsFile();

                if (!siv3dDragDropFileReader) {
                    siv3dDragDropFileReader = new FileReader();
                }

                const filePath = "/tmp/" + file.name;

                siv3dDragDropFileReader.addEventListener("load", function onLoaded() {
                    FS.writeFile(filePath, new Uint8Array(siv3dDragDropFileReader.result));

                    const namePtr = allocate(intArrayFromString(filePath), ALLOC_NORMAL);
                    {{{ makeDynCall('vi', 'ptr') }}}(namePtr, adusted.x, adusted.y);

                    siv3dDragDropFileReader.removeEventListener("load", onLoaded);
                });

                siv3dDragDropFileReader.readAsArrayBuffer(file);              
            }
        };
    },
    siv3dRegisterDragDrop__sig: "vi",
    siv3dRegisterDragDrop__deps: [ "$siv3dDragDropFileReader", "$FS" ],

    //
    // WebCamera/Movie Support
    //
    $videoElements: [],

    $siv3dOpenVideoStream: function(filename, callback, callbackArg) {
        const videoData = FS.readFile(UTF8ToString(fileName));
        const media_source = new MediaSource();
       
        const video = document.createElement("video");
        video["muted"] = true;
        video["autoplay"] = true;
        video["playsInline"] = true;

        media_source.addEventListener('sourceopen', function() {
            const source_buffer = media_source.addSourceBuffer('video/mp4');
			source_buffer.addEventListener("updateend", function () {
                media_source.endOfStream()
            });
			source_buffer.appendBuffer(videoData)
        });

        video.addEventListener('loadedmetadata', function onLoaded() {
            const idx = GL.getNewId(videoElements);

            video.removeEventListener('loadedmetadata', onLoaded);
            videoElements[idx] = video;

            if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
            _siv3dMaybeAwake();
        });

        video.src = URL.createObjectURL(media_source);
    },
    $siv3dOpenVideoStream__deps: [ "siv3dMaybeAwake" ],

    siv3dOpenVideo: function(fileName, callback, callbackArg) {
        const videoData = FS.readFile(UTF8ToString(fileName));
        const videoBlob = new Blob([ videoData ], { type: "video/mp4" });
       
        const video = document.createElement("video");
        video["muted"] = true;
        video["autoplay"] = true;
        video["playsInline"] = true;

        video.addEventListener('loadedmetadata', function onLoaded() {
            const idx = GL.getNewId(videoElements);

            video.removeEventListener('loadedmetadata', onLoaded);
            videoElements[idx] = video;

            if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
            _siv3dMaybeAwake();
        });

        video.src = URL.createObjectURL(videoBlob);
    },
    siv3dOpenVideo__sig: "viii",
    siv3dOpenVideo__deps: [ "$FS", "$videoElements", "$siv3dRegisterUserAction", "siv3dMaybeAwake" ],

    siv3dOpenCamera: function(width, height, callback, callbackArg) {
        const constraint = {
            video: { 
                width : width > 0 ? width : undefined, 
                height: height > 0 ? height : undefined 
            },
            audio: false
        };

        navigator.mediaDevices.getUserMedia(constraint).then(
            function(stream) {
                const video = document.createElement("video");

                video["playsInline"] = true;          
                video.addEventListener('loadedmetadata', function onLoaded() {
                    const idx = GL.getNewId(videoElements);

                    video.removeEventListener('loadedmetadata', onLoaded);
                    videoElements[idx] = video;

                    if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
                    _siv3dMaybeAwake();
                });

                video.srcObject = stream;
            }
        ).catch(function(_) {
            if (callback) {{{ makeDynCall('vii', 'callback') }}}(0, callbackArg);
            _siv3dMaybeAwake();
        })
    },
    siv3dOpenCamera__sig: "viiii",
    siv3dOpenCamera__deps: [ "$videoElements", "siv3dMaybeAwake" ],

    siv3dSetCameraResolution: function(idx, width, height, callback, callbackArg) {
        /** @type { HTMLVideoElement } */
        const video = videoElements[idx];
        /** @type { MediaStreamTrack } */
        const stream = video.srcObject.getVideoTracks()[0];

        const constraint = {
            video: { width, height },
            audio: false
        };

        stream.applyConstraints(constraint).then(
            function () {
                if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
                _siv3dMaybeAwake();
            }
        );
    },
    siv3dSetCameraResolution__sig: "viiiii",
    siv3dSetCameraResolution__deps: [ "$videoElements", "siv3dMaybeAwake" ],

    siv3dQueryCameraAvailability: function () {
        return !!navigator.getUserMedia;
    },
    siv3dQueryCameraAvailability__sig: "iv",

    siv3dRegisterVideoTimeUpdateCallback: function(idx, callback, callbackArg) {
        const video = videoElements[idx];

        if (callback) {
            video.ontimeupdate = function() {
                {{{ makeDynCall('vi', 'callback') }}}(callbackArg);
                _siv3dMaybeAwake();
            }
        } else {
            video.ontimeupdate = null;
        }
    },
    siv3dRegisterVideoTimeUpdateCallback__sig: "viii",
    siv3dRegisterVideoTimeUpdateCallback__deps: [ "$videoElements", "siv3dMaybeAwake" ], 

    siv3dCaptureVideoFrame: function(target, level, internalFormat, width, height, border, format, type, idx) {
        const video = videoElements[idx];
        GLctx.texSubImage2D(target, level, 0, 0, width, height, format, type, video);
    },
    siv3dCaptureVideoFrame__sig: "viiiiiiiii",
    siv3dCaptureVideoFrame__deps: ["$videoElements"],

    siv3dQueryVideoPlaybackedTime: function(idx) {
        const video = videoElements[idx];
        return video.currentTime;
    },
    siv3dQueryVideoPlaybackedTime__sig: "di",
    siv3dQueryVideoPlaybackedTime__deps: ["$videoElements"],

    siv3dSetVideoPlaybackedTime: function(idx, time) {
        const video = videoElements[idx];
        video.currentTime = time;
    },
    siv3dSetVideoPlaybackedTime__sig: "vid",
    siv3dSetVideoPlaybackedTime__deps: ["$videoElements"],

    siv3dQueryVideoDuration: function(idx) {
        const video = videoElements[idx];
        return video.duration;
    },
    siv3dQueryVideoDuration__sig: "di",
    siv3dQueryVideoDuration__deps: ["$videoElements"],

    siv3dQueryVideoEnded: function(idx) {
        const video = videoElements[idx];
        return video.ended;
    },
    siv3dQueryVideoEnded__sig: "ii",
    siv3dQueryVideoEnded__deps: ["$videoElements"],

    siv3dQueryVideoPreference: function(idx, width, height, fps) {
        const video = videoElements[idx];

        setValue(width, video.videoWidth, 'i32');
        setValue(height, video.videoHeight, 'i32');
        setValue(fps, 29.7, 'double');
    },
    siv3dQueryVideoPlaybackedTime__sig: "viiii",
    siv3dQueryVideoPlaybackedTime__deps: ["$videoElements"],

    siv3dPlayVideo: function(idx) {
        const video = videoElements[idx];
        
        video.play().catch(function () {
                siv3dRegisterUserAction(function() {
                    video.play();
                })
            }
        );
    },
    siv3dPlayVideo__sig: "vi",
    siv3dPlayVideo__deps: ["$videoElements"],

    siv3dStopVideo: function(idx) {
        const video = videoElements[idx];
        video.pause();
    },
    siv3dStopVideo__sig: "vi",
    siv3dStopVideo__deps: ["$videoElements"],

    siv3dDestroyVideo: function(idx) {
        _siv3dStopVideo(idx);

        const video = videoElements[idx];
        if (!!video.src) {
            URL.revokeObjectURL(video.src);
        }

        delete videoElements[idx];
    },
    siv3dDestroyVideo__sig: "vi",
    siv3dDestroyVideo__deps: ["$videoElements", "siv3dStopVideo"],

    //
    // MultiTouch Support
    //
    $siv3dActiveTouches: [],

    $siv3dAdjustPoint: function (x, y) {
        const rect = Module["canvas"].getBoundingClientRect();
        const cw = Module["canvas"].width;
        const ch = Module["canvas"].height;

        const scrollX = ((typeof window.scrollX !== 'undefined') ? window.scrollX : window.pageXOffset);
        const scrollY = ((typeof window.scrollY !== 'undefined') ? window.scrollY : window.pageYOffset);

        let adjustedX = x - (scrollX + rect.left);
        let adjustedY = y - (scrollY + rect.top);

        adjustedX = adjustedX * (cw / rect.width);
        adjustedY = adjustedY * (ch / rect.height);

        return { x: adjustedX, y: adjustedY };
    },
    
    $siv3dOnTouchStart: function(e) {
        siv3dActiveTouches = Array.from(e.touches);
        e.preventDefault()
    },

    $siv3dOnTouchEnd: function(e) {
        siv3dActiveTouches = Array.from(e.touches);
        e.stopPropagation();
    },

    $siv3dOnTouchMove: function(e) {
        siv3dActiveTouches = Array.from(e.touches);
        e.stopPropagation();
    },

    siv3dRegisterTouchCallback: function() {
        Module["canvas"].addEventListener("touchstart", siv3dOnTouchStart);
        Module["canvas"].addEventListener("touchmove", siv3dOnTouchMove);
    },
    siv3dRegisterTouchCallback__sig: "v",
    siv3dRegisterTouchCallback__deps: [ "$siv3dOnTouchMove", "$siv3dOnTouchStart", "$siv3dActiveTouches" ],

    siv3dUnregisterTouchCallback: function() {
        Module["canvas"].removeEventListener("touchstart", siv3dOnTouchStart);
        Module["canvas"].removeEventListener("touchmove", siv3dOnTouchMove);
    },
    siv3dUnregisterTouchCallback__sig: "v",
    siv3dUnregisterTouchCallback__deps: [ "$siv3dOnTouchMove", "$siv3dOnTouchStart" ],

    siv3dGetPrimaryTouchPoint: function(pX, pY) {
        if (siv3dActiveTouches.length > 0) {
            const touch = siv3dActiveTouches[0];
            const adjusted = siv3dAdjustPoint(touch.pageX, touch.pageY);
            
            setValue(pX, adjusted.x, 'double');
            setValue(pY, adjusted.y, 'double');
            return 1;
        } else {
            return 0;
        }
    },
    siv3dGetPrimaryTouchPoint__sig: "iii",
    siv3dGetPrimaryTouchPoint__deps: [ "$siv3dActiveTouches", "$siv3dAdjustPoint" ],

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

    //
    // User Action Emulation
    //
    $siv3dHasUserActionTriggered: false,
    $siv3dPendingUserActions: [],

    $siv3dTriggerUserAction: function() {
        for (var i = 0; i < siv3dPendingUserActions.length; i++) {
            (siv3dPendingUserActions[i])();
        }

        siv3dPendingUserActions.splice(0);
        siv3dHasUserActionTriggered = false;
    },
    $siv3dTriggerUserAction__deps: [ "$siv3dPendingUserActions" ],

    $siv3dRegisterUserAction: function(func) {
        siv3dPendingUserActions.push(func);
    },
    $siv3dRegisterUserAction__deps: [ "$siv3dPendingUserActions", "$autoResumeAudioContext", "$dynCall" ],

    $siv3dUserActionHookCallBack: function() {
        if (!siv3dHasUserActionTriggered) {
            setTimeout(siv3dTriggerUserAction, 30);
            siv3dHasUserActionTriggered = true;
        }
    },
    $siv3dUserActionHookCallBack__deps: [ "$siv3dHasUserActionTriggered", "$siv3dTriggerUserAction" ],

    siv3dStartUserActionHook: function() {
        Module["canvas"].addEventListener('touchend', siv3dUserActionHookCallBack);
        Module["canvas"].addEventListener('mousedown', siv3dUserActionHookCallBack);
        window.addEventListener('keydown', siv3dUserActionHookCallBack);
    },
    siv3dStartUserActionHook__sig: "v",
    siv3dStartUserActionHook__deps: [ "$siv3dUserActionHookCallBack", "$siv3dHasUserActionTriggered" ],

    siv3dStopUserActionHook: function() {
        Module["canvas"].removeEventListener('touchend', siv3dUserActionHookCallBack);
        Module["canvas"].removeEventListener('mousedown', siv3dUserActionHookCallBack);
        window.removeEventListener('keydown', siv3dUserActionHookCallBack);
    },
    siv3dStopUserActionHook__sig: "v",
    siv3dStopUserActionHook__deps: [ "$siv3dUserActionHookCallBack" ],

    //
    // Dialog Support
    //
    $siv3dInputElement: null,
    $siv3dDialogFileReader: null,
    $siv3dDownloadLink: null,

    siv3dInitDialog: function() {
        siv3dInputElement = document.createElement("input");
        siv3dInputElement.type = "file";

        siv3dDialogFileReader = new FileReader();
        siv3dDownloadLink = document.createElement("a");
    },
    siv3dInitDialog__sig: "v",
    siv3dInitDialog__deps: [ "$siv3dInputElement", "$siv3dDialogFileReader", "$siv3dDownloadLink" ],

    siv3dOpenDialogAsync: function(filterStr, callback, futurePtr) {
        siv3dInputElement.accept = UTF8ToString(filterStr);
        siv3dInputElement.oninput = function(e) {
            const files = e.target.files;

            if (files.length < 1) {
                {{{ makeDynCall('vii', 'callback') }}}(0, futurePtr);
                _siv3dMaybeAwake();
                return;
            }

            const file = files[0];
            const filePath = "/tmp/" + file.name;

            siv3dDialogFileReader.addEventListener("load", function onLoaded() {
                FS.writeFile(filePath, new Uint8Array(siv3dDialogFileReader.result));

                const namePtr = allocate(intArrayFromString(filePath), ALLOC_NORMAL);
                {{{ makeDynCall('vii', 'callback') }}}(namePtr, futurePtr);
                _siv3dMaybeAwake();

                siv3dDialogFileReader.removeEventListener("load", onLoaded);
            });

            siv3dDialogFileReader.readAsArrayBuffer(file);         
        };

        siv3dRegisterUserAction(function() {
            siv3dInputElement.click();
        });
    },
    siv3dOpenDialogAsync__sig: "vii",
    siv3dOpenDialogAsync__deps: [ "$siv3dInputElement", "$siv3dDialogFileReader", "$siv3dRegisterUserAction", "$FS", "siv3dMaybeAwake" ],

    $siv3dSaveFileBuffer: null, 
    $siv3dSaveFileBufferWritePos: 0,
    $siv3dDefaultSaveFileName: null,

    siv3dDownloadFile: function(filePathPtr, fileNamePtr, mimeTypePtr) {
        const filePath = UTF8ToString(filePathPtr);
        const fileName = UTF8ToString(fileNamePtr);
        const mimeType = mimeTypePtr ? UTF8ToString(mimeTypePtr) : "application/octet-stream";
        const fileData = FS.readFile(filePath);

        const blob = new Blob([ fileData ], { type: mimeType });

        siv3dDownloadLink.href = URL.createObjectURL(blob);
        siv3dDownloadLink.download = fileName;

        siv3dRegisterUserAction(function() {
            siv3dDownloadLink.click();         
        });
    },
    siv3dDownloadFile__sig: "viii",
    siv3dDownloadFile__deps: [ "$siv3dRegisterUserAction" ],

    //
    // Audio Support
    //
    siv3dDecodeAudioFromFileAsync: function(filePath, callback, arg) {
        const path = UTF8ToString(filePath, 1024);
        const fileBytes = FS.readFile(path);

        const onSuccess = function(decoded) {
            const leftDataBuffer = Module["_malloc"](decoded.length * 4);
            HEAPF32.set(decoded.getChannelData(0), leftDataBuffer>>2);

            let rightDataBuffer;
            
            if (decoded.numberOfChannels >= 2) {
                rightDataBuffer = Module["_malloc"](decoded.length * 4);
                HEAPF32.set(decoded.getChannelData(1), rightDataBuffer>>2);
            } else {
                rightDataBuffer = leftDataBuffer;
            }

            HEAP32[(arg>>2)+0] = leftDataBuffer;
            HEAP32[(arg>>2)+1] = rightDataBuffer;
            HEAPU32[(arg>>2)+2] = decoded.sampleRate;
            HEAPU32[(arg>>2)+3] = decoded.length;

            {{{ makeDynCall('vi', 'callback') }}}(arg);
            _siv3dMaybeAwake();
        };

        const onFailure = function() {
            HEAP32[(arg>>2)+0] = 0;
            HEAP32[(arg>>2)+1] = 0;
            HEAPU32[(arg>>2)+2] = 0;
            HEAPU32[(arg>>2)+3] = 0;

            {{{ makeDynCall('vi', 'callback') }}}(arg);
            _siv3dMaybeAwake();
        }

        Module["SDL2"].audioContext.decodeAudioData(fileBytes.buffer, onSuccess, onFailure);   
    },
    siv3dDecodeAudioFromFileAsync__sig: "viii",
    siv3dDecodeAudioFromFileAsync__deps: [ "$AL", "$FS", "siv3dMaybeAwake" ],

    //
    // Clipboard
    //
    siv3dSetClipboardText: function(ctext) {
        const text = UTF8ToString(ctext);
        
        siv3dRegisterUserAction(function () {
            navigator.clipboard.writeText(text);
        });
    },
    siv3dSetClipboardText__sig: "vi",
    siv3dSetClipboardText__deps: [ "$siv3dRegisterUserAction" ],

    siv3dGetClipboardText: function() {
        return Asyncify.handleSleep(function (wakeUp) {
            siv3dRegisterUserAction(function () {
                navigator.clipboard.readText()
                .then(function(str) {
                    const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);       
                    wakeUp(strPtr);
                })
                .catch(function(_) {
                    wakeUp(0);
                })
            }); 
        });
    },
    siv3dGetClipboardText__sig: "iv",
    siv3dGetClipboardText__deps: [ "$siv3dRegisterUserAction", "$Asyncify" ],

    siv3dGetClipboardTextAsync: function(callback, promise) {
        siv3dRegisterUserAction(function () {
            navigator.clipboard.readText()
            .then(function(str) {
                const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);       
                {{{ makeDynCall('vii', 'callback') }}}(strPtr, promise);
                Module["_free"](strPtr);
            })
            .catch(function (e) {
                {{{ makeDynCall('vii', 'callback') }}}(0, promise);
            })
        });
        
    },
    siv3dGetClipboardTextAsync__sig: "vii",
    siv3dGetClipboardTextAsync__deps: [ "$siv3dRegisterUserAction" ],

    //
    // TextInput
    //
    $siv3dTextInputElement: null,

    siv3dInitTextInput: function() {
        const textInput = document.createElement("input");
        textInput.type = "text";
        textInput.style.position = "absolute";
        textInput.style.zIndex = -2;
        textInput.autocomplete = false;

        const maskDiv = document.createElement("div");
        maskDiv.style.background = "white";
        maskDiv.style.position = "absolute";
        maskDiv.style.width = "100%";
        maskDiv.style.height = "100%";
        maskDiv.style.zIndex = -1;

        /**
         * @type { HTMLCanvasElement }
         */
        const canvas = Module["canvas"];

        canvas.parentNode.prepend(textInput);
        canvas.parentNode.prepend(maskDiv);

        siv3dTextInputElement = textInput;
    },
    siv3dInitTextInput__sig: "v",
    siv3dInitTextInput__deps: [ "$siv3dTextInputElement" ],

    siv3dRegisterTextInputCallback: function(callback) {
        siv3dTextInputElement.addEventListener('input', function (e) {
            if (e.inputType == "insertText") {
                if (e.data) {
                    for (var i = 0; i < e.data.length; i++) {
                        const codePoint = e.data.charCodeAt(i);
                        {{{ makeDynCall('vi', 'callback') }}}(codePoint);
                    }
                }
            }    
        });
        siv3dTextInputElement.addEventListener('compositionend', function (e) {
            for (var i = 0; i < e.data.length; i++) {
                const codePoint = e.data.charCodeAt(i);
                {{{ makeDynCall('vi', 'callback') }}}(codePoint);
            }
        });
    },
    siv3dRegisterTextInputCallback__sig: "vi",
    siv3dRegisterTextInputCallback__deps: [ "$siv3dTextInputElement" ],

    siv3dRegisterTextInputMarkedCallback: function(callback) {
        siv3dTextInputElement.addEventListener('compositionupdate', function (e) {
            const strPtr = allocate(intArrayFromString(e.data), ALLOC_NORMAL);
            {{{ makeDynCall('vi', 'callback') }}}(strPtr);
            Module["_free"](strPtr);
        })
        siv3dTextInputElement.addEventListener('compositionend', function (e) {
            {{{ makeDynCall('vi', 'callback') }}}(0);
        });
    },
    siv3dRegisterTextInputMarkedCallback__sig: "vi",
    siv3dRegisterTextInputMarkedCallback__deps: [ "$siv3dTextInputElement" ],

    siv3dRequestTextInputFocus: function(isFocusRequired) {
        const isFocusRequiredBool = isFocusRequired != 0;

        if (isFocusRequiredBool) {
            siv3dRegisterUserAction(function () {
                siv3dTextInputElement.value = ""
                siv3dTextInputElement.focus();
            });
        } else {
            siv3dRegisterUserAction(function () {
                siv3dTextInputElement.blur();
            });
        }
    },
    siv3dRequestTextInputFocus__sig: "vi",
    siv3dRequestTextInputFocus__deps: [ "$siv3dRegisterUserAction", "$siv3dTextInputElement" ],

    //
    // Font Rendering
    //
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
    siv3dRenderText__deps: [ "$siv3dTextRenderingCanvas", "$siv3dTextRenderingCanvasContext" ],


    //
    // Notification
    //
    $siv3dNotifications: [],

    siv3dRequestNotificationPermission: function(callback, callbackArg) {
        if (Notification.permission === "granted") {
            {{{ makeDynCall('vii', 'callback') }}}(1 /* NotificationPermission.Granted */, callbackArg);
            _siv3dMaybeAwake();
        } else {
            siv3dRegisterUserAction(function () {
                Notification.requestPermission().then(function(v) {
                    if (v === "granted") {
                        {{{ makeDynCall('vii', 'callback') }}}(1 /* NotificationPermission.Granted */, callbackArg);
                    } else {
                        {{{ makeDynCall('vii', 'callback') }}}(2 /* NotificationPermission.Denied */, callbackArg);
                    }
                    _siv3dMaybeAwake();
                });
            });
        }
    },
    siv3dRequestNotificationPermission__sig: "vii",
    siv3dRequestNotificationPermission__deps: [ "siv3dMaybeAwake"],

    siv3dCreateNotification: function(title, body, actionsNum, actionTexts, callback, callbackArg) {
        if (!window.Notification && Notification.permission !== "granted") {
            {{{ makeDynCall('vii', 'callback') }}}(0, callbackArg);
            _siv3dMaybeAwake();
            return 0;
        }

        const idx = GL.getNewId(siv3dNotifications);

        const titleText = UTF8ToString(title);
        const bodyText = UTF8ToString(body);
        let actions = [];

        for (var i = 0; i < actionsNum; i++) {
            const textPtr = getValue(actionTexts + i * 4, "i32");
            const actionText = UTF8ToString(textPtr);

            actions.push({ title: actionText, action: actionText });
        }

        siv3dNotifications[idx] = new Notification(titleText, { body: bodyText, actions: actions });
        {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
        _siv3dMaybeAwake();

        return idx;
    },
    siv3dCreateNotification__sig: "iiiiiii",
    siv3dCreateNotification__deps: [ "$siv3dRegisterUserAction", "$siv3dNotifications", "siv3dMaybeAwake" ],

    siv3dRegisterNotificationCallback: function(id, callback, callbackArg) {
        const notificattion = siv3dNotifications[id];

        notificattion.onclick = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 1 /* ToastNotificationState.Activated */, callbackArg);
            _siv3dMaybeAwake();
        }
        notificattion.onshow = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 2 /* ToastNotificationState.Shown */, callbackArg);
            _siv3dMaybeAwake();
        }
        notificattion.onclose = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 5 /* ToastNotificationState.TimedOut */, callbackArg);
            _siv3dMaybeAwake();
        }
        notificattion.onerror = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 6 /* ToastNotificationState.Error */, callbackArg);
            _siv3dMaybeAwake();
        }
    },
    siv3dRegisterNotificationCallback__sig: "viii",
    siv3dRegisterNotificationCallback__deps: [ "$siv3dNotifications", "siv3dMaybeAwake" ],

    siv3dCloseNotification: function(id) {
        const notificattion = siv3dNotifications[id];
        notificattion.close();

        delete siv3dNotifications[id];
    },
    siv3dCloseNotification__sig: "vi",
    siv3dCloseNotification__deps: [ "$siv3dNotifications" ],

    siv3dQueryNotificationPermission: function() {
        const status = {
            "default": 0,
            "granted": 1,
            "denied": 2
        };
        return status[Notification.permission];
    },
    siv3dQueryNotificationPermission__sig: "iv",

    //
    // TextToSpeech
    //
    siv3dEnumerateAvailableTextToSpeechLanguages: function(returnPtr) {
        const LanguageNameToLanguageCodeList = {
            "ar-SA": 1025,
            "zh-CN": 2052,
            "zh-HK": 3076,
            "zh-TW": 1028,
            "en-AU": 3081,
            "en-GB": 2057,
            "en-US": 1033,
            "fr-FR": 1036,
            "de-DE": 1031,
            "hi-IN": 1081,
            "it-IT": 1040,
            "ja-JP": 1041,
            "ko-KR": 1042,
            "pt-BR": 1046,
            "ru-RU": 1049,
            "es-ES": 1034
        };
        
        const voices = window.speechSynthesis.getVoices();
        let listBufferPtr = Module["_malloc"](voices.length * 4 * 2);

        setValue(returnPtr, voices.length, "i32");
        setValue(returnPtr + 4, listBufferPtr, "i32");

        for(var i = 0; i < voices.length; i++) {
            const languageCode = LanguageNameToLanguageCodeList[voices[i].lang];
             
            setValue(listBufferPtr + 0, languageCode, "i32");
            setValue(listBufferPtr + 4, voices[i].default, "i32");

            listBufferPtr += 8;
        }
    },
    siv3dEnumerateAvailableTextToSpeechLanguages__sig: "vi",

    siv3dStartTextToSpeechLanguages: function(textPtr, rate, volume, languageCode) {
        const LanguageCodeToLanguageNameList = {
            1025: "ar-SA",
            2052: "zh-CN",
            3076: "zh-HK",
            1028: "zh-TW",
            3081: "en-AU",
            2057: "en-GB",
            1033: "en-US",
            1036: "fr-FR",
            1031: "de-DE",
            1081: "hi-IN",
            1040: "it-IT",
            1041: "ja-JP",
            1042: "ko-KR",
            1046: "pt-BR",
            1049: "ru-RU",
            1034: "es-ES"
        };
        const text = UTF8ToString(textPtr);

        const speechUtter = new SpeechSynthesisUtterance(text);

        speechUtter.lang = LanguageCodeToLanguageNameList[languageCode];
        speechUtter.rate = rate;
        speechUtter.volume = volume;

        window.speechSynthesis.speak(speechUtter);
    },
    siv3dStartTextToSpeechLanguages__sig: "viiii",

    siv3dIsSpeakingTextToSpeechLanguages: function() {
        return window.speechSynthesis.speaking;
    },
    siv3dIsSpeakingTextToSpeechLanguages__sig: "iv",

    siv3dPauseTextToSpeechLanguages: function() {
        window.speechSynthesis.pause();
    },
    siv3dPauseTextToSpeechLanguages__sig: "v",

    siv3dResumeTextToSpeechLanguages: function() {
        window.speechSynthesis.resume();
    },
    siv3dResumeTextToSpeechLanguages__sig: "v",

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

    siv3dWebGPUConfigureSwapchain: function(deviceId, swapChainId, descriptor) {
        var device = WebGPU["mgrDevice"].get(deviceId);
        var swapChain = WebGPU["mgrSwapChain"].get(swapChainId);
        var width = {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.width, 'u32', false) }}};
        var height = {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.height, 'u32', false) }}};

        var desc = {
            "device": device,
            "format": WebGPU.TextureFormat[
                {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.format, 'u32', false) }}}],
            "usage": {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.usage, 'u32', false) }}},
            "size": { width, height }
        };

        swapChain["configure"](desc);
    },
    siv3dWebGPUConfigureSwapchain__sig: "viii",
    siv3dWebGPUConfigureSwapchain__deps: [ "$WebGPU" ], 

    //
    // Asyncify Support
    //
#if ASYNCIFY

    $siv3dAwakeFunction: null,
    siv3dSleepUntilWaked: function() {
        Asyncify.handleSleep(function(wakeUp) {
            siv3dAwakeFunction = wakeUp;
        });
        return 0;
    },
    siv3dSleepUntilWaked__sig: "iv",
    siv3dSleepUntilWaked__deps: [ "$Asyncify", "$siv3dAwakeFunction" ],

    siv3dMaybeAwake: function() {
        if (siv3dAwakeFunction) {
            let awake = siv3dAwakeFunction;
            siv3dAwakeFunction = null;

            try {
                awake();
            } catch (e) {
                abort(e);
            } finally {
                maybeExit();
            }
        }
    },
    siv3dMaybeAwake__sig: "v",
    siv3dMaybeAwake__deps: [ "$siv3dAwakeFunction" ],
    
    siv3dRequestAnimationFrame: function() {
        Asyncify.handleSleep(function(wakeUp) {
            requestAnimationFrame(function() {
                try {
                    wakeUp();
                } catch (e) {
                    abort(e);
                } finally {
                    maybeExit();
                }
            });
        });
    },
    siv3dRequestAnimationFrame__sig: "v", 
    siv3dRequestAnimationFrame__deps: [ "$Asyncify", "$maybeExit", "abort" ],

    //
    // ImageDecode
    //
    $siv3dDecodeCanvas: null,
    $siv3dDecodeCanvasContext: null,

    siv3dDecodeImageFromFile: function(src, size, data) {
        Asyncify.handleSleep(function(wakeUp) {
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
        });
    },
    siv3dDecodeImageFromFile__sig: "viii",
    siv3dDecodeImageFromFile__deps: [ "$siv3dDecodeCanvas", "$siv3dDecodeCanvasContext", "$Asyncify" ],
#else
    siv3dSleepUntilWaked: function() {
        return -1;
    },
    siv3dSleepUntilWaked__sig: "iv",
    siv3dMaybeAwake: function() {
        // nop
    },
    siv3dMaybeAwake__sig: "v",
    siv3dRequestAnimationFrame: function() {
        // nop
    },
    siv3dRequestAnimationFrame__sig: "v",

    siv3dDecodeImageFromFile: function(_, _, arg) {
        HEAP32[(arg>>2)+0] = 0;
        HEAP32[(arg>>2)+1] = 0;
        HEAPU32[(arg>>2)+2] = 0;
        HEAPU32[(arg>>2)+3] = 0;
    },
    siv3dDecodeImageFromFile__sig: "viii",
#endif
})