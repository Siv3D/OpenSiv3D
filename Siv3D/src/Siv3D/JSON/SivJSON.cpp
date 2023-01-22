//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <variant>
# include <Siv3D/JSON.hpp>
# include <Siv3D/TextReader.hpp>
# include <Siv3D/TextWriter.hpp>
# include <Siv3D/Unicode.hpp>
# include <ThirdParty/nlohmann/json.hpp>
# include <ThirdParty/nlohmann/json-schema.hpp>

namespace s3d
{
	namespace detail
	{
		struct JSONIteratorDetail
		{
			nlohmann::json::iterator it;

			JSONIteratorDetail() = default;

			explicit JSONIteratorDetail(nlohmann::json::iterator _it)
				: it{ _it } {}
		};

		struct JSONConstIteratorDetail
		{
			nlohmann::json::const_iterator it;

			JSONConstIteratorDetail() = default;

			explicit JSONConstIteratorDetail(nlohmann::json::const_iterator _it)
				: it{ _it } {}

			explicit JSONConstIteratorDetail(const JSONIteratorDetail& _it)
				: it{_it.it} {}

			explicit JSONConstIteratorDetail(JSONIteratorDetail&& _it)
				: it{std::move(_it).it} {}
		};

		struct JSONIterationProxyDetail
		{
			nlohmann::detail::iteration_proxy_value<nlohmann::json::iterator> it;

			explicit JSONIterationProxyDetail(nlohmann::detail::iteration_proxy_value<nlohmann::json::iterator> _it)
				: it{ _it } {}
		};

		class JSONDetail
		{
		private:

			using ValueType = nlohmann::json;

			using RefType = std::reference_wrapper<ValueType>;

			static constexpr size_t ValueIndex = 0;

			static constexpr size_t RefIndex = 1;

			std::variant<ValueType, RefType> m_json;

		public:

			struct Value {};

			struct Ref {};

			JSONDetail() = default;

			JSONDetail(Value, nlohmann::json&& _json)
				: m_json{ std::move(_json) } {}

			JSONDetail(Ref, nlohmann::json& _json)
				: m_json{ std::ref(_json) } {}

			nlohmann::json& get()
			{
				return (m_json.index() == ValueIndex) ?
					std::get<ValueType>(m_json) : std::get<RefType>(m_json).get();
			}

			const nlohmann::json& get() const
			{
				return (m_json.index() == ValueIndex) ?
					std::get<ValueType>(m_json) : std::get<RefType>(m_json).get();
			}
		};

		struct ValidationErrorHandler : nlohmann::json_schema::error_handler
		{
			void error(const nlohmann::json::json_pointer& pointer, const nlohmann::json& instance, const std::string& message) override
			{
				isOK = false;

				nlohmann::json tmp{ instance };

				details.message  = Unicode::FromUTF8(message);
				details.pointer  = JSONPointer{ std::make_shared<detail::JSONPointerDetail>(pointer) };
				details.instance = JSON(std::make_shared<detail::JSONDetail>(JSONDetail::Value{}, std::move(tmp)));
			}

			bool isOK = true;

			JSONSchema::ErrorDetails details;
		};

		struct JSONPointerDetail
		{
			nlohmann::json::json_pointer pointer;

			explicit JSONPointerDetail(const std::string& s = "")
				: pointer(s)
			{}
		};

		struct JSONSchemaDetail
		{
			nlohmann::json_schema::json_validator validator;

			JSONSchemaDetail() = default;

			JSONSchemaDetail(const JSONSchemaDetail&) = delete;

			JSONSchemaDetail(JSONSchemaDetail&&) = default;

			JSONSchemaDetail(nlohmann::json_schema::json_validator&& validator)
				: validator(std::move(validator))
			{}

			~JSONSchemaDetail() = default;

			JSONSchemaDetail& operator=(const JSONSchemaDetail&) = delete;

			JSONSchemaDetail& operator=(JSONSchemaDetail&&) = default;
		};
	}

	//////////////////////////////////////////////////
	//
	//	JSONIterator
	//
	//////////////////////////////////////////////////

	JSONIterator::JSONIterator(const JSONIterator& rhs)
		: m_parent{ rhs.m_parent }
		, m_index{ rhs.m_index }
		, m_detail{ std::make_shared<detail::JSONIteratorDetail>(*rhs.m_detail) } {}

	JSONIterator::JSONIterator(JSON* parent, JSONIterator::difference_type index, const detail::JSONIteratorDetail& d)
		: m_parent{ parent }
		, m_index{ index }
		, m_detail{ std::make_shared<detail::JSONIteratorDetail>(d.it) } {}

	JSONIterator& JSONIterator::operator =(const JSONIterator& rhs)
	{
		JSONIterator tmp{ rhs };

		this->m_parent = tmp.m_parent;
		this->m_index  = tmp.m_index;
		this->m_detail = std::move(tmp.m_detail);

		return *this;
	}

	JSONIterator& JSONIterator::operator ++()
	{
		++m_detail->it;

		++m_index;

		return *this;
	}

