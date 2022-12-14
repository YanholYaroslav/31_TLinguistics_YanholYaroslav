/*  File TLinguistics.c


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

 *	Implementations of TWord class and its heirs
*/



/* Headers */

#define _CRT_SECURE_NO_WARNINGS

#include "TLinguistics.h"
#include <iostream>
#include <cwchar>

#include <io.h>
#include <fcntl.h>

#include <locale>
#include <codecvt>

using namespace std;



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





/* Functions for the SyllsArray methods */

/* Input SyllsArray */
int SyllsArray::input(wistream& inp) {

	wstreambuf const* cinbuf = wcin.rdbuf();
	wstreambuf const* streambuf = inp.rdbuf();

	if (streambuf == cinbuf) {

		fflush(stdin);
		int istream_mode = _setmode(_fileno(stdin), _O_U16TEXT);

		wcout << L"Input the number of syllables (n <= 20): ";
		int n_h = 0;
		inp >> n_h;
		if (n_h > SyllsAmount || n_h < 0) {
			wcout << L"\nn is too big (n > 20)!" << endl;
			_setmode(_fileno(stdin), istream_mode);
			return -1;
		}
		this->n = n_h;

		wcout << L"Input syllables separated by space:\n" ;
		for (int i = 0; i < this->n; i++) {
			inp >> this->sylls[i];
		}

		_setmode(_fileno(stdin), istream_mode);
		return 0;

	}

	else {

		locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
		inp.imbue(utf8_locale);

		int n_h = 0;
		inp >> n_h;
		if (n_h > SyllsAmount) {
			return -1;
		}
		this->n = n_h;

		for (int i = 0; i < this->n; i++) {
			inp >> this->sylls[i];
		}

		return 0;

	}

}

/* Output SyllsArray */
void SyllsArray::output(wostream& out) {
	
	wstreambuf const* coutbuf = wcout.rdbuf();
	wstreambuf const* cerrbuf = wcerr.rdbuf();
	wstreambuf const* streambuf = out.rdbuf();

	if (streambuf == coutbuf || streambuf == cerrbuf) {

		fflush(stdout);
		int ostream_mode = _setmode(_fileno(stdout), _O_U16TEXT);

		out << this->n << ": ";
		for (int i = 0; i < this->n; i++) {
			for (int j = 0; j < wcslen(this->sylls[i]); j++) {
				out << this->sylls[i][j];
			}
			out << L" ";
		}

		_setmode(_fileno(stdout), ostream_mode);

	}
	else {

		locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
		out.imbue(utf8_locale);

		out << this->n << " ";
		for (int i = 0; i < this->n; i++) {
			for (int j = 0; j < wcslen(this->sylls[i]); j++) {
				out << this->sylls[i][j];
			}
			out << L" ";
		}

	}

}

/* Friend operator<< */
wostream& operator<< (wostream& out, SyllsArray& arr) {
	arr.output(out);
	return out;
}





/* Functions for the TWord methods */

/* TWord init */
void TWord::init() {

	wcscpy(this->text, L"_");
	this->text[wcslen(L"_")] = NULL;
	wcscpy(this->type, L"_");
	this->type[wcslen(L"_")] = NULL;
	wcscpy(this->gender, L"_");
	this->gender[wcslen(L"_")] = NULL;
	wcscpy(this->quantity, L"_");
	this->quantity[wcslen(L"_")] = NULL;
	wcscpy(this->person, L"0");
	this->person[wcslen(L"0")] = NULL;
	wcscpy(this->sort, L"_");
	this->sort[wcslen(L"_")] = NULL;

	for (int i = 0; i < 3; i++) {
		for (int o = 0; o < wcslen(this->prefix[i]); o++) {
			this->prefix[i][o] = NULL;
		}
	}
	for (int o = 0; o < wcslen(this->radix[0]); o++) {
		this->radix[0][o] = NULL;
		this->radix[1][o] = NULL;
	}
	for (int i = 0; i < 3; i++) {
		for (int o = 0; o < wcslen(this->suffix[i]); o++) {
			this->suffix[i][0] = NULL;
		}
	}
	for (int o = 0; o < wcslen(this->ending[0]); o++) {
		this->ending[0][o] = NULL;
	}

}

