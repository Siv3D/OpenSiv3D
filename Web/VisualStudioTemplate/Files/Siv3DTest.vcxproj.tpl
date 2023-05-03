<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" ToolsVersion="15.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|Emscripten">
      <Configuration>Debug</Configuration>
      <Platform>Emscripten</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|Emscripten">
      <Configuration>Release</Configuration>
      <Platform>Emscripten</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <VCProjectVersion>15.0</VCProjectVersion>
    <ProjectGuid>{$guid1$}</ProjectGuid>
    <RootNamespace>$safeprojectname$</RootNamespace>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v141</PlatformToolset>
    <CharacterSet>MultiByte</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v141</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>MultiByte</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v141</PlatformToolset>
    <CharacterSet>MultiByte</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v141</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>MultiByte</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Label="Configuration" Condition="'$(Configuration)|$(Platform)'=='Debug|Emscripten'">
    <ConfigurationType>HTMLPage</ConfigurationType>
    <PlatformToolset>emcc</PlatformToolset>
    <EmscriptenDir>$(EMSDK)\upstream\emscripten\</EmscriptenDir>
  </PropertyGroup>
  <PropertyGroup Label="Configuration" Condition="'$(Configuration)|$(Platform)'=='Release|Emscripten'">
    <ConfigurationType>HTMLPage</ConfigurationType>
    <PlatformToolset>emcc</PlatformToolset>
    <EmscriptenDir>$(EMSDK)\upstream\emscripten\</EmscriptenDir>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Label="Shared">
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Emscripten'">
    <IncludePath>$(SIV3D_0_6_6_WEB)\include;$(SIV3D_0_6_6_WEB)\include\ThirdParty;$(IncludePath)</IncludePath>
    <LibraryPath>$(SIV3D_0_6_6_WEB)\lib\freetype;$(SIV3D_0_6_6_WEB)\lib\giflib;$(SIV3D_0_6_6_WEB)\lib\harfbuzz;$(SIV3D_0_6_6_WEB)\lib\opencv;$(SIV3D_0_6_6_WEB)\lib\turbojpeg;$(SIV3D_0_6_6_WEB)\lib\webp;$(SIV3D_0_6_6_WEB)\lib\opus;$(SIV3D_0_6_6_WEB)\lib\tiff;$(SIV3D_0_6_6_WEB)\lib\png;$(SIV3D_0_6_6_WEB)\lib\zlib;$(SIV3D_0_6_6_WEB)\lib\SDL2;$(SIV3D_0_6_6_WEB)\lib</LibraryPath>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Emscripten'">
    <IncludePath>$(SIV3D_0_6_6_WEB)\include;$(SIV3D_0_6_6_WEB)\include\ThirdParty;$(IncludePath)</IncludePath>
    <LibraryPath>$(SIV3D_0_6_6_WEB)\lib\freetype;$(SIV3D_0_6_6_WEB)\lib\giflib;$(SIV3D_0_6_6_WEB)\lib\harfbuzz;$(SIV3D_0_6_6_WEB)\lib\opencv;$(SIV3D_0_6_6_WEB)\lib\turbojpeg;$(SIV3D_0_6_6_WEB)\lib\webp;$(SIV3D_0_6_6_WEB)\lib\opus;$(SIV3D_0_6_6_WEB)\lib\tiff;$(SIV3D_0_6_6_WEB)\lib\png;$(SIV3D_0_6_6_WEB)\lib\zlib;$(SIV3D_0_6_6_WEB)\lib\SDL2;$(SIV3D_0_6_6_WEB)\lib</LibraryPath>
  </PropertyGroup>
  <ItemGroup>
    <ClCompile Include="Main.cpp" />
  </ItemGroup>
  <ItemGroup>
${ResourcesItems}
  </ItemGroup>
  <ItemGroup>
