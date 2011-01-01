/*********************************************************\
 *  File: SimpleList.h                                   *
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


#ifndef __PLGENERAL_CONTAINER_SIMPLELIST_H__
#define __PLGENERAL_CONTAINER_SIMPLELIST_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Container.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLGeneral {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
template <class ValueType> class SimpleListIterator;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linked simple list class
*
*  @remarks
*    Purpose of this class is a 'as memory compact as possible'-list, so we also needed to
*    get rid of the virtual-table. As result you can't cast this list type down to "Container"
*    or "Iterable", but get a most memory compact list. We recommend to use this list only
*    in memory-critical implementations were each byte counts.
*    Within the single linked list each node knows it's next element. If you
*    want to recive element x, internally the process begins with the first element and
*    goes to the next until element x was found. As you see the following example isn't
*    that performant:\n
*  @verbatim
*    for (uint32 i=0; i<lstSimpleList.GetNumOfElements(); i++) {
*      ListElement &cElement = lstSimpleList[i];
*    }
*  @endverbatim
*    Instead use the provided iterator whenever possible:\
*  @verbatim
*    SimpleListIterator<ListElement*> cIterator = m_lstSimpleList.GetIterator();
*    while (cIterator.HasNext()) {
*        ListElement *pElement = cIterator.Next();
*    }
*  @endverbatim
*
*  @note
*    - IsEmpty(), GetNumOfElements(), GetSize() linear, not constant
*    - Iterator from end to start is quite slow
*    - For maximum performance options the access to the internal data is public, we strongly recommend
*      to use this ONLY when really required and only to read, not to manipulate!
*
*  @see
*    - 'Iterable' for the documentation of the 'Public Iterable functions'
*    - 'Container' for the documentation of the 'Public Container functions'
*/
template <class ValueType>
class SimpleList {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class SimpleListIterator<ValueType>;


	//[-------------------------------------------------------]
	//[ Public static variables                               ]
	//[-------------------------------------------------------]
	public:
		static ValueType Null;	/**< 'Null'-object, do NEVER EVER manipulate this object! */


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Internal linked simple list element
		*/
		struct ListElement {
			ListElement *pNextElement;	/**< Pointer to the next element in the list, can be NULL */
			ValueType	 Data;			/**< The stored data */
		};


	//[-------------------------------------------------------]
	//[ Public data                                           ]
	//[-------------------------------------------------------]
	public:
		ListElement *pFirstElement;	/**< Pointer to first list element, can be NULL */


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		SimpleList();

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] lstSource
		*    Simple list to copy from
		*  @param[in] nStart
		*    Index the copy operation should start
		*  @param[in] nCount
		*    Number of elements to copy, if 0 copy all elements of lstSource behind nStart
		*/
		SimpleList(const SimpleList<ValueType> &lstSource, uint32 nStart = 0, uint32 nCount = 0);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] lstSource
		*    Container to copy from
		*  @param[in] nStart
		*    Index the copy operation should start
		*  @param[in] nCount
		*    Number of elements to copy, if 0 copy all elements of lstSource behind nStart
		*/
		SimpleList(const Container<ValueType> &lstSource, uint32 nStart = 0, uint32 nCount = 0);

		/**
		*  @brief
		*    Destructor
		*/
		~SimpleList();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] lstSource
		*    Simple list to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		SimpleList<ValueType> &operator =(const SimpleList<ValueType> &lstSource);


	//[-------------------------------------------------------]
	//[ Public Iterable functions                             ]
	//[-------------------------------------------------------]
	public:
		Iterator<ValueType> GetIterator(uint32 nIndex = 0) const;
		ConstIterator<ValueType> GetConstIterator(uint32 nIndex = 0) const;
		Iterator<ValueType> GetEndIterator() const;
		ConstIterator<ValueType> GetConstEndIterator() const;


	//[-------------------------------------------------------]
	//[ Public Container functions                            ]
	//[-------------------------------------------------------]
	public:
		bool IsEmpty() const;
		uint32 GetNumOfElements() const;
		uint32 GetElementSize() const;
		uint32 GetSize() const;
		void Clear();
		bool IsElement(const ValueType &Element) const;
		int GetIndex(const ValueType &Element) const;
		ValueType &Get(uint32 nIndex) const;
		ValueType &operator [](uint32 nIndex) const;
		bool Replace(const ValueType &Element1, const ValueType &Element2);
		bool ReplaceAtIndex(uint32 nIndex, const ValueType &Element);
		ValueType &Add();
		ValueType &Add(const ValueType &Element);
		uint32 Add(const ValueType *pElements, uint32 nCount);
		SimpleList<ValueType> &operator +=(const ValueType &Element);
		bool Add(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		SimpleList<ValueType> &operator +=(const Container<ValueType> &lstContainer);
		ValueType &AddAtIndex(int nIndex);
		bool AddAtIndex(const ValueType &Element, int nIndex);
		bool Remove(const ValueType &Element);
		bool RemoveAtIndex(uint32 nElement);
		SimpleList<ValueType> &operator -=(const ValueType &Element);
		bool Remove(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		SimpleList<ValueType> &operator -=(const Container<ValueType> &lstContainer);
		bool Copy(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		SimpleList<ValueType> &operator =(const Container<ValueType> &lstContainer);
		bool Compare(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0) const;
		bool operator ==(const Container<ValueType> &lstContainer) const;
		bool operator !=(const Container<ValueType> &lstContainer) const;


};


//[-------------------------------------------------------]
//[ Public static variables                               ]
//[-------------------------------------------------------]
template <class ValueType> ValueType SimpleList<ValueType>::Null;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/SimpleList.inl"


#endif // __PLGENERAL_CONTAINER_SIMPLELIST_H__
