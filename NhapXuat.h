#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define Max 100
#define Book_max 5

//**********************************************************************************
//Struct define
//**********************************************************************************
struct date
{
	int d, m, y;
};

/*Thong tin doc gia*/
struct Reader {
	int Reader_id=11;
	char mail[Max];
	int join_date;
	int expire;
};

struct Reader_data {
	int n;//so luong doc gia trong thu vien
	Reader data[Max];
};

struct User_Information
{
	char id[50];
	char pass[50];
	char name[50];
	date ngay;
	int cmnd;
	char sex[8];
	int status = 1;//0:block, 1:active
	int admin = 0;//0:user, 1:admin
	Reader tag;
};
typedef struct User_Information info;

struct Data {
	int n;//so luong user trong he thong
	User_Information lst[Max];//mang chua danh sach user
};


struct book {
	int ISBN;
	char name[Max];
	char author[Max];
	char nxb[Max];
	int year;
	char type[Max];
	double cost;
	int quantity;
};

struct Book_data {
	int n=0;//so luong sach
	book book_lst[Max];//mang cau truc, moi cau truc la 1 cuon sach
};

/*Phieu muon tra sach*/
struct hire_book {
	int reader_id;
	int ISBN_list[Book_max];
	int number=0;//so sach trong list muon
	date check_out;//ngay muon
	date ret_expect;//ngay tra du kien
	date check_in;//ngay tra thuc te
};

struct hires_data {
	int n=0;//so phieu muon da dc tao
	hire_book lst[Max];//danh sach cac phieu muon
};

int GetData(char* file_name, Data* user);

int GetBookData(char * file_name, Book_data * book_list);

int GetHireData(char* file_name, hires_data* hire_list);

int SaveData(char* file_name, Data user);

int SaveBookData(char * file_name, Book_data book_list);

int SaveHireData(char* file_name, hires_data hire_list);

int CheckDataNull(Data lst);

void CreateAcc(Data* user);

void XuatThongTin(info n);

int checkAcc(info a, Data user);

void XuatMang(Data user);

void ChangePassword(info* acc, Data* user);

void DangNhap(info* n);

void Login(info* acc, Data user, char& c);

void UpdateInfo(info *n);

void Del_Space(char s[]);

int checkSpecialChar(char s[]);

int lenCheck(char s[]);

int DigitCheck(char s[]);

int CapsCheck(char s[]);

int accAvailable_check(info n, Data user);

int valid_Acc_check(info n);

void Block_user(Data* user, info acc);

void ChangeRole(Data* user, info acc);

void AdminUpdateInfo(Data* user);

int RemoveUser(Data* user, info acc);

void SearchCMND(Data user);

void SearchName(Data user);

int ChonQuanLy();

void InSach(Book_data bd);

void NhapInfoSach(book* b);

int checkName(char s[]);

int Book_Validate(book *b);

void AddBook(Book_data* bd);

int SearchBook_ISBN(Book_data* bd);

int SearchBook_name(Book_data bd);

int Empty_Book_List(Book_data bd);

void Modify_Book(Book_data* bd);

int XoaPos(Book_data* bd, int pos);

void Delete_book(Book_data* bd);

void MuonSach(Book_data* bd, hires_data* data_list, info user);

int TaoPhieuMuon(Book_data* bd, hire_book* paper, info user);

int Nhuan(int* year);

int dayMax(int* month, int* year);

void FillIn(hire_book* paper, info user);