	JSONIterator JSONIterator::operator ++(int)
	{
		const JSONIterator tmp{ *this };

		++(*this);

		return tmp;
	}

	JSONIterator& JSONIterator::operator --()
	{
		--m_detail->it;

		--m_index;

		return *this;
	}

	JSONIterator JSONIterator::operator --(int)
	{
		const JSONIterator tmp{ *this };

		--(*this);

		return tmp;
	}

	JSONIterator JSONIterator::operator +(JSONIterator::difference_type index) const
	{
		const detail::JSONIteratorDetail tmp{ m_detail->it + index };

		return JSONIterator{ m_parent, (m_index + index), tmp };
	}

	JSONItem JSONIterator::operator *() const
	{
		return{ key(), value() };
	}

	String JSONIterator::key() const
	{
		if (m_parent != nullptr) SIV3D_LIKELY
		{
			switch (m_parent->getType())
			{
			case JSONValueType::Object:
				return Unicode::FromUTF8(m_detail->it.key());
			case JSONValueType::Array:
				return Format(m_index);
			default:
				return{};
			}
		}
		else SIV3D_UNLIKELY
		{
			throw Error{ U"This JSONIterator has not been constructed from any JSON." };
		}
	}

	JSON JSONIterator::value() const
	{
		return JSON(std::make_shared<detail::JSONDetail>(detail::JSONDetail::Ref(), *m_detail->it));
	}

	bool JSONIterator::operator ==(const JSONIterator& other) const noexcept
	{
		if ((not m_detail) || (not other.m_detail))
		{
			return (not m_detail) && (not other.m_detail);
		}

		return (m_detail->it == other.m_detail->it);
	}

	bool JSONIterator::operator !=(const JSONIterator& other) const noexcept
	{
		return (not (*this == other));
	}

	//////////////////////////////////////////////////
	//
	//	JSONConstIterator
	//
	//////////////////////////////////////////////////

	JSONConstIterator::JSONConstIterator(const JSONIterator& rhs)
		: m_parent{ rhs.m_parent }
		, m_index{ rhs.m_index }
		, m_detail{ std::make_shared<detail::JSONConstIteratorDetail>(*rhs.m_detail) } {}

	JSONConstIterator::JSONConstIterator(const JSONConstIterator& rhs)
		: m_parent{ rhs.m_parent }
		, m_index{ rhs.m_index }
		, m_detail{ std::make_shared<detail::JSONConstIteratorDetail>(*rhs.m_detail) } {}

	JSONConstIterator::JSONConstIterator(const JSON* parent, JSONConstIterator::difference_type index, const detail::JSONConstIteratorDetail& d)
		: m_parent{ parent }
		, m_index{ index }
		, m_detail{ std::make_shared<detail::JSONConstIteratorDetail>(d.it) } {}

	JSONConstIterator& JSONConstIterator::operator =(const JSONIterator& rhs)
	{
		JSONConstIterator tmp{ rhs };

		this->m_parent = tmp.m_parent;
		this->m_index  = tmp.m_index;
		this->m_detail = std::move(tmp.m_detail);

		return *this;
	}

	JSONConstIterator& JSONConstIterator::operator =(const JSONConstIterator& rhs)
	{
		JSONConstIterator tmp{ rhs };

		this->m_parent = tmp.m_parent;
		this->m_index  = tmp.m_index;
		this->m_detail = std::move(tmp.m_detail);

		return *this;
	}

	JSONConstIterator& JSONConstIterator::operator ++()
	{
		++m_detail->it;

		++m_index;

		return *this;
	}

	JSONConstIterator JSONConstIterator::operator ++(int)
	{
		const JSONConstIterator tmp{ *this };

		++(*this);

		return tmp;
	}

	JSONConstIterator& JSONConstIterator::operator --()
	{
		--m_detail->it;

		--m_index;

		return *this;
	}

	JSONConstIterator JSONConstIterator::operator --(int)
	{
		const JSONConstIterator tmp{ *this };

		--(*this);

		return tmp;
	}

	JSONConstIterator JSONConstIterator::operator +(JSONConstIterator::difference_type index) const
	{
		const detail::JSONConstIteratorDetail tmp{ m_detail->it + index };

		return JSONConstIterator{ m_parent, (m_index + index), tmp };
	}

	const JSONItem JSONConstIterator::operator *() const
	{
		return{ key(), value() };
	}

	String JSONConstIterator::key() const
	{
		if (m_parent != nullptr) SIV3D_LIKELY
		{
			switch (m_parent->getType())
			{
			case JSONValueType::Object:
				return Unicode::FromUTF8(m_detail->it.key());
			case JSONValueType::Array:
				return Format(m_index);
			default:
				return{};
			}
		}
		else SIV3D_UNLIKELY
		{
			throw Error{ U"This JSONConstIterator has not been constructed from any JSON." };
		}
	}

	const JSON JSONConstIterator::value() const
	{
		return JSON(std::make_shared<detail::JSONDetail>(detail::JSONDetail::Ref(), const_cast<nlohmann::json&>(*m_detail->it)));
	}

