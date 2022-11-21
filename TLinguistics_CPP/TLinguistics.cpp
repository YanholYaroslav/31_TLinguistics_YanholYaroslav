/*  File TLinguistics.c


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

	and adding "ccs=UTF-16LE" or "ccs=UTF-8" to file opening mode parametres for FILE* streams.



 *	Done by Yanhol Yaroslav (group: Computer mechanics 2)
	Date __.__.____

 *	Implementations of TWord structure and its heirs
*/



/* Headers */

#define _CRT_SECURE_NO_WARNINGS

#include "TLinguistics.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>



/* Helper functions */

/* Is there a wchar_t character in the wchar_t string */
int iswchar_inwcs(wchar_t c, wchar_t str[]) {
	for (int i = 0; i < wcslen(str); i++)
	{
		if (c == str[i]) return 1;
	}
	return 0;
}

/* Is wchar_t character is equal to the other wchar_t character */
int iswchar_eq(wchar_t c1, wchar_t c2) {
	return c1 == c2 ? 1 : 0;
}

/* Functions for the SyllsArray */

/* SyllsArray constructor */
void SyllsArray_Constructor(SyllsArray* sylarr) {
	sylarr->private = malloc(sizeof(SyllsArrayPrivate));
	sylarr->private->n = SyllsAmount;
	for (int i = 0; i < SyllsAmount; i++) {
		wmemset(sylarr->private->sylls[i], (void*)0, 1);
	}
}

/* SyllsArray destructor */
void SyllsArray_Destructor(SyllsArray* sylarr) {
	free(sylarr->private);
}

/* Function of creating a new SyllsArray object */
SyllsArray* SyllsArray_New(void) {
	SyllsArray* sylarr = malloc(sizeof(SyllsArrayPrivate));
	SyllsArray_Constructor(sylarr);
	return sylarr;
}

/* Function of deleting a SyllsArray object */
void SyllsArray_Delete(SyllsArray* sylarr) {
	SyllsArray_Destructor(sylarr);
	free(sylarr);
}

/* Input SyllsArray: 

*/
int InputSyllsArray(SyllsArray* sylarr, FILE* istream, const char* f_type) {

	fflush(istream);
	int istream_mode = _setmode(_fileno(istream), _O_U16TEXT);

	if (istream == stdin) {

		fflush(stdout);
		int ostream_mode = _setmode(_fileno(stdout), _O_U16TEXT);

		int n;
		fwprintf(stdout, L"Input the number of syllables (n <= 20): ");
		int r_s = fwscanf(istream, L"%d", &n);
		if (n > sylarr->private->n) {
			fwprintf(stdout, L"\nn is too big (n > 20)!");
			_setmode(_fileno(istream), istream_mode);
			_setmode(_fileno(stdout), ostream_mode);
			return -1;
		}
		sylarr->private->n = n;

		fwprintf(stdout, L"Input syllables separated by space:\n");
		for (int i = 0; i < sylarr->private->n; i++) {
			int r_s = fwscanf(istream, L"%s", sylarr->private->sylls[i]);
			if (!r_s) {
				_setmode(_fileno(istream), istream_mode);
				_setmode(_fileno(stdout), ostream_mode);
				return r_s;
			}
			else {
				sylarr->private->sylls[i][wcslen(sylarr->private->sylls[i]) + 1] = (void*)0;
				_setmode(_fileno(istream), istream_mode);
				_setmode(_fileno(stdout), ostream_mode);
			}
		}

		return 0;

	}
	else if (f_type == "txt") {

		int n;
		int r_s = fwscanf(istream, L"%d", &n);
		if (n > sylarr->private->n) {
			_setmode(_fileno(istream), istream_mode);
			return -1;
		}
		sylarr->private->n = n;

		for (int i = 0; i < sylarr->private->n; i++) {
			int r_s = fwscanf(istream, L"%s", sylarr->private->sylls[i]);
			if (!r_s) {
				_setmode(_fileno(istream), istream_mode);
				return r_s;
			}
			else {
				sylarr->private->sylls[i][wcslen(sylarr->private->sylls[i]) + 1] = (void*)0;
				_setmode(_fileno(istream), istream_mode);
			}
		}

		return 0;

	}
	else if (f_type == "bin") {

		int size = ftell(istream);
		int n = size / sizeof(SyllsArray);
		fread(sylarr, sizeof(SyllsArray), n, istream);

		_setmode(_fileno(istream), istream_mode);

		return 0;

	}
	else return -2;
	
}

