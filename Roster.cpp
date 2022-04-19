// Roster.cpp
// Modified by James Fu, cs32-w22
// for lab03
#include "Roster.h"
#include <cstdlib>
#include <fstream>
#include <cassert>
#include <iostream> // for cout and cerr

Roster::Roster() {
  // initialize to empty array

  this->numStudents = 0;
  for (int i=0; i<ROSTER_MAX; i++) {
    this->students[i] = NULL;
  }

}

void Roster::resetRoster() {
 // To avoid memory leaks:
  //  Recycle memory for all allocated students on roster
  
  while (this->numStudents > 0) {
    delete this->students[this->numStudents - 1];
    this->numStudents --;
  }

}

void Roster::addStudentsFromFile(std::string filename) {
  std::ifstream ifs; // the stream we will use for the input file
  ifs.open(filename);
  
  if (ifs.fail()) {
    std::cerr << "Could not open input file: "
	      << filename << std::endl;
    exit(2); 
  }

  // ifs is an instance of ifstream
  // ifstream inherits from istream, 
  //   i.e. ifs is-a istream

  this->addStudentsFromStream(ifs);

}

void Roster::addStudentsFromStream(std::istream &is) {

  this->resetRoster();

  std::string thisLine;
  // Try to read past the header line.
  getline(is,thisLine);
  if ( is.eof() || is.fail() ) {
    std::cerr << "Unable to read first line of input stream" << std::endl;
    exit(3);
  }

  getline(is,thisLine);
  while (  !is.eof() && !is.fail() ) {
    // If we get here, it means the most recent attempt to read succeeded!
    // So do something with thisLine
    
    Student *sPtr = new Student(thisLine);
    this->students[this->numStudents] = sPtr;
    this->numStudents++;
    
    // try to read another line
    getline(is,thisLine);
  } // end while

}

int Roster::getNumStudents() const { 
  return numStudents;
}

Student Roster::getStudentAt(int index) const {
  if( index < 0 || index >= numStudents){
    std::cerr << "invalid index: " << index
    << " number of student is: " << numStudents << std::endl;
    exit(4);
  } 
  return *students[index];
}

std::string Roster::toString() const {
  std::string result = "{\n";
  
  for(int i = 0; i < numStudents; i++){
    result += students[i]->toString();
    if(i != numStudents - 1){
      result += ",";
    }
    result += "\n";
  }

  result += "}\n";
  return result;

}

void Roster::sortByPerm() {
  for(int i = numStudents; i > 1; i--){
    sortByPermHelper(i);
  }
}

int Roster::indexOfMaxPermAmongFirstKStudents(int k) const {
  if(k > this->numStudents){
    std::cerr << "invalid k: " << k << 
    " numStudent is: " << this->numStudents << std::endl;
  }
  int max = 0;
  int maxPerm = students[max]->getPerm();
  for(int i = 0; i < k; i++){
    int currentPerm = students[i]->getPerm();
    if(currentPerm > maxPerm){
      max = i;
      maxPerm = currentPerm;
    }
  }
  return max;
}

void Roster::sortByPermHelper(int k) {
  // swaps max perm from [0..k-1] with elem [k-1]
  int im = indexOfMaxPermAmongFirstKStudents(k);
  if(im == (k-1)){
    return;
  }
  Student* max = students[im];
  students[im] = students[k-1];
  students[k-1] = max;
}
