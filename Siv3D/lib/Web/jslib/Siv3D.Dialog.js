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
    siv3dInitDialog__proxy: "sync",
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
    siv3dOpenDialogAsync__proxy: "sync",
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
    siv3dDownloadFile__proxy: "sync",
    siv3dDownloadFile__deps: [ "$siv3dRegisterUserAction" ],
});
