mergeInto(LibraryManager.library, {
    $siv3dAllowedKeyBindings: [],

    siv3dAddAllowedKeyBinding: function(keyCode, ctrlKey, shiftKey, altKey, metaKey, allowed) {
        const key = {
            keyCode,
            ctrlKey: !!ctrlKey, shiftKey: !!shiftKey, altKey: !!altKey, metaKey: !!metaKey
        };

        function compareObject(obj) {
            return JSON.stringify(obj) == JSON.stringify(key);
        }

        const index = siv3dAllowedKeyBindings.findIndex(compareObject);

        if (allowed) {
            if (index === -1) {
                siv3dAllowedKeyBindings.push(key);
            }
        } else {
            if (index !== -1) {
                delete siv3dAllowedKeyBindings[index];
            }
        }
    },
    siv3dAddAllowedKeyBinding__sig: "viiiiii",
    siv3dAddAllowedKeyBinding__proxy: "sync",
    siv3dAddAllowedKeyBinding__deps: [ "$siv3dAllowedKeyBindings" ],

    siv3dDisableAllKeyBindings: function(disabled) {
        function onKeyEvent(e) {
            if (siv3dGetTextInputFocused()) {
                return;
            }

            const key = {
                keyCode: GLFW.DOMToGLFWKeyCode(e.keyCode),
                ctrlKey: e.ctrlKey, shiftKey: e.shiftKey, altKey: e.altKey, metaKey: e.metaKey
            };

            function compareObject(obj) {
                return JSON.stringify(obj) == JSON.stringify(key);
            }
    
            const index = siv3dAllowedKeyBindings.findIndex(compareObject);

            if (index === -1) {
                e.preventDefault();
            }
        }

        if (disabled) {
            window.addEventListener("keydown", onKeyEvent);
        } else {
            window.removeEventListener("keydown", onKeyEvent);
        }
    },
    siv3dDisableAllKeyBindings__sig: "vi",
    siv3dDisableAllKeyBindings__proxy: "sync",
    siv3dDisableAllKeyBindings__deps: [ "$siv3dAllowedKeyBindings", "$siv3dGetTextInputFocused" ],
});
