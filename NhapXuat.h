#include <stdio.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#define Max 50

//**********************************************************************************
//Struct define
//**********************************************************************************
struct date
{
	int d, m, y;
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
};
typedef struct User_Information info;

struct Data {
	int n;//so luong user trong he thong
	User_Information lst[Max];//mang chua danh sach user
};

int GetData(char* file_name, Data* user);

int SaveData(char* file_name, Data user);

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