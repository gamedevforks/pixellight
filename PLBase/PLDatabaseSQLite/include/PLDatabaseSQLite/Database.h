/*********************************************************\
 *  File: Database.h                                     *
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


#ifndef __PLDATABASESQLITE_DATABASE_H__
#define __PLDATABASESQLITE_DATABASE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLDatabase/Database.h>
#include "PLDatabaseSQLite/PLDatabaseSQLite.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
typedef struct sqlite3 sqlite3;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLDatabaseSQLite {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    SQLite 3.3.7 (http://www.sqlite.org/) database implementation
*
*  @note
*    - The following parameters of the Connect()-function are used: sDatabase
*/
class Database : public PLDatabase::Database {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLDATABASESQLITE_RTTI_EXPORT, Database, "PLDatabaseSQLite", PLDatabase::Database, "SQLite 3.3.7 (http://www.sqlite.org/) database implementation")
		pl_constructor_0(DefaultConstructor, "Default constructor", "")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLDATABASESQLITE_API Database();

		/**
		*  @brief
		*    Destructor
		*/
		PLDATABASESQLITE_API virtual ~Database();

		/**
		*  @brief
		*    Returns the SQLite socket object
		*
		*  @return
		*    The SQLite socket object, can be NULL
		*/
		PLDATABASESQLITE_API sqlite3 *GetSQLite() const;


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
		Database(const Database &cSource);

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
		Database &operator =(const Database &cSource);


	//[-------------------------------------------------------]
	//[ Public virtual PLDatabase::Database functions         ]
	//[-------------------------------------------------------]
	public:
		PLDATABASESQLITE_API virtual PLGeneral::String GetVersion() const;
		PLDATABASESQLITE_API virtual bool Connect(const PLGeneral::String &sServer, const PLGeneral::String &sUserName,
												  const PLGeneral::String &sUserPassword, const PLGeneral::String &sDatabase);
		PLDATABASESQLITE_API virtual bool IsConnected() const;
		PLDATABASESQLITE_API virtual bool IsConnectionActive() const;
		PLDATABASESQLITE_API virtual bool Disconnect();
		PLDATABASESQLITE_API virtual PLDatabase::DatabaseQuery *CreateQuery() const;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		sqlite3 *m_pSQLite;	/**< SQLite socket object, can be NULL */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLDatabaseSQLite


#endif // __PLDATABASESQLITE_DATABASE_H__
