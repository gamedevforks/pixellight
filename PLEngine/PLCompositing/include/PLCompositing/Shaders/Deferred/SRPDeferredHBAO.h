/*********************************************************\
 *  File: SRPDeferredHBAO.h                              *
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


#ifndef __PLCOMPOSITING_DEFERRED_HBAO_H__
#define __PLCOMPOSITING_DEFERRED_HBAO_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLMath/Vector2.h>
#include <PLRenderer/Renderer/ProgramGenerator.h>
#include "PLCompositing/Shaders/Deferred/SRPDeferredSSAO.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class TextureBuffer2D;
	class TextureBufferRectangle;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer pass for deferred rendering "Horizon Based Ambient Occlusion" (HBAO), a "Screen-Space Ambient Occlusion" (SSAO) technique
*
*  @note
*    - Using "Horizon-Based Ambient Occlusion" as described within NVIDIA Direct3D SDK 10 Code Samples
*      (http://developer.download.nvidia.com/SDK/10.5/direct3d/Source/ScreenSpaceAO/doc/ScreenSpaceAO.pdf)
*/
class SRPDeferredHBAO : public SRPDeferredSSAO {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer pass flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoNormals = 1<<2,	/**< Ignore the per fragment normals when calculating the ambient occlusion (less AO details for heavy normal mapped scenes) */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferredSSAO::EFlags)
			pl_enum_value(NoNormals, "Ignore the per fragment normals when calculating the ambient occlusion (less AO details for heavy normal mapped scenes)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredHBAO, "PLCompositing", PLCompositing::SRPDeferredSSAO, "Scene renderer pass for deferred rendering \"Horizon Based Ambient Occlusion\" (HBAO), a \"Screen-Space Ambient Occlusion\" (SSAO) technique")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
		pl_attribute(NumberOfSteps,			PLGeneral::uint32,		8,								ReadWrite,	DirectValue,	"The maximum number samples per direction",																																														"Min='1'")
		pl_attribute(NumberOfDirections,	PLGeneral::uint32,		8,								ReadWrite,	DirectValue,	"The number of randomly-rotated 2D directions in image space distributed around the current pixel. The higher this parameter, the lower is the noise in the ambient occlusion.",												"Min='1'")
		pl_attribute(AORadius,				float,					0.25f,							ReadWrite,	DirectValue,	"AO radius in scene metrics. The radius is the distance outside which occluders are ignored.",																																	"Min='0.0'")
		pl_attribute(AngleBias,				float,					30.0f,							ReadWrite,	DirectValue,	"For low-tessellated geometry, occlusion variations tend to appear at creases and ridges, which betray the underlying tessellation. To remove these artifacts, we use an angle bias parameter which restricts the hemisphere.",	"Min='0.0'")
		pl_attribute(Attenuation,			float,					1.0f,							ReadWrite,	DirectValue,	"This scale factor W0 is applied to the per-sample attenuation function. The occlusion contribution of a given sample is attenuated by W0 * W(r/ R) where W(x) = 1 � x2.",														"Min='0.0'")
		pl_attribute(RandomUVScale,			PLMath::Vector2,		PLMath::Vector2(20.0f, 20.f),	ReadWrite,	DirectValue,	"UV scale for the random normals texture",																																														"")
		// Overwritten SceneRendererPass variables
		pl_attribute(Flags,					pl_flag_type(EFlags),	0,								ReadWrite,	GetSet,			"Flags",																																																						"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLCOM_API PLGeneral::uint32 GetNumberOfDirections() const;
		PLCOM_API void SetNumberOfDirections(PLGeneral::uint32 nValue);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCOM_API SRPDeferredHBAO();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredHBAO();


	//[-------------------------------------------------------]
	//[ Private definitions                                   ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Fragment shader flags, flag names become to source code definitions
		*/
		enum EFragmentShaderFlags {
			FS_NORMAL = 1<<0	/**< Use per fragment normal vector */
		};

		/**
		*  @brief
		*    Direct pointers to uniforms & attributes of a generated program
		*/
		struct GeneratedProgramUserData {
			// Vertex shader attributes
			PLRenderer::ProgramAttribute *pVertexPosition;
			// Fragment shader uniforms
			PLRenderer::ProgramUniform *pNumSteps;
			PLRenderer::ProgramUniform *pNumDir;
			PLRenderer::ProgramUniform *pRadius;
			PLRenderer::ProgramUniform *pInvR;
			PLRenderer::ProgramUniform *pSqrR;
			PLRenderer::ProgramUniform *pAngleBias;
			PLRenderer::ProgramUniform *pTanAngleBias;
			PLRenderer::ProgramUniform *pContrast;
			PLRenderer::ProgramUniform *pAttenuation;
			PLRenderer::ProgramUniform *pFocalLen;
			PLRenderer::ProgramUniform *pInvFocalLen;
			PLRenderer::ProgramUniform *pResolution;
			PLRenderer::ProgramUniform *pInvResolution;
			PLRenderer::ProgramUniform *pRandomUVScale;
			PLRenderer::ProgramUniform *pRandomNormalsMap;
			PLRenderer::ProgramUniform *pNormalDepthMap;
		};


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::uint32					 m_nNumberOfDirections;		/**< The number of randomly-rotated 2D directions in image space distributed around the current pixel. The higher this parameter, the lower is the noise in the ambient occlusion. */
		PLRenderer::TextureBuffer2D			*m_pRandomNormalsTexture;	/**< Texture with random normal vectors, can be NULL */
		PLRenderer::ProgramGenerator		*m_pProgramGenerator;		/**< Program generator, can be NULL */
		PLRenderer::ProgramGenerator::Flags	 m_cProgramFlags;			/**< Program flags as class member to reduce dynamic memory allocations */


	//[-------------------------------------------------------]
	//[ Protected virtual SRPDeferredSSAO functions           ]
	//[-------------------------------------------------------]
	protected:
		virtual void DrawAO(const PLGeneral::String &sShaderLanguage, PLRenderer::VertexBuffer &cVertexBuffer, PLRenderer::TextureBufferRectangle &cNormalDepthTextureBuffer);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DEFERRED_HBAO_H__
