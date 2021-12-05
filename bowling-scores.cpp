#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// GLOBAL CONSTANT VARIABLES
const int NUMBER_OF_BOWLERS = 10;   // change according to how many players are in the file.
const int GAME_ROUNDS = 5;          // change according to how many scores per player are in the file.

// FUNCTION PROTOTYPES
void welcomeMessage();
void InitializeArrays(string bowlerNames[], int bowlingScores[][GAME_ROUNDS], double bowlerAverage[]);
bool GetBowlingData(const string FILE_NAME, string bowlerNames[], int bowlingScores[][GAME_ROUNDS]);
void GetAverageScore(const int bowlingScores[][GAME_ROUNDS], double bowlerAverage[]);
void BowlerHighestAverage(const string bowlerNames[], const double bowlerAverage[]);
void PrettyPrintResults(const string bowlerNames[], const int bowlingScores[][GAME_ROUNDS], const double bowlerAverage[]);

// MAIN
int main()
{
    // ARRAYS USED
    string bowlerNames[NUMBER_OF_BOWLERS];
    int bowlingScores[NUMBER_OF_BOWLERS][GAME_ROUNDS];
    double bowlerAverage[NUMBER_OF_BOWLERS];

    // CONSTANT VARIABLE - change the file name here
    const string FILE_NAME = "BowlingScores.txt";

    // INITIALIZE ARRAYS - A function to initialize all arrays to default values(i.e., "Name" and 0's)
    // just In case the file was missing some values that the program was excepting, these values will
    // be printed as default values when calling PrettyPrintResults() instead of garbage values.
    InitializeArrays(bowlerNames, bowlingScores, bowlerAverage);

    // CALL FUNCTIONS
    welcomeMessage();
    // Check if the file was read into the arrays successfully before calculating averages and showing results.
    bool isDataStored;
    isDataStored = GetBowlingData(FILE_NAME, bowlerNames, bowlingScores);

    if (isDataStored)
    {
        GetAverageScore(bowlingScores, bowlerAverage);
        PrettyPrintResults(bowlerNames, bowlingScores, bowlerAverage);
        BowlerHighestAverage(bowlerNames, bowlerAverage);
    }
    else
    {
        cout << " [!] Existing program...\n" << endl;
        cout << " > Press any key to exit. . . ";
        cin.get();
        return 1;
    }
    
    cout << "\n > Press any key to exit. . . ";
    cin.get();

    return 0;
}

// WELCOME MESSAGE
void welcomeMessage()
{
    const string TITLE = " BOWLING LEAGUE ";
    // The welcome message length will always fit according
    // to how many games(scores per player) are there.
    const int LENGTH = 18 + (12 * GAME_ROUNDS) + 8;
    const int HALF_LENGTH = (LENGTH - TITLE.length()) / 2;
    const char SYMBOLE = '=';
    // Output welcome message
    cout << '\n' << setfill(SYMBOLE) << setw(LENGTH) << '\n';
    cout << setw(HALF_LENGTH) << "" << TITLE << setw(HALF_LENGTH) << '\n';
    cout << setw(LENGTH) << '\n' << setfill(' ') << endl;
}
// INITIALIZE ARRAYS
void InitializeArrays(string bowlerNames[], int bowlingScores[][GAME_ROUNDS], double bowlerAverage[])
{
    // initialize all names to "i.e. Bowler1, Bowler2..."
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
        bowlerNames[i] = "Bowler" + to_string(i + 1);
    // initialize all averages to 0.0
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
        bowlerAverage[i] = 0.0;
    // initialize all scores to 0
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
        for (int j = 0; j < GAME_ROUNDS; j++)
            bowlingScores[i][j] = 0;
}
// READ AND STORE DATA INTO ARRAYS
bool GetBowlingData(const string FILE_NAME, string bowlerNames[], int bowlingScores[][GAME_ROUNDS])
{
    ifstream inFile;
    inFile.open(FILE_NAME.c_str());

    // Check if file is open
    if (!inFile)
    {
        cout << " [!] ERROR: Can't open file name \"" << FILE_NAME << "\"" << endl;
        return false;
    }
    // Read file names into names array and scores into two dimensional array
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
    {
        inFile >> bowlerNames[i];
        for (int j = 0; j < GAME_ROUNDS; j++)
            inFile >> bowlingScores[i][j];
    }
    inFile.close();
    return true;
}
// CALCULATE THE AVERAGE BOWLING SCORE
void GetAverageScore(const int bowlingScores[][GAME_ROUNDS], double bowlerAverage[])
{
    int sum = 0;
    double avg = 0;
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
    {
        for (int j = 0; j < GAME_ROUNDS; j++)
            sum = sum + bowlingScores[i][j];

        avg = static_cast<double>(sum) / GAME_ROUNDS;
        bowlerAverage[i] = avg;

        sum = 0;
        avg = 0;
    }
}
// HIGHEST AVERAGE
void BowlerHighestAverage(const string bowlerNames[], const double bowlerAverage[])
{
    int highestIndex = 0;
    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
        if (bowlerAverage[i] > bowlerAverage[highestIndex])
            highestIndex = i;

    cout << " [+] " << bowlerNames[highestIndex] << " had the highest score average: " << bowlerAverage[highestIndex] << endl;
}
// OUTPUT RESULTS
void PrettyPrintResults(const string bowlerNames[], const int bowlingScores[][GAME_ROUNDS], const double bowlerAverage[])
{
    // Initialize variables - Modify table formatting here
    const string NAME_HEADER = "NAME";
    const string GAME_HEADERS = "GAME";
    const string AVERAGE_HEADER = "AVERAGE";
    const int S_WIDTH = 12;             // width of scores rows 
    const int N_WIDTH2 = S_WIDTH - 1;   // width of name rows

    // A very flexible line separator will always fit according to the table's rows.
    // If there are more or fewer GAME_ROUNDS(rows), the line will always fit accordingly.
    const string LINE_SEPARATOR = ' ' + string(N_WIDTH2 + (S_WIDTH * GAME_ROUNDS) + S_WIDTH, '-');

    // ROW HEADERS - print formated row header (NAME - GAME 1 GAME 2 ... GAME N - AVERAGE) 
    cout << " " << left << setw(N_WIDTH2) << NAME_HEADER;
    for (int i = 0; i < GAME_ROUNDS; i++)
        cout << right << setw(S_WIDTH) << GAME_HEADERS + ' ' + to_string(i + 1);
    cout << right << setw(S_WIDTH) << AVERAGE_HEADER << endl;

    cout << LINE_SEPARATOR << endl;

    for (int i = 0; i < NUMBER_OF_BOWLERS; i++)
    {
        cout << " " << left << setw(N_WIDTH2) << bowlerNames[i];

        for (int j = 0; j < GAME_ROUNDS; j++)
            cout << right << setw(S_WIDTH) << bowlingScores[i][j];

        cout << fixed << showpoint << setprecision(2);
        cout << right << setw(S_WIDTH) << bowlerAverage[i] << endl;
    }
    cout << LINE_SEPARATOR << endl;
}