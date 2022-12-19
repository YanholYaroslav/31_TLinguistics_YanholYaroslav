/*  File TLinguistics.h


 *	Realization of TWord and its heirs (Noun, Verb, Adjective, Numeral, Pronoun, Adverb) classes,
	input and ouput methods, breaking in and work with parts of TWord functions.


 *	!!!Attention!!! 

	The module is designed to work with Ukrainian text.
	For compatibility with third-party wchar_t type objects connect the appropriate file conversion mode _O_U16TEXT (Unicode) for reading/writing wide-character strings from/to the stream.
	Unicode is for advanced reading/printing functions (like wcout) only. All functions and methods in this module are initialized based on such functions.
	The author recommends using this piece of code at the beginning of your main.cpp file:

	fflush(stdout);
	_setmode(_fileno(stdout), _O_U16TEXT);
	fflush(stdin);
	_setmode(_fileno(stdin), _O_U16TEXT);

	and setting locales for file streams.



 *	Done by Yanhol Yaroslav (group: Computer mechanics)
	Date 20.12.2022


 *	Headers for TWord class and its heirs
*/

/* Constants */


#define SyllsAmount 20
#define SyllsLen 11

#define WideStringLen 151
#define TWordLen 51
#define TWordPropFieldLen 21

/* Headers */

#include <cwchar>
#include <iostream>

using namespace std;



/* Helper functions */

/* Determine if there is the same wide character in the string
	@param[c] - character to find
	@param[str[]] - wide character array (wide character string) which can contain the wanted character
	@result - int :
	1 - if found,
	0 - if not found
*/
extern int iswchar_inwcs(wchar_t c, wchar_t str[]);

/* Determine if wchar_t character is equal to the other wchar_t character 
	@param[c1] - 1st character to compare
	@param[c2] - 2nd character to compare
	@result - int :
	1 - if equal,
	0 - if not equal
*/
extern int iswchar_eq(wchar_t* c1, wchar_t* c2);





/* Base class of syllables array */

class SyllsArray {

protected:

	

public:

	/* Fields */

	wchar_t sylls[SyllsAmount][SyllsLen];
	int n;

	/* Methods */

	// Declaration of SyllsArray constructor
	SyllsArray() {}

	// Declaration of SyllsArray destructor
	~SyllsArray() {}

	/* Input syllables array:
	input syllables array from console/text file
	@param[inp] - output stream (wcin, fstream)
	@result - int :
	0 - in the case of success,
	error_code - number of error
	*/
	int input(wistream& inp = wcin);

	/* Output syllables array:
		write syllables array to console/text file
		@param[out] - output stream (wcout, fstream)
		@result - void
	*/
	void output(wostream& out = wcout);

	/* Friend operator<<
	param[out] - c++ style out wstream
	param[w] - SyllsArray object to output
	*/
	friend wostream& operator<< (wostream& out, SyllsArray& arr);

};





/* Base class of word */

class TWord {

protected:

	/* Fields */

	wchar_t text[TWordLen];
	wchar_t type[TWordPropFieldLen];
	wchar_t gender[TWordPropFieldLen];
	wchar_t quantity[TWordPropFieldLen];
	wchar_t person[TWordPropFieldLen];
	wchar_t sort[TWordPropFieldLen];

	wchar_t prefix[3][10];
	wchar_t radix[2][15];
	wchar_t suffix[3][10];
	wchar_t ending[1][10];

	// Declaration of TWord init
	void init();

public:

	/* Methods */

	// Declaration of TWord constructor
	TWord();

	// Declaration of TWord destructor
	~TWord() {}


	/* Input word:
	input word from console/text file
	@param[inp] - input wstream (wcin, fstream)
	@result - int :
	0 - in the case of success,
	error_code - number of error
	*/
	int input(wistream& inp = wcin);

	/* Friend operator>>
	param[out] - c++ style input wstream
	param[w] - TWord object to input
	*/
	friend wistream& operator>> (wistream& inp, TWord& w);

	/* Output word:
	write word to console/text file
	@param[out] - output wstream (wcout, fstream)
	@result - void
	*/
	void output(wostream& out = wcout);

	/* Friend operator<< 
	param[out] - c++ style output wstream
	param[w] - TWord object to output
	*/
	friend wostream& operator<< (wostream& out, TWord& w);

	/* Input word text field:
	input word text field from console/text file
	@param[inp] - input stream (wcin, fstream)
	@result - int :
	0 - in the case of success,
	error_code - number of error
	*/
	int input_text(wistream& inp = wcin);

	/* Output word text field:
	write word text field to console/text file
	@param[out] - output stream (wcout, fstream)
	@result - void
	*/
	void output_text(wostream& out = wcout);

	/* Get text from TWord field
	param[text_out] - OUT - wchar_t*
	@result - void
	*/
	void get_text(wchar_t* text_out);

	/* Set text to TWord field:
	@param[text_in] - wchar_t*
	@result - void
	*/
	void set_text(wchar_t* text_in);

	/* Breakdown word:
	break the word into syllables and put them in array
	@param[sylarr] - SyllablesArray
	*/
	void breakdown(SyllsArray& sylarr);

	/* Combine word:
	combine syllables unto a word
	@param[in_arr] - IN - SyllablesArray to combine
	@result - void
	*/
	void combine(SyllsArray sylarr);

	/* Input word by parts:
	input word from console/text file by parts
	@param[inp] - input stream (wcin, fstream)
	@result - int :
	0 - in the case of success,
	error_code - number of error
	*/
	int input_by_parts(wistream& inp = wcin);

	/* Output word by parts:
	write word to console/text file by parts
	@param[out] - output stream (wcout, fstream)
	@result - void
	*/
	void output_by_parts(wostream& out = wcout);

	/* Set word properties:
	Set word properties like type, gender, quantity and sort
	@param[type] - const wchar_t* string
	@param[gender] - const wchar_t* string
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
	*/
	void set_props(const wchar_t* type, const wchar_t* gender, const wchar_t* quantity, const wchar_t* sort);

	/* Change word properties:
	Change word properties like quantity and sort
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
	*/
	void change_props(const wchar_t* quantity, const wchar_t* sort);

};





/* Base class of TNoun */

class TNoun : public TWord {

};



/* Base class of TVerb */

class TVerb : public TWord {

};



/* Base class of TAdjective */

class TAdjective : public TWord {

};



/* Base class of TNumeral */

class TNumeral : public TWord {

};



/* Base class of TPronoun */

class TPronoun : public TWord {

};



/* Base class of TAdverb */

class TAdverb : public TWord {

};