	bool JSONConstIterator::operator ==(const JSONConstIterator& other) const noexcept
	{
		if ((not m_detail) || (not other.m_detail))
		{
			return (not m_detail) && (not other.m_detail);
		}

		return (m_detail->it == other.m_detail->it);
	}

	bool JSONConstIterator::operator !=(const JSONConstIterator& other) const noexcept
	{
		return (not (*this == other));
	}

	//////////////////////////////////////////////////
	//
	//	JSONIterationProxy
	//
	//////////////////////////////////////////////////

	JSONIterationProxy::JSONIterationProxy(const JSONIterationProxy& rhs)
		: m_detail{ std::make_shared<detail::JSONIterationProxyDetail>(*rhs.m_detail) } {}

	JSONIterationProxy::JSONIterationProxy(const detail::JSONIterationProxyDetail& d)
		: m_detail{ std::make_shared<detail::JSONIterationProxyDetail>(d.it) } {}

	JSONIterationProxy& JSONIterationProxy::operator =(const JSONIterationProxy& rhs)
	{
		JSONIterationProxy tmp = rhs;

		m_detail = std::move(tmp.m_detail);

		return *this;
	}

	JSONIterationProxy& JSONIterationProxy::operator++()
	{
		++m_detail->it;

		return *this;
	}

	JSONIterationProxy JSONIterationProxy::operator++(int)
	{
		const detail::JSONIterationProxyDetail tmp{ m_detail->it };

		++m_detail->it;

		return JSONIterationProxy{ tmp };
	}

	JSONIterationProxy JSONIterationProxy::operator+(size_t index) const
	{
		auto it = m_detail->it;

		std::advance(it, index);

		return JSONIterationProxy{ detail::JSONIterationProxyDetail{ it } };
	}

	JSON JSONIterationProxy::operator *() const
	{
		return JSON(std::make_shared<detail::JSONDetail>(detail::JSONDetail::Ref(), m_detail->it.value()));
	}

	bool JSONIterationProxy::operator ==(const JSONIterationProxy& other) const noexcept
	{
		return (m_detail->it == other.m_detail->it);
	}

	bool JSONIterationProxy::operator !=(const JSONIterationProxy& other) const noexcept
	{
		return (not (*this == other));
	}

	//////////////////////////////////////////////////
	//
	//	JSONArrayView
	//
	//////////////////////////////////////////////////

	JSONArrayView::JSONArrayView(JSONIterationProxy begin, JSONIterationProxy end)
		: m_begin{ begin }
		, m_end{ end } {}

	JSONIterationProxy JSONArrayView::begin() const
	{
		return m_begin;
	}

	JSONIterationProxy JSONArrayView::end() const
	{
		return m_end;
	}

	JSON JSONArrayView::operator [](const size_t index) const
	{
		return *(m_begin + index);
	}

	//////////////////////////////////////////////////
	//
	//	JSON
	//
	//////////////////////////////////////////////////

	JSON::JSON()
		: JSON(nullptr) {}

	JSON::JSON(Invalid_)
		: m_detail{ std::make_shared<detail::JSONDetail>() }
		, m_isValid{ false } {}

	JSON::JSON(std::nullptr_t)
		: m_detail{ std::make_shared<detail::JSONDetail>() } {}

	JSON::JSON(std::shared_ptr<detail::JSONDetail>&& detail)
		: m_detail{ std::move(detail) } {}

	JSON::JSON(const std::initializer_list<std::pair<String, JSON>>& list)
		: m_detail{ std::make_shared<detail::JSONDetail>() }
	{
		operator =(list);
	}

	JSON::JSON(const Array<JSON>& array)
		: m_detail{ std::make_shared<detail::JSONDetail>() }
	{
		*this = array;
	}

	JSON::JSON(const StringView value)
		: m_detail{ std::make_shared<detail::JSONDetail>(detail::JSONDetail::Value(), nlohmann::json(Unicode::ToUTF8(value))) } {}

	JSON::JSON(const int64 value)
		: m_detail{ std::make_shared<detail::JSONDetail>(detail::JSONDetail::Value(), nlohmann::json(value)) } {}

	JSON::JSON(const uint64 value)
		: m_detail{ std::make_shared<detail::JSONDetail>(detail::JSONDetail::Value(), nlohmann::json(value)) } {}

	JSON::JSON(const double value)
		: m_detail{ std::make_shared<detail::JSONDetail>(detail::JSONDetail::Value(), nlohmann::json(value)) } {}

	JSON::JSON(const bool value)
		: m_detail{ std::make_shared<detail::JSONDetail>(detail::JSONDetail::Value(), nlohmann::json(value)) } {}

	JSON& JSON::operator =(std::nullptr_t)
	{
		if (not m_isValid)
		{
			return *this;
		}

		m_detail->get() = nullptr;

		return *this;
	}

	JSON& JSON::operator =(const JSON& value)
	{
		if (not m_isValid)
		{
			return *this;
		}

		m_detail->get() = value.m_detail->get();

		return *this;
	}

