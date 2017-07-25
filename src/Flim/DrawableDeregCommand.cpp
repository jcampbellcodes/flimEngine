#include "DrawableDeregCommand.h"

#include "Drawable.h"

DrawableDeregistrationCommand::DrawableDeregistrationCommand(Drawable * _draw) : draw(_draw)
{
}

void DrawableDeregistrationCommand::execute()
{
	draw->SceneDeregistration();
}
