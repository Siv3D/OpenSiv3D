
# include <Siv3D.hpp>
# include <HamFramework.hpp>

void Main()
{
	///*
	TCPClient client;
	const IPv4 ip(IPv4::localhost());
	client.connect(ip, 50000);

	int32 n = 0;

	while (System::Update())
	{
		ClearPrint();
		Print << U"Client {}fps"_fmt(Profiler::FPS());
		Print << U"client.isConnected(): " << client.isConnected();
		Print << U"client.hasError(): " << client.hasError();

		if (client.isConnected())
		{
			client.send(Cursor::Pos());

			while (client.read(n))
			{

			}
		}

		if (client.hasError())
		{
			client.disconnect();
		}

		if (KeyC.down())
		{
			client.connect(ip, 50000);
		}

		if (KeyD.down())
		{
			client.disconnect();
		}

		Print << n;
	}
	//*/

	/*
	TCPClient client1, client2;
	client1.connect(IPv4::localhost(), 50000);
	int32 n1 = 0, n2 = 0;

	while (System::Update())
	{
		ClearPrint();
		Print << U"Client {}fps"_fmt(Profiler::FPS());
		Print << U"client1.isConnected(): " << client1.isConnected();
		Print << U"client2.isConnected(): " << client2.isConnected();
		Print << U"client1.hasError(): " << client1.hasError();
		Print << U"client2.hasError(): " << client2.hasError();

		if (client1.isConnected())
		{
			client1.send(Cursor::Pos());

			while (client1.read(n1))
			{

			}
		}

		if (client2.isConnected())
		{
			client2.send(Cursor::Pos());

			while (client2.read(n2))
			{

			}
		}

		if (client1.hasError())
		{
			client1.disconnect();
		}

		if (client2.hasError())
		{
			client2.disconnect();
		}

		if (Key1.down())
		{
			Logger << U"try c1";
			client1.connect(IPv4::localhost(), 50000);
		}

		if (Key2.down())
		{
			Logger << U"try c2";
			client2.connect(IPv4::localhost(), 50000);
		}

		if (Key3.down())
		{
			client1.disconnect();
		}

		if (Key4.down())
		{
			client2.disconnect();
		}

		Print << n1;
		Print << n2;
	}
	//*/

	/*
	TCPServer server;
	server.startAcceptMulti(50000);

	while (System::Update())
	{
		ClearPrint();
		Print << Network::GetPrivateIPv4();
		Print << U"Server {}fps"_fmt(Profiler::FPS());
		Print << server.num_sessions();
		Print << server.getSessionIDs();

		for (;;)
		{
			bool update = false;

			Point p(0, 0);

			for (const auto& sessionID : server.getSessionIDs())
			{
				if (server.read(p, sessionID))
				{
					server.send(p.x + p.y, sessionID);

					update = true;
				}
			}

			if (!update)
			{
				break;
			}
		}
	}
	//*/
}
