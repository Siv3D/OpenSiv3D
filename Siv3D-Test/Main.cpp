
# include <Siv3D.hpp>

void Main()
{
	{
		const String s = U"AB";
		const String kk = s + s;
		const String kc = s + U'C';
		const String ks = s + U"C";
		const String kV = s + StringView(U"C");
		const String kv = s + U"C"sv;
		const String kr = s + String(U"C");

		const StringView V = StringView(U"AB");
		const String Vk = V + s;
		const String Vc = V + U'C';
		const String Vs = V + U"C";
		const String VV = V + StringView(U"C");
		const String Vv = V + U"C"sv;
		const String Vr = V + String(U"C");

		const std::u32string_view v = U"AB"sv;
		const String vk = v + s;
		const String vc = v + U'C';
		const String vs = v + U"C";
		const String vV = v + StringView(U"C");
		const String vv = v + U"C"sv;
		const String vr = v + String(U"C");

		const String rk = String(U"AB") + s;
		const String rc = String(U"AB") + U'C';
		const String rs = String(U"AB") + U"C";
		const String rV = String(U"AB") + StringView(U"C");
		const String rv = String(U"AB") + U"C"sv;
		const String rr = String(U"AB") + String(U"C");

		const String ck = U'C' + s;
		//const String cc = U'C' + U'C';
		//const String cs = U'C' + U"C";
		const String cV = U'C' + StringView(U"C");
		const String cv = U'C' + U"C"sv;
		const String cr = U'C' + String(U"C");

		const String sk = U"AB" + s;
		//const String sc = U"AB" + U'C';
		//const String ss = U"AB" + U"C";
		const String sV = U"AB" + StringView(U"C");
		const String sv = U"AB" + U"C"sv;
		const String sr = U"AB" + String(U"C");
	}

	{
		const String s = U"AB";
		const bool kk = s == s;
		//const bool kc = s == U'C';
		const bool ks = s == U"C";
		const bool kV = s == StringView(U"C");
		const bool kv = s == U"C"sv;
		const bool kr = s == String(U"C");

		const StringView V = StringView(U"AB");
		const bool Vk = V == s;
		//const bool Vc = V == U'C';
		const bool Vs = V == U"C";
		const bool VV = V == StringView(U"C");
		const bool Vv = V == U"C"sv;
		const bool Vr = V == String(U"C");

		const std::u32string_view v = U"AB"sv;
		const bool vk = v == s;
		//const bool vc = v == U'C';
		const bool vs = v == U"C";
		const bool vV = v == StringView(U"C");
		const bool vv = v == U"C"sv;
		const bool vr = v == String(U"C");

		const bool rk = String(U"AB") == s;
		//const bool rc = String(U"AB") == U'C';
		const bool rs = String(U"AB") == U"C";
		const bool rV = String(U"AB") == StringView(U"C");
		const bool rv = String(U"AB") == U"C"sv;
		const bool rr = String(U"AB") == String(U"C");

		//const String ck = U'C' == s;
		//const String cc = U'C' == U'C';
		//const String cs = U'C' == U"C";
		//const String cV = U'C' == StringView(U"C");
		//const String cv = U'C' == U"C"sv;
		//const String cr = U'C' == String(U"C");

		const bool sk = U"AB" == s;
		//const String sc = U"AB" == U'C';
		//const String ss = U"AB" == U"C";
		const bool sV = U"AB" == StringView(U"C");
		const bool sv = U"AB" == U"C"sv;
		const bool sr = U"AB" == String(U"C");
	}

	ManagedScript script(U"example/script.txt");

	while (System::Update())
	{
		script.update();
	}
}
