mergeInto(LibraryManager.library, {
    $siv3dXMLHTTPRequestList: [],
    $siv3dXMLHTTPRequestListNextID: 0,

    siv3dCreateXMLHTTPRequest: function() {
        const id = siv3dXMLHTTPRequestListNextID++;
        siv3dXMLHTTPRequestList[id] = new XMLHttpRequest();
        return id;
    },
    siv3dCreateXMLHTTPRequest__sig: "vi",
    siv3dCreateXMLHTTPRequest__proxy: "sync",
    siv3dCreateXMLHTTPRequest__deps: [ "$siv3dXMLHTTPRequestList", "$siv3dXMLHTTPRequestListNextID" ],

    siv3dSetXMLHTTPRequestWriteBackFile: function(id, fileNamePtr) {
        const http = siv3dXMLHTTPRequestList[id];
        const _file = UTF8ToString(fileNamePtr);

        http.addEventListener("load", function() {
            const index = _file.lastIndexOf('/');
            const destinationDirectory = PATH.dirname(_file);
            
            if (http.status >= 200 && http.status < 300) {
                // if a file exists there, we overwrite it
                try {
                    FS.unlink(_file);
                } catch (e) {}
                // if the destination directory does not yet exist, create it
                FS.mkdirTree(destinationDirectory);
                FS.createDataFile( _file.substr(0, index), _file.substr(index + 1), new Uint8Array(/** @type{ArrayBuffer}*/(http.response)), true, true, false);
            }
        });
    },
    siv3dSetXMLHTTPRequestWriteBackFile__sig: "vii",
    siv3dSetXMLHTTPRequestWriteBackFile__proxy: "sync",
    siv3dSetXMLHTTPRequestWriteBackFile__deps: [ "$siv3dXMLHTTPRequestList" ],

    siv3dSetXMLHTTPRequestCallback: function(id, fnPtr, userDataPtr) {
        siv3dXMLHTTPRequestList[id].addEventListener("load", function() {
            {{{ makeDynCall("vii", "fnPtr") }}}(id, userDataPtr);
        });
    },
    siv3dSetXMLHTTPRequestCallback__sig: "viii",
    siv3dSetXMLHTTPRequestCallback__proxy: "sync",
    siv3dSetXMLHTTPRequestCallback__deps: [ "$siv3dXMLHTTPRequestList" ],

    siv3dSetXMLHTTPRequestErrorCallback: function(id, fnPtr, userDataPtr) {
        siv3dXMLHTTPRequestList[id].addEventListener("error", function() {
            {{{ makeDynCall("vii", "fnPtr") }}}(id, userDataPtr);
        });
    },
    siv3dSetXMLHTTPRequestErrorCallback__sig: "viii",
    siv3dSetXMLHTTPRequestErrorCallback__proxy: "sync",
    siv3dSetXMLHTTPRequestErrorCallback__deps: [ "$siv3dXMLHTTPRequestList" ],

    siv3dSetXMLHTTPRequestProgressCallback: function(id, fnPtr, userDataPtr) {
        siv3dXMLHTTPRequestList[id].addEventListener("progress", function(e) {
            {{{ makeDynCall("viiii", "fnPtr") }}}(id, userDataPtr, e.total, e.loaded);
        });
    },
    siv3dSetXMLHTTPRequestProgressCallback__sig: "viii",
    siv3dSetXMLHTTPRequestProgressCallback__proxy: "sync",
    siv3dSetXMLHTTPRequestProgressCallback__deps: [ "$siv3dXMLHTTPRequestList" ],

    siv3dSetXMLHTTPRequestRequestHeader: function(id, namePtr, dataPtr) {
        const name = UTF8ToString(namePtr);
        const data = UTF8ToString(dataPtr);
        siv3dXMLHTTPRequestList[id].setRequestHeader(name, data);
    },
    siv3dSetXMLHTTPRequestRequestHeader__sig: "viii",
    siv3dSetXMLHTTPRequestRequestHeader__proxy: "sync",
    siv3dSetXMLHTTPRequestRequestHeader__deps: [ "$siv3dXMLHTTPRequestList" ],

    siv3dGetXMLHTTPRequestResponseHeaders: function(id) {
        const http = siv3dXMLHTTPRequestList[id];
        const responseHeaders = http.getAllResponseHeaders();
        return allocate(intArrayFromString(`HTTP/1.1 ${http.status} ${http.statusText}\r\n${responseHeaders}`), ALLOC_NORMAL);
    },
    siv3dGetXMLHTTPRequestResponseHeaders__sig: "ii",
    siv3dGetXMLHTTPRequestResponseHeaders__proxy: "sync",
    siv3dGetXMLHTTPRequestResponseHeaders__deps: [ "$siv3dXMLHTTPRequestList" ],

    siv3dSendXMLHTTPRequest: function(id, dataPtr) {
        {{{ runtimeKeepalivePush() }}}

        siv3dXMLHTTPRequestList[id].addEventListener("load", function() {
            {{{ runtimeKeepalivePop() }}}
        });
        siv3dXMLHTTPRequestList[id].addEventListener("error", function() {
            {{{ runtimeKeepalivePop() }}}
        });

        const data = dataPtr ? UTF8ToString(dataPtr) : null;
        siv3dXMLHTTPRequestList[id].send(data);
    },
    siv3dSendXMLHTTPRequest__sig: "vii",
    siv3dSendXMLHTTPRequest__proxy: "sync",
    siv3dSendXMLHTTPRequest__deps: [ "$siv3dXMLHTTPRequestList" ],

    siv3dOpenXMLHTTPRequest: function(id, methodPtr, urlPtr) {
        const http = siv3dXMLHTTPRequestList[id];
        const method = UTF8ToString(methodPtr);
        const url = UTF8ToString(urlPtr);
        
        http.open(method, url, true);
        http.responseType = "arraybuffer";

        if (method == "POST") {
            http.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        }
    },
    siv3dOpenXMLHTTPRequest__sig: "viii",
    siv3dOpenXMLHTTPRequest__proxy: "sync",
    siv3dOpenXMLHTTPRequest__deps: [ "$siv3dXMLHTTPRequestList" ],

    siv3dAbortXMLHTTPRequest: function(id) {
        siv3dXMLHTTPRequestList[id].abort();
    },
    siv3dAbortXMLHTTPRequest__sig: "vi",
    siv3dAbortXMLHTTPRequest__proxy: "sync",
    siv3dAbortXMLHTTPRequest__deps: [ "$siv3dXMLHTTPRequestList" ],

    siv3dDeleteXMLHTTPRequest: function(id, methodPtr, urlPtr) {
        delete siv3dXMLHTTPRequestList[id];
    },
    siv3dDeleteXMLHTTPRequest__sig: "viii",
    siv3dDeleteXMLHTTPRequest__proxy: "sync",
    siv3dDeleteXMLHTTPRequest__deps: [ "$siv3dXMLHTTPRequestList" ],
});
