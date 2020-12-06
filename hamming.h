
#ifndef hamming_h
#define hamming_h
#include <iostream>
#include <fstream>
#define LENGTH 7
using namespace std;


int printMenu() {
    int n=0, x=0;
    do
    {
        if (x==1)   // this makes it so that the invalid choice message is only displayed after incorrect try
        {
            cout << "Invalid Choice." << endl;
            cout << "Please input a valid selection from the menu." << endl;
        }
            
        cout << "Please select an option from the following menu:" << endl;
        cout << "1) Encode a message" << endl;
        cout << "2) Decode a message" << endl;
        cout << "3) Exit" << endl;
        cin >> n;
        x=1;
    }
    while (n<1 || n>3);
    
    return (n);
}


void generateHammingCode(bool message[], int n) {
    for (int i=0; i<=n; i++)
    {
        if(i==6)
            message[i] = message[4]^message[2]^message[0];
        if(i==5)
            message[i] = message[4]^message[1]^message[0];
        if(i==3)
            message[i] = message[2]^message[1]^message[0];
    }
}


void encodeMessageStream(string file) {
    bool message[LENGTH];
    char ch;
    
    ifstream fin(file);
    
    if(fin.fail())
    {
        cerr << "Could not open the input file " << file << endl;
        exit(1);
    }
    
    ofstream fout("encodedMessages.txt");
    
    if(fout.fail())
    {
    cerr << "Could not open the output file encodedMessages.txt" << endl;
    exit(1);
    }
    

    for (int i=0; i<=LENGTH; i++)
    {
        if(fin.eof())
            break;
        if (i==6 || i==5 || i==3) // those indices are left empty for the parity values to occupy them later
            continue;
        
        ch = fin.get();
    
        if (ch=='0')
            message[i] = 0;
        else if (ch=='1')
            message[i] = 1;
        else   // After the program reads end of line, it does all processing necessary for 1 line and reset the loop
        {
            fin.get();
            i=-1; // used to reset loop
            generateHammingCode(message, LENGTH);
            cout << "Encoded Message: ";
        
            for (int x=0; x<LENGTH; x++)
            {
                cout << message[x];
                fout << message[x];
            }
            cout << endl;
            fout << endl;
        }
    }
    
    fin.close();
    fout.close();
    
}


int checkMessageParity(bool encodedmessage[], int n) {
    int p1, p2, p4, bit_num, i;
    p1 = encodedmessage[0]^encodedmessage[2]^encodedmessage[4]^encodedmessage[6];
    p2 = encodedmessage[0]^encodedmessage[1]^encodedmessage[4]^encodedmessage[5];
    p4 = encodedmessage[0]^encodedmessage[1]^encodedmessage[2]^encodedmessage[3];
    
    if (p1==0 && p2==0 && p4==0)
        bit_num = -1; // indicates no error found
    
    else
    {
    bit_num = (p4*2*2 + p2*2 + p1*1);
    i = n - bit_num;
    
    if (encodedmessage[i]==1)
        encodedmessage[i] = 0;
    if (encodedmessage[i]==0)
        encodedmessage[i] = 1;
    }
        
    return bit_num;
}


void decodeMessageStream(string file) {
    
    ifstream fin(file);
    
    if(fin.fail())
    {
        cerr << "Could not open the input file " << file << endl;
        exit(1);
    }
    
    ofstream fout("decodedMessages.txt");
       
       if(fout.fail())
       {
       cerr << "Could not open the output file decodedMessages.txt" << endl;
       exit(1);
       }
    
    cout << "Encoded|Corrected|Decoded|STATUS" << endl;
    
    while(!fin.eof())
    {
        bool encodedmessage[LENGTH];
        int bit_num;
        
        for (int x=0; x<=LENGTH; x++) //reads the original encoded message
        {
            char ch;
        
            ch = fin.get();
        
            if (ch=='0')
                encodedmessage[x] = 0;
            if (ch=='1')
                encodedmessage[x] = 1;
            if (ch=='\n')
                break;
        }
            
        for (int y=0; y<LENGTH; y++) // prints the original encoded message
        {
            cout << encodedmessage[y];
            fout << encodedmessage[y];
        }
                
        cout << "|";
        fout << "|";
        bit_num = checkMessageParity(encodedmessage, LENGTH);
                
        for (int z=0; z<LENGTH; z++) // prings the corrected encoded message
        {
            cout << encodedmessage[z];
            fout << encodedmessage[z];
        }
            
        cout << "|";
        fout << "|";
                
        for (int a=0; a<LENGTH; a++) // prints the 4-bit message
        {
            if (a==6 || a==5 || a==3)
                continue;
            cout << encodedmessage[a];
            fout << encodedmessage[a];
        }
        if (bit_num==-1)
        {
            cout << "|NO_ERROR" << endl;
            fout << "|NO_ERROR" << endl;
        }
        else
        {
            cout << "|ERROR_" << bit_num << endl;
            fout << "|ERROR_" << bit_num << endl;
        }
    }
    
    fin.close();
    fout.close();
    
}


#endif /* hamming_h */
