#include<iostream>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Plyer1 =1,Computer =2,Draw = 3 };
struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoice PlayerChoice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName = "";

};
struct stGameResults
{
	short GameRounds = 0;
	short PlayWinTime = 0;
	short ComputerWinTime = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName;
};

int Random(int From, int To)
{
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

enGameChoice ReadPlayerChoice()
{
	short Choice = 0;
	do
	{
		cout << "Your Choice: [1]:Stone, [2]:Paper, [3]:Scssors?" << endl;
		cin >> Choice;
	} while (Choice < 1 || Choice >3);

	return (enGameChoice)Choice;
}
enGameChoice GetComputerChoice()
{
	return (enGameChoice)Random(1, 3);
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.PlayerChoice)
	{
	case enGameChoice::Stone:
	
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;

		}
		break;
	
	case enGameChoice::Paper:
	
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
		break;
	case enGameChoice::Scissors:
	
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	
		
	}
	return enWinner::Plyer1;



	
}
string ChoiceName(short Choice)
{
	string arrNameChoice[3] = { "Stone","Paper","Scissors" };
	return arrNameChoice[Choice - 1];
}
string WinnerName(short Choice)
{
	string arrWinnerName[3] = { "Plyer","Computer","Draw" };
	return arrWinnerName[Choice - 1];
}
void setWinnerScreenColor(enWinner winner)
{
	switch (winner)
	{
	case Plyer1:
		system("color 2F");
		break;
	case Computer:
		system("color 4F");
		cout << "\a";
		break;
	case Draw:
		system("color 6F");
		break;
	default:
		break;
	}
}
void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n___________Round [" << RoundInfo.RoundNumber << "]____________\n\n";
	cout << "Player Choice   : " << ChoiceName(RoundInfo.PlayerChoice) << endl;
	cout << "Computer Choice : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner      : " << RoundInfo.WinnerName << endl;
	cout << "---------------------------------------\n" << endl;
	setWinnerScreenColor(RoundInfo.Winner);
}
enWinner WhoWonTheGame(short PlayWinTime, short ComputerWinTime)
{
	if (PlayWinTime > ComputerWinTime)
		return enWinner::Plyer1;
	else if (ComputerWinTime > PlayWinTime)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}
stGameResults FillGameResults(short Rounds, short PlayWinnerTime,short computerWinnertime,short DrawTime)
{
	stGameResults GameResults;
	GameResults.GameRounds = Rounds;
	GameResults.PlayWinTime = PlayWinnerTime;
	GameResults.ComputerWinTime = computerWinnertime;
	GameResults.DrawTimes = DrawTime;
	GameResults.GameWinner = WhoWonTheGame(PlayWinnerTime, computerWinnertime);
	GameResults.WinnerName = WinnerName(GameResults.GameWinner);
	return GameResults;
}
string Tap(short NumberOfTaps)
{
	string t = "";
	for (int i = 1; i < NumberOfTaps; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

stGameResults PlayGame(short Rounds)
{
	stRoundInfo RoundInfo;
	short PlayWinTime = 0, ComputerWinTime = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= Rounds; GameRound++)
	{
		cout << "\n Round [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.PlayerChoice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputerChoice();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Plyer1)
			PlayWinTime++;
		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerWinTime++;
		else
			DrawTimes++;
		PrintRoundResults(RoundInfo);
	}
	return FillGameResults(Rounds, PlayWinTime, ComputerWinTime, DrawTimes);
}
short ReadHowManyRounds()
{
	short Rounds = 0;
	do
	{
		cout << "How Many Rounds Do you want to Play (1,10)" << endl;
		cin >> Rounds;
	} while (Rounds < 1 || Rounds > 10);
	return Rounds;
}
void ResetScreen()
{
	system("color 0F");
	system("cls");
}
void ShowGameOverScreen()
{
	cout << Tap(2) << "---------------------------------------------------------------------\n\n";
	cout << Tap(2) << "                         +++ G a m e  O v e r +++                    ";
	cout << Tap(2) << "---------------------------------------------------------------------\n\n";

}

void ShowFinalGameResults(stGameResults GameResults)
{
	cout << Tap(2) << "---------------------------[Game Results]------------------\n\n";
	cout << Tap(2) << "Game Rounds        : " << GameResults.GameRounds << endl;
	cout << Tap(2) << "Player won times   : " << GameResults.PlayWinTime << endl;
	cout << Tap(2) << "Computer won times : " << GameResults.ComputerWinTime << endl;
	cout << Tap(2) << "Draw times         : " << GameResults.DrawTimes << endl;
	cout << Tap(2) << "Final Winner       : " << GameResults.WinnerName << endl;
	setWinnerScreenColor(GameResults.GameWinner);
}
void StartGame()
{
	char PlayingAgian = 'Y';
	do
	{
		ResetScreen();
		stGameResults GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResults(GameResults);
		cout << endl << "Do you wnat to play again? Y/N ";
		cin >> PlayingAgian;
		
	} while (PlayingAgian == 'Y' || PlayingAgian == 'y');

}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}