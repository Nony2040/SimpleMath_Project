#include <iostream>
using namespace std;

enum enLevels{Easy = 1,Med,Hard,All};
enum enOperation{Add = 1,Sub,Mul,Div,Mix};
struct stLevel{
    int LevelInt;
    string Level;
};
struct stOperation{
    int OperationInt;
    int ConstOperationType;
    string OpString;
    string PrintOpWord;
};
struct stCounter{
    int Right = 0;
    int Wrong = 0;
};
struct stExamInfo{
    int Number1, Number2, Real_Result, User_Result;
    int Questions;
};

string ReadString(string message){
    string Name;
    cout << message << endl;
    cin >> Name;
    return Name;
}
int ReadPosNum(string Message){
    int Num;
    do
    {
        cout << Message << " ....\n";
        cin >> Num;
    } while (Num <= 0);

    return Num;
}

int RandomNumber(int From, int To){
    int RandomNum = rand() % (To - From + 1) + From;
    return RandomNum;
}
void SetCounter0(stCounter &Count){
    Count.Right = 0;
    Count.Wrong = 0;
}

int Level_Number(stLevel Level){
    switch (Level.LevelInt)
    {
    case enLevels::Easy:
        return RandomNumber(0, 10);
    case enLevels::Med:
        return RandomNumber(11, 50);
    case enLevels::Hard:
        return RandomNumber(51, 100);
    case enLevels::All:
        return RandomNumber(0, 100);
    }
    return 0;
}

void Get_Level_Operation(stLevel &Level, stOperation &Oper){ // Enter Questions Level
    do
    {
        Level.LevelInt = ReadPosNum("Enter Questions Level :  Easy:[1] Med:[2] Hard:[3] Mix:[4]");
    } while (Level.LevelInt > 4);

    do
    {
        Oper.OperationInt = ReadPosNum("Enter Operation Type :  Add:[1] Sub:[2] Mul:[3] Div:[4] Mix:[5]");
    } while (Oper.OperationInt > 5);
}
void Get_Operations(stOperation &Oper){
    // Creat_Number1_Number2(Info,Level);
    switch (Oper.ConstOperationType)
    {
    case enOperation::Add:
        Oper.OpString = "+";
        Oper.PrintOpWord = "Addition";
        break;
    case enOperation::Sub:
        Oper.OpString = "-";
        Oper.PrintOpWord = "substitution";
        break;
    case enOperation::Mul:
        Oper.OpString = "x";
        Oper.PrintOpWord = "Multiply";
        break;
    case enOperation::Div:
        Oper.OpString = "/";
        Oper.PrintOpWord = "Divide";
        break;

    default:
        Oper.PrintOpWord = "Mix";
        break;
    }
}

void Creat_Number1_Number2(stExamInfo &Info, stLevel Level){
    Info.Number1 = Level_Number(Level);
    Info.Number2 = Level_Number(Level);
}

void Get_RealResult(stOperation Oper, stExamInfo &Info){
    switch (Oper.OperationInt)
    {
    case enOperation::Add:
        Info.Real_Result = Info.Number1 + Info.Number2;
        break;
    case enOperation::Sub:
        Info.Real_Result = Info.Number1 - Info.Number2;
        break;
    case enOperation::Mul:
        Info.Real_Result = Info.Number1 * Info.Number2;
        break;
    case enOperation::Div:
        Info.Real_Result = Info.Number1 / Info.Number2;
        break;

    default:
        break;
    }
} // Mix Repeat this function
void MakeExamLevel_ToString(stLevel &Level){
    switch (Level.LevelInt)
    {
    case enLevels::All:
        Level.Level = "Mix";
        break;
    case enLevels::Easy:
        Level.Level = "Easy";
        break;
    case enLevels::Med:
        Level.Level = "Medium";
        break;
    case enLevels::Hard:
        Level.Level = "Hard";
        break;
    default:
        break;
    }
}
void CountTheRes(stCounter &Count, stExamInfo Info){
    if (Info.Real_Result == Info.User_Result)
        Count.Right++;
    else
        Count.Wrong++;
}
string Exam_Result(stCounter Count){
    if (Count.Right >= Count.Wrong)
        return "Success :)";
    else if (Count.Wrong > Count.Right)
        return "Failled :(";
    else
        return "Something went Wrong Exam_res";
}

void Ask_User(stExamInfo &Info, stOperation Oper, int X){
    cout << "\n\n";
    cout << "_______________Question [" << X << "/" << Info.Questions << "]_______________\n";
    cout << Info.Number1 << endl;
    cout << Info.Number2 << " " + Oper.OpString << endl;
    cout << "_______\n";
    cin >> Info.User_Result;
    cout << "\n";
}

void Querry_Function(stCounter &Count, stExamInfo &Info, stOperation &Oper, stLevel &Level)
{

    Info.Questions = ReadPosNum("Enter How Many Questions You Want??");
    Get_Level_Operation(Level, Oper);
    Oper.ConstOperationType = Oper.OperationInt;

    for (int i = 1; i <= Info.Questions; i++)
    {
        Creat_Number1_Number2(Info, Level);

        if (Oper.ConstOperationType == enOperation::Mix)
            Oper.OperationInt = RandomNumber(1, 4);

        Get_Operations(Oper);
        Ask_User(Info, Oper, i);
        Get_RealResult(Oper, Info);

        CountTheRes(Count, Info);

        cout << "Your Answer = " << Info.User_Result << "\n";
        cout << "Real Result = " << Info.Real_Result << "\n";
    }
}

void Print_Card(stCounter Count, stExamInfo Info, stOperation Oper, stLevel Level){

    MakeExamLevel_ToString(Level);

    cout << "\t\t\t" << "_________________________________________________________________\n";
    cout << "\t\t\t" << "___________________ Final Result is " << Exam_Result(Count) << " __________________\n";
    cout << "\t\t\t" << "_________________________________________________________________\n\n";

    cout << "\t\t\t" << "Number of Questions: " << Info.Questions << endl;
    cout << "\t\t\t" << "Right Aswers: " << Count.Right << endl;
    cout << "\t\t\t" << "Wrong Aswers: " << Count.Wrong << endl;
    cout << "\t\t\t" << "Questions Level: " << Level.Level << endl;
    cout << "\t\t\t" << "Operations Type: " << Oper.PrintOpWord << endl;
    cout << "\t\t\t" << "_________________________________________________________________\n\n";
}


void RunTheProgram(stCounter Count, stExamInfo Info, stOperation Oper, stLevel Level){
    string YN = "";
    do
    {
        Querry_Function(Count, Info, Oper, Level);
        Print_Card(Count, Info, Oper, Level);

        SetCounter0(Count);

        YN = ReadString("Do You Want To Play Again??  Y/N");
    } while (YN == "YES" || YN == "Yes" || YN == "yes" || YN == "Y" || YN == "YeS" || YN == "yEs" || YN == "yeS");
}
int main(){
    srand((unsigned)time(NULL));
    stExamInfo Info;
    stLevel Level;
    stOperation Oper;
    stCounter Count;

    RunTheProgram(Count, Info, Oper, Level);

    return 0;
}
