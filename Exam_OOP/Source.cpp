#include "Test.h"
void main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Student St;
	Administrator Ad;
	Test T;
	int MainMenu;
	do {
		cout << "�������� ������� ������\n";
		cout << "1 - ������������:\n";
		cout << "2 - �������������:\n";
		cin >> MainMenu;
		cin.ignore();
		switch (MainMenu) {
		case 1: {
			int StudMenu;


			do {
				cout << "Welcome student!\n";
				cout << "1 - ����������� ������������:\n";
				cout << "2 - ����c������ ������������:\n";
				cout << "3 - ������ ����:\n";
				cout << "4 - ����������� ����������:\n";
				cout << "0 - �����: \n";
				cin >> StudMenu;
				cin.ignore();
				switch (StudMenu)
				{
				case 1: {
					St.AutorizationSt();
					break;
				}
				case 2: {

					St.Registration();
					St.RegisLogPas();
					break;
				}

				case 3: {
					string buf, Category;
					cout << "�������� ���������:\n";						
					ifstream fin("Categories.txt", ios_base::in);
					while (!fin.eof())
					{
						getline(fin, buf);						
					}
					getline(cin, Category);	
					fin.close();
					string buf2, TestName;
					cout << "�������� ����:\n";					
					getline(cin, TestName);
					ifstream fin2("Tests_name.txt", ios_base::in);						
					St.PassTest(TestName);	
					fin2.close();
					break;

				}
				case 4: {

					ifstream fin(St.GetLogin() + "_result_Of_test.txt", ios_base::in);
					string buf;
					while (!fin.eof())
					{
						fin >> buf;
						cout << "����: " << buf << endl;
						fin >> buf;
						cout << "���������� ������� �� " << buf << " ��������\n";
						fin >> buf;
						cout << "��� " << buf << "%\n";
						fin >> buf;
						cout << "���� ������ - " << buf << endl;
					}
					fin.close();
					break;
				}
				}

			} while (StudMenu != 0);
		}
		case 2: {
			int AdminMenu;
			do {
				cout << "Welcome Admin:\n";
				cout << "1 - ����������� ������\n";
				cout << "2 - ����������� ������\n";
				cout << "3 - �������� ���� ����� � ������:\n";
				cout << "4 - �������� ������ ���������:\n";
				cout << "5 - ������� ������ � ��������:\n";
				cout << "6 - ������� ������ ��������\n";
				cout << "7 - �������� ������ � ��������:\n";
				cout << "8 - �������� ��������� � ����:\n";
				cout << "9 - ����������:\n";

				cin >> AdminMenu;
				cin.ignore();
				switch (AdminMenu)
				{
				case 1: {

					Ad.AutorizationAd();
					break;
				}
				case 2: {

					Ad.RegisLogPas();
					break;
				}


				case 3: {
					Ad.RegisLogPas();
					cout << "����� � ������ ��������:\n";
					break;
				}
				case 4: {
					Ad.ShowDatabase();
					break;
				}
				case 5: {

					Ad.RemoveStud();
					cout << "������� ������ �������\n";
					break;
				}

				case 6: {

					Ad.CreateStud();
					break;
				}
				case 7: {
					Ad.ModifyStud();
					break;
				}
				case 8: {

					Ad.AddCategory();
					break;
				}
				case 9: {
						string buf, buf2, log;
						cout << "������� �����\n";
						getline(cin, log);
						ifstream fin1("Categories.txt", ios_base::in);
						while (!fin1.eof())
						{
							getline(fin1, buf);							

						}
						fin1.close();

						ifstream fin2("Tests_name.txt", ios_base::in);
						while (!fin2.eof())
						{

							fin2 >> buf2;
							T.Show_statistic(buf2, log);
						}
						fin2.close();
						break;
					}
				}
				
			} while (AdminMenu != 0);
		}
		}
	} while (MainMenu != 0);
	system("pause");
}


