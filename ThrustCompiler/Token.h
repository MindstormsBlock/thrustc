#pragma once

#include "app.h"

#include <vector>

#include <utility>
#include <algorithm>

namespace ThrustCompiler {

	template<typename K, typename V>
	class TokenMap {
	public:
		using Value = std::pair<K, V>;
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
	};

	enum class Token {
		TNONE = 0,

		TVAR,

		TPRINT,
		
		TASSIGN,

		TIDENTIFIER,

		TF64VAL
	};
}