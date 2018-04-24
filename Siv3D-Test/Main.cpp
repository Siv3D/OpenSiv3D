
# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	TCPServer server;
	server.startAcceptMulti(50000);
	Point n1(0,0);
	int32 n2=0;

	while (System::Update())
	{
		ClearPrint();
		Print << Network::GetPrivateIPv4();
		Print << server.port();
		Print << U"isAccepting: " << server.isAccepting();
		Print << server.num_sessions();
		Print << server.getSessionIDs();
		Print << server.available(1);
		Print << server.available(2);

		while (server.read(n1, 1))
		{
			server.send(n1.x + n1.y);
		}

		while (server.read(n2, 2))
		{

		}

		Print << n1;
		Print << n2;
	}
}
