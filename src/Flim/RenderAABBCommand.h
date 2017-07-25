#pragma once
#ifndef RenderAABBCommand_H

#define RenderAABBCommand_H

#include "AzulCore.h"
#include "Command.h"
#include "FlimColor.h"

class Matrix;
class Vect;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	RenderAABBCommand
///
/// \brief	A render b sphere command.
/// \ingroup TOOLS
/// \author	Jack Campbell
/// \date	3/5/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class RenderAABBCommand : public Command, public Align16
{
private:
	Matrix mat;
	Vect vect;

public:
	RenderAABBCommand() = delete;
	virtual ~RenderAABBCommand() {
		//DebugMsg::out("Base RenderAABBCommand Cleaned\n");
	};
	RenderAABBCommand& operator=(const RenderAABBCommand&) = default;
	RenderAABBCommand(const RenderAABBCommand&) = default;

	//RenderAABBCommand(Matrix& _mat, const Vect& col);
	RenderAABBCommand(Matrix& _mat, const Vect& col);

	void setContext(Matrix& mat, const Vect& col = flimColor::pink);
	void execute() override;
};

#endif