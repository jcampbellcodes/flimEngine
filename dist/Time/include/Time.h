#ifndef ENGINE_TIME_H
#define ENGINE_TIME_H

enum Duration
{
	/* For constructing a Time of zero. */
	TIME_ZERO,

	/* For constructing one NTSC 60 hz frame of Time. */
	TIME_NTSC_FRAME,

	/* For constructing one NTSC 60 hz frame of Time. */
	TIME_NTSC_30_FRAME,

	/* For constructing one PAL 50 hz frame of Time. */
	TIME_PAL_FRAME,

	/* For constructing one millisecond of Time. */
	TIME_ONE_MILLISECOND,

	/* For constructing one nanosecond of Time. */
	TIME_ONE_NANOSECOND,

	/* For constructing one second of Time. */
	TIME_ONE_SECOND,

	/* For constructing one minute of Time. */
	TIME_ONE_MINUTE,

	/* For constructing one hour of Time. */
	TIME_ONE_HOUR,

	/*
	 * For constructing the most <i>negative</i> Time 
	 * that can be represented. 
	 */
	TIME_MIN,

	/*
	 * For constructing the most positive Time 
	 * that can be represented. 
	 */
	TIME_MAX,

	// insure the enum is size int
	TIME_DWORD = 0x7FFFFFFF
	};


//---------------------------------------------------------------------------
// CLASS DECLARATION:
//---------------------------------------------------------------------------

class Time
{

	public:

	//-----------------------------------------------------------------
	// Friends
	//-----------------------------------------------------------------

		/*
		* return: The product of the specified float and Time. 
		*
		* Example:
		*    const Time halfSecond = 0.5f * Time(ONE_SECOND);
		*/
		friend const Time operator*( const float, const Time & );
	
		/*
		* return: The product of the specified integer and Time. 
		*
		* Example:
		*    const Time fourMinutes = 4 * Time(ONE_MINUTE);
		*/
		friend const Time operator*( const int, const Time & );
	
	//-----------------------------------------------------------------
	// Constructors / Destructors / Assignment
	//-----------------------------------------------------------------

		/* Creates a Time equal to Time(ZERO). */ 
		inline Time();
	
		/*
		* Creates the specific amount of Time. 
		*
		* Example:
		*    const Time oneSecond( ONE_SECOND );
		*/
		explicit Time( const Duration );
	
		/* Creates a copy of the specified Time. */ 
		inline Time( const Time& );
	
		/*
		* Assigns the right-hand side to this Time. 
		* return: this Time.
		*
		*  Example:
		*    const Time tickDuration = Time(NTSC_DURATION);
		*/ 
		inline Time& operator=( const Time& rhs );
	
		// destrutor
		~Time()
		{ }
	
	//-----------------------------------------------------------------
	// Comparisons
	//-----------------------------------------------------------------

		/*
		* return: true if this Time is equal to the right-hand side. 
		*
		*  Example: 
		*    assert( Time(ONE_HOUR)   == 60 * Time(ONE_MINUTE) );
		*    assert( Time(ONE_MINUTE) == 60 * Time(ONE_SECOND) );
		*/
		bool operator==( const Time& rhs ) const;
	
		/* 
		* return: true if this Time is not equal to the right-hand side. 
		*/
		bool operator!=( const Time& rhs ) const;
	
		/*
		* return: true if this Time is less than the right-hand side.
		*
		* Example:
		*    bool couldBeOttosMileTime( const Time t )
		*    {
		*       return( t < 4 * Time(ONE_MINUTE) );
		*    }
		*/
		bool operator<( const Time& rhs ) const;
	
		/* 
		* return: true if this Time is less or equal to the right-hand side.
		*/
		bool operator<=( const Time& rhs ) const;
	
		/*
		* return: true if this Time is greater than the right-hand side.
		*/
		bool operator>( const Time& rhs ) const;
	
		/* 
		* return: true if this Time is greather than or equal to
		*  the right-hand side.
		*/
		bool operator>=( const Time& rhs ) const;
	
	//-----------------------------------------------------------------
	// Negation / Addition / Subtraction
	//-----------------------------------------------------------------

		/*
		* return: A negative copy of this Time. 
		*
		* Example:
		*    void neverFail( const Time t )
		*    {
		*       assert( t + (-t) == Time(ZERO) );
		*    }
		*/
		const Time operator-() const;
	
