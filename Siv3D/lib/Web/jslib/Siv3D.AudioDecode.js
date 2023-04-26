mergeInto(LibraryManager.library, {
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
            _siv3dMaybeAwake();
        };

        const onFailure = function() {
            HEAP32[(arg>>2)+0] = 0;
            HEAP32[(arg>>2)+1] = 0;
            HEAPU32[(arg>>2)+2] = 0;
            HEAPU32[(arg>>2)+3] = 0;

            {{{ makeDynCall('vi', 'callback') }}}(arg);
            _siv3dMaybeAwake();
        }

        Module["SDL2"].audioContext.decodeAudioData(fileBytes.buffer, onSuccess, onFailure);   
    },
    siv3dDecodeAudioFromFileAsync__sig: "viii",
    siv3dDecodeAudioFromFileAsync__proxy: "sync",
    siv3dDecodeAudioFromFileAsync__deps: [ "$AL", "$FS", "siv3dMaybeAwake" ],
});
