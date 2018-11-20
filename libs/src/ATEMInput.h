#pragma once
#include "ofMain.h"

class ATEMInput
{
public:
	ATEMInput(long long _id, string _name) : inputId(_id), inputName(_name)
	{

	}
	long long inputId;
	string inputName;
};