${ExampleItems}
  </ItemGroup>
  <ItemGroup>
    <None Include="Templates\Embeddable\web-player.html" />
    <None Include="Templates\Embeddable\web-player.js" />
  </ItemGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Emscripten'">
    <Link>
      <PreloadFile>$(ProjectDir)\resources@/resources;</PreloadFile>
      <AdditionalOptions>-s USE_OGG=1 -s USE_VORBIS=1 -s WARN_ON_UNDEFINED_SYMBOLS=0 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s FULL_ES3=1 -s USE_WEBGPU=1 -s USE_GLFW=3 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s MODULARIZE=1
  -s EXCEPTION_CATCHING_ALLOWED=["main","_ZN3s3d7TryMainEv"] -s ASYNCIFY=1 -s ASYNCIFY_IGNORE_INDIRECT=1
  -s ASYNCIFY_IMPORTS="[ 'siv3dRequestAnimationFrame', 'siv3dGetClipboardText', 'siv3dDecodeImageFromFile', 'siv3dSleepUntilWaked', 'invoke_vi', 'invoke_v' ]"
  -s ASYNCIFY_ADD="[ 'main','Main()','dynCall_v','dynCall_vi','s3d::TryMain()','s3d::CSystem::init()','s3d::System::Update()','s3d::AACDecoder::decode(*) const','s3d::MP3Decoder::decode(*) const','s3d::CAudioDecoder::decode(*)','s3d::AudioDecoder::Decode(*)','s3d::Wave::Wave(*)','s3d::Audio::Audio(*)','s3d::Clipboard::GetText(*)','s3d::CClipboard::getText(*)','s3d::GenericDecoder::decode(*) const','s3d::CImageDecoder::decode(*)','s3d::Image::Image(*)','s3d::Texture::Texture(*)','s3d::ImageDecoder::Decode(*)','s3d::ImageDecoder::GetImageInfo(*)','s3d::Model::Model(*)','s3d::CModel::create(*)','s3d::CRenderer2D_GLES3::init()','s3d::CRenderer2D_WebGPU::init()','s3d::Clipboard::GetText(*)','s3d::CClipboard::getText(*)','s3d::SimpleHTTP::Save(*)','s3d::SimpleHTTP::Load(*)','s3d::SimpleHTTP::Get(*)','s3d::SimpleHTTP::Post(*)','s3d::VideoReader::VideoReader(*)','s3d::VideoReader::open(*)','s3d::Platform::Web::FetchFile(*)' ]" %(AdditionalOptions)</AdditionalOptions>
      <AdditionalLinkDirectories>$(LibraryPath);%(AdditionalLinkDirectories)</AdditionalLinkDirectories>
      <AdditionalDependencies>Siv3DScript;Siv3D;opencv_objdetect;opencv_photo;opencv_imgproc;opencv_core;harfbuzz;freetype;turbojpeg;gif;webp;opusfile;opus;tiff;png;z;SDL2;</AdditionalDependencies>
      <EchoCommandLines>false</EchoCommandLines>
      <JsLibrary>$(SIV3D_0_6_6_WEB)\lib\Siv3D.js;</JsLibrary>
      <PreJsFile>$(SIV3D_0_6_6_WEB)\lib\Siv3D.pre.js;</PreJsFile>
      <PostJsFile>$(ProjectDir)\Templates\Embeddable\web-player.js;$(SIV3D_0_6_6_WEB)\lib\Siv3D.post.js;</PostJsFile>
      <HtmlShellFile>$(ProjectDir)\Templates\Embeddable\web-player.html</HtmlShellFile>
      <EnableMemoryGrowth>true</EnableMemoryGrowth>
      <EmRun>true</EmRun>
      <IncludedAssetTargets></IncludedAssetTargets>
    </Link>
    <ClCompile>
      <AdditionalIncludeDirectories>$(IncludePath);</AdditionalIncludeDirectories>
      <LanguageStandard>stdcpplatest</LanguageStandard>
      <AdditionalOptions>-D_XM_NO_INTRINSICS_</AdditionalOptions>
    </ClCompile>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Emscripten'">
    <ClCompile>
      <AdditionalIncludeDirectories>$(IncludePath);</AdditionalIncludeDirectories>
      <LanguageStandard>stdcpplatest</LanguageStandard>
      <AdditionalOptions>-D_XM_NO_INTRINSICS_</AdditionalOptions>
    </ClCompile>
    <Link>
      <AdditionalOptions>-s USE_OGG=1 -s USE_VORBIS=1 -s WARN_ON_UNDEFINED_SYMBOLS=0 -s ERROR_ON_UNDEFINED_SYMBOLS=0 -s FULL_ES3=1 -s USE_WEBGPU=1 -s USE_GLFW=3 -s MIN_WEBGL_VERSION=2 -s MAX_WEBGL_VERSION=2 -s MODULARIZE=1
  -s ASYNCIFY=1 -s ASYNCIFY_IGNORE_INDIRECT=1
  -s ASYNCIFY_IMPORTS="[ 'siv3dRequestAnimationFrame', 'siv3dGetClipboardText', 'siv3dDecodeImageFromFile', 'siv3dSleepUntilWaked', 'invoke_vi', 'invoke_v' ]"
  -s ASYNCIFY_ADD="[ 'main','Main()','dynCall_v','dynCall_vi','s3d::TryMain()','s3d::CSystem::init()','s3d::System::Update()','s3d::AACDecoder::decode(*) const','s3d::MP3Decoder::decode(*) const','s3d::CAudioDecoder::decode(*)','s3d::AudioDecoder::Decode(*)','s3d::Wave::Wave(*)','s3d::Audio::Audio(*)','s3d::Clipboard::GetText(*)','s3d::CClipboard::getText(*)','s3d::GenericDecoder::decode(*) const','s3d::CImageDecoder::decode(*)','s3d::Image::Image(*)','s3d::Texture::Texture(*)','s3d::ImageDecoder::Decode(*)','s3d::ImageDecoder::GetImageInfo(*)','s3d::Model::Model(*)','s3d::CModel::create(*)','s3d::CRenderer2D_GLES3::init()','s3d::CRenderer2D_WebGPU::init()','s3d::Clipboard::GetText(*)','s3d::CClipboard::getText(*)','s3d::SimpleHTTP::Save(*)','s3d::SimpleHTTP::Load(*)','s3d::SimpleHTTP::Get(*)','s3d::SimpleHTTP::Post(*)','s3d::VideoReader::VideoReader(*)','s3d::VideoReader::open(*)','s3d::Platform::Web::FetchFile(*)' ]" %(AdditionalOptions)</AdditionalOptions>
      <AdditionalDependencies>Siv3DScript;Siv3D;opencv_objdetect;opencv_photo;opencv_imgproc;opencv_core;harfbuzz;freetype;turbojpeg;gif;webp;opusfile;opus;tiff;png;z;SDL2;</AdditionalDependencies>
      <PreloadFile>$(ProjectDir)\resources@/resources;</PreloadFile>
      <JsLibrary>$(SIV3D_0_6_6_WEB)\lib\Siv3D.js;</JsLibrary>
      <PreJsFile>$(SIV3D_0_6_6_WEB)\lib\Siv3D.pre.js;</PreJsFile>
      <PostJsFile>$(ProjectDir)\Templates\Embeddable\web-player.js;$(SIV3D_0_6_6_WEB)\lib\Siv3D.post.js;</PostJsFile>
      <HtmlShellFile>$(ProjectDir)\Templates\Embeddable\web-player.html</HtmlShellFile>
      <AdditionalLinkDirectories>$(LibraryPath);%(AdditionalLinkDirectories)</AdditionalLinkDirectories>
      <EchoCommandLines>false</EchoCommandLines>
      <EnableMemoryGrowth>true</EnableMemoryGrowth>
      <EmRun>true</EmRun>
      <IncludedAssetTargets></IncludedAssetTargets>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(DesignTimeBuild)'=='true' and '$(Platform)'=='Emscripten'">
    <ClCompile>
      <AdditionalOptions>-D_XM_NO_INTRINSICS_ -DSIMDE_NO_VECTOR -DFMT_USE_NONTYPE_TEMPLATE_PARAMETERS=0</AdditionalOptions>
    </ClCompile>
  </ItemDefinitionGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>