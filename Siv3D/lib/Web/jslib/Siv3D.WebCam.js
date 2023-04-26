mergeInto(LibraryManager.library, {
    $videoElements: [],

    $siv3dOpenVideoStream: function(filename, callback, callbackArg) {
        const videoData = FS.readFile(UTF8ToString(fileName));
        const media_source = new MediaSource();
       
        const video = document.createElement("video");
        video["muted"] = true;
        video["autoplay"] = true;
        video["playsInline"] = true;

        media_source.addEventListener('sourceopen', function() {
            const source_buffer = media_source.addSourceBuffer('video/mp4');
			source_buffer.addEventListener("updateend", function () {
                media_source.endOfStream()
            });
			source_buffer.appendBuffer(videoData)
        });

        video.addEventListener('loadedmetadata', function onLoaded() {
            const idx = GL.getNewId(videoElements);

            video.removeEventListener('loadedmetadata', onLoaded);
            videoElements[idx] = video;

            if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
            _siv3dMaybeAwake();
        });

        video.src = URL.createObjectURL(media_source);
    },
    $siv3dOpenVideoStream__deps: [ "siv3dMaybeAwake" ],

    siv3dOpenVideo: function(fileName, callback, callbackArg) {
        const videoData = FS.readFile(UTF8ToString(fileName));
        const videoBlob = new Blob([ videoData ], { type: "video/mp4" });
       
        const video = document.createElement("video");
        video["muted"] = true;
        video["autoplay"] = true;
        video["playsInline"] = true;

        video.addEventListener('loadedmetadata', function onLoaded() {
            const idx = GL.getNewId(videoElements);

            video.removeEventListener('loadedmetadata', onLoaded);
            videoElements[idx] = video;

            if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
            _siv3dMaybeAwake();
        });

        video.src = URL.createObjectURL(videoBlob);
    },
    siv3dOpenVideo__sig: "viii",
    siv3dOpenVideo__proxy: "sync",
    siv3dOpenVideo__deps: [ "$FS", "$videoElements", "$siv3dRegisterUserAction", "siv3dMaybeAwake" ],

    siv3dOpenCamera: function(width, height, callback, callbackArg) {
        const constraint = {
            video: { 
                width : width > 0 ? width : undefined, 
                height: height > 0 ? height : undefined 
            },
            audio: false
        };

        navigator.mediaDevices.getUserMedia(constraint).then(
            function(stream) {
                const video = document.createElement("video");

                video["playsInline"] = true;          
                video.addEventListener('loadedmetadata', function onLoaded() {
                    const idx = GL.getNewId(videoElements);

                    video.removeEventListener('loadedmetadata', onLoaded);
                    videoElements[idx] = video;

                    if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
                    _siv3dMaybeAwake();
                });

                video.srcObject = stream;
            }
        ).catch(function(_) {
            if (callback) {{{ makeDynCall('vii', 'callback') }}}(0, callbackArg);
            _siv3dMaybeAwake();
        })
    },
    siv3dOpenCamera__sig: "viiii",
    siv3dOpenCamera__proxy: "sync",
    siv3dOpenCamera__deps: [ "$videoElements", "siv3dMaybeAwake" ],

    siv3dSetCameraResolution: function(idx, width, height, callback, callbackArg) {
        /** @type { HTMLVideoElement } */
        const video = videoElements[idx];
        /** @type { MediaStreamTrack } */
        const stream = video.srcObject.getVideoTracks()[0];

        const constraint = {
            video: { width, height },
            audio: false
        };

        stream.applyConstraints(constraint).then(
            function () {
                if (callback) {{{ makeDynCall('vii', 'callback') }}}(idx, callbackArg);
                _siv3dMaybeAwake();
            }
        );
    },
    siv3dSetCameraResolution__sig: "viiiii",
    siv3dSetCameraResolution__proxy: "sync",
    siv3dSetCameraResolution__deps: [ "$videoElements", "siv3dMaybeAwake" ],

    siv3dQueryCameraAvailability: function () {
        return !!navigator.getUserMedia;
    },
    siv3dQueryCameraAvailability__sig: "iv",
    siv3dQueryCameraAvailability__proxy: "sync",

    siv3dRegisterVideoTimeUpdateCallback: function(idx, callback, callbackArg) {
        const video = videoElements[idx];

        if (callback) {
            video.ontimeupdate = function() {
                {{{ makeDynCall('vi', 'callback') }}}(callbackArg);
                _siv3dMaybeAwake();
            }
        } else {
            video.ontimeupdate = null;
        }
    },
    siv3dRegisterVideoTimeUpdateCallback__sig: "viii",
    siv3dRegisterVideoTimeUpdateCallback__proxy: "sync",
    siv3dRegisterVideoTimeUpdateCallback__deps: [ "$videoElements", "siv3dMaybeAwake" ], 

    siv3dCaptureVideoFrame: function(target, level, internalFormat, width, height, border, format, type, idx) {
        const video = videoElements[idx];
        GLctx.texSubImage2D(target, level, 0, 0, width, height, format, type, video);
    },
    siv3dCaptureVideoFrame__sig: "viiiiiiiii",
    siv3dCaptureVideoFrame__proxy: "sync",
    siv3dCaptureVideoFrame__deps: ["$videoElements"],

    siv3dQueryVideoPlaybackedTime: function(idx) {
        const video = videoElements[idx];
        return video.currentTime;
    },
    siv3dQueryVideoPlaybackedTime__sig: "di",
    siv3dQueryVideoPlaybackedTime__proxy: "sync",
    siv3dQueryVideoPlaybackedTime__deps: ["$videoElements"],

    siv3dSetVideoPlaybackedTime: function(idx, time) {
        const video = videoElements[idx];
        video.currentTime = time;
    },
    siv3dSetVideoPlaybackedTime__sig: "vid",
    siv3dSetVideoPlaybackedTime__proxy: "sync",
    siv3dSetVideoPlaybackedTime__deps: ["$videoElements"],

    siv3dQueryVideoDuration: function(idx) {
        const video = videoElements[idx];
        return video.duration;
    },
    siv3dQueryVideoDuration__sig: "di",
    siv3dQueryVideoDuration__proxy: "sync",
    siv3dQueryVideoDuration__deps: ["$videoElements"],

    siv3dQueryVideoEnded: function(idx) {
        const video = videoElements[idx];
        return video.ended;
    },
    siv3dQueryVideoEnded__sig: "ii",
    siv3dQueryVideoEnded__proxy: "sync",
    siv3dQueryVideoEnded__deps: ["$videoElements"],

    siv3dQueryVideoPreference: function(idx, width, height, fps) {
        const video = videoElements[idx];

        setValue(width, video.videoWidth, 'i32');
        setValue(height, video.videoHeight, 'i32');
        setValue(fps, 29.7, 'double');
    },
    siv3dQueryVideoPlaybackedTime__sig: "viiii",
    siv3dQueryVideoPlaybackedTime__proxy: "sync",
    siv3dQueryVideoPlaybackedTime__deps: ["$videoElements"],

    siv3dPlayVideo: function(idx) {
        const video = videoElements[idx];
        
        video.play().catch(function () {
                siv3dRegisterUserAction(function() {
                    video.play();
                })
            }
        );
    },
    siv3dPlayVideo__sig: "vi",
    siv3dPlayVideo__proxy: "sync",
    siv3dPlayVideo__deps: ["$videoElements"],

    siv3dStopVideo: function(idx) {
        const video = videoElements[idx];
        video.pause();
    },
    siv3dStopVideo__sig: "vi",
    siv3dStopVideo__proxy: "sync",
    siv3dStopVideo__deps: ["$videoElements"],

    siv3dDestroyVideo: function(idx) {
        _siv3dStopVideo(idx);

        const video = videoElements[idx];
        if (!!video.src) {
            URL.revokeObjectURL(video.src);
        }

        delete videoElements[idx];
    },
    siv3dDestroyVideo__sig: "vi",
    siv3dDestroyVideo__proxy: "sync",
    siv3dDestroyVideo__deps: ["$videoElements", "siv3dStopVideo"],
});
