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

	cout << "Enter name file without .txt and special character, spaces and tabs: ";
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

void getCurrentFileName() {
	cout << DBfile::getCurrentFileName() << endl;
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
	bool isItConnectedFile = false;
	string fieldName, currentFileName = DBfile::getCurrentFileName();

	//if(DBfile::isEmpty(currentFileName))
	if (DBfile::getCurrentFileName() == "No current file!" || DBfile::getCurrentFileName() == "oops, you removed all files :)\n") {
		cout << "No files!" << endl;
	}
	else if(DBfile::numberOfLines() == 0){
		cout << "What count of fields should be in file: "; cin >> countFields;
		if (countFields == 0) {
			cout << "Uncorrent data!";
			return;
		}
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
		vector<string> columnsName; // Названия колонок
		vector<int> widthForWord; // Длина места в котором стоит слово
		int length, spaceCounter = 0;
		bool flag = false;

		string wordForColumn;
		vector<string> wordsForColumns;

		for (int i = 5; i < line.size(); i++) {
			if (line[i] != ' ' || (line.size() - 1 == i)) {
				if (line.size() - 1 == i) spaceCounter++;
				if (flag) {
					length = spaceCounter + columnsName.back().size();
					widthForWord.push_back(length);
					spaceCounter = 0;
				}
				flag = false;
				word += line[i];
			}
			else {
				if (!flag) {
					columnsName.push_back(word);
					word.clear();
					flag = true;
				}
				spaceCounter++;
			}
		}

		vector<string> attachedFiles = DBfile::getAttachedFiles();	// К какому файлу 
		vector<string> toColumn = DBfile::getToColumn();	// К какой калонке подключаем
		vector<string> fileNameOfId = DBfile::getFileNameOfId();	// Файл, который подключаем
		bool isExceptionWas = false;

		/*for(int i = 0; i < attachedFiles.size(); i++) cout << attachedFiles[i] << endl;
		for(int i = 0; i < toColumn.size(); i++) cout << toColumn[i] << endl;
		for(int i = 0; i < fileNameOfId.size(); i++) cout << fileNameOfId[i] << endl;*/


		for (int i = 0; i < columnsName.size(); i++) {
			cout << "Column \"" + columnsName[i] + "\": "; cin >> wordForColumn;
			if (find(attachedFiles.begin(), attachedFiles.end(), currentFileName) != attachedFiles.end()) {
				auto attachedFileIterator = find(attachedFiles.begin(), attachedFiles.end(), currentFileName);
				int attachedFilePos = distance(attachedFiles.begin(), attachedFileIterator);
				int maxID = DBfile::numberOfLines(fileNameOfId[attachedFilePos]) - 1;

				if (stoi(wordForColumn) >= 1 && stoi(wordForColumn) <= maxID) {
					if (wordForColumn.size() > widthForWord[i]) {
						cout << "Too long word\n";
						i--;
						continue;
					}
					else {
						wordsForColumns.push_back(wordForColumn);
					}
				}
				else {
					cout << "No such id in \"" << fileNameOfId[attachedFilePos] << "\"!\n";
					isExceptionWas = true;
				}
			}
			else {
				if (wordForColumn.size() > widthForWord[i]) {
					cout << "Too long word\n";
					i--;
					continue;
				}
				else {
					wordsForColumns.push_back(wordForColumn);
				}
			}
		}
		if (!isExceptionWas) DBfile::addLine(wordsForColumns, widthForWord);
		else cout << "Failed to add data. Try again.\n";
	}
}

void showTable() {
	if (DBfile::getCurrentFileName() == "No current file!") cout << "No files!" << endl;
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
	string currentFile = DBfile::getCurrentFileName();
	if (currentFile != "No current file!" || currentFile != "oops, you removed all files :)\n") {
		DBfile::removeLine();
	}
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

void connectionBetweenFiles() {
	string currentFile = DBfile::getCurrentFileName();
	string attachedFileName, fileNameOfId;
	vector<string> fileNames = DBfile::getFileNames();
	vector<string> toOpenFiles, columns;
	bool flag = false;

	cout << "What file column \"id\" you want to attach to the column: " << endl;
	showFiles();
	cout << "Write name of file: ";
	cin >> fileNameOfId;
	/*for (int i = 0; i < fileNames.size(); i++) {
		if (fileNameOfId == fileNames[i]) {
			flag = true;
			break;
		}
	}*/
	if (find(fileNames.begin(), fileNames.end(), fileNameOfId) != fileNames.end()) {
		cout << "To which file column you want to bind \"" << fileNameOfId << "\"" << endl;
		for (int i = 0; i < fileNames.size(); i++) {
			if (fileNames[i] != fileNameOfId) {
				cout << fileNames[i] << endl;
				toOpenFiles.push_back(fileNames[i]);
			}
		}
		//flag = false;
		string connectionColumn;
		cout << "Write name of file: ";
		cin >> attachedFileName;
		/*for (int i = 0; i < toOpenFiles.size(); i++) {
			if (attachedFileName == toOpenFiles[i]) {
				flag = true;
				break;
			}
		}*/
		if (find(toOpenFiles.begin(), toOpenFiles.end(), attachedFileName) != toOpenFiles.end()) {
			columns = DBfile::getHeaderLine(attachedFileName);
			if (!columns.empty()) {
				cout << "Which column of \"" << attachedFileName << "\" should you associate the id of the \"" << currentFile << "\"?\n";
				for (int i = 0; i < columns.size(); i++) {
					cout << columns[i] << endl;
				}
				cout << "Write name of column: ";
				cin >> connectionColumn;
				//flag = false;
				/*for (int i = 0; i < columns.size(); i++) {
					if (columns[i] == connectionColumn) {
						flag = true;
						break;
					}
				}*/
				if (find(columns.begin(), columns.end(), connectionColumn) != columns.end()) {
					DBfile::setConnection(attachedFileName, connectionColumn, fileNameOfId);
				}
				else cout << "No such column!\n";
			}
			else cout << "No columns!\n";
		}
		else cout << "No such file!\n";
	}
	else cout << "No such file!\n";
}

int main() {
	string request;
	string info = "To know how use it write - info\n";
	string instruction = "To make file write - make\nTo add line write - add line\nTo add column write - add column\n";
	string instruction2 = "To remove line write - remove line\nTo remove column write - remove column\nTo show table write - show\n";
	string instruction3 = "To see all list of created files write - file list\nTo see current opened file write - current\n";
	string instruction4 = "To make connection between files write - connect\n";
	string instruction5 = "To remove file write - remove\nTo exit write - exit\n";
	cout << info;
	while (true) {
		getline(cin, request);
		if (request == "exit") break;
		if (request == "info") cout << instruction << instruction2 << instruction3 << instruction4 << instruction5;
		if (request == "make") makeFile();
		if (request == "current") getCurrentFileName();
		if (request == "open") openFile();
		if (request == "remove") removeFile();
		if (request == "file list") showFiles();
		if (request == "add line") addLine();
		if (request == "show") showTable();
		if (request == "add column") addColumn();
		if (request == "remove line") removeLine();
		if (request == "remove column") removeColumn();
		if (request == "connect") connectionBetweenFiles();
	}
	return 0;
}