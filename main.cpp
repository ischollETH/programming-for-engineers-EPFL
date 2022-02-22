#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <stdlib.h>
using namespace std;
/*
    Pix2Pos.cpp

    searches positions of two pucks and writes them into a text file

    reads from file "bitmap.bin" the pixels of a picture and looks for two pucks of different colour (0 and 1)
    and checks their positions. If no error occurs and all the data is valid the program saves the positions of
    the pucks into a file, called "pos.txt", in the following form:
    0, column, row
    1, column, row
    where 0 and 1 are the colours of the two pucks respectively.

    Version 8.2

    © by M.Zemp, I.Scholl GM BA2
*/
//universal variables
vector<vector<unsigned int> > pixel;                                        //for saving pixels
int pos_1_column (-1), pos_1_row (-1), pos_2_column (-1), pos_2_row (-1);   //for saving positions
unsigned int largeur(0), hauteur(0);                                        //for dimensions of picture
//prototypes:
    int Nmbr_Pixel();                                   //checks if number of pixels is valid
    int Import_Pixels();                                //opens "bitmap.bin", checks first for values and imports pixels into vector of vectors "pixel"
    int Check_Puck1(int i, int j);                      //checks if 5x5 pattern is fulfilled for colour 1 (0)
    int Check_Puck2(int i, int j);                      //checks if 5x5 pattern is fulfilled for colour 2 (1)
    int Save_Pos(int i, int j, int colour);             //saves found and validated positions into variables inside program
    int Write_Pos(int P1l, int P1r, int P2l, int P2r);  //writes saved coordinates into "pos.txt"
    int Check_Pos(int P1l, int P1r, int P2l, int P2r);  //checks if positions of two pucks are valid

//main program
main() {
    //import pixels
    vector<unsigned int> line;
    if (Import_Pixels() == 0) return 0; //error while importing pixels from file -> stop
    else                                //importing okay
    //check colours, search for pucks
    for (int i(0); i<(pixel.size()-4); i++)  //go through rows
    {
        line = pixel.at(i);
        for (int j(0); j<(line.size()); j++) //go through lines
        {
            //check for colour 1 (0)
            if (0 == line.at(j)) {
                int tmp = Check_Puck1(i, j);
                if(tmp == -1) exit(7); //two pucks of same colour found -> stop
                else if (tmp == 1) //position found
                    if (Save_Pos(i, j, 0) == 0) {cerr<<"error: could not save positions of puck 1 (0)"<<endl; //error while saving positions -> stop
                                                 exit(9); }
            }
            //check for colour 2 (1)
            if (1 == line.at(j)) {
                int tmp = Check_Puck2(i, j);
                if(tmp == -1) exit(8); //two pucks of same colour found -> stop
                else if (tmp == 1) //position found
                    if (Save_Pos(i, j, 1) == 0) {cerr<<"error: could not save positions of puck 2 (1)"<<endl; //error while saving positions -> stop
                                                 exit(10); }
            }
            else continue; //5x5 pattern not valid, or colour of pixel not right
        }
    } //searched whole pixmap
    //Check positions of pucks
    if (Check_Pos(pos_1_column, pos_1_row, pos_2_column, pos_2_row) == 0) exit(11); //not valid -> stop
    //writing into "pos.txt"
    if (Write_Pos(pos_1_column, pos_1_row, pos_2_column, pos_2_row) == 0) exit(12); //error with writing -> stop
    cout<<"success"<<endl; //file searched without error
    return 0;
}

