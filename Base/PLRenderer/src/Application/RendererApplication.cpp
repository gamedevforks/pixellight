/*********************************************************\
 *  File: RendererApplication.cpp                        *
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
#include <PLCore/Log/Log.h>
#include <PLCore/Config/Config.h>
#include "PLRenderer/RendererContext.h"
#include "PLRenderer/Renderer/Surface.h"
#include "PLRenderer/Renderer/FontManager.h"
#include "PLRenderer/Renderer/SurfacePainter.h"
#include "PLRenderer/Texture/TextureManager.h"
#include "PLRenderer/Application/RendererApplication.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRenderer {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(RendererApplication)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
RendererApplication::RendererApplication(Frontend &cFrontend, const String &sSurfacePainter) : FrontendApplication(cFrontend),
	m_sSurfacePainter(sSurfacePainter),
	m_pRendererContext(nullptr),
	m_pDisplayMode(new DisplayMode)
{
}

/**
*  @brief
*    Destructor
*/
RendererApplication::~RendererApplication()
{
	// Destroy display mode information
	delete m_pDisplayMode;
}

/**
*  @brief
*    Returns the renderer context
*/
RendererContext *RendererApplication::GetRendererContext() const
{
	return m_pRendererContext;
}

/**
*  @brief
*    Get surface painter of the main window
*/
SurfacePainter *RendererApplication::GetPainter() const
{
	// Get the surface
	const Surface *pSurface = GetSurface();
	if (pSurface) {
		// Return painter
		return pSurface->GetPainter();
	}

	// Error!
	return nullptr;
}

/**
*  @brief
*    Set surface painter of the main window
*/
void RendererApplication::SetPainter(SurfacePainter *pPainter)
{
	// Get the surface
	Surface *pSurface = GetSurface();
	if (pSurface) {
		// Set painter
		pSurface->SetPainter(pPainter);
	}
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::AbstractLifecycle functions ]
//[-------------------------------------------------------]
/**
*  @brief
*    Initialization function that is called prior to OnInit()
*/
bool RendererApplication::OnStart()
{
	// Call base implementation
	if (FrontendApplication::OnStart()) {
		// Create renderer context
		OnCreateRendererContext();
		if (!m_bRunning)
			return false;

		// Check if a renderer context has been created
		if (m_pRendererContext) {
			// Start in fullscreen mode?
			if (GetConfig().GetVar("PLRenderer::Config", "Fullscreen").GetBool()) {
				// Fullscreen mode (the current display mode is automatically read from the configuration)
				GetFrontend().SetFullscreen(true);
			} else {
				// Read the current display mode from the configuration
				ReadDisplayModeFromConfig();

				// Window mode
				SurfaceWindowHandler::Init(m_pRendererContext->GetRenderer(), GetFrontend().GetNativeWindowHandle(), *m_pDisplayMode);
			}

			// Create surface painter
			OnCreatePainter();
			if (!m_bRunning)
				return false;

			// Done
			return true;
		}
	}

	// Error
	return false;
}

/**
*  @brief
*    De-initialization function that is called after OnDeInit()
*/
void RendererApplication::OnStop()
{
	{ // Save renderer related configuration
		// Write fullscreen state back to the configuration
		GetConfig().SetVar("PLRenderer::Config", "Fullscreen", String(GetFrontend().IsFullscreen()));

		// Write down display mode information
		GetConfig().SetVar("PLRenderer::Config", "DisplayWidth",     String(m_pDisplayMode->vSize.x));
		GetConfig().SetVar("PLRenderer::Config", "DisplayHeight",    String(m_pDisplayMode->vSize.y));
		GetConfig().SetVar("PLRenderer::Config", "DisplayColorBits", String(m_pDisplayMode->nColorBits));
		GetConfig().SetVar("PLRenderer::Config", "DisplayFrequency", String(m_pDisplayMode->nFrequency));
	}

	// Destroy renderer context
	if (m_pRendererContext) {
		delete m_pRendererContext;
		m_pRendererContext = nullptr;
	}

	// Call base implementation
	FrontendApplication::OnStop();
}


