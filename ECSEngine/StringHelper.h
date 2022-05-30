#pragma once
#include <string>

namespace StringHelper
{
	std::string ToString(const float _value, const int _precision = 6);
	std::string GenerateImGuiHash(const int _compId, const int _elementId);
}