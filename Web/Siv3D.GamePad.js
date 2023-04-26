mergeInto(LibraryManager.library, {
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
});
