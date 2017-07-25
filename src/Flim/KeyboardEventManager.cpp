#include "KeyboardEventManager.h"

void KeyboardEventManager::Register(Inputable * in, AZUL_KEY k, input_type in_type)
{
	// if a key manager exists for the key, add 'in' to it
	// if not, create it first

	std::map<AZUL_KEY, KeyEvent*>::iterator iter = keyManagers.find(k);
	if (iter == keyManagers.end())
	{
		// create it
		KeyEvent* newKey = new KeyEvent(k);
		// add to map
		iter = keyManagers.insert(keyManagers.end(), std::pair<AZUL_KEY, KeyEvent*>(k, newKey));
	}


	// then register the key event
	iter->second->Register(in, in_type);
}

KeyboardEventManager::~KeyboardEventManager() 
{
	// calls key state test on every registered key
	std::map<AZUL_KEY, KeyEvent*>::iterator iter = keyManagers.begin();
	while (iter != keyManagers.end())
	{
		delete (*iter).second;
		iter++;
	}
	keyManagers.clear();
	//DebugMsg::out("KeyboardEvent Cleaned\n");
};

void KeyboardEventManager::Deregister(Inputable * in, AZUL_KEY k, input_type in_type)
{
	// if a key manager exists for the key, add 'in' to it
	// if not, create it first

	std::map<AZUL_KEY, KeyEvent*>::iterator iter = keyManagers.find(k);
	if (iter != keyManagers.end())
	{
		iter->second->Deregister(in, in_type);
	}
}

void KeyboardEventManager::ProcessKeys()
{
	// calls key state test on every registered key
	std::map<AZUL_KEY, KeyEvent*>::iterator iter = keyManagers.begin();
	while (iter != keyManagers.end())
	{
		(*iter).second->ProcessKeyEvent();
		iter++;
	}
}
