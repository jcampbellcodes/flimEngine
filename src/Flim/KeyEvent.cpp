#include "KeyEvent.h"
#include "Inputable.h"



KeyEvent::KeyEvent(AZUL_KEY k) : Key(k)
{
	keyChange = Keyboard::GetKeyState(k);
};

void KeyEvent::ProcessKeyEvent()
{
	
	if (Keyboard::GetKeyState(Key) != keyChange && Keyboard::GetKeyState(Key))
	{
		// iterate through list and call update on updatables
		std::list<Inputable*>::iterator iter = PressedObjects.begin();

		while (iter != PressedObjects.end())
		{
			// check errcode of updates?
			(*iter)->KeyPressed(this->Key);
			iter++;
		}
		keyChange = !keyChange;
	}
	else if (Keyboard::GetKeyState(Key) != keyChange && !Keyboard::GetKeyState(Key))
	{
		std::list<Inputable*>::iterator iter = ReleasedObjects.begin();

		while (iter != ReleasedObjects.end())
		{
			// check errcode of updates?
			(*iter)->KeyReleased(this->Key);
			iter++;
		}
		keyChange = !keyChange;
	}
	
}

void KeyEvent::Register(Inputable * a, input_type evnt)
{
	if (evnt == input_type::pressed)
	{
		a->SetDeletionIterator(PressedObjects.insert(PressedObjects.end(), a));
	}
	else
	{
		a->SetDeletionIterator(ReleasedObjects.insert(ReleasedObjects.end(), a));
	}
}

void KeyEvent::Deregister(Inputable * a, input_type evnt)
{
	if (evnt == input_type::pressed)
	{
		PressedObjects.erase(a->GetDeletionIterator());
	}
	else
	{
		ReleasedObjects.erase(a->GetDeletionIterator());
	}
}
