(function() 
{
    Module["onAbort"] = function(e) 
    {
        if (e instanceof WebAssembly.CompileError)
        {
            const additionalMessage = 
                "WebAssembly compilation failed. \
Maybe some webassembly features are required to execute this program. \
Please refer https://webassembly.org/roadmap/ to check which webassembly features are supported in your brouser. \
\
Original Error: " + e;
            
            window.alert(additionalMessage);
        }
        else
        {
            window.alert(e)
        }
    }
})();
