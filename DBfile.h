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
		vector <string> params = {"Surname", "Name", "Patronymic", "Age", "Class"};
		vector <string> lines;

		static vector <string> fileNames;
		static string currentFileName;
		static vector<vector<string>> fileParams;

		string fileName;
		string name = "Name";
		string surname = "Surname";
		string patronymic = "Patronymic";
		string age = "Age";
		string cl = "Class";

		void remakeFile();

	public:
		// Ñonstructors
		DBfile(string fileName);

		// Getters
		static vector<string> getFileNames();
		static string getFileName();

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
		void makeFile(string currentFileName);

		/*
		void removeLine();
		void addColumn(string param);
		void removeColumn();*/
};
