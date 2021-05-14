// Copyright (C) 2021 twyleg
#pragma once

#include <linux/spi/spidev.h>

#include <chrono>
#include <string>
#include <cstdint>
#include <cstddef>
#include <iostream>

namespace spidevpp {

using namespace std::literals::chrono_literals;

class Spi {

public:

	explicit Spi(const std::string& device);

	void setBitsPerWord(uint8_t bitsPerWord);
	uint8_t getBitsPerWord() const;

	void setSpeed(uint32_t speed);
	uint32_t getSpeed() const;

	void setMode(uint32_t mode);
	uint32_t getMode() const;

	void setDelay(std::chrono::microseconds);
	std::chrono::microseconds getDelay() const;

	void write(char* pData, size_t len);
	void read(char* pData, size_t len);
	void writeRead(char* pData, size_t len);
	char writeRead(char data);

	template <class Stream>
	friend Stream& operator<<(Stream& out, const Spi&);

private:

	const std::string mDevice;

	int mFd;
	uint8_t mBitsPerWord = 8;
	std::chrono::microseconds mDelay = 0us;
	uint32_t mMode = 0;
	uint32_t mSpeed = 500000;

};

template <class Stream>
Stream& operator<<(Stream& out, const Spi& spi)
{
	out << "SPI " << spi.mDevice << std::endl;
	out << "\tMode: " << spi.getMode() << std::endl;
	out << "\tSpeed [Hz]: " << spi.getSpeed() << std::endl;
	out << "\tWord length [bits]: " << static_cast<int>(spi.getBitsPerWord()) << std::endl;
	out << "\tDelay [us]: " << spi.getDelay().count() << std::endl;

	return out;
}

}

