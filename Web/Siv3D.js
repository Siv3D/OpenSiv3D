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
            window.keysBuffer = Module._malloc(349 /* GLFW_KEY_LAST + 1 */)
        }
        Module.HEAPU8.set(window.keys, window.keysBuffer);
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
        setValue(w, 0, 'i32');
        setValue(h, 0, 'i32');
    },
    glfwGetMonitorInfo_Siv3D__sig: "viiiiiiiiiii",

    glfwGetMonitorWorkarea: function(handle, wx, wy, ww, wh) {
        setValue(wx, 0, 'i32');
        setValue(wy, 0, 'i32');
        setValue(ww, 1280, 'i32');
        setValue(wh, 720, 'i32');
    },
    glfwGetMonitorWorkarea__sig: "viiiii",

    glfwGetMonitorContentScale: function(handle, xscale, yscale) {
        setValue(xscale, 1, 'float');
        setValue(yscale, 1, 'float'); 
    },
    glfwGetMonitorContentScale__sig: "viii",

    siv3dSetCursorStyle: function(style) {
        const styleText = UTF8ToString(style);
        Module["canvas"].style.cursor = styleText;
    },
    siv3dSetCursorStyle__sig: "vi",

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
        Module["canvas"].ondragenter = function (e) {
            e.preventDefault();

            const types = e.dataTransfer.types;

            if (types.length > 0) {
                {{{ makeDynCall('vi', 'ptr') }}}(types[0] === 'Files' ? 1 : 0);
            }        
        };
    },
    siv3dRegisterDragEnter__sig: "vi",

    siv3dRegisterDragUpdate: function(ptr) {
        Module["canvas"].ondragover = function (e) {
            e.preventDefault();
            {{{ makeDynCall('v', 'ptr') }}}();
        };
    },
    siv3dRegisterDragUpdate__sig: "vi",

    siv3dRegisterDragExit: function(ptr) {
        Module["canvas"].ondragexit = function (e) {
            e.preventDefault();
            {{{ makeDynCall('v', 'ptr') }}}();
        };
    },
    siv3dRegisterDragExit__sig: "vi",

    $siv3dDragDropFileReader: null,
    siv3dRegisterDragDrop: function(ptr) {
        Module["canvas"].ondrop = function (e) {
            e.preventDefault();

            const items = e.dataTransfer.items;

            if (items.length == 0) {
                return;
            }

            if (items[0].kind === 'text') {
                items[0].getAsString(function(str) {
                    const strPtr = allocate(intArrayFromString(str), ALLOC_NORMAL);
                    {{{ makeDynCall('vi', 'ptr') }}}(strPtr);
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
                    {{{ makeDynCall('vi', 'ptr') }}}(namePtr);

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

    siv3dOpenVideo: function(fileName) {

    },
    siv3dOpenVideo__sig: "vi",

    siv3dOpenCamera: function(width, height, callback, callbackArg) {
        const constraint = {
            video: { width, height },
            audio: false
        };

        navigator.mediaDevices.getUserMedia(constraint).then(
            stream => {
                const video = document.createElement("video");

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

    siv3dCaptureVideoFrame: function(target, level, internalFormat, width, height, border, format, type, idx) {
        const video = videoElements[idx];
        GLctx.texImage2D(target, level, internalFormat, width, height, border, format, type, video);
    },
    siv3dCaptureVideoFrame__sig: "viiiiiiiii",
    siv3dCaptureVideoFrame__deps: ["$videoElements"],

    siv3dQueryVideoPlaybackedTime: function(idx) {
        const video = videoElements[idx];
        return video.currentTime;
    },
    siv3dQueryVideoPlaybackedTime__sig: "di",
    siv3dQueryVideoPlaybackedTime__deps: ["$videoElements"],

    siv3dPlayVideo: function(idx) {
        const video = videoElements[idx];
        video.play();
    },
    siv3dPlayVideo__sig: "vi",
    siv3dPlayVideo__deps: ["$videoElements"],

    siv3dStopVideo: function(idx) {
        const video = videoElements[idx];

        let stream = video.srcObject;
        let tracks = stream.getTracks();
      
        tracks.forEach(function(track) {
            track.stop();
        });
    },
    siv3dStopVideo__sig: "vi",
    siv3dStopVideo__deps: ["$videoElements"],

    siv3dDestroyVideo: function(idx) {
        _siv3dStopVideo(idx);
        delete videoElements[idx];
    },
    siv3dDestroyVideo__sig: "vi",
    siv3dDestroyVideo__deps: ["$videoElements"],
})