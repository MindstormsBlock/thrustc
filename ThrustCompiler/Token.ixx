#include "app.h"

#include <algorithm>

export module Token;

namespace ThrustCompiler {

	export enum class Token {
		TNONE = 0,

		TVAR,

		TPRINT,

		TLPAREN,
		TRPAREN,
		TCOMMA,
		TASSIGN,

		TIDENTIFIER,

		TF64VAL
	};
	
	export OStream& operator<<(OStream& os, const Token token) {
		String s;

		switch (token) {
		case Token::TNONE:
			s = strVal("TNONE");
			break;
		case Token::TVAR:
			s = strVal("TVAR");
			break;
		case Token::TPRINT:
			s = strVal("TPRINT");
			break;
		case Token::TLPAREN:
			s = strVal("TLPAREN");
			break;
		case Token::TRPAREN:
			s = strVal("TRPAREN");
			break;
		case Token::TCOMMA:
			s = strVal("TCOMMA");
			break;
		case Token::TASSIGN:
			s = strVal("TASSIGN");
			break;
		case Token::TIDENTIFIER:
			s = strVal("TIDENTIFIER");
			break;
		case Token::TF64VAL:
			s = strVal("TF64VAL");
			break;
		default:
			s = strVal("Uknown token");
			break;
		}

		return os << s;
	}

	/*export template<typename V>
	class TokenMap {
	public:
		using Value = std::pair<Token, V>;
		using Container = std::vector<Value>;

		using Iterator = typename Container::const_iterator;
		using ConstIterator = Iterator;

		TokenMap(std::initializer_list<Value> init) : container(init) {
			std::sort(this->container.begin(), this->container.end());
		}

		TokenMap(Container container) : container(std::move(container)) {
			std::sort(this->container.begin(), this->container.end());
		}

		ConstIterator begin() const {
			return container.begin();
		}

		ConstIterator end() const {
			return container.end();
		}

		template<typename K>
		ConstIterator find(const K& key) {
			ConstIterator iterator = std::lower_bound(begin(), end(), key, [](const Value& pair, const K& key) {
				return pair.first < key;
				}
			);
			return iterator != end() && iterator->first == key ? iterator : end();
		}

		sizep length() const {
			return container.size();
		}

	private:
		Container container;
	};*/
}