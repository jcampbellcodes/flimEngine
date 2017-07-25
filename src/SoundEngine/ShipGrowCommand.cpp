#include "ShipGrowCommand.h"
#include "../Frigate.h"

ShipGrowCommand::ShipGrowCommand(Frigate * f, float s) : frig(f), scale(s)
{
	this->instant_execute = true;
}

void ShipGrowCommand::execute()
{
	// has a frigate object
	//frig->Scale(scale);
}
