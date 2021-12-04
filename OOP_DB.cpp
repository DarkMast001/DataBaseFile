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
	if (DBfile::getFileName() == "No current file!") {
		cout << "No files!" << endl;
	}
	else if(DBfile::numberOfLines() == 0){
		cout << "What count of fields should be in file: "; cin >> countFields;
		for (int i = 0; i < countFields; i++) {
			cout << "Name of " << i + 1 << " field: "; cin >> fieldName; // getline(cin, fieldName);
			fields.push_back(fieldName);
			cout << "Length this field in file: "; cin >> lengthField;
			if (lengthField < fieldName.size()) {
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
		string line = DBfile::getFirstLine();
		int couter;
		for (int i = 0; i < line.size(); i++) {
			// Ќаписать алгоритм дл€ определени€ setw дл€ каждого слќва и словј
		}
	}
}

void showTable() {
	if (DBfile::getFileName() == "No current file!") cout << "No files!" << endl;
	else DBfile::showTable();
}

//void showTable() {
//	db.showTable();
//}
//
//void addLine() {
//	vector <string> lineParams;
//
//	string surname, name, patronymic, cl;
//	int age, id;
//	cout << "Surname: "; cin >> surname;
//	cout << "Name: "; cin >> name;
//	cout << "Patronymic: "; cin >> patronymic;
//	cout << "Age: "; cin >> age;
//	cout << "Class: "; cin >> cl;
//	//db.addLine(surname, name, patronymic, age, cl);
//}
//
//void addColumn() {
//	string columnName;
//	db.addColumn(columnName);
//}
//
//void removeLine() {
//	db.removeLine();
//}
//
//void removeColumn() {
//	db.removeColumn();
//}
//

int main() {
	string request;
	string info = "To know how use it write - info\n";
	string instruction = "To make file write - make\nTo add line write - add line\nTo add column write - add column\n";
	string instruction2 = "To remove line write - remove line\nTo remove column write - remove column\nTo show table write - show table\n";
	string instruction3 = "To see all list of created files write - file list\n";
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
		if (request == "show table") showTable();
		/*if (request == "add column") addColumn();
		if (request == "remove line") removeLine();
		if (request == "remove column") removeColumn();*/
	}
	return 0;
}