/* Output SyllsArray */
void OutputSyllsArray(SyllsArray* sylarr, FILE* ostream, const char* f_type) {

	fflush(ostream);
	int ostream_mode = _setmode(_fileno(ostream), _O_U16TEXT);

	if (ostream == stdout) {

		fwprintf(ostream, L"%d syllables: ", sylarr->private->n);
		for (int i = 0; i < sylarr->private->n; i++) {
			for (int j = 0; j < SyllsLen; j++) {
				if (sylarr->private->sylls[i][j] == (void*)0) break;
				fwprintf(ostream, L"%lc", sylarr->private->sylls[i][j]);
			}
			fwprintf(ostream, L" ");
		}

	}
	else if (f_type == "txt") {

		fwprintf(ostream, L"%d ", sylarr->private->n);
		for (int i = 0; i < sylarr->private->n; i++) {
			for (int j = 0; j < SyllsLen; j++) {
				if (sylarr->private->sylls[i][j] == (void*)0) break;
				fwprintf(ostream, L"%lc", sylarr->private->sylls[i][j]);
			}
			fwprintf(ostream, L" ");
		}

	}
	else if (f_type == "bin") {

	int size = ftell(ostream);
	int n = size / sizeof(SyllsArray);
	fwrite(sylarr, sizeof(SyllsArray), n, ostream);

	}

	_setmode(_fileno(ostream), ostream_mode);

}



/* Functions for the TWord */

/* TWord constructor */
void TWord_Constructor(TWord* word) {

	word->private = malloc(sizeof(TWordPrivate));
	//wchar_t undl = L"_";
	wmemcpy(word->private->text, L"_", wcslen(L"_"));
	word->private->text[wcslen(L"_")] = (void*)0;
	wmemcpy(word->private->type, L"_", wcslen(L"_"));
	word->private->type[wcslen(L"_")] = (void*)0;
	wmemcpy(word->private->gender, L"_", wcslen(L"_"));
	word->private->gender[wcslen(L"_")] = (void*)0;
	wmemcpy(word->private->quantity, L"_", wcslen(L"_"));
	word->private->quantity[wcslen(L"_")] = (void*)0;
	wmemcpy(word->private->person, L"0", wcslen(L"0"));
	word->private->person[wcslen(L"_")] = (void*)0;
	wmemcpy(word->private->sort, L"_", wcslen(L"_"));
	word->private->sort[wcslen(L"_")] = (void*)0;

	for (int i = 0; i < 3; i++) {
		wmemcpy(word->private->prefix[i], L"", wcslen(L""));
		word->private->prefix[i][wcslen(L"")] = (void*)0;
	}
	wmemcpy(word->private->radix[0], L"_", wcslen(L"_"));
	word->private->radix[0][wcslen(L"_")] = (void*)0;
	for (int i = 1; i < 2; i++) {
		wmemcpy(word->private->radix[i], L"", wcslen(L""));
		word->private->radix[i][wcslen(L"")] = (void*)0;
	}
	for (int i = 0; i < 3; i++) {
		wmemcpy(word->private->suffix[i], L"", wcslen(L""));
		word->private->suffix[i][wcslen(L"")] = (void*)0;
	}
	wmemcpy(word->private->ending[0], L"", wcslen(L""));
	word->private->ending[0][wcslen(L"")] = (void*)0;

}

/* TWord destructor */
void TWord_Destructor(TWord* word) {
	free(word->private);
}

