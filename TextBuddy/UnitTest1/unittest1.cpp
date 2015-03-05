#include "stdafx.h"
#include "CppUnitTest.h"
#include <fstream>
#include "TextBuddy.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TextBuddyTests
{		
	static	const string testString_1 = "somebody is sleeping";
	static	const string testString_2 = "he is hungry";
	static	const string testString_3 = "is fun";

	TEST_CLASS(sortTest){


	public:
		
		TEST_METHOD(sortAlphaTest) {
			TextBuddy::addLine("atest.txt", testString_1);
	        TextBuddy::addLine("atest.txt", testString_2);
	        TextBuddy::addLine("atest.txt", testString_3);
			const string ExpectedOutput = "all content in atest.txt are sorted alphabetically";

			Assert::AreEqual(ExpectedOutput, TextBuddy::sortAlphabetically("atest.txt"));
		}
	};
	
	TEST_CLASS(searchTest) {

	public:
		TEST_METHOD(searchWordTest) {

			TextBuddy::addLine("atest.txt", testString_1);
	        TextBuddy::addLine("atest.txt", testString_2);
	        TextBuddy::addLine("atest.txt", testString_3);
			string target = "he";
			string result = TextBuddy::searchWord("atest.txt", target);
			string expected = "";
			Assert::AreEqual(expected, result); //found case
	
			string target2 = "am";
			string result2 = TextBuddy::searchWord("atest.txt", target2);
			string expected2 = "word not found in %s";
			Assert::AreEqual(expected2, result2); //not found case
		}
	};
}