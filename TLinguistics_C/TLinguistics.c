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

	and adding "ccs=UTF-16LE" or "ccs=UTF-8" to file opening mode parametre.



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
		fwprintf(stdout, L"Введіть кількість слогів для введення (n <= 20): ");
		int r_s = fwscanf(istream, L"%d", &n);
		if (n > sylarr->private->n) {
			fwprintf(stdout, L"\nВведено занадто велике число (n > 20)!");
			_setmode(_fileno(istream), istream_mode);
			_setmode(_fileno(stdout), ostream_mode);
			return -1;
		}
		sylarr->private->n = n;

		fwprintf(stdout, L"Введіть слоги, розділяючи пропуском:\n");
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
	else if (istream == "bin") {

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

		fwprintf(ostream, L"%d слогів: ", sylarr->private->n);
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
	wmemcpy(word->private->text, L"", wcslen(L""));
	word->private->text[wcslen(L"")] = (void*)0;
	wmemcpy(word->private->type, L"*не_визначено*", wcslen(L"*не_визначено*"));
	word->private->type[wcslen(L"*не_визначено*")] = (void*)0;
	wmemcpy(word->private->gender, L"*не_визначено*", wcslen(L"*не_визначено*"));
	word->private->gender[wcslen(L"*не_визначено*")] = (void*)0;
	wmemcpy(word->private->quantity, L"*не_визначено*", wcslen(L"*не_визначено*"));
	word->private->quantity[wcslen(L"*не_визначено*")] = (void*)0;
	wmemcpy(word->private->person, L"*не_визначено*", wcslen(L"*не_визначено*"));
	word->private->person[wcslen(L"*не_визначено*")] = (void*)0;
	wmemcpy(word->private->sort, L"*не_визначено*", wcslen(L"*не_визначено*"));
	word->private->sort[wcslen(L"*не_визначено*")] = (void*)0;
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
		fwprintf(ostream, L" роду ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->person[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->person[i]);
		}
		fwprintf(ostream, L"-ої особи ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->quantity[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->quantity[i]);
		}
		fwprintf(ostream, L", ");
		for (int i = 0; i < TWordPropFieldLen; i++) {
			if (w->private->sort[i] == (void*)0) break;
			fwprintf(ostream, L"%lc", w->private->sort[i]);
		}
		fwprintf(ostream, L" відмінок.");

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
	else if (istream == "bin") {

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
	w->private->text[wcslen(text) + 1] = (void*)0;
}


/* Breakdown word */
void BreakdownWord(TWord* w, SyllsArray* w_syl) {

	wchar_t louds[21] = L"АЕЄИІЇОУЮЯаеєиіїоуюя";

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

			//wprintf(L"\nGlobal: %d", i);

			if (i + 3 > wcslen(w->private->text))
			{
				fwprintf(stdout, L"\nIt is the last syl!\n");
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
				//fwprintf(stdout, L"\nThere can be two syls!\n");
				if (louds_c <= 1)
				{
					//fwprintf(stdout, L"\nIt is the last syl!\n");
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
			// remove comms

			else if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_inwcs(w->private->text[i + 1], louds) == 1 && iswchar_inwcs(w->private->text[i + 2], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = (void*)0;
				i++;
				i++;
				s = 0;

				fwprintf(stdout, L"1?");
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_inwcs(w->private->text[i + 1], louds) == 1 && iswchar_inwcs(w->private->text[i + 2], L"й") == 1 && iswchar_inwcs(w->private->text[i + 3], L"о") == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = (void*)0;
				i++;
				i++;
				s = 0;

				fwprintf(stdout, L"2?");
			}
			
			else if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_inwcs(w->private->text[i + 1], louds) == 1 && iswchar_inwcs(w->private->text[i + 2], L"й") == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = w->private->text[i + 2];
				w_syl->private->sylls[k][s + 3] = (void*)0;
				i++;
				i++;
				i++;
				s = 0;

				fwprintf(stdout, L"3?");
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 0 && iswchar_inwcs(w->private->text[i + 1], L"ь") == 1 && iswchar_inwcs(w->private->text[i + 2], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = w->private->text[i + 2];
				w_syl->private->sylls[k][s + 3] = (void*)0;
				i++;
				i++;
				i++;
				s = 0;

				fwprintf(stdout, L"4?");
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 1 && iswchar_inwcs(w->private->text[i + 1], louds) == 0 && iswchar_inwcs(w->private->text[i + 2], L"'") == 1 && iswchar_inwcs(w->private->text[i + 3], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = w->private->text[i + 2];
				w_syl->private->sylls[k][s + 3] = (void*)0;
				i++;
				i++;
				i++;
				s = 0;

				fwprintf(stdout, L"5?");
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 1 && iswchar_inwcs(w->private->text[i + 1], louds) == 0 && iswchar_inwcs(w->private->text[i + 2], louds) == 0 && iswchar_inwcs(w->private->text[i + 2], L"ь") == 0 && iswchar_inwcs(w->private->text[i + 3], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = (void*)0;
				i++;
				i++;
				s = 0;

				fwprintf(stdout, L"6?");
			}

			else if (iswchar_inwcs(w->private->text[i], louds) == 1 && iswchar_inwcs(w->private->text[i + 1], louds) == 0 && iswchar_inwcs(w->private->text[i + 2], L"ь") == 1 && iswchar_inwcs(w->private->text[i + 3], louds) == 0 && iswchar_inwcs(w->private->text[i + 4], louds) == 1)
			{
				w_syl->private->sylls[k][s] = w->private->text[i];
				w_syl->private->sylls[k][s + 1] = w->private->text[i + 1];
				w_syl->private->sylls[k][s + 2] = w->private->text[i + 2];
				w_syl->private->sylls[k][s + 3] = (void*)0;
				i++;
				i++;
				i++;
				s = 0;

				fwprintf(stdout, L"7?");
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
	return 0;
}

/* Output word by parts */
void OutputWordByParts(TWord* w, FILE* ostream, const char* f_type) {

}

/* Set word properties */
extern void SetWordProps(TWord* w) {

}

/* Change word properties */
extern void ChangeWordProps(TWord* w) {

}

/* Transfer word */
/*
void TransferWord(TWord* w) {
	SyllsArray* sylls = SyllsArray_New();
	BreakdownWord(w, sylls);

	OutputSyllsArray(sylls, stdout, "txt");

	wmemcpy(w->private->text, sylls->private->sylls[0], wcslen(sylls->private->sylls[0]));
	w->private->text[wcslen(w->private->text) + 1] = L"-";
	w->private->text[wcslen(w->private->text) + 2] = L"\n";
	w->private->text[wcslen(w->private->text) + 3] = (void*)0;
	int t = wcslen(w->private->text) + 1;

	OutputWord(w, stdout, "txt");

	for (int i = 1; i < sylls->private->n; i++) {
		for (int j = 0; j < SyllsLen; j++) {
			if (sylls->private->sylls[i][j] == (void*)0) break;
			w->private->text[t] = sylls->private->sylls[i][j];
			t++;
		}
	}
	w->private->text[t] = (void*)0;
	//w->private->text[wcslen(w->private->text) + 1] = (void*)0;
}
*/
