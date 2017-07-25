#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

// SIMD includes
#include <xmmintrin.h>
#include <smmintrin.h> 

#include "Enum.h"
#include "Vect.h"

class Quat;

   
class Matrix final : public Align16
{
public:
	// Big 4
	Matrix();
	const Matrix &operator = (const Matrix &A);
	Matrix( const Matrix &tM );
	~Matrix();

	// Constructors
	Matrix( const Vect &tV0, const Vect &tV1, const Vect &tV2, const Vect &tV3);
	Matrix( RotType type, const float angle );
	Matrix( MatrixTransType type, const float tx, const float ty, const float tz );
	Matrix( MatrixScaleType type, const float sx, const float sy, const float sz );

	Matrix( MatrixTransType type, const Vect &vIn );
	Matrix( MatrixScaleType type, const Vect &vIn );
	Matrix( Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2);
	Matrix(const RotAxisAngleType type, const Vect &vAxis, const float angle_radians);
	Matrix(const RotOrientType type, const Vect &dof, const Vect &up);

    explicit Matrix( MatrixSpecialType type );
	Matrix ( const Quat &q );

	// Set 
	void set(const Vect &V0, const Vect &V1, const Vect &V2, const Vect &V3);
	void set( RotType type, const float angle );

	void set( Rot3AxisType type, const float angle_0, const float angle_1, const float angle_2);
	void set( MatrixTransType type, const Vect &vIn );
	void set( MatrixScaleType type, const Vect &vIn );

	void set( const RotAxisAngleType, const Vect &vAxis, const float angle_radians );
	void set( const RotOrientType , const Vect &dof, const Vect &up);
	void set( MatrixTransType type, const float tx, const float ty, const float tz );
	void set( MatrixScaleType type, const float sx, const float sy, const float sz );
	void set( MatrixSpecialType type );
	void set(MatrixRowType type, const Vect &V);
	void set( const Quat &q ); 

	// Get
	Vect get(MatrixRowType type) const;

	// Matrix functions
	const float det() const;
	Matrix &T( void );
	const Matrix getT( void )const ;
	const Matrix getInv( void ) const;
	Matrix &inv( void );

	// comparison
	bool isEqual( const Matrix &A, const float epsilon = MATH_TOLERANCE) const;
	bool isIdentity( const float epsilon = MATH_TOLERANCE) const;
	const bool isRotation( const float epsilon = 0.0f ) const;

	// bracket operators	
	float &operator[] (const enum m0_enum );
	float &operator[] (const enum m1_enum );
	float &operator[] (const enum m2_enum );
	float &operator[] (const enum m3_enum );	
	float &operator[] (const enum m4_enum );	
	float &operator[] (const enum m5_enum );	
	float &operator[] (const enum m6_enum );	
	float &operator[] (const enum m7_enum );	
	float &operator[] (const enum m8_enum );	
	float &operator[] (const enum m9_enum );	
	float &operator[] (const enum m10_enum );	
	float &operator[] (const enum m11_enum );	
    float &operator[] (const enum m12_enum );	
	float &operator[] (const enum m13_enum );	
	float &operator[] (const enum m14_enum );	
	float &operator[] (const enum m15_enum );
	const float operator[] (const enum m0_enum ) const;
	const float operator[] (const enum m1_enum ) const;	
	const float operator[] (const enum m2_enum ) const;	
	const float operator[] (const enum m3_enum ) const;	
	const float operator[] (const enum m4_enum ) const;	
	const float operator[] (const enum m5_enum ) const;	
	const float operator[] (const enum m6_enum ) const;	
	const float operator[] (const enum m7_enum ) const;	
	const float operator[] (const enum m8_enum ) const;
	const float operator[] (const enum m9_enum ) const;	
	const float operator[] (const enum m10_enum ) const;	
	const float operator[] (const enum m11_enum ) const;	
    const float operator[] (const enum m12_enum ) const;	
	const float operator[] (const enum m13_enum ) const;	
	const float operator[] (const enum m14_enum ) const;	
	const float operator[] (const enum m15_enum ) const;

	// accessor	
	float &M0();
	float &M1();
	float &M2();
	float &M3();
	float &M4();
	float &M5();
	float &M6();
	float &M7();
	float &M8();
	float &M9();
	float &M10();
	float &M11();
	float &M12();
	float &M13();
	float &M14();
	float &M15();

	const float M0() const;
	const float M1() const;
	const float M2() const;
	const float M3() const;
	const float M4() const;
	const float M5() const;
	const float M6() const;
	const float M7() const;
	const float M8() const;
	const float M9() const;
	const float M10() const;
	const float M11() const;
	const float M12() const;
	const float M13() const;
	const float M14() const;
	const float M15() const;

	// add/sub operators
	Matrix operator + (void) const 	{return Matrix(*this);	};
	Matrix operator + (const Matrix &A) const ;
	void operator += (const Matrix &A);
	Matrix operator - (void) const;
	Matrix operator - (const Matrix &A) const ;
	void operator -= (const Matrix &A);

	// Multiply
	Matrix operator * (const float s) const ;
	friend Matrix operator *(const float scale, const Matrix &A );
	void operator *= (const float scale);
	Matrix operator * (const Matrix &A) const;
	void  operator *= (const Matrix &A);

private:
	const Matrix Matrix::getAdj(void) const;
	void setRotOrient( const Vect &vect_dof, const Vect &vect_vup);
	void setRotInvOrient( const Vect &vect_dof, const Vect &vect_vup);
	void privSetRotXYZ( const float a,  const float b, const float c);

// Vect and Matrix are highly coupled
friend Vect;

// Level 4 complains nameless struct/union ...
#pragma warning( disable : 4201)

union 
	{
	struct 
		{
		Vect _v0;
		Vect _v1;
		Vect _v2;
		Vect _v3;
		};

	struct 
		{
		float _m0;
		float _m1;
		float _m2;
		float _m3;
		float _m4;
		float _m5;
		float _m6;	
		float _m7;
		float _m8;
		float _m9;
		float _m10;
		float _m11;
		float _m12;
		float _m13;
		float _m14;
		float _m15;
		};
	};
};

#endif