/* TWord Constructor */
TWord::TWord() { void init(); }

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
int TWord::input(wistream& inp) {

	wstreambuf const* cinbuf = wcin.rdbuf();
	wstreambuf const* streambuf = inp.rdbuf();

	if (streambuf == cinbuf) {

		fflush(stdin);
		int istream_mode = _setmode(_fileno(stdin), _O_U16TEXT);

		inp >> this->text;
		inp >> this->type;
		inp >> this->gender;
		inp >> this->quantity;
		inp >> this->person;
		inp >> this->sort;

		_setmode(_fileno(stdin), istream_mode);

		return 0;

	}
	else {

		locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
		inp.imbue(utf8_locale);

		inp >> this->text;
		inp >> this->type;
		inp >> this->gender;
		inp >> this->quantity;
		inp >> this->person;
		inp >> this->sort;

		return 0;

	}

}

/* Output word */
void TWord::output(wostream& out) {

	wstreambuf const* coutbuf = wcout.rdbuf();
	wstreambuf const* cerrbuf = wcerr.rdbuf();
	wstreambuf const* streambuf = out.rdbuf();

	if (streambuf == coutbuf || streambuf == cerrbuf) {

		fflush(stdout);
		int ostream_mode = _setmode(_fileno(stdout), _O_U16TEXT);

		out << this->text;
		out << L": ";
		out << this->type;
		out << L" ";
		out << this->gender;
		out << L" gender ";
		out << this->person;
		out << L"-th person ";
		out << this->quantity;
		out << L", ";
		out << this->sort;
		out << L" sort.";

	}
	else {

		locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
		out.imbue(utf8_locale);

		out << this->text;
		out << L" ";
		out << this->type;
		out << L" ";
		out << this->gender;
		out << L" ";
		out << this->person;
		out << L" ";
		out << this->quantity;
		out << L" ";
		out << this->sort;

	}

}

/* Friend operator>> */
wistream& operator>> (wistream& inp, TWord& w) {
	w.input(inp);
	return inp;
}

/* Friend operator<< */
wostream& operator<< (wostream& out, TWord& w) {
	w.output(out);
	return out;
}

/* Input word text field */
int TWord::input_text(wistream& inp) {

	wstreambuf const* cinbuf = wcin.rdbuf();
	wstreambuf const* streambuf = inp.rdbuf();

	if (streambuf == cinbuf) {

		fflush(stdin);
		int istream_mode = _setmode(_fileno(stdin), _O_U16TEXT);

		inp >> this->text;
		this->text[wcslen(this->text)] = NULL;

		_setmode(_fileno(stdin), istream_mode);

		return 0;

	}
	else {

		locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
		inp.imbue(utf8_locale);

		inp >> this->text;
		this->text[wcslen(this->text)] = NULL;

		return 0;

	}

}

/* Output word text field */
void TWord::output_text(wostream& out) {

	wstreambuf const* coutbuf = wcout.rdbuf();
	wstreambuf const* cerrbuf = wcerr.rdbuf();
	wstreambuf const* streambuf = out.rdbuf();

	if (streambuf == coutbuf || streambuf == cerrbuf) {

		fflush(stdout);
		int ostream_mode = _setmode(_fileno(stdout), _O_U16TEXT);

		out << this->text;

	}
	else {

		locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
		out.imbue(utf8_locale);

		out << this->text;
	}

}

/* Get text from TWord field */
void TWord::get_text(wchar_t* text_out) {
	wmemcpy(text_out, this->text, wcslen(this->text));
}

/* Set text to TWord field */
void TWord::set_text(wchar_t* text_in) {
	wmemcpy(this->text, text_in, wcslen(text_in));
}