		/*
		* return: The sum of this Time and the right-hand side. 
		*
		* Example:
		*    void neverFail( const Time t )
		*    {
		*       assert( t + t == 2 * t );
		*    }
		*/
		const Time operator+( const Time& rhs ) const;
	
		/*
		* return: The difference between this Time and the right-hand side. 
		*
		* Example: 
		*    void neverFail( const Time t )
		*    {
		*       assert( t - t == Time(ZERO) );
		*    }
		*/
		const Time operator-( const Time& rhs ) const;
	
		/*
		* Adds the right-hand side to this Time.
		*
		* return: This Time. 
		*
		*  Example:
		*    void zeroOutTime( Time& t )
		*    {
		*       t += (-t);
		*       assert( Time(ZERO) == t );
		*    }
		*/
		Time& operator+=( const Time& rhs );
	
		/*
		* Subtracts the right-hand side from this Time.
		*
		* return: This Time. 
		*
		*  Example:
		*    void zeroOutTime( Time& t )
		*    {
		*       t -= t;
		*       assert( Time(ZERO) == t );
		*    }
		*/
		Time& operator-=( const Time& rhs );
	
	//-----------------------------------------------------------------
	// Multiplication
	//-----------------------------------------------------------------

		/*
		* return: The product of this Time and the specified float. 
		*
		* Example:
		*    const Time halfSecond = Time(ONE_SECOND) * 0.5f;
		*/
		const Time operator*( const float ) const;
	
		/*
		* return: The product of this Time and the specified integer. 
		*
		*  Example:
		*    const Time fourMinutes = Time(ONE_MINUTE) * 4;
		*/
		const Time operator*( const int ) const;
	
		/*
		* Multiplies this Time by the specified float.
		*
		* return: This Time. 
		*
		* Example:
		*    void decayTime( Time& t )
		*    {
		*       t *= 0.95f;
		*    }
		*/
		Time& operator*=( const float );
	
		/*
		* Multiplies this Time by the specified integer.
		*
		* return: This Time. 
		*
		* Example:
		*    void doubleTime( Time& t )
		*    {
		*       t *= 2;
		*    }
		*/
		Time& operator*=( const int );
	
	//-----------------------------------------------------------------
	// name: Division
	//-----------------------------------------------------------------

		/*
		* return: The ratio of this Time divided by the denominator Time.
		*
		* note: Dividing by Time::ZERO is undefined.
		*/
		float operator/( const Time& denominator ) const;
	
		/*
		* return: The result of dividing this Time and by the
		* specified float.
		*
		* note: Dividing by zero is undefined.
		*/
		const Time operator/( const float denominator ) const;
	
		/*
		* return: The result of dividing this Time and by the
		* specified integer.
		*
		* note: Dividing by zero is undefined.
		*/
		const Time operator/( const int denominator ) const;
	
		/*
		* Divides this Time by the specified float.
		*
		* return: This Time. 
		*
		* note: Dividing by zero is undefined.
		*/
		Time& operator/=( const float );
	
		/*
		* Divides this Time by the specified integer.
		*
		* return: This Time. 
		*
		* note: Dividing by zero is undefined.
		*/
		Time& operator/=( const int );
	
	//-----------------------------------------------------------------
	// Quotient / Remainder
	//-----------------------------------------------------------------
	
		/*
		* return: The <i>truncated</i>, integral division of the
		* numerator and denominator.  In other words,
		* the result of the division is rounded down to the nearest
		* integer.
		*
		* note: Dividing by Time(ZERO) is undefined.
		*/
		static int 	quotient( const Time& numerator, const Time& denominator );
	
		/*
		* return: The remainder of dividing the numerator into the
		* denominator.  This is the equivalent of a modulus operation.
		*
		* note: Dividing by Time(ZERO) is undefined.
		*/
		static const Time 	remainder( const Time& numerator, const Time& denominator );

	private:
		// types
		typedef long long Representation;

		// constructor
		explicit Time( const Representation );

		// data
		Representation _rawTime;
};




//---------------------------------------------------------------------------
// INLINED IMPLEMENTATION:
//---------------------------------------------------------------------------
Time::Time(): _rawTime( 0 )
{
}


Time::Time( const Time& rhs ): _rawTime( rhs._rawTime )
{
}


Time& Time::operator=( const Time& rhs )
{
	if ( this != &rhs )
	{
		this->_rawTime = rhs._rawTime;
	}

	return( *this );
}



#endif  

