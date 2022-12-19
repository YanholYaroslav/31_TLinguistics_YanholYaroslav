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

	and adding "ccs=UTF-16LE" to file opening mode parametres for FILE* streams.



 *	Done by Yanhol Yaroslav (group: Computer mechanics)
	Date 20.12.2022


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
extern int iswchar_eq(wchar_t c1, wchar_t c2);










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
	@result - SyllsArray*
*/
extern SyllsArray* SyllsArray_New(void);

/* Function of deleting a SyllsArray object:
	delete syllables array
	@param[sylarr] - SyllsArray* to delete
*/
extern void SyllsArray_Delete(SyllsArray* sylarr);

/* Input syllables array:
	input word from console/file/binfile
	@param[sylarr] - OUT - SyllsArray* for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputSyllsArray(SyllsArray* sylarr, FILE* istream);

/* Output syllables array:
	write word to console/file/binfile
	@param[sylarr] - IN - SyllsArray*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputSyllsArray(SyllsArray* sylarr, FILE* ostream);










/* Base structure of TWord */


// Declaration of TWord private fields
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

// Declaration of pointer to TWord structure
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
	@result - TWord*
*/
extern TWord* TWord_New(void);

/* Function of deleting a TWord object:
	delete word
	@param[word] - word to delete
*/
extern void TWord_Delete(TWord* word);



/* Input word:
	input word from console/file/binfile
	@param[w] - OUT - Word for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputWord(TWord* w, FILE* istream);

/* Output word:
	write word to console/file/binfile
	@param[w] - IN word*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputWord(TWord* w, FILE* ostream);

/* Input word text field:
	input word  text field from console/file/binfile
	@param[w] - OUT - Word for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputWordText(TWord* w, FILE* istream);

/* Output word text field:
	write word text field to console/file/binfile
	@param[w] - IN word*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputWordText(TWord* w, FILE* ostream);

/* Get text from TWord field
	@param[w] - TWord*
	@result - wchar_t* array
*/
extern void GetWordText(TWord* w, wchar_t* text[]);

/* Set text to TWord field:
	@param[w] - TWord*
	@param[text] - wchar_t* array
	@result - void
*/
extern void SetWordText(TWord* w, wchar_t* text[]);

/* Breakdown word:
	break the word into syllables and put them in array
	@param - IN word*
	@result - SyllablesArray*
*/
extern void BreakdownWord(TWord* w, SyllsArray* sylarr);

/* Combine word:
	combine syllables unto a word
	@param[in_arr] - IN - SyllablesArray to combine
	@result - new TWord*
*/
extern TWord* CombineWord(SyllsArray* sylarr);

/* Input word by parts:
	input word from console/file/binfile by parts
	@param[w] - OUT - Word for return
	@param[istream] - input stream (stdout, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputWordByParts(TWord* w, FILE* istream);

/* Output word by parts:
	write word to console/file/binfile by parts
	@param[w] - TWord
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputWordByParts(TWord* w, FILE* ostream);

/* Set word properties:
	Set word properties like type, gender, quantity and sort
	@param[w] - OUT - TWord*
	@param[type] - const wchar_t* string
	@param[gender] - const wchar_t* string
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void SetWordProps(TWord* w, const wchar_t* type, const wchar_t* gender, const wchar_t* quantity, const wchar_t* sort);

/* Change word properties:
	Change word properties like quantity and sort
	@param[w] - OUT - TWord*
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void ChangeWordProps(TWord* w, const wchar_t* quantity, const wchar_t* sort);









/* Declarations of TWord heirs (TNoun, TVerb, TAdjective, TNumeral, TPronoun, TAdverb) structures. */



/* Base structure of TNoun */


// Declaration of TNoun private fields
typedef struct _TNounPrivate {
	unsigned char uch;
} TNounPrivate;

// Declaration of pointer to TNoun structure
typedef struct _TNoun {
	TWord parent;
	TNounPrivate* private;
} TNoun;


