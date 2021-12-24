#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <algorithm>
#pragma once

using namespace std;

class DBfile{
	private:
		//vector <string> params;
		vector <string> lines;

		static vector <string> fileNames;
		static string currentFileName;
		static string connectableFile;

		static vector<string> attachedFiles;
		static vector<string> toColumn;
		static vector<string> fileNameOfId;

		string fileName;

		void remakeFile();

	public:
		// Ñonstructors
		DBfile(string fileName);

		// Getters
		static vector<string> getFileNames();
		static string getCurrentFileName();
		static vector<string> getHeaderLine();
		static vector<string> getHeaderLine(string fileName);
		static vector<string> getAttachedFiles();
		static vector<string> getToColumn();
		static vector<string> getFileNameOfId();
		static int getNumberOfLines();
		static int getNumberOfLines(string fileName);

		// Setters
		void setCurrentFileName(string currentFileName) { this->currentFileName = currentFileName; }
		static void setConnection(string fileName, string columnName, string fileNameOfID);

		// Other functions
		static void openFile(string fileName);
		static void removeFile();
		static void addLine(vector<string> fields, vector<int> lengthFields);
		static bool isEmpty();
		static void showTable();
		static string getFirstLine();
		static void addColumn(string param, int widthCell);
		static void removeLine();
		static void removeColumn(vector<int> headerWordsLength);
		static void connectionBetweenFiles(string openableFile);
		static void checkRemoveInConnection();
		void makeFile(string currentFileName);
};
