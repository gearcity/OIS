/*
The zlib/libpng License

Copyright (c) 2018 Arthur Brainville
Copyright (c) 2015 Andrew Fenn
Copyright (c) 2005-2010 Phillip Castaneda (pjcast -- www.wreckedgames.com)

This software is provided 'as-is', without any express or implied warranty. In no
event will the authors be held liable for any damages arising from the use of this
software.

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to the
following restrictions:

    1. The origin of this software must not be misrepresented; you must not claim that
        you wrote the original software. If you use this software in a product,
        an acknowledgment in the product documentation would be appreciated
        but is not required.

    2. Altered source versions must be plainly marked as such, and must not be
        misrepresented as being the original software.

    3. This notice may not be removed or altered from any source distribution.   
*/
#ifndef OIS_MacInputManager_H
#define OIS_MacInputManager_H

#include "OISInputManager.h"
#include "OISFactoryCreator.h"
#include "mac/MacPrereqs.h"
#include <Carbon/Carbon.h>

namespace OIS
{

	class MacInputManager : public InputManager, public FactoryCreator
	{
	public:
		MacInputManager();
		virtual ~MacInputManager();

		//InputManager Overrides
		/** @copydoc InputManager::_initialize */
		void _initialize(ParamList& paramList);

		//FactoryCreator Overrides
		/** @copydoc FactoryCreator::deviceList */
		DeviceList freeDeviceList();

		/** @copydoc FactoryCreator::totalDevices */
		int totalDevices(Type iType);

		/** @copydoc FactoryCreator::freeDevices */
		int freeDevices(Type iType);

		/** @copydoc FactoryCreator::vendorExist */
		bool vendorExist(Type iType, const std::string& vendor);

		/** @copydoc FactoryCreator::createObject */
		Object* createObject(InputManager* creator, Type iType, bool bufferMode, const std::string& vendor = "");

		/** @copydoc FactoryCreator::destroyObject */
		void destroyObject(Object* obj);

		//Internal Items
		//! Internal method, used for flaggin keyboard as available/unavailable for creation
		void _setKeyboardUsed(bool used) { keyboardUsed = used; }

		//! Internal method, used for flaggin mouse as available/unavailable for creation
		void _setMouseUsed(bool used) { mouseUsed = used; }

		//! methodfor getting the event target
		EventTargetRef _getEventTarget() { return mEventTargetRef; }

		//! method for getting window
		WindowRef _getWindow() { return mWindow; }

	protected:
		void _parseConfigSettings(ParamList& paramList);

		void _enumerateDevices();

		static const std::string iName;

		// Mac stuff
		EventTargetRef mEventTargetRef;
		WindowRef mWindow;

		// settings
		bool mHideMouse;
		bool mUseRepeat;
                bool mNonExclusiveMouse;

		//! Used to know if we used up keyboard
		bool keyboardUsed;

		//! Used to know if we used up mouse
		bool mouseUsed;

		//! HID Manager class handling devices other than keyboard/mouse
		MacHIDManager* mHIDManager;
	};
}
#endif
