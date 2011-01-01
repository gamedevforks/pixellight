/*********************************************************\
 *  File: Config.h                                       *
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


#ifndef __PLCORE_CONFIG_H__
#define __PLCORE_CONFIG_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/Base/Object.h"
#include "PLCore/Tools/Loadable.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Configuration group
*
*  @remarks
*    This is the base class ALL configuration group are derived from. Derive your configuration
*    groups from this new configuration group 'collection'. By doing it in this way, you are able
*    to save this own configuration group into seperate configuration files.
*
*  @verbatim
*   Example:
*   cConfig.Save("Config/All.cfg") will save ALL available configurations into one
*   file.
*   cConfig.Save("Config/Core.cfg", "CoreConfigGroup") will ONLY will save
*   available configurations derived from 'CoreConfigGroup' into one file.
*
*   class CoreConfigGroup : public ConfigGroup {
*     pl_class(CoreConfigGroup, "PLCore", PLCore::ConfigGroup, "PLCore configuration classes")
*     pl_class_end
*   };
*
*   class CoreGeneralConfig : public CoreConfigGroup {
*     pl_class(CoreGeneralConfig, "PLCore", PLCore::CoreConfigGroup, "PLCore general configuration classes")
*       pl_constructor_0(DefaultConstructor, "Default constructor", "")
*       pl_attribute(Blabla, bool, true, ReadWrite, DirectValue, "Blabla setting", "")
*     pl_class_end
*   };
*  @endverbatim
*/
class ConfigGroup : public Object {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Config;


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCORE_RTTI_EXPORT, ConfigGroup, "PLCore", PLCore::Object, "Configuration group")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLCORE_API ConfigGroup();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ConfigGroup();


};

/**
*  @brief
*    Configuration class
*
*  @remarks
*    Configuration class. If this configuration class is created it
*    will register all RTTI classes which are in the group "PLCore::ConfigGroup"
*    automatically to it's configuration system.\n
*
*    Usage example:\n
*  @verbatim
*    // Somewhere deep within your custom configuration class header...
*    class ConfigTest : public ConfigGroup {
*      pl_class(ConfigTest, "PLCore", PLCore::ConfigGroup, "Test config class")
*        pl_constructor_0(DefaultConstructor, "Default constructor", "")
*        pl_attribute(Detail, float, 1.0f, ReadWrite, DirectValue, "Detail description text", "")
*      pl_class_end
*    };
*    // Somewhere in your custom configuration class source code
*    pl_implement_class(ConfigTest)
*    // Set ConfigTest variable value
*    cConfig.SetVar("ConfigTest", "Detail", "2.0");
*    // Get ConfigTest variable value
*    float fDetail = cConfig.GetVar("ConfigTest", "Detail").GetFloat();
*  @endverbatim
*/
class Config : public Loadable {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API Config();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~Config();

		/**
		*  @brief
		*    Returns the value of a configuration class variable
		*
		*  @param[in] sClass
		*    Configuration class name (no empty string)
		*  @param[in] sVariable
		*    Name of the variable (no empty string)
		*
		*  @return
		*    Configuration variable value, empty string on error so
		*    this pointer is never NULL!
		*/
		PLCORE_API PLGeneral::String GetVar(const PLGeneral::String &sClass, const PLGeneral::String &sVariable);

		/**
		*  @brief
		*    Returns the value of a configuration class variable
		*
		*  @param[in] sClass
		*    Configuration class name (no empty string)
		*  @param[in] sVariable
		*    Name of the variable (no empty string)
		*
		*  @return
		*    Configuration variable value
		*
		*  @note
		*    - If the variable type is PL_VAR_FLAGS, the flags will be read out
		*    - If the variable type is PL_VAR_ENUM, the enum value will be read out
		*/
		PLCORE_API int GetVarInt(const PLGeneral::String &sClass, const PLGeneral::String &sVariable);

		/**
		*  @brief
		*    Set the value of a configuration class variable
		*
		*  @param[in] sClass
		*    Configuration class name (no empty string)
		*  @param[in] sVariable
		*    Name of the variable (no empty string)
		*  @param[in] sValue
		*    Variable value
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool SetVar(const PLGeneral::String &sClass, const PLGeneral::String &sVariable, const PLGeneral::String &sValue = "");

		/**
		*  @brief
		*    Set default configuration settings
		*
		*  @param[in] sClass
		*    Configuration class name, if empty string, set ALL settings to default values
		*  @param[in] sVariable
		*    Name of the variable, if empty string, set all variables
		*    of the given configuration class to default values
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		PLCORE_API bool SetDefault(const PLGeneral::String &sClass = "", const PLGeneral::String &sVariable = "");

		/**
		*  @brief
		*    Returns the number of configuration class instances
		*
		*  @return
		*    The number of configuration class instances
		*/
		PLCORE_API PLGeneral::uint32 GetNumOfClasses() const;

		/**
		*  @brief
		*    Returns a configuration class instance by index
		*
		*  @param[in] nIndex
		*    Index of the configuration class instance to return
		*
		*  @return
		*    The requested configuration class instance, NULL on error
		*/
		PLCORE_API ConfigGroup *GetClassByIndex(PLGeneral::uint32 nIndex) const;

		/**
		*  @brief
		*    Returns a configuration class instance
		*
		*  @param[in] sName
		*    Configuration class name
		*
		*  @return
		*    The requested configuration class instance, NULL if the class wasn't found
		*
		*  @remarks
		*    You can use\n
		*    List<Class*> lstClasses;\n
		*    System::GetInstance()->GetClassList(&lstClasses, "PLConfig");\n
		*    to get a list of all configuration plugins.
		*/
		PLCORE_API ConfigGroup *GetClass(const PLGeneral::String &sName);


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] cSource
		*    Source to copy from
		*/
		Config(const Config &cSource);

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] cSource
		*    Source to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Config &operator =(const Config &cSource);

		/**
		*  @brief
		*    Set a class to default configuration settings
		*
		*  @param[in] sClass
		*    Configuration class name (no empty string)
		*  @param[in] sVariable
		*    Name of the variable, if empty string, set all variables
		*    of the given configuration class to default values
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*/
		bool SetClassDefault(const PLGeneral::String &sClass, const PLGeneral::String &sVariable);


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLGeneral::Array<ConfigGroup*>						m_lstConfig;
		PLGeneral::HashMap<PLGeneral::String, ConfigGroup*> m_mapConfig;


	//[-------------------------------------------------------]
	//[ Public virtual Loadable functions                     ]
	//[-------------------------------------------------------]
	public:
		PLCORE_API virtual PLGeneral::String GetLoadableTypeName() const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_CONFIG_H__
