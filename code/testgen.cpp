/* 
Input Format:
First line should have two integers (everything is space-separated) - NumInpPorts, and NumLocalPorts.
The next line contains NumInpPorts integers, which denote the size of the alphabet of each of the Input Ports. (InpAlphabetSize[i])
The next line contains NumLocalPorts integers, which denote the size of the alphabet of each of the Local Ports. (LocalAlphabetSize[i])
The next line contains NumLocalPorts integers, which denote the default values on the Local Ports. (Stored directly in LocalTape[i])
[empty line]
The next line should have a single integer - NumTransitions
[empty line]
Then NumTransitions many sets of lines follow, the i-th of which should follow this format:
    The first NumLocalPorts lines contain a single integer denoting what the Local Port values should be, to trigger this transition.
    Then NumInpPorts lines contain many integers, each denoting what the suffix of the Input Ports should be, to trigger this. They follow this format:
        The first integer is TInpLen[i][j], the length of the suffix.
        The next TInpLen[i][j] integers are the suffix.
    The next NumLocalPorts lines contain a single integer each, which denote the Local Port output values, if this transition is triggered.
    Then a single line with a single integer, TOut, which is the integer outputted when this transition is triggered.
[empty line after each transition]
A single line with a single integer - the index of the transition (1-indexed) that needs to be trigerred.

Output Format:
The requisite input, two integers in each line.
[empty line]
All the inputs and outputs produced by the above input string, are outputted at the end, interleaved in sequence. Output a is displayed as "Output a".
*/

#include <bits/stdc++.h>

#define SZ(x) static_cast < int > ((x).size())

using namespace std;

const int MaxNumInpPorts = 100;
const int MaxNumLocalPorts = 100;
const int MaxNumTransitions = 1000;

int NumInpPorts, NumLocalPorts, NumTransitions;
int InpAlphabetSize[MaxNumInpPorts + 1], LocalAlphabetSize[MaxNumLocalPorts + 1];
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

int TargetTransition;
int InpMaxLen[MaxNumInpPorts + 1];
int TotalAlphabetSize = 0, TotalInpAlphabetSize = 0;
int MaxInpLen;
vector < pair < int, int > > InputString, AnsString;
bool FoundTarget = false;


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

    for (int i = 1; i <= NumInpPorts; i++)
    {
        InpTape[i].clear();
    }
    IOTape.clear();
    for (int i = 1; i <= NumLocalPorts; i++)
    {
        a = LocalTape[i][0]; // Default value
        LocalTape[i].clear();
        LocalTape[i].push_back(a);
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

    for (int i = 1; i <= NumInpPorts; i++)
    {
        cin >> InpAlphabetSize[i];
        TotalAlphabetSize += InpAlphabetSize[i];
        TotalInpAlphabetSize += InpAlphabetSize[i];
    }
    for (int i = 1; i <= NumLocalPorts; i++)
    {
        cin >> LocalAlphabetSize[i];
        TotalAlphabetSize += LocalAlphabetSize[i];
    }

    //Inputting default values for the local variables
    for(int i = 1; i <= NumLocalPorts; i++)
    {
        cin >> a;
        LocalTape[i].push_back(a);
    }

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
            InpMaxLen[j] = max(InpMaxLen[j], TInpLen[i][j]);
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

    cin >> TargetTransition;

    MaxInpLen = 1;
    for (int i = 1; i <= NumInpPorts; i++)
    {
        for (int j = 1; j <= InpMaxLen[i]; j++)
        {
            MaxInpLen *= InpAlphabetSize[i]; // +1 for null string?
        }
    }
    for (int i = 1; i <= NumLocalPorts; i++)
    {
        MaxInpLen *= LocalAlphabetSize[i];
    }
    MaxInpLen++; //

    cout << "Max Inp Len is " << MaxInpLen << "\n";

    for (long long bitmask = 0; bitmask < pow(TotalInpAlphabetSize, MaxInpLen) + 1; bitmask++)
    {
        //cout<<bitmask<<"\n";
        //Generating the input string
        InputString.clear();
        long long temp = bitmask;
        for(int ww = 1; ww <= MaxInpLen; ww++)
        {
            long long temp2 = temp % TotalInpAlphabetSize;
            temp2++;
            temp /= TotalInpAlphabetSize;

            for (int i = 1; i <= NumInpPorts; i++)
            {
                if (temp2 <= InpAlphabetSize[i])
                {
                    InputString.push_back(make_pair(i, temp2));
                    break;
                }
                temp2 -= InpAlphabetSize[i];
            }
        }
        InputString.push_back(make_pair(-1, -1));
        AnsString.clear();
        initialize();

        //Checking the input string
        for (int qq = 0; qq < InputString.size(); qq++)
        {
            a = InputString[qq].first;
            b = InputString[qq].second;
            //(a, b) is the next character of the string, where a is the port number
            if (a == -1)
                break;

            assert((a >= 1) && (a <= NumInpPorts));

            InpTape[a].push_back(b);
            IOTape.push_back(make_pair(a, b));
            AnsString.push_back(make_pair(a, b));

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
                        if (i == TargetTransition)
                        {
                            FoundTarget = true;
                            break;
                        }
                        break;
                    }
                }

                if (FoundTarget == true)
                    break;
                if (TriggeredAny == false) // None of the transitions got triggered. So we are at a 'stable' place, and can now read the next input.
                    break;
            }
            if (FoundTarget == true)
                break;
        }


        if (FoundTarget == true)
        {
            cout << "Found Input String:\n";
            for (int i = 0; i < AnsString.size(); i++)
                cout << AnsString[i].first << " " << AnsString[i].second << "\n";

            cout << "\nIOTape:\n";
            for (int ii = 0; ii < SZ(IOTape); ii++)
            {
                if (IOTape[ii].first == -1)
                    cout << "Output " << IOTape[ii].second << "\n";
                else
                    cout << IOTape[ii].first << " " << IOTape[ii].second << "\n";
            }
            break;
        }
    }

    if(FoundTarget == false)
        cout << "This transtion cannot be triggered.\n";

    return 0;
}