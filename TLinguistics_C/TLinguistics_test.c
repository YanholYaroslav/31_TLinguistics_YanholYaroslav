/*  File TLinguistics_test.c

	Realization of tests for TWord structure (its heirs) and its functions

	Done by Yanhol Yaroslav (group: Computer mechanics)
	Date 20.12.2022

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

	/* Make i/o streams "understand Unicode" for ukrainian localization */
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
			FILE* fout_t = fopen("Test_Txt_Output.txt", "w, ccs=UTF-16LE");
			fwprintf(stdout, L"\n\n");

			/* Test 1 � Create, Input, Output, Delete TWord object */
			TWord* word1 = TWord_New();

			fwprintf(stdout, L"Test 1 � Create, Input, Output, Delete TWord object\n");
			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"Enter a word in the following format (separate by space):");
			fwprintf(stdout, L"\n\n");
			fwprintf(stdout, L"text(any ukrainian word) type gender quantity person sort");
			fwprintf(stdout, L"\n\n");
			InputWord(word1, inp_stream);

			fwprintf(stdout, L"\nFull word output:\n");
			OutputWord(word1, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"Test 1 � Create, Input, Output, Delete TWord object\n");
			fwprintf(fout_t, L"\nFull word output:\n");
			OutputWord(word1, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word1);

			/* Test 2 - Get, Set, Input, Output TWord text field */
			TWord* word2_1 = TWord_New();
			TWord* word2_2 = TWord_New();

			fwprintf(stdout, L"\nTest 2 - Get, Set, Input, Output TWord text field\n");
			fwprintf(stdout, L"\nEnter a single ukrainian word:\n");
			InputWordText(word2_1, inp_stream);

			wchar_t* w2_1_text[TWordLen];
			GetWordText(word2_2, w2_1_text);
			SetWordText(word2_2, w2_1_text);

			fwprintf(stdout, L"\nWord text field output:\n");
			OutputWordText(word2_1, stdout);
			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nSecond word text field output (set(get()) from first word):\n");
			OutputWordText(word2_1, stdout);
			fwprintf(stdout, L"\n");

			fwprintf(fout_t, L"\nTest 2 - Get, Set, Input, Output TWord text field\n");
			fwprintf(fout_t, L"\nWord text field output:\n");
			OutputWordText(word2_1, fout_t);
			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"\nSecond word text field output (set(get()) from first word):\n");
			OutputWordText(word2_2, fout_t);
			fwprintf(fout_t, L"\n");

			TWord_Delete(word2_1);
			TWord_Delete(word2_2);

			/* Test 3 - Create, Input, Output, Delete SyllsArray and CombineWord */
			SyllsArray* sylls3 = SyllsArray_New();
			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nTest 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions\n");
			InputSyllsArray(sylls3, inp_stream);

			fwprintf(stdout, L"\nSyllsArray:\n");
			OutputSyllsArray(sylls3, stdout);
			fwprintf(stdout, L"\n");

			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"\nTest 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions\n");
			fwprintf(fout_t, L"\nSyllsArray:\n");
			OutputSyllsArray(sylls3, fout_t);
			fwprintf(fout_t, L"\n");

			TWord* word3_1 = CombineWord(sylls3);

			fwprintf(stdout, L"\nCombineWord result:\n");
			OutputWordText(word3_1, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\nCombineWord result:\n");
			OutputWordText(word3_1, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word3_1);
			SyllsArray_Delete(sylls3);

			/* Test 4 - BreakDownWord function */
			TWord* word4_1 = TWord_New();
			SyllsArray* sylls4 = SyllsArray_New();

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"Test 4 - BreakDownWord function\n");
			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nEnter a single ukrainian word for breakdown test:\n");
			InputWordText(word4_1, inp_stream);

			BreakdownWord(word4_1, sylls4);

			fwprintf(stdout, L"\nBreakdown result:\n");
			OutputSyllsArray(sylls4, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"Test 4 - BreakDownWord function\n");
			fwprintf(fout_t, L"\nBreakdown result:\n");
			OutputSyllsArray(sylls4, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word4_1);
			SyllsArray_Delete(sylls4);

			/* Test 5 - SetWordProps and ChangeWordProps functions */
			TWord* word5_1 = TWord_New();

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"Test 5 - SetWordProps and ChangeWordProps functions\n");
			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nEnter a single ukrainian word:\n");
			InputWordText(word5_1, inp_stream);

			fwprintf(stdout, L"\nEnter properties to set (type, gender, quantity, sort) sep by space:\n");
			wchar_t* type[TWordLen], gender[TWordPropFieldLen], quantity[TWordPropFieldLen], sort[TWordPropFieldLen];
			fwscanf(inp_stream, L"%s", &type);
			fwscanf(inp_stream, L"%s", &gender);
			fwscanf(inp_stream, L"%s", &quantity);
			fwscanf(inp_stream, L"%s", &sort);

			SetWordProps(word5_1, type, gender, quantity, sort);

			fwprintf(stdout, L"\nFull word output after setting properties:\n");
			OutputWord(word5_1, stdout);
			fwprintf(stdout, L"\n");

			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"Test 5 - SetWordProps and ChangeWordProps functions\n");
			fwprintf(fout_t, L"\nFull word output after setting properties\n");
			OutputWord(word5_1, fout_t);
			fwprintf(fout_t, L"\n");

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nEnter the new text for ukrainian word:\n");
			InputWordText(word5_1, inp_stream);

			fwprintf(stdout, L"\nEnter properties to change (quantity, sort) sep by space:\n");
			fwscanf(inp_stream, L"%s", &quantity);
			fwscanf(inp_stream, L"%s", &sort);

			ChangeWordProps(word5_1, quantity, sort);

			fwprintf(stdout, L"\nFull word output after changing properties:\n");
			OutputWord(word5_1, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\nFull word output after changing properties:\n");
			OutputWord(word5_1, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word5_1);

			/* Test 6 - InputWordByParts and OutputWordByParts functions */
			TWord* word6_1 = TWord_New();

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"Test 6 - InputWordByParts and OutputWordByParts functions\n");
			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nEnter a single ukrainian word by parts:\n");
			InputWordByParts(word6_1, inp_stream);

			fwprintf(stdout, L"\nThe word output by parts:\n");
			OutputWordByParts(word6_1, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"Test 6 - InputWordByParts and OutputWordByParts functions\n");
			fwprintf(fout_t, L"\nThe word output by parts:\n");
			OutputWordByParts(word6_1, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word6_1);



			/* Close FILE* streams */
			fclose(inp_stream);
			fclose(fout_t);
			fwprintf(fout_t, L"\n\nCheck results in file \"Test_Txt_Output.txt\"\n");
		}
		else if (input_mode == 2)
		{
			FILE* inp_stream = fopen("TLinguistics_test.txt", "r, ccs=UTF-16LE");
			FILE* fout_t = fopen("Test_Txt_Output.txt", "w, ccs=UTF-16LE");
			fwprintf(stdout, L"\n\n");

			/* Test 1 � Create, Input, Output, Delete TWord object */
			TWord* word1 = TWord_New();
			InputWord(word1, inp_stream);

			fwprintf(stdout, L"Test 1 - Create, Input, Output, Delete TWord object\n");
			fwprintf(stdout, L"\nFull word output:\n");
			OutputWord(word1, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"Test 1 - Create, Input, Output, Delete TWord object\n");
			fwprintf(fout_t, L"\nFull word output:\n");
			OutputWord(word1, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word1);

			/* Test 2 - Get, Set, Input, Output TWord text field */
			TWord* word2_1 = TWord_New();
			TWord* word2_2 = TWord_New();

			InputWordText(word2_1, inp_stream);

			wchar_t* w2_1_text[TWordLen];
			GetWordText(word2_2, w2_1_text);
			SetWordText(word2_2, w2_1_text);

			fwprintf(stdout, L"\nTest 2 - Get, Set, Input, Output TWord text field\n");
			fwprintf(stdout, L"\nWord text field output:\n");
			OutputWordText(word2_1, stdout);
			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nSecond word text field output (set(get()) from first word):\n");
			OutputWordText(word2_1, stdout);
			fwprintf(stdout, L"\n");

			fwprintf(fout_t, L"\nTest 2 - Get, Set, Input, Output TWord text field\n");
			fwprintf(fout_t, L"\nWord text field output:\n");
			OutputWordText(word2_1, fout_t);
			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"\nSecond word text field output (set(get()) from first word):\n");
			OutputWordText(word2_2, fout_t);
			fwprintf(fout_t, L"\n");

			TWord_Delete(word2_1);
			TWord_Delete(word2_2);

			/* Test 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions */
			SyllsArray* sylls3 = SyllsArray_New();

			InputSyllsArray(sylls3, inp_stream);

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nTest 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions\n");
			fwprintf(stdout, L"\nSyllsArray:\n");
			OutputSyllsArray(sylls3, stdout);
			fwprintf(stdout, L"\n");

			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"\nTest 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions\n");
			fwprintf(fout_t, L"\nSyllsArray:\n");
			OutputSyllsArray(sylls3, fout_t);
			fwprintf(fout_t, L"\n");

			TWord* word3_1 = CombineWord(sylls3);

			fwprintf(stdout, L"\nCombineWord result:\n");
			OutputWordText(word3_1, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\nCombineWord result:\n");
			OutputWordText(word3_1, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word3_1);
			SyllsArray_Delete(sylls3);

			/* Test 4 - BreakDownWord function */
			TWord* word4_1 = TWord_New();
			SyllsArray* sylls4 = SyllsArray_New();

			
			InputWordText(word4_1, inp_stream);

			BreakdownWord(word4_1, sylls4);

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"Test 4 - BreakDownWord function\n");
			fwprintf(stdout, L"\nBreakdown result:\n");
			OutputSyllsArray(sylls4, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"Test 4 - BreakDownWord function\n");
			fwprintf(fout_t, L"\nBreakdown result:\n");
			OutputSyllsArray(sylls4, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word4_1);
			SyllsArray_Delete(sylls4);

			/* Test 5 - SetWordProps and ChangeWordProps functions */
			TWord* word5_1 = TWord_New();

			InputWordText(word5_1, inp_stream);

			wchar_t* type[TWordLen], gender[TWordPropFieldLen], quantity[TWordPropFieldLen], sort[TWordPropFieldLen];
			fwscanf(inp_stream, L"%s", &type);
			fwscanf(inp_stream, L"%s", &gender);
			fwscanf(inp_stream, L"%s", &quantity);
			fwscanf(inp_stream, L"%s", &sort);

			SetWordProps(word5_1, type, gender, quantity, sort);

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"Test 5 - SetWordProps and ChangeWordProps functions\n");
			fwprintf(stdout, L"\nFull word output after setting properties:\n");
			OutputWord(word5_1, stdout);
			fwprintf(stdout, L"\n");

			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"Test 5 - SetWordProps and ChangeWordProps functions\n");
			fwprintf(fout_t, L"\nFull word output after setting properties\n");
			OutputWord(word5_1, fout_t);
			fwprintf(fout_t, L"\n");

			InputWordText(word5_1, inp_stream);

			fwscanf(inp_stream, L"%s", &quantity);
			fwscanf(inp_stream, L"%s", &sort);

			ChangeWordProps(word5_1, quantity, sort);

			fwprintf(stdout, L"\nFull word output after changing properties:\n");
			OutputWord(word5_1, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\nFull word output after changing properties:\n");
			OutputWord(word5_1, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word5_1);

			/* Test 6 - InputWordByParts and OutputWordByParts functions */
			TWord* word6_1 = TWord_New();

			InputWordByParts(word6_1, inp_stream);

			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"Test 6 - InputWordByParts and OutputWordByParts functions\n");
			fwprintf(stdout, L"\nThe word output by parts:\n");
			OutputWordByParts(word6_1, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"Test 6 - InputWordByParts and OutputWordByParts functions\n");
			fwprintf(fout_t, L"\nThe word output by parts:\n");
			OutputWordByParts(word6_1, fout_t);
			fwprintf(fout_t, L"\n\n");

			TWord_Delete(word6_1);

			/* Test 8 - Full test for TWord heir (TNoun for example, heirs realizations are identical) */

			TNoun* noun8 = TNoun_New();
			SyllsArray* sylls8 = SyllsArray_New();

			InputNoun(noun8, inp_stream);
			BreakdownNoun(noun8, sylls8);

			fwprintf(stdout, L"\n\n\nTest 8 - Full test for TWord heir (TNoun for example, heirs realizations are identical)\n");
			fwprintf(stdout, L"\nFull noun output:\n");
			OutputNoun(noun8, stdout);
			fwprintf(stdout, L"\n\n");
			fwprintf(stdout, L"\Noun text field output:\n");
			OutputNounText(noun8, stdout);
			fwprintf(stdout, L"\n");
			fwprintf(stdout, L"\nBreakdown result:\n");
			OutputSyllsArray(sylls8, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\n\n\nTest 8 - Full test for TWord heir (TNoun for example, heirs realizations are identical)\n");
			fwprintf(fout_t, L"\nFull noun output:\n");
			OutputNoun(noun8, fout_t);
			fwprintf(fout_t, L"\n\n");
			fwprintf(fout_t, L"\Noun text field output:\n");
			OutputNounText(noun8, fout_t);
			fwprintf(fout_t, L"\n");
			fwprintf(fout_t, L"\nBreakdown result:\n");
			OutputSyllsArray(sylls8, fout_t);
			fwprintf(fout_t, L"\n\n");

			InputSyllsArray(sylls8, inp_stream);
			TNoun* noun8_2 = CombineNoun(sylls8);

			fwprintf(stdout, L"\nCombineNoun result:\n");
			OutputNounText(noun8_2, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\nCombineNoun result:\n");
			OutputNounText(noun8_2, fout_t);
			fwprintf(fout_t, L"\n\n");


			InputNounText(noun8_2, inp_stream);
			wchar_t* type8[TWordLen], gender8[TWordPropFieldLen], quantity8[TWordPropFieldLen], sort8[TWordPropFieldLen];
			fwscanf(inp_stream, L"%s", &type8);
			fwscanf(inp_stream, L"%s", &gender8);
			fwscanf(inp_stream, L"%s", &quantity8);
			fwscanf(inp_stream, L"%s", &sort8);

			SetNounProps(noun8_2, type8, gender8, quantity8, sort8);

			fwprintf(stdout, L"\nFull noun output after setting properties:\n");
			OutputNoun(noun8_2, stdout);
			fwprintf(stdout, L"\n");

			fwprintf(fout_t, L"\nFull noun output after setting properties\n");
			OutputNoun(noun8_2, fout_t);
			fwprintf(fout_t, L"\n");


			InputNounText(noun8_2, inp_stream);
			fwscanf(inp_stream, L"%s", &quantity8);
			fwscanf(inp_stream, L"%s", &sort8);

			ChangeNounProps(noun8_2, quantity8, sort8);

			fwprintf(stdout, L"\nFull noun output after changing properties:\n");
			OutputNoun(noun8_2, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\nFull noun output after changing properties:\n");
			OutputNoun(noun8_2, fout_t);
			fwprintf(fout_t, L"\n\n");


			InputNounByParts(noun8_2, inp_stream);

			fwprintf(stdout, L"\nThe noun output by parts:\n");
			OutputNounByParts(noun8_2, stdout);
			fwprintf(stdout, L"\n\n");

			fwprintf(fout_t, L"\nThe noun output by parts:\n");
			OutputNounByParts(noun8_2, fout_t);
			fwprintf(fout_t, L"\n\n");



			TNoun_Delete(noun8);
			TNoun_Delete(noun8_2);
			SyllsArray_Delete(sylls8);


			/* Close FILE* streams */
			fclose(inp_stream);
			fclose(fout_t);
			fwprintf(stdout, L"\n\nCheck results in file \"Test_Txt_Output.txt\"\n");
		}
		else
		{
			fwprintf(stdout, L"\n\nWrong choice! Try again:");
		}
	}

}
