if [ $# -ne 1 ]; then
	echo "usage : a.sh [file].cpp"
	exit 1
fi

g++ --std=c++17 -Wall -Wextra -Wno-unknown-pragmas -I[path/to/OpenSiv3D/Siv3D/Include] -I/usr/include -g3 -O0 -pg -o $1 $1.cpp [path/to/libSiv3D.a(Debug)] [path/to/OpenSiv3D/Siv3D/Lib/Linux/harfbuzz/libharfbuzz.a] [path/to/OpenSiv3D/Siv3D/Linux/Lib/angelscript/libangelscript.a] -lboost_filesystem -lboost_system -lglib-2.0 -lgio-2.0 -lgobject-2.0 -lpthread -lGL -lpng -lturbojpeg -lX11 -lXi -lXrandr -lXinerama -lXcursor -ldl -lgif -lGLEW -lfreetype
