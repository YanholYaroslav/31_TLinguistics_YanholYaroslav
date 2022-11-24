# 31_TLinguistics

С/C++ project: 31_Tlinguistic

Realization of TWord and its heirs (TNoun, TVerb, TAdjective, TNumeral, TPronoun, tAdverb) structures/classes,
	    input and ouput methods, breaking in syllables and work with parts and fields of TWord functions.




C part \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

Taking into account the fact that there is no possibility to implement a class in c,
structure TWord and its heirs structures are used as analogues.


!!!Attention!!!

The module is designed to work with Ukrainian text.
For compatibility with third-party wchar_t type objects you need connect the appropriate file conversion mode _O_U16TEXT (Unicode) for reading/writing wide-character strings from/to the stream.
Unicode is for advanced reading/printing functions (like wprintf) only. All functions and methods in this module are initialized based on such functions.
The author recommends using this piece of code at the beginning of your main.c file:

	fflush(stdout);
	_setmode(_fileno(stdout), _O_U16TEXT);
	fflush(stdin);
	_setmode(_fileno(stdin), _O_U16TEXT);

and adding "ccs=UTF-16LE" to file opening mode parametres for FILE* streams.

//////////////////////////////////////////////////////////////////////////



CPP part \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

(not done yet)

//////////////////////////////////////////////////////////////////////////
