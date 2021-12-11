#include "app.h"

export module Value;

namespace ThrustCompiler {

	/*export enum class SimpleValue {
		PLUS
	};

	export OStream& operator<<(OStream& os, const SimpleValue simpleValue) {
		String s;

		switch (simpleValue) {
		case SimpleValue::PLUS:
			s = strVal("PLUS");
			break;
		}

		return os << s;
	}*/

	export class Value {
	public:
		Value(String field) : field(field) {}

		//using enum SimpleValue;

		String field;

		friend OStream& operator<<(OStream& os, const Value& value) {
			return os << value.field;
		}
	};
}