// Declaration of TNoun constructor
extern void TNoun_Constructor(TNoun* T);

// Declaration of TNoun destructor
extern void TNoun_Destructor(TNoun* T);

/* Function of creating a new TNoun object:
	create new noun
	@result - TNoun*
*/
extern TNoun* TNoun_New(void);

/* Function of deleting a TNoun object:
	delete noun
	@param[T] - noun to delete
*/
extern void TNoun_Delete(TNoun* T);

/* Input noun:
	input noun from console/file/binfile
	@param[T] - OUT - noun for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputNoun(TNoun* T, FILE* istream);

/* Output noun:
	write noun to console/file/binfile
	@param[T] - IN noun*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/

extern void OutputNoun(TNoun* T, FILE* ostream);

/* Input noun text field:
	input noun  text field from console/file/binfile
	@param[T] - OUT - noun for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputNounText(TNoun* T, FILE* istream);

/* Output noun text field:
	write noun text field to console/file/binfile
	@param[T] - IN noun*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputNounText(TNoun* T, FILE* ostream);

/* Get text from TNoun field
	@param[T] - TNoun*
	@param[text] - OUT - wchar_t* text
*/
extern void GetNounText(TWord* w, wchar_t* text[]);

/* Set text to TNoun field:
	@param[T] - TNoun*
	@param[text] - wchar_t
	@result - void
*/
extern void SetNounText(TNoun* T, wchar_t* text[]);

/* Breakdown noun:
	break the noun into syllables and put them in array
	@param - IN noun*
	@result - SyllablesArray*
*/
extern void BreakdownNoun(TNoun* T, SyllsArray* sylarr);

/* Combine noun:
	combine syllables unto a noun
	@param[in_arr] - IN - SyllablesArray to combine
	@result - new TNoun*
*/
extern TNoun* CombineNoun(SyllsArray* sylarr);

/* Input noun by parts:
	input noun from console/file/binfile by parts
	@param[T] - OUT - noun for return
	@param[istream] - input stream (stdout, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputNounByParts(TNoun* T, FILE* istream);

/* Output noun by parts:
	write noun to console/file/binfile by parts
	@param[T] - TNoun
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputNounByParts(TNoun* T, FILE* ostream);

/* Set noun properties:
	Set noun properties like type, gender, quantity and sort
	@param[T] - OUT - TNoun*
	@param[type] - const wchar_t* string
	@param[gender] - const wchar_t* string
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void SetNounProps(TNoun* w, wchar_t type[], wchar_t gender[], wchar_t quantity[], wchar_t sort[]);

/* Change noun properties:
	Change noun properties like quantity and sort
	@param[T] - OUT - Tnoun*
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void ChangeNounProps(TNoun* T, wchar_t quantity[], wchar_t sort[]);









/* Base structure of TAdjective */


// Declaration of TAdjective private fields
typedef struct _TAdjectivePrivate {
	unsigned char uch;
} TAdjectivePrivate;

// Declaration of pointer to TAdjective structure
typedef struct _TAdjective {
	TWord parent;
	TAdjectivePrivate* private;
} TAdjective;


// Declaration of TAdjective constructor
extern void TAdjective_Constructor(TAdjective* T);

// Declaration of TAdjective destructor
extern void TAdjective_Destructor(TAdjective* T);

/* Function of creating a new TAdjective object:
	create new Adjective
	@result - TAdjective*
*/
extern TAdjective* TAdjective_New(void);

/* Function of deleting a TAdjective object:
	delete Adjective
	@param[T] - Adjective to delete
*/
extern void TAdjective_Delete(TAdjective* T);

