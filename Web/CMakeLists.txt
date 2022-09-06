cmake_minimum_required(VERSION 3.12)

project(OpenSiv3D_Web CXX C)

option(BUILD_SHARED_LIBS "Build 3rd party libraries as shared libraries (lib*.wasm)." OFF)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-missing-field-initializers -DWITH_SDL2_STATIC -DWITH_NOSOUND")
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wno-unknown-pragmas -DAS_USE_NAMESPACE -DMUPARSER_STATIC -D_UNICODE -DWITH_SDL2_STATIC -DWITH_NOSOUND -DBOOST_ASIO_HAS_STD_INVOKE_RESULT -DASIO_HAS_STD_INVOKE_RESULT")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -O2 -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

if (NOT CMAKE_CONFIGURATION_TYPES AND 
    NOT CMAKE_NO_BUILD_TYPE AND
    NOT CMAKE_BUILD_TYPE AND
    CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    message(STATUS "[!] Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release)
endif()

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  add_compile_options ("-fcolor-diagnostics")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_compile_options ("-fdiagnostics-color=always")
endif()

if (NOT CMAKE_BUILD_TYPE STREQUAL "MINSIZEREL")
  add_compile_options ("SHELL:-s EXCEPTION_CATCHING_ALLOWED=[\"InitSiv3D\"]")
endif()

if (${CMAKE_C_FLAGS} MATCHES "-msimd128" OR ${CMAKE_CXX_FLAGS} MATCHES "-msimd128")
  set(Siv3DEnableSIMD On)
else()
  add_compile_options ("-D_XM_NO_INTRINSICS_")
endif ()

if (${CMAKE_C_FLAGS} MATCHES "-pthread" OR ${CMAKE_CXX_FLAGS} MATCHES "-pthread")
  set(Siv3DEnablePThread On)
endif ()

if (BUILD_SHARED_LIBS)
  include(CMake/BuildThirdParty.cmake)
endif()

if (BUILD_SHARED_LIBS OR ${CMAKE_C_FLAGS} MATCHES "-fPIC" OR ${CMAKE_CXX_FLAGS} MATCHES "-fPIC")
  set(Siv3DEnablePICBuild On)

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s SIDE_MODULE=1")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s SIDE_MODULE=1")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s SIDE_MODULE=1")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s SIDE_MODULE=1")
  set(CMAKE_SHARED_LIBRARY_SUFFIX ".wasm")
endif()



