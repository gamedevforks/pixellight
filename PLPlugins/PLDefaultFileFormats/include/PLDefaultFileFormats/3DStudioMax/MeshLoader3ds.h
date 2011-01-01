/*********************************************************\
 *  File: MeshLoader3ds.h                                *
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


#ifndef __PLDEFAULTFILEFORMATS_3DSTUDIOMAX_MESHLOADER_3DS_H__
#define __PLDEFAULTFILEFORMATS_3DSTUDIOMAX_MESHLOADER_3DS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMesh/Loader/MeshLoader.h>


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDefaultFileFormats {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Mesh loader implementation for 3ds (3D Studio Max)
*
*  @note
*    - Internally 'The 3D Studio File Format Library' (lib3ds) is used.
*      (http://lib3ds.sourceforge.net/)
*/
class MeshLoader3ds : public PLMesh::MeshLoader {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, MeshLoader3ds, "PLDefaultFileFormats", PLMesh::MeshLoader, "Mesh loader implementation for 3ds (3D Studio Max)")
		pl_properties
			pl_property("Formats",	"3ds,3DS")
			pl_property("Load",		"1")
			pl_property("Save",		"0")
		pl_properties_end
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_method_2(Load, bool, PLMesh::Mesh&, PLGeneral::File&, "Load method. The loaded mesh is static.", "")
		pl_method_3(LoadParams, bool, PLMesh::Mesh&, PLGeneral::File&, bool, "Load method. Parameters: First 'bool' parameter determines whether or not the mesh is static.", "")
		pl_method_2(Save, bool, PLMesh::Mesh&, PLGeneral::File&, "Save method", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI methods                                   ]
	//[-------------------------------------------------------]
	public:
		bool Load(PLMesh::Mesh &cMesh, PLGeneral::File &cFile);
		bool LoadParams(PLMesh::Mesh &cMesh, PLGeneral::File &cFile, bool bStatic);
		bool Save(PLMesh::Mesh &cMesh, PLGeneral::File &cFile);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		MeshLoader3ds();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MeshLoader3ds();


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDefaultFileFormats


#endif // __PLDEFAULTFILEFORMATS_3DSTUDIOMAX_MESHLOADER_3DS_H__