/* Input Adjective:
	input Adjective from console/file/binfile
	@param[T] - OUT - Adjective for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputAdjective(TAdjective* T, FILE* istream);

/* Output Adjective:
	write Adjective to console/file/binfile
	@param[T] - IN Adjective*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/

extern void OutputAdjective(TAdjective* T, FILE* ostream);

/* Input Adjective text field:
	input Adjective  text field from console/file/binfile
	@param[T] - OUT - Adjective for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputAdjectiveText(TAdjective* T, FILE* istream);

/* Output Adjective text field:
	write Adjective text field to console/file/binfile
	@param[T] - IN Adjective*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputAdjectiveText(TAdjective* T, FILE* ostream);

/* Get text from TAdjective field
	@param[T] - TAdjective*
	@param[text] - OUT - wchar_t* text
*/
extern void GetAdjectiveText(TWord* w, wchar_t* text[]);

/* Set text to TAdjective field:
	@param[T] - TAdjective*
	@param[text] - wchar_t
	@result - void
*/
extern void SetAdjectiveText(TAdjective* T, wchar_t* text[]);

/* Breakdown Adjective:
	break the Adjective into syllables and put them in array
	@param - IN Adjective*
	@result - SyllablesArray*
*/
extern void BreakdownAdjective(TAdjective* T, SyllsArray* sylarr);

/* Combine Adjective:
	combine syllables unto a Adjective
	@param[in_arr] - IN - SyllablesArray to combine
	@result - new TAdjective*
*/
extern TAdjective* CombineAdjective(SyllsArray* sylarr);

/* Input Adjective by parts:
	input Adjective from console/file/binfile by parts
	@param[T] - OUT - Adjective for return
	@param[istream] - input stream (stdout, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputAdjectiveByParts(TAdjective* T, FILE* istream);

/* Output Adjective by parts:
	write Adjective to console/file/binfile by parts
	@param[T] - TAdjective
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputAdjectiveByParts(TAdjective* T, FILE* ostream);

/* Set Adjective properties:
	Set Adjective properties like type, gender, quantity and sort
	@param[T] - OUT - TAdjective*
	@param[type] - const wchar_t* string
	@param[gender] - const wchar_t* string
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void SetAdjectiveProps(TAdjective* w, wchar_t type[], wchar_t gender[], wchar_t quantity[], wchar_t sort[]);

/* Change Adjective properties:
	Change Adjective properties like quantity and sort
	@param[T] - OUT - TAdjective*
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void ChangeAdjectiveProps(TAdjective* T, wchar_t quantity[], wchar_t sort[]);









/* Base structure of TNumeral */


// Declaration of TNumeral private fields
typedef struct _TNumeralPrivate {
	unsigned char uch;
} TNumeralPrivate;

// Declaration of pointer to TNumeral structure
typedef struct _TNumeral {
	TWord parent;
	TNumeralPrivate* private;
} TNumeral;


// Declaration of TNumeral constructor
extern void TNumeral_Constructor(TNumeral* T);

// Declaration of TNumeral destructor
extern void TNumeral_Destructor(TNumeral* T);

/* Function of creating a new TNumeral object:
	create new Numeral
	@result - TNumeral*
*/
extern TNumeral* TNumeral_New(void);

/* Function of deleting a TNumeral object:
	delete Numeral
	@param[T] - Numeral to delete
*/
extern void TNumeral_Delete(TNumeral* T);

/* Input Numeral:
	input Numeral from console/file/binfile
	@param[T] - OUT - Numeral for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputNumeral(TNumeral* T, FILE* istream);

/* Output Numeral:
	write Numeral to console/file/binfile
	@param[T] - IN Numeral*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/

extern void OutputNumeral(TNumeral* T, FILE* ostream);

/* Input Numeral text field:
	input Numeral  text field from console/file/binfile
	@param[T] - OUT - Numeral for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputNumeralText(TNumeral* T, FILE* istream);

/* Output Numeral text field:
	write Numeral text field to console/file/binfile
	@param[T] - IN Numeral*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputNumeralText(TNumeral* T, FILE* ostream);

/* Get text from TNumeral field
	@param[T] - TNumeral*
	@param[text] - OUT - wchar_t* text
*/
extern void GetNumeralText(TWord* w, wchar_t* text[]);

