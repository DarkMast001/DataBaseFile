#include "DBfile.h"

using namespace std;

// Definition variable
vector<string> DBfile::fileNames;
string DBfile::currentFileName = "No current file!";
vector<vector<string>> DBfile::fileParams;

// Constructors
DBfile::DBfile(string fileName) {
	ofstream fout;

	this->fileName = fileName;
	currentFileName = fileName;
	fileNames.push_back(fileName);

	fout.open(fileName + ".txt");
	fout.close();

	cout << "File successfully created!" << endl;
}

// Getters
vector <string> DBfile::getFileNames() { return fileNames; }
string DBfile::getFileName() { return currentFileName; }
vector<string> DBfile::getHeaderLine() {
	vector<string> headerLineWords;
	ifstream fin;
	string line, word;
	bool flag = false;
	fin.open(currentFileName + ".txt");
	getline(fin, line);
	for (int i = 5; i < line.size(); i++) {
		if (line[i] != ' ' || (line.size() - 1 == i)) {
			flag = false;
			word += line[i];
		}
		else if (!flag) {
			headerLineWords.push_back(word);
			word = "";
			flag = true;
		}
	}
	fin.close();
	return headerLineWords;
}

// Setters

// Other functions

//void DBfile::makeFile(string currentFileName) {
//	ofstream fout;
//
//	fileNames.push_back(currentFileName);
//	//fileParams[0].push_back(currentFileName);
//	this->currentFileName = currentFileName;
//
//	fout.open(currentFileName + ".txt");
//	fout << setw(5) << left << "id";
//	/*fout << setw(5) << left << "id" << setw(20) << left << "Surename" << setw(20) << left << "Name" << setw(20) << left
//		<< "Patronymic" << setw(5) << left << "Age" << setw(5) << left << "Class";*/
//	fout.close();
//	cout << "File successfully created!\n";
//}

void DBfile::openFile(string fileName) {
	currentFileName = fileName;
}

void DBfile::removeFile() {
	string fileName = currentFileName + ".txt";
	vector<string> tmp_names;

	remove(fileName.c_str());
	for (int i = 0; i < fileNames.size(); i++) {
		if (fileNames[i] == currentFileName) {
			fileNames.erase(fileNames.begin() + i);
			break;
		}
	}
	if (fileNames.empty()) currentFileName = "oops, you removed all files :)\n";
	else currentFileName = fileNames[0];
	cout << "File successfully removed!\n";
}

void DBfile::addLine(vector<string> fields, vector<int> lengthFields) {
	ofstream fout;
	fout.open(currentFileName + ".txt", ofstream::app);
	if (isEmpty()) {
		fout << setw(5) << left << "id";
		for (int i = 0; i < fields.size(); i++) {
			fout << setw(lengthFields[i]) << left << fields[i];
		}
		//fout << "\n";
	}
	else if (numberOfLines() >= 1) {
		fout << "\n";
		fout << setw(5) << left << numberOfLines();
		for (int i = 0; i < fields.size(); i++) {
			fout << setw(lengthFields[i]) << left << fields[i];
		}
		//fout << "\n";
	}
	fout.close();
	cout << "Line successfully added\n";
}

bool DBfile::isEmpty() {
	ifstream file(currentFileName + ".txt");
	return file.peek() == ifstream::traits_type::eof();
}

void DBfile::showTable() {
	ifstream fin;
	fin.open(currentFileName + ".txt");
	string currentLine;
	while (!fin.eof()) {
		getline(fin, currentLine);
		cout << currentLine << endl;
	}
	fin.close();
}

string DBfile::getFirstLine() {
	string line;

	ifstream fin;
	fin.open(currentFileName + ".txt");
	getline(fin, line);
	fin.close();
	return line;
}

int DBfile::numberOfLines() {
	string line;
	int counter = 0;

	ifstream fin;
	fin.open(currentFileName + ".txt");
	while (getline(fin, line))
		counter++;
	fin.close();
	return counter;
}