	JSON& JSON::operator =(const std::initializer_list<std::pair<String, JSON>>& list)
	{
		if (not m_isValid)
		{
			return *this;
		}

		for (const auto& element : list)
		{
			m_detail->get()[Unicode::ToUTF8(element.first)] = element.second.m_detail->get();
		}

		return *this;
	}

	JSON& JSON::operator =(const Array<JSON>& array)
	{
		if (not m_isValid)
		{
			return *this;
		}

		if (array)
		{
			for (const auto& element : array)
			{
				m_detail->get().push_back(element.m_detail->get());
			}
		}
		else
		{
			m_detail->get() = nlohmann::json::array();
		}

		return *this;
	}

	JSON& JSON::operator =(const StringView value)
	{
		if (not m_isValid)
		{
			return *this;
		}

		m_detail->get() = Unicode::ToUTF8(value);

		return *this;
	}

	JSON& JSON::operator =(const int64 value)
	{
		if (not m_isValid)
		{
			return *this;
		}

		m_detail->get() = value;

		return *this;
	}

	JSON& JSON::operator =(const uint64 value)
	{
		if (not m_isValid)
		{
			return *this;
		}

		m_detail->get() = value;

		return *this;
	}

	JSON& JSON::operator =(const double value)
	{
		if (not m_isValid)
		{
			return *this;
		}

		m_detail->get() = value;

		return *this;
	}

	JSON& JSON::operator =(const bool value)
	{
		if (not m_isValid)
		{
			return *this;
		}

		m_detail->get() = value;

		return *this;
	}

	bool JSON::operator ==(const JSON& other) const
	{
		if (not m_isValid)
		{
			return (not other.m_isValid);
		}

		return (m_detail->get() == other.m_detail->get());
	}

	bool JSON::operator !=(const JSON& other) const
	{
		return !(*this == other);
	}

	bool JSON::isEmpty() const
	{
		return (not m_isValid);
	}

	JSON::operator bool() const
	{
		return m_isValid;
	}