set(SIV3D_SOURCES
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Siv3DMain.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Audio/NullSoundTouchFunctions.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/AudioCodec/AudioCodecFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/AudioCodec/CAudioCodec.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/AudioDecoder/SivAudioDecoder.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/AudioFormat/AAC/AACDecoder.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/AudioFormat/MP3/MP3Decoder.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/AsyncHTTPTask/AsyncHTTPTaskDetail.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/AsyncHTTPTask/SivAsyncHTTPTask.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/ChildProcess/ChildProcessDetail.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Clipboard/CClipboard.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Common/OpenGL.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/ConstantBuffer/ConstantBufferDetailFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/CPUInfo/SivCPUInfo.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Cursor/CCursor.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Dialog/SivDialog_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/DirectoryWatcher/DirectoryWatcherDetail.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/DragDrop/CDragDrop.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/FileSystem/SivFileSystem_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/FreestandingMessageBox/FreestandingMessageBox_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/LicenseManager/CLicenseManager.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/LicenseManager/LicenseManagerFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/LicenseManager/SivLicenseManager.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/MessageBox/SivMessageBox_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Mesh/MeshFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Microphone/MicrophoneDetail.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Microphone/SivMicrophone.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/MicrophoneInfo/SivMicrophoneInfo.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Monitor/SivMonitor_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/PowerStatus/SivPowerStatus.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer/GLES3/CRenderer_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer/RendererFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer2D/Renderer2DFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer3D/Renderer3DFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Resource/CResource.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Resource/SivResource_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Script/CScript.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Shader/ShaderFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/System/CSystem.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/System/SivSystem_Web.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/TCPClient/SivTCPClient.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/TCPClient/TCPClientDetail.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/TextToSpeech/CTextToSpeech.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Texture/TextureFactory.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/TextInput/CTextInput.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Time/SivTime.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/ToastNotification/CToastNotification.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/ToastNotification/SivToastNotification.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/VideoReader/SivVideoReader.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/VideoReader/VideoReaderDetail.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Webcam/SivWebcam.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Webcam/WebcamDetail.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/VideoCapture/VideoCapture.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/WebcamInfo/SivWebcamInfo.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Window/CWindow.cpp
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Window/WindowFactory.cpp

  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/BinaryReader/BinaryReaderDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/BinaryWriter/BinaryWriterDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Console/CConsole.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Date/SivDate_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/DateTime/SivDateTime_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/DLL/SivDLL.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/EnvironmentVariable/SivEnvironmentVariable.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Gamepad/CGamepad.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Keyboard/CKeyboard.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Logger/CLogger.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/MemoryMappedFileView/MemoryMappedFileViewDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/MemoryMappedFile/MemoryMappedFileDetail.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Monitor/SivMonitor_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Mouse/CMouse.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Pentablet/PentabletFactory.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/System/SivSystem_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/Unicode/SivUnicode_macOS_Linux.cpp
  ../Siv3D/src/Siv3D-Platform/macOS_Linux/Siv3D/XInput/XInputFactory.cpp

  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/ConstantBuffer/GLES3/ConstantBufferDetail_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Mesh/GLES3/CMesh_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Mesh/GLES3/GLES3Mesh.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/BackBuffer/GLES3BackBuffer.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/BackBuffer/GLES3InternalTexture2D.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/BlendState/GLES3BlendState.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/DepthStencilState/GLES3DepthStencilState.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/RasterizerState/GLES3RasterizerState.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer/GLES3/SamplerState/GLES3SamplerState.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer2D/GLES3/CRenderer2D_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer2D/GLES3/GLES3Renderer2DCommand.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer2D/GLES3/GLES3Vertex2DBatch.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer3D/GLES3/CRenderer3D_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer3D/GLES3/GLES3Line3DBatch.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Renderer3D/GLES3/GLES3Renderer3DCommand.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Shader/GLES3/CShader_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Shader/GLES3/PixelShader/GLES3PixelShader.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Shader/GLES3/VertexShader/GLES3VertexShader.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Shader/GLES3/ShaderPipeline/GLES3ShaderPipeline.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Texture/GLES3/CTexture_GLES3.cpp
  ../Siv3D/src/Siv3D-Platform/OpenGLES3/Siv3D/Texture/GLES3/GLES3Texture.cpp

  ../Siv3D/src/Siv3D/Addon/AddonFactory.cpp
  ../Siv3D/src/Siv3D/Addon/CAddon.cpp
  ../Siv3D/src/Siv3D/Addon/SivAddon.cpp
  ../Siv3D/src/Siv3D/AnimatedGIFReader/AnimatedGIFReaderDetail.cpp
  ../Siv3D/src/Siv3D/AnimatedGIFReader/SivAnimatedGIFReader.cpp
  ../Siv3D/src/Siv3D/AnimatedGIFWriter/AnimatedGIFWriterDetail.cpp
  ../Siv3D/src/Siv3D/AnimatedGIFWriter/SivAnimatedGIFWriter.cpp
  ../Siv3D/src/Siv3D/ArcEmitter2D/SivArcEmitter2D.cpp
  ../Siv3D/src/Siv3D/Asset/AssetFactory.cpp
  ../Siv3D/src/Siv3D/Asset/CAsset.cpp
  ../Siv3D/src/Siv3D/Asset/IAssetDetail.cpp
  ../Siv3D/src/Siv3D/Asset/SivAsset.cpp
  ../Siv3D/src/Siv3D/AssetMonitor/AssetMonitorFactory.cpp
  ../Siv3D/src/Siv3D/AssetMonitor/CAssetMonitor.cpp
  # ../Siv3D/src/Siv3D/AsyncHTTPTask/AsyncHTTPTaskDetail.cpp
  # ../Siv3D/src/Siv3D/AsyncHTTPTask/SivAsyncHTTPTask.cpp
  ../Siv3D/src/Siv3D/Audio/AudioBus.cpp
  ../Siv3D/src/Siv3D/Audio/AudioData.cpp
  ../Siv3D/src/Siv3D/Audio/AudioFactory.cpp
  ../Siv3D/src/Siv3D/Audio/CAudio.cpp
  ../Siv3D/src/Siv3D/Audio/DynamicAudioSource.cpp
  ../Siv3D/src/Siv3D/Audio/SivAudio.cpp
  ../Siv3D/src/Siv3D/AudioAsset/SivAudioAsset.cpp
  ../Siv3D/src/Siv3D/AudioAssetData/SivAudioAssetData.cpp
  ../Siv3D/src/Siv3D/AudioDecoder/AudioDecoderFactory.cpp
  ../Siv3D/src/Siv3D/AudioDecoder/CAudioDecoder.cpp
  ../Siv3D/src/Siv3D/AudioDecoder/SivAudioDecoder.cpp
  ../Siv3D/src/Siv3D/AudioEncoder/AudioEncoderFactory.cpp
  ../Siv3D/src/Siv3D/AudioEncoder/CAudioEncoder.cpp
  ../Siv3D/src/Siv3D/AudioEncoder/SivAudioEncoder.cpp
  ../Siv3D/src/Siv3D/AudioFormat/MIDI/MIDIDecoder.cpp
  ../Siv3D/src/Siv3D/AudioFormat/OggVorbis/OggVorbisDecoder.cpp
  ../Siv3D/src/Siv3D/AudioFormat/OggVorbis/OggVorbisEncoder.cpp
  ../Siv3D/src/Siv3D/AudioFormat/Opus/OpusDecoder.cpp
  ../Siv3D/src/Siv3D/AudioFormat/Opus/OpusEncoder.cpp
  ../Siv3D/src/Siv3D/AudioFormat/WAVE/WAVEDecoder.cpp
  ../Siv3D/src/Siv3D/AudioFormat/WAVE/WAVEEncoder.cpp
  ../Siv3D/src/Siv3D/AudioGroup/AudioGroupDetail.cpp
  ../Siv3D/src/Siv3D/AudioGroup/SivAudioGroup.cpp
  ../Siv3D/src/Siv3D/Base64/SivBase64.cpp
  ../Siv3D/src/Siv3D/BasicCamera3D/SivBasicCamera3D.cpp
  ../Siv3D/src/Siv3D/Bezier2/SivBezier2.cpp
  ../Siv3D/src/Siv3D/Bezier3/SivBezier3.cpp
  ../Siv3D/src/Siv3D/BigFloat/SivBigFloat.cpp
  ../Siv3D/src/Siv3D/BigInt/SivBigInt.cpp
  ../Siv3D/src/Siv3D/BinaryReader/SivBinaryReader.cpp
  ../Siv3D/src/Siv3D/BinaryWriter/SivBinaryWriter.cpp
  ../Siv3D/src/Siv3D/Blob/SivBlob.cpp
  ../Siv3D/src/Siv3D/Box/SivBox.cpp
  ../Siv3D/src/Siv3D/Buffer2D/SivBuffer2D.cpp
  ../Siv3D/src/Siv3D/Byte/SivByte.cpp
  ../Siv3D/src/Siv3D/CacheDirectory/CacheDirectory.cpp
  ../Siv3D/src/Siv3D/Camera2DParameters/SivCamera2DParameters.cpp
  ../Siv3D/src/Siv3D/Camera2D/SivCamera2D.cpp
  ../Siv3D/src/Siv3D/CascadeClassifier/CascadeClassifierDetail.cpp
  ../Siv3D/src/Siv3D/CascadeClassifier/SivCascadeClassifier.cpp
  ../Siv3D/src/Siv3D/ChildProcess/SivChildProcess.cpp
  ../Siv3D/src/Siv3D/Circle/SivCircle.cpp
  ../Siv3D/src/Siv3D/CircleEmitter2D/SivCircleEmitter2D.cpp
  ../Siv3D/src/Siv3D/Clipboard/ClipboardFactory.cpp
  ../Siv3D/src/Siv3D/Clipboard/SivClipboard.cpp
  ../Siv3D/src/Siv3D/Color/SivColor.cpp
  ../Siv3D/src/Siv3D/Colormap/SivColormap.cpp
  ../Siv3D/src/Siv3D/CommandLine/SivCommandLine.cpp
  ../Siv3D/src/Siv3D/Common/Siv3DEngine.cpp
  ../Siv3D/src/Siv3D/Compression/SivCompression.cpp
  ../Siv3D/src/Siv3D/Cone/SivCone.cpp
  ../Siv3D/src/Siv3D/Console/ConsoleFactory.cpp
  ../Siv3D/src/Siv3D/Console/SivConsole.cpp
  ../Siv3D/src/Siv3D/ConstantBuffer/Null/ConstantBufferDetail_Null.cpp
  ../Siv3D/src/Siv3D/ConstantBuffer/SivConstantBuffer.cpp
  # ../Siv3D/src/Siv3D/CPUInfo/SivCPUInfo.cpp
  ../Siv3D/src/Siv3D/CSV/SivCSV.cpp
  ../Siv3D/src/Siv3D/Cursor/CCursor_Null.cpp
  ../Siv3D/src/Siv3D/Cursor/CursorFactory.cpp
  ../Siv3D/src/Siv3D/Cursor/SivCursor.cpp
  ../Siv3D/src/Siv3D/Cylinder/SivCylinder.cpp
  ../Siv3D/src/Siv3D/DateTime/SivDateTime.cpp
  ../Siv3D/src/Siv3D/DebugCamera3D/SivDebugCamera3D.cpp
  ../Siv3D/src/Siv3D/Demangle/SivDemangle.cpp
  ../Siv3D/src/Siv3D/Dialog/SivDialog.cpp
  ../Siv3D/src/Siv3D/DirectoryWatcher/SivDirectoryWatcher.cpp
  ../Siv3D/src/Siv3D/Disc/SivDisc.cpp
  ../Siv3D/src/Siv3D/DragDrop/DragDropFactory.cpp
  ../Siv3D/src/Siv3D/DragDrop/SivDragDrop.cpp
  ../Siv3D/src/Siv3D/DrawableText/SivDrawableText.cpp
  ../Siv3D/src/Siv3D/Duration/SivDuration.cpp
  ../Siv3D/src/Siv3D/DynamicMesh/SivDynamicMesh.cpp
  ../Siv3D/src/Siv3D/DynamicTexture/SivDynamicTexture.cpp
  ../Siv3D/src/Siv3D/Effect/CEffect.cpp
  ../Siv3D/src/Siv3D/Effect/EffectData.cpp
  ../Siv3D/src/Siv3D/Effect/EffectFactory.cpp
  ../Siv3D/src/Siv3D/Effect/SivEffect.cpp
  ../Siv3D/src/Siv3D/Ellipse/SivEllipse.cpp
  ../Siv3D/src/Siv3D/Emoji/SivEmoji.cpp
  ../Siv3D/src/Siv3D/Empty/CEmpty.cpp
  ../Siv3D/src/Siv3D/Empty/EmptyFactory.cpp
  ../Siv3D/src/Siv3D/EngineLog/SivEngineLog.cpp
  ../Siv3D/src/Siv3D/EngineOptions/SivEngineOptions.cpp
  ../Siv3D/src/Siv3D/Error/SivError.cpp
  ../Siv3D/src/Siv3D/Exif/SivExif.cpp
  ../Siv3D/src/Siv3D/FFT/CFFT.cpp
  ../Siv3D/src/Siv3D/FFT/FFTFactory.cpp
  ../Siv3D/src/Siv3D/FFT/SivFFT.cpp
  ../Siv3D/src/Siv3D/FileFilter/SivFileFilter.cpp
  ../Siv3D/src/Siv3D/FileSystem/SivFileSystem.cpp
  ../Siv3D/src/Siv3D/Font/CFont.cpp
  ../Siv3D/src/Siv3D/Font/CFont_Headless.cpp
  ../Siv3D/src/Siv3D/Font/EmojiData.cpp
  ../Siv3D/src/Siv3D/Font/FontCommon.cpp
  ../Siv3D/src/Siv3D/Font/GlyphCache/BitmapGlyphCache.cpp
  ../Siv3D/src/Siv3D/Font/GlyphCache/GlyphCacheCommon.cpp
  ../Siv3D/src/Siv3D/Font/GlyphCache/MSDFGlyphCache.cpp
  ../Siv3D/src/Siv3D/Font/GlyphCache/SDFGlyphCache.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/agg/agg.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/GlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/BitmapGlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/MSDFGlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/OutlineGlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/GlyphRenderer/SDFGlyphRenderer.cpp
  ../Siv3D/src/Siv3D/Font/FontData.cpp
  ../Siv3D/src/Siv3D/Font/FontFace.cpp
  ../Siv3D/src/Siv3D/Font/FontFactory.cpp
  ../Siv3D/src/Siv3D/Font/IconData.cpp
  ../Siv3D/src/Siv3D/Font/SivFont.cpp
  ../Siv3D/src/Siv3D/FontAsset/SivFontAsset.cpp
  ../Siv3D/src/Siv3D/FontAssetData/SivFontAssetData.cpp
  ../Siv3D/src/Siv3D/FormatData/SivFormatData.cpp
  ../Siv3D/src/Siv3D/FormatFloat/SivFormatFloat.cpp
  ../Siv3D/src/Siv3D/FormatInt/SivFormatInt.cpp
  ../Siv3D/src/Siv3D/Formatter/SivFormatter.cpp
  ../Siv3D/src/Siv3D/FormatUtility/SivFormatUtility.cpp
  ../Siv3D/src/Siv3D/Gamepad/GamepadFactory.cpp
  ../Siv3D/src/Siv3D/Gamepad/SivGamepad.cpp
  ../Siv3D/src/Siv3D/GamepadInfo/SivGamepadInfo.cpp
  ../Siv3D/src/Siv3D/GeoJSON/SivGeoJSON.cpp
  ../Siv3D/src/Siv3D/Geometry2D/SivGeometry2D.cpp
  ../Siv3D/src/Siv3D/Geometry3D/SivGeometry3D.cpp
  ../Siv3D/src/Siv3D/GlobalAudio/SivGlobalAudio.cpp
  ../Siv3D/src/Siv3D/GrabCut/GrabCutDetail.cpp
  ../Siv3D/src/Siv3D/GrabCut/SivGrabCut.cpp
  ../Siv3D/src/Siv3D/Graphics/SivGraphics.cpp
  ../Siv3D/src/Siv3D/Graphics2D/SivGraphics2D.cpp
  ../Siv3D/src/Siv3D/Graphics3D/SivGraphics3D.cpp
  ../Siv3D/src/Siv3D/GUI/CGUI.cpp
  ../Siv3D/src/Siv3D/GUI/GUIFactory.cpp
  ../Siv3D/src/Siv3D/Hash/SivHash.cpp
  ../Siv3D/src/Siv3D/HSV/SivHSV.cpp
  ../Siv3D/src/Siv3D/HTMLWriter/HTMLWriterDetail.cpp
  ../Siv3D/src/Siv3D/HTMLWriter/SivHTMLWriter.cpp
  ../Siv3D/src/Siv3D/HTTPResponse/SivHTTPResponse.cpp
  ../Siv3D/src/Siv3D/Icon/SivIcon.cpp
  ../Siv3D/src/Siv3D/Image/ImagePainting.cpp
  ../Siv3D/src/Siv3D/Image/ShapePainting.cpp
  ../Siv3D/src/Siv3D/Image/SivImage.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/CImageDecoder.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/ImageDecoderFactory.cpp
  ../Siv3D/src/Siv3D/ImageDecoder/SivImageDecoder.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/CImageEncoder.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/ImageEncoderFactory.cpp
  ../Siv3D/src/Siv3D/ImageEncoder/SivImageEncoder.cpp 
  ../Siv3D/src/Siv3D/ImageFormat/BMP/BMPDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/BMP/BMPEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/GIF/GIFDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/GIF/GIFEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/JPEG/JPEGDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/JPEG/JPEGEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PNG/PNGDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PNG/PNGEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PPM/PPMDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/PPM/PPMEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/SVG/SVGDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/TGA/TGADecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/TGA/TGAEncoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/TIFF/TIFFDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/WebP/WebPDecoder.cpp
  ../Siv3D/src/Siv3D/ImageFormat/WebP/WebPEncoder.cpp
  ../Siv3D/src/Siv3D/ImageProcessing/SivImageProcessing.cpp
  ../Siv3D/src/Siv3D/ImageROI/SivImageROI.cpp
  ../Siv3D/src/Siv3D/InfinitePlane/SivInfinitePlane.cpp
  ../Siv3D/src/Siv3D/INI/SivINI.cpp
  ../Siv3D/src/Siv3D/Input/InputState.cpp
  ../Siv3D/src/Siv3D/Input/SivInput.cpp
  ../Siv3D/src/Siv3D/InputCombination/SivInputCombination.cpp
  ../Siv3D/src/Siv3D/InputGroup/SivInputGroup.cpp
  ../Siv3D/src/Siv3D/Int128/SivInt128.cpp
  ../Siv3D/src/Siv3D/Interpolation/SivInterpolation.cpp
  ../Siv3D/src/Siv3D/IntFormatter/SivIntFormatter.cpp
  ../Siv3D/src/Siv3D/IPv4Address/SivIPv4Address.cpp
  ../Siv3D/src/Siv3D/JoyCon/SivJoyCon.cpp
  ../Siv3D/src/Siv3D/JSON/SivJSON.cpp
  ../Siv3D/src/Siv3D/Keyboard/KeyboardFactory.cpp
  ../Siv3D/src/Siv3D/Keyboard/SivKeyboard.cpp
  ../Siv3D/src/Siv3D/KlattTTS/SivKlattTTS.cpp
  # ../Siv3D/src/Siv3D/LicenseManager/CLicenseManager.cpp
  # ../Siv3D/src/Siv3D/LicenseManager/LicenseManagerFactory.cpp
  # ../Siv3D/src/Siv3D/LicenseManager/SivLicenseManager.cpp
  ../Siv3D/src/Siv3D/Line/SivLine.cpp
  ../Siv3D/src/Siv3D/Line3D/SivLine3D.cpp
  ../Siv3D/src/Siv3D/LineString/SivLineString.cpp
  ../Siv3D/src/Siv3D/Logger/LoggerFactory.cpp
  ../Siv3D/src/Siv3D/Logger/SivLogger.cpp
  ../Siv3D/src/Siv3D/ManagedScript/ManagedScriptDetail.cpp
  ../Siv3D/src/Siv3D/ManagedScript/SivManagedScript.cpp
  ../Siv3D/src/Siv3D/Mat3x2/SivMat3x2.cpp
  ../Siv3D/src/Siv3D/Mat3x3/SivMat3x3.cpp
  ../Siv3D/src/Siv3D/Mat4x4/SivMat4x4.cpp
  ../Siv3D/src/Siv3D/MathParser/MathParserDetail.cpp
  ../Siv3D/src/Siv3D/MathParser/SivMathParser.cpp
  ../Siv3D/src/Siv3D/MD5/SivMD5.cpp
  ../Siv3D/src/Siv3D/MD5Value/SivMD5Value.cpp
  ../Siv3D/src/Siv3D/MemoryMappedFileView/SivMemoryMappedFileView.cpp
  ../Siv3D/src/Siv3D/MemoryMappedFile/SivMemoryMappedFile.cpp
  ../Siv3D/src/Siv3D/MemoryReader/SivMemoryReader.cpp
  ../Siv3D/src/Siv3D/MemoryViewReader/SivMemoryViewReader.cpp
  ../Siv3D/src/Siv3D/MemoryWriter/SivMemoryWriter.cpp
  ../Siv3D/src/Siv3D/Mesh/Null/CMesh_Null.cpp
  ../Siv3D/src/Siv3D/Mesh/SivMesh.cpp
  ../Siv3D/src/Siv3D/MeshData/MeshUtility.cpp
  ../Siv3D/src/Siv3D/MeshData/SivMeshData.cpp
  ../Siv3D/src/Siv3D/MessageBox/SivMessageBox.cpp
  # ../Siv3D/src/Siv3D/Microphone/MicrophoneDetail.cpp
  # ../Siv3D/src/Siv3D/Microphone/SivMicrophone.cpp
  # ../Siv3D/src/Siv3D/MicrophoneInfo/SivMicrophoneInfo.cpp
  ../Siv3D/src/Siv3D/MicrosecClock/SivMicrosecClock.cpp
  ../Siv3D/src/Siv3D/MillisecClock/SivMillisecClock.cpp
  ../Siv3D/src/Siv3D/Model/CModel.cpp
  ../Siv3D/src/Siv3D/Model/ModelData.cpp
  ../Siv3D/src/Siv3D/Model/ModelFactory.cpp
  ../Siv3D/src/Siv3D/Model/SivModel.cpp
  ../Siv3D/src/Siv3D/ModelObject/SivModelObject.cpp
  ../Siv3D/src/Siv3D/Monitor/SivMonitor.cpp
  ../Siv3D/src/Siv3D/Mouse/MouseFactory.cpp
  ../Siv3D/src/Siv3D/Mouse/SivMouse.cpp
  ../Siv3D/src/Siv3D/MSRenderTexture/SivMSRenderTexture.cpp
  ../Siv3D/src/Siv3D/MultiPolygon/SivMultiPolygon.cpp
  ../Siv3D/src/Siv3D/NavMesh/NavMeshDetail.cpp
  ../Siv3D/src/Siv3D/NavMesh/SivNavMesh.cpp
  ../Siv3D/src/Siv3D/Network/CNetwork.cpp
  ../Siv3D/src/Siv3D/Network/NetworkFactory.cpp
  ../Siv3D/src/Siv3D/Network/SivNetwork.cpp
  ../Siv3D/src/Siv3D/None/SivNone.cpp
  ../Siv3D/src/Siv3D/OpenCV_Bridge/SivOpenCV_Bridge.cpp
  ../Siv3D/src/Siv3D/OrientedBox/SivOrientedBox.cpp
  ../Siv3D/src/Siv3D/Parse/SivParse.cpp
  ../Siv3D/src/Siv3D/ParseBool/SivParseBool.cpp
  ../Siv3D/src/Siv3D/ParseFloat/SivParseFloat.cpp
  ../Siv3D/src/Siv3D/ParseInt/SivParseInt.cpp
  ../Siv3D/src/Siv3D/Particle2D/SivParticle2D.cpp
  ../Siv3D/src/Siv3D/ParticleSystem2D/ParticleSystem2DDetail.cpp
  ../Siv3D/src/Siv3D/ParticleSystem2D/SivParticleSystem2D.cpp
  ../Siv3D/src/Siv3D/Pentablet/Null/CPentablet_Null.cpp
  ../Siv3D/src/Siv3D/Pentablet/SivPentablet.cpp
  ../Siv3D/src/Siv3D/Periodic/SivPeriodic.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2Body.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2BodyDetail.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2Circle.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2ContactListener.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2DistanceJoint.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2DistanceJointDetail.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2Line.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2LineString.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2MouseJoint.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2MouseJointDetail.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2PivotJoint.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2PivotJointDetail.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2Polygon.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2Quad.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2Rect.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2Shape.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2SliderJoint.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2SliderJointDetail.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2Triangle.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2WheelJoint.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2WheelJointDetail.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2World.cpp
  ../Siv3D/src/Siv3D/Physics2D/P2WorldDetail.cpp
  ../Siv3D/src/Siv3D/PixelShader/SivPixelShader.cpp
  ../Siv3D/src/Siv3D/PixelShaderAsset/SivPixelShaderAsset.cpp
  ../Siv3D/src/Siv3D/PixelShaderAssetData/SivPixelShaderAssetData.cpp
  ../Siv3D/src/Siv3D/Plane/SivPlane.cpp
  ../Siv3D/src/Siv3D/PlayingCard/SivPlayingCard.cpp
  ../Siv3D/src/Siv3D/Point/SivPoint.cpp
  ../Siv3D/src/Siv3D/Polygon/PolygonDetail.cpp
  ../Siv3D/src/Siv3D/Polygon/SivPolygon.cpp
  ../Siv3D/src/Siv3D/Polygon/Triangulation.cpp
  ../Siv3D/src/Siv3D/PolygonEmitter2D/SivPolygonEmitter2D.cpp
  ../Siv3D/src/Siv3D/PrimeNumber/SivPrimeNumber.cpp
  ../Siv3D/src/Siv3D/PrimitiveMesh/CPrimitiveMesh.cpp
  ../Siv3D/src/Siv3D/PrimitiveMesh/PrimitiveMeshFactory.cpp
  ../Siv3D/src/Siv3D/Print/CPrint.cpp
  ../Siv3D/src/Siv3D/Print/PrintFactory.cpp
  ../Siv3D/src/Siv3D/Print/SivPrint.cpp
  ../Siv3D/src/Siv3D/ProController/SivProController.cpp
  ../Siv3D/src/Siv3D/Profiler/CProfiler.cpp
  ../Siv3D/src/Siv3D/Profiler/ProfilerFactory.cpp
  ../Siv3D/src/Siv3D/Profiler/SivProfiler.cpp
  ../Siv3D/src/Siv3D/ProfilerStat/SivProfilerStat.cpp
  ../Siv3D/src/Siv3D/PutText/SivPutText.cpp
  ../Siv3D/src/Siv3D/QR/SivQR.cpp
  ../Siv3D/src/Siv3D/QRScanner/QRScannerDetail.cpp
  ../Siv3D/src/Siv3D/QRScanner/SivQRScanner.cpp
  ../Siv3D/src/Siv3D/Quad/SivQuad.cpp
  ../Siv3D/src/Siv3D/Quaternion/SivQuaternion.cpp
  ../Siv3D/src/Siv3D/Random/SivRandom.cpp
  ../Siv3D/src/Siv3D/Ray/SivRay.cpp
  ../Siv3D/src/Siv3D/RDTSCClock/SivRDTSCClock.cpp
  ../Siv3D/src/Siv3D/Rect/SivRect.cpp
  ../Siv3D/src/Siv3D/RectanglePacking/SivRectanglePacking.cpp
  ../Siv3D/src/Siv3D/RectEmitter2D/SivRectEmitter2D.cpp
  ../Siv3D/src/Siv3D/RectF/SivRectF.cpp
  ../Siv3D/src/Siv3D/RegExp/RegExpDetail.cpp
  ../Siv3D/src/Siv3D/RegExp/SivRegExp.cpp
  ../Siv3D/src/Siv3D/Renderer/Null/CRenderer_Null.cpp
  ../Siv3D/src/Siv3D/Renderer2D/Null/CRenderer2D_Null.cpp
  ../Siv3D/src/Siv3D/Renderer2D/Vertex2DBuilder.cpp
  ../Siv3D/src/Siv3D/Renderer3D/Null/CRenderer3D_Null.cpp
  ../Siv3D/src/Siv3D/RenderTexture/SivRenderTexture.cpp
  ../Siv3D/src/Siv3D/Resource/ResourceFactory.cpp
  ../Siv3D/src/Siv3D/Resource/SivResource.cpp
  ../Siv3D/src/Siv3D/RoundRect/SivRoundRect.cpp
  ../Siv3D/src/Siv3D/Say/SivSay.cpp
  ../Siv3D/src/Siv3D/Scene/CScene.cpp
  ../Siv3D/src/Siv3D/Scene/FrameCounter.cpp
  ../Siv3D/src/Siv3D/Scene/FrameTimer.cpp
  ../Siv3D/src/Siv3D/Scene/SceneFactory.cpp
  ../Siv3D/src/Siv3D/Scene/SivScene.cpp
  ../Siv3D/src/Siv3D/ScopedColorAdd2D/SivScopedColorAdd2D.cpp
  ../Siv3D/src/Siv3D/ScopedColorMul2D/SivScopedColorMul2D.cpp
  ../Siv3D/src/Siv3D/ScopedCustomShader2D/SivScopedCustomShader2D.cpp
  ../Siv3D/src/Siv3D/ScopedCustomShader3D/SivScopedCustomShader3D.cpp
  ../Siv3D/src/Siv3D/ScopedRenderStates2D/SivScopedRenderStates2D.cpp
  ../Siv3D/src/Siv3D/ScopedRenderStates3D/SivScopedRenderStates3D.cpp
  ../Siv3D/src/Siv3D/ScopedRenderTarget2D/SivScopedRenderTarget2D.cpp
  ../Siv3D/src/Siv3D/ScopedRenderTarget3D/SivScopedRenderTarget3D.cpp
  ../Siv3D/src/Siv3D/ScopedViewport2D/SivScopedViewport2D.cpp
  ../Siv3D/src/Siv3D/ScopedViewport3D/SivScopedViewport3D.cpp
  ../Siv3D/src/Siv3D/ScreenCapture/CScreenCapture.cpp
  ../Siv3D/src/Siv3D/ScreenCapture/ScreenCaptureFactory.cpp
  ../Siv3D/src/Siv3D/ScreenCapture/SivScreenCapture.cpp
  ../Siv3D/src/Siv3D/ScriptFunction/SivScriptFunction.cpp
  ../Siv3D/src/Siv3D/ScriptModule/SivScriptModule.cpp
  ../Siv3D/src/Siv3D/Script/ScriptData.cpp
  ../Siv3D/src/Siv3D/Script/ScriptFactory.cpp
  ../Siv3D/src/Siv3D/Script/SivScript.cpp
  ../Siv3D/src/Siv3D/SerialPortInfo/SivSerialPortInfo.cpp
  ../Siv3D/src/Siv3D/Serial/SerialDetail.cpp
  ../Siv3D/src/Siv3D/Serial/SivSerial.cpp
  ../Siv3D/src/Siv3D/SFMT/SivSFMT.cpp
  ../Siv3D/src/Siv3D/ShaderCommon/SivShaderCommon.cpp
  ../Siv3D/src/Siv3D/Shader/Null/CShader_Null.cpp
  ../Siv3D/src/Siv3D/Shader/SivShader.cpp
  ../Siv3D/src/Siv3D/Shape2D/SivShape2D.cpp
  ../Siv3D/src/Siv3D/SIMDMath/SivSIMDMath.cpp
  ../Siv3D/src/Siv3D/SimpleAnimation/SivSimpleAnimation.cpp
  ../Siv3D/src/Siv3D/SimpleGUI/SivSimpleGUI.cpp
  ../Siv3D/src/Siv3D/SimpleHTTP/SivSimpleHTTP.cpp
  ../Siv3D/src/Siv3D/Sky/SivSky.cpp
  ../Siv3D/src/Siv3D/SoundFont/CSoundFont.cpp
  ../Siv3D/src/Siv3D/SoundFont/SivSoundFont.cpp
  ../Siv3D/src/Siv3D/SoundFont/SoundFontDetail.cpp
  ../Siv3D/src/Siv3D/SoundFont/SoundFontFactory.cpp
  ../Siv3D/src/Siv3D/Sphere/SivSphere.cpp
  ../Siv3D/src/Siv3D/Spline2D/SivSpline2D.cpp
  ../Siv3D/src/Siv3D/String/SivString.cpp
  ../Siv3D/src/Siv3D/String/Levenshtein.cpp
  ../Siv3D/src/Siv3D/StringView/SivStringView.cpp
  ../Siv3D/src/Siv3D/Subdivision2D/SivSubdivision2D.cpp
  ../Siv3D/src/Siv3D/SVG/SivSVG.cpp
  ../Siv3D/src/Siv3D/SVG/SVGDetail.cpp
  ../Siv3D/src/Siv3D/System/SivSystem.cpp
  ../Siv3D/src/Siv3D/System/SystemFactory.cpp
  ../Siv3D/src/Siv3D/System/SystemLog.cpp
  ../Siv3D/src/Siv3D/System/SystemMisc.cpp
  # ../Siv3D/src/Siv3D/TCPClient/SivTCPClient.cpp
  # ../Siv3D/src/Siv3D/TCPClient/TCPClientDetail.cpp
  ../Siv3D/src/Siv3D/TCPServer/SivTCPServer.cpp
  ../Siv3D/src/Siv3D/TCPServer/TCPServerDetail.cpp
  ../Siv3D/src/Siv3D/TextEncoding/SivTextEncoding.cpp
  ../Siv3D/src/Siv3D/TextInput/SivTextInput.cpp
  ../Siv3D/src/Siv3D/TextInput/TextInputFactory.cpp
  ../Siv3D/src/Siv3D/TextReader/SivTextReader.cpp
  ../Siv3D/src/Siv3D/TextReader/TextReaderDetail.cpp
  ../Siv3D/src/Siv3D/TextToSpeech/SivTextToSpeech.cpp
  ../Siv3D/src/Siv3D/TextToSpeech/TextToSpeechFactory.cpp
  ../Siv3D/src/Siv3D/Texture/Null/CTexture_Null.cpp
  ../Siv3D/src/Siv3D/Texture/SivTexture.cpp
  ../Siv3D/src/Siv3D/Texture/TextureCommon.cpp
  ../Siv3D/src/Siv3D/TextureAsset/SivTextureAsset.cpp
  ../Siv3D/src/Siv3D/TextureAssetData/SivTextureAssetData.cpp
  ../Siv3D/src/Siv3D/TexturedCircle/SivTexturedCircle.cpp
  ../Siv3D/src/Siv3D/TexturedQuad/SivTexturedQuad.cpp
  ../Siv3D/src/Siv3D/TexturedRoundRect/SivTexturedRoundRect.cpp
  ../Siv3D/src/Siv3D/TextureFormat/SivTextureFormat.cpp
  ../Siv3D/src/Siv3D/TextureRegion/SivTextureRegion.cpp
  ../Siv3D/src/Siv3D/TextWriter/SivTextWriter.cpp
  ../Siv3D/src/Siv3D/TextWriter/TextWriterDetail.cpp  
  ../Siv3D/src/Siv3D/Threading/SivThreading.cpp
  ../Siv3D/src/Siv3D/TimeProfiler/SivTimeProfiler.cpp
  ../Siv3D/src/Siv3D/Timer/SivTimer.cpp
  ../Siv3D/src/Siv3D/ToastNotification/SivToastNotification.cpp
  ../Siv3D/src/Siv3D/ToastNotification/ToastNotificationFactory.cpp
  ../Siv3D/src/Siv3D/TOMLReader/SivTOMLReader.cpp
  ../Siv3D/src/Siv3D/Triangle/SivTriangle.cpp
  ../Siv3D/src/Siv3D/Transformer2D/SivTransformer2D.cpp
  ../Siv3D/src/Siv3D/Transformer3D/SivTransformer3D.cpp
  ../Siv3D/src/Siv3D/Triangle3D/SivTriangle3D.cpp
  ../Siv3D/src/Siv3D/Twitter/SivTwitter.cpp
  ../Siv3D/src/Siv3D/Unicode/SivUnicode.cpp
  ../Siv3D/src/Siv3D/Unicode/UnicodeUtility.cpp
  ../Siv3D/src/Siv3D/UnicodeConverter/SivUnicodeConverter.cpp
  ../Siv3D/src/Siv3D/UserAction/CUserAction.cpp
  ../Siv3D/src/Siv3D/UserAction/UserActionFactory.cpp
  ../Siv3D/src/Siv3D/UUIDValue/SivUUIDValue.cpp
  ../Siv3D/src/Siv3D/VariableSpeedStopwatch/SivVariableSpeedStopwatch.cpp
  ../Siv3D/src/Siv3D/Vector2D/SivVector2D.cpp
  ../Siv3D/src/Siv3D/Vector3D/SivVector3D.cpp
  ../Siv3D/src/Siv3D/Vector4D/SivVector4D.cpp
  ../Siv3D/src/Siv3D/VertexShader/SivVertexShader.cpp
  ../Siv3D/src/Siv3D/VertexShaderAsset/SivVertexShaderAsset.cpp
  ../Siv3D/src/Siv3D/VertexShaderAssetData/SivVertexShaderAssetData.cpp
  # ../Siv3D/src/Siv3D/VideoReader/SivVideoReader.cpp
  # ../Siv3D/src/Siv3D/VideoReader/VideoReaderDetail.cpp
  ../Siv3D/src/Siv3D/VideoWriter/SivVideoWriter.cpp
  ../Siv3D/src/Siv3D/VideoWriter/VideoWriterDetail.cpp
  ../Siv3D/src/Siv3D/VideoTexture/SivVideoTexture.cpp
  ../Siv3D/src/Siv3D/VideoTexture/VideoTextureDetail.cpp
  ../Siv3D/src/Siv3D/ViewFrustum/SivViewFrustum.cpp
  ../Siv3D/src/Siv3D/Wave/SivWave.cpp
  # ../Siv3D/src/Siv3D/Webcam/SivWebcam.cpp
  # ../Siv3D/src/Siv3D/Webcam/WebcamDetail.cpp
  ../Siv3D/src/Siv3D/Window/SivWindow.cpp
  ../Siv3D/src/Siv3D/Window/Null/CWindow_Null.cpp
  ../Siv3D/src/Siv3D/XInput/Null/CXInput_Null.cpp
  ../Siv3D/src/Siv3D/XInput/SivXInput.cpp
  ../Siv3D/src/Siv3D/XMLReader/SivXMLReader.cpp
  ../Siv3D/src/Siv3D/ZIPReader/SivZIPReader.cpp
  ../Siv3D/src/Siv3D/ZIPReader/ZIPReaderDetail.cpp
  ../Siv3D/src/Siv3D/Zlib/SivZlib.cpp
)



