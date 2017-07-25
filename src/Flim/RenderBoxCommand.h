#pragma once
#ifndef RENDERBOXCOMMAND_H
#define RENDERBOXCOMMAND_H

#include "AzulCore.h"
#include "Command.h"
class RenderBoxCommand : public Command, public Align16
{
public:
	//big four
	RenderBoxCommand(Matrix& mat, const Vect& col);

	virtual void execute() override;

private:
	Matrix mat;
	Vect vect;

};

#endif