/* Function of creating a new TWord object */
TWord* TWord_New(void) {
	TWord* word = malloc(sizeof(TWordPrivate));
	TWord_Constructor(word);
	return word;
}

/* Function of deleting a TWord object */
void TWord_Delete(TWord* word) {
	TWord_Destructor(word);
	free(word);
}


/* Input word:
	The word is entered in the following format (separate by space):

	text type gender quantity person sort

	lower case allowed:

	text = any ukrainian word
	type = {"Іменник", "Дієслово", "Прикметник", "Числівник", "Займенник", "Прислівник"} or {"Ім.", "Дієсл.", "Прикм.", "Числ., "Займ.", "Присл."}
	gender = {"_", "чоловічий", "жіночий", "середній", "спільний"} or {"_", "чол.", "жін.", "сер.", "спн."}
	quantity = {"_", "однина", "множина"} or {"_", "од.", "мн."}
	person = {"_", 0, 1, 2, 3}
	sort = {"_", "Називний", "Родовий", "Давальний", "Знахідний", "Орудний", "Місцевий", "Кличний"} or {"_", "Наз.", "Род.", "Дав.", "Зн.", "Оруд.", "Місц.", "Кл."}

	( 0 and "_" for infinitive or special type of word )
*/
int InputWord(TWord* w, FILE* istream, const char* f_type) {

	fflush(istream);
	int istream_mode = _setmode(_fileno(istream), _O_U16TEXT);

	if (istream == stdin) {

		int r_s;
		r_s = fwscanf(istream, L"%s", &w->private->text);
		if (!r_s) return r_s;
		w->private->text[wcslen(w->private->text)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->type);
		if (!r_s) return r_s;
		w->private->type[wcslen(w->private->type)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->gender);
		if (!r_s) return r_s;
		w->private->gender[wcslen(w->private->gender)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->quantity);
		if (!r_s) return r_s;
		w->private->quantity[wcslen(w->private->quantity)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->person);
		if (!r_s) return r_s;
		w->private->person[wcslen(w->private->person)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->sort);
		if (!r_s) return r_s;
		w->private->sort[wcslen(w->private->sort)] = (void*)0;

		_setmode(_fileno(istream), istream_mode);

		return 0;

	}
	else if (f_type == "txt") {

		int r_s;
		r_s = fwscanf(istream, L"%s", &w->private->text);
		if (!r_s) return r_s;
		w->private->text[wcslen(w->private->text)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->type);
		if (!r_s) return r_s;
		w->private->type[wcslen(w->private->type)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->gender);
		if (!r_s) return r_s;
		w->private->gender[wcslen(w->private->gender)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->quantity);
		if (!r_s) return r_s;
		w->private->quantity[wcslen(w->private->quantity)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->person);
		if (!r_s) return r_s;
		w->private->person[wcslen(w->private->person)] = (void*)0;
		r_s = fwscanf(istream, L"%s", &w->private->sort);
		if (!r_s) return r_s;
		w->private->sort[wcslen(w->private->sort)] = (void*)0;

		_setmode(_fileno(istream), istream_mode);

		return 0;

	}
	else if (istream == "bin") {

		int size = ftell(istream);
		int n = size / sizeof(TWord);
		fread(w, sizeof(TWord), n, istream);

		_setmode(_fileno(istream), istream_mode);

		return 0;

	}
	else return -2;
}