set(SIV3D_THIRDPARTY_SOURCES
  ${SIV3D_THIRDPARTY_SOURCES}
  ../Siv3D/src/ThirdParty/absl/numeric/int128.cc
  ../Siv3D/src/ThirdParty/absl/random/discrete_distribution.cc
  ../Siv3D/src/ThirdParty/absl/random/gaussian_distribution.cc

  ../Siv3D/src/ThirdParty/box2d/collision/b2_broad_phase.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_chain_shape.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_circle_shape.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_collide_circle.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_collide_edge.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_collide_polygon.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_collision.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_distance.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_dynamic_tree.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_edge_shape.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_polygon_shape.cpp
  ../Siv3D/src/ThirdParty/box2d/collision/b2_time_of_impact.cpp
  ../Siv3D/src/ThirdParty/box2d/common/b2_block_allocator.cpp
  ../Siv3D/src/ThirdParty/box2d/common/b2_draw.cpp
  ../Siv3D/src/ThirdParty/box2d/common/b2_math.cpp
  ../Siv3D/src/ThirdParty/box2d/common/b2_settings.cpp
  ../Siv3D/src/ThirdParty/box2d/common/b2_stack_allocator.cpp
  ../Siv3D/src/ThirdParty/box2d/common/b2_timer.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_body.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_chain_circle_contact.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_chain_polygon_contact.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_circle_contact.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_contact.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_contact_manager.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_contact_solver.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_distance_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_edge_circle_contact.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_edge_polygon_contact.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_fixture.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_friction_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_gear_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_island.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_motor_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_mouse_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_polygon_circle_contact.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_polygon_contact.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_prismatic_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_pulley_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_revolute_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_weld_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_wheel_joint.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_world.cpp
  ../Siv3D/src/ThirdParty/box2d/dynamics/b2_world_callbacks.cpp
  ../Siv3D/src/ThirdParty/box2d/rope/b2_rope.cpp

  # ../Siv3D/src/ThirdParty/cpu_features/cpuinfo_x86.c
  ../Siv3D/src/ThirdParty/cpu_features/filesystem.c
  ../Siv3D/src/ThirdParty/cpu_features/stack_line_reader.c
  ../Siv3D/src/ThirdParty/cpu_features/string_view.c

  ../Siv3D/src/ThirdParty/DirectXMath/DirectXCollision.cpp

  ../Siv3D/src/ThirdParty/double-conversion/bignum-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/bignum.cc
  ../Siv3D/src/ThirdParty/double-conversion/cached-powers.cc
  ../Siv3D/src/ThirdParty/double-conversion/double-to-string.cc
  ../Siv3D/src/ThirdParty/double-conversion/fast-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/fixed-dtoa.cc
  ../Siv3D/src/ThirdParty/double-conversion/string-to-double.cc
  ../Siv3D/src/ThirdParty/double-conversion/strtod.cc

  ../Siv3D/src/ThirdParty/easyexif/exif.cpp

  ../Siv3D/src/ThirdParty/fmt/format.cc
  
  ../Siv3D/src/ThirdParty/lua/lapi.c
  ../Siv3D/src/ThirdParty/lua/lauxlib.c
  ../Siv3D/src/ThirdParty/lua/lbaselib.c
  ../Siv3D/src/ThirdParty/lua/lcode.c
  ../Siv3D/src/ThirdParty/lua/lcorolib.c
  ../Siv3D/src/ThirdParty/lua/lctype.c
  ../Siv3D/src/ThirdParty/lua/ldblib.c
  ../Siv3D/src/ThirdParty/lua/ldebug.c
  ../Siv3D/src/ThirdParty/lua/ldo.c
  ../Siv3D/src/ThirdParty/lua/ldump.c
  ../Siv3D/src/ThirdParty/lua/lfunc.c
  ../Siv3D/src/ThirdParty/lua/lgc.c
  ../Siv3D/src/ThirdParty/lua/linit.c
  ../Siv3D/src/ThirdParty/lua/liolib.c
  ../Siv3D/src/ThirdParty/lua/llex.c
  ../Siv3D/src/ThirdParty/lua/lmathlib.c
  ../Siv3D/src/ThirdParty/lua/lmem.c
  ../Siv3D/src/ThirdParty/lua/loadlib.c
  ../Siv3D/src/ThirdParty/lua/lobject.c
  ../Siv3D/src/ThirdParty/lua/lopcodes.c
  ../Siv3D/src/ThirdParty/lua/loslib.c
  ../Siv3D/src/ThirdParty/lua/lparser.c
  ../Siv3D/src/ThirdParty/lua/lstate.c
  ../Siv3D/src/ThirdParty/lua/lstring.c
  ../Siv3D/src/ThirdParty/lua/lstrlib.c
  ../Siv3D/src/ThirdParty/lua/ltable.c
  ../Siv3D/src/ThirdParty/lua/ltablib.c
  ../Siv3D/src/ThirdParty/lua/ltm.c
  # ../Siv3D/src/ThirdParty/lua/lua.c
  ../Siv3D/src/ThirdParty/lua/lundump.c
  ../Siv3D/src/ThirdParty/lua/lutf8lib.c
  ../Siv3D/src/ThirdParty/lua/lvm.c
  ../Siv3D/src/ThirdParty/lua/lzio.c

  ../Siv3D/src/ThirdParty/lunasvg/canvas.cpp
  ../Siv3D/src/ThirdParty/lunasvg/clippathelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/defselement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/element.cpp
  ../Siv3D/src/ThirdParty/lunasvg/gelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/geometryelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/graphicselement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/layoutcontext.cpp
  ../Siv3D/src/ThirdParty/lunasvg/lunasvg.cpp
  ../Siv3D/src/ThirdParty/lunasvg/markerelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/maskelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/paintelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/parser.cpp
  ../Siv3D/src/ThirdParty/lunasvg/property.cpp
  ../Siv3D/src/ThirdParty/lunasvg/stopelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/styledelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/styleelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/svgelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/symbolelement.cpp
  ../Siv3D/src/ThirdParty/lunasvg/useelement.cpp

  ../Siv3D/src/ThirdParty/minizip/mz_compat.c
  ../Siv3D/src/ThirdParty/minizip/mz_crypt.c
  ../Siv3D/src/ThirdParty/minizip/mz_crypt_brg.c
  ../Siv3D/src/ThirdParty/minizip/mz_os.c
  ../Siv3D/src/ThirdParty/minizip/mz_os_posix.c
  ../Siv3D/src/ThirdParty/minizip/mz_strm.c
  ../Siv3D/src/ThirdParty/minizip/mz_strm_buf.c
  ../Siv3D/src/ThirdParty/minizip/mz_strm_mem.c
  ../Siv3D/src/ThirdParty/minizip/mz_strm_os_posix.c
  ../Siv3D/src/ThirdParty/minizip/mz_strm_pkcrypt.c
  ../Siv3D/src/ThirdParty/minizip/mz_strm_split.c
  ../Siv3D/src/ThirdParty/minizip/mz_strm_wzaes.c
  ../Siv3D/src/ThirdParty/minizip/mz_strm_zlib.c
  ../Siv3D/src/ThirdParty/minizip/mz_zip.c
  ../Siv3D/src/ThirdParty/minizip/mz_zip_rw.c

  ../Siv3D/src/ThirdParty/msdfgen/core/contour-combiners.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/Contour.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/edge-coloring.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/edge-segments.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/edge-selectors.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/EdgeHolder.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/equation-solver.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/msdf-edge-artifact-patcher.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/msdf-error-correction.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/msdfgen.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/rasterization.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/render-sdf.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/save-bmp.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/save-tiff.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/Scanline.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/sdf-error-estimation.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/shape-description.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/Shape.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/SignedDistance.cpp
  ../Siv3D/src/ThirdParty/msdfgen/core/Vector2.cpp

  ../Siv3D/src/ThirdParty/muparser/muParser.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserBase.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserBytecode.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserCallback.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserError.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserInt.cpp
  ../Siv3D/src/ThirdParty/muparser/muParserTokenReader.cpp
  
  ../Siv3D/src/ThirdParty/Oniguruma/ascii.c
  ../Siv3D/src/ThirdParty/Oniguruma/big5.c
  ../Siv3D/src/ThirdParty/Oniguruma/cp1251.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_jp.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_jp_prop.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_kr.c
  ../Siv3D/src/ThirdParty/Oniguruma/euc_tw.c
  ../Siv3D/src/ThirdParty/Oniguruma/gb18030.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_1.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_10.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_11.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_13.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_14.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_15.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_16.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_2.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_3.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_4.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_5.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_6.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_7.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_8.c
  ../Siv3D/src/ThirdParty/Oniguruma/iso8859_9.c
  ../Siv3D/src/ThirdParty/Oniguruma/koi8.c
  ../Siv3D/src/ThirdParty/Oniguruma/koi8_r.c
  ../Siv3D/src/ThirdParty/Oniguruma/onig_init.c
  ../Siv3D/src/ThirdParty/Oniguruma/regcomp.c
  ../Siv3D/src/ThirdParty/Oniguruma/regenc.c
  ../Siv3D/src/ThirdParty/Oniguruma/regerror.c
  ../Siv3D/src/ThirdParty/Oniguruma/regexec.c
  ../Siv3D/src/ThirdParty/Oniguruma/reggnu.c
  ../Siv3D/src/ThirdParty/Oniguruma/regparse.c
  ../Siv3D/src/ThirdParty/Oniguruma/regsyntax.c
  ../Siv3D/src/ThirdParty/Oniguruma/regtrav.c
  ../Siv3D/src/ThirdParty/Oniguruma/regversion.c
  ../Siv3D/src/ThirdParty/Oniguruma/sjis.c
  ../Siv3D/src/ThirdParty/Oniguruma/sjis_prop.c
  ../Siv3D/src/ThirdParty/Oniguruma/st.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_fold1_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_fold2_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_fold3_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/unicode_unfold_key.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf16_be.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf16_le.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf32_be.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf32_le.c
  ../Siv3D/src/ThirdParty/Oniguruma/utf8.c

  ../Siv3D/src/ThirdParty/pffft/pffft.c

  ../Siv3D/src/ThirdParty/plutovg/plutovg-blend.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg-dash.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg-geometry.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg-paint.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg-rle.c
  ../Siv3D/src/ThirdParty/plutovg/plutovg.c
  ../Siv3D/src/ThirdParty/plutovg/sw_ft_math.c
  ../Siv3D/src/ThirdParty/plutovg/sw_ft_raster.c
  ../Siv3D/src/ThirdParty/plutovg/sw_ft_stroker.c

  ../Siv3D/src/ThirdParty/qr-code-generator-library/qrcodegen.cpp

  ../Siv3D/src/ThirdParty/quirc/decode.c
  ../Siv3D/src/ThirdParty/quirc/identify.c
  ../Siv3D/src/ThirdParty/quirc/quirc.c
  ../Siv3D/src/ThirdParty/quirc/version_db.c

  ../Siv3D/src/ThirdParty/RecastDetour/DetourAlloc.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourAssert.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourCommon.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourNavMesh.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourNavMeshBuilder.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourNavMeshQuery.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/DetourNode.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/Recast.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastAlloc.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastArea.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastAssert.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastContour.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastFilter.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastLayers.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastMesh.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastMeshDetail.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastRasterization.cpp
  ../Siv3D/src/ThirdParty/RecastDetour/RecastRegion.cpp

  ../Siv3D/src/ThirdParty/rtaudio/RtAudio.cpp

  ../Siv3D/src/ThirdParty/serial/impl/list_ports/list_ports_linux.cc
  ../Siv3D/src/ThirdParty/serial/impl/unix.cc
  ../Siv3D/src/ThirdParty/serial/serial.cc

  ../Siv3D/src/ThirdParty/soloud/src/audiosource/monotone/soloud_monotone.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/noise/soloud_noise.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/sfxr/soloud_sfxr.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/darray.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/klatt.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/resonator.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/soloud_speech.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/speech/tts.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/tedsid/sid.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/tedsid/soloud_tedsid.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/tedsid/ted.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/vic/soloud_vic.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/vizsn/soloud_vizsn.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/wav/dr_impl.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/wav/soloud_wav.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/wav/soloud_wavstream.cpp
  ../Siv3D/src/ThirdParty/soloud/src/audiosource/wav/stb_vorbis.c
  ../Siv3D/src/ThirdParty/soloud/src/backend/alsa/soloud_alsa.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/coreaudio/soloud_coreaudio.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/jack/soloud_jack.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/miniaudio/soloud_miniaudio.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/nosound/soloud_nosound.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/null/soloud_null.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/openal/soloud_openal.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/openal/soloud_openal_dll.c
  ../Siv3D/src/ThirdParty/soloud/src/backend/opensles/soloud_opensles.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/oss/soloud_oss.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/portaudio/soloud_portaudio.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/portaudio/soloud_portaudio_dll.c
  ../Siv3D/src/ThirdParty/soloud/src/backend/sdl2_static/soloud_sdl2_static.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/sdl/soloud_sdl1.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/sdl/soloud_sdl1_dll.c
  ../Siv3D/src/ThirdParty/soloud/src/backend/sdl/soloud_sdl2.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/sdl/soloud_sdl2_dll.c
  ../Siv3D/src/ThirdParty/soloud/src/backend/sdl_static/soloud_sdl_static.cpp
  # ../Siv3D/src/ThirdParty/soloud/src/backend/vita_homebrew/soloud_vita_homebrew.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/wasapi/soloud_wasapi.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/winmm/soloud_winmm.cpp
  ../Siv3D/src/ThirdParty/soloud/src/backend/xaudio2/soloud_xaudio2.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_audiosource.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_bus.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_3d.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_basicops.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_faderops.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_filterops.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_getters.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_setters.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_voicegroup.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_core_voiceops.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_fader.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_fft.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_fft_lut.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_file.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_filter.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_misc.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_queue.cpp
  ../Siv3D/src/ThirdParty/soloud/src/core/soloud_thread.cpp
  ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_biquadresonantfilter.cpp
  ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_dcremovalfilter.cpp
  ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_echofilter.cpp
  ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_eqfilter.cpp
  ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_fftfilter.cpp
  ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_flangerfilter.cpp
  ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_freeverbfilter.cpp
  ../Siv3D/src/ThirdParty/soloud/src/filter/soloud_lofifilter.cpp

  ../Siv3D/src/ThirdParty/SplineLib/Splines.cpp

  ../Siv3D/src/ThirdParty/tinyobjloader/tiny_obj_loader.cc

  ../Siv3D/src/ThirdParty/tinyxml/tinyxml2.cpp

  ../Siv3D/src/ThirdParty/zstd/common/debug.c
  ../Siv3D/src/ThirdParty/zstd/common/entropy_common.c
  ../Siv3D/src/ThirdParty/zstd/common/error_private.c
  ../Siv3D/src/ThirdParty/zstd/common/fse_decompress.c
  ../Siv3D/src/ThirdParty/zstd/common/pool.c
  ../Siv3D/src/ThirdParty/zstd/common/threading.c
  ../Siv3D/src/ThirdParty/zstd/common/xxhash.c
  ../Siv3D/src/ThirdParty/zstd/common/zstd_common.c
  ../Siv3D/src/ThirdParty/zstd/compress/fse_compress.c
  ../Siv3D/src/ThirdParty/zstd/compress/hist.c
  ../Siv3D/src/ThirdParty/zstd/compress/huf_compress.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstdmt_compress.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_compress.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_compress_literals.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_compress_sequences.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_compress_superblock.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_double_fast.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_fast.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_lazy.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_ldm.c
  ../Siv3D/src/ThirdParty/zstd/compress/zstd_opt.c
  ../Siv3D/src/ThirdParty/zstd/decompress/huf_decompress.c
  ../Siv3D/src/ThirdParty/zstd/decompress/zstd_ddict.c
  ../Siv3D/src/ThirdParty/zstd/decompress/zstd_decompress.c
  ../Siv3D/src/ThirdParty/zstd/decompress/zstd_decompress_block.c
  ../Siv3D/src/ThirdParty/zstd/dictBuilder/cover.c
  ../Siv3D/src/ThirdParty/zstd/dictBuilder/divsufsort.c
  ../Siv3D/src/ThirdParty/zstd/dictBuilder/fastcover.c
  ../Siv3D/src/ThirdParty/zstd/dictBuilder/zdict.c
)



