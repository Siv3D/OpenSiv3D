mergeInto(LibraryManager.library, {
    $siv3dTextInputElement: null,
    $siv3dTextInputCompositionRange: null,

    siv3dInitTextInput: function() {
        const textInput = document.createElement("div");
        textInput.contentEditable = true;
        textInput.style.position = "absolute";
        textInput.style.zIndex = -2;
        textInput.style.whiteSpace = "pre-wrap";
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
    siv3dInitTextInput__proxy: "sync",
    siv3dInitTextInput__proxy: "sync",
    siv3dInitTextInput__deps: [ "$siv3dTextInputElement" ],

    siv3dRegisterTextInputCallback: function(callback) {
        let composing = false;
        let insertCompositionTextInvoked = false;

        siv3dTextInputElement.addEventListener('input', function (e) {
            if (e.isComposing || composing) {
                return;
            }

            if (e.inputType == "insertText") {
                if (e.data) {
                    for (var i = 0; i < e.data.length; i++) {
                        const codePoint = e.data.charCodeAt(i);
                        {{{ makeDynCall('vi', 'callback') }}}(codePoint);
                    }
                }
            } else if (e.inputType == "insertFromPaste") {
                if (e.data) {
                    for (var i = 0; i < e.data.length; i++) {
                        const codePoint = e.data.charCodeAt(i);
                        {{{ makeDynCall('vi', 'callback') }}}(codePoint);
                    }
                } else {
                    navigator.clipboard.readText().then(
                        data => {
                            for (var i = 0; i < data.length; i++) {
                                const codePoint = data.charCodeAt(i);
                                {{{ makeDynCall('vi', 'callback') }}}(codePoint);
                            }
                        }
                    );
                }
            } else if (e.inputType == "deleteContentBackward") {
                {{{ makeDynCall('vi', 'callback') }}}(8);
            } else if (e.inputType == "deleteContentForward") {
                {{{ makeDynCall('vi', 'callback') }}}(0x7F);
            }
        });
        siv3dTextInputElement.addEventListener('beforeinput', function (e) {
            if (e.inputType == "insertCompositionText" || (composing && e.inputType == "insertText")) {
                siv3dTextInputCompositionRange = e.getTargetRanges()[0];

                if (!insertCompositionTextInvoked && !!siv3dTextInputCompositionRange) {
                    const length = siv3dTextInputCompositionRange.endOffset - siv3dTextInputCompositionRange.startOffset;
                    for (var i = 0; i < length; i++) {
                        {{{ makeDynCall('vi', 'callback') }}}(8);
                    }
                }
                insertCompositionTextInvoked = true;
            }
        });
        siv3dTextInputElement.addEventListener('compositionstart', function (e) {
            composing = true;
            insertCompositionTextInvoked = false;
        });
        siv3dTextInputElement.addEventListener('compositionend', function (e) {
            composing = false;
            siv3dTextInputCompositionRange = null;
            for (var i = 0; i < e.data.length; i++) {
                const codePoint = e.data.charCodeAt(i);
                {{{ makeDynCall('vi', 'callback') }}}(codePoint);
            }
        });
    },
    siv3dRegisterTextInputCallback__sig: "vi",
    siv3dRegisterTextInputCallback__proxy: "sync",
    siv3dRegisterTextInputCallback__proxy: "sync",
    siv3dRegisterTextInputCallback__deps: [ "$siv3dTextInputElement", "$siv3dTextInputCompositionRange" ],

    siv3dGetTextInputCompositionRange: function(start, end) {
        if (siv3dTextInputCompositionRange) {
            setValue(start, siv3dTextInputCompositionRange.startOffset, 'i32');
            setValue(end, siv3dTextInputCompositionRange.endOffset, 'i32');
        } else {
            setValue(start, 0, 'i32');
            setValue(end, 0, 'i32');
        }
    },
    siv3dGetTextInputCompositionRange__sig: "vii",
    siv3dGetTextInputCompositionRange__proxy: "sync",
    siv3dGetTextInputCompositionRange__proxy: "sync",
    siv3dGetTextInputCompositionRange__deps: [ "$siv3dTextInputCompositionRange" ],

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
    siv3dRegisterTextInputMarkedCallback__proxy: "sync",
    siv3dRegisterTextInputMarkedCallback__proxy: "sync",
    siv3dRegisterTextInputMarkedCallback__deps: [ "$siv3dTextInputElement" ],

    siv3dRequestTextInputFocus: function(isFocusRequired) {
        const isFocusRequiredBool = isFocusRequired != 0;

        if (isFocusRequiredBool) {
            if (document.activeElement != siv3dTextInputElement) {
                siv3dRegisterUserAction(function () {
                    siv3dTextInputElement.focus();
                });
            }
        } else {
            if (document.activeElement == siv3dTextInputElement) {
                siv3dRegisterUserAction(function () {
                    siv3dTextInputElement.blur();
                });
            }
        }
    },
    siv3dRequestTextInputFocus__sig: "vi",
    siv3dRequestTextInputFocus__proxy: "sync",
    siv3dRequestTextInputFocus__sync: "sync",
    siv3dRequestTextInputFocus__deps: [ "$siv3dRegisterUserAction", "$siv3dTextInputElement" ],

    siv3dSetTextInputText: function(ptr) {
        /** @type { string } */
        const newText = UTF8ToString(ptr);
        siv3dTextInputElement.textContent = " ".repeat(newText.length);
    },
    siv3dSetTextInputText__sig: "vi",
    siv3dSetTextInputText__proxy: "sync",
    siv3dSetTextInputText__proxy: "sync",
    siv3dSetTextInputText__deps: [ "$siv3dTextInputElement" ],

    siv3dSetTextInputCursor: function(index) {
        const targetTextNode = siv3dTextInputElement.childNodes[0];

        if (!targetTextNode) {
            return;
        }

        const selection = window.getSelection();
        const range = document.createRange();

        range.selectNode(targetTextNode);
        range.setStart(targetTextNode, index);
        range.setEnd(targetTextNode, index);

        selection.removeAllRanges();
        selection.addRange(range);
    },
    siv3dSetTextInputCursor__sig: "vi",
    siv3dSetTextInputCursor__proxy: "sync",
    siv3dSetTextInputCursor__proxy: "proxy",
    siv3dSetTextInputCursor__deps: [ "$siv3dTextInputElement" ],

    siv3dGetTextInputCursor: function() {
        const selection = window.getSelection();
        const targetTextNode = siv3dTextInputElement.childNodes[0];

        if (selection.focusNode == targetTextNode) {
            return selection.focusOffset;
        } else {
            return 0;
        }
    },
    siv3dGetTextInputCursor__sig: "iv",
    siv3dGetTextInputCursor__proxy: "sync",
    siv3dGetTextInputCursor__proxy: "sync",
    siv3dGetTextInputCursor__deps: [ "$siv3dTextInputElement" ],

    $siv3dGetTextInputFocused: function() {
        return document.activeElement == siv3dTextInputElement;
    },
    $siv3dGetTextInputFocused__deps: [ "$siv3dTextInputElement" ],
});
