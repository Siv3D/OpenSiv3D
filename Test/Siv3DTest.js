Module.preRun = [
  function () 
  {
    FS.mkdir('/test');
    FS.mount(NODEFS, { root: '../../Test/test' }, '/test');

    FS.mkdir('/resources');
    FS.mount(NODEFS, { root: './resources' }, '/resources');

    //
    // Mock Implementations 
    //
    global.navigator = {
      getGamepads() { return []; }
    }

    global.window = {
      addEventListener() {},
      removeEventListener() {}
    }

    global.document = {
      createElement() { return {}; }
    }
    
    Module.canvas = {
      style: {},
      addEventListener() {},
      removeEventListener() {}
    }
  }
]
