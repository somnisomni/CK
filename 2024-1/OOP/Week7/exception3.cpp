#include <iostream>
#include <fstream>
using namespace std;

class FileException: public exception {
  private:
    string fileName;
    string errorMsg;
  protected:
    void setErrorMessage(string msg) {
      errorMsg = msg;
    }
  public:
    FileException(string fileName): fileName(fileName) { }
    virtual const char* what() const noexcept override {
      return errorMsg.c_str();
    }
    string getFileName() const noexcept {
      return fileName;
    }
};

class FileOpenException: public FileException {
  private:
    string fileName;
    string errorMsg;
  public:
    FileOpenException(string fileName): FileException(fileName) {
      setErrorMessage("Error openError: " + fileName);
    }
};

class FileReadException: public FileException {
  private:
    string fileName;
    int line;
    string errorMsg;
  public:
    FileReadException(string fileName, int line): FileException(fileName), line(line) {
      setErrorMessage("Error readError: " + fileName);
    }
};

string findAcePlayerNameExt(string fileName) {
  string data;
  ifstream fileStream;
  fileStream.open(fileName);

  if(fileStream.fail()) {
    throw FileOpenException(fileName);
  }

  int readLine = 0;
  if(fileStream.is_open()) {
    while(!fileStream.eof()) {
      if(!getline(fileStream, data)) {
        readLine++;
        throw FileReadException(fileName, readLine);
      }
    }

    fileStream.close();
  }
}

int main() {
  try {
    findAcePlayerNameExt("a.txt");
  } catch(const FileOpenException &e) {
    cout << "FileOpenException caught: " << e.what() << endl;
  } catch(const FileReadException &e) {
    cout << "FileReadException caught: " << e.what() << endl;
  } catch(...) {
    cout << "Exception caught" << endl;
  }
}
