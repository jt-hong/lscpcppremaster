#include"FuncPort.h"
#include<iostream>
#include<string>
#include<fstream>
#include<regex>
#include <iterator>
#include <sstream>
#include <algorithm> 
bool StrProcess::ReadFile(std::string Path)
{
	std::ifstream CodeFile;
	std::string FileContents;
	CodeFile.open(Path.c_str(), std::ios::in);
	if (CodeFile.is_open())
	{
		std::stringstream Buffer;
		Buffer << CodeFile.rdbuf();
		std::string Contents(Buffer.str());
		FileContents = Contents;
		CodeFile.close();
		StrProcess::CodeStr = FileContents;
		return true;
	}
	else
	{
		std::cout << "Fail";
		return false;
	}
}

//std::string StrProcess::IsCode(std::string CodeContents, bool Doit)    //Can Only match Multi Line Text at Now.
//{
//	std::string Str = " '''print''' ";
//	std::smatch Result;
//	std::string Pattern("(''')[\\S\\s]+?'{3}?");
//	std::regex Re(Pattern);
//	std::sregex_iterator Pos(CodeContents.begin(), CodeContents.end(), Re);
//	std::sregex_iterator End;
//	for (; Pos != End; Pos++)
//	{
//		std::cout << Pos->position() << std::endl << "------------------------" << std::endl;
//	}
//	return StrProcess::CodeStr;
//}
std::string StrProcess::IsCode( bool Doit)
{
	std::string CodeContents = CodeStr;
	std::string MultLine = "";
	std::string SingleLine = "";
	std::string MultL("(''')[\\S\\s]+?'{3}?");
	std::regex MRe(MultL);
	std::sregex_iterator MPos(CodeContents.begin(), CodeContents.end(), MRe);
	std::sregex_iterator MEnd;
	for (; MPos != MEnd; MPos++)
	{
		MultLine.append(CodeContents.substr(MPos->position() + 3, MPos->length() - 6));
		MultLine.append("#");
	}
	CodeContents = std::regex_replace(CodeContents, MRe, "");
	//SIngleLine Part
	std::string SingleEx("#.+");
	std::regex Single(SingleEx);
	std::sregex_iterator Fin(CodeContents.begin(), CodeContents.end(), Single);
	std::sregex_iterator IteEnd;
	for (; Fin != IteEnd; Fin++)
	{
		SingleLine.append(CodeContents.substr(Fin->position() + 1, Fin->length()));
	}
	CodeContents = std::regex_replace(CodeContents, Single, "");
	StrProcess::CodeStr = CodeContents;
	std::string MultLineComment = MultLine;
	std::string SingleLineComment = SingleLine;
	return CodeContents;
}


/*DoPunction:
Replace All punction.
Input: String Object
OutPut: String Object
*/
std::string StrProcess::DoPunction()
{
	std::string Code = StrProcess::CodeStr;
	std::string Buffer;
	std::string Pattern("[\\W_]+");
	std::regex Re(Pattern);
	Buffer = std::regex_replace(Code, Re, " ");
	StrProcess::CodeStr = Buffer;
	return Buffer;
}

std::string StrProcess::DoIdentifiers()    //Must using after BuildDict() and DoPunction() Done
{
	std::string Code = StrProcess::CodeStr;
	int Begin = 0;
	int Found=0;
	std::string word;
	for (int End = 0; End <= Code.length(); End++)
	{
		if (Code[End] == ' ')
		{
			word = Code.substr(Begin, End - Begin);
			Found = StrProcess::Dict.count(word);
			if (Found == 1)
			{
				Code.erase(Begin, End - Begin + 1);
				End = Begin;
			}
			else
			{
				Begin = End + 1;
			}
		}
	}
	StrProcess::CodeStr = Code;
	return Code;
}

std::string StrProcess::GetStr()
{
	return StrProcess::CodeStr;
}

void StrProcess::BuildDict()    //Build Python Keyword Dictionary
{
	std::string Dictionary[] = { "False","class","finally","for","return","None","continue","for","lambda","try","True",
		"def","from","nonlocal","while","and","del","global","not","with","as","elif","if","or","yield","assert","else",
		"import","pass","break","except","in","raise" };
	StrProcess::Dict.insert(Dictionary, Dictionary + 33);
}

void StrProcess::DoRemoveDigits()
{
	std::string Code = StrProcess::CodeStr;
	std::string Digits("\\d+");
	std::regex ReMoveDig(Digits);
	Code = std::regex_replace(Code, ReMoveDig, "");
	std::string Space(" {2}");
	std::regex Sort(Space);
	Code = std::regex_replace(Code, Sort, " ");
	StrProcess::CodeStr = Code;
}

void StrProcess::DoLowerCase()
{
	std::string Code = StrProcess::CodeStr;
	std::transform(Code.begin(), Code.end(), Code.begin(), ::tolower);
	StrProcess::CodeStr = Code;
}

void StrProcess::RemoveSmallWords()
{
	std::string Code = StrProcess::CodeStr;
	int Begin = 0;
	for (int End = 0; End <= Code.length(); End++)
	{
		if (Code[End] == ' ' || End == Code.length() - 1)
		{
			if ((End - Begin) <= StrProcess::SmallWordSize)
			{
				Code.erase(Begin, End - Begin + 1);
				End = Begin;
			}
			else
			{
				Begin = End + 1;
			}
		}
	}
	StrProcess::CodeStr = Code;
}



