// Copyright (C) 2021 twyleg
#include "gpio.h"

#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>

namespace spidevpp {

namespace {

std::string getDirectionFilePath(unsigned int pin) {
	std::ostringstream oss;
	oss << "/sys/class/gpio/gpio" << pin << "/direction";
	return oss.str();
}

std::string getValueFilePath(unsigned int pin) {
	std::ostringstream oss;
	oss << "/sys/class/gpio/gpio" << pin << "/value";
	return oss.str();
}

std::string directionToString(Gpio::Direction direction) {
	switch (direction) {
	case Gpio::Direction::INPUT:
		return "in";
	case Gpio::Direction::OUTPUT:
		return "out";
	default:
		throw std::runtime_error("Unknown direction");
	}
}

}

Gpio::Gpio(unsigned int pin, Direction direction, Value initialValue)
	: mPin(pin),
	  mDirection(direction),
	  mDirectionFilePath(getDirectionFilePath(pin)),
	  mValueFilePath(getValueFilePath(pin)),
	  mValue(initialValue)
{
	std::ofstream exportFileStream("/sys/class/gpio/export", std::ios_base::out);
	exportFileStream << mPin;
	exportFileStream.close();

	std::ofstream directionFileStream(mDirectionFilePath, std::ios_base::out);
	directionFileStream << directionToString(mDirection);
	directionFileStream.close();

	setValue(mValue);
}

void Gpio::setValue(Value value) {
	mValue = value;
	std::ofstream valueFileStream(mValueFilePath, std::ios_base::out);
	valueFileStream << static_cast<int>(value);
	valueFileStream.close();
}

Gpio::Value Gpio::getValue() {
	std::ifstream valueFileStream(mValueFilePath, std::ios_base::in);
	int value;
	valueFileStream >> value;
	mValue = value ? Value::HIGH : Value::LOW;
	return mValue;
}

}