/* Set text to TNumeral field:
	@param[T] - TNumeral*
	@param[text] - wchar_t
	@result - void
*/
extern void SetNumeralText(TNumeral* T, wchar_t* text[]);

/* Breakdown Numeral:
	break the Numeral into syllables and put them in array
	@param - IN Numeral*
	@result - SyllablesArray*
*/
extern void BreakdownNumeral(TNumeral* T, SyllsArray* sylarr);

/* Combine Numeral:
	combine syllables unto a Numeral
	@param[in_arr] - IN - SyllablesArray to combine
	@result - new TNumeral*
*/
extern TNumeral* CombineNumeral(SyllsArray* sylarr);

/* Input Numeral by parts:
	input Numeral from console/file/binfile by parts
	@param[T] - OUT - Numeral for return
	@param[istream] - input stream (stdout, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputNumeralByParts(TNumeral* T, FILE* istream);

/* Output Numeral by parts:
	write Numeral to console/file/binfile by parts
	@param[T] - TNumeral
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputNumeralByParts(TNumeral* T, FILE* ostream);

/* Set Numeral properties:
	Set Numeral properties like type, gender, quantity and sort
	@param[T] - OUT - TNumeral*
	@param[type] - const wchar_t* string
	@param[gender] - const wchar_t* string
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void SetNumeralProps(TNumeral* w, wchar_t type[], wchar_t gender[], wchar_t quantity[], wchar_t sort[]);

/* Change Numeral properties:
	Change Numeral properties like quantity and sort
	@param[T] - OUT - TNumeral*
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void ChangeNumeralProps(TNumeral* T, wchar_t quantity[], wchar_t sort[]);









/* Base structure of TPronoun */


// Declaration of TPronoun private fields
typedef struct _TPronounPrivate {
	unsigned char uch;
} TPronounPrivate;

// Declaration of pointer to TPronoun structure
typedef struct _TPronoun {
	TWord parent;
	TPronounPrivate* private;
} TPronoun;


// Declaration of TPronoun constructor
extern void TPronoun_Constructor(TPronoun* T);

// Declaration of TPronoun destructor
extern void TPronoun_Destructor(TPronoun* T);

/* Function of creating a new TPronoun object:
	create new Pronoun
	@result - TPronoun*
*/
extern TPronoun* TPronoun_New(void);

/* Function of deleting a TPronoun object:
	delete Pronoun
	@param[T] - Pronoun to delete
*/
extern void TPronoun_Delete(TPronoun* T);

/* Input Pronoun:
	input Pronoun from console/file/binfile
	@param[T] - OUT - Pronoun for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputPronoun(TPronoun* T, FILE* istream);

/* Output Pronoun:
	write Pronoun to console/file/binfile
	@param[T] - IN Pronoun*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/

extern void OutputPronoun(TPronoun* T, FILE* ostream);

/* Input Pronoun text field:
	input Pronoun  text field from console/file/binfile
	@param[T] - OUT - Pronoun for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputPronounText(TPronoun* T, FILE* istream);

/* Output Pronoun text field:
	write Pronoun text field to console/file/binfile
	@param[T] - IN Pronoun*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputPronounText(TPronoun* T, FILE* ostream);

/* Get text from TPronoun field
	@param[T] - TPronoun*
	@param[text] - OUT - wchar_t* text
*/
extern void GetPronounText(TWord* w, wchar_t* text[]);

/* Set text to TPronoun field:
	@param[T] - TPronoun*
	@param[text] - wchar_t
	@result - void
*/
extern void SetPronounText(TPronoun* T, wchar_t* text[]);

/* Breakdown Pronoun:
	break the Pronoun into syllables and put them in array
	@param - IN Pronoun*
	@result - SyllablesArray*
*/
extern void BreakdownPronoun(TPronoun* T, SyllsArray* sylarr);

/* Combine Pronoun:
	combine syllables unto a Pronoun
	@param[in_arr] - IN - SyllablesArray to combine
	@result - new TPronoun*
*/
extern TPronoun* CombinePronoun(SyllsArray* sylarr);

