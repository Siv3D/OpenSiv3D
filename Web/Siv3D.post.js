(function () {
    const dependencyName = "WebGPU";

    addRunDependency(dependencyName);

    (async function() {
        try {
            const adapter = await navigator.gpu.requestAdapter();
            const device = await adapter.requestDevice();
    
            Module["preinitializedWebGPUDevice"] = device;
        } catch(_) {
            // ignore
        } finally {
            removeRunDependency(dependencyName);
        }
    })();

    if (Module["_emscripten_clear_interval"]) {
        Module["_emscripten_clear_interval"].sig = "vi";
    }
})();

__ATEXIT__.push(function() {
    if (Module["onRuntimeExit"]) {
      Module["onRuntimeExit"]();
    }
})
