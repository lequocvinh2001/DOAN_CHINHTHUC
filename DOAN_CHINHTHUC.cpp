// DOAN_CHINHTHUC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include "DictionaryTree.hpp"

#define ABSOLUTE_PATH "E:\\DO AN CNTT\\DOAN_CHINHTHUC\\"

using namespace std;

void waitForEnter()
{
	cout << "NHAN ENTER DE TIEP TUC!...";
	cin.get();
}

template<class T>
void exportToFileInput(string filename, DictionaryTree<T>& dt)
{
#ifdef ABSOLUTE_PATH
	filename = ABSOLUTE_PATH + filename;
#endif
	ofstream ofs(filename);
	string str;

	if (ofs.fail()) {
		cout << "LOI MO FILE!" << endl;
	}

	traverse(dt.getRoot(), ofs);
	ofs.close();

}

template<typename T>
int insertTu(string filename, DictionaryTree<T> &dt)
{
	T word, meaning;
	WordNode<string>* wn;

	cout << "NHAP TU CAN THEM VAO CAY: ";
	getline(cin, word);
	cout << "NHAP NGHIA: ";
	getline(cin, meaning);

	wn = dt.search(word);
	if (wn) {
		cout << word << " DA CO TRONG TU DIEN!" << endl;
		return -1;
	}

	dt.insert(word, meaning);
	
	exportToFileInput(filename, dt);
	return 0;
}


template<class T>
int importFromFile(string filename, DictionaryTree<T>& dt)
{
#ifdef ABSOLUTE_PATH
	filename = ABSOLUTE_PATH + filename;
#endif
	ifstream ifs(filename);
	string str;

	if (ifs.fail()) {
		cout << "LOI MO FILE!" << endl;
		return -1;
	}

	while (getline(ifs, str)) {
		T word, meaning;

		istringstream iss(str);
		getline(iss, word, ';');
		getline(iss, meaning);
		dt.insert(word, meaning);
	}

	ifs.close();
	return 0;
}

template<class T>
void traverse(WordNode<T>* root, ostream& os) //duyet theo kieu LNR
{
	if (root->hasLeft())
		traverse(root->getLeft(), os);

	os << root->getWord() << ";";
	os << root->getMeaning() << std::endl;

	if (root->hasRight())
		traverse(root->getRight(), os);
}

template<class T>
int exportToFile(string filename, DictionaryTree<T>& dt)
{
#ifdef ABSOLUTE_PATH
	filename = ABSOLUTE_PATH + filename;
#endif
	ofstream ofs(filename);
	string str;

	if (ofs.fail()) {
		cout << "LOI MO FILE!" << endl;
		return -1;
	}

	traverse(dt.getRoot(), ofs);
	ofs.close();
	return 0;
}


int main()
{
	DictionaryTree<string> dt;
	int choice;
	
	lable:
	do {
		string word, meaning;
		WordNode<string>* wn;

		cout << "\n|=========================== TU DIEN ANH-VIET ===========================|";
		cout << "\n|---------------|      1. CAP NHAT DU LIEU TU FILE TXT   |---------------|";
		cout << "\n|---------------|      2. TIM KIEM MOT TU                |---------------|";
		cout << "\n|---------------|      3. THAY DOI NGHIA CUA TU          |---------------|";
		cout << "\n|---------------|      4. XOA 1 TU TRONG TU DIEN         |---------------|";
		cout << "\n|---------------|      5. THEM 1 TU VAO TU DIEN          |---------------|";
		cout << "\n|---------------|      6. XUAT TAT CAC TU TRONG TU DIEN  |---------------|";
		cout << "\n|---------------|      7. XUAT FILE DU LIEU TU DIEN      |---------------|";
		cout << "\n|---------------|      8. XOA MAN HINH                   |---------------|";
		cout << "\n|---------------|      9. THOAT KHOI CHUONG TRINH        |---------------|";
		cout << "\n|============================  MOI BAN CHON  ============================|";
		cout << "\nHAY NHAP LUA CHON: ";
		cin >> choice;
		cin.ignore();

		if (choice > 1 && choice < 9) {
			if (dt.getRoot() == NULL) {
				cout << "CHUA NHAP DU LIEU! DANG TIEN HANH NHAP DU LIEU..." << endl;
				choice = 1;
			}
		}

		cout << endl << endl;
		switch (choice) {
		case 1://nhap file
			if (!importFromFile("dict.txt", dt))
				cout << "NHAP DU LIEU THANH CONG! ";
			waitForEnter();
			break;
		case 2://search
			cout << "NHAP TU CAN TRA: ";
			getline(cin, word);

			wn = dt.search(word);
			if (!wn) {
				cout << word << " KHONG TON TAI!" << endl;
				waitForEnter();
				break;
			}
			cout << "TU: " << wn->getWord() << endl;
			cout << "NGHIA: " << wn->getMeaning() << endl;
			waitForEnter();
			break;
		case 3://edit
			cout << "NHAP TU CAN TRA: ";
			getline(cin, word);

			wn = dt.search(word);
			if (!wn) {
				cout << word << " KHONG TON TAI!" << endl;
				waitForEnter();
				break;
			}

			cout << "TU BAN DA CHON: " << wn->getWord() << endl;
			cout << "DAY LA NGHIA BAN DAU: " << wn->getMeaning() << endl;
			cout << "NHAP MOT NGHIA MOI (NEU KHONG-NHAN 'ENTER' DE BO QUA!): ";
			getline(cin, meaning);

			if (meaning.length() != 0) {
				dt.modify(word, meaning);
				cout << "CHINH SUA THANH CONG!";
				waitForEnter();
			}
			break;
		case 4://xoa
			cout << "NHAP TU DE XOA: ";
			getline(cin, word);

			wn = dt.search(word);
			if (!wn) {
				cout << word << " KHONG TON TAI!" << endl;
				waitForEnter();
				break;
			}

			dt.remove(word);
			exportToFileInput("dict.txt", dt);
			cout << "XOA THANH CONG!";
			waitForEnter();
			break;
		case 5:
			//chen tu vao node
			if (!insertTu("dict.txt", dt))
				cout << "THEM TU THANH CONG!" << endl;
			waitForEnter();
			break;
		case 6://print all
			dt.print();
			waitForEnter();
			break;
		case 7://print file to file
			if (!exportToFile("out.txt", dt))
				cout << "XUAT DU LIEU RA FILE THANH CONG VUI LONG KIEM TRA!" << endl;
			waitForEnter();
			break;
		case 8:
			system("cls");
			waitForEnter();
			break;
		case 9://thoat
			cout << "CAM ON BAN DA SU DUNG TU DIEN ANH - VIET!" << endl;
			break;
		default:
			cout << "KHONG HOP LE! VUI LONG NHAP LAI!" << endl;
			goto lable;
		}
		cout << endl << endl;
	} while (choice > 0 && choice < 9);

	return 0;
}