/* Input Pronoun by parts:
	input Pronoun from console/file/binfile by parts
	@param[T] - OUT - Pronoun for return
	@param[istream] - input stream (stdout, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputPronounByParts(TPronoun* T, FILE* istream);

/* Output Pronoun by parts:
	write Pronoun to console/file/binfile by parts
	@param[T] - TPronoun
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputPronounByParts(TPronoun* T, FILE* ostream);

/* Set Pronoun properties:
	Set Pronoun properties like type, gender, quantity and sort
	@param[T] - OUT - TPronoun*
	@param[type] - const wchar_t* string
	@param[gender] - const wchar_t* string
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void SetPronounProps(TPronoun* w, wchar_t type[], wchar_t gender[], wchar_t quantity[], wchar_t sort[]);

/* Change Pronoun properties:
	Change Pronoun properties like quantity and sort
	@param[T] - OUT - TPronoun*
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void ChangePronounProps(TPronoun* T, wchar_t quantity[], wchar_t sort[]);









/* Base structure of TAdverb */


// Declaration of TAdverb private fields
typedef struct _TAdverbPrivate {
	unsigned char uch;
} TAdverbPrivate;

// Declaration of pointer to TAdverb structure
typedef struct _TAdverb {
	TWord parent;
	TAdverbPrivate* private;
} TAdverb;


// Declaration of TAdverb constructor
extern void TAdverb_Constructor(TAdverb* T);

// Declaration of TAdverb destructor
extern void TAdverb_Destructor(TAdverb* T);

/* Function of creating a new TAdverb object:
	create new Adverb
	@result - TAdverb*
*/
extern TAdverb* TAdverb_New(void);

/* Function of deleting a TAdverb object:
	delete Adverb
	@param[T] - Adverb to delete
*/
extern void TAdverb_Delete(TAdverb* T);

/* Input Adverb:
	input Adverb from console/file/binfile
	@param[T] - OUT - Adverb for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputAdverb(TAdverb* T, FILE* istream);

/* Output Adverb:
	write Adverb to console/file/binfile
	@param[T] - IN Adverb*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/

extern void OutputAdverb(TAdverb* T, FILE* ostream);

/* Input Adverb text field:
	input Adverb  text field from console/file/binfile
	@param[T] - OUT - Adverb for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputAdverbText(TAdverb* T, FILE* istream);

/* Output Adverb text field:
	write Adverb text field to console/file/binfile
	@param[T] - IN Adverb*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputAdverbText(TAdverb* T, FILE* ostream);

/* Get text from TAdverb field
	@param[T] - TAdverb*
	@param[text] - OUT - wchar_t* text
*/
extern void GetAdverbText(TWord* w, wchar_t* text[]);

/* Set text to TAdverb field:
	@param[T] - TAdverb*
	@param[text] - wchar_t
	@result - void
*/
extern void SetAdverbText(TAdverb* T, wchar_t* text[]);

/* Breakdown Adverb:
	break the Adverb into syllables and put them in array
	@param - IN Adverb*
	@result - SyllablesArray*
*/
extern void BreakdownAdverb(TAdverb* T, SyllsArray* sylarr);

/* Combine Adverb:
	combine syllables unto a Adverb
	@param[in_arr] - IN - SyllablesArray to combine
	@result - new TAdverb*
*/
extern TAdverb* CombineAdverb(SyllsArray* sylarr);

