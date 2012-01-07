/*********************************************************\
 *  File: DockWidgetSceneRenderer.h                      *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLFRONTENDQT_DOCKWIDGET_SCENERENDERER_H__
#define __PLFRONTENDQT_DOCKWIDGET_SCENERENDERER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLFrontendQt/DockWidget/DockWidgetScene.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
QT_BEGIN_NAMESPACE
	class QMainWindow;
QT_END_NAMESPACE
namespace PLScene {
	class SceneRenderer;
}
namespace PLFrontendQt {
	namespace DataModels {
		namespace SceneRendererDataModel {
			class SceneRendererDataModel;
		}
	}
	class DockWidgetSceneRendererQObject;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer Qt dock widget class
*
*  @note
*    - Similar to "PLFrontend::DockWidgetObject", but specialized in scene renderer
*    - By default, the "PLEngine::EngineApplication::GetSceneRendererTool()::GetSceneRenderer()" scene renderer is
*      used, but only if "PLCore::CoreApplication::GetApplication()" is an "PLEngine::EngineApplication"-instance
*/
class DockWidgetSceneRenderer : public DockWidgetScene {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class DockWidgetSceneRendererQObject;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLFRONTENDQT_RTTI_EXPORT, DockWidgetSceneRenderer, "PLFrontendQt", PLFrontendQt::DockWidgetScene, "Scene renderer Qt dock widget class")
		// Properties
		pl_properties
			pl_property("Title", "Scene Renderer")
		pl_properties_end
		// Constructors
		pl_constructor_2(DefaultConstructor,	QMainWindow*,	DockWidgetManager*,	"Constructor with a pointer to the Qt main window as first parameter, pointer to the dock widget manager this dock widget should be registered to as second parameter",	"")
		// Slots
		pl_slot_0(OnDestroyed,	"Called when the scene renderer assigned with this dock widget was destroyed",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pQMainWindow
		*    Pointer to Qt main window, can be a null pointer (in this case you're responsible for destroying this instance)
		*  @param[in] pDockWidgetManager
		*    Optional pointer to the dock widget manager this dock widget should be registered to, can be a null pointer
		*/
		PLFRONTENDQT_API DockWidgetSceneRenderer(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLFRONTENDQT_API virtual ~DockWidgetSceneRenderer();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene renderer assigned with this dock widget was destroyed
		*/
		void OnDestroyed();

		/**
		*  @brief
		*    Selects the given scene renderer
		*
		*  @param[in] pSceneRenderer
		*    Scene renderer to select, can be a null pointer
		*/
		void SelectSceneRenderer(PLScene::SceneRenderer *pSceneRenderer);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		DataModels::SceneRendererDataModel::SceneRendererDataModel *m_pSceneRendererDataModel;			/**< Scene renderer data model, can be a null pointer */
		DockWidgetSceneRendererQObject							   *m_pDockWidgetSceneRendererQObject;	/**< QObject instance for Qt's signal/slot mechanisms, always valid */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt


#endif // __PLFRONTENDQT_DOCKWIDGET_SCENERENDERER_H__