set(SIV3D_WEBGPU_SOURCES
  ../Siv3D/src/Siv3D-Platform/Web/Siv3D/Renderer/WebGPU/CRenderer_WebGPU.cpp

  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/ConstantBuffer/WebGPU/ConstantBufferDetail_WebGPU.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Mesh/WebGPU/CMesh_WebGPU.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Mesh/WebGPU/WebGPUMesh.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Renderer/WebGPU/BackBuffer/WebGPUBackBuffer.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Renderer/WebGPU/BackBuffer/WebGPUInternalTexture2D.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Renderer/WebGPU/SamplerState/WebGPUSamplerState.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Renderer2D/WebGPU/CRenderer2D_WebGPU.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Renderer2D/WebGPU/WebGPURenderer2DCommand.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Renderer2D/WebGPU/WebGPUVertex2DBatch.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Renderer3D/WebGPU/CRenderer3D_WebGPU.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Renderer3D/WebGPU/WebGPULine3DBatch.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Renderer3D/WebGPU/WebGPURenderer3DCommand.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Shader/WebGPU/CShader_WebGPU.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Shader/WebGPU/PixelShader/WebGPUPixelShader.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Shader/WebGPU/VertexShader/WebGPUVertexShader.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Shader/WebGPU/ShaderPipeline/WebGPUShaderPipeline.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Shader/WebGPU/UniformState/WebGPUUniformState.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Texture/WebGPU/CTexture_WebGPU.cpp
  ../Siv3D/src/Siv3D-Platform/WebGPU/Siv3D/Texture/WebGPU/WebGPUTexture.cpp
)



