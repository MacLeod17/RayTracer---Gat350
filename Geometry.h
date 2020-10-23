#pragma once

#include "Types.h"

class Geometry
{
public:
	virtual bool Hit(const ray& r) = 0;
};