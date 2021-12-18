#include "DBfile.h"

using namespace std;

// Definition variable
vector<string> DBfile::fileNames;
string DBfile::currentFileName = "No current file!";
vector<string> DBfile::attachedFiles;
vector<string> DBfile::toColumn;
vector<string> DBfile::fileNameOfId;

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
string DBfile::getCurrentFileName() { return currentFileName; }
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
vector<string> DBfile::getHeaderLine(string fileName) {
	vector<string> headerLineWords;
	ifstream fin;
	string line, word;
	bool flag = false;
	fin.open(fileName + ".txt");
	getline(fin, line);
	line += " ";
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
string DBfile::getFirstLine() {
	string line;

	ifstream fin;
	fin.open(currentFileName + ".txt");
	getline(fin, line);
	fin.close();
	return line;
}
vector<string> DBfile::getAttachedFiles() {
	return attachedFiles;
}
vector<string> DBfile::getToColumn() {
	return toColumn;
}
vector<string> DBfile::getFileNameOfId() {
	return fileNameOfId;
}

// Setters
void DBfile::setConnection(string fileName, string columnName, string fileNameOfID) {
	attachedFiles.push_back(currentFileName);
	toColumn.push_back(columnName);
	fileNameOfId.push_back(fileNameOfID);
	cout << "You successfully connected files!\n";
}

// Other functions
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

	if (find(attachedFiles.begin(), attachedFiles.end(), currentFileName) != attachedFiles.end()) {
		auto iterator = find(attachedFiles.begin(), attachedFiles.end(), currentFileName);
		int index = distance(attachedFiles.begin(), iterator);

		attachedFiles.erase(attachedFiles.begin() + index);
		toColumn.erase(toColumn.begin() + index);
		fileNameOfId.erase(fileNameOfId.begin() + index);
	}
	else if (find(fileNameOfId.begin(), fileNameOfId.end(), currentFileName) != fileNameOfId.end()) {
		auto iterator = find(fileNameOfId.begin(), fileNameOfId.end(), currentFileName);
		int index = distance(fileNameOfId.begin(), iterator);

		attachedFiles.erase(attachedFiles.begin() + index);
		toColumn.erase(toColumn.begin() + index);
		fileNameOfId.erase(fileNameOfId.begin() + index);
	}

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

int DBfile::numberOfLines(string fileName) {
	string line;
	int counter = 0;

	ifstream fin;
	fin.open(fileName + ".txt");
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

void DBfile::removeLine() {
	ifstream foutMain;
	ofstream foutNewMain;
	string tmpLine;
	int tmpCounter = 0;
	int numberOfLine = numberOfLines();
	foutMain.open(currentFileName + ".txt");
	foutNewMain.open(currentFileName + "_tmp.txt");
	while (!foutMain.eof()) {
		tmpCounter++;
		if (tmpCounter == numberOfLine) {
			break;
		}
		else {
			getline(foutMain, tmpLine);
			if(tmpCounter == 1)
				foutNewMain << tmpLine;
			else
				foutNewMain << "\n" << tmpLine;
		}
	}
	foutMain.close();
	foutNewMain.close();

	remove((currentFileName + ".txt").c_str());
	rename((currentFileName + "_tmp.txt").c_str(), (currentFileName + ".txt").c_str());
	cout << "Line successfully removed!\n";
}

void DBfile::removeColumn(vector<int> headerWordsLength) {
	vector <string> lines;
	ifstream fin;
	fin.open(currentFileName + ".txt");
	string currentLine;
	while (!fin.eof()) {
		getline(fin, currentLine);
		lines.push_back(currentLine);
	}
	fin.close();

	ofstream newFout;
	newFout.open(currentFileName + "_tmp.txt");

	for (int i = 0; i < lines.size(); i++) {
		lines[i].resize(lines[i].size() - headerWordsLength.back());
		newFout << lines[i] << "\n";
	}
	newFout.close();

	remove((currentFileName + ".txt").c_str());
	rename((currentFileName + "_tmp.txt").c_str(), (currentFileName + ".txt").c_str());
	headerWordsLength.clear();
	cout << "Column successfully removed!\n";
}

void DBfile::connectionBetweenFiles(string openableFile) {
	
}

void DBfile::checkRemoveInConnection() {
	for (int i = 0; i < attachedFiles.size(); i++) {
		if (currentFileName == attachedFiles[i]) {

		}
	}
}
