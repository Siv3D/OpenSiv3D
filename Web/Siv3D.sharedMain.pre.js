(function() {
    const scriptUrl = document.currentScript.src;
    const scriptUrlRoot = scriptUrl.substr(0, scriptUrl.lastIndexOf("/") + 1);
    Module["locateFile"] = function(url) {
        return scriptUrlRoot + url;
    }
    const libs = Module["dynamicLibraries"];
    Module["dynamicLibraries"] = [];
    libs.forEach(lib => Module["dynamicLibraries"] += Module["locateFile"](lib));
})();
// This is meaningless, but occurs runtime error without this...
var _SDL_CloseAudio=function(){};
