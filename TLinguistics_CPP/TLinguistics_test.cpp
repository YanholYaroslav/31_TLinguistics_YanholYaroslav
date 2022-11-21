/*  File TLinguistics_test.c

	Realization of tests for TWord structure (its heirs) and its functions

	Done by Yanhol Yaroslav (group: Computer mechanics 2)
	Date __.__.____

	Tests for TWord 
*/

/* Headers */

#define _CRT_SECURE_NO_WARNINGS

#include "TLinguistics.h"
#include <stdio.h>
#include <stdlib.h>



void main(void) {

	/* Make wchar_t understand Unicode for ukrainian localization */
	/*
	fflush(stdout);
	_setmode(_fileno(stdout), _O_U16TEXT);
	fflush(stdin);
	_setmode(_fileno(stdin), _O_U16TEXT);
	*/

	/* Test 1 – Create, Input, Output, Delete TWord object */


	
}




//FILE* f = fopen("Tlinguistics_test.dat", "wb");
//int mark_pos = ftell(f);
//int mark_pos = 0;
//fseek(f, 0, SEEK_END);
//int size = ftell(f);
//fseek(f, mark_pos, SEEK_SET);
//fclose(f);

/*
		//int mark_pos = ftell(f);
		int mark_pos = 0;
		fseek(f, 0, SEEK_END);
		int size = ftell(f);
		fseek(f, mark_pos, SEEK_SET);
		int n = size / sizeof(wchar_t);

		fread(w, sizeof(wchar_t), n, f);

		fclose(f);
		return 0;
		*/