#include <sstream>
#include "StringHelper.h"

std::string StringHelper::ToString(const float _value, const int _precision)
{
	std::ostringstream out;
	out.precision(_precision);
	out << std::fixed << _value;
	return out.str();
}

std::string StringHelper::GenerateImGuiHash(const int _compId, const int _elementId)
{
	return std::string("##" + std::to_string(_compId) + "#" + std::to_string(_elementId));
}