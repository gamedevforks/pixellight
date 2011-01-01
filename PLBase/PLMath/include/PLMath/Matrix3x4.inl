/*********************************************************\
 *  File: Matrix3x4.inl                                  *
 *      Matrix3x4 inline implementation
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
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLMath {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
//[-------------------------------------------------------]
//[ Constructor                                           ]
//[-------------------------------------------------------]
inline Matrix3x4::Matrix3x4() :
	// Set identity
	xx(1.0f), xy(0.0f), xz(0.0f), xw(0.0f),
	yx(0.0f), yy(1.0f), yz(0.0f), yw(0.0f),
	zx(0.0f), zy(0.0f), zz(1.0f), zw(0.0f)
{
}

inline Matrix3x4::Matrix3x4(const float fS[])
{
	PLGeneral::MemoryManager::Copy(this->fM, fS, sizeof(float)*12);
}

inline Matrix3x4::Matrix3x4(const Matrix3x4 &mM)
{
	PLGeneral::MemoryManager::Copy(this->fM, mM.fM, sizeof(float)*12);
}

inline Matrix3x4::Matrix3x4(float fXX, float fXY, float fXZ, float fXW,
							float fYX, float fYY, float fYZ, float fYW,
							float fZX, float fZY, float fZZ, float fZW) :
	xx(fXX), xy(fXY), xz(fXZ), xw(fXW),
	yx(fYX), yy(fYY), yz(fYZ), yw(fYW),
	zx(fZX), zy(fZY), zz(fZZ), zw(fZW)
{
}


//[-------------------------------------------------------]
//[ Destructor                                            ]
//[-------------------------------------------------------]
inline Matrix3x4::~Matrix3x4()
{
}


//[-------------------------------------------------------]
//[ Operators                                             ]
//[-------------------------------------------------------]
inline Matrix3x4 &Matrix3x4::operator =(const float fS[])
{
	PLGeneral::MemoryManager::Copy(this->fM, fS, sizeof(float)*12);
	return *this;
}

inline Matrix3x4 &Matrix3x4::operator =(const Matrix3x4 &mM)
{
	PLGeneral::MemoryManager::Copy(this->fM, mM.fM, sizeof(float)*12);
	return *this;
}

inline Matrix3x4 Matrix3x4::operator +(const Matrix3x4 &mM) const
{
	return Matrix3x4(xx+mM.xx, xy+mM.xy, xz+mM.xz, xw+mM.xw,
					 yx+mM.yx, yy+mM.yy, yz+mM.yz, yw+mM.yw,
					 zx+mM.zx, zy+mM.zy, zz+mM.zz, zw+mM.zw);
}

inline void Matrix3x4::operator +=(const Matrix3x4 &mM)
{
	xx += mM.xx; xy += mM.xy; xz += mM.xz; xw += mM.xw;
	yx += mM.yx; yy += mM.yy; yz += mM.yz; yw += mM.yw;
	zx += mM.zx; zy += mM.zy; zz += mM.zz; zw += mM.zw;
}

inline Matrix3x4 Matrix3x4::operator -() const
{
	return GetInverted();
}

inline Matrix3x4 Matrix3x4::operator -(const Matrix3x4 &mM) const
{
	return Matrix3x4(xx-mM.xx, xy-mM.xy, xz-mM.xz, xw-mM.xw,
					 yx-mM.yx, yy-mM.yy, yz-mM.yz, yw-mM.yw,
					 zx-mM.zx, zy-mM.zy, zz-mM.zz, zw-mM.zw);
}

inline void Matrix3x4::operator -=(const Matrix3x4 &mM)
{
	xx -= mM.xx; xy -= mM.xy; xz -= mM.xz; xw -= mM.xw;
	yx -= mM.yx; yy -= mM.yy; yz -= mM.yz; yw -= mM.yw;
	zx -= mM.zx; zy -= mM.zy; zz -= mM.zz; zw -= mM.zw;
}

inline Matrix3x4 Matrix3x4::operator *(float fS) const
{
	return Matrix3x4(xx*fS, xy*fS, xz*fS, xw*fS,
					 yx*fS, yy*fS, yz*fS, yw*fS,
					 zx*fS, zy*fS, zz*fS, zw*fS);
}

inline void Matrix3x4::operator *=(float fS)
{
	xx *= fS; xy *= fS; xz *= fS; xw *= fS;
	yx *= fS; yy *= fS; yz *= fS; yw *= fS;
	zx *= fS; zy *= fS; zz *= fS; zw *= fS;
}

inline Vector2 Matrix3x4::operator *(const Vector2 &vV) const
{
	float x = vV.x, y = vV.y;
	return Vector2(xx*x + xy*y + xw,
				   yx*x + yy*y + yw);
}

inline Vector3 Matrix3x4::operator *(const Vector3 &vV) const
{
	float x = vV.x, y = vV.y, z = vV.z;
	return Vector3(xx*x + xy*y + xz*z + xw,
				   yx*x + yy*y + yz*z + yw,
				   zx*x + zy*y + zz*z + zw);
}

inline Vector4 Matrix3x4::operator *(const Vector4 &vV) const
{
	float x = vV.x, y = vV.y, z = vV.z, w = vV.w;
	return Vector4(xx*x + xy*y + xz*z + xw*w,
				   yx*x + yy*y + yz*z + yw*w,
				   zx*x + zy*y + zz*z + zw*w,
				   w);
}

inline void Matrix3x4::operator *=(const Matrix3x4 &mM)
{
	*this = *this * mM;
}

inline void Matrix3x4::operator *=(const Matrix4x4 &mM)
{
	*this = *this * mM;
}

inline Matrix3x4 Matrix3x4::operator /(float fS) const
{
	return Matrix3x4(xx/fS, xy/fS, xz/fS, xw/fS,
					 yx/fS, yy/fS, yz/fS, yw/fS,
					 zx/fS, zy/fS, zz/fS, zw/fS);
}

inline void Matrix3x4::operator /=(float fS)
{
	xx /= fS; xy /= fS; xz /= fS; xw /= fS;
	yx /= fS; yy /= fS; yz /= fS; yw /= fS;
	zx /= fS; zy /= fS; zz /= fS; zw /= fS;
}

inline float Matrix3x4::operator [](int nIndex) const
{
	return fM[nIndex];
}

inline float &Matrix3x4::operator [](int nIndex)
{
	return fM[nIndex];
}

inline float Matrix3x4::operator () (PLGeneral::uint32 nRow, PLGeneral::uint32 nColumn) const
{
	return fM[nRow+4*nColumn];
}

inline float &Matrix3x4::operator () (PLGeneral::uint32 nRow, PLGeneral::uint32 nColumn)
{
	return fM[nRow+4*nColumn];
}

inline Matrix3x4::operator float *() const
{
	return (float*)this->fM;
}

inline Matrix3x4::operator const float *() const
{
	return (const float*)this->fM;
}


//[-------------------------------------------------------]
//[ Matrix operations                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns whether or not this matrix is the zero matrix using an epsilon environment
*/
inline bool Matrix3x4::IsZero() const
{
	return (Math::AreEqual(xx, 0.0f) && Math::AreEqual(xy, 0.0f) && Math::AreEqual(xz, 0.0f) && Math::AreEqual(xw, 0.0f) &&
			Math::AreEqual(yx, 0.0f) && Math::AreEqual(yy, 0.0f) && Math::AreEqual(yz, 0.0f) && Math::AreEqual(yw, 0.0f) &&
			Math::AreEqual(zx, 0.0f) && Math::AreEqual(zy, 0.0f) && Math::AreEqual(zz, 0.0f) && Math::AreEqual(zw, 0.0f));
}

