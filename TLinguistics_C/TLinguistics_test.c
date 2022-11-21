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


	TWord* word1 = TWord_New();
	wchar_t* modec = L"c";
	fwprintf(stdout, L"Put in just word or its fields sep by space:\n");
	InputWord(word1, stdin, "txt");
	OutputWord(word1, stdout, "txt");

	SyllsArray* omg = SyllsArray_New();
	BreakdownWord(word1, omg);
	TWord* word2 = CombineWord(omg);

	

	//wprintf(L"\n\n");
	//OutputSyllsArray(omg, stdout, "txt");
	//wprintf(L"\n\n");
	//OutputWord(word2, stdout, "txt");

	
	FILE* f = fopen("TLinguistics_test.txt", "w, ccs=UTF-8");
	OutputWord(word2, f, "txt");
	fclose(f);

	FILE* f1 = fopen("TLinguistics_test.dat", "wb, ccs=UTF-8");
	OutputWord(word2, f1, "bin");
	fclose(f1);

	FILE* fw = fopen("TLinguistics_test.dat", "rb, ccs=UTF-8");
	InputWord(word2, f1, "bin");
	fclose(fw);


	wprintf(L"\n!!!\n");
	OutputWord(word2, stdout, "txt");
	
	
	//wprintf(L"Input sylls: \n");
	//InputSyllsArray(omg, L"c");
	OutputSyllsArray(omg, stdout, "txt");

	
	SyllsArray_Delete(omg);


	TWord_Delete(word1);
	TWord_Delete(word2);
	
	
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