// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <uslscore/STLString.h>
#include <algorithm>
#include <cctype>
#include <iostream>

#include <uslscore/USBase64Cipher.h>
#include <uslscore/USCipherStream.h>
#include <uslscore/USMemStream.h>

//================================================================//
// STLString
//================================================================//

//----------------------------------------------------------------//
void STLString::base_64_encode ( const void* buffer, u32 len ) {
	
	( *this ) = "";
	if ( !len ) return;
	
	USCipherStream cipherStream;
	USMemStream memStream;
	USBase64Cipher base64;
	
	cipherStream.OpenCipher ( memStream, base64 );
	cipherStream.WriteBytes ( buffer, len );
	cipherStream.CloseCipher ();
	
	memStream.Seek ( 0, SEEK_SET );
	( *this ) = memStream.ToString ( memStream.GetLength ());
}

//----------------------------------------------------------------//
STLString STLString::clip ( u32 first, u32 last ) {

	return this->substr ( first, last - first );
}

//----------------------------------------------------------------//
STLString STLString::clip_to_back ( u32 first ) {

	return this->substr ( first );
}

//----------------------------------------------------------------//
STLString STLString::clip_to_front ( u32 last ) {

	return this->substr ( 0, last );
}

//----------------------------------------------------------------//
void STLString::hex_encode ( const void* buffer, u32 len ) {

	( *this ) = "";
	if ( !len ) return;

	u8* digits = ( u8* )buffer;

	for ( u32 i = 0; i < len; ++i ) {
		this->write ( "%02X", ( u32 )digits [ i ]);
	}
}

//----------------------------------------------------------------//
void STLString::replace_char ( cc8 match, cc8 sub ) {

	for ( u32 i = 0; this->peek ( i ); ++i ) {
		if ( this->peek ( i ) == match ) {
			this->at ( i ) = sub;
		}
	}
}

//----------------------------------------------------------------//
void STLString::tokenize ( STLArray < STLString > & tokens, const STLString& delimiters ) {

	STLString::size_type lastPos = this->find_first_not_of ( delimiters, 0 );
	STLString::size_type pos = this->find_first_of ( delimiters, lastPos );

	while (( STLString::npos != pos ) || ( STLString::npos != lastPos )) {
        tokens.push_back ( this->substr ( lastPos, pos - lastPos ));
		lastPos = this->find_first_not_of ( delimiters, pos );
		pos = this->find_first_of ( delimiters, lastPos );
	}
}

//----------------------------------------------------------------//
double STLString::to_double () {

	return atof ( this->str ());
}

//----------------------------------------------------------------//
float STLString::to_float () {

	return ( float )atof ( this->str ());
}

//----------------------------------------------------------------//
int STLString::to_int () {

	return atoi ( this->str ());
}

//----------------------------------------------------------------//
void STLString::to_lower () {

	transform ( this->begin (), this->end (),this->begin (), ( int( * )( int ))tolower );
}

//----------------------------------------------------------------//
void STLString::to_upper () {

	transform ( this->begin (), this->end (),this->begin (), ( int( * )( int ))toupper );
}

//----------------------------------------------------------------//
void STLString::write ( cc8* format, ... ) {

	va_list args;
	va_start ( args, format );
	
	this->write_var ( format, args );
	
	va_end ( args );
}

//----------------------------------------------------------------//
void STLString::write_var ( cc8* format, va_list args ) {

	// TODO: fix me
	char buffer [ 4096 ];
	vsprintf ( buffer, format, args );
	this->append ( buffer );
}

//----------------------------------------------------------------//

STLString::STLString ( int value, int radix ) {

	const char *format;

	switch ( radix ) {

		case 8:
			format = "%o";
			break;
		case 10:
			format = "%i";
			break;
		case 16:
			format = "%08X";
			break;
		default:
			format = "%i";
	}

	write ( format, value );
}

//----------------------------------------------------------------//
STLString::STLString ( double value ) {

	write ( "%f", value );
}