	bool JSON::isNull() const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().is_null();
	}

	bool JSON::isBool() const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().is_boolean();
	}

	bool JSON::isNumber() const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().is_number();
	}

	bool JSON::isInteger() const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().is_number_integer();
	}

	bool JSON::isUnsigned() const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().is_number_unsigned();
	}

	bool JSON::isFloat() const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().is_number_float();
	}

	bool JSON::isString() const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().is_string();
	}

	bool JSON::isArray() const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().is_array();
	}

	bool JSON::isObject() const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().is_object();
	}

	JSONValueType JSON::getType() const
	{
		if (not m_isValid)
		{
			return JSONValueType::Empty;
		}

		if (isArray())
		{
			return JSONValueType::Array;
		}
		else if (isBool())
		{
			return JSONValueType::Bool;
		}
		else if (isNull())
		{
			return JSONValueType::Null;
		}
		else if (isNumber())
		{
			return JSONValueType::Number;
		}
		else if (isObject())
		{
			return JSONValueType::Object;
		}
		else if (isString())
		{
			return JSONValueType::String;
		}

		throw Error{ U"JSON::getType(): Unknown JSONValueType" };
	}

	bool JSON::hasElement(const StringView name) const
	{
		if (not m_isValid)
		{
			return false;
		}

		return m_detail->get().contains(Unicode::ToUTF8(name));
	}

	String JSON::getString() const
	{
		if (not isString())
		{
			throw Error{ U"JSON::getString(): Value is not a String type" };
		}

		return Unicode::FromUTF8(m_detail->get().get<std::string>());
	}

	JSON JSON::operator [](const StringView name)
	{
		if (not m_isValid)
		{
			return JSON::Invalid();
		}

		const std::string key = Unicode::ToUTF8(name);

		return JSON(std::make_shared<detail::JSONDetail>(
			detail::JSONDetail::Ref(), *m_detail->get().emplace(key, nlohmann::json()).first));
	}

	const JSON JSON::operator [](const StringView name) const
	{
		if (not m_isValid)
		{
			return JSON::Invalid();
		}

		const std::string key = Unicode::ToUTF8(name);

		const auto it = m_detail->get().find(key);

		if (it != m_detail->get().end())
		{
			return JSON(std::make_shared<detail::JSONDetail>(detail::JSONDetail::Ref(), *it));
		}

		throw Error{ U"JSON::operator [](): Key `{}` not found"_fmt(name) };
	}

	JSON JSON::operator [](const size_t index)
	{
		if (not m_isValid)
		{
			return JSON::Invalid();
		}

		if (not isArray())
		{
			throw Error{ U"JSON::operator [](size_t): Value is not an Array type" };
		}

		if (index >= m_detail->get().size())
		{
			throw Error{ U"JSON::operator [](size_t): Index out of range" };
		}

		return JSON(std::make_shared<detail::JSONDetail>(detail::JSONDetail::Ref(), m_detail->get()[index]));
	}

	const JSON JSON::operator [](const size_t index) const
	{
		if (not m_isValid)
		{
			return JSON::Invalid();
		}

		if (not isArray())
		{
			throw Error{ U"JSON::operator [](size_t): Value is not an Array type" };
		}

		if (const size_t size = m_detail->get().size();
			index >= size)
		{
			throw Error{ U"JSON::operator [](size_t): Index out of range (index: {} >= size: {})"_fmt(index, size) };
		}

		return JSON(std::make_shared<detail::JSONDetail>(detail::JSONDetail::Ref(), m_detail->get()[index]));
	}

	JSON JSON::access(const StringView jsonPointer)
	{
		if (not jsonPointer.starts_with(U'/'))
		{
			throw Error{ U"JSON::access(): Invalid JSON pointer `{}`"_fmt(jsonPointer) };
		}

		if (isObject() || isArray() || isNull())
		{
			return JSON(std::make_shared<detail::JSONDetail>(detail::JSONDetail::Ref(), m_detail->get()[nlohmann::json::json_pointer(Unicode::ToUTF8(jsonPointer))]));
		}

		throw Error{ U"JSON::access(): Invalid JSON type" };
	}

	const JSON JSON::access(const StringView jsonPointer) const
	{
		if (not jsonPointer.starts_with(U'/'))
		{
			throw Error{ U"JSON::access(): Invalid JSON pointer `{}`"_fmt(jsonPointer) };
		}

		if (isObject() || isArray() || isNull())
		{
			return JSON(std::make_shared<detail::JSONDetail>(detail::JSONDetail::Ref(), m_detail->get()[nlohmann::json::json_pointer(Unicode::ToUTF8(jsonPointer))]));
		}

		throw Error{ U"JSON::access(): Invalid JSON type" };
	}

	void JSON::push_back(const JSON& value)
	{
		m_detail->get().push_back(value.m_detail->get());
	}

	void JSON::clear() const
	{
		if (not m_isValid)
		{
			return;
		}

		m_detail->get().clear();
	}

	void JSON::erase(const StringView name)
	{
		if (not m_isValid)
		{
			return;
		}

		const std::string key = Unicode::ToUTF8(name);

		m_detail->get().erase(key);
	}

	void JSON::erase(const size_t index)
	{
		if (not m_isValid)
		{
			return;
		}

		if (not isArray())
		{
			return;
		}

		m_detail->get().erase(index);
	}

	//JSON::iterator JSON::find(const StringView name)
	//{
	//	const std::string key = Unicode::ToUTF8(name);

	//	return iterator(detail::JSONIteratorDetail(m_detail->get().find(key)));
	//}

	//JSON::const_iterator JSON::find(const StringView name) const
	//{
	//	const std::string key = Unicode::ToUTF8(name);

	//	return const_iterator(detail::JSONConstIteratorDetail(m_detail->get().find(key)));
	//}

	JSON::iterator JSON::begin()
	{
		return iterator{ std::addressof(*this), 0, detail::JSONIteratorDetail(m_detail->get().begin()) };
	}

	JSON::const_iterator JSON::begin() const
	{
		return const_iterator{ std::addressof(*this), 0, detail::JSONConstIteratorDetail(m_detail->get().begin()) };
	}

	JSON::iterator JSON::end()
	{
		return iterator{ std::addressof(*this), static_cast<JSON::iterator::difference_type>(size()), detail::JSONIteratorDetail(m_detail->get().end()) };
	}

	JSON::const_iterator JSON::end() const
	{
		return const_iterator{ std::addressof(*this), static_cast<JSON::iterator::difference_type>(size()), detail::JSONConstIteratorDetail(m_detail->get().end()) };
	}

	JSONArrayView JSON::arrayView() const
	{
		if (not isArray())
		{
			throw Error{ U"JSON::arrayView(): Value is not an Array type" };
		}

		return JSONArrayView{
			JSONIterationProxy{ detail::JSONIterationProxyDetail(m_detail->get().items().begin()) },
			JSONIterationProxy{ detail::JSONIterationProxyDetail(m_detail->get().items().end()) }
		};
	}

	size_t JSON::size() const
	{
		if (not m_isValid)
		{
			return 0;
		}

		return m_detail->get().size();
	}

	String JSON::format(const char32 space, const size_t spaceCount) const
	{
		return Unicode::FromUTF8(formatUTF8(space, spaceCount));
	}

	String JSON::formatMinimum() const
	{
		return Unicode::FromUTF8(formatUTF8Minimum());
	}

	std::string JSON::formatUTF8(const char32 space, const size_t spaceCount) const
	{
		if (not m_isValid)
		{
			return{};
		}

		return m_detail->get().dump(static_cast<int>(spaceCount), static_cast<char>(space));
	}

	std::string JSON::formatUTF8Minimum() const
	{
		if (not m_isValid)
		{
			return{};
		}

		return m_detail->get().dump();
	}

	bool JSON::save(const FilePathView path) const
	{
		if (not m_isValid)
		{
			return false;
		}

		TextWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		writer.write(format());

		return true;
	}

	bool JSON::saveMinimum(const FilePathView path) const
	{
		if (not m_isValid)
		{
			return false;
		}

		TextWriter writer{ path };

		if (not writer)
		{
			return false;
		}

		writer.write(formatMinimum());

		return true;
	}

	Blob JSON::toBSON() const
	{
		std::vector<uint8> result;
		nlohmann::json::to_bson(m_detail->get(), result);
		return Blob{ result.data(), result.size() };
	}

	Blob JSON::toCBOR() const
	{
		std::vector<uint8> result;
		nlohmann::json::to_cbor(m_detail->get(), result);
		return Blob{ result.data(), result.size() };
	}

	Blob JSON::toMessagePack() const
	{
		std::vector<uint8> result;
		nlohmann::json::to_msgpack(m_detail->get(), result);
		return Blob{ result.data(), result.size() };
	}

	JSON JSON::Invalid()
	{
		return JSON(Invalid_{});
	}

	JSON JSON::Load(const FilePathView path, const AllowExceptions allowExceptions)
	{
		TextReader reader{ path };

		if (not reader)
		{
			if (allowExceptions)
			{
				throw Error{ U"JSON::load(): failed to open `{}`"_fmt(path) };
			}

			return JSON::Invalid();
		}

		return Parse(reader.readAll(), allowExceptions);
	}

	JSON JSON::Load(std::unique_ptr<IReader>&& reader, const AllowExceptions allowExceptions)
	{
		TextReader textReader{ std::move(reader) };

		if (not textReader)
		{
			if (allowExceptions)
			{
				throw Error(U"JSON::load(): failed to open from IReader");
			}

			return JSON::Invalid();
		}

		return Parse(textReader.readAll(), allowExceptions);
	}

	JSON JSON::Parse(const StringView str, const AllowExceptions allowExceptions)
	{
		JSON value{ Invalid_{} };

		try
		{
			value.m_detail = std::make_shared<detail::JSONDetail>(detail::JSONDetail::Value(), nlohmann::json::parse(Unicode::ToUTF8(str)));
			value.m_isValid = true;
		}
		catch (const std::exception& e)
		{
			if (not allowExceptions)
			{
				return JSON::Invalid();
			}

			throw Error{ U"JSON::Parse(): " + Unicode::Widen(e.what()) };
		}

		return value;
	}

	JSON JSON::FromBSON(const Blob& bson, const AllowExceptions allowExceptions)
	{
		JSON value{ Invalid_{} };

		try
		{
			value.m_detail = std::make_shared<detail::JSONDetail>(detail::JSONDetail::Value(), nlohmann::json::from_bson(bson.begin(), bson.end(), true, allowExceptions.getBool()));
			value.m_isValid = true;
		}
		catch (const std::exception& e)
		{
			if (not allowExceptions)
			{
				return JSON::Invalid();
			}

			throw Error{ U"JSON::FromBSON(): " + Unicode::Widen(e.what()) };
		}

		return value;
	}

	JSON JSON::FromCBOR(const Blob& cbor, const AllowExceptions allowExceptions)
	{
		JSON value{ Invalid_{} };

		try
		{
			value.m_detail = std::make_shared<detail::JSONDetail>(detail::JSONDetail::Value(), nlohmann::json::from_cbor(cbor.begin(), cbor.end(), true, allowExceptions.getBool()));
			value.m_isValid = true;
		}
		catch (const std::exception& e)
		{
			if (not allowExceptions)
			{
				return JSON::Invalid();
			}

			throw Error{ U"JSON::FromCBOR(): " + Unicode::Widen(e.what()) };
		}

		return value;
	}

	JSON JSON::FromMessagePack(const Blob& msgpack, const AllowExceptions allowExceptions)
	{
		JSON value{ Invalid_{} };

		try
		{
			value.m_detail = std::make_shared<detail::JSONDetail>(detail::JSONDetail::Value(), nlohmann::json::from_msgpack(msgpack.begin(), msgpack.end(), true, allowExceptions.getBool()));
			value.m_isValid = true;
		}
		catch (const std::exception& e)
		{
			if (not allowExceptions)
			{
				return JSON::Invalid();
			}

			throw Error{ U"JSON::FromMessagePack(): " + Unicode::Widen(e.what()) };
		}

		return value;
	}

	void Formatter(FormatData& formatData, const JSON& value)
	{
		Formatter(formatData, value.format());
	}

	Optional<String> JSON::getOptString() const
	{
		if (not isString())
		{
			return none;
		}

		return Unicode::FromUTF8(m_detail->get().get<std::string>());
	}

	Optional<int64> JSON::getOptInt64() const
	{
		if (not isNumber())
		{
			return none;
		}

		if (isBool())
		{
			return static_cast<int64>(m_detail->get().get<bool>());
		}

		return m_detail->get().get<int64>();
	}

	Optional<double> JSON::getOptDouble() const
	{
		if (not isNumber())
		{
			return none;
		}

		return m_detail->get().get<double>();
	}

	Optional<bool> JSON::getOptBool() const
	{
		if (not isBool())
		{
			return none;
		}

		return m_detail->get().get<bool>();
	}

	//////////////////////////////////////////////////
	//
	//	JSONPointer
	//
	//////////////////////////////////////////////////

	JSONPointer::JSONPointer(const String& jsonPointer)
		: m_detail(std::make_shared<detail::JSONPointerDetail>(Unicode::ToUTF8(jsonPointer)))
	{}

	JSONPointer::JSONPointer(const JSONPointer& other)
		: m_detail(std::make_shared<detail::JSONPointerDetail>(other.m_detail->pointer))
	{}

	JSONPointer::JSONPointer(std::shared_ptr<detail::JSONPointerDetail>&& detail)
		: m_detail(std::move(detail))
	{}

	JSONPointer& JSONPointer::operator =(const JSONPointer& other)
	{
		JSONPointer tmp{ other };

		this->m_detail = std::move(tmp).m_detail;

		return *this;
	}

	String JSONPointer::format() const
	{
		return Unicode::FromUTF8(m_detail->pointer.to_string());
	}

	bool operator ==(const JSONPointer& lhs, const JSONPointer& rhs) noexcept
	{
		return lhs.m_detail->pointer == rhs.m_detail->pointer;
	}

	JSONPointer& JSONPointer::operator /=(const JSONPointer& rhs)
	{
		this->m_detail->pointer /= rhs.m_detail->pointer;

		return *this;
	}

	JSONPointer& JSONPointer::operator /=(const String& unescapedToken)
	{
		this->m_detail->pointer /= Unicode::ToUTF8(unescapedToken);

		return *this;
	}

	JSONPointer& JSONPointer::operator /=(size_t index)
	{
		this->m_detail->pointer /= index;

		return *this;
	}

	JSONPointer JSONPointer::operator /(const JSONPointer& rhs) const
	{
		JSONPointer tmp{ *this };

		return tmp /= rhs;
	}

	JSONPointer JSONPointer::operator /(const String& unescapedToken) const
	{
		JSONPointer tmp{ *this };

		return tmp /= unescapedToken;
	}

	JSONPointer JSONPointer::operator /(size_t index) const
	{
		JSONPointer tmp{ *this };

		return tmp /= index;
	}

	JSONPointer JSONPointer::parent() const
	{
		return JSONPointer{ std::make_shared<detail::JSONPointerDetail>(m_detail->pointer.parent_pointer()) };
	}

	String JSONPointer::back() const
	{
		return Unicode::FromUTF8(m_detail->pointer.back());
	}

	void JSONPointer::pop_back()
	{
		m_detail->pointer.pop_back();
	}

	void JSONPointer::push_back(const String& unescapedToken)
	{
		// nlohmann::json::json_pointer において
		// operator /= は push_back に投げられるので問題ない
		*this /= unescapedToken;
	}

	void JSONPointer::push_back(size_t index)
	{
		*this /= index;
	}

	bool JSONPointer::isEmpty() const noexcept
	{
		return m_detail->pointer.empty();
	}

	void Formatter(FormatData& formatData, const JSONPointer& value)
	{
		formatData.string += value.format();
	}

	String JSONPointer::Escape(const String& unescapedToken)
	{
		return Unicode::FromUTF8(nlohmann::detail::escape(Unicode::ToUTF8(unescapedToken)));
	}

	String JSONPointer::Unescape(const String& escapedToken)
	{
		std::string tmp{ Unicode::ToUTF8(escapedToken) };

		nlohmann::detail::unescape(tmp);

		return Unicode::FromUTF8(tmp);
	}

	//////////////////////////////////////////////////
	//
	//	JSONSchema
	//
	//////////////////////////////////////////////////

	JSONSchema::JSONSchema()
		: m_detail{ std::make_shared<detail::JSONSchemaDetail>() }
	{}

	JSONSchema::JSONSchema(Invalid_)
		: m_detail{ std::make_shared<detail::JSONSchemaDetail>() }
		, m_isValid{ false }
	{}

	JSONSchema::JSONSchema(std::shared_ptr<detail::JSONSchemaDetail>&& detail)
		: m_detail(std::move(detail))
	{}

	bool JSONSchema::isEmpty() const noexcept
	{
		return (not m_isValid);
	}

	bool JSONSchema::validate(const JSON& json) const noexcept
	{
		nlohmann::json_schema::basic_error_handler err;

		m_detail->validator.validate(json.m_detail.get()->get(), err);

		return (not static_cast<bool>(err));
	}

	bool JSONSchema::validate(const JSON& json, ValidationStatus& status) const noexcept
	{
		detail::ValidationErrorHandler err;

		m_detail->validator.validate(json.m_detail.get()->get(), err);

		if (err.isOK)
		{
			status.reset();

			return true;
		}
		else
		{
			status = err.details;

			return false;
		}
	}

	void JSONSchema::validationAssert(const JSON& json) const
	{
		detail::ValidationErrorHandler err;

		m_detail->validator.validate(json.m_detail.get()->get(), err);

		if (not err.isOK)
		{
			throw JSONSchema::ValidationError{ 
				std::move(err.details.message), 
				std::move(err.details.pointer), 
				std::move(err.details.instance) };
		}
	}

	JSONSchema JSONSchema::Invalid()
	{
		return JSONSchema{ JSONSchema::Invalid_{} };
	}

	JSONSchema JSONSchema::Load(FilePathView path, AllowExceptions allowExceptions)
	{
		return JSONSchema::Set(JSON::Load(path, allowExceptions), allowExceptions);
	}

	JSONSchema JSONSchema::Load(std::unique_ptr<IReader>&& reader, AllowExceptions allowExceptions)
	{
		return JSONSchema::Set(JSON::Load(std::move(reader), allowExceptions), allowExceptions);
	}

	JSONSchema JSONSchema::Parse(StringView str, AllowExceptions allowExceptions)
	{
		return JSONSchema::Set(JSON::Parse(str, allowExceptions), allowExceptions);
	}

	JSONSchema JSONSchema::Set(const JSON& schema, AllowExceptions allowExceptions)
	{
		try
		{
			nlohmann::json_schema::json_validator validator;

			validator.set_root_schema(schema.m_detail.get()->get());

			return JSONSchema{ std::make_shared<detail::JSONSchemaDetail>(std::move(validator)) };
		}
		catch (const std::exception& e)
		{
			if (not allowExceptions)
			{
				return JSONSchema::Invalid();
			}

			throw Error{ U"JSONSchema::Load/Parse/Set(): " + Unicode::Widen(e.what()) };
		}
	}

	//////////////////////////////////////////////////
	//
	//	JSONSchema::ErrorDetails
	//
	//////////////////////////////////////////////////

	void Formatter(FormatData& formatData, const JSONSchema::ErrorDetails& value)
	{
		formatData.string += UR"(message : {}
pointer : {}
instance: {})"_fmt(value.message, value.pointer.format(), value.instance.format());
		;
	}

	//////////////////////////////////////////////////
	//
	//	JSONSchema::ValidationStatus
	//
	//////////////////////////////////////////////////

	JSONSchema::ValidationStatus::ValidationStatus(const ErrorDetails& details)
		: m_data(details)
	{}

	JSONSchema::ValidationStatus::ValidationStatus(ErrorDetails&& details)
		: m_data(std::move(details))
	{}

	bool JSONSchema::ValidationStatus::isOK() const noexcept
	{
		return (not m_data.has_value());
	}

	bool JSONSchema::ValidationStatus::isError() const noexcept
	{
		return m_data.has_value();
	}

	JSONSchema::ValidationStatus::operator bool() const noexcept
	{
		return isOK();
	}

	void JSONSchema::ValidationStatus::reset()
	{
		return m_data.reset();
	}

	const JSONSchema::ErrorDetails& JSONSchema::ValidationStatus::value() const noexcept
	{
		return m_data.value();
	}

	const JSONPointer& JSONSchema::ValidationStatus::pointer() const noexcept
	{
		return m_data->pointer;
	}

	const JSON& JSONSchema::ValidationStatus::instance() const noexcept
	{
		return m_data->instance;
	}

	const String& JSONSchema::ValidationStatus::message() const noexcept
	{
		return m_data->message;
	}

	void Formatter(FormatData& formatData, const JSONSchema::ValidationStatus& value)
	{
		//if (value.isOK())
		//{
		//	formatData.string += value.value().format();
		//}
		//else if (value.isError())
		//{
		//	formatData.string += Format(value.value());
		//}
	}

	//////////////////////////////////////////////////
	//
	//	JSONSchema::ValidationError
	//
	//////////////////////////////////////////////////

	JSONSchema::ValidationError::ValidationError(StringView message, const JSONPointer& pointer, const JSON& instance)
		: Error(message)
		, m_pointer(pointer)
		, m_instance(instance)
	{}

	const JSONPointer& JSONSchema::ValidationError::pointer() const noexcept
	{
		return m_pointer;
	}

	const JSON& JSONSchema::ValidationError::instance() const noexcept
	{
		return m_instance;
	}

	StringView JSONSchema::ValidationError::type() const noexcept
	{
		return StringView{ U"JSONSchema::ValidationError" };
	}

	std::ostream& operator<<(std::ostream& output, const JSONSchema::ValidationError& value)
	{
		return (output << Format(value).narrow());
	}

	std::wostream& operator<<(std::wostream& output, const JSONSchema::ValidationError& value)
	{
		return (output << Format(value).toWstr());
	}

	std::basic_ostream<char32>& operator<<(std::basic_ostream<char32>& output, const JSONSchema::ValidationError& value)
	{
		return (output << Format(value));
	}

	void Formatter(FormatData& formatData, const JSONSchema::ValidationError& value)
	{
		Formatter(formatData, static_cast<const Error&>(value));

		formatData.string += UR"(
pointer : {}
instance: {})"_fmt(value.pointer().format(), value.instance().format());
	}
}