/**
*  @brief
*    Returns whether or not this matrix is truely the zero matrix
*/
inline bool Matrix3x4::IsTrueZero() const
{
	return (PLGeneral::MemoryManager::Compare(this->fM, Zero.fM, sizeof(float)*12) == 0);
}

/**
*  @brief
*    Sets a zero matrix
*/
inline void Matrix3x4::SetZero()
{
	PLGeneral::MemoryManager::Set(this->fM, 0, sizeof(float)*12);
}

/**
*  @brief
*    Returns whether or not this matrix is the identity matrix using an epsilon environment
*/
inline bool Matrix3x4::IsIdentity() const
{
	return (Math::AreEqual(xx, 1.0f) && Math::AreEqual(xy, 0.0f) && Math::AreEqual(xz, 0.0f) && Math::AreEqual(xw, 0.0f) &&
			Math::AreEqual(yx, 0.0f) && Math::AreEqual(yy, 1.0f) && Math::AreEqual(yz, 0.0f) && Math::AreEqual(yw, 0.0f) &&
			Math::AreEqual(zx, 0.0f) && Math::AreEqual(zy, 0.0f) && Math::AreEqual(zz, 1.0f) && Math::AreEqual(zw, 0.0f));
}

/**
*  @brief
*    Returns whether or not this matrix is truely the identity matrix
*/
inline bool Matrix3x4::IsTrueIdentity() const
{
	return (PLGeneral::MemoryManager::Compare(this->fM, Identity.fM, sizeof(float)*12) == 0);
}