void DBfile::addColumn(string param, int widthCell) {
	vector<string> headerLineWords = getHeaderLine();
	string oldHeaderLineWords = getFirstLine();
	headerLineWords.push_back(param);
	string currentLine, newValue;

	ifstream fin;
	ofstream fout;
	fin.open(currentFileName + ".txt");
	fout.open(currentFileName + "_tmp.txt");
	for (int i = 0; i < numberOfLines(); i++) {
		getline(fin, currentLine);
		if (i == 0) {
			fout << currentLine << setw(widthCell) << left << param;
		}
		else {
			cout << "Value for last column of \"" + currentLine + "\" "; cin >> newValue;
			fout << "\n" << currentLine << setw(widthCell) << left << newValue;
		}
	}
	fout.close();
	fin.close();
	string tmpFileName = currentFileName + "_tmp.txt", name = currentFileName + ".txt";
	remove(name.c_str());
	rename(tmpFileName.c_str(), name.c_str());
	cout << "Column successfully added!\n";
}

//void DBfile::removeLine() {
//	ifstream fin;
//	fin.open(this->currentFileName);
//	string lastLine;
//	int counter = 0, tmpCounter = 0;
//	while (!fin.eof()) {
//		getline(fin, lastLine);
//		counter++;
//	}
//    fin.close();
//
//	ifstream foutMain;
//	ofstream foutNewMain;
//	string tmpLine;
//	foutMain.open(this->currentFileName.c_str());
//	foutNewMain.open("students_tmp.txt");
//	while (!foutMain.eof()) {
//		tmpCounter++;
//		if (tmpCounter == counter) {
//			break;
//		}
//		else {
//			getline(foutMain, tmpLine);
//			if(tmpCounter == 1)
//				foutNewMain << tmpLine;
//			else
//				foutNewMain << "\n" << tmpLine;
//		}
//	}
//	foutMain.close();
//	foutNewMain.close();
//
//	remove(this->currentFileName.c_str());
//	rename("students_tmp.txt", this->currentFileName.c_str());
//	cout << "Line successfully removed!\n";
//}
//
//
//void DBfile::remakeFile() {
//	ifstream fin;
//	fin.open(this->currentFileName.c_str());
//	string currentLine;
//	while (!fin.eof()) {
//		getline(fin, currentLine);
//		lines.push_back(currentLine);
//	}
//	fin.close();
//
//	ofstream newFout;
//	newFout.open("tmp_students.txt");
//
//	for (int i = 0; i < params.size(); i++) {
//		newFout << setw(20) << left << params[i];
//	}
//	for (int i = 1; i < lines.size(); i++) {
//		newFout << "\n" << lines[i];
//	}
//	lines.clear();
//	newFout.close();
//
//	remove("students.txt");
//	rename("tmp_students.txt", this->currentFileName.c_str());
//}
//
//	ofstream newFout;
//	newFout.open("tmp_students.txt");
//
//	for (int i = 0; i < params.size(); i++) {
//		newFout << setw(20) << left << params[i];
//	}
//	for (int i = 1; i < lines.size(); i++) {
//		newFout << "\n" << lines[i];
//	}
//	lines.clear();
//	newFout.close();
//
//	remove("students.txt");
//	rename("tmp_students.txt", "students.txt");*/
//}
//
//void DBfile::removeColumn() {
//	params.pop_back();
//	remakeFile();
//	cout << "Column successfully removed!\n";
//	/*ifstream fin;
//	fin.open("students.txt");
//	string currentLine;
//	while (!fin.eof()) {
//		getline(fin, currentLine);
//		lines.push_back(currentLine);
//	}
//	fin.close();
//
//	ofstream newFout;
//	newFout.open("tmp_students.txt");
//
//	for (int i = 0; i < params.size(); i++) {
//		newFout << setw(20) << left << params[i];
//	}
//	for (int i = 1; i < lines.size(); i++) {
//		newFout << "\n" << lines[i];
//	}
//	lines.clear();
//	newFout.close();
//
//	remove("students.txt");
//	rename("tmp_students.txt", "students.txt");*/
//}