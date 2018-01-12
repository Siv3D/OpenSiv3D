if [ $# -ne 1 ]; then
	echo "usage : a.sh [file].cpp"
	exit 1
fi

g++ --std=c++17 -Wall -Wextra -Wno-unknown-pragmas -I[path/to/OpenSiv3D/Siv3D/Include] -I/usr/include -O2 -DNDEBUG -march=x86-64 -o $1 $1.cpp [path/to/libSiv3D.a(Release)] [path/to/OpenSiv3D/Siv3D/Lib/Linux/harfbuzz/libharfbuzz.a] [path/to/OpenSiv3D/Siv3D/Lib/Linux/angelscript/libangelscript.a] [path/to/OpenSiv3D/Siv3D/Lib/Linux/giflib/libgif.a] -lboost_filesystem -lboost_system -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lpthread -lGL -lpng -lturbojpeg -lX11 -lXi -lXrandr -lXinerama -lXcursor -ldl -lGLEW -lfreetype -lopenal
