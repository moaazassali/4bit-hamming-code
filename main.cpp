//
//  main.cpp
//  Assignment 2
//
//  Description: Computer Engineering Case Study
//  Created by Muaath Asali on 10/18/19.
//  Copyright © 2019 Muaath Asali. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "hamming.h"
using namespace std;



int main() {
    int y=0;
    string fname;
    
    do
    {
        
    y=printMenu();
        
    if (y==1)
    {
        cout << "Please input the name of the file with the messages to encode with the file extension (e.g. messages.txt):" << endl;
        cin >> fname;
        encodeMessageStream(fname);
        cout << "The messages have been successfully encoded; check the 'encodedMessages.txt' file." << endl;
    }
        
    if (y==2)
    {
        cout << "Please input the name of the file with the messages to decoded with the file extension (e.g. messages.txt):" << endl;
        cin >> fname;
        decodeMessageStream(fname);
        cout << "The messages have been successfully decoded; check the 'decodedMessages.txt' file." << endl;
    }
        
    }
    while (y!=3);
    
    return 0;
}

