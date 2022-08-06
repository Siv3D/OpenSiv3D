(function () {
    const dependencyName = "WebGPU";

    addRunDependency(dependencyName);

    (async function() {
        try {
            const adapter = await navigator.gpu.requestAdapter();
            const device = await adapter.requestDevice();
    
            Module["preinitializedWebGPUDevice"] = device;
        } finally {
            removeRunDependency(dependencyName);
        }
    })();

    if (findEventTarget) {
        findEventTarget = new Proxy(findEventTarget, {
            apply(target, thisArg, argumentsList) {
                const elementTarget = maybeCStringToJsString(argumentsList[0]);
                if (elementTarget === "canvas") {
                    return new Proxy(Module["canvas"], {
                        get(target, prop, receiver) {
                            if (prop === "getContext") {
                                return function(contextName) {
                                    if (contextName === "gpupresent") {
                                        contextName = "webgpu";
                                    }
                
                                    const context = target[prop](contextName);

                                    if (contextName == "webgpu" && !Module["preinitializedWebGPUDevice"]) {
                                        window.alert("WebGPU is not enabled!");
                                        throw new Error("WebGPU is not enabled!");
                                    }
                
                                    return new Proxy(context, {
                                        get(target, prop, receiver) {
                                            if (prop === "configureSwapChain") {
                                                return function(config) {
                                                    target["configure"](config);
                                                    return target;
                                                }
                                            }
                                            
                                            const result = target[prop];
                                            return typeof result === "function" ? result.bind(target) : result;
                                        }
                                    })
                                }
                            }
                
                            const result = target[prop];
                            return typeof result === "function" ? result.bind(target) : result;
                        },
                        set(obj, prop, value) {
                            obj[prop] = value;
                        }
                    })
                } else {
                    return target.apply(thisArg, argumentsList);
                }
            }
        })
    }

    runtimeKeepalivePush();
})();
