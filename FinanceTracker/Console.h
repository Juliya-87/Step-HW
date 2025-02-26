#pragma once
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>

#include "MyString.h"

class Console
{
public:
	static void ReadLine(char* line, const std::streamsize maxSize)
	{
		std::cin.getline(line, maxSize - 1);
	}

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

	static void ReadLine(MyString& value)
	{
		const size_t capacity = value.GetCapacity();
		const auto line = new char[capacity];
		ReadLine(line, static_cast<std::streamsize>(capacity));

		value = MyString(line);
		delete[] line;
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