//function declarations:
  //reads from pixmap.bin and checks data of first four values
    int Import_Pixels() {
        ifstream leser;
        vector<unsigned int> line;
        unsigned int zwsp(0);
        //crate link and open file
        leser.open("pixmap.bin", ios::binary);
        if (leser.fail()) {cerr<<"error: not able to open file 'pixmap.bin"<<endl; //opening error -> stop
                           exit(1); }
        else
        //saving and checking first 4 values
        leser.read(reinterpret_cast<char*>(&zwsp), sizeof(zwsp));
        if (leser.fail()) {cerr<<"error: not able to read in file 'pixmap.bin"<<endl; //reading error -> stop
                           exit(2); }
        else if (zwsp < 10 || zwsp > 1000) {cerr<<"error: largeur not valid"<<endl; //largeur valid? if not -> stop
                                            exit(3); }
        else
        largeur = zwsp;
        leser.read(reinterpret_cast<char*>(&zwsp), sizeof(zwsp));
        if (zwsp < 10 || zwsp > 1000) {cerr<<"error: hauteur not valid"<<endl; //hauteur valid? if not -> stop
                                       exit(4); }
        else
        hauteur = zwsp;
        leser.read(reinterpret_cast<char*>(&zwsp), sizeof(zwsp));
        if (zwsp != 0) cerr<<"warning: colour 1 (0) not correct"<<endl; //colour 1 (0) valid? if not -> warning
        else
        leser.read(reinterpret_cast<char*>(&zwsp), sizeof(zwsp));
        if (zwsp != 1) cerr<<"warning: colour 2 (1) not correct"<<endl; //colour 2 (1) valid? if not -> warning
        else
        //checking if number of pixels valid
        if (0 == Nmbr_Pixel()) {cerr<<"error: too few pixels"<<endl; //not enough pixels -> stop
                                exit(5); }
        else
        //read pixels into "pixel"
        for (int i(0); i<hauteur; i++) {
            for (int j(0); j<largeur; j++) {
                leser.read(reinterpret_cast<char*>(&zwsp), sizeof(zwsp));
                if (zwsp < 0 || zwsp > 255) cerr<<"warning: pixel not valid"<<endl; //pixel valid? if not -> warning
                line.push_back(zwsp);
            }
            pixel.push_back(line);
            line.clear();
        } //imported whole pixmap
        leser.close();  //closes file
            if (leser.fail()){cout<<"error: not able to close file"<<endl; //closing problem -> stop
                              exit(6); }
        return 1; //success, all values okay and pixels imported
    }

  //check if 5x5 structure for colour 1 (0) -> 1 if correct, 0 if not, -1 if two pucks
    int Check_Puck1(int i, int j) {
        vector<unsigned int> line;
        line = pixel.at(i);
        if (0==line.at(j+1)
         && 0==line.at(j+2)
         && 0==line.at(j+3)
         && 0==line.at(j+4))
         {
            line = pixel.at(i+1);
            if (0==line.at(j)
             && 0==line.at(j+1)
             && 0==line.at(j+2)
             && 0==line.at(j+3)
             && 0==line.at(j+4))
             {
                line = pixel.at(i+2);
                if (0==line.at(j)
                 && 0==line.at(j+1)
                 && 0==line.at(j+2)
                 && 0==line.at(j+3)
                 && 0==line.at(j+4))
                 {
                    line = pixel.at(i+3);
                    if (0==line.at(j)
                     && 0==line.at(j+1)
                     && 0==line.at(j+2)
                     && 0==line.at(j+3)
                     && 0==line.at(j+4))
                     {
                        line = pixel.at(i+4);
                        if (0==line.at(j)
                         && 0==line.at(j+1)
                         && 0==line.at(j+2)
                         && 0==line.at(j+3)
                         && 0==line.at(j+4))
                         {
                            if (pos_1_column != -1 && pos_1_row != -1) {cerr<<"error: two pucks of colour 1 (0)"<<endl; //two pucks -> stop
                                                                        return -1; }
                            else
                            return 1; //success
                         }
                     }
                 }
             }
         }
    return 0; //structure not correct
    }

  //check if 5x5 structure for colour 2 (1) -> 1 if correct, 0 if not, -1 if two pucks
    int Check_Puck2(int i, int j) {
        vector<unsigned int> line;
        line = pixel.at(i);
        if (1==line.at(j+1)
         && 1==line.at(j+2)
         && 1==line.at(j+3)
         && 1==line.at(j+4))
         {
            line = pixel.at(i+1);
            if (1==line.at(j)
             && 1==line.at(j+1)
             && 1==line.at(j+2)
             && 1==line.at(j+3)
             && 1==line.at(j+4))
             {
                line = pixel.at(i+2);
                if (1==line.at(j)
                 && 1==line.at(j+1)
                 && 1==line.at(j+2)
                 && 1==line.at(j+3)
                 && 1==line.at(j+4))
                 {
                    line = pixel.at(i+3);
                    if (1==line.at(j)
                     && 1==line.at(j+1)
                     && 1==line.at(j+2)
                     && 1==line.at(j+3)
                     && 1==line.at(j+4))
                     {
                        line = pixel.at(i+4);
                        if (1==line.at(j)
                         && 1==line.at(j+1)
                         && 1==line.at(j+2)
                         && 1==line.at(j+3)
                         && 1==line.at(j+4))
                         {
                            if (pos_2_column != -1 && pos_2_row != -1) {cerr<<"error: two pucks of colour 2 (1)"<<endl; //two pucks found -> stop
                                                                        return -1; }
                            else
                            return 1; //success
                         }
                     }
                 }
             }
         }
    return 0; //structure not correct
    }

  //save positions into variables inside program
    int Save_Pos(int i, int j, int colour) {
        if (colour == 0)
        {   pos_1_column = j+2;
            pos_1_row = hauteur - (i+3); //inverse to centre on lower left side
            return 1;
        }
        else if (colour == 1)
        {   pos_2_column = j+2;
            pos_2_row = hauteur - (i+3); //inverse to centre on lower left side
            return 1;
        }
        else return 0;
    }

  //check if bitmap.bin has correct number of pixels
    int Nmbr_Pixel(){
    /*
    in order to do this we run through the document with separate variables in order not to overwrite the main ones.
    the document is being read until the end, and then the number of pixels is compared to the value hauteur*largeur
    if it is too small there are too few pixels -> stop
    if it is too large it's no problem -> warning
    */
        int i(0);
        unsigned int zwsp2(0);
        ifstream leser2;
        leser2.open("pixmap.bin", ios::binary); //creates link to file
        if (leser2.fail()) {cerr<<"error: not able to open file 'pixmap.bin'"<<endl; //tests opening
                            exit(1); }
        else
        while (!leser2.eof()) { //goes through whole file
            i++;
            leser2.read(reinterpret_cast<char*>(&zwsp2), sizeof(zwsp2));
        }
        i -= 5; //-4 first values -1 because while-loop is done again after condition is satisfied
        if (i == largeur*hauteur) return 1; //everything okay
        else if (i > largeur*hauteur) {cerr<<"warning: too many pixels"<<endl; //too many pixels -> warning
                                       return 1; }
        else return 0; //too few pixels -> stop
    }

  //check if positions of pucks are valid
    int Check_Pos(int P1l, int P1r, int P2l, int P2r) {
        if (abs(P1l-P2l) < 5 && abs(P1r-P2r) == 5) {cerr<<"error: positions of pucks not valid"<<endl; //pucks are side-by-side -> stop
                                                   return 0; }
        else if (abs(P1r-P2r) < 5 && abs(P1l-P2l) == 5) {cerr<<"error: positions of pucks not valid"<<endl; //pucks are side-by-side -> stop
                                                        return 0; }
        else return 1; //everything okay
    }

  //write position in pos.txt
    int Write_Pos(int P1l, int P1r, int P2l, int P2r) {
        ofstream schreiber("pos.txt"); //create or open file
        if (schreiber.fail()) {cerr<<"error: not able to open/create file 'pos.txt'"<<endl; //opening or creating problem -> stop
                               return 0; }
        else
        schreiber<<"0,"<<P1l<<","<<P1r<<endl;
        schreiber<<"1,"<<P2l<<","<<P2r<<endl;
        schreiber.close();
        if (schreiber.fail()) {cerr<<"error: not able to close file 'pos.txt'"<<endl; //closing problem -> stop
                               return 0; }
        else return 1; //writing successful
    }
