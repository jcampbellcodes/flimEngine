#pragma once
#ifndef SHIPGROW_H
#define SHIPGROW_H

#include "CallbackCommand.h"

class Frigate;

class ShipGrowCommand : public CallbackCommand
{
public:
	// big four
	ShipGrowCommand() = default;
	ShipGrowCommand(const ShipGrowCommand&) = default;
	ShipGrowCommand& operator=(const ShipGrowCommand&) = default;
	~ShipGrowCommand() = default;

	ShipGrowCommand(Frigate* f, float s);

	virtual ShipGrowCommand* clone() override { return this; };

	void execute() override;

private:
	Frigate* frig;
	float scale;

};

#endif