/* This is simulator of mDSA, that is, multi-port DSA.

The number of Input Ports (or input variables in EDT) is NumInpPorts. They are numbered from 1 to NumInpPorts. 
The alphabet of any two ports are disjoint. A pair of integers (i, j) represents the j-th letter in the alphabet of Port i.

There are NumLocalPorts local (or state / internal) variables, which are numbered from 1 to NumLocalPorts. 
Their alphabet is represented similarly as above - (i,j) corresponds to the j-th letter in the alphabet of the i-th local variable.

Transitions (or EDT row definitions) :
There are a total of NumTransitions transitions.
We assume that the EDT row definitions are given in decreasing priority order. 
That is, if at a given moment, two rows can be triggered, the row defined earlier is triggered first.
We are ignoring timing and Row Sequences for now.
The i-th transition is given as follows: (TInp[i][NumInpPorts+1], TLocalInp[i][NumLocalPorts+1], TLocalOut[i][NumLocalPorts+1]).
TInp[i][NumInpPorts+1] is an array of size NumInpPorts+1 (1-indexed), each element of which is a string. 
TInp[i][j] should be a suffix of the j-th Input Channel for the i-th transition to be triggered.
TInpLen[i][j] stores the length of TInp[i][j].
TLocalInp[i][NumLocalPorts+1] is an array of size NumLocalPorts+1 (1-indexed), each element of which is a character. 
TLocalInp[i][j] should be the last character of the j-th Local Channel for the i-th transition to be triggered.
TLocalOut[i][NumLocalPorts+1] is an array of size NumLocalPorts+1 (1-indexed), each element of which is a character. 
TLocalOut[i][j] is the character written to the j-th Local Channel when the i-th transition is triggered.
TLocalInp, and TLocalOut can also be (-1, -1), which signifies that it is a null string. TInp will be empty in such a case, since TInpLen will be 0;
TOut is the output produced when this transition is triggered.

InpTape[i] is the tape corresponding to the i-th input port.
LocalTape[i] is the tape corresponding to the i-th local variable.
InpTapeHead[i][j] is the tape head on the j-th input tape corresponding to the i-th transition.
LocalTapeHead[i][j] is the tape head on the j-th local tape corresponding to the i-th transition.
IOTape contains all the inputs and outputs produced, interleaved in sequence. This is outputted at the very end. Output a is displayed as "Output a".


Input format:
First line should have two integers (everything is space-separated) - NumInpPorts, and NumLocalPorts.
The second line should have a single integer - NumTransitions
Then NumTransitions many lines follow, the i-th of which should follow this format:
    The first NumLocalPorts integers denote what the Local Port values should be, to trigger this transition.
    Then NumInpPorts 'sets' of integers follow, each denoting what the suffix of the Input Ports should be, to trigger this. They follow this format:
        The first integer is TInpLen[i][j], the length of the suffix.
        The next TInpLen[i][j] integers are the suffix.
    Then NumLocalPorts integers follow, which denote the Local Port output values, if this transition is triggered.
    Then a single integer, TOut, which is the integer outputted when this transition is triggered.
Then the input stream starts. Each line should contain two integers a and b. a denotes the port number, and b is the actual input. 
The stream ends with (-1, -1).
*/

#include <bits/stdc++.h>

#define SZ(x) static_cast < int > ((x).size())

using namespace std;

const int MaxNumInpPorts = 100;
const int MaxNumLocalPorts = 100;
const int MaxNumTransitions = 1000;

int NumInpPorts, NumLocalPorts, NumTransitions;
int TInpLen[MaxNumTransitions + 1][MaxNumInpPorts + 1]; // Doesn't need to be stored
vector < int > TInp[MaxNumTransitions + 1][MaxNumInpPorts + 1];
vector < pair < int, int > > IOTape;
int TLocalInp[MaxNumTransitions + 1][MaxNumLocalPorts + 1];
int TLocalOut[MaxNumTransitions + 1][MaxNumLocalPorts + 1];
int TOut[MaxNumTransitions + 1];
vector < int > InpTape[MaxNumInpPorts + 1];
vector < int > LocalTape[MaxNumLocalPorts + 1];
int InpTapeHead[MaxNumTransitions + 1][MaxNumInpPorts + 1]; // Points to the last character which has been consumed. So initialized with -1
int LocalTapeHead[MaxNumTransitions + 1][MaxNumLocalPorts + 1]; // Points to the last character which has been consumed. So initialized with -1
int a, b; // temp variables


