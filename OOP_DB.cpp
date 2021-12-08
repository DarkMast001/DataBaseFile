#include "DBfile.h";

using namespace std;

void showFiles() {
	vector<string> fileNames = DBfile::getFileNames();

	if (fileNames.empty()) cout << "No files!\n";
	else {
		for (int i = 0; i < fileNames.size(); i++) {
			cout << fileNames[i] << endl;
		}
	}
}

void makeFile() {
	vector <string> fileNames = DBfile::getFileNames();
	string fileName;
	bool flag = false;

	cout << "Enter name file without special character, spaces and tabs: ";
	cin >> fileName;
	if (fileNames.empty()) {
		DBfile db(fileName);
	}
	else {
		for (int i = 0; i < fileNames.size(); i++) {
			if (fileNames[i] == fileName) {
				flag = true;
				break;
			}
		}
		if (flag) cout << "File with such name already exists!\n";
		else DBfile db(fileName);
	}
}

void getFileName() {
	cout << DBfile::getFileName() << endl;
}

void openFile() {
	vector <string> fileNames = DBfile::getFileNames();
	string fileName;
	bool flag = false;

	if (fileNames.empty()) cout << "You haven't created any files\n";
	else if (fileNames.size() == 1) cout << "Your only file is already open\n";
	else {
		cout << "What file you want to open?\n";
		showFiles();
		cout << "Write the name of the file you want to open: "; cin >> fileName;
		for (int i = 0; i < fileNames.size(); i++) {
			if (fileNames[i] == fileName) {
				flag = true;
				break;
			}
		}
		if(flag) DBfile::openFile(fileName);
		else cout << "No such file exists!\n";
	}
}

void removeFile() {
	vector <string> fileNames = DBfile::getFileNames();
	string fileName;

	if (fileNames.empty()) cout << "You haven't created any files to remove\n";
	else DBfile::removeFile();
}

void addLine() {
	vector<string> fields;
	vector<int> lengthFields;
	int countFields, lengthField;
	string fieldName, currentFileName = DBfile::getFileName();

	//if(DBfile::isEmpty(currentFileName))
	if (DBfile::getFileName() == "No current file!" || DBfile::getFileName() == "oops, you removed all files :)\n") {
		cout << "No files!" << endl;
	}
	else if(DBfile::numberOfLines() == 0){
		cout << "What count of fields should be in file: "; cin >> countFields;
		for (int i = 0; i < countFields; i++) {
			cout << "Name of " << i + 1 << " field: "; cin >> fieldName; // getline(cin, fieldName);
			fields.push_back(fieldName);
			cout << "Length this field in file: "; cin >> lengthField;
			if (lengthField <= fieldName.size()) {
				cout << "Too short length!\n";
				fields.pop_back();
				i--;
				continue;
			}
			else {
				lengthFields.push_back(lengthField);
			}
		}
		DBfile::addLine(fields, lengthFields);
	}
	else {
		string line = DBfile::getFirstLine(), word;
		vector<string> words; // Слова
		vector<int> widthForWord; // Длина места в котором стоит слово
		int length, spaceCounter = 0;
		bool flag = false;

		string wordForColumn;
		vector<string> wordsForColumns;

		for (int i = 5; i < line.size(); i++) {
			if (line[i] != ' ' || (line.size() - 1 == i)) {
				if (line.size() - 1 == i) spaceCounter++;
				if (flag) {
					length = spaceCounter + words.back().size();
					widthForWord.push_back(length);
					spaceCounter = 0;
				}
				flag = false;
				word += line[i];
			}
			else {
				if (!flag) {
					words.push_back(word);
					word.clear();
					flag = true;
				}
				spaceCounter++;
			}
		}

		/*for (int i = 0; i < widthForWord.size();  i++) {
			cout << widthForWord[i] << " ";
		}
		cout << endl;*/

		for (int i = 0; i < words.size(); i++) {
			cout << "Column \"" + words[i] + "\": "; cin >> wordForColumn;
			if (wordForColumn.size() > widthForWord[i]) {
				cout << "Too long word\n";
				i--;
				continue;
			}
			else {
				wordsForColumns.push_back(wordForColumn);
			}
		}

		DBfile::addLine(wordsForColumns, widthForWord);
	}
}

void showTable() {
	if (DBfile::getFileName() == "No current file!") cout << "No files!" << endl;
	else DBfile::showTable();
}

void addColumn() {
	string param;
	int widthCell;
	cout << "Enter the name of new column: "; cin >> param;
	cout << "Enter the width for \"" + param + "\": "; cin >> widthCell;
	if (widthCell <= param.size()) {
		cout << "Too short length! Try again\n";
	}
	else {
		DBfile::addColumn(param, widthCell);
	}
}

void removeLine() {
	// Добавить проверку на удалённый файл
	DBfile::removeLine();
}

void removeColumn() {
	string line = DBfile::getFirstLine(), word;
	vector<string> words; // Слова
	vector<int> widthForWord; // Длина места в котором стоит слово
	int length, spaceCounter = 0;
	bool flag = false;

	for (int i = 5; i < line.size(); i++) {
		if (line[i] != ' ' || (line.size() - 1 == i)) {
			if (line.size() - 1 == i) spaceCounter++;
			if (flag) {
				length = spaceCounter + words.back().size();
				widthForWord.push_back(length);
				spaceCounter = 0;
			}
			flag = false;
			word += line[i];
		}
		else {
			if (!flag) {
				words.push_back(word);
				word.clear();
				flag = true;
			}
			spaceCounter++;
		}
	}

	DBfile::removeColumn(widthForWord);
}

int main() {
	string request;
	string info = "To know how use it write - info\n";
	string instruction = "To make file write - make\nTo add line write - add line\nTo add column write - add column\n";
	string instruction2 = "To remove line write - remove line\nTo remove column write - remove column\nTo show table write - show\n";
	string instruction3 = "To see all list of created files write - file list\nTo see current opened file write - current\n";
	string instruction4 = "To remove file write - remove\nTo exit write - exit\n";
	cout << info;
	while (true) {
		getline(cin, request);
		if (request == "exit") break;
		if (request == "info") cout << instruction << instruction2 << instruction3 << instruction4;
		if (request == "make") makeFile();
		if (request == "current") getFileName();
		if (request == "open") openFile();
		if (request == "remove") removeFile();
		if (request == "file list") showFiles();
		if (request == "add line") addLine();
		if (request == "show") showTable();
		if (request == "add column") addColumn();
		if (request == "remove line") removeLine();
		if (request == "remove column") removeColumn();
	}
	return 0;
}