#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <algorithm>
#include <time.h>
#include <format>
#include <chrono>


typedef enum CHARS_ {
	CHARS_REGULAR = 0b00000001,
	CHARS_CAPS = 0b00000010,
	CHARS_NUMS = 0b00000100,
	CHARS_SPECIAL = 0b00001000,

	CHARS_ALL_ALPHA = 0b00000011,
	CHARS_ALL = 0b00001111,
}CHARS;

inline CHARS operator|(CHARS a, CHARS b) {
	//return static_cast<CHARS>(static_cast<int>(a) + static_cast<int>(b));
	return static_cast<CHARS>(static_cast<int>(a) | static_cast<int>(b));
}

namespace str_ext {
	const std::string regular = "abcdefghijklmnopqrstuvwxyz";
	const std::string caps = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const std::string nums = "0123456789";
	const std::string special = "!@#$%^&*()";

	bool Contains(std::string& str, std::string element) {
		return (str.find(element) != std::string::npos);
	}

	std::string Trim(std::string trimMode, std::string str, const std::vector<std::string> itemsToTrim) {
		for (std::string toTrim : itemsToTrim) {
			if (Contains(trimMode, "l")) {
				while (str.starts_with(toTrim)) {
					str = str.substr(toTrim.length());
				}
			}

			if (Contains(trimMode, "r")) {
				while (str.ends_with(toTrim)) {
					str = str.substr(0, str.length() - toTrim.length());
				}
			}
		}

		return str;
	}

	
	// ========================================
	// bool stuff
	bool IsDigit(std::string str);
}