set(SIV3D_SCRIPT_SOURCES
  ../Siv3D/src/Siv3D/Script/angelscript/scriptarray.cpp
  ../Siv3D/src/Siv3D/Script/angelscript/scriptbuilder.cpp
  ../Siv3D/src/Siv3D/Script/angelscript/scriptgrid.cpp
  ../Siv3D/src/Siv3D/Script/angelscript/scriptstdstring.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptAudio.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptAudioFormat.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptBezier2.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptBezier3.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptCamera2D.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptCameraControl.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptChar.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptCircle.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptCircular.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptColor.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptColorF.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptCopyOption.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptCursor.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptCursorStyle.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptDate.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptDateTime.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptDialog.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptDrawableText.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptDuration.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptDynamicTexture.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptEasing.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptEllipse.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptEmoji.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFileSystem.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFloat2.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFloat3.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFloat4.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFloatingPoint.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFloatRect.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFont.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFontMethod.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFontStyle.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptFormat.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptGlobalAudio.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptGMInstrument.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptGraphics.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptGraphics2D.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptHSV.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptIcon.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptImage.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptImageFormat.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptINI.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptInput.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptInterpolation.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptKeyboard.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptLanguageCode.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptLine.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptLineString.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptLineStyle.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptLineStyleParameters.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptMat3x2.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptMath.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptMathConstants.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptMicrosecClock.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptMillisecClock.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptMixBus.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptMonitor.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptMouse.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptNamedParameter.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptNone_t.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptNumber.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptOffsetCircular.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptOpenMode.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptOptional.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptPalette.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptParse.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptPeriodic.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptPianoKey.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptPoint.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptPolygon.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptPrimeNumber.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptPrint.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptProfiler.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptPutText.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptQuad.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptRandom.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptRDTSCClock.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptRect.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptRectF.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptResizeMode.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptResource.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptRoundRect.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptSay.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptScene.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptScopedViewport2D.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptShape2D.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptSimpleGUI.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptSpecialFolder.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptSpline2D.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptStopwatch.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptSystem.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextEditState.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextEncoding.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextInput.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextInputMode.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextReader.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextStyle.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextToSpeech.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTexture.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTexturedCircle.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextureDesc.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTexturedQuad.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTexturedRoundRect.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextureFormat.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTexturePixelFormat.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextureRegion.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTextWriter.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptThreading.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTime.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTimer.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTransformer2D.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTriangle.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTriangleIndex.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTypeface.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptTypes.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptUserAction.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptUtility.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptVariableSpeedStopwatch.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptVec2.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptVec3.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptVec4.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptVideoTexture.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptWave.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptWaveSample.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptWindow.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptWindowStyle.cpp
  ../Siv3D/src/Siv3D/Script/Bind/ScriptYesNo.cpp
  ../Siv3D/src/Siv3D/Script/CScript.cpp

  ../Siv3D/src/ThirdParty/angelscript/as_atomic.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_builder.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_bytecode.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_callfunc.cpp
	../Siv3D/src/ThirdParty/angelscript/as_callfunc_wasm32.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_compiler.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_configgroup.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_context.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_datatype.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_gc.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_generic.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_globalproperty.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_memory.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_module.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_objecttype.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_outputbuffer.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_parser.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_restore.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_scriptcode.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_scriptengine.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_scriptfunction.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_scriptnode.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_scriptobject.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_string.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_string_util.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_thread.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_tokenizer.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_typeinfo.cpp
  ../Siv3D/src/ThirdParty/angelscript/as_variablescope.cpp
)



add_library(
  OpenSiv3D STATIC
  ${SIV3D_SOURCES}
  ${SIV3D_THIRDPARTY_SOURCES}
)

set_target_properties(OpenSiv3D 
  PROPERTIES 
    OUTPUT_NAME "Siv3D"
)

target_include_directories(OpenSiv3D
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../Siv3D/include>
    $<INSTALL_INTERFACE:include/Siv3D> 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../Siv3D/include/ThirdParty>
    $<INSTALL_INTERFACE:include/Siv3D/ThirdParty> 
  PRIVATE
    ../Siv3D/src
    ../Siv3D/src/Siv3D-Platform/Web
    ../Siv3D/src/Siv3D-Platform/macOS_Linux
    ../Siv3D/src/Siv3D-Platform/OpenGLES3
    ../Siv3D/src/Siv3D-Platform/WebGPU
    ../Siv3D/src/ThirdParty
    ../Siv3D/src/ThirdParty/asio
    ../Siv3D/src/ThirdParty/freetype
    ../Siv3D/src/ThirdParty/soloud/include
    ../Siv3D/src/ThirdParty-prebuilt
    ../Dependencies/boost_1_74_0
    ${SIV3D_THIRD_PARTY_INCLUDE_DIRS}
)



add_library(
  OpenSiv3DWebGPU STATIC
  ${SIV3D_WEBGPU_SOURCES}
)

