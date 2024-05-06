#include <iostream>
#include <cstdlib>
using namespace std;

enum enQustionLevel { Easy = 1, Med = 2, Hard = 3, QuestionMix = 4 };

enum enOpType { Add = 1, Sub = 2, Multi = 3, Divison = 4, OpMix = 5 };

struct stRoundQuestion
{
	int Answer;
	int Num1;
	int Num2;
	char OpType;
	bool isCorrect;
	int CorrAnswer;
};

struct stGameInfo
{
	short NumofQuestons;
	enQustionLevel QustionLevel;
	enOpType OpType;
};

struct stGameStatics
{
	short NumOfQuestions;
	string QustionLevel;
	string OpType;
	short NumOfRightAns;
	short NumOfWrongAns;
};

int RandomNumber(int From, int To)
{
	// Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

int ReadPostiveNumber(string Message)
{
	int Num;
	do {
		cout << Message << endl;
		cin >> Num;
	} while (Num <= 0);
	return Num;
}

stGameInfo ReadGameInfo()
{
	stGameInfo GameInfo;

	GameInfo.NumofQuestons = ReadPostiveNumber("How Many Questions Do You want to answer? ");
	GameInfo.QustionLevel = enQustionLevel(ReadPostiveNumber("Enter Questions Level [1] Easy , [2] Med , [3] Hard , [4] Mix ? "));
	GameInfo.OpType = enOpType(ReadPostiveNumber("Enter Operation Type [1] Add , [2] Sub , [3] Multiplay , [4] Divsion , [5] Mix ? "));
	return GameInfo;
}

int GetNumber(enQustionLevel QL)
{
	int Num = 0;
	switch (QL)
	{
	case enQustionLevel::Easy:
		Num = RandomNumber(1, 10);
		break;
	case enQustionLevel::Med:
		Num = RandomNumber(10, 100);
		break;
	case enQustionLevel::Hard:
		Num = RandomNumber(100, 1000);
		break;
	case enQustionLevel::QuestionMix:
		Num = RandomNumber(1, 1000);
		break;
	}
	return Num;
}

char RadnomOptType(enOpType OpT)
{
	char OpTc[4] = { '+', '-', 'x', '/' };
	short num = RandomNumber(1, 4);
	return OpTc[4 - num];
}

char OpType(enOpType OpT)
{

	switch (OpT)
	{
	case enOpType::Add:
		return '+';
	case enOpType::Sub:
		return '-';
	case enOpType::Multi:
		return 'x';
	case enOpType::Divison:
		return '/';
	case enOpType::OpMix:
		return RadnomOptType(enOpType::OpMix);
	default:
		return '?';
	}
}

int PrintQuestion(stRoundQuestion RoundInfo)
{
	int Answer = 0;
	cout << RoundInfo.Num1 << " " << RoundInfo.OpType << " " << RoundInfo.Num2 << " = ";
	cin >> Answer;
	cout << "\n___________________" << endl;
	return Answer;
}

int CorrAnswer(stRoundQuestion& RoundInfo)
{
	int actualAnswer = 0;
	switch (RoundInfo.OpType)
	{
	case '+':
		actualAnswer = RoundInfo.Num1 + RoundInfo.Num2;
		break;
	case '-':
		actualAnswer = RoundInfo.Num1 - RoundInfo.Num2;
		break;
	case 'x':
		actualAnswer = RoundInfo.Num1 * RoundInfo.Num2;
		break;
	case '/':
		actualAnswer = RoundInfo.Num1 / RoundInfo.Num2;
		break;
	}
	return actualAnswer;
}

bool isAnsweCorrect(stRoundQuestion RoundInfo)
{

	int actualAnswer = 0;

	switch (RoundInfo.OpType)
	{
	case '+':
		actualAnswer = RoundInfo.Num1 + RoundInfo.Num2;
		break;
	case '-':
		actualAnswer = RoundInfo.Num1 - RoundInfo.Num2;
		break;
	case 'x':
		actualAnswer = RoundInfo.Num1 * RoundInfo.Num2;
		break;
	case '/':
		actualAnswer = RoundInfo.Num1 / RoundInfo.Num2;
		break;
	}

	return actualAnswer == RoundInfo.Answer;
}

void PrintQuestionResult(stRoundQuestion RoundInfo)
{
	if (RoundInfo.isCorrect)
	{
		cout << "Right Answer :-)\n\n" << endl;
		system("color 2F"); //turn screen to Green  
	}
	else
	{
		cout << "Wrong Answer :-(" << endl;
		cout << "The Right Answer is: " << RoundInfo.CorrAnswer << "\n\n" << endl;
		system("color 4F"); //turn screen to Red 
		cout << "\a";
	}
}

string opType(enOpType type)
{
	string OPTC[5] = { "Mix", "/", "x", "-", "+" };
	return OPTC[5 - type];
}

string Queslevel(enQustionLevel level)
{
	string QL[4] = { "Mix", "Hard", "Med", "Easy" };
	return QL[4 - level];
}

stGameStatics FillFinalReslut(stGameInfo GameInfo, short CorrectAns, short WrongAns)
{
	stGameStatics GameResluts;
	GameResluts.NumOfQuestions = GameInfo.NumofQuestons;
	GameResluts.NumOfRightAns = CorrectAns;
	GameResluts.NumOfWrongAns = WrongAns;
	GameResluts.OpType = opType(GameInfo.OpType);
	GameResluts.QustionLevel = Queslevel(GameInfo.QustionLevel);

	return GameResluts;
}

stGameStatics PlayGame(stGameInfo GameInfo)
{
	stRoundQuestion RoundInfo;
	short CorrectAns = 0, WrongAns = 0;
	short Question;
	for (Question = 1; Question <= GameInfo.NumofQuestons; Question++)
	{
		cout << "\nQuestion [" << Question << "/" << GameInfo.NumofQuestons << "]" << endl;
		RoundInfo.OpType = OpType(GameInfo.OpType);
		RoundInfo.Num1 = GetNumber(GameInfo.QustionLevel);
		RoundInfo.Num2 = GetNumber(GameInfo.QustionLevel);
		RoundInfo.Answer = PrintQuestion(RoundInfo);
		RoundInfo.CorrAnswer = CorrAnswer(RoundInfo);
		RoundInfo.isCorrect = isAnsweCorrect(RoundInfo);


		//Increase Correct/Wrong counters 
		if (RoundInfo.isCorrect)
			CorrectAns++;
		else
			WrongAns++;

		PrintQuestionResult(RoundInfo);
	}

	return FillFinalReslut(GameInfo, CorrectAns, WrongAns);
}

void FindFinalReslut(stGameStatics final)
{
	if (final.NumOfRightAns >= final.NumOfWrongAns)
	{
		cout << "Pass :-)\n";
		system("Color 2F");
	}
	else
	{
		cout << "Fail :-(\n";
		system("Color 4F");
		cout << "\a";
	}
}

void PrintReslutsofGame(stGameStatics GameResluts)
{
	cout << "\n\n__________________________________\n" << endl;
	cout << "   Final Reslut is ";
	FindFinalReslut(GameResluts);
	cout << "__________________________________\n" << endl;
	cout << "Number of Question: " << GameResluts.NumOfQuestions << endl;
	cout << "Questions Level   : " << GameResluts.QustionLevel << endl;
	cout << "Operation Type    : " << GameResluts.OpType << endl;
	cout << "Number of Right Answers: " << GameResluts.NumOfRightAns << endl;
	cout << "Number of Wrong Answers: " << GameResluts.NumOfWrongAns << endl;
	cout << "__________________________________\n" << endl;
}

void RestScreen()
{
	system("cls");
	system("Color 0F");
}

void Start()
{
	char PlayAgain = '-';
	do {
		RestScreen();
		stGameStatics GameStatics;
		GameStatics = PlayGame(ReadGameInfo());
		PrintReslutsofGame(GameStatics);
		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	Start();

	return 0;
}
