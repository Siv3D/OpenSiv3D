(function() {
    Module["locateFile"] = function(url) {
        const scriptUrl = document.currentScript.src;
        return scriptUrl.substr(0, scriptUrl.lastIndexOf("/") + 1) + url;
    }
    const libs = Module["dynamicLibraries"];
    Module["dynamicLibraries"] = [];
    libs.forEach(lib => Module["dynamicLibraries"] += Module["locateFile"](lib));
})();
// This is meaningless, but occurs runtime error without this...
var _SDL_CloseAudio=function(){};
