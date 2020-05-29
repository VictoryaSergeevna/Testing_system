#include "Person.h"
Person::Person()
{
	this->login = "Default login";
	this->password = "Default password";
}

istream & operator>>(istream & is, Student & S)
{
	is >> S.FullName >> S.homeAdress >> S.telNumber >> S.login >> S.password;
	return is;
}

ostream & operator<<(ostream & os, const Student & S)
{
	os << S.FullName << S.homeAdress << S.telNumber << S.login << S.password;
	return os;

}
Student::Student() :Person()
{
	this->FullName = "Default fullname";
	this->homeAdress = "Default homeadress";
	this->telNumber = "Default telnumber";
	int counter = 0;
}

Student::Student(string FullName, string homeAdress, string telNumber)
{
	this->FullName = FullName;
	this->homeAdress = homeAdress;
	this->telNumber = telNumber;
}

Student::Student(const string login, const string password)
{
	this->login = login;
	this->password = password;

}



void Student::Registration()
{

	puts("Введите ФИО:");
	getline(cin, FullName);
	puts("Введите домашний адрес:");
	getline(cin, homeAdress);
	puts("Введите номер телефона:");
	getline(cin, telNumber);
	ofstream fout("Student_registration.txt", ios_base::out | ios_base::app);
	try {
		if (!fout.is_open()) {
			throw myExeption("Файл не открылся для записи!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout << FullName << "  " << homeAdress << "  " << telNumber << endl;
	fout.close();
	cout << "Вы успешно зарегестрировались!\n";


}

void Student::RegisLogPas()
{
	cout << "Регестрация логина и пароля:\n";
	puts("Введите логин для регестрации:");
	getline(cin, login);
	puts("Введите пароль:");
	getline(cin, password);
	string buf = login + " " + password;
	CheckRegis();
	char* str = new char[buf.size() + 1];
	strcpy(str, buf.c_str());
	Shifr(str);	
	
	ofstream fout("Student_entrance.txt", ios_base::out | ios_base::app);
	try {
		if (!fout.is_open()) {
			throw myExeption("Файл не открылся для записи!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout << str << endl;
	fout.close();
}






void Student::CheckRegis()
{
	string logUser, passUser;	
	puts("Введите логин:");
	getline(cin, logUser);
	puts("Введите пароль:");
	getline(cin, passUser);
	string buf_str, buf_str2;
	ifstream fin("Student_entrance.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("Файл не открылся для чтения !", "ShowFromFile", 103);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	buf_str2 = logUser + " " + passUser;
	bool flag = true;
	while (!fin.eof())
	{
		getline(fin, buf_str);

		if (buf_str2 == buf_str) {
			cout << "Такой логин уже есть!:\n";
			flag = false;
			return;
		}	
		
	}
	if (flag == true) {
		
cout << "Логин зарегестрирован!\n";
	}
	fin.close();
}


void Student::AutorizationSt()
{
	string logUser, passUser;
	string buf_str, buf_str2;
	puts("Введите логин:");
	getline(cin, logUser);
	puts("Введите пароль:");
	getline(cin, passUser);
	ifstream fin("Student_entrance.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("Файл не открылся для чтения !", "ShowFromFile", 103);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	buf_str2 = logUser + " " + passUser;
	bool flag = true;
	while (!fin.eof())
	{
		getline(fin, buf_str);
		char* str = new char[buf_str.size() + 1];
		strcpy(str, buf_str.c_str());
		Deshifr(str);


		if (buf_str2 == this->login) {
			cout << "Student:\n";
			cout << "Вы успешно вошли!!\n";
			flag = false;
			return;			
		}
		
	}
	if (flag == true) {
	cout << "Такого логина не найдено, зарегестрируйтесь,пожалуйста!\n";	
	}
	fin.close();
}

void Student::Shifr(char* log)
{
	int key = 3;

	for (int i = 0; i < strlen(log); i++)
	{
		if (log[i] != ' ')
			log[i] += key;
	}
	cout << "Зашифрованое слово: " << log << endl;
	
}



void Student::Deshifr(char* log)
{
	int key = 3;
	
	for (int i = 0; i < strlen(log); i++)
	{
		if (log[i] != ' ')
			log[i] -= key;
	}
	cout << "Расшифрованое слово: " << log << endl;	
	this->login = string(log);	
	
}

int Student::GetCount()
{
	return counter;
}

string Student::GetFullName()
{
	return FullName;
}

string Student::GetLogin()
{
	return login;
}

string Student::GetPassword()
{
	return password;
}

void Student::PassTest(string SubName)
{
	string buf, all_answers;
	char answer;
	int i = 0;
	ifstream fin1(SubName + "_question.txt", ios_base::in);
	ifstream fin2(SubName + "_answer.txt", ios_base::in);
	ifstream fin3(SubName + "_correct_answer.txt", ios_base::in);
	while (!fin1.eof()&& !fin2.eof()&& !fin3.eof())
	{
		getline(fin1, buf);
		
		if (buf.length() != 0)
		{
			cout << i + 1 << ". " << buf << endl;
			i++;
			for (char j = 'a'; j <= 'c'; j++)
			{
				getline(fin2, buf);
				cout << j << ") " << buf << endl;
			}
			cin >> answer;	
			cin.ignore();
			all_answers += answer;
		}
	}
	int count = 0;
	int max_count = all_answers.size();
	for (int i = 0; i < max_count; i++)
	{
		fin3.get(answer);
		if (answer == all_answers[i])
		{
			count++;
		}
	}
	fin1.close();
	fin2.close();
	fin3.close();
	double percent = (double)count / max_count * 100;
	double mark = 12 * percent / 100;
	cout << "Правильных ответов " << count << "  из вопросов: " << max_count << endl;
	cout << percent << "%\n";
	cout << "Ваша оценка - " << mark << endl;
	ofstream fout(this->login + "_result_Of_test.txt", ios_base::out | ios_base::app);
	fout << SubName << " " << count << " " << percent << " " << mark << endl;
}

void Student::RezultOfTest()
{	
	string buf;
	ifstream fin(this->login + "result_Of_test.txt", ios_base::in);
	while (!fin.eof())
	{
		getline(fin, buf);		
		cout << buf;
		}

	fin.close();
	}

istream & operator>>(istream & is, Administrator & Ad)
{
	is >> Ad.login >> Ad.password;
	return is;

}

ostream & operator<<(ostream & os, const Administrator & Ad)
{
	os << Ad.login << Ad.password;
	return os;
}

Administrator::Administrator() :Person()
{

}

Administrator::Administrator(string login, string password)
{
	this->login = login;
	this->password = password;

}



void Administrator::RegisLogPas()
{
	cout << "Регестрация логина и пароля:\n";
	puts("Введите логин для регестрации:");
	getline(cin, login);
	puts("Введите пароль:");
	getline(cin, password);
	string buf = login + " " + password;	
	char* str = new char[buf.size() + 1];
	strcpy(str, buf.c_str());
	Shifr(str);
	ofstream fout("Admin_registration.txt", ios_base::out | ios_base::trunc);
	try {
		if (!fout.is_open()) {
			throw myExeption("Файл не открылся для записи!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout << str<< endl;
	fout.close();	
}

string Administrator::GetLogin()
{
	return login;
}

string Administrator::GetPassword()
{
	return password;
}








void Administrator::AutorizationAd()
{
	string log_admin, pass_admin;
	string buf_str, buf_str2;
	puts("Введите логин:");
	getline(cin, log_admin);
	puts("Введите пароль:");
	getline(cin, pass_admin);
	ifstream fin("Admin_registration.txt", ios_base::in);
	try {
		if (!fin.is_open()) {
			throw myExeption("Файл не открылся для чтения !", "ShowFromFile", 103);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}


	bool flag = true;
	while (!fin.eof())
	{	
		buf_str2 = log_admin + " " + pass_admin;
		getline(fin, buf_str);
		char* str = new char[buf_str.size() + 1];
		strcpy(str, buf_str.c_str());
		Deshifr(str);


		if (buf_str2 == this->login) {
			cout << "Вы успешно вошли!!\n";
			flag = false;
			break;
		}	
	}
	if (flag == true) {

		cout << "Такого логина не найдено, зарегестрируйтесь,пожалуйста!\n";
	}
	fin.close();
}
void Administrator::Shifr(char* log)
{
	int key = 3;

	for (int i = 0; i < strlen(log); i++)
	{
		log[i] += key;
	}
	cout << "Зашифрованое слово: " << log << endl;
	

}

void Administrator::Deshifr(char* log)
{
	int key = 3;


	for (int i = 0; i < strlen(log); i++)
	{

		log[i] -= key;
	}
	cout << "Расшифрованое слово: " << log << endl;
	this->login = string(log);
	

}

void Administrator::CreateStud()
{
	string FullName, homeAdress, telNumber;
	puts("Введите ФИО:");
	getline(cin, FullName);
	puts("Введите домашний адрес:");
	getline(cin, homeAdress);
	puts("Введите номер телефона:");
	getline(cin, telNumber);
	ofstream fout("Student_registration.txt", ios_base::out | ios_base::app);
	try {
		if (!fout.is_open()) {
			throw myExeption("Файл не открылся для записи!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	fout << FullName << "  " << homeAdress << "  " << telNumber << endl;
	fout.close();
	cout << "Вы успешно зарегестрировали студента!\n";
}

void Administrator::RemoveStud() {
	string buf_str1, buf_str2;
	int pos;
	string log;
	puts("Введите логин:");
	getline(cin, log);
	int counter = 0;
	vector <string> vec1, vec2;
	ifstream fin1("Student_entrance.txt", ios_base::in);
	ifstream fin2("Student_registration.txt", ios_base::in);

	try {
		if (!fin1.is_open()&& !fin2.is_open()) {
			throw myExeption("Файл не открылся для чтения !", "ShowFromFile", 103);
			exit(1);
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	while (!fin1.eof() && !fin2.eof())
	{
		getline(fin1, buf_str1);
		getline(fin2, buf_str2);
		vec1.push_back(buf_str1);
		vec2.push_back(buf_str2);

		if (buf_str1.find(log) != -1) {
			pos = counter;
		}
		counter++;
	}
	fin1.close();
	fin2.close();


	ofstream fout1("Student_entrance.txt", ios_base::out);
	ofstream fout2("Student_registration.txt", ios_base::out);

	try {
		if (!fout1.is_open()&& !fin2.is_open()) {
			throw myExeption("Файл не открылся для записи!", "SaveToFile", 102);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}

	for (int i = 0; i < counter; i++)
	{
		if (i != pos) {
			fout1 << vec1[i] << endl;
			fout2 << vec2[i] << endl;
		}

	}
	fout1.close();
	fout2.close();

}

void Administrator::AddCategory()
{
	string Category, buf;
	puts("Введите название категории");
	getline(cin, Category);
	ofstream fout("Categories.txt", ios_base::out | ios_base::app);	
	fout << Category << endl;
	fout.close();

	ifstream fin("Categories.txt", ios_base::in);	
	try {
		if (!fin.is_open()) {
			throw myExeption("Файл не открылся для чтения !", "ShowFromFile", 103);
			return;
		}
	}
	catch (myExeption obj) {
		obj.Show();
	}
	int i = 0;
	while (!fin.eof())
	{
		getline(fin, buf);
		for (int i = 0; i < buf.length(); i++) {
			if (Category == buf)
			{
				break;
			}
		}
	}
	fin.close();
	AddNameTest(i+1);
}
void Administrator::AddNameTest(int SubName)
{
	string TestName;
	puts("Введите название теста");
	getline(cin, TestName);
	ofstream fout("Tests_name.txt", ios_base::out | ios_base::app);	
	fout << SubName <<" "<< TestName << endl;
	fout.close();
	AddQuestion(TestName);
}

void Administrator::AddQuestion(string SubName)
{	
	string tmp, buf;		
	ofstream fout1(SubName + "_question.txt", ios_base::out | ios_base::app);	
	puts("Введите вопрос: ");
	getline(cin, buf);
	fout1 << buf << endl;
	fout1.close();	
	ofstream fout2(SubName + "_answer.txt", ios_base::out | ios_base::app);
		cout << "Введите ответ: a \n";
		getline(cin, buf);
		fout2 << buf << endl;
		cout << "Введите ответ: b \n";
		getline(cin, buf);
		fout2 << buf << endl;
		cout << "Введите ответ: c \n";
		getline(cin, buf);
		fout2 << buf << endl;	
	fout2.close();
	ofstream fout3(SubName + "_correct_answer.txt", ios_base::out | ios_base::app);
	char correct;
	cout << "Введите букву правильного ответа: \n";
	cin >> correct;
	fout3 << correct;
	fout3.close();
}




void Administrator::ShowDatabase()
{
	string buf;
	vector <string> vec;
	ifstream fin("Student_registration.txt", ios_base::in);
	while (!fin.eof())
	{
		getline(fin, buf);
		vec.push_back(buf);

	}
	fin.close();

	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}

void Administrator::ModifyStud()
{
	string mod, buf;
	int counter = 0;
	int pos;
	vector <string> vec;
	ifstream fin("Student_registration.txt", ios_base::in);
	while (!fin.eof())
	{
		getline(fin, buf);
		vec.push_back(buf);
		counter++;
	}
	fin.close();
	ofstream fout("Student_registration.txt", ios_base::out);
	cout << "Введите позицию для изменения данных\n";
	cin >> pos;
	cin.ignore();
	puts("Введите данные студента: ФИО, адрес, телефон:");
	getline(cin, mod);
	for (int i = 0; i < counter; i++)
	{
		if (i != pos) {
			fout << endl << vec[i];
		}

		else if (i == pos)
		{
			vec[i] = mod;
			fout << endl << vec[i];

		}
	}
	fout.close();
}