/**
*  @brief
*    Sets an identity matrix
*/
inline void Matrix3x4::SetIdentity()
{
	PLGeneral::MemoryManager::Copy(this->fM, Identity.fM, sizeof(float)*12);
}

/**
*  @brief
*    Returns a requested row
*/
inline Vector4 Matrix3x4::GetRow(PLGeneral::uint8 nRow) const
{
	switch (nRow) {
		case 0:  return Vector4(  xx,   xy,   xz,   xw);
		case 1:  return Vector4(  yx,   yy,   yz,   yw);
		case 2:  return Vector4(  zx,   zy,   zz,   zw);
		default: return Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	}
}

/**
*  @brief
*    Sets a row
*/
inline void Matrix3x4::SetRow(PLGeneral::uint8 nRow, const Vector4 &vRow)
{
	switch (nRow) {
		case 0: xx = vRow.x; xy = vRow.y; xz = vRow.z; xw = vRow.w; break;
		case 1: yx = vRow.x; yy = vRow.y; yz = vRow.z; yw = vRow.w; break;
		case 2: zx = vRow.x; zy = vRow.y; zz = vRow.z; zw = vRow.w; break;
	}
}

/**
*  @brief
*    Returns a requested column
*/
inline Vector3 Matrix3x4::GetColumn(PLGeneral::uint8 nColumn) const
{
	switch (nColumn) {
		case 0:  return Vector3(xx, yx, zx);
		case 1:  return Vector3(xy, yy, zy);
		case 2:  return Vector3(xz, yz, zz);
		case 3:  return Vector3(xw, yw, zw);
		default: return Vector3::Zero; // Error!
	}
}

/**
*  @brief
*    Sets a column
*/
inline void Matrix3x4::SetColumn(PLGeneral::uint8 nColumn, const Vector3 &vColumn)
{
	switch (nColumn) {
		case 0: xx = vColumn.x; yx = vColumn.y; zx = vColumn.z; break;
		case 1: xy = vColumn.x; yy = vColumn.y; zy = vColumn.z; break;
		case 2: xz = vColumn.x; yz = vColumn.y; zz = vColumn.z; break;
		case 3: xw = vColumn.x; yw = vColumn.y; zw = vColumn.z; break;
	}
}

/**
*  @brief
*    Returns true if this matrix is symmetric
*/
inline bool Matrix3x4::IsSymmetric() const
{
	return (Math::AreEqual(xy, yx) && Math::AreEqual(xz, zx) && Math::AreEqual(yz, zy));
}

/**
*  @brief
*    Returns true if this matrix is orthogonal
*/
inline bool Matrix3x4::IsOrthogonal() const
{
	return (GetTransposed() == GetInverted());
}

/**
*  @brief
*    Returns true if this matrix is a rotation matrix
*/
inline bool Matrix3x4::IsRotationMatrix() const
{
	return (GetTransposed() == GetInverted() && Math::AreEqual(GetDeterminant(), 1.0f));
}

/**
*  @brief
*    Returns true if this matrix is a rotation and translation matrix
*/
inline bool Matrix3x4::IsRotationTranslationMatrix() const
{
	return (IsRotationMatrix() && !Math::AreEqual(xw, 0.0f) && !Math::AreEqual(yw, 0.0f) && !Math::AreEqual(zw, 0.0f));
}

/**
*  @brief
*    Returns the trace of the matrix
*/
inline float Matrix3x4::GetTrace() const
{
	return xx+yy+zz;
}

/**
*  @brief
*    Returns the determinant of the matrix
*/
inline float Matrix3x4::GetDeterminant() const
{
	// 'Classic'
//	return xx*yy*zz + xy*yz*zx + xz*yx*zy - (zx*yy*xz + zy*yz*xx + zz*yx*xy);
	// Faster :)
	return xx*(yy*zz - yz*zy) - yx*(xy*zz - xz*zy) + zx*(xy*yz - xz*yy);
}

/**
*  @brief
*    Transpose this matrix
*/
inline void Matrix3x4::Transpose()
{
	// xy <-> yx
	float fT = xy;
	xy = yx;
	yx = fT;

	// xz <-> zx
	fT = xz;
	xz = zx;
	zx = fT;

	// yz <-> zy
	fT = yz;
	yz = zy;
	zy = fT;
}