//[-------------------------------------------------------]
//[ Protected virtual PLCore::AbstractFrontend functions  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the fullscreen mode was changed
*/
void RendererApplication::OnFullscreenMode()
{
	if (m_pRendererContext) {
		// Read the current display mode from the configuration
		ReadDisplayModeFromConfig();

		// Get the renderer surface
		Surface *pSurface = GetSurface();
		if (pSurface) {
			// Backup information from renderer surface
			SurfacePainter *pPainter = pSurface->GetPainter();
			pSurface->SetPainter(nullptr, false);

			// De-init previous renderer surface
			DeInit();

			// Initialize new renderer surface
			Init(m_pRendererContext->GetRenderer(), GetFrontend().GetNativeWindowHandle(), *m_pDisplayMode, GetFrontend().IsFullscreen());

			// Set previous renderer surface painter
			pSurface = GetSurface();
			if (pSurface)
				pSurface->SetPainter(pPainter, false);
		} else {
			// Initialize new renderer surface
			Init(m_pRendererContext->GetRenderer(), GetFrontend().GetNativeWindowHandle(), *m_pDisplayMode, GetFrontend().IsFullscreen());
		}
	}
}

void RendererApplication::OnDraw()
{
	// Get the surface
	Surface *pSurface = GetSurface();
	if (pSurface) {
		// Draw the surface
		pSurface->Draw();
	}
}

/**
*  @brief
*    Called to let the frontend update it's states
*/
void RendererApplication::OnUpdate()
{
	// Update renderer context
	if (m_pRendererContext)
		m_pRendererContext->Update();
}


//[-------------------------------------------------------]
//[ Protected virtual RendererApplication functions       ]
//[-------------------------------------------------------]
/**
*  @brief
*    Function that is called to create the application's renderer context
*/
void RendererApplication::OnCreateRendererContext()
{
	// Get the class name of the renderer to use
	const String sRenderer     = GetConfig().GetVar("PLRenderer::Config", "RendererAPI");
	const uint32 nRendererMode = GetConfig().GetVarInt("PLRenderer::Config", "RendererMode");

	// Get Z buffer bits (for example 24)
	const uint32 nZBufferBits = GetConfig().GetVarInt("PLRenderer::Config", "ZBufferBits");

	// Stencil buffer bits (for example 8)
	const uint32 nStencilBits = GetConfig().GetVarInt("PLRenderer::Config", "StencilBits");

	// Get the number of multisample antialiasing samples per pixel
	const uint32 nMultisampleAntialiasingSamples = GetConfig().GetVarInt("PLRenderer::Config", "MultisampleAntialiasingSamples");

	// Get the name of the default shader language to use
	const String sDefaultShaderLanguage = GetConfig().GetVar("PLRenderer::Config", "DefaultShaderLanguage");

	// Create and return renderer context instance
	m_pRendererContext = sRenderer.GetLength() ? RendererContext::CreateInstance(sRenderer, static_cast<Renderer::EMode>(nRendererMode), nZBufferBits, nStencilBits, nMultisampleAntialiasingSamples, sDefaultShaderLanguage) : nullptr;
	if (!m_pRendererContext) {
		// Error!
		PL_LOG(Error, "Can't create renderer context instance: " + sRenderer)
	} else {
		// Set the swap interval (vertical synchronisation)
		m_pRendererContext->GetRenderer().SetSwapInterval(GetConfig().GetVar("PLRenderer::Config", "SwapInterval").GetUInt32());

		// Set texture manager settings
		TextureManager &cTextureManager = m_pRendererContext->GetTextureManager();
		cTextureManager.SetTextureQuality			(GetConfig().GetVar("PLRenderer::Config", "TextureQuality").GetFloat());
		cTextureManager.SetTextureMipmapsAllowed	(GetConfig().GetVar("PLRenderer::Config", "TextureMipmaps").GetBool());
		cTextureManager.SetTextureCompressionAllowed(GetConfig().GetVar("PLRenderer::Config", "TextureCompression").GetBool());
	}
}

/**
*  @brief
*    Function that is called to create the application's surface painter
*/
void RendererApplication::OnCreatePainter()
{
	// Is there a renderer context?
	if (m_pRendererContext) {
		// Create and set the surface painter
		SetPainter(m_pRendererContext->GetRenderer().CreateSurfacePainter(m_sSurfacePainter));
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Reads the current display mode from the configuration
*/
void RendererApplication::ReadDisplayModeFromConfig()
{
	// Read the current display mode from the configuration
	m_pDisplayMode->vSize.x    = GetConfig().GetVarInt("PLRenderer::Config", "DisplayWidth");
	m_pDisplayMode->vSize.y    = GetConfig().GetVarInt("PLRenderer::Config", "DisplayHeight");
	m_pDisplayMode->nColorBits = GetConfig().GetVarInt("PLRenderer::Config", "DisplayColorBits");
	m_pDisplayMode->nFrequency = GetConfig().GetVarInt("PLRenderer::Config", "DisplayFrequency");
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRenderer
