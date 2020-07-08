#include "Header.h"
void InitSystemFolder()
{
	fstream f;
	_mkdir("books");
	_mkdir("borrowedbook");
	_mkdir("cache");
	_mkdir("parameterSYSTEM");
	_mkdir("readers");

	f.open("readers/readers.csv", ios::in);
	if (f.fail())
	{
		f.open("readers/readers.csv", ios::out);
		f.close();
	}
	else
		f.close();

	f.open("readers/readersCount.txt", ios::in);
	if (f.fail())
	{
		f.close();
		f.open("readers/readersCount.txt", ios::out);
		f << 0;
		f.close();
	}
	else f.close();

	_mkdir("user");
	_mkdir("user/admin");
	_mkdir("user/experts");
	_mkdir("user/managers");
}

void AddReader() {
	Reader reader;
	fstream f;
	f.open("readers/readersCount.txt", ios::in);
	f >> reader.Code;
	f.close();
	reader.Code++;
	cout << "Ma doc gia: " << reader.Code << endl;
	cout << "Nhap gioi tinh Nam(1), Nu(0): ";
	cin >> reader.Sex;
	cout << "Ho va ten: ";
	cin.ignore();
	cin.getline(reader.Fullname, sizeof(reader.Fullname));
	cout << "CMND: ";
	cin.getline(reader.ID, sizeof(reader.ID));
	cout << "Ngay sinh: " << endl;
	InputDay(reader.DOB);
	cout << "Email: ";
	cin >> reader.Email;
	cout << "Dia chi: ";
	cin.ignore();
	cin.getline(reader.Address, sizeof(reader.Address));
	reader.CreatedDate = GetCurrentDate();
	cout << "Ngay lap the: ";
	PrintDay(reader.CreatedDate);
	cout << endl;
	reader.ExpirationDate = CountDaysAfter(reader.CreatedDate, 7);
	cout << "Ngay het han: ";
	PrintDay(reader.ExpirationDate);
	PrintReader(reader);
	//if reader hop le thi add vao file reader.csv va neu add thi moi(nghia la check xem co open reader.csv dc ko) roi moi ++ trong Countreader;
	f.open("readers/readersCount.txt", ios::out);
	f << reader.Code;
	f.close();
	f.open("readers/readers.csv", ios::out | ios::app);
	WriteReader(f, reader);
	f.close();
}
void WriteReader(fstream& f, Reader reader) {
	f << reader.Code;
	f << ",";
	f << reader.Fullname;
	f << ",";
	f << reader.ID;
	f << ",";
	f << reader.DOB.Date << "/" << reader.DOB.Month << "/" << reader.DOB.Year;
	f << ",";
	f << reader.Sex;
	f << ",";
	f << reader.Email;
	f << ",";
	f << reader.Address;
	f << ",";
	f << reader.CreatedDate.Date << "/" << reader.CreatedDate.Month << "/" << reader.CreatedDate.Year;
	f << ",";
	f << reader.ExpirationDate.Date << "/" << reader.ExpirationDate.Month << "/" << reader.ExpirationDate.Year;
	f << "\n";
}
void InputDay(Day& day) {
	cout << "Nhap ngay: ";
	cin >> day.Date;
	cout << "Nhap thang: ";
	cin >> day.Month;
	cout << "Nhap nam: ";
	cin >> day.Year;
}
Day CountDaysAfter(Day D1, int day)
{
	while (day > 0)
	{
		if (D1.Date == 31 && D1.Month == 12)
		{
			D1.Year++;
			D1.Month = 1;
			D1.Date = 0;
		}
		switch (D1.Month)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if (D1.Date == 31)
			{
				D1.Date = 0;
				D1.Month++;
			}
			break;
		case 2:
			if (D1.Date == 28 && LeapYear(D1.Year) == 0)
			{
				D1.Date = 0;
				D1.Month++;
			}
			if (D1.Date == 29 && LeapYear(D1.Year) == 1)
			{
				D1.Date = 0;
				D1.Month++;
			}
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			if (D1.Date == 30)
			{
				D1.Date = 0;
				D1.Month++;
			}
			break;
		}
		day--;
		D1.Date++;
	}
	return D1;
}
bool LeapYear(int year)
{
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
		return 1;
	return 0;
}
Day GetCurrentDate() {
	Day day;
	time_t now = time(0);
	tm* ltm = localtime(&now);
	day.Year = 1900 + ltm->tm_year;
	day.Month = 1 + ltm->tm_mon;
	day.Date = ltm->tm_mday;
	return day;
}


//In het reader ra man hinh
void PrintAllReader() {
	DList dlist{ NULL,NULL };
	ReadReader(dlist);
	for (DNode* p = dlist.Head; p; p = p->Next)
		PrintReader(p->reader);
}

void PrintReader(Reader reader) {
	cout << "Ma doc gia: " << reader.Code << endl;
	cout << "Ho va ten: " << reader.Fullname << endl;
	cout << "CMND: " << reader.ID << endl;
	cout << "Ngay sinh: ";
	PrintDay(reader.DOB);
	cout << endl;
	if (reader.Sex == 1)
		cout << "Gioi tinh: Nam" << endl;
	else
		cout << "Gioi tinh: Nu" << endl;
	cout << "Email: " << reader.Email << endl;
	cout << "Dia chi: " << reader.Address << endl;
	cout << "Ngay lap the: ";
	PrintDay(reader.CreatedDate);
	cout << endl;
	cout << "Ngay het han: ";
	PrintDay(reader.ExpirationDate);
	cout << endl;
}
void PrintDay(Day day) {
	cout << day.Date << "/" << day.Month << "/" << day.Year;
}

DNode* Initialize(Reader reader) {
	DNode* temp = new DNode;
	temp->reader = reader;
	temp->Next = NULL;
	temp->Prev = NULL;
	return temp;
}
void AddTail(DList& dlist, DNode* reader) {
	if (dlist.Head == NULL)
	{
		dlist.Head = reader;
		dlist.Tail = reader;
		return;
	}
	reader->Prev = dlist.Tail;
	dlist.Tail->Next = reader;
	dlist.Tail = reader;
}
void ReadReader(DList& dlist) {
	char Filename[] = "readers/readers.csv";
	fstream f;
	f.open("readers/readersCount.txt", ios::in);
	int n;
	f >> n;
	f.close();
	f.open(Filename, ios::in);
	Reader reader;
	for (int i = 0; i < n; i++) {
		f >> reader.Code;
		f.seekg(1, SEEK_CUR);
		f.getline(reader.Fullname, sizeof(reader.Fullname), ',');
		f.getline(reader.ID, sizeof(reader.ID), ',');
		f >> reader.DOB.Date;
		f.seekg(1, SEEK_CUR);
		f >> reader.DOB.Month;
		f.seekg(1, SEEK_CUR);
		f >> reader.DOB.Year;
		f.seekg(1, SEEK_CUR);
		f >> reader.Sex;
		f.seekg(1, SEEK_CUR);
		f.getline(reader.Email, sizeof(reader.Email), ',');
		f.getline(reader.Address, sizeof(reader.Address), ',');
		f >> reader.CreatedDate.Date;
		f.seekg(1, SEEK_CUR);
		f >> reader.CreatedDate.Month;
		f.seekg(1, SEEK_CUR);
		f >> reader.CreatedDate.Year;
		f.seekg(1, SEEK_CUR);
		f >> reader.ExpirationDate.Date;
		f.seekg(1, SEEK_CUR);
		f >> reader.ExpirationDate.Month;
		f.seekg(1, SEEK_CUR);
		f >> reader.ExpirationDate.Year;
		AddTail(dlist, Initialize(reader));
	}
	f.close();
}

//2.3 
//2.5 
void FindReaderByID() {
	char ID[45];
	cin >> ID;
	DList dlist = { NULL,NULL };
	ReadReader(dlist);
	for (DNode* p = dlist.Head; p; p = p->Next) {
		if (strcmp(ID, p->reader.ID) == 0)
		{
			PrintReader(p->reader);
			return;
		}
	}
	cout << "Khong co doc gia nao co CMND la: " << ID;
}

//2.6


