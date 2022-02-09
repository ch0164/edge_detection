/* File: main.cpp */

#include <iostream>
#include <fstream>

using namespace std;

int main(void) {
    //std::cout << "Hello, world!" << std::endl;

    char buffer[3];

    short magicno;
    int ifdaddress;
    short ifdcount;


    ifstream imfile;
    imfile.open("pooh.tif",ios::binary);

    imfile.seekg(0,ios::beg);

    imfile.read(buffer,2);
    imfile.read((char*)&magicno, 2);
    imfile.read((char*)&ifdaddress, 4);

    imfile.seekg(ifdaddress, ios::beg);
    imfile.read((char*)&ifdcount, 2);

    imfile.close();

    buffer[2]='\0';


    cout<<"Endian: "<<buffer<<endl;
    cout<<"Magic: "<<magicno<<endl;
    cout<<"IFD Address: "<<ifdaddress<<endl;
    cout<<"IFD CountL "<<ifdcount<<endl;

    return 0;
}