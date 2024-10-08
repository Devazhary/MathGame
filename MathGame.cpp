#include <iostream>
#include <cstdlib>
using namespace std;

enum enLevels {Easy = 1, Med = 2, Hard = 3, Mix = 4};

enum enOpTypes {Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5};

struct stQuestion
{
	int Number1;
	int Number2;
	enLevels SelectedLevel;
	enOpTypes SelectedOpType;
	int CorrectAnswer;
	int UserAnswer;
	bool IsTure = false;
};

struct stQuizz
{
	stQuestion QuestionsList[100];
	short NumberOfQuestions;
	enLevels SelectedLevel;
	enOpTypes SelectedOpType;
	short NumberOfRightAnswer;
	short NumberOfWrongAnswer;
	bool IsPass = false;
};

string GetLevelName(enLevels level)
{
	string ArrayLevelsName[4] = { "Easy", "Med", "Hard", "Mix" };
	return ArrayLevelsName[level - 1];
}

string GetOpSymbol(enOpTypes OpType)
{
	switch (OpType)
	{
	case enOpTypes::Add:
		return "+";
	case enOpTypes::Sub:
		return "-";
	case enOpTypes::Mul:
		return "*";
	case enOpTypes::Div:
		return "/";
	case enOpTypes::MixOp:
		return "Mix";
	}
}

int RandomNumber(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

short HowManyQuestions()
{
	short Number;
	do
	{
		cout << "How many Questions want to answer ? ";
		cin >> Number;

	} while (Number < 1 || Number > 10);
	return Number;
}

enLevels GetLevelFromUser()
{
	short Number;
	do
	{
		cout << "Enter Questions level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
		cin >> Number;

	} while (Number < 1 || Number > 4);
	return (enLevels)Number;
}

enOpTypes GetOpTypeFromUser()
{
	short Number;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
		cin >> Number;

	} while (Number < 1 || Number > 5);
	return (enOpTypes)Number;
}

void SetScreenColor(bool Pass)
{
	if (Pass)
	{
		system("Color 2F");
	}
	else
	{
		system("Color 4F");
	}
}

void ResetScreen()
{
	system("cls");
	system("Color 0F");
}

int  SimpleCalculator(int Number1, int Number2, enOpTypes OpType)
{
	switch (OpType)
	{
	case enOpTypes::Add:
		return Number1 + Number2;
	case enOpTypes::Sub:
		return Number1 - Number2;
	case enOpTypes::Mul:
		return Number1 * Number2;
	case enOpTypes::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}

stQuestion MakeOneQuestion(enLevels Level, enOpTypes OpType)
{
	stQuestion Question;
	if (Level == enLevels::Mix)
	{
		Level = (enLevels)RandomNumber(1, 3);
	}

	if (OpType == enOpTypes::MixOp)
	{
		OpType = (enOpTypes)RandomNumber(1, 4);
	}

	Question.SelectedOpType = OpType;

	switch (Level)
	{
	case enLevels::Easy:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalculator( Question.Number1, Question.Number2, Question.SelectedOpType);
		Question.SelectedLevel = Level;
		return Question;
	case enLevels::Med:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.SelectedOpType);
		Question.SelectedLevel = Level;
		return Question;
	case enLevels::Hard:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.SelectedOpType);
		Question.SelectedLevel = Level;
		return Question;
	}
	return Question;
}

void MakeQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionsList[Question] = MakeOneQuestion(Quizz.SelectedLevel, Quizz.SelectedOpType);
	}
}

void AskAndCorrectTheAnswer(stQuizz& Quizz)
{

}










void PlayGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = HowManyQuestions();
	Quizz.SelectedLevel = GetLevelFromUser();
	Quizz.SelectedOpType = GetOpTypeFromUser();

	MakeQuestions(Quizz);
	AskAndCorrectTheAnswer(Quizz);

}



void StartGame()
{
	char Continue = 'y';
	do
	{
		ResetScreen();
		PlayGame();

		cout << "Do you want to play again? Y/N? ";
		cin >> Continue;

	} while (Continue == 'Y' || Continue == 'y');
}





int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
}