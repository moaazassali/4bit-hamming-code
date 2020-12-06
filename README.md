# 4bit-hamming-code

The objective of this project is to design a “hamming code” software that detects and corrects errors while the data is being transmitted over unreliable networks. The software asks the user to choose the function desired: encoding, decoding or exiting the program. Then, it asks the user to input the name of the file that contains the messages. Then, if the user chose to encode, the program would encode the 4-bit messages provided from the file by embedding 3 parity bits into specific positions. The program would then print the encoded messages and generate a file containing them. Otherwise, if the user chose to decode messages, the program would identify whether each message has an error, correct it,provide the position of the bit that was incorrectand print the originaldecoded message. Finally,it would print that information to the user and write it into a file.
