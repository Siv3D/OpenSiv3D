mergeInto(LibraryManager.library, { 
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

    $siv3dOpenDialogAsync: function(filter, callback, futurePtr, acceptMuilitple) {
        siv3dInputElement.accept = filter;
        siv3dInputElement.multiple = acceptMuilitple;

        function cancelHandler(e) {
            {{{ makeDynCall('viii', 'callback') }}}(0, 0, futurePtr);
            _siv3dMaybeAwake();
        }

        // Using addEventListener works in Firefox
        // Set 'once' to automatically delete the handler when the event fires
        siv3dInputElement.addEventListener('cancel', cancelHandler, { once: true });

        siv3dInputElement.oninput = async function(e) {
            // Delete event handler if cancel event is not fired
            siv3dInputElement.removeEventListener('cancel', cancelHandler);

            // Workaround for event firing
            const files = [...e.target.files];
            e.target.value = '';

            if (files.length < 1) {
                callback(0, 0, futurePtr);
                _siv3dMaybeAwake();
                return;
            }

            let filePathes = [];
            const sp = stackSave();

            for (let file of files) {
                await new Promise((resolve) => {
                    const filePath = "/tmp/" + file.name;

                    siv3dDialogFileReader.addEventListener("load", function onLoaded() {
                        FS.writeFile(filePath, new Uint8Array(siv3dDialogFileReader.result));
        
                        const namePtr = allocate(intArrayFromString(filePath), ALLOC_STACK);
                        filePathes.push(namePtr);
                        
                        siv3dDialogFileReader.removeEventListener("load", onLoaded);
                        resolve();
                    });
        
                    siv3dDialogFileReader.readAsArrayBuffer(file);  
                });
            }

            const filePathesPtr = stackAlloc(filePathes.length * {{{ POINTER_SIZE }}});

            for (let i = 0; i < filePathes.length; i++) {
                setValue(filePathesPtr + i * {{{ POINTER_SIZE }}}, filePathes[i], "i32");
            }

            callback(filePathesPtr, filePathes.length, futurePtr);
            
            stackRestore(sp);
            _siv3dMaybeAwake();
        };

        siv3dRegisterUserAction(function() {
            siv3dInputElement.click();
        });
    },
    $siv3dOpenDialogAsync__deps: [ "$siv3dInputElement", "$siv3dDialogFileReader", "$siv3dRegisterUserAction", "$FS", "siv3dMaybeAwake" ],
    siv3dOpenDialogAsync: function(filterStr, callback, futurePtr, acceptMuilitple) {
        const filter = UTF8ToString(filterStr);
        const callbackFn = {{{ makeDynCall('viii', 'callback') }}};
        siv3dOpenDialogAsync(filter, callbackFn, futurePtr, !!acceptMuilitple);
    },
    siv3dOpenDialogAsync__sig: "vii",
    siv3dOpenDialogAsync__deps: [ "$siv3dOpenDialogAsync" ],

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
});