/* Input Adverb by parts:
	input Adverb from console/file/binfile by parts
	@param[T] - OUT - Adverb for return
	@param[istream] - input stream (stdout, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputAdverbByParts(TAdverb* T, FILE* istream);

/* Output Adverb by parts:
	write Adverb to console/file/binfile by parts
	@param[T] - TAdverb
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputAdverbByParts(TAdverb* T, FILE* ostream);

/* Set Adverb properties:
	Set Adverb properties like type, gender, quantity and sort
	@param[T] - OUT - TAdverb*
	@param[type] - const wchar_t* string
	@param[gender] - const wchar_t* string
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void SetAdverbProps(TAdverb* w, wchar_t type[], wchar_t gender[], wchar_t quantity[], wchar_t sort[]);

/* Change Adverb properties:
	Change Adverb properties like quantity and sort
	@param[T] - OUT - TAdverb*
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void ChangeAdverbProps(TAdverb* T, wchar_t quantity[], wchar_t sort[]);









/* Base structure of TVerb */


// Declaration of TVerb private fields
typedef struct _TVerbPrivate {
	unsigned char uch;
} TVerbPrivate;

// Declaration of pointer to TVerb structure
typedef struct _TVerb {
	TWord parent;
	TVerbPrivate* private;
} TVerb;


// Declaration of TVerb constructor
extern void TVerb_Constructor(TVerb* T);

// Declaration of TVerb destructor
extern void TVerb_Destructor(TVerb* T);

/* Function of creating a new TVerb object:
	create new verb
	@result - TVerb*
*/
extern TVerb* TVerb_New(void);

/* Function of deleting a TVerb object:
	delete verb
	@param[T] - verb to delete
*/
extern void TVerb_Delete(TVerb* T);

/* Input verb:
	input verb from console/file/binfile
	@param[T] - OUT - verb for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputVerb(TVerb* T, FILE* istream);

/* Output verb:
	write verb to console/file/binfile
	@param[T] - IN verb*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/

extern void OutputVerb(TVerb* T, FILE* ostream);

/* Input verb text field:
	input verb  text field from console/file/binfile
	@param[T] - OUT - verb for return
	@param[istream] - input stream (stdin, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputVerbText(TVerb* T, FILE* istream);

/* Output verb text field:
	write verb text field to console/file/binfile
	@param[T] - IN verb*
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputVerbText(TVerb* T, FILE* ostream);

/* Get text from TVerb field
	@param[T] - TVerb*
	@param[text] - OUT - wchar_t* text
*/
extern void GetVerbText(TWord* w, wchar_t* text[]);

/* Set text to TVerb field:
	@param[T] - TVerb*
	@param[text] - wchar_t
	@result - void
*/
extern void SetVerbText(TVerb* T, wchar_t* text[]);

/* Breakdown verb:
	break the verb into syllables and put them in array
	@param - IN verb*
	@result - SyllablesArray*
*/
extern void BreakdownVerb(TVerb* T, SyllsArray* sylarr);

/* Combine verb:
	combine syllables unto a verb
	@param[in_arr] - IN - SyllablesArray to combine
	@result - new TVerb*
*/
extern TVerb* CombineVerb(SyllsArray* sylarr);

/* Input verb by parts:
	input verb from console/file/binfile by parts
	@param[T] - OUT - verb for return
	@param[istream] - input stream (stdout, FILE*)
	
	@result - int :
	0 - in the case of success,
	error_code - number of error
*/
extern int InputVerbByParts(TVerb* T, FILE* istream);

/* Output verb by parts:
	write verb to console/file/binfile by parts
	@param[T] - TVerb
	@param[ostream] - output stream (stdout, FILE*)
	
	@result - void
*/
extern void OutputVerbByParts(TVerb* T, FILE* ostream);

/* Set verb properties:
	Set verb properties like type, gender, quantity and sort
	@param[T] - OUT - TVerb*
	@param[type] - const wchar_t* string
	@param[gender] - const wchar_t* string
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void SetVerbProps(TVerb* w, wchar_t type[], wchar_t gender[], wchar_t quantity[], wchar_t sort[]);

/* Change verb properties:
	Change verb properties like quantity and sort
	@param[T] - OUT - TVerb*
	@param[quantity] - const wchar_t* string
	@param[sort] - const wchar_t* string
	@result - void
*/
extern void ChangeVerbProps(TVerb* T, wchar_t quantity[], wchar_t sort[]);
