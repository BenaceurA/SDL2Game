#include "Inputtable.h"
#include "Input.h"

Inputtable::Inputtable()
{
	Input::registerCallBack([this]() {
		this->inputCallBack();
		});
}