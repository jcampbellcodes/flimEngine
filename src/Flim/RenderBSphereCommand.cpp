#include "RenderBSphereCommand.h"
#include "AzulCore.h"
#include "Visualizer.h"
#include "FlimColor.h"

/*
RenderBSphereCommand::RenderBSphereCommand(Matrix & _mat, const Vect & col) : mat(_mat), vect()
{
	col;
}
*/

RenderBSphereCommand::RenderBSphereCommand(Matrix & _mat, const Vect& col) : mat(_mat), vect(col)
{
}

void RenderBSphereCommand::setContext(Matrix & _mat, const Vect & col)
{
	this->mat = _mat;
	this->vect.set(col);
}

void RenderBSphereCommand::execute()
{
	Visualizer::RenderBSphere(mat, vect);
}
