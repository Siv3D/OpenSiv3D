mergeInto(LibraryManager.library, {
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
    siv3dRegisterDragEnter__proxy: "sync",

    siv3dRegisterDragUpdate: function(ptr) {
        Module["canvas"]["ondragover"] = function (e) {
            e.preventDefault();
            const adusted = siv3dAdjustPoint(e.pageX, e.pageY);
            {{{ makeDynCall('vii', 'ptr') }}}(adusted.x, adusted.y);
        };
    },
    siv3dRegisterDragUpdate__sig: "vi",
    siv3dRegisterDragUpdate__proxy: "sync",
    siv3dRegisterDragUpdate__deps: [ "$siv3dAdjustPoint" ],

    siv3dRegisterDragExit: function(ptr) {
        Module["canvas"]["ondragexit"] = function (e) {
            e.preventDefault();
            {{{ makeDynCall('v', 'ptr') }}}();
        };
    },
    siv3dRegisterDragExit__sig: "vi",
    siv3dRegisterDragExit__proxy: "sync",

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
    siv3dRegisterDragDrop__proxy: "sync",
    siv3dRegisterDragDrop__deps: [ "$siv3dDragDropFileReader", "$FS" ],
});
