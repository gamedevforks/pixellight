/*********************************************************\
 *  File: Array.h                                        *
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


#ifndef __PLGENERAL_CONTAINER_ARRAY_H__
#define __PLGENERAL_CONTAINER_ARRAY_H__
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
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Array class
*
*  @remarks
*    Within the array, all elements will be arranged sequentially in memory. The array is
*    resized automatically if required, in this case a new array is created internally,
*    old data is copied and the old array is destroyed. Therefore, avoid array resizing
*    if you have a lot of big elements. Using 'GetData()' you can receive a pointer to the
*    first element, now you can iterate through the array using 'GetData()+1' etc. for more
*    performance.
*
*  @note
*    - Do NOT backup pointer to array elements, if the array is resized they will become
*      invalid
*/
template <class ValueType>
class PLGENERAL_TMPL Array : public Container<ValueType> {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] nMaxNumOfElements
		*    Maximum number of elements within the array
		*  @param[in] bAdded
		*    Are all elements added? (GetNumOfElements() = GetMaxNumOfElements())
		*  @param[in] bInit
		*    Initialize new elements by setting them to null?
		*
		*  @see
		*    - Resize()
		*/
		Array(uint32 nMaxNumOfElements = 0, bool bAdded = true, bool bInit = false);

		/**
		*  @brief
		*    Copy constructor
		*
		*  @param[in] lstSource
		*    Array to copy from
		*  @param[in] nStart
		*    Index the copy operation should start
		*  @param[in] nCount
		*    Number of elements to copy, if 0 copy all elements of lstSource behind nStart
		*/
		Array(const Array<ValueType> &lstSource, uint32 nStart = 0, uint32 nCount = 0);

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
		Array(const Container<ValueType> &lstSource, uint32 nStart = 0, uint32 nCount = 0);

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~Array();

		/**
		*  @brief
		*    Copy operator
		*
		*  @param[in] lstSource
		*    Array to copy from
		*
		*  @return
		*    Reference to this instance
		*/
		Container<ValueType> &operator =(const Array<ValueType> &lstSource);

		/**
		*  @brief
		*    Returns the maximum number of elements in the array
		*
		*  @return
		*    Maximum number of element in the array
		*/
		uint32 GetMaxNumOfElements() const;

		/**
		*  @brief
		*    Sets the maximum number of elements in the array
		*
		*  @param[in] nMaxNumOfElements
		*    New maximum number of elements (0 = clear array)
		*  @param[in] bAdded
		*    Are all elements added? (GetNumOfElements() = GetMaxNumOfElements())
		*  @param[in] bInit
		*    Initialize new elements by setting them to null?
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - In arrays with direct objects like Array<MyClass> which have some internal
		*      classes and especial virtual functions it's NOT recommended to set 'bInit' to true!
		*/
		bool Resize(uint32 nMaxNumOfElements, bool bAdded = true, bool bInit = false);

		/**
		*  @brief
		*    Returns the number of elements automatically added if the array
		*    size is to small
		*
		*  @return
		*    Number of elements automatically added if the array size is to small
		*/
		uint32 GetResizeCount() const;

		/**
		*  @brief
		*    Sets the number of elements automatically added if the array
		*    size is to small
		*
		*  @param[in] nCount
		*    Number of elements automatically added if the array size is to small
		*
		*  @return
		*    'true' if all went fine, else 'false'
		*
		*  @note
		*    - If nCount is 0, the array size isn't changed automatically
		*/
		bool SetResizeCount(uint32 nCount = 10);

		/**
		*  @brief
		*    Returns the array data
		*
		*  @return
		*    The array data, can be NULL
		*
		*  @note
		*    - Do NOT delete this data by yourself!
		*    - Do NOT mess up the memory by writing outside the given buffer...
		*/
		ValueType *GetData() const;

		/**
		*  @brief
		*    Resets the array
		*
		*  @remarks
		*    While the Clear() function destroys also the data, this function will only
		*    reset the current number of elements within the array to 0.
		*/
		void Reset();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		uint32     m_nMaxNumOfElements;	/**< Maximum number of elements */
		uint32     m_nNumOfElements;	/**< Current number of elements */
		ValueType *m_pData;				/**< Elements, can be NULL */
		uint32     m_nResizeCount;		/**< Automatic resize count */


	//[-------------------------------------------------------]
	//[ Public virtual Iterable functions                     ]
	//[-------------------------------------------------------]
	public:
		virtual Iterator<ValueType> GetIterator(uint32 nIndex = 0) const;
		virtual ConstIterator<ValueType> GetConstIterator(uint32 nIndex = 0) const;
		virtual Iterator<ValueType> GetEndIterator() const;
		virtual ConstIterator<ValueType> GetConstEndIterator() const;


	//[-------------------------------------------------------]
	//[ Public virtual Container functions                    ]
	//[-------------------------------------------------------]
	public:
		virtual bool IsEmpty() const;
		virtual uint32 GetNumOfElements() const;
		virtual uint32 GetElementSize() const;
		virtual uint32 GetSize() const;
		virtual void Clear();
		virtual bool IsElement(const ValueType &Element) const;
		virtual int GetIndex(const ValueType &Element) const;
		virtual ValueType &Get(uint32 nIndex) const;
		virtual ValueType &operator [](uint32 nIndex) const;
		virtual bool Replace(const ValueType &Element1, const ValueType &Element2);
		virtual bool ReplaceAtIndex(uint32 nIndex, const ValueType &Element);
		virtual ValueType &Add();
		virtual ValueType &Add(const ValueType &Element);
		virtual uint32 Add(const ValueType *pElements, uint32 nCount);
		virtual Container<ValueType> &operator +=(const ValueType &Element);
		virtual bool Add(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		virtual Container<ValueType> &operator +=(const Container<ValueType> &lstContainer);
		virtual ValueType &AddAtIndex(int nIndex);
		virtual bool AddAtIndex(const ValueType &Element, int nIndex);
		virtual bool Remove(const ValueType &Element);
		virtual bool RemoveAtIndex(uint32 nElement);
		virtual Container<ValueType> &operator -=(const ValueType &Element);
		virtual bool Remove(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		virtual Container<ValueType> &operator -=(const Container<ValueType> &lstContainer);
		virtual bool Copy(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0);
		virtual Container<ValueType> &operator =(const Container<ValueType> &lstContainer);
		virtual bool Compare(const Container<ValueType> &lstContainer, uint32 nStart = 0, uint32 nCount = 0) const;
		virtual bool operator ==(const Container<ValueType> &lstContainer) const;
		virtual bool operator !=(const Container<ValueType> &lstContainer) const;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLGeneral


//[-------------------------------------------------------]
//[ Implementation                                        ]
//[-------------------------------------------------------]
#include "PLGeneral/Container/Array.inl"


#endif // __PLGENERAL_CONTAINER_ARRAY_H__