/**
*  @brief
*    Returns the transposed matrix
*/
inline Matrix3x4 Matrix3x4::GetTransposed() const
{
	return Matrix3x4(xx, yx, zx, xw,
					 xy, yy, zy, yw,
					 xz, yz, zz, zw);
}


//[-------------------------------------------------------]
//[ Scale                                                 ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets a scale matrix
*/
inline void Matrix3x4::SetScaleMatrix(float fX, float fY, float fZ)
{
	xx =   fX; xy = 0.0f; xz = 0.0f; xw = 0.0f;
	yx = 0.0f; yy =   fY; yz = 0.0f; yw = 0.0f;
	zx = 0.0f; zy = 0.0f; zz =   fZ; zw = 0.0f;
}

inline void Matrix3x4::SetScaleMatrix(const Vector3 &vV)
{
	xx = vV.x; xy = 0.0f; xz = 0.0f; xw = 0.0f;
	yx = 0.0f; yy = vV.y; yz = 0.0f; yw = 0.0f;
	zx = 0.0f; zy = 0.0f; zz = vV.z; zw = 0.0f;
}

inline Vector3 Matrix3x4::GetScale() const
{
	Vector3 vScale;
	GetScale(vScale.x, vScale.y, vScale.z);
	return vScale;
}

inline void Matrix3x4::GetScale(float fV[]) const
{
	GetScale(fV[0], fV[1], fV[2]);
}


//[-------------------------------------------------------]
//[ Translation                                           ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets a translation matrix
*/
inline void Matrix3x4::SetTranslationMatrix(float fX, float fY, float fZ)
{
	xx = 1.0f; xy = 0.0f; xz = 0.0f; xw =   fX;
	yx = 0.0f; yy = 1.0f; yz = 0.0f; yw =   fY;
	zx = 0.0f; zy = 0.0f; zz = 1.0f; zw =   fZ;
}

inline void Matrix3x4::SetTranslationMatrix(const Vector3 &vV)
{
	xx = 1.0f; xy = 0.0f; xz = 0.0f; xw = vV.x;
	yx = 0.0f; yy = 1.0f; yz = 0.0f; yw = vV.y;
	zx = 0.0f; zy = 0.0f; zz = 1.0f; zw = vV.z;
}

inline void Matrix3x4::GetTranslation(float &fX, float &fY, float &fZ) const
{
	fX = xw;
	fY = yw;
	fZ = zw;
}

inline Vector3 Matrix3x4::GetTranslation() const
{
	return Vector3(xw, yw, zw);
}

inline void Matrix3x4::GetTranslation(float fV[]) const
{
	fV[0] = xw;
	fV[1] = yw;
	fV[2] = zw;
}

inline void Matrix3x4::SetTranslation(float fX, float fY, float fZ)
{
	xw = fX;
	yw = fY;
	zw = fZ;
}

inline void Matrix3x4::SetTranslation(const Vector3 &vV)
{
	SetTranslation(vV.x, vV.y, vV.z);
}

inline void Matrix3x4::SetTranslation(const float fV[])
{
	SetTranslation(fV[0], fV[1], fV[2]);
}


//[-------------------------------------------------------]
//[ Rotation                                              ]
//[-------------------------------------------------------]
/**
*  @brief
*    Returns the x (left) axis
*/
inline Vector3 Matrix3x4::GetXAxis() const
{
	return Vector3(xx, yx, zx);
}

/**
*  @brief
*    Returns the y (up) axis
*/
inline Vector3 Matrix3x4::GetYAxis() const
{
	return Vector3(xy, yy, zy);
}

/**
*  @brief
*    Returns the z (forward) axis
*/
inline Vector3 Matrix3x4::GetZAxis() const
{
	return Vector3(xz, yz, zz);
}


//[-------------------------------------------------------]
//[ Misc                                                  ]
//[-------------------------------------------------------]
/**
*  @brief
*    Sets a shearing matrix
*/
inline Matrix3x4 &Matrix3x4::SetShearing(float fShearXY, float fShearXZ, float fShearYX, float fShearYZ,
										 float fShearZX, float fShearZY)
{
	xx = 1.0f;     xy = fShearYX; xz = fShearZX; xw = 0.0f;
	yx = fShearXY; yy = 1.0f;     yz = fShearZY; yw = 0.0f;
	zx = fShearXZ; zy = fShearYZ; zz = 1.0f;     zw = 0.0f;
	return *this;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLMath
