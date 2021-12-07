#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <vector>
#include <stdio.h>
#pragma once

using namespace std;

class DBfile{
	private:
		//vector <string> params;
		vector <string> lines;

		static vector <string> fileNames;
		static string currentFileName;
		static vector<vector<string>> fileParams;

		string fileName;

		void remakeFile();

	public:
		// �onstructors
		DBfile(string fileName);

		// Getters
		static vector<string> getFileNames();
		static string getFileName();
		static vector<string> getHeaderLine();

		// Setters
		void setCurrentFileName(string currentFileName) { this->currentFileName = currentFileName; }

		// Other functions
		static void openFile(string fileName);
		static void removeFile();
		static void addLine(string surname, string name, string patronymic, int age, string cl);
		static void addLine(vector<string> fields, vector<int> lengthFields);
		static bool isEmpty();
		static void showTable();
		static string getFirstLine();
		static int numberOfLines();
		static void addColumn(string param, int widthCell);
		void makeFile(string currentFileName);

		/*
		void removeLine();
		void removeColumn();*/
};
