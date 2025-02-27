#pragma once
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>

#include "MyString.h"

class Console
{
private:
	static constexpr std::streamsize DEFAULT_MAX_SIZE = 50;

public:
	static void ReadLine(int& value)
	{
		constexpr int maxSize = 20;
		char line[maxSize];
		std::cin.getline(line, maxSize - 1);

		std::stringstream lineStream(line);
		lineStream >> value;
	}

	static void ReadLine(double& value)
	{
		constexpr int maxSize = 20;
		char line[maxSize];
		std::cin.getline(line, maxSize - 1);

		std::stringstream lineStream(line);
		lineStream >> value;
	}

	static void ReadLine(MyString& value, const std::streamsize maxSize = DEFAULT_MAX_SIZE)
	{
		const auto line = std::make_unique<char[]>(maxSize + 1);
		std::cin.getline(line.get(), maxSize + 1);

		value.Assign(line.get());
	}

	template <typename... Args>
	static void WriteLine(Args... args)
	{
		(std::cout << ... << args) << "\n";
	}

	template <typename... Args>
	static void Write(Args... args)
	{
		(std::cout << ... << args);
	}

	template <typename T>
	static void WriteAligned(T value, const std::streamsize width, const bool isLeftAligned)
	{
		std::ios_base&(*alignment)(std::ios_base& iosBase) = isLeftAligned ? std::left : std::right;

		if (width) {
			std::cout << std::setw(width) << alignment << value;
		}
		else {
			std::cout << alignment << value;
		}
	}
};

