// Copyright (C) 2021 twyleg
#pragma once

#include <string>

namespace spidevpp {

class Gpio {

public:

	enum class Direction {
		INPUT,
		OUTPUT
	};

	enum class Value {
		LOW = 0,
		HIGH = 1
	};

	Gpio(unsigned int pin, Direction direction, Value initialValue = Value::LOW);

	void setValue(Value);
	Value getValue();

private:

	const unsigned int mPin;
	const Direction mDirection;
	const std::string mDirectionFilePath;
	const std::string mValueFilePath;

	Value mValue;

};

}
