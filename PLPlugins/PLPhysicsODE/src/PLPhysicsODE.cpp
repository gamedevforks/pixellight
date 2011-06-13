/*********************************************************\
 *  File: PLPhysicsODE.cpp                               *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/ModuleMain.h>


//[-------------------------------------------------------]
//[ Plugin implementation                                 ]
//[-------------------------------------------------------]
pl_module_plugin("PLPhysicsODE")
	pl_module_vendor("Copyright (C) 2002-2011 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("ODE 0.8.1 rc1 (http://www.ode.org/) physics implementation")
	pl_module_dependencies_win32_release("ode.dll")
	pl_module_dependencies_win32_debug("ode.dll")
	pl_module_dependencies_win64_release("ode.dll")	// [TODO] 64 bit support
	pl_module_dependencies_win64_debug("ode.dll")	// [TODO] 64 bit support
pl_module_end