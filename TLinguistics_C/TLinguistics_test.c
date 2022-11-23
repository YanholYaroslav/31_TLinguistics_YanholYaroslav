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
#include <io.h>
#include <fcntl.h>



void main(void) {

	/* Make wchar_t understand Unicode for ukrainian localization */

	fflush(stdout);
	_setmode(_fileno(stdout), _O_U16TEXT);
	fflush(stdin);
	_setmode(_fileno(stdin), _O_U16TEXT);


	int input_mode = -1;
	fwprintf(stdout, L"File TLinguistics_test.c is running.");
	fwprintf(stdout, L"\n\n");
	fwprintf(stdout, L"Available input modes for testing:");
	while (1)
	{
		input_mode = -1;
		fwprintf(stdout, L"\n(1) -- console");
		fwprintf(stdout, L"\n(2) -- TLinguistics_test.txt file");
		fwprintf(stdout, L"\n(3) -- TLinguistics_test.dat file");
		fwprintf(stdout, L"\n(0) -- terminate run");
		fwprintf(stdout, L"\nChoice: ");
		fwscanf(stdin, L"%d", &input_mode);
		if (input_mode == 0)
		{
			fwprintf(stdout, L"\n\n");
			fwprintf(stdout, L"Run terminated");
			exit(0);
		}
		else if (input_mode == 1)
		{
			FILE* inp_stream = stdin;
			FILE* fout_t = fopen("Test_Txt_Output.txt", "w, ccs=UTF-8");
			FILE* fout_b = fopen("Test_Bin_Output.dat", "wb, ccs=UTF-8");
			fwprintf(stdout, L"\n\n");

			/* Test 1 – Create, Input, Output, Delete TWord object */
			TWord* word1 = TWord_New();
			fwprintf(stdout, L"Enter a word in the following format (separate by space):");
			fwprintf(stdout, L"\n\n");
			fwprintf(stdout, L"text(any ukrainian word) type gender quantity person sort");
			fwprintf(stdout, L"\n\n");
			InputWord(word1, inp_stream, "txt");

			fwprintf(stdout, L"\nFull word output:\n");
			OutputWord(word1, stdout, "txt");

			fwprintf(fout_t, L"\nFull word output:\n");
			OutputWord(word1, fout_t, "txt");
			fwprintf(fout_t, L"\n");

			OutputWord(word1, fout_b, "bin");

			TWord_Delete(word1);

			/* Test 2 - Get, Set, Input, Output TWord text field */
			TWord* word2_1 = TWord_New();
			TWord* word2_2 = TWord_New();

			fwprintf(stdout, L"\nEnter a single ukrainian word:\n");
			InputWordText(word2_1, inp_stream, "txt");

			wchar_t* w2_1_text = GetWordText(word2_1);
			SetWordText(word2_2, w2_1_text);

			fwprintf(stdout, L"\nWord text field output:\n");
			OutputWordText(word2_1, stdout, "txt");
			fwprintf(stdout, L"\nSecond word text field output (set(get()) from first word):\n");
			OutputWordText(word2_1, stdout, "txt");

			fwprintf(fout_t, L"\nWord text field output:\n");
			OutputWordText(word2_1, fout_t, "txt");
			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"\nSecond word text field output:\n");
			OutputWordText(word2_2, fout_t, "txt");
			fwprintf(fout_t, L"\n");

			OutputWordText(word2_1, fout_b, "bin");
			OutputWordText(word2_2, fout_b, "bin");

			TWord_Delete(word2_1);
			TWord_Delete(word2_2);

			/* Test 3 - Create, Input, Output, Delete SyllsArray and CombineWord */
			SyllsArray* sylls3 = SyllsArray_New();
			fwprintf(stdout, L"\n\n");
			InputSyllsArray(sylls3, inp_stream, "txt");

			fwprintf(stdout, L"\n");
			OutputSyllsArray(sylls3, stdout, "txt");

			fwprintf(fout_t, L"\nSyllsArray\n");
			OutputSyllsArray(sylls3, fout_t, "txt");
			fwprintf(fout_t, L"\n");

			OutputSyllsArray(sylls3, fout_b, "bin");

			TWord* word3_1 = CombineWord(sylls3);
			fwprintf(stdout, L"\nCombineWord result:\n");
			OutputWordText(word3_1, stdout, "txt");

			fwprintf(fout_t, L"\nCombineWord result:\n");
			OutputWordText(word3_1, fout_t, "txt");
			fwprintf(fout_t, L"\n");

			OutputWordText(word3_1, fout_b, "bin");

			TWord_Delete(word3_1);
			SyllsArray_Delete(sylls3);

			/* Test 4 - BreakDownWord function */
			TWord* word4_1 = TWord_New();
			SyllsArray* sylls4 = SyllsArray_New();

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nEnter a single ukrainian word for breakdown test:\n");
			InputWordText(word4_1, inp_stream, "txt");

			BreakdownWord(word4_1, sylls4);

			fwprintf(stdout, L"\nresult:\n");
			OutputSyllsArray(sylls4, stdout, "txt");

			fwprintf(fout_t, L"\nBreakdown result:\n");
			OutputSyllsArray(sylls4, fout_t, "txt");
			fwprintf(fout_t, L"\n");

			OutputSyllsArray(sylls4, fout_b, "bin");

			TWord_Delete(word4_1);
			SyllsArray_Delete(sylls4);

			/* Test 5 - SetWordProps and ChangeWordProps functions */
			TWord* word5_1 = TWord_New();

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nEnter a single ukrainian word:\n");
			InputWordText(word5_1, inp_stream, "txt");

			fwprintf(stdout, L"\nEnter properties to set (type, gender, quantity, sort) sep by space:\n");
			wchar_t* type, gender, quantity, sort;
			fwscanf(inp_stream, L"%s", &type);
			fwscanf(inp_stream, L"%s", &gender);
			fwscanf(inp_stream, L"%s", &quantity);
			fwscanf(inp_stream, L"%s", &sort);

			fwprintf(stdout, L"\nFull word output after setting properties:\n");
			OutputWord(word5_1, stdout, "txt");

			fwprintf(fout_t, L"\nFull word output after setting properties\n");
			OutputWord(word5_1, fout_t, "txt");
			fwprintf(fout_t, L"\n");

			OutputWord(word5_1, fout_b, "bin");

			fwprintf(stdout, L"\nEnter properties to change (quantity, sort) sep by space:\n");
			fwscanf(inp_stream, L"%s", &quantity);
			fwscanf(inp_stream, L"%s", &sort);

			fwprintf(stdout, L"\nFull word output after changing properties:\n");
			OutputWord(word5_1, stdout, "txt");

			fwprintf(fout_t, L"\nFull word output after changing properties:\n");
			OutputWord(word5_1, fout_t, "txt");
			fwprintf(fout_t, L"\n");

			OutputWord(word5_1, fout_b, "bin");

			TWord_Delete(word5_1);

			/* Test 6 - InputWordByParts and OutputWordByParts functions */
			TWord* word6_1 = TWord_New();

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nEnter a single ukrainian word by parts:\n");
			InputWordByParts(word6_1, inp_stream, "txt");

			fwprintf(stdout, L"\nWord output after by parts input:\n");
			OutputWordText(word6_1, stdout, "txt");
			fwprintf(stdout, L"\nThe same word output by parts:\n");
			OutputWordByParts(word6_1, stdout, "txt");

			fwprintf(fout_t, L"\nWord output after by parts input:\n");
			OutputWordText(word6_1, fout_t, "txt");
			fwprintf(fout_t, L"\nThe same word output by parts:\n");
			OutputWordByParts(word6_1, fout_t, "txt");

			OutputWordByParts(word6_1, fout_b, "bin");

			TWord_Delete(word6_1);


			/* Test for TWord heir */

			/* Close FILE* streams */
			fclose(fout_t);
			fclose(fout_b);
			fwprintf(fout_t, L"\n\nCheck results in files \"Test_Txt_Output.txt\" and \"Test_Bin_Output.dat\"\n");
		}
		else if (input_mode == 2)
		{
			fwprintf(stdout, L"\n\n");

		}
		else if (input_mode == 3)
		{
			fwprintf(stdout, L"\n\n");

		}
		else
		{
			fwprintf(stdout, L"\n\nWrong choice! Try again:");
		}
	}

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