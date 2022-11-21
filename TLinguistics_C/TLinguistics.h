/*  File TLinguistics.h


 *	Realization of TWord and its heirs (Noun, Verb, Adjective, Numeral, Pronoun, Adverb) structures,
	input and ouput methods, breaking in and work with parts of TWord functions.


 *	Taking into account the fact that there is no possibility to implement a class in c,
    a structure TWord and its heirs structures are used as analogues.


 *	!!!Attention!!! 

	The module is designed to work with Ukrainian text.
	For compatibility with third-party wchar_t type objects connect the appropriate file conversion mode _O_U16TEXT (Unicode) for reading/writing wide-character strings from/to the stream.
	Unicode is for advanced reading/printing functions (like wprintf) only. All functions and methods in this module are initialized based on such functions.
	The author recommends using this piece of code at the beginning of your main.c file:

	fflush(stdout);
	_setmode(_fileno(stdout), _O_U16TEXT);
	fflush(stdin);
	_setmode(_fileno(stdin), _O_U16TEXT);

	and adding "ccs=UTF-16LE" or "ccs=UTF-8" to file opening mode parametre.



 *	Done by Yanhol Yaroslav (group: Computer mechanics 2)
	Date __.__.____


 *	Headers for TWord structure and its heirs
*/

/* Constants */


#define SyllsAmount 20
#define SyllsLen 11

#define WideStringLen 151
#define TWordLen 51
#define TWordPropFieldLen 21

/* Headers */

#include <wchar.h>



/* Helper functions */

/* Determine if there is the same wide character in the string
	@param[c] - character to find
	@param[str[]] - wide character array (wide character string) which can contain the wanted character
	@result – int :
	1 - if found,
	0 - if not found
*/
extern int iswchar_inwcs(wchar_t c, wchar_t str[]);

/* Determine if wchar_t character is equal to the other wchar_t character 
	@param[c1] - 1st character to compare
	@param[c2] - 2nd character to compare
	@result – int :
	1 - if equal,
	0 - if not equal
*/
extern int iswchar_eq(wchar_t c1, wchar_t c2);



/* Base structures of TWord fields */
/*
// prefix field
typedef struct prefix {
	wchar_t prefixes[3][15];
} Prefix;

// radix field
typedef struct radix {
	wchar_t radixes[2][15];
} Radix;

// suffix field
typedef struct suffix {
	wchar_t suffixes[3][15];
} Suffix;

// ending field
typedef struct ending {
	wchar_t endings[1][10];
} Ending;
*/



/* Base structure of syllables array */

// Declaration of private fields
typedef struct _SyllsArrayPrivate {

	wchar_t sylls[SyllsAmount][SyllsLen];
	int n;

} SyllsArrayPrivate;

// Declaration of pointer to structure
typedef struct _SyllsArray {
	SyllsArrayPrivate* private;
} SyllsArray;



/* Functions for the SyllsArray */

// Declaration of SyllsArray constructor
extern void SyllsArray_Constructor(SyllsArray* sylarr);

// Declaration of SyllsArray destructor
extern void SyllsArray_Destructor(SyllsArray* sylarr);

/* Function of creating a new SyllsArray object:
	create new syllables array
	@result – SyllsArray*
*/
extern SyllsArray* SyllsArray_New(void);

/* Function of deleting a SyllsArray object:
	delete syllables array
	@param[sylarr] - SyllsArray* to delete
*/
extern void SyllsArray_Delete(SyllsArray* sylarr);

/* Input syllables array:
	input word from console/file/binfile
	@param[sylarr] - OUT – SyllsArray* for return
	@param[istream] - input stream (stdin, FILE*)
	@param[f_type] - char string to tell the type of file ("txt" or "bin")
	@result – int :
	0 - in the case of success,
	error_code – number of error
*/
extern int InputSyllsArray(SyllsArray* sylarr, FILE* istream, const char* f_type);

/* Output syllables array:
	write word to console/file/binfile
	@param[sylarr] - IN - SyllsArray*
	@param[ostream] - output stream (stdout, FILE*)
	@param[f_type] - char string to tell the type of file ("txt" or "bin")
	@result - void
*/
extern void OutputSyllsArray(SyllsArray* sylarr, FILE* ostream, const char* f_type);



/* Base structure of word */

// Declaration of private fields
typedef struct _TWordPrivate {

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

} TWordPrivate;

// Declaration of pointer to structure
typedef struct _TWord {
	TWordPrivate* private;
} TWord;



/* Functions for the TWord */

// Declaration of TWord constructor
extern void TWord_Constructor(TWord* word);

// Declaration of TWord destructor
extern void TWord_Destructor(TWord* word);

/* Function of creating a new TWord object:
    create new word
	@result – TWord*
*/
extern TWord* TWord_New(void);

/* Function of deleting a TWord object:
	delete word
	@param[word] - word to delete
*/
extern void TWord_Delete(TWord* word);



/* Input word:
	input word from console/file/binfile
	@param[w] - OUT – Word for return
	@param[istream] - input stream (stdin, FILE*)
	@param[f_type] - char string to tell the type of file ("txt" or "bin")
	@result – int :
	0 - in the case of success,
	error_code – number of error
*/
extern int InputWord(TWord* w, FILE* istream, const char* f_type);

/* Output word:
	write word to console/file/binfile
	@param[w] - IN word*
	@param[ostream] - output stream (stdout, FILE*)
	@param[f_type] - char string to tell the type of file ("txt" or "bin")
	@result - void
*/
extern void OutputWord(TWord* w, FILE* ostream, const char* f_type);

/* Input word text field:
	input word  text field from console/file/binfile
	@param[w] - OUT – Word for return
	@param[istream] - input stream (stdin, FILE*)
	@param[f_type] - char string to tell the type of file ("txt" or "bin")
	@result – int :
	0 - in the case of success,
	error_code – number of error
*/
extern int InputWordText(TWord* w, FILE* istream, const char* f_type);

/* Output word text field:
	write word text field to console/file/binfile
	@param[w] - IN word*
	@param[ostream] - output stream (stdout, FILE*)
	@param[f_type] - char string to tell the type of file ("txt" or "bin")
	@result - void
*/
extern void OutputWordText(TWord* w, FILE* ostream, const char* f_type);

/* Get text from TWord field
	@param[w] - TWord*
	@result - wchar_t
*/
wchar_t GetWordText(TWord* w);

/* Set text to TWord field:
	@param[w] - TWord*
	@param[text] - wchar_t
	@result - void
*/
void SetWordText(TWord* w, wchar_t text);

/* Breakdown word:
	break the word into syllables and put them in array
	@param - IN word*
	@result - SyllablesArray*
*/
extern void BreakdownWord(TWord* w, SyllsArray* sylarr);

/* Combine word:
	combine syllables unto a word
	@param[in_arr] - IN - SyllablesArray to combine
	@result – new TWord*
*/
extern TWord* CombineWord(SyllsArray* sylarr);

/* Input word by parts:
	input word from console/file/binfile by parts
	@param[w] - OUT – Word for return
	@param[mode] - input mode (L"c" - console, L"f" - file, L"b" - binary file)
	@result – int :
	0 - in the case of success,
	error_code – number of error
*/
extern int InputWordByParts(TWord* w, FILE* istream, const char* f_type);

/* Output word by parts:
	write word to console/file/binfile by parts
	@param[w] - TWord
	@param[mode] - output mode (L"c" - console, L"f" - file, L"b" - binary file)
	@result - void
*/
extern void OutputWordByParts(TWord* w, FILE* ostream, const char* f_type);

/* Set word properties:
	Set word properties like type, gender, quantity and sort
	@param - IN word
	@result - void
*/
extern void SetWordProps(TWord* w);

/* Change word properties:
	Change word properties like quantity and sort
	@param - IN word
	@result - void
*/
extern void ChangeWordProps(TWord* w);



/* Functions for the TWord fields */

/* Input prefix:
	input prefix from console/file/binfile
	@param[w] - OUT – Word for return
	@param[mode] - input mode ("c" - console, "f" - file, "b" - binary file)
	@result – int :
	0 - in the case of success,
	error_code – number of error
*/
extern int InputPrefix(TWord* w, const wchar_t* mode);

/* Output prefix:
	write prefix to console/file/binfile
	@param[w] - IN word
	@param[mode] - output mode ("c" - console, "f" - file, "b" - binary file)
	@result - void
*/
extern void OutputPrefix(TWord* w, const wchar_t* mode);

/* Input radix:
	input radix from console/file/binfile
	@param[w] - OUT – Word for return
	@param[mode] - input mode ("c" - console, "f" - file, "b" - binary file)
	@result – int :
	0 - in the case of success,
	error_code – number of error
*/
extern int InputRadix(TWord* w, const wchar_t* mode);

/* Output radix:
	write radix to console/file/binfile
	@param[w] - IN word
	@param[mode] - output mode ("c" - console, "f" - file, "b" - binary file)
	@result - void
*/
extern void OutputRadix(TWord* w, const wchar_t* mode);

/* Input suffix:
	input suffix from console/file/binfile
	@param[w] - OUT – Word for return
	@param[mode] - input mode ("c" - console, "f" - file, "b" - binary file)
	@result – int :
	0 - in the case of success,
	error_code – number of error
*/
extern int InputSuffix(TWord* w, const wchar_t* mode);

/* Output suffix:
	write suffix to console/file/binfile
	@param[w] - IN word
	@param[mode] - output mode ("c" - console, "f" - file, "b" - binary file)
	@result - void
*/
extern void OutputSuffix(TWord* w, const wchar_t* mode);

/* Input ending:
	input ending from console/file/binfile
	@param[w] - OUT – Word for return
	@param[mode] - input mode ("c" - console, "f" - file, "b" - binary file)
	@result – int :
	0 - in the case of success,
	error_code – number of error
*/
extern int InputEnding(TWord* w, const wchar_t* mode);

/* Output ending:
	write ending to console/file/binfile
	@param[w] - IN word
	@param[mode] - output mode ("c" - console, "f" - file, "b" - binary file)
	@result - void
*/
extern void OutputEnding(TWord* w, const wchar_t* mode);