set_target_properties(OpenSiv3DWebGPU
  PROPERTIES 
    OUTPUT_NAME "Siv3DWebGPU"
)

target_include_directories(
  OpenSiv3DWebGPU
  PRIVATE
    ../Siv3D/include
    ../Siv3D/include/ThirdParty
    ../Siv3D/src
    ../Siv3D/src/Siv3D-Platform/Web
    ../Siv3D/src/Siv3D-Platform/macOS_Linux
    ../Siv3D/src/Siv3D-Platform/OpenGLES3
    ../Siv3D/src/Siv3D-Platform/WebGPU
    ../Siv3D/src/ThirdParty
    ../Siv3D/src/ThirdParty/asio
    ../Siv3D/src/ThirdParty/freetype
    ../Siv3D/src/ThirdParty/soloud/include
    ../Siv3D/src/ThirdParty-prebuilt
    ../Dependencies/boost_1_74_0
    ${SIV3D_THIRD_PARTY_INCLUDE_DIRS}
)



add_library(
  OpenSiv3DScript STATIC
  ${SIV3D_SCRIPT_SOURCES}
)

set_target_properties(OpenSiv3DScript
  PROPERTIES 
    OUTPUT_NAME "Siv3DScript"
)

target_include_directories(
  OpenSiv3DScript
  PRIVATE
    ../Siv3D/include
    ../Siv3D/include/ThirdParty
    ../Siv3D/src
    ../Siv3D/src/Siv3D-Platform/Web
    ../Siv3D/src/Siv3D-Platform/macOS_Linux
    ../Siv3D/src/Siv3D-Platform/OpenGLES3
    ../Siv3D/src/Siv3D-Platform/WebGPU
    ../Siv3D/src/ThirdParty
    ../Siv3D/src/ThirdParty/asio
    ../Siv3D/src/ThirdParty/freetype
    ../Siv3D/src/ThirdParty/soloud/include
    ../Siv3D/src/ThirdParty-prebuilt
    ../Dependencies/boost_1_74_0
    ${SIV3D_THIRD_PARTY_INCLUDE_DIRS}
)



