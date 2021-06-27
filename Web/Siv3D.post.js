(function () {
    const dependencyName = "WebGPU";

    (async function() {
        const adapter = await navigator.gpu.requestAdapter();
        const device = await adapter.requestDevice();

        Module["preinitializedWebGPUDevice"] = device;
        removeRunDependency(dependencyName);
    })();

    addRunDependency(dependencyName);
})()
    