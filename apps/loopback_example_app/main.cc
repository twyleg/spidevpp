// Copyright (C) 2021 twyleg
#include <spidevpp/spi.h>

#include <iostream>

int main(int argc, char *argv[]) {

	spidevpp::Spi spi(argv[1]);
	spi.setBitsPerWord(8);
	spi.setSpeed(3900000);

	{
		char buf[4] = {0};
		spi.read(buf, 4);

		if (buf[0] == 0 &&
			buf[1] == 0 &&
			buf[2] == 0 &&
			buf[3] == 0) {
			std::cout << "read check PASSED" << std::endl;
		} else {
			std::cout << "read check FAILED" << std::endl;
		}
	}

	{
		char buf[4] = {0};
		spi.write(buf, 4);

		if (buf[0] == 0 &&
			buf[1] == 0 &&
			buf[2] == 0 &&
			buf[3] == 0) {
			std::cout << "write check PASSED" << std::endl;
		} else {
			std::cout << "write check FAILED" << std::endl;
		}
	}

	{
		char buf[4] = {1, 2, 3, 4};
		spi.writeRead(buf, 4);

		if (buf[0] == 1 &&
			buf[1] == 2 &&
			buf[2] == 3 &&
			buf[3] == 4) {
			std::cout << "readWrite check PASSED" << std::endl;
		} else {
			std::cout << "readWrite check FAILED" << std::endl;
		}
	}

	return 0;
}
