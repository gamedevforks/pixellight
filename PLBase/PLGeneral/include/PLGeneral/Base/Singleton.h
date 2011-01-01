/*********************************************************\
 *  File: Singleton.h                                    *
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


#ifndef __PLGENERAL_SINGLETON_H__
#define __PLGENERAL_SINGLETON_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/PLGeneral.h"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_PUSH
PL_WARNING_DISABLE(4251) // "'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Singleton template
*
*  @remarks
*    If you want to export a class based on this template by creating e.g. a dynamic library, you have to explicitly
*    instantiate that template class, so that the compiler can import it instead of creating an own class base
*    on the class template. If you don't do this, a call to ::GetInstance() will result in different objects
*    being created for each module, e.g. the library will then get another Singleton-instance than an application using
*    that library. This is of course not desired.
*    To instantiate and export a class, use the export-macros which are defined in each PL-library.
*    Because it seems that according to the ISO/IEC standard 14882 par. 17.4.3 (http://www.kuzbass.ru:8086/docs/isocpp/template.html)
*    instantiation of a template (which is defined in an namespace) inside another namespace is forbidden, use the
*    export macros like this:
*      namespace PLMath {
*        class GraphManager;
*      }
*      PLMATHAPI_TEMPLATE template class PLMATH_API PLGeneral::Singleton<PLMath::GraphManager>;
*/
template <class AType> class PLGENERAL_TMPL Singleton {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Returns the class instance
		*
		*  @return
		*    Pointer to the instance, assumed to be never NULL
		*
		*  @note
		*    - Returns a pointer to the singleton instance.
		*      The instance will be created if it has not been created before.
		*    - The returned pointer can be NULL if the instance has already
		*      been destroyed, that is on deinitialization of the program.
		*      So be careful when using a singleton during deinitialization
		*      of the program, or better - don't do it :-)
		*/
		static AType *GetInstance();

		/**
		*  @brief
		*    Returns whether or not there's an instance
		*
		*  @return
		*    'true' if there's an instance, else 'false'
		*/
		static bool HasInstance();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*/
		Singleton();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Singleton();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Destruction guard, deletes a singleton on deinitialization
		*/
		class __Destruction_Guard {
			public:
				__Destruction_Guard()
				{
				}
				~__Destruction_Guard()
				{
					if (Singleton<AType>::__Instance) {
						delete (Singleton<AType>*)Singleton<AType>::__Instance;
					}
				}
				inline void init() {}
		};

		// Static data
		static __Destruction_Guard __Guard;	/**< Destroyes the object on shutdown */
		static AType *__Instance;			/**< Pointer to the singleton instance, can be NULL */
		static bool __Destroyed;			/**< Destruction flag - set only on shutdown */

		// Undefined methods to prevent usage
		Singleton(const Singleton&);
		Singleton& operator =(Singleton);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Base/Singleton.inl"


//[-------------------------------------------------------]
//[ Compiler settings                                     ]
//[-------------------------------------------------------]
PL_WARNING_POP


#endif // __PLGENERAL_SINGLETON_H__