/* Output word */
void OutputWord(TWord* w, FILE* ostream, const char* f_type) {

	fflush(ostream);
	int ostream_mode = _setmode(_fileno(ostream), _O_U16TEXT);

	if (ostream == stdout) {
		


		for (int i = 0; i < TWordLen; i++) {
			if (w->private->text[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->text[i]);
		}
		fwprintf(ostream, L": ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->type[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->type[i]);
		}
		fwprintf(ostream, L" ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->gender[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->gender[i]);
		}
		fwprintf(ostream, L" gender ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->person[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->person[i]);
		}
		fwprintf(ostream, L"-th person ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->quantity[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->quantity[i]);
		}
		fwprintf(ostream, L", ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->sort[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->sort[i]);
		}
		fwprintf(ostream, L" sort.");

	}
	else if (f_type == "txt") {

		for (int i = 0; i < TWordLen; i++) {
			if (w->private->text[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->text[i]);
		}
		fwprintf(ostream, L" ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->type[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->type[i]);
		}
		fwprintf(ostream, L" ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->gender[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->gender[i]);
		}
		fwprintf(ostream, L" ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->person[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->person[i]);
		}
		fwprintf(ostream, L" ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->quantity[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->quantity[i]);
		}
		fwprintf(ostream, L" ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->sort[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->sort[i]);
		}

	}
	else if (f_type == "bin") {

		int size = ftell(ostream);
		int n = size / sizeof(TWord);
		fwrite(w, sizeof(TWord), n, ostream);
		
	}

	_setmode(_fileno(ostream), ostream_mode);

}

/* Input word text field:
	input word text field from console/file/binfile
	@param[w] - OUT – Word for return
	@param[istream] - input stream (stdin, FILE*)
	@param[f_type] - char string to tell the type of file ("txt" or "bin")
	@result – int :
	0 - in the case of success,
	error_code – number of error
*/
int InputWordText(TWord* w, FILE* istream, const char* f_type) {

	fflush(istream);
	int istream_mode = _setmode(_fileno(istream), _O_U16TEXT);

	if (istream == stdin) {

		int r_s;
		r_s = fwscanf(istream, L"%s", &w->private->text);
		if (!r_s) return r_s;
		w->private->text[wcslen(w->private->text)] = (void*)0;

		_setmode(_fileno(istream), istream_mode);

		return 0;

	}
	else if (f_type == "txt") {

		int r_s;
		r_s = fwscanf(istream, L"%s", &w->private->text);
		if (!r_s) return r_s;
		w->private->text[wcslen(w->private->text)] = (void*)0;

		_setmode(_fileno(istream), istream_mode);

		return 0;

	}
	else if (f_type == "bin") {

		int size = ftell(istream);
		int n = size / sizeof(w->private->text);
		fread(w, sizeof(w->private->text), n, istream);

		_setmode(_fileno(istream), istream_mode);

		return 0;

	}
	else return -2;
}

/* Output word text field:
	write word text field to console/file/binfile
	@param[w] - IN word*
	@param[ostream] - output stream (stdout, FILE*)
	@param[f_type] - char string to tell the type of file ("txt" or "bin")
	@result - void
*/
void OutputWordText(TWord* w, FILE* ostream, const char* f_type) {

	fflush(ostream);
	int ostream_mode = _setmode(_fileno(ostream), _O_U16TEXT);

	if (ostream == stdout) {

		for (int i = 0; i < TWordLen; i++) {
			if (w->private->text[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->text[i]);
		}

	}
	else if (f_type == "txt") {

		for (int i = 0; i < TWordLen; i++) {
			if (w->private->text[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->text[i]);
		}

	}
	else if (f_type == "bin") {

		int size = ftell(ostream);
		int n = size / sizeof(w->private->text);
		fwrite(w, sizeof(w->private->text), n, ostream);

	}

	_setmode(_fileno(ostream), ostream_mode);

}

/* Get text from TWord field */
wchar_t GetWordText(TWord* w) {
	return w->private->text;
}

/* Set text to TWord field */
void SetWordText(TWord* w, wchar_t text) {
	wmemcpy(w->private->text, text, wcslen(text));
	w->private->text[wcslen(text)] = (void*)0;
}


/* Breakdown word */
void BreakdownWord(TWord* w, SyllsArray* w_syl) {

	//wchar_t louds[21] = L"АЕЄИІЇОУЮЯаеєиіїоуюя";
	wchar_t louds[21];
	FILE* f = fopen("louds.dat", "rb");
	fgetws(louds, 21, f);
	fclose(f);

	// breakdown word rules characters
	wchar_t bdwr_ch[5];
	f = fopen("BDWR_chars.dat", "rb");
	fgetws(bdwr_ch, 5, f);
	fclose(f);

	int louds_c = 0;
	for (int i = 0; i < wcslen(w->private->text); i++)
	{
		if (iswchar_inwcs(w->private->text[i], louds)) louds_c++;
	}
	w_syl->private->n = louds_c;
	
	if (louds_c == 1) wcscpy(w_syl->private->sylls[0], w->private->text);
	else
	{
		int i = 0;
		int k = 0;
		int s = 0;
		while (i < wcslen(w->private->text)) {

			if (i + 3 > wcslen(w->private->text))
			{
				while (w->private->text[i] != (void*)0)
				{
					w_syl->private->sylls[k][s] = w->private->text[i];
					i++;
					s++;
				}
				w_syl->private->sylls[k][s] = (void*)0;
				break;
			}

			else if (i + 4 > wcslen(w->private->text))
			{	
				if (louds_c <= 1)
				{
					while (w->private->text[i] != (void*)0)
					{
						w_syl->private->sylls[k][s] = w->private->text[i];
						i++;
						s++;
					}
				}
				else
				{
					if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_inwcs(w->private->text[i + 1], louds) == 1 && iswchar_inwcs(w->private->text[i + 2], louds) == 1)
					{
						while (w->private->text[i] != (void*)0)
						{
							w_syl->private->sylls[k][s] = w->private->text[i];
							i++;
							s++;
						}
					}
					else if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_inwcs(w->private->text[i + 1], louds) == 1 && iswchar_inwcs(w->private->text[i + 2], louds) == 0)
					{
						while (w->private->text[i] != (void*)0)
						{
							w_syl->private->sylls[k][s] = w->private->text[i];
							i++;
							s++;
						}
					}
					else
					{
						w_syl->private->sylls[k][s] = w->private->text[i];
						w_syl->private->sylls[k][s + 1] = (void*)0;
						i++;
						s = 0;
						w_syl->private->sylls[k + 1][s] = w->private->text[i];
						w_syl->private->sylls[k + 1][s + 1] = w->private->text[i + 1];
						w_syl->private->sylls[k + 1][s + 2] = (void*)0;
						break;
					}
				}
				w_syl->private->sylls[k][s] = (void*)0;
				break;
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_inwcs(w->private->text[i + 1], louds) == 1 && iswchar_inwcs(w->private->text[i + 2], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = (void*)0;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_inwcs(w->private->text[i + 1], louds) == 1 && iswchar_eq(w->private->text[i + 2], bdwr_ch[0]) == 1 && iswchar_eq(w->private->text[i + 3], bdwr_ch[1]) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = (void*)0;
				i++;
				i++;
				s = 0;
			}
			
			else if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_inwcs(w->private->text[i + 1], louds) == 1 && iswchar_eq(w->private->text[i + 2], bdwr_ch[0]) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = w->private->text[i + 2];
				w_syl->private->sylls[k][s + 3] = (void*)0;
				i++;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_eq(w->private->text[i + 1], bdwr_ch[2]) == 1 && iswchar_inwcs(w->private->text[i + 2], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = w->private->text[i + 2];
				w_syl->private->sylls[k][s + 3] = (void*)0;
				i++;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 1 && iswchar_inwcs(w->private->text[i + 1], louds) == 0 && iswchar_eq(w->private->text[i + 2], bdwr_ch[3]) == 1 && iswchar_inwcs(w->private->text[i + 3], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = w->private->text[i + 2];
				w_syl->private->sylls[k][s + 3] = (void*)0;
				i++;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 1 && iswchar_inwcs(w->private->text[i + 1], louds) == 0 && iswchar_inwcs(w->private->text[i + 2], louds) == 0 && iswchar_eq(w->private->text[i + 2], bdwr_ch[2]) == 0 && iswchar_inwcs(w->private->text[i + 3], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = (void*)0;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 1 && iswchar_inwcs(w->private->text[i + 1], louds) == 0 && iswchar_eq(w->private->text[i + 2], bdwr_ch[2]) == 1 && iswchar_inwcs(w->private->text[i + 3], louds) == 0 && iswchar_inwcs(w->private->text[i + 4], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = w->private->text[i + 2];
				w_syl->private->sylls[k][s + 3] = (void*)0;
				i++;
				i++;
				i++;
				s = 0;
			}

			// + rule for "дз/дж" ?

			else if (iswchar_inwcs(w->private->text[i], louds) == 1 && w_syl->private->sylls[k][s] != (void*)0 && louds_c != 0)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = (void*)0;
				i++;
				s = 0;
			}

			else
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				i++;
				s++;
				k--;
				louds_c++;
			}

			k++;
			louds_c--;

		}
	}

}

/* Combine word */
TWord* CombineWord(SyllsArray* sylarr) {
	TWord* w = TWord_New();
	int t = 0;
	for (int i = 0; i < sylarr->private->n; i++) {
		for (int j = 0; j < SyllsLen; j++) {
			if (sylarr->private->sylls[i][j] == (void*)0) break;
			w->private->text[t] = sylarr->private->sylls[i][j];
			t++;
		}
	}
	w->private->text[t] = (void*)0;
	return w;
}

/* Input word by parts */
int InputWordByParts(TWord* w, FILE* istream, const char* f_type) {

	fflush(istream);
	int istream_mode = _setmode(_fileno(istream), _O_U16TEXT);
	
	if (istream == stdin) {

		fflush(stdout);
		int ostream_mode = _setmode(_fileno(stdout), _O_U16TEXT);

		int n;
		int r_s;

		fwprintf(stdout, L"Put in amount of prefixes (0 <= n <= 3): ");
		r_s = fwscanf(istream, L"%d", &n);
		if (!r_s) return r_s;
		if( (n < 0) || (n > 3) ) {
			fwprintf(stdout, L"\nWrong amount %d: ", n);
			return -1;
		}
		if (n != 0) {
			fwprintf(stdout, L"\nPut in prefixes sep by space:\n");
		}
		for (int i = 0; i < n; i++) {
			r_s = fwscanf(istream, L"%s", &w->private->prefix[i]);
			if (!r_s) return r_s;
			w->private->prefix[i][wcslen(w->private->prefix[i])] = (void*)0;
		}

		fwprintf(stdout, L"\n");

		fwprintf(stdout, L"Put in amount of radixes (1 <= n <= 2): ");
		r_s = fwscanf(istream, L"%d", &n);
		if (!r_s) return r_s;
		if ((n < 1) || (n > 2)) {
			fwprintf(stdout, L"\nWrong amount %d: ", n);
			return -1;
		}
		fwprintf(stdout, L"\nPut in radixes sep by space:\n");
		for (int i = 0; i < n; i++) {
			r_s = fwscanf(istream, L"%s", &w->private->radix[i]);
			if (!r_s) return r_s;
			w->private->radix[i][wcslen(w->private->radix[i])] = (void*)0;
		}

		fwprintf(stdout, L"\n");

		fwprintf(stdout, L"Put in amount of suffixes (0 <= n <= 3): ");
		r_s = fwscanf(istream, L"%d", &n);
		if (!r_s) return r_s;
		if ((n < 0) || (n > 3)) {
			fwprintf(stdout, L"\nWrong amount %d: ", n);
			return -1;
		}
		if (n != 0) {
			fwprintf(stdout, L"\nPut in suffixes sep by space:\n");
		}
		for (int i = 0; i < n; i++) {
			r_s = fwscanf(istream, L"%s", &w->private->suffix[i]);
			if (!r_s) return r_s;
			w->private->suffix[i][wcslen(w->private->suffix[i])] = (void*)0;
		}

		fwprintf(stdout, L"\n");

		fwprintf(stdout, L"Put in amount of endings (0 <= n <= 1): ");
		r_s = fwscanf(istream, L"%d", &n);
		if (!r_s) return r_s;
		if ((n < 0) || (n > 1)) {
			fwprintf(stdout, L"\nWrong amount %d: ", n);
			return -1;
		}
		fwprintf(stdout, L"\nPut in ending:\n");
		r_s = fwscanf(istream, L"%s", &w->private->ending[0]);
		if (!r_s) return r_s;
		w->private->ending[0][wcslen(w->private->ending[0])] = (void*)0;

		fwprintf(stdout, L"\n");

		_setmode(_fileno(istream), istream_mode);
		_setmode(_fileno(stdout), ostream_mode);

		return 0;

	}
	else if (f_type == "txt") {

		int n;
		int r_s;

		r_s = fwscanf(istream, L"%d", &n);
		if (!r_s) return r_s;
		if ((n < 0) || (n > 3)) {
			return -1;
		}
		for (int i = 0; i < n; i++) {
			r_s = fwscanf(istream, L"%s", &w->private->prefix[i]);
			if (!r_s) return r_s;
			w->private->prefix[i][wcslen(w->private->prefix[i])] = (void*)0;
		}

		r_s = fwscanf(istream, L"%d", &n);
		if (!r_s) return r_s;
		if ((n < 1) || (n > 2)) {
			return -1;
		}
		for (int i = 0; i < n; i++) {
			r_s = fwscanf(istream, L"%s", &w->private->radix[i]);
			if (!r_s) return r_s;
			w->private->radix[i][wcslen(w->private->radix[i])] = (void*)0;
		}

		r_s = fwscanf(istream, L"%d", &n);
		if (!r_s) return r_s;
		if ((n < 0) || (n > 3)) {
			return -1;
		}
		for (int i = 0; i < n; i++) {
			r_s = fwscanf(istream, L"%s", &w->private->suffix[i]);
			if (!r_s) return r_s;
			w->private->suffix[i][wcslen(w->private->suffix[i])] = (void*)0;
		}

		r_s = fwscanf(istream, L"%d", &n);
		if (!r_s) return r_s;
		if ((n < 0) || (n > 1)) {
			return -1;
		}
		if (n != 0) {
			r_s = fwscanf(istream, L"%s", &w->private->ending[0]);
			if (!r_s) return r_s;
			w->private->ending[0][wcslen(w->private->ending[0])] = (void*)0;
		}

		_setmode(_fileno(istream), istream_mode);

		return 0;

	}
	else if (f_type == "bin") {

		int m, size, n;

		/*
		size = ftell(istream);
		n = size / sizeof(int);
		fread(m, sizeof(int), n, istream);
		*/
		size = ftell(istream);
		n = size / sizeof(w->private->prefix);
		fread(w, sizeof(w->private->prefix), n, istream);

		size = ftell(istream);
		n = size / sizeof(w->private->radix);
		fread(w, sizeof(w->private->radix), n, istream);

		size = ftell(istream);
		n = size / sizeof(w->private->suffix);
		fread(w, sizeof(w->private->suffix), n, istream);

		size = ftell(istream);
		n = size / sizeof(w->private->ending);
		fread(w, sizeof(w->private->ending), n, istream);

		_setmode(_fileno(istream), istream_mode);

		return 0;

	}
	else return -2;

}

/* Output word by parts */
void OutputWordByParts(TWord* w, FILE* ostream, const char* f_type) {

	fflush(ostream);
	int ostream_mode = _setmode(_fileno(ostream), _O_U16TEXT);
	
	if (ostream == stdout) {

		int n = 0;

		n = 0;
		while (n != 3) {
			if (w->private->prefix[n][0] != (void*)0) n++;
		}
		fwprintf(ostream, L"%d prefixes: ", n);
		n = 0;
		while (n != 3) {
			if (w->private->prefix[n][0] != (void*)0) {
				n++;
				fwprintf(ostream, L"%s ", w->private->prefix[n]);
			}
		}

		n = 0;
		while (n != 2) {
			if (w->private->radix[n][0] != (void*)0) n++;
		}
		fwprintf(ostream, L"%d radixes: ", n);
		n = 0;
		while (n != 2) {
			if (w->private->radix[n][0] != (void*)0) {
				n++;
				fwprintf(ostream, L"%s ", w->private->radix[n]);
			}
		}

		n = 0;
		while (n != 3) {
			if (w->private->suffix[n][0] != (void*)0) n++;
		}
		fwprintf(ostream, L"%d suffixes: ", n);
		n = 0;
		while (n != 3) {
			if (w->private->suffix[n][0] != (void*)0) {
				n++;
				fwprintf(ostream, L"%s ", w->private->suffix[n]);
			}
		}

		n = 0;
		if (w->private->ending[n][0] == (void*)0) {
			fwprintf(ostream, L"%d ending ", n);
		}
		else {
			fwprintf(ostream, L"%d ending: ", n);
			fwprintf(ostream, L"%s ", w->private->ending[n]);
		}


	}
	else if (f_type == "txt") {

		int n = 0;

		n = 0;
		while (n != 3) {
			if (w->private->prefix[n][0] != (void*)0) n++;
		}
		fwprintf(ostream, L"%d ", n);
		n = 0;
		while (n != 3) {
			if (w->private->prefix[n][0] != (void*)0) {
				n++;
				fwprintf(ostream, L"%s ", w->private->prefix[n]);
			}
		}

		n = 0;
		while (n != 2) {
			if (w->private->radix[n][0] != (void*)0) n++;
		}
		fwprintf(ostream, L"%d ", n);
		n = 0;
		while (n != 2) {
			if (w->private->radix[n][0] != (void*)0) {
				n++;
				fwprintf(ostream, L"%s ", w->private->radix[n]);
			}
		}

		n = 0;
		while (n != 3) {
			if (w->private->suffix[n][0] != (void*)0) n++;
		}
		fwprintf(ostream, L"%d ", n);
		n = 0;
		while (n != 3) {
			if (w->private->suffix[n][0] != (void*)0) {
				n++;
				fwprintf(ostream, L"%s ", w->private->suffix[n]);
			}
		}

		n = 0;
		if (w->private->ending[n][0] == (void*)0) {
			fwprintf(ostream, L"%d ", n);
		}
		else {
			fwprintf(ostream, L"%d ", n);
			fwprintf(ostream, L"%s ", w->private->ending[n]);
		}

	}
	else if (f_type == "bin") {
		
	int m, size, n;

	/*
	size = ftell(istream);
	n = size / sizeof(int);
	fread(m, sizeof(int), n, istream);
	*/
	size = ftell(ostream);
	n = size / sizeof(w->private->prefix);
	fwrite(w, sizeof(w->private->prefix), n, ostream);

	size = ftell(ostream);
	n = size / sizeof(w->private->radix);
	fwrite(w, sizeof(w->private->radix), n, ostream);

	size = ftell(ostream);
	n = size / sizeof(w->private->suffix);
	fwrite(w, sizeof(w->private->suffix), n, ostream);

	size = ftell(ostream);
	n = size / sizeof(w->private->ending);
	fwrite(w, sizeof(w->private->ending), n, ostream);

	}

	_setmode(_fileno(ostream), ostream_mode);

}

/* Set word properties */
void SetWordProps(TWord* w, const wchar_t* type, const wchar_t* gender, const wchar_t* quantity, const wchar_t* sort) {
	wmemcpy(w->private->type, type, wcslen(type));
	wmemcpy(w->private->gender, gender, wcslen(gender));
	wmemcpy(w->private->quantity, quantity, wcslen(quantity));
	wmemcpy(w->private->sort, sort, wcslen(sort));
}

/* Change word properties */
void ChangeWordProps(TWord* w, const wchar_t* quantity, const wchar_t* sort) {
	wmemcpy(w->private->quantity, quantity, wcslen(quantity));
	wmemcpy(w->private->sort, sort, wcslen(sort));
}
