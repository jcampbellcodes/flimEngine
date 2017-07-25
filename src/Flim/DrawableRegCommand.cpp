#include "DrawableRegCommand.h"

#include "Drawable.h"

DrawableRegistrationCommand::DrawableRegistrationCommand(Drawable * _draw) : draw(_draw)
{
}

void DrawableRegistrationCommand::execute()
{
	draw->SceneRegistration();
}
