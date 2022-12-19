/*  File TLinguistics_test.cpp

	Realization of tests for TWord class (its heirs) and its functions

	Done by Yanhol Yaroslav (group: Computer mechanics)
	Date 20.12.2022

	Tests for TWord 
*/

/* Headers */

#include "TLinguistics.h"
#include <iostream>
#include <fstream>

#include <io.h>
#include <fcntl.h>

#include <locale>
#include <codecvt>


void main(void) {		//lots of work

	fflush(stdin);
	int in_stream_mode = _setmode(_fileno(stdin), _O_U16TEXT);
	fflush(stdout);
	int out_stream_mode = _setmode(_fileno(stdout), _O_U16TEXT);

	int input_mode = -1;
	wcout << L"File TLinguistics_test.cpp is running.";
	wcout << L"\n\n";
	wcout << L"Available input modes for testing:";
	while (1)
	{
		input_mode = -1;
		wcout << L"\n(1) -- console";
		wcout << L"\n(2) -- TLinguistics_test.txt file";
		wcout << L"\n(0) -- terminate run";
		wcout << L"\nChoice: ";
		wcin >> input_mode;
		if (input_mode == 0)
		{
			wcout << L"\n\n";
			wcout << L"Run terminated";
			exit(0);
		}
		else if (input_mode == 1)
		{

			wfstream fout_t;
			fout_t.open("Test_Txt_Output.txt");

			wcout << L"\n\n";

			/* Test 1 - Create, Input, Output, Delete TWord object */
			TWord word1;
			
			wcout << L"Test 1 - Create, Input, Output, Delete TWord object\n";
			wcout << L"\n";
			wcout << L"Enter a word in the following format (separate by space):";
			wcout << L"\n\n";
			wcout << L"text(any ukrainian word) type gender quantity person sort";
			wcout << L"\n\n";
			wcin >> word1;

			wcout << L"\nFull word output:\n";
			wcout << word1;
			wcout << L"\n\n";

			fout_t << L"Test 1 - Create, Input, Output, Delete TWord object\n";
			fout_t << L"\nFull word output:\n";
			fout_t << word1;
			fout_t << L"\n\n";


			/* Test 2 - Get, Set, Input, Output TWord text field */
			TWord word2_1;
			TWord word2_2;

			wcout << L"\nTest 2 - Get, Set, Input, Output TWord text field\n";
			wcout << L"\nEnter a single ukrainian word:\n";
			word2_1.input_text();

			wchar_t w2_1_text[TWordLen];
			word2_1.get_text(w2_1_text);
			word2_2.set_text(w2_1_text);

			
			wcout << L"\nWord text field output:\n";
			word2_1.output_text();
			wcout << L"\n";
			wcout << L"\nSecond word text field output (set(get()) from first word):\n";
			word2_1.output_text();
			wcout << L"\n";

			fout_t << L"\nTest 2 - Get, Set, Input, Output TWord text field\n";
			fout_t << L"\nWord text field output:\n";
			word2_1.output_text(fout_t);
			fout_t << L"\n";
			fout_t << L"\nSecond word text field output (set(get()) from first word):\n";
			word2_1.output_text(fout_t);
			fout_t << L"\n";


			/* Test 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions */
			SyllsArray sylls3;

			wcout << L"\n";
			wcout << L"\nTest 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions\n";
			sylls3.input();

			wcout << L"\nSyllsArray:\n";
			wcout << sylls3;
			wcout << L"\n";

			fout_t << L"\n";
			fout_t << L"\nTest 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions\n";
			fout_t << L"\nSyllsArray:\n";
			fout_t << sylls3;
			fout_t << L"\n";


			TWord word3_1;

			word3_1.combine(sylls3);

			wcout << L"\nCombineWord result:\n";
			word3_1.output_text();
			wcout << L"\n\n";

			fout_t << L"\nCombineWord result:\n";
			word3_1.output_text(fout_t);
			fout_t << L"\n\n";


			/* Test 4 - BreakDownWord function */
			TWord word4_1;
			SyllsArray sylls4;

			wcout << L"\n";
			wcout << L"Test 4 - BreakDownWord function\n";
			wcout << L"\n";
			wcout << L"\nEnter a single ukrainian word for breakdown test:\n";
			word4_1.input_text();

			word4_1.breakdown(sylls4);

			wcout << L"\nBreakdown result:\n";
			wcout << sylls4;
			wcout << L"\n\n";

			fout_t << L"\n";
			fout_t << L"Test 4 - BreakDownWord function\n";
			fout_t << L"\nBreakdown result:\n";
			fout_t << sylls4;
			fout_t << L"\n\n";


			/* Test 5 - SetWordProps and ChangeWordProps functions */
			TWord word5_1{};

			wcout << L"\n";
			wcout << L"Test 5 - SetWordProps and ChangeWordProps functions\n";
			wcout << L"\n";
			wcout << L"\nEnter a single ukrainian word:\n";
			word5_1.input_text();

			wcout << L"\nEnter properties to set (type, gender, quantity, sort) sep by space:\n";
			wchar_t type[TWordLen], gender[TWordPropFieldLen], quantity[TWordPropFieldLen], sort[TWordPropFieldLen];
			wcin >> type;
			wcin >> gender;
			wcin >> quantity;
			wcin >> sort;

			word5_1.set_props(type, gender, quantity, sort);

			wcout << L"\nFull word output after setting properties:\n";
			wcout << word5_1;
			wcout << L"\n";

			fout_t << L"\n";
			fout_t << L"Test 5 - SetWordProps and ChangeWordProps functions\n";
			fout_t << L"\nFull word output after setting properties\n";
			fout_t << word5_1;
			fout_t << L"\n";

			wcout << L"\n";
			wcout << L"\nEnter the new text for ukrainian word:\n";
			word5_1.input_text();

			wcout << L"\nEnter properties to change (quantity, sort) sep by space:\n";
			wcin >> quantity;
			wcin >> sort;

			word5_1.change_props(quantity, sort);

			wcout << L"\nFull word output after changing properties:\n";
			wcout << word5_1;
			wcout << L"\n\n";

			fout_t << L"\nFull word output after changing properties:\n";
			fout_t << word5_1;
			fout_t << L"\n\n";


			/* Test 6 - InputWordByParts and OutputWordByParts functions */
			TWord word6_1{};

			wcout << L"\n";
			wcout << L"Test 6 - InputWordByParts and OutputWordByParts functions\n";
			wcout << L"\n";
			wcout << L"\nEnter a single ukrainian word by parts:\n";
			word6_1.input_by_parts();

			wcout << L"\nThe word output by parts:\n";
			word6_1.output_by_parts(wcout);
			wcout << L"\n\n";

			fout_t << L"\n";
			fout_t << L"Test 6 - InputWordByParts and OutputWordByParts functions\n";
			fout_t << L"\nThe word output by parts:\n";
			word6_1.output_by_parts(fout_t);
			fout_t << L"\n\n";


			/* Test 8 - TWord heirs (TNoun for example, realizations are identical) */

			/* Close fstreams */
			fout_t.close();
			fout_t << L"\n\nCheck results in file \"Test_Txt_Output.txt\"\n";



		}
		else if (input_mode == 2)
		{

			wifstream inp_stream;
			inp_stream.open("TLinguistics_test.txt");
			wfstream fout_t;
			fout_t.open("Test_Txt_Output.txt");

			//locale utf8_out_locale(locale(), new codecvt_utf8<wchar_t>);
			//fout_t.imbue(utf8_out_locale);

			wcout << L"\n\n";

			/* Test 1 - Create, Input, Output, Delete TWord object */
			TWord word1;
			word1.input(inp_stream);

			wcout << L"Test 1 - Create, Input, Output, Delete TWord object\n";
			wcout << L"\nFull word output:\n";
			wcout << word1;
			wcout << L"\n\n";

			fout_t << L"Test 1 - Create, Input, Output, Delete TWord object\n";
			fout_t << L"\nFull word output:\n";
			fout_t << word1;
			fout_t << L"\n\n";


			/* Test 2 - Get, Set, Input, Output TWord text field */
			TWord word2_1;
			TWord word2_2;

			word2_1.input_text(inp_stream);

			wchar_t w2_1_text[TWordLen];
			word2_1.get_text(w2_1_text);
			word2_2.set_text(w2_1_text);

			wcout << L"\nTest 2 - Get, Set, Input, Output TWord text field\n";
			wcout << L"\nWord text field output:\n";
			word2_1.output_text();
			wcout << L"\n";
			wcout << L"\nSecond word text field output (set(get()) from first word):\n";
			word2_1.output_text();
			wcout << L"\n";

			fout_t << L"\nTest 2 - Get, Set, Input, Output TWord text field\n";
			fout_t << L"\nWord text field output:\n";
			word2_1.output_text(fout_t);
			fout_t << L"\n";
			fout_t << L"\nSecond word text field output (set(get()) from first word):\n";
			word2_1.output_text(fout_t);
			fout_t << L"\n";


			/* Test 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions */
			SyllsArray sylls3;

			sylls3.input(inp_stream);

			wcout << L"\n";
			wcout << L"\nTest 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions\n";
			wcout << L"\nSyllsArray:\n";
			wcout << sylls3;
			wcout << L"\n";

			fout_t << L"\n";
			fout_t << L"\nTest 3 - Create, Input, Output, Delete SyllsArray and CombineWord functions\n";
			fout_t << L"\nSyllsArray:\n";
			fout_t << sylls3;
			fout_t << L"\n";


			TWord word3_1;

			word3_1.combine(sylls3);

			wcout << L"\nCombineWord result:\n";
			word3_1.output_text();
			wcout << L"\n\n";

			fout_t << L"\nCombineWord result:\n";
			word3_1.output_text(fout_t);
			fout_t << L"\n\n";


			/* Test 4 - BreakDownWord function */
			TWord word4_1;
			SyllsArray sylls4;


			word4_1.input_text(inp_stream);

			word4_1.breakdown(sylls4);

			wcout << L"\n";
			wcout << L"Test 4 - BreakDownWord function\n";
			wcout << L"\nBreakdown result:\n";
			wcout << sylls4;
			wcout << L"\n\n";

			fout_t << L"\n";
			fout_t << L"Test 4 - BreakDownWord function\n";
			fout_t << L"\nBreakdown result:\n";
			fout_t << sylls4;
			fout_t << L"\n\n";


			/* Test 5 - SetWordProps and ChangeWordProps functions */
			TWord word5_1;

			word5_1.input_text(inp_stream);

			wchar_t type[TWordLen], gender[TWordPropFieldLen], quantity[TWordPropFieldLen], sort[TWordPropFieldLen];
			inp_stream >> type;
			inp_stream >> gender;
			inp_stream >> quantity;
			inp_stream >> sort;

			word5_1.set_props(type, gender, quantity, sort);

			wcout << L"\n";
			wcout << L"Test 5 - SetWordProps and ChangeWordProps functions\n";
			wcout << L"\nFull word output after setting properties:\n";
			wcout << word5_1;
			wcout << L"\n";

			fout_t << L"\n";
			fout_t << L"Test 5 - SetWordProps and ChangeWordProps functions\n";
			fout_t << L"\nFull word output after setting properties\n";
			fout_t << word5_1;
			fout_t << L"\n";


			word5_1.input_text(inp_stream);

			inp_stream >> quantity;
			inp_stream >> sort;

			word5_1.change_props(quantity, sort);

			wcout << L"\nFull word output after changing properties:\n";
			wcout << word5_1;
			wcout << L"\n\n";

			fout_t << L"\nFull word output after changing properties:\n";
			fout_t << word5_1;
			fout_t << L"\n\n";


			/* Test 6 - InputWordByParts and OutputWordByParts functions */
			TWord word6_1;

			word6_1.input_by_parts(inp_stream);

			wcout << L"\n";
			wcout << L"Test 6 - InputWordByParts and OutputWordByParts functions\n";
			wcout << L"\nThe word output by parts:\n";
			word6_1.output_by_parts(wcout);
			wcout << L"\n\n";

			fout_t << L"\n";
			fout_t << L"Test 6 - InputWordByParts and OutputWordByParts functions\n";
			fout_t << L"\nThe word output by parts:\n";
			word6_1.output_by_parts(fout_t);
			fout_t << L"\n\n";


			/* Test 8 - TWord heirs (TNoun for example, realizations are identical) */

			/* Close fstreams */
			inp_stream.close();
			fout_t.close();
			fout_t << L"\n\nCheck results in file \"Test_Txt_Output.txt\"\n";

		}
		else
		{
			wcout << L"\n\nWrong choice! Try again:";
		}

	}
	
}
