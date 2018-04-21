
# include <Siv3D.hpp>

void Main()
{
	TCPServer server;

	server.start(3001);

	while (System::Update())
	{

	}
}
