#include "RenderAABBCommand.h"
#include "AzulCore.h"
#include "Visualizer.h"
#include "FlimColor.h"

/*
RenderAABBCommand::RenderAABBCommand(Matrix & _mat, const Vect & col) : mat(_mat), vect()
{
col;
}
*/

RenderAABBCommand::RenderAABBCommand(Matrix & _mat, const Vect& col) : mat(_mat), vect(col)
{
}

void RenderAABBCommand::setContext(Matrix & _mat, const Vect & col)
{
	this->mat = _mat;
	this->vect.set(col);
}

void RenderAABBCommand::execute()
{
	Visualizer::RenderAABB(mat, vect);
}
