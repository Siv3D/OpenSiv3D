mergeInto(LibraryManager.library, {
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
})