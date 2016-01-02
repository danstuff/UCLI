#pragma once

#ifndef DATA_VALUE_H
#define DATA_VALUE_H

#include "main.h"

enum DataValueType{
	TYPE_NONE,
	TYPE_INTEGER,
	TYPE_DOUBLE,
	TYPE_CHARACTER
};

struct DataValue{
	DataValueType type;
	union{
		int    asInteger;
		double asDouble;
		char   asCharacter;
	};

	DataValue operator+(DataValue value){
		DataValue finval;
		finval.type = type;
		finval.asInteger = value.asInteger + asInteger;

		return finval;
	}
	DataValue operator-(DataValue value){
		DataValue finval;
		finval.type = type;
		finval.asInteger = value.asInteger - asInteger;

		return finval;
	}
	DataValue operator*(DataValue value){
		DataValue finval;
		finval.type = type;
		finval.asInteger = value.asInteger * asInteger;

		return finval;
	}
	DataValue operator/(DataValue value){
		DataValue finval;
		finval.type = type;
		finval.asInteger = value.asInteger / asInteger;

		return finval;
	}
};

#endif