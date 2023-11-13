//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once

# ifdef SIV3D_MOCK_INPLEMENTATION

# define WasmBindgenConcatenate(x, y) x##y
# define WasmBindgenConcatenateMacro(x, y)     WasmBindgenConcatenate(x, y)

# define WasmBindgenReverseIndexSequence() 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
# define WasmBindgenTupleSizeHelper(\
        Arg1,  Arg2,  Arg3,  Arg4,  Arg5,  Arg6,  Arg7,  Arg8,  Arg9,  Arg10, \
        Arg11, Arg12, Arg13, Arg14, Arg15, Arg16, N, ...) N
# define WasmBindgenTupleSizeImpl(...)      WasmBindgenTupleSizeHelper(__VA_ARGS__)
# define WasmBindgenTupleSize(...)        WasmBindgenTupleSizeImpl(__VA_ARGS__ __VA_OPT__(,) WasmBindgenReverseIndexSequence())
# define WasmBindgenForEachImpl_0( Functor, ...      ) 
# define WasmBindgenForEachImpl_1( Functor, Arg1, ...) Functor(Arg1, 1)
# define WasmBindgenForEachImpl_2( Functor, Arg1, ...) Functor(Arg1, 2), WasmBindgenForEachImpl_1( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_3( Functor, Arg1, ...) Functor(Arg1, 3), WasmBindgenForEachImpl_2( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_4( Functor, Arg1, ...) Functor(Arg1, 4), WasmBindgenForEachImpl_3( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_5( Functor, Arg1, ...) Functor(Arg1, 5), WasmBindgenForEachImpl_4( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_6( Functor, Arg1, ...) Functor(Arg1, 6), WasmBindgenForEachImpl_5( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_7( Functor, Arg1, ...) Functor(Arg1, 7), WasmBindgenForEachImpl_6( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_8( Functor, Arg1, ...) Functor(Arg1, 8), WasmBindgenForEachImpl_7( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_9( Functor, Arg1, ...) Functor(Arg1, 9), WasmBindgenForEachImpl_8( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_10( Functor, Arg1, ...) Functor(Arg1, 10), WasmBindgenForEachImpl_9( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_11( Functor, Arg1, ...) Functor(Arg1, 11), WasmBindgenForEachImpl_10( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_12( Functor, Arg1, ...) Functor(Arg1, 12), WasmBindgenForEachImpl_11( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_13( Functor, Arg1, ...) Functor(Arg1, 13), WasmBindgenForEachImpl_12( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_14( Functor, Arg1, ...) Functor(Arg1, 14), WasmBindgenForEachImpl_13( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_15( Functor, Arg1, ...) Functor(Arg1, 15), WasmBindgenForEachImpl_14( Functor, __VA_ARGS__)
# define WasmBindgenForEachImpl_16( Functor, Arg1, ...) Functor(Arg1, 16), WasmBindgenForEachImpl_15( Functor, __VA_ARGS__)

# define WasmBindgenForEach(Functor, ...) \
    WasmBindgenConcatenateMacro(WasmBindgenForEachImpl_, WasmBindgenTupleSize(__VA_ARGS__))(Functor, __VA_ARGS__)

# define SIV3D_MOCK_GENERATE_PARAMETERS_NAME(Type, Index) Type arg##Index
# define SIV3D_MOCK_PARAMETERS_NAME(...) WasmBindgenForEach(SIV3D_MOCK_GENERATE_PARAMETERS_NAME, __VA_ARGS__)

# define SIV3D_MOCK_GENERATE_PARAMETERS(Type, Index) arg##Index
# define SIV3D_MOCK_PARAMETERS(...) WasmBindgenForEach(SIV3D_MOCK_GENERATE_PARAMETERS, __VA_ARGS__)

# define SIV3D_MOCK_FUNCTION(FunctionName, ReturnType, ...) \
    __attribute__((import_name(#FunctionName))) \
    ReturnType Original_##FunctionName (__VA_ARGS__); \
    ReturnType (*MockFunction_##FunctionName)(__VA_ARGS__) = nullptr; \
    void SetMockFunction_##FunctionName(ReturnType (*mockFunction)(__VA_ARGS__)) \
    { \
        MockFunction_##FunctionName = mockFunction; \
    } \
    extern "C" ReturnType FunctionName (SIV3D_MOCK_PARAMETERS_NAME(__VA_ARGS__))  \
    { \
        if (MockFunction_##FunctionName) \
            return (*MockFunction_##FunctionName)(SIV3D_MOCK_PARAMETERS(__VA_ARGS__)); \
        else \
            return Original_##FunctionName(SIV3D_MOCK_PARAMETERS(__VA_ARGS__)); \
    }
    

# define SIV3D_MOCK_RETURN_VALUE(FunctionName, ReturnType, ...) \
    Optional<ReturnType> ReturnValue_##FunctionName = none; \
    void SetReturnValue_##FunctionName(Optional<ReturnType> mockReturnValue) \
    { \
        ReturnValue_##FunctionName = mockReturnValue; \
    } \
    __attribute__((import_name(#FunctionName))) \
    ReturnType Original_##FunctionName(__VA_ARGS__); \
    extern "C" ReturnType FunctionName(SIV3D_MOCK_PARAMETERS_NAME(__VA_ARGS__)) \
    { \
        if (ReturnValue_##FunctionName.has_value()) \
        { \
            return *ReturnValue_##FunctionName; \
        } \
        return Original_##FunctionName(SIV3D_MOCK_PARAMETERS(__VA_ARGS__)); \
    }

# else

# define SIV3D_MOCK_FUNCTION(FunctionName, ReturnType, ...) \
    void SetMockFunction_##FunctionName(ReturnType (*mockFunction)(__VA_ARGS__))

# define SIV3D_MOCK_RETURN_VALUE(FunctionName, ReturnType, ...) \
    void SetReturnValue_##FunctionName(Optional<ReturnType> mockReturnValue);

# endif
