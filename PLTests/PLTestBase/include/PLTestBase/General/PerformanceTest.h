/*********************************************************\
 *  File: PerformanceTest.h                              *
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


#ifndef __PLTESTBASE_GENERAL_PERFORMANCETEST_H__
#define __PLTESTBASE_GENERAL_PERFORMANCETEST_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLTest/TestCase.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Performance class for function tests
*/
class PerformanceTest : public TestCase {


	//[-------------------------------------------------------]
	//[ Public virtual TestCase functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual const char *GetName() const;


	//[-------------------------------------------------------]
	//[ Private virtual TestCase functions                    ]
	//[-------------------------------------------------------]
	private:
		virtual void Test();


};


#endif // __PLTESTBASE_GENERAL_PERFORMANCETEST_H__
