#include "RenderBoxCommand.h"
#include "Visualizer.h"

RenderBoxCommand::RenderBoxCommand(Matrix & _mat, const Vect & col)
{
	this->mat = _mat;
	this->vect.set(col);
}

void RenderBoxCommand::execute()
{
	Visualizer::RenderAABB(this->mat, this->vect);
}