add_library(
  OpenSiv3DBrowserImageEncodeDecode STATIC
    ../Siv3D/src/Siv3D-Platform/Web/Siv3D/ImageFormat/Generic/GenericDecoder.cpp
    ../Siv3D/src/Siv3D-Platform/Web/Siv3D/ImageDecoder/CImageDecoder.cpp
    ../Siv3D/src/Siv3D-Platform/Web/Siv3D/ImageEncoder/CImageEncoder.cpp
)

set_target_properties(OpenSiv3DBrowserImageEncodeDecode
  PROPERTIES 
    OUTPUT_NAME "Siv3DBrowserImageEncodeDecode"
)

target_include_directories(
  OpenSiv3DBrowserImageEncodeDecode
  PRIVATE
    ../Siv3D/include
    ../Siv3D/include/ThirdParty
    ../Siv3D/src
    ../Siv3D/src/Siv3D-Platform/Web
    ../Siv3D/src/Siv3D-Platform/macOS_Linux
    ../Siv3D/src/Siv3D-Platform/OpenGLES3
    ../Siv3D/src/Siv3D-Platform/WebGPU
    ../Siv3D/src/ThirdParty
    ../Siv3D/src/ThirdParty/asio
    ../Siv3D/src/ThirdParty/freetype
    ../Siv3D/src/ThirdParty/soloud/include
    ../Siv3D/src/ThirdParty-prebuilt
    ../Dependencies/boost_1_74_0
    ${SIV3D_THIRD_PARTY_INCLUDE_DIRS}
)



include(GNUInstallDirs)

if (BUILD_SHARED_LIBS)
  set(Siv3DLibraryConfig "wasm-shared")
  set(Siv3DLibraryPostfix ".wasm.a")
elseif (Siv3DEnablePICBuild)
  set(Siv3DLibraryConfig "wasm-side-module")
  set(Siv3DLibraryPostfix ".a")
elseif (Siv3DEnablePThread AND Siv3DEnableSIMD)
  set(Siv3DLibraryConfig "wasm-mt-simd")
  set(Siv3DLibraryPostfix ".a")
elseif (Siv3DEnablePThread)
  set(Siv3DLibraryConfig "wasm-mt")
  set(Siv3DLibraryPostfix ".a")
elseif (Siv3DEnableSIMD)
  set(Siv3DLibraryConfig "wasm-simd")
  set(Siv3DLibraryPostfix ".a")
else()
  set(Siv3DLibraryConfig "wasm")
  set(Siv3DLibraryPostfix ".a")
endif()

target_link_libraries(OpenSiv3D
  PUBLIC
    \${_IMPORT_PREFIX}/lib/Siv3D/opencv/libopencv_objdetect${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/opencv/libopencv_photo${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/opencv/libopencv_imgproc${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/opencv/libopencv_core${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/harfbuzz/libharfbuzz${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/freetype/libfreetype${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/turbojpeg/libturbojpeg${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/giflib/libgif${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/webp/libwebp${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/opus/libopusfile${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/opus/libopus${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/tiff/libtiff${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/png/libpng${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/zlib/libz${Siv3DLibraryPostfix}
    \${_IMPORT_PREFIX}/lib/Siv3D/SDL2/libSDL2${Siv3DLibraryPostfix}
)

install(TARGETS OpenSiv3D
  EXPORT OpenSiv3DExport
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT OpenSiv3DExport
  FILE OpenSiv3DConfig.cmake
  DESTINATION share/cmake/OpenSiv3D/
)

install(TARGETS OpenSiv3DBrowserImageEncodeDecode
  EXPORT OpenSiv3DBrowserImageEncodeDecodeExport
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT OpenSiv3DBrowserImageEncodeDecodeExport
  FILE OpenSiv3DBrowserImageEncodeDecodeConfig.cmake
  DESTINATION share/cmake/OpenSiv3DBrowserImageEncodeDecode/
)

install(TARGETS OpenSiv3DScript
  EXPORT OpenSiv3DScriptExport
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT OpenSiv3DScriptExport
  FILE OpenSiv3DScriptConfig.cmake
  DESTINATION share/cmake/OpenSiv3DScript/
)

install(TARGETS OpenSiv3DWebGPU
  EXPORT OpenSiv3DWebGPUExport
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(EXPORT OpenSiv3DWebGPUExport
  FILE OpenSiv3DWebGPUConfig.cmake
  DESTINATION share/cmake/OpenSiv3DWebGPU/
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/../Siv3D/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Siv3D)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/../Siv3D/lib/Web/${Siv3DLibraryConfig}/ DESTINATION ${CMAKE_INSTALL_LIBDIR}/Siv3D)
install(FILES
    ${PROJECT_SOURCE_DIR}/Siv3D.js
    ${PROJECT_SOURCE_DIR}/Siv3D.post.js
    ${PROJECT_SOURCE_DIR}/Siv3D.pre.js
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/Siv3D
)
