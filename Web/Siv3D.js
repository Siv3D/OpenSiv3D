mergeInto(LibraryManager.library, {
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

                const filePath = `/tmp/${file.name}`;

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
        });

        video.src = URL.createObjectURL(media_source);
    },

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
        });

        video.src = URL.createObjectURL(videoBlob);
    },
    siv3dOpenVideo__sig: "viii",
    siv3dOpenVideo__deps: [ "$FS", "$videoElements", "$siv3dRegisterUserAction" ],

    siv3dOpenCamera: function(width, height, callback, callbackArg) {
        const constraint = {
            video: { 
                width : width > 0 ? width : undefined, 
                height: height > 0 ? height : undefined 
            },
            audio: false
        };

        navigator.mediaDevices.getUserMedia(constraint).then(
            stream => {
                const video = document.createElement("video");

                video["playsInline"] = true;          
                video.addEventListener('loadedmetadata', function onLoaded() {
                    const idx = GL.getNewId(videoElements);

                    video.removeEventListener('loadedmetadata', onLoaded);
                    videoElements[idx] = video;

                    if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
                });

                video.srcObject = stream;
            }
        ).catch(_ => {
            if (callback) {{{ makeDynCall('vii', 'callback') }}}(0, callbackArg);
        })
    },
    siv3dOpenCamera__sig: "viiii",
    siv3dOpenCamera__deps: ["$videoElements"],

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
            () => {
                if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
            }
        );
    },
    siv3dSetCameraResolution__sig: "viiiii",
    siv3dSetCameraResolution__deps: ["$videoElements"],

    siv3dQueryCameraAvailability: function () {
        return !!navigator.getUserMedia;
    },
    siv3dQueryCameraAvailability__sig: "iv",

    siv3dRegisterVideoTimeUpdateCallback: function(idx, callback, callbackArg) {
        const video = videoElements[idx];

        if (callback) {
            video.ontimeupdate = function() {
                {{{ makeDynCall('vi', 'callback') }}}(callbackArg);
            }
        } else {
            video.ontimeupdate = null;
        }
    },
    siv3dRegisterVideoTimeUpdateCallback__sig: "viii",
    siv3dRegisterVideoTimeUpdateCallback__deps: [ "$videoElements" ], 

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
        
        video.play().catch(() =>
            siv3dRegisterUserAction(function() {
                video.play();
            })
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
        for (let action of siv3dPendingUserActions) {
            action();
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

        siv3dSaveFileBuffer = new Uint8Array(16*1024 /* 16KB */)
        siv3dDownloadLink = document.createElement("a");

        TTY.register(FS.makedev(20, 0), { put_char: siv3dWriteSaveFileBuffer, flush: siv3dFlushSaveFileBuffer });
        FS.mkdev('/dev/save', FS.makedev(20, 0));
    },
    siv3dInitDialog__sig: "v",
    siv3dInitDialog__deps: [ "$siv3dInputElement", "$siv3dDialogFileReader", "$siv3dWriteSaveFileBuffer", "$siv3dFlushSaveFileBuffer", "$siv3dSaveFileBuffer", "$siv3dDownloadLink", "$TTY", "$FS" ],

    siv3dOpenDialog: function(filterStr) {
        return Asyncify.handleSleep(function (wakeUp) {
            siv3dInputElement.accept = UTF8ToString(filterStr);
            siv3dInputElement.oninput = function(e) {
                const files = e.target.files;

                if (files.length < 1) {
                    wakeUp(0);
                    return;
                }

                const file = files[0];
                const filePath = `/tmp/${file.name}`;

                siv3dDialogFileReader.addEventListener("load", function onLoaded() {
                    FS.writeFile(filePath, new Uint8Array(siv3dDialogFileReader.result));

                    const namePtr = allocate(intArrayFromString(filePath), ALLOC_NORMAL);
                    wakeUp(namePtr);

                    siv3dDialogFileReader.removeEventListener("load", onLoaded);
                });

                siv3dDialogFileReader.readAsArrayBuffer(file);         
            };

            siv3dRegisterUserAction(function() {
                siv3dInputElement.click();
            });
        })
    },
    siv3dOpenDialog__sig: "ii",
    siv3dOpenDialog__deps: [ "$siv3dInputElement", "$siv3dDialogFileReader", "$siv3dRegisterUserAction", "$FS", "$Asyncify" ],

    siv3dOpenDialogAsync: function(filterStr, callback, futurePtr) {
        siv3dInputElement.accept = UTF8ToString(filterStr);
        siv3dInputElement.oninput = function(e) {
            const files = e.target.files;

            if (files.length < 1) {
                {{{ makeDynCall('vii', 'callback') }}}(0, futurePtr);
                return;
            }

            const file = files[0];
            const filePath = `/tmp/${file.name}`;

            siv3dDialogFileReader.addEventListener("load", function onLoaded() {
                FS.writeFile(filePath, new Uint8Array(siv3dDialogFileReader.result));

                const namePtr = allocate(intArrayFromString(filePath), ALLOC_NORMAL);
                {{{ makeDynCall('vii', 'callback') }}}(namePtr, futurePtr);

                siv3dDialogFileReader.removeEventListener("load", onLoaded);
            });

            siv3dDialogFileReader.readAsArrayBuffer(file);         
        };

        siv3dRegisterUserAction(function() {
            siv3dInputElement.click();
        });
    },
    siv3dOpenDialogAsync__sig: "vii",
    siv3dOpenDialogAsync__deps: [ "$siv3dInputElement", "$siv3dDialogFileReader", "$siv3dRegisterUserAction", "$FS" ],

    $siv3dSaveFileBuffer: null, 
    $siv3dSaveFileBufferWritePos: 0,
    $siv3dDefaultSaveFileName: null,

    $siv3dWriteSaveFileBuffer: function(tty, chr) {       
        if (siv3dSaveFileBufferWritePos >= siv3dSaveFileBuffer.length) {
            const newBuffer = new Uint8Array(siv3dSaveFileBuffer.length * 2);
            newBuffer.set(siv3dSaveFileBuffer);
            siv3dSaveFileBuffer = newBuffer;
        }

        siv3dSaveFileBuffer[siv3dSaveFileBufferWritePos] = chr;
        siv3dSaveFileBufferWritePos++;
    },
    $siv3dWriteSaveFileBuffer__deps: [ "$siv3dSaveFileBuffer", "$siv3dSaveFileBufferWritePos" ], 
    $siv3dFlushSaveFileBuffer: function(tty) {
        if (siv3dSaveFileBufferWritePos == 0) {
            return;
        }

        const data = siv3dSaveFileBuffer.subarray(0, siv3dSaveFileBufferWritePos);
        const blob = new Blob([ data ], { type: "application/octet-stream" });

        siv3dDownloadLink.href = URL.createObjectURL(blob);
        siv3dDownloadLink.download = siv3dDefaultSaveFileName;

        siv3dRegisterUserAction(function() {
            siv3dDownloadLink.click();         
        });

        siv3dSaveFileBufferWritePos = 0;
    },
    $siv3dWriteSaveFileBuffer__deps: [ "$siv3dSaveFileBuffer", "$siv3dSaveFileBufferWritePos", "$siv3dRegisterUserAction", "$siv3dDefaultSaveFileName", "$siv3dDownloadLink" ], 

    siv3dSaveDialog: function(str) {
        siv3dDefaultSaveFileName = UTF8ToString(str);
        siv3dSaveFileBufferWritePos = 0;
    },
    siv3dSaveDialog__sig: "v",
    siv3dSaveDialog__deps: [ "$siv3dSaveFileBufferWritePos", "$siv3dDefaultSaveFileName" ],

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
        };

        const onFailure = function() {
            HEAP32[(arg>>2)+0] = 0;
            HEAP32[(arg>>2)+1] = 0;
            HEAPU32[(arg>>2)+2] = 0;
            HEAPU32[(arg>>2)+3] = 0;

            {{{ makeDynCall('vi', 'callback') }}}(arg);
        }

        Module["SDL2"].audioContext.decodeAudioData(fileBytes.buffer, onSuccess, onFailure);   
    },
    siv3dDecodeAudioFromFileAsync__sig: "viii",
    siv3dDecodeAudioFromFileAsync__deps: [ "$AL", "$FS" ],

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
                .then(str => {
                    const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);       
                    wakeUp(strPtr);
                })
                .catch(_ => {
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
            .then(str => {
                const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);       
                {{{ makeDynCall('vii', 'callback') }}}(strPtr, promise);
                Module["_free"](strPtr);
            })
            .catch(e => {
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
                    for (let i = 0; i < e.data.length; i++) {
                        const codePoint = e.data.charCodeAt(i);
                        {{{ makeDynCall('vi', 'callback') }}}(codePoint);
                    }
                }
            }    
        });
        siv3dTextInputElement.addEventListener('compositionend', function (e) {
            for (let i = 0; i < e.data.length; i++) {
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
    // Notification
    //
    $siv3dNotifications: [],

    siv3dRequestNotificationPermission: function(callback, callbackArg) {
        if (Notification.permission === "granted") {
            {{{ makeDynCall('vii', 'callback') }}}(1 /* NotificationPermission.Granted */, callbackArg);
        } else {
            Notification.requestPermission().then(function(v) {
                if (v === "granted") {
                    {{{ makeDynCall('vii', 'callback') }}}(1 /* NotificationPermission.Granted */, callbackArg);
                } else {
                    {{{ makeDynCall('vii', 'callback') }}}(2 /* NotificationPermission.Denied */, callbackArg);
                }
            });
        }
    },
    siv3dRequestNotificationPermission__sig: "vii",

    siv3dCreateNotification: function(title, body, actionsNum, actionTexts, callback, callbackArg) {
        if (!window.Notification && Notification.permission !== "granted") {
            {{{ makeDynCall('vii', 'callback') }}}(0, callbackArg);
            return 0;
        }

        const idx = GL.getNewId(siv3dNotifications);

        const titleText = UTF8ToString(title);
        const bodyText = UTF8ToString(body);
        let actions = [];

        for (let i = 0; i < actionsNum; i++) {
            const textPtr = getValue(actionTexts + i * 4, "i32");
            const actionText = UTF8ToString(textPtr);

            actions.push({ title: actionText, action: actionText });
        }

        siv3dRegisterUserAction(function () {
            siv3dNotifications[idx] = new Notification(titleText, { body: bodyText, actions: actions })
            {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
        }); 

        return idx;
    },
    siv3dCreateNotification__sig: "iiiiiii",
    siv3dCreateNotification__deps: [ "$siv3dRegisterUserAction", "$siv3dNotifications" ],

    siv3dRegisterNotificationCallback: function(id, callback, callbackArg) {
        const notificattion = siv3dNotifications[id];

        notificattion.onclick = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 1 /* ToastNotificationState.Activated */, callbackArg);
        }
        notificattion.onshow = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 2 /* ToastNotificationState.Shown */, callbackArg);
        }
        notificattion.onclose = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 5 /* ToastNotificationState.TimedOut */, callbackArg);
        }
        notificattion.onerror = function() {
            {{{ makeDynCall('viii', 'callback') }}}(id, 6 /* ToastNotificationState.Error */, callbackArg);
        }
    },
    siv3dRegisterNotificationCallback__sig: "viii",
    siv3dRegisterNotificationCallback__deps: [ "$siv3dNotifications" ],

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

        for(let i = 0; i < voices.length; i++) {
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

        for (let i = 0; i < paramStrs.length; i++)
        {
            HEAP32[dataPos + i] = allocate(intArrayFromString(paramStrs[i]), ALLOC_NORMAL);
        }

        return dataPos * 4; // dataPos * sizeof(uint32_t)
    },
    siv3dGetURLParameters__sig: "iv",

    siv3dWebGPUConfigureSwapchain: function(deviceId, swapChainId, descriptor) {
        var device = WebGPU["mgrDevice"].get(deviceId);
        var swapChain = WebGPU["mgrSwapChain"].get(swapChainId);
        var width = {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.width, 'i32', false, true) }}};
        var height = {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.height, 'i32', false, true) }}};

        var desc = {
            "device": device,
            "format": WebGPU.TextureFormat[
                {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.format, 'i32', false, true) }}}],
            "usage": {{{ makeGetValue('descriptor', C_STRUCTS.WGPUSwapChainDescriptor.usage, 'i32', false, true) }}},
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
    siv3dRequestAnimationFrame: function() {
        Asyncify.handleSleep(function(wakeUp) {
            requestAnimationFrame(function() {
                wakeUp();
            });
        });
    },
    siv3dRequestAnimationFrame__sig: "v", 
    siv3dRequestAnimationFrame__deps: [ "$Asyncify" ],

    siv3dDecodeAudioFromFile: function(filePath, arg) {
        Asyncify.handleSleep(function(wakeUp) {
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

                wakeUp();
            };

            const onFailure = function() {
                HEAP32[(arg>>2)+0] = 0;
                HEAP32[(arg>>2)+1] = 0;
                HEAPU32[(arg>>2)+2] = 0;
                HEAPU32[(arg>>2)+3] = 0;

                wakeUp();
            }

            Module["SDL2"].audioContext.decodeAudioData(fileBytes.buffer, onSuccess, onFailure); 
        });
    },
    siv3dDecodeAudioFromFile__sig: "vii",
    siv3dDecodeAudioFromFile__deps: [ "$AL", "$FS", "$Asyncify" ],
#else
    siv3dRequestAnimationFrame: function() {
    },
    siv3dRequestAnimationFrame__sig: "v",

    siv3dDecodeAudioFromFile: function(_, arg) {
        HEAP32[(arg>>2)+0] = 0;
        HEAP32[(arg>>2)+1] = 0;
        HEAPU32[(arg>>2)+2] = 0;
        HEAPU32[(arg>>2)+3] = 0;
    },
    siv3dDecodeAudioFromFile__sig: "vii",
#endif
})