/* Breakdown word */
void TWord::breakdown(SyllsArray& sylarr) {

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
	for (int i = 0; i < wcslen(this->text); i++)
	{
		if (iswchar_inwcs(this->text[i], louds)) louds_c++;
	}
	sylarr.n = louds_c;

	if (louds_c == 1) wcscpy(sylarr.sylls[0], this->text);
	else
	{
		int i = 0;
		int k = 0;
		int s = 0;
		while (i < wcslen(this->text)) {

			if (i + 3 > wcslen(this->text))
			{
				while (this->text[i] != NULL)
				{
					sylarr.sylls[k][s] = this->text[i];
					i++;
					s++;
				}
				sylarr.sylls[k][s] = NULL;
				break;
			}

			else if (i + 4 > wcslen(this->text))
			{
				if (louds_c <= 1)
				{
					while (this->text[i] != NULL)
					{
						sylarr.sylls[k][s] = this->text[i];
						i++;
						s++;
					}
				}
				else
				{
					if (iswchar_inwcs(this->text[i], louds) == 0 && iswchar_inwcs(this->text[i + 1], louds) == 1 && iswchar_inwcs(this->text[i + 2], louds) == 1)
					{
						while (this->text[i] != NULL)
						{
							sylarr.sylls[k][s] = this->text[i];
							i++;
							s++;
						}
					}
					else if (iswchar_inwcs(this->text[i], louds) == 0 && iswchar_inwcs(this->text[i + 1], louds) == 1 && iswchar_inwcs(this->text[i + 2], louds) == 0)
					{
						while (this->text[i] != NULL)
						{
							sylarr.sylls[k][s] = this->text[i];
							i++;
							s++;
						}
					}
					else
					{
						sylarr.sylls[k][s] = this->text[i];
						sylarr.sylls[k][s + 1] = NULL;
						i++;
						s = 0;
						sylarr.sylls[k + 1][s] = this->text[i];
						sylarr.sylls[k + 1][s + 1] = this->text[i + 1];
						sylarr.sylls[k + 1][s + 2] = NULL;
						break;
					}
				}
				sylarr.sylls[k][s] = NULL;
				break;
			}

			else if (iswchar_inwcs(this->text[i], louds) == 0 && iswchar_inwcs(this->text[i + 1], louds) == 1 && iswchar_inwcs(this->text[i + 2], louds) == 1)
			{
				sylarr.sylls[k][s] = this->text[i];
				sylarr.sylls[k][s + 1] = this->text[i + 1];
				sylarr.sylls[k][s + 2] = NULL;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(this->text[i], louds) == 0 && iswchar_inwcs(this->text[i + 1], louds) == 1 && iswchar_eq(this->text[i + 2], bdwr_ch[0]) == 1 && iswchar_eq(this->text[i + 3], bdwr_ch[1]) == 1)
			{
				sylarr.sylls[k][s] = this->text[i];
				sylarr.sylls[k][s + 1] = this->text[i + 1];
				sylarr.sylls[k][s + 2] = NULL;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(this->text[i], louds) == 0 && iswchar_inwcs(this->text[i + 1], louds) == 1 && iswchar_eq(this->text[i + 2], bdwr_ch[0]) == 1)
			{
				sylarr.sylls[k][s] = this->text[i];
				sylarr.sylls[k][s + 1] = this->text[i + 1];
				sylarr.sylls[k][s + 2] = this->text[i + 2];
				sylarr.sylls[k][s + 3] = NULL;
				i++;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(this->text[i], louds) == 0 && iswchar_eq(this->text[i + 1], bdwr_ch[2]) == 1 && iswchar_inwcs(this->text[i + 2], louds) == 1)
			{
				sylarr.sylls[k][s] = this->text[i];
				sylarr.sylls[k][s + 1] = this->text[i + 1];
				sylarr.sylls[k][s + 2] = this->text[i + 2];
				sylarr.sylls[k][s + 3] = NULL;
				i++;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(this->text[i], louds) == 1 && iswchar_inwcs(this->text[i + 1], louds) == 0 && iswchar_eq(this->text[i + 2], bdwr_ch[3]) == 1 && iswchar_inwcs(this->text[i + 3], louds) == 1)
			{
				sylarr.sylls[k][s] = this->text[i];
				sylarr.sylls[k][s + 1] = this->text[i + 1];
				sylarr.sylls[k][s + 2] = this->text[i + 2];
				sylarr.sylls[k][s + 3] = NULL;
				i++;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(this->text[i], louds) == 1 && iswchar_inwcs(this->text[i + 1], louds) == 0 && iswchar_inwcs(this->text[i + 2], louds) == 0 && iswchar_eq(this->text[i + 2], bdwr_ch[2]) == 0 && iswchar_inwcs(this->text[i + 3], louds) == 1)
			{
				sylarr.sylls[k][s] = this->text[i];
				sylarr.sylls[k][s + 1] = this->text[i + 1];
				sylarr.sylls[k][s + 2] = NULL;
				i++;
				i++;
				s = 0;
			}

			else if (iswchar_inwcs(this->text[i], louds) == 1 && iswchar_inwcs(this->text[i + 1], louds) == 0 && iswchar_eq(this->text[i + 2], bdwr_ch[2]) == 1 && iswchar_inwcs(this->text[i + 3], louds) == 0 && iswchar_inwcs(this->text[i + 4], louds) == 1)
			{
				sylarr.sylls[k][s] = this->text[i];
				sylarr.sylls[k][s + 1] = this->text[i + 1];
				sylarr.sylls[k][s + 2] = this->text[i + 2];
				sylarr.sylls[k][s + 3] = NULL;
				i++;
				i++;
				i++;
				s = 0;
			}

			// + rule for "дз/дж" ?

			else if (iswchar_inwcs(this->text[i], louds) == 1 && sylarr.sylls[k][s] != NULL && louds_c != 0)
			{
				sylarr.sylls[k][s] = this->text[i];
				sylarr.sylls[k][s + 1] = NULL;
				i++;
				s = 0;
			}

			else
			{
				sylarr.sylls[k][s] = this->text[i];
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
void TWord::combine(SyllsArray sylarr) {
	int t = 0;
	for (int i = 0; i < sylarr.n; i++) {
		for (int j = 0; j < wcslen(sylarr.sylls[i]); j++) {
			if (sylarr.sylls[i][j] == NULL) break;
			this->text[t] = sylarr.sylls[i][j];
			t++;
		}
	}
	this->text[t] = NULL;
}

/* Input word by parts */
int TWord::input_by_parts(wistream& inp) {

	wstreambuf const* cinbuf = wcin.rdbuf();
	wstreambuf const* streambuf = inp.rdbuf();

	if (streambuf == cinbuf) {

		fflush(stdin);
		int istream_mode = _setmode(_fileno(stdin), _O_U16TEXT);

		int n;

		wcout << L"Put in amount of prefixes (0 <= n <= 3): ";
		inp >> n;
		if ((n < 0) || (n > 3)) {
			wcout << L"\nWrong amount: " << n;
			return -1;
		}
		if (n != 0) {
			wcout << L"\nPut in prefixes sep by space:\n";
		}
		for (int i = 0; i < n; i++) {
			inp >> this->prefix[i];
			this->prefix[i][wcslen(this->prefix[i])] = L'\0';
		}
		wcout << L"\n";

		wcout << L"Put in amount of radixes (1 <= n <= 2): ";
		inp >> n;
		if ((n < 1) || (n > 2)) {
			wcout << L"\nWrong amount: " << n;
			return -1;
		}
		wcout << L"\nPut in radixes sep by space:\n";
		for (int i = 0; i < n; i++) {
			inp >> this->radix[i];
			this->radix[i][wcslen(this->radix[i])] = L'\0';
		}
		wcout << L"\n";

		wcout << L"Put in amount of suffixes (0 <= n <= 3): ";
		inp >> n;
		if ((n < 0) || (n > 3)) {
			wcout << L"\nWrong amount: " << n;
			return -1;
		}
		if (n != 0) {
			wcout << L"\nPut in suffixes sep by space:\n";
		}
		for (int i = 0; i < n; i++) {
			inp >> this->suffix[i];
			this->suffix[i][wcslen(this->suffix[i])] = L'\0';
		}
		wcout << L"\n";

		wcout << L"Put in amount of endings (0 <= n <= 1): ";
		inp >> n;
		if ((n < 0) || (n > 1)) {
			wcout << L"\nWrong amount: " << n;
			return -1;
		}
		wcout << L"\nPut in ending:\n";
		inp >> this->ending[0];
		this->ending[0][wcslen(this->ending[0])] = L'\0';
		wcout << L"\n";

		_setmode(_fileno(stdin), istream_mode);

		return 0;

	}
	else {

		locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
		inp.imbue(utf8_locale);

		int n;

		inp >> n;
		if ((n < 0) || (n > 3)) {
			return -1;
		}
		for (int i = 0; i < n; i++) {
			inp >> this->prefix[i];
			this->prefix[i][wcslen(this->prefix[i])] = L'\0';
		}

		inp >> n;
		if ((n < 1) || (n > 2)) {
			return -1;
		}
		for (int i = 0; i < n; i++) {
			inp >> this->radix[i];
			this->radix[i][wcslen(this->radix[i])] = L'\0';
		}

		inp >> n;
		if ((n < 0) || (n > 3)) {
			return -1;
		}
		for (int i = 0; i < n; i++) {
			inp >> this->suffix[i];
			this->suffix[i][wcslen(this->suffix[i])] = L'\0';
		}

		inp >> n;
		if ((n < 0) || (n > 1)) {
			return -1;
		}
		if (n != 0) {
			inp >> this->ending[0];
			this->ending[0][wcslen(this->ending[0])] = L'\0';
		}

		return 0;

	}

}

/* Output word by parts */
void TWord::output_by_parts(wostream& out) {

	wstreambuf const* coutbuf = wcout.rdbuf();
	wstreambuf const* cerrbuf = wcerr.rdbuf();
	wstreambuf const* streambuf = out.rdbuf();

	if (streambuf == coutbuf || streambuf == cerrbuf) {

		fflush(stdout);
		int ostream_mode = _setmode(_fileno(stdout), _O_U16TEXT);

		int n = 0;

		n = 0;
		while (n != 3) {
			if (this->prefix[n][0] != L'\0') n++;
			else break;
		}
		out << n << L" prefixes: ";
		n = 0;
		while (n != 3) {
			if (this->prefix[n][0] != L'\0') {
				out << this->prefix[n] << L" ";
				n++;
			}
			else break;
		}

		n = 0;
		while (n != 2) {
			if (this->radix[n][0] != L'\0') n++;
			else break;
		}
		out << n << L" radixes: ";
		n = 0;
		while (n != 2) {
			if (this->radix[n][0] != L'\0') {
				out << this->radix[n] << L" ";
				n++;
			}
			else break;
		}

		n = 0;
		while (n != 3) {
			if (this->suffix[n][0] != L'\0') n++;
			else break;
		}
		out << n << L" suffixes: ";
		n = 0;
		while (n != 3) {
			if (this->suffix[n][0] != L'\0') {
				out << this->suffix[n] << L" ";
				n++;
			}
			else break;
		}

		n = 0;
		if (this->ending[n][0] == L'\0') {
			out << n << L" ending ";
		}
		else {
			out << n + 1 << L" ending: ";
			out << this->ending[n];
		}


	}
	else {

		locale utf8_locale(locale(), new codecvt_utf8<wchar_t>);
		out.imbue(utf8_locale);

		int n = 0;

		n = 0;
		while (n != 3) {
			if (this->prefix[n][0] != L'\0') n++;
			else break;
		}
		out << n << L" ";
		n = 0;
		while (n != 3) {
			if (this->prefix[n][0] != L'\0') {
				out << this->prefix[n] << L" ";
				n++;
			}
			else break;
		}

		n = 0;
		while (n != 2) {
			if (this->radix[n][0] != L'\0') n++;
			else break;
		}
		out << n << L" ";
		n = 0;
		while (n != 2) {
			if (this->radix[n][0] != L'\0') {
				out << this->radix[n] << L" ";
				n++;
			}
			else break;
		}

		n = 0;
		while (n != 3) {
			if (this->suffix[n][0] != L'\0') n++;
			else break;
		}
		out << n << L" ";
		n = 0;
		while (n != 3) {
			if (this->suffix[n][0] != L'\0') {
				out << this->suffix[n] << L" ";
				n++;
			}
			else break;
		}

		n = 0;
		if (this->ending[n][0] == L'\0') {
			out << n << L" ";
		}
		else {
			out << n + 1 << L" ";
			out << this->ending[n];
		}

	}

}

/* Set word properties */
void TWord::set_props(const wchar_t* type, const wchar_t* gender, const wchar_t* quantity, const wchar_t* sort) {
	wcscpy(this->type, type);
	this->type[wcslen(this->type)] = NULL;
	wcscpy(this->gender, gender);
	this->gender[wcslen(this->gender)] = NULL;
	wcscpy(this->quantity, quantity);
	this->quantity[wcslen(this->quantity)] = NULL;
	wcscpy(this->sort, sort);
	this->sort[wcslen(this->sort)] = NULL;
}

/* Change word properties */
void TWord::change_props(const wchar_t* quantity, const wchar_t* sort) {
	wcscpy(this->quantity, quantity);
	this->quantity[wcslen(this->quantity)] = NULL;
	wcscpy(this->sort, sort);
	this->sort[wcslen(this->sort)] = NULL;
}