void initialize()
{
    for (int i = 1; i <= NumTransitions; i++)
    {
        for (int j = 1; j <= NumInpPorts; j++)
        {
            InpTapeHead[i][j] = -1;
        }
        for (int j = 1; j <= NumLocalPorts; j++)
        {
            LocalTapeHead[i][j] = -1;
        }
    }
    return;
}


bool CheckTrigger(int i) // returns true if the i-th transition should be triggered
{
    bool FoundNonEmptyNonEnd = false;

    for (int j = 1; j <= NumInpPorts; j++)
    {
        if (SZ(TInp[i][j]) == 0)
            continue;

        if (SZ(InpTape[j]) < SZ(TInp[i][j]))
        {
            return false;
        }

        if (InpTapeHead[i][j] != (SZ(InpTape[j]) - 1))
        {
            if (InpTapeHead[i][j] >= (SZ(InpTape[j]) - SZ(TInp[i][j])))
            {
                return false;
            }
        }
        //This check ensures that either the tape-head is at the end, or the suffix is totally after the tape-head.

        for (int kt = (SZ(TInp[i][j]) - 1), ki = (SZ(InpTape[j]) - 1); kt >= 0; kt--, ki--)
        {
            if (TInp[i][j][kt] != InpTape[j][ki])
                return false;
        }

        if (InpTapeHead[i][j] != (SZ(InpTape[j]) - 1))
            FoundNonEmptyNonEnd = true;
    }

    for (int j = 1; j <= NumLocalPorts; j++)
    {
        if (TLocalInp[i][j] == -1)
            continue;

        if (SZ(LocalTape[j]) == 0)
        {
            return false;
        }

        if (TLocalInp[i][j] != LocalTape[j][SZ(LocalTape[j]) - 1])
            return false;

        if (LocalTapeHead[i][j] == (SZ(LocalTape[j]) - 1))
            continue;

        FoundNonEmptyNonEnd = true;
    }

    if (FoundNonEmptyNonEnd == false)
        return false;
    return true;
}


void Trigger(int i)
{
    for (int j = 1; j <= NumLocalPorts; j++)
    {
        if (TLocalOut[i][j] != -1)
        {
            LocalTapeHead[i][j] = SZ(LocalTape[j]) - 1; //The character outputted in the next line shouldn't be considered as consumed.
            LocalTape[j].push_back(TLocalOut[i][j]);
        }
        else
        {
            LocalTapeHead[i][j] = SZ(LocalTape[j]) - 1; //This is a redundant line, since this tape-head is never going to be used.
        }
    }

    for (int j = 1; j <= NumInpPorts; j++)
    {
        InpTapeHead[i][j] = SZ(InpTape[j]) - 1;
    }

    IOTape.push_back(make_pair(-1, TOut[i]));
    return;
}


int main() {

    cin >> NumInpPorts >> NumLocalPorts;
    cin >> NumTransitions;

    initialize();

    //Inputting the transitions
    for (int i = 1; i <= NumTransitions; i++)
    {
        for (int j = 1; j <= NumLocalPorts; j++)
        {
            cin >> TLocalInp[i][j];
        }


        for (int j = 1; j <= NumInpPorts; j++)
        {
            cin >> TInpLen[i][j];
            for (int k = 1; k <= TInpLen[i][j]; k++)
            {
                cin >> a;
                TInp[i][j].push_back(a);
            }
        }

        for (int j = 1; j <= NumLocalPorts; j++)
        {
            cin >> TLocalOut[i][j];
        }

        cin >> TOut[i];
    }

    // Inputting the string
    while (1)
    {
        cin >> a >> b; //(a, b) is the next character of the string, where a is the port number
        if (a == -1)
            break;

        assert((a >= 1) && (a <= NumInpPorts));

        InpTape[a].push_back(b);
        IOTape.push_back(make_pair(a, b));

        while (1)
        {
            bool TriggeredAny = false;
            for (int i = 1; i <= NumTransitions; i++)
            {
                if (CheckTrigger(i))
                {
                    TriggeredAny = true;
                    // cout << "Triggering " << i << endl;
                    Trigger(i);
                    break;
                }
            }
            if (TriggeredAny == false) // None of the transitions got triggered. So we are at a 'stable' place, and can now read the next input.
                break;
        }
    }

    for (int ii = 0; ii < SZ(IOTape); ii++)
    {
        if (IOTape[ii].first == -1)
            cout << "Output " << IOTape[ii].second << "\n";
        else
            cout << IOTape[ii].first << " " << IOTape[ii].second << "\n";
    }

    return 0;
}