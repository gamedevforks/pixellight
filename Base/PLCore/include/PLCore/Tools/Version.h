/*********************************************************\
 *  File: Version.h                                      *
 *
 *  Copyright (C) 2002-2013 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or
 *  substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 *  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 *  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
\*********************************************************/


#ifndef __PLCORE_VERSION_H__
#define __PLCORE_VERSION_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/String/String.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Version class
*/
class Version {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API Version();

		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] sName
		*    Project name
		*  @param[in] sCodename
		*    Code name for this release
		*  @param[in] nMajor
		*    Major version number
		*  @param[in] nMinor
		*    Minor version number
		*  @param[in] nPatch
		*    Patch number
		*  @param[in] sRelease
		*    Release name (e.g. "r1" for release #1, "rc1" for release candidate #1, "nightly-date" for a nightly build etc.)
		*/
		PLCORE_API Version(const String &sName, const String &sCodename, uint16 nMajor, uint16 nMinor, uint16 nPatch, const String &sRelease);

		/**
		*  @brief
		*    Destructor
		*/
		inline ~Version();

		/**
		*  @brief
		*    Get project name
		*
		*  @return
		*    Name of the project
		*/
		inline String GetName() const;

		/**
		*  @brief
		*    Set project name
		*
		*  @param[in] sName
		*    Name of the project
		*/
		inline void SetName(const String &sName);

		/**
		*  @brief
		*    Get codename
		*
		*  @return
		*    Codename of the release
		*/
		inline String GetCodename() const;

		/**
		*  @brief
		*    Set codename
		*
		*  @param[in] sCodename
		*    Codename of the release
		*/
		inline void SetCodename(const String &sCodename);

		/**
		*  @brief
		*    Get major version number
		*
		*  @return
		*    Major version
		*/
		inline uint16 GetMajor() const;

		/**
		*  @brief
		*    Set major version number
		*
		*  @param[in] nMajor
		*    Major version
		*/
		inline void SetMajor(uint16 nMajor);

		/**
		*  @brief
		*    Get minor version number
		*
		*  @return
		*    Minor version
		*/
		inline uint16 GetMinor() const;

		/**
		*  @brief
		*    Set minor version number
		*
		*  @param[in] nMinor
		*    Minor version
		*/
		inline void SetMinor(uint16 nMinor);

		/**
		*  @brief
		*    Get patch number
		*
		*  @return
		*    Patch number
		*/
		inline uint16 GetPatch() const;

		/**
		*  @brief
		*    Set patch number
		*
		*  @param[in] nPatch
		*    Patch number
		*/
		inline void SetPatch(uint16 nPatch);

		/**
		*  @brief
		*    Get release name
		*
		*  @return
		*    Release name
		*/
		inline String GetRelease() const;

		/**
		*  @brief
		*    Set release name
		*
		*  @param[in] sRelease
		*    Release name
		*/
		inline void SetRelease(const String &sRelease);

		/**
		*  @brief
		*    Returns a string representation of the version
		*
		*  @return
		*    String representation (for example: FooBar 1.0.1-rc5 - Bulky Bug)
		*/
		PLCORE_API String ToString() const;

		//[-------------------------------------------------------]
		//[ Comparison                                            ]
		//[-------------------------------------------------------]
		PLCORE_API bool operator ==(const Version &cVersion) const;
		PLCORE_API bool operator !=(const Version &cVersion) const;
		PLCORE_API bool operator  <(const Version &cVersion) const;
		PLCORE_API bool operator  >(const Version &cVersion) const;
		PLCORE_API bool operator <=(const Version &cVersion) const;
		PLCORE_API bool operator >=(const Version &cVersion) const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		String m_sName;		/**< Project name */
		String m_sCodename;	/**< Code name for this release */
		uint16 m_nMajor;	/**< Major version number */
		uint16 m_nMinor;	/**< Minor version number */
		uint16 m_nPatch;	/**< Patch number */
		String m_sRelease;	/**< Release name (e.g. "r1") */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLCore/Tools/Version.inl"


#endif // __PLCORE_VERSION_H__
