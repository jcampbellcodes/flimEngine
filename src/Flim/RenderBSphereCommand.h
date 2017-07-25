#pragma once
#ifndef RenderBSphereCommand_H

#define RenderBSphereCommand_H

#include "AzulCore.h"
#include "Command.h"
#include "FlimColor.h"

class Matrix;
class Vect;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	RenderBSphereCommand
///
/// \brief	A render b sphere command.
/// \ingroup TOOLS
/// \author	Jack Campbell
/// \date	3/5/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class RenderBSphereCommand : public Command, public Align16
{
private:
	Matrix mat;
	Vect vect;

public:
	RenderBSphereCommand() = delete;
	virtual ~RenderBSphereCommand() {
		//DebugMsg::out("Base RenderBSphereCommand Cleaned\n");
	};
	RenderBSphereCommand& operator=(const RenderBSphereCommand&) = default;
	RenderBSphereCommand(const RenderBSphereCommand&) = default;

	//RenderBSphereCommand(Matrix& _mat, const Vect& col);
	RenderBSphereCommand(Matrix& _mat, const Vect& col);

	void setContext(Matrix& mat, const Vect& col = flimColor::pink);
	void execute() override;
};

#endif