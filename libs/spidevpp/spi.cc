// Copyright (C) 2021 twyleg
#include "spi.h"

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

namespace spidevpp {

Spi::Spi(const std::string& device)
	: mDevice(device)
{
	if ((mFd = open(mDevice.c_str(), O_RDWR)) < 0) {
		throw std::runtime_error("Unable to open device");
	}
}

void Spi::setBitsPerWord(uint8_t bitsPerWord) {
	mBitsPerWord = bitsPerWord;
	if (ioctl(mFd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord) == -1) {
		throw std::runtime_error("Error on SPI_IOC_WR_BITS_PER_WORD");
	}
}

uint8_t Spi::getBitsPerWord() const {
	uint32_t bitsPerWord;
	if (ioctl(mFd, SPI_IOC_RD_BITS_PER_WORD, &bitsPerWord) == -1) {
		throw std::runtime_error("Error on SPI_IOC_RD_BITS_PER_WORD");
	}
	return bitsPerWord;
}

void Spi::setSpeed(uint32_t speed) {
	mSpeed = speed;
	if (ioctl(mFd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) == -1) {
		throw std::runtime_error("Error on SPI_IOC_WR_MAX_SPEED_HZ");
	}
}

uint32_t Spi::getSpeed() const {
	uint32_t speed;
	if (ioctl(mFd, SPI_IOC_RD_MAX_SPEED_HZ, &speed) == -1) {
		throw std::runtime_error("Error on SPI_IOC_RD_MAX_SPEED_HZ");
	}
	return speed;
}

void Spi::setMode(uint32_t mode) {
	mMode = mode;
	if (ioctl(mFd, SPI_IOC_WR_MODE32, &mode) == -1) {
		throw std::runtime_error("Error on SPI_IOC_WR_MODE32");
	}
}

uint32_t Spi::getMode() const {
	uint32_t mode;
	if (ioctl(mFd, SPI_IOC_RD_MODE32, &mode) == -1) {
		throw std::runtime_error("Error on SPI_IOC_RD_MODE32");
	}
	return mode;
}

void Spi::setDelay(std::chrono::microseconds delay) {
	mDelay = delay;
}

std::chrono::microseconds Spi::getDelay() const {
	return mDelay;
}

void Spi::write(char* pData, size_t len) {
	struct spi_ioc_transfer spi = { 0 };

	if (pData == nullptr)
		throw std::runtime_error("pData should not be a nullptr");

	spi.tx_buf = reinterpret_cast<unsigned long>(pData);
	spi.rx_buf = reinterpret_cast<unsigned long>(nullptr);
	spi.len = len;
	spi.delay_usecs = mDelay.count();
	spi.speed_hz = mSpeed;
	spi.bits_per_word = mBitsPerWord;

	if (ioctl(mFd, SPI_IOC_MESSAGE(1), &spi) < 1) {
		throw std::runtime_error("Error on SPI_IOC_MESSAGE");
	}
}

void Spi::read(char* pData, size_t len) {
	struct spi_ioc_transfer spi = { 0 };

	if (pData == nullptr)
		throw std::runtime_error("pData should not be a nullptr");

	spi.tx_buf = reinterpret_cast<unsigned long>(nullptr);
	spi.rx_buf = reinterpret_cast<unsigned long>(pData);
	spi.len = len;
	spi.delay_usecs = mDelay.count();
	spi.speed_hz = mSpeed;
	spi.bits_per_word = mBitsPerWord;

	if (ioctl(mFd, SPI_IOC_MESSAGE(1), &spi) < 1) {
		throw std::runtime_error("Error on SPI_IOC_MESSAGE");
	}
}

void Spi::writeRead(char* pData, size_t len) {
	struct spi_ioc_transfer spi = { 0 };

	if (pData == nullptr)
		throw std::runtime_error("pData should not be a nullptr");

	spi.tx_buf = reinterpret_cast<unsigned long long>(pData);
	spi.rx_buf = reinterpret_cast<unsigned long long>(pData);
	spi.len = len;
	spi.delay_usecs = mDelay.count();
	spi.speed_hz = mSpeed;
	spi.bits_per_word = mBitsPerWord;

	if (ioctl(mFd, SPI_IOC_MESSAGE(1), &spi) < 1) {
		throw std::runtime_error("Error on SPI_IOC_MESSAGE");
	}
}

char Spi::writeRead(char data) {
	writeRead(&data, 1);
	return data;
}

}
