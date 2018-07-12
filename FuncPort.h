#include<string>
#include<set>

class StrProcess
{
    public:
		bool ReadFile(std::string Path);    //Read File and save to CodeStr as string.
        std::string IsCode(bool Doit);      //Still Not Complete.
		std::string DoPunction();
		std::string DoIdentifiers();
		std::string GetStr();
		void BuildDict();
    
        void DoRemoveDigits();
        void DoLowerCase();
        void DoTokenize();    //Comform in DoPunction()
        void RemoveSmallWords();    //Remove Word that shorter than min word size word 

     private:
		 std::string CodeStr;
		 std::set <std::string> Dict;
		 bool DoSmallWordSize = false;
		 int SmallWordSize=1;
		 std::string MultLineComment;    //Each Comment will separate by '#', Like Comment1#Comment2#Comment3...
		 std::string SingleLineComment;
};