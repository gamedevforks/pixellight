/*********************************************************\
 *  File: Bluetooth.h                                    *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


#ifndef __PLINPUT_BLUETOOTH_H__
#define __PLINPUT_BLUETOOTH_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGeneral/Base/Singleton.h>
#include <PLGeneral/Container/List.h>
#include "PLInput/PLInput.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLInput {
	class Bluetooth;
	class BTImpl;
	class BTDevice;
}


//[-------------------------------------------------------]
//[ Template instance                                     ]
//[-------------------------------------------------------]
namespace PLGeneral {
	PLINPUT_TEMPLATE template class PLINPUT_API Singleton<PLInput::Bluetooth>;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Class for accessing Bluetooth devices
*/
class Bluetooth : public PLGeneral::Singleton<Bluetooth> {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class PLGeneral::Singleton<Bluetooth>;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Detect available Bluetooth devices
		*/
		PLINPUT_API void DetectDevices();

		/**
		*  @brief
		*    Get list of available Bluetooth devices
		*
		*  @return
		*    Device list
		*/
		PLINPUT_API const PLGeneral::List<BTDevice*> &GetDevices() const;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		Bluetooth();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Bluetooth();

		/**
		*  @brief
		*    Remove all devices
		*/
		void Clear();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		BTImpl						*m_pBTImpl;		/**< Platform specific Bluetooth implementation */
		PLGeneral::List<BTDevice*>	 m_lstDevices;	/**< List of devices */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_BLUETOOTH_H__
