#include "NhapXuat.h"

//**********************************************************************************
//Global variables declaration
//**********************************************************************************
int stLog=0;
int is_admin = 0;


int main()
{
	//******************************************************************************
	//Variable's declaration
	//******************************************************************************
	char file[] = "Data.dat";
	char book_file[] = "Book.dat";
	char hire_file[] = "Hire.dat";
	int option;
	Data user;
	info acc;
	Book_data book_list;
	book bk;
	hires_data hire_list;
	//******************************************************************************
	if (GetData(file, &user) == 0 || GetBookData(book_file,&book_list)==0 || GetHireData(hire_file,&hire_list)==0)
	{
		printf("Khong lay duoc data\n");
	}
	else
	{
		do
		{
			//***************************************************************************
			//tao giao dien ban dau
			//***************************************************************************
			printf("\n--------------Library Management System----------------\n");
			printf("Option 1: Login\n");
			printf("Option 2: Log out\n");
			printf("Option 3: Create account\n");
			printf("Enter 0 to exit\n");
			printf("Enter you option: ");
			scanf("%d", &option);
			//******************************************************************************
			switch (option)
			{
			case 0:
				//exit ngay lap tuc khoi chuong trinh, khong can log out
				stLog = 0;
				printf("See you later!!!\n");
				break;
			case 1:
				//*********************************Login************************************
				if (user.n == 0)//list user rong thi khong the dang nhap
				{
					printf("Chua co account nao duoc tao ra trong he thong\n");
					break;
				}
				if (stLog == 1) //neu dang nhap roi thi thong bao va thoat
				{
					printf("You already here!!!\n");
					break;
				}
				char again;
				do //vong lap, neu dang nhap sai id/pass thi dang nhap lai
				{
					again = 'n';
					Login(&acc, user, again);//dang nhap, check id, pass
				} while (again == 'y');
				break;
				//**************************************************************************
			case 2:
				//********************************Log out***********************************
				if (stLog == 0)
				{
					printf("Please log in first!!!\n");
				}
				else
				{
					stLog = 0;
					is_admin = 0;
					printf("Log out successful!!!\n");
				}
				break;
				//**************************************************************************
			case 3:
				//*****************************Create account*******************************
				CreateAcc(&user);
				break;
				//**************************************************************************
			default:
				printf("Your choice is not available!!!\n");
				break;
			}

			//*******************************************************************************
			//Cac chuc nang sau khi dang nhap thanh cong
			//*******************************************************************************
			if (stLog == 1)
			{
				if (is_admin == 0)
				{
					int action = 0;
					do
					{
						printf("\n----------------------Login Menu------------------------\n");
						printf("1. Update information\n");
						printf("2. Change password\n");
						printf("3. Print book list\n");
						printf("4. Rent a book\n");
						printf("0. Exit\n");
						printf("Enter your action: ");
						scanf("%d", &action);
						rewind(stdin);
						switch (action)
						{
						case 1:
							//**************************Update Information***************************
							for (int i = 0; i < user.n; i++)
							{
								if (strcmp(user.lst[i].id, acc.id) == 0)
								{
									UpdateInfo(&user.lst[i]);
									break;
								}
							}
							break;
							//***********************************************************************
						case 2:
							//**************************Change password******************************
							printf("\n------------------------Change password----------------------\n");
							ChangePassword(&acc, &user);
							break;
							//***********************************************************************
						case 3:
							//**************************Print book list******************************
							InSach(book_list);
							break;
							//***********************************************************************
						case 4:
							//******************************Rent a book******************************
							printf("--------------------------Muon sach---------------------------\n");
							MuonSach(&book_list, &hire_list, acc);
							break;
							//***********************************************************************
						default:
							break;
						}
					} while (action != 0);
				}
				else
				{
					int type = 0;
					type = ChonQuanLy();
					if (type == 0)
					{
						int action = 0;
						do
						{
							printf("\n----------------------Login Menu------------------------\n");
							printf("1. Update my information\n");
							printf("2. Change password\n");
							printf("3. Print user list\n");
							printf("4. Block/Unblock user in list\n");
							printf("5. Change user role\n");
							printf("6. Add user\n");
							printf("7. Change user information\n");
							printf("8. Remove a user\n");
							printf("9 Search user by cmnd\n");
							printf("10. Search user by name\n");
							printf("0. Exit\n");
							printf("Enter your action: ");
							scanf("%d", &action);
							rewind(stdin);
							int check = 0;
							switch (action)
							{
							case 1:
								//**************************Update My Information***************************
								for (int i = 0; i < user.n; i++)
								{
									if (strcmp(user.lst[i].id, acc.id) == 0)
									{
										UpdateInfo(&user.lst[i]);
										break;
									}
								}
								break;
								//***********************************************************************
							case 2:
								//**************************Change password******************************
								printf("\n------------------------Change password----------------------\n");
								ChangePassword(&acc, &user);
								break;
								//***********************************************************************
							case 3:
								//**************************Print user list******************************
								printf("\n------------------------User list----------------------\n");
								XuatMang(user);
								break;
								//***********************************************************************
							case 4:
								//**************************Block user in list***************************
								printf("\n------------------------User list----------------------\n");
								XuatMang(user);
								printf("\n------------------------Block/Unblock user----------------------\n");
								Block_user(&user, acc);
								break;
								//***********************************************************************
							case 5:
								//**************************Change user role*****************************
								printf("\n------------------------User list----------------------\n");
								XuatMang(user);
								printf("\n------------------------Change user role-------------------\n");
								ChangeRole(&user, acc);
								break;
								//***********************************************************************
							case 6:
								//**************************Add a user to list***************************
								printf("\n------------------------Add user----------------------\n");
								CreateAcc(&user);
								break;
								//***********************************************************************
							case 7:
								//**************************Change user information**********************
								printf("\n------------------------User list----------------------\n");
								XuatMang(user);
								printf("\n------------------------Change user information-------------------\n");
								AdminUpdateInfo(&user);
								break;
								//***********************************************************************
							case 8:
								//**************************Remove a user account**********************
								printf("\n------------------------User list----------------------\n");
								XuatMang(user);
								printf("\n------------------------Remove a user-------------------\n");
								check = RemoveUser(&user, acc);
								switch (check)
								{
								case 0:
									printf("Chua xoa user\n");
									break;
								case 1:
									break;
								case 2:
									printf("Day la account cua ban\n");
									break;
								}
								break;
								//***********************************************************************
							case 9:
								//**************************Search user by cmnd**************************
								printf("*********Tim kim user bang tai so chung minh nhan dan*********\n");
								SearchCMND(user);
								break;
								//***********************************************************************
							case 10:
								//**************************Search user by name**************************
								printf("*********Tim kim user theo ten*********\n");
								SearchName(user);
								break;
							default:
								break;
							}
						} while (action != 0);
					}
					else 
					{
						int action = 0;
						do
						{
							printf("**************Book Management*************\n");
							printf("1. In danh sach cac cuon sach\n");
							printf("2. Them sach vao thu vien\n");
							printf("3. Tim kim sach theo ISBN\n");
							printf("4. Tim kim sach theo ten\n");
							printf("5. Chinh sua thong tin sach\n");
							printf("6. Xoa thong tin sach\n");
							printf("Enter 0 to Exit\n");
							printf("Nhap vao chuc nang ban muon su dung: ");
							scanf("%d", &action);
							switch (action)
							{
							case 1:
								InSach(book_list);
								break;
							case 2:
								AddBook(&book_list);
								break;
							case 3:
								if (SearchBook_ISBN(&book_list) == 0)
								{
									printf("Khong tim duoc sach\n");
								}
								break;
							case 4:
								if (SearchBook_name(book_list) == 0)
								{
									printf("Khong tim duoc sach\n");
								}
								break;
							case 5:
								printf("*********Danh sach sach co trong thu vien*********\n");
								InSach(book_list);//in danh sach ra de chon sach muon chinh sua
								Modify_Book(&book_list);
								break;
							case 6:
								printf("*********Danh sach sach co trong thu vien*********\n");
								InSach(book_list);//in danh sach ra de chon sach muon xoa
								Delete_book(&book_list);
								break;
							default:
								break;
							}
						} while (action!=0);
					}
				}
			}
		} while (option != 0);//neu option = 0 thi exit chuong trinh
	}	
	//luu data vao file truoc khi exit
	if (SaveData(file, user) == 0 || SaveBookData(book_file,book_list)==0 || SaveHireData(hire_file,hire_list)==0)
	{
		printf("Khong luu duoc du lieu vao file\n");
	}
	return 0;
}

int GetData(char* file_name, Data* user)
{
	FILE* fp;
	int k = 0;
	fp = fopen(file_name, "rb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		while (feof(fp) == 0)
		{
			if (fread(&user->lst[k], sizeof(info), 1, fp) == 1)
				k++;
		}
		user->n = k;
		fclose(fp);
		return 1;
	}
}

int GetBookData(char *file_name, Book_data *book_list)
{
	FILE *fp;
	int k = 0;
	fp = fopen(file_name, "rb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		while (feof(fp) == 0)
		{
			if (fread(&book_list->book_lst[k], sizeof(book), 1, fp) == 1)
			{
				book_list->n++;
			}
		}
		fclose(fp);
		return 1;
	}
}

int GetHireData(char* file_name, hires_data* hire_list)
{
	FILE* fp;
	fp = fopen(file_name,"rb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		int k = 0;
		while (feof(fp) == 0)
		{
			if (fread(&hire_list->lst[k], sizeof(hire_book), 1, fp) == 1)
			{
				hire_list->n++;
			}
			fclose(fp);
			return 1;
		}
	}
}
int SaveData(char* file_name, Data user)
{
	FILE* fp;
	fp = fopen(file_name, "wb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		fwrite(user.lst, sizeof(info), user.n, fp);
		fclose(fp);
		return 1;
	}
}

int SaveBookData(char *file_name, Book_data book_list)
{
	FILE *fp;
	fp = fopen(file_name, "wb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		fwrite(book_list.book_lst, sizeof(book), book_list.n, fp);
		fclose(fp);
		return 1;
	}
}

int SaveHireData(char* file_name, hires_data hire_list)
{
	FILE* fp;
	fp = fopen(file_name, "wb");
	if (fp == NULL)
	{
		return 0;
	}
	else
	{
		fwrite(hire_list.lst, sizeof(hire_book), hire_list.n, fp);
		fclose(fp);
		return 1;
	}
}

int CheckDataNull(Data lst)
{
	return (lst.n == 0) ? 0 : 1;
}

void CreateAcc(Data *user)
{
	info temp;
	int valid_account = 0;
	do
	{
		printf("\t\t\tEnter your user id: ");
		rewind(stdin);
		gets_s(temp.id);
		printf("\t\t\tEnter your password: ");
		rewind(stdin);
		gets_s(temp.pass);
		Del_Space(temp.id);
		Del_Space(temp.pass);
		if (accAvailable_check(temp, *user) == 1)
		{
			printf("Ten ID nay da dc dang ki roi!!!\n");
			continue;
		}
		valid_account =valid_Acc_check(temp);
		if (valid_account == 0)
			printf("Tai khoan dang ki cua ban khong hop le!!\n");
	} while (valid_account==0);
	printf("Dang ki tai khoan thanh cong!!!\n");
	printf("Vui long cap nhat them thong tin!!!\n");
	UpdateInfo(&temp);
	user->lst[user->n] = temp;
	user->n++;
}

void XuatThongTin(info n)
{
	printf("Your user id: %s\n",n.id);
	printf("Your password: %s\n", n.pass);
	printf("Your user name: %s", n.name);
}

int checkAcc(info a, Data user)
{
	for (int i = 0; i < user.n; i++)
	{
		if (_strcmpi(a.id, user.lst[i].id) == 0 && _strcmpi(a.pass, user.lst[i].pass)==0)
		{
			if (user.lst[i].status == 1)
			{
				printf("!!!Welcome back %s!!!\n", user.lst[i].name);
				is_admin = user.lst[i].admin;
				return 1;
			}
			else
			{
				printf("Your account is blocked!!!\n");
				return 0;
			}
		}
	}
	printf("Your user id/password is not correct!!!\n");
	return 0;
}

void XuatMang(Data user)
{
	printf("\nUser id                  \tUser Name\n");
	for (int i = 0; i < user.n; i++)
	{
		printf("%s                   \t%s\n", user.lst[i].id, user.lst[i].name);
	}
}

void ChangePassword(info *acc, Data *user)
{
	info old_acc;
	char temp1[50];
	char temp2[50];
	//nhap lai password cu
	printf("Enter your old password: ");
	gets_s(old_acc.pass);
	rewind(stdin);
	//check password nhap vao co dung hay khong
	if (strcmp(old_acc.pass, acc->pass) == 0)
	{
		//neu dung
		//nhap pass moi
		int valid = 0;
		do
		{
			printf("\nEnter new password: ");
			gets_s(temp1);
			rewind(stdin);
			Del_Space(temp1);
			//check password xem co thoa cac dieu kien can thiet chua
			if (lenCheck(temp1) == 0 || DigitCheck(temp1) == 0 || CapsCheck(temp1) == 0 || checkSpecialChar(temp1) == 0)
			{
				printf("Password moi cua ban khong hop le!!!\n");
				valid = 0;
			}
			else
				valid = 1;
		} while (valid==0);	
		//double check password moi
		printf("\nEnter new password again: ");
		gets_s(temp2);
		rewind(stdin);
		Del_Space(temp2);
		//check password moi
		if (strcmp(temp1, temp2) == 0)
		{
			//neu nhap dung
			//doi password
			printf("\n***********************************\n");
			for (int i = 0; i < user->n; i++)
			{
				if (strcmp(user->lst[i].id, acc->id) == 0)
				{
					strcpy(acc->pass, temp1);
					strcpy(user->lst[i].pass, temp1);
					printf("Password change successful!!!\n");
				}
			}
			//XuatMang(list, n);
		}
		else
			printf("You enter wrong new password\n"); //neu sai, xuat password nhap sai
	}
	else
		printf("You enter a wrong password\n");
}

void DangNhap(info *n)
{
	printf("\t\t\tEnter your user id: ");
	rewind(stdin);
	gets_s(n->id);
	Del_Space(n->id);
	printf("\t\t\tEnter your password: ");
	rewind(stdin);
	gets_s(n->pass);
	Del_Space(n->pass);
	rewind(stdin);
}

void Login(info *acc, Data user, char &c)
{
	c = 'n';
	DangNhap(acc);
	stLog = checkAcc(*acc, user);
	if (stLog == 0)
	{
		printf("Ban co muon dang nhap lai ?(y/n): ");
		rewind(stdin);
		c = getchar();
		rewind(stdin);
	}
}

void UpdateInfo(info *n)
{
	printf("\t\t\tEnter your name: ");
	rewind(stdin);
	gets_s(n->name);
	rewind(stdin);
	printf("\t\t\tEnter day: ");
	scanf("%d", &n->ngay.d);
	printf("\t\t\tEnter month: ");
	scanf("%d", &n->ngay.m);
	printf("\t\t\tEnter year: ");
	scanf("%d", &n->ngay.y);
	printf("\t\t\tEnter your identifier: ");
	scanf("%d", &n->cmnd);
	printf("\t\t\tAre you male or female: ");
	rewind(stdin);
	gets_s(n->sex);
	rewind(stdin);
}

void Del_Space(char s[])
{
	//ham xoa khoang trang dau va cuoi string
	while (s[0] == ' ')
	{
		strcpy(s, s + 1);
	}
	while (s[strlen(s) - 1] == ' ')
	{
		s[strlen(s) - 1] = 0;
	}
}

int checkSpecialChar(char s[])
{
	char spe_char[] = "!@#$%^&*()-_+=\?;><.,][{}: ";
	for (int i = 0; i < strlen(spe_char); i++)
	{
		if (strchr(s, spe_char[i]) != NULL)
		{
			return 0;
		}
	}
	return 1;
}

int lenCheck(char s[])
{
	return strlen(s) < 7 ? 0 : 1;
}

int DigitCheck(char s[])
{
	char num[] = "0123456789";
	for (int i = 0; i < strlen(num); i++)
	{
		if (strchr(s, num[i]) != NULL)
		{
			return 1;
		}
	}
	return 0;
}

int CapsCheck(char s[])
{
	for (int i = 0; i < strlen(s); i++)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			return 1;
	}
	return 0;
}

int accAvailable_check(info n, Data user)
{
	for (int i = 0; i < user.n; i++)
	{
		if (_stricmp(n.id, user.lst[i].id) == 0)
			return 1;
	}
	return 0;
}

int valid_Acc_check(info n)
{
	//check user id
	if (lenCheck(n.id) == 0 || DigitCheck(n.id) == 0 || checkSpecialChar(n.id)==0)
		return 0;
	//check user pass
	if (lenCheck(n.pass) == 0 || DigitCheck(n.pass) == 0 || CapsCheck(n.pass) == 0 || checkSpecialChar(n.pass) == 0)
		return 0;
	return 1;
}

void Block_user(Data *user, info acc)
{
	char user_id_temp[50];
	rewind(stdin);
	printf("Nhap user id: ");
	gets_s(user_id_temp);
	rewind(stdin);
	if (_stricmp(user_id_temp, acc.id) == 0)
	{
		printf("Day la account cua ban!!!\n");
		return;
	}
	for (int i = 0; i < user->n; i++)
	{
		if (_stricmp(user_id_temp, user->lst[i].id) == 0)
		{
			char user_stt[8];
			printf("Ban muon block hay unblock user nay? : ");
			gets_s(user_stt);
			rewind(stdin);
			if(_stricmp(user_stt,"block")==0)
				user->lst[i].status = 0;
			else
				user->lst[i].status = 1;
			printf("Da thay doi status cua user %s\n", user->lst[i].id);
			return;
		}
	}
	printf("User %s khong ton tai\n", user_id_temp);
}

void ChangeRole(Data *user, info acc)
{
	char user_id_temp[50];
	rewind(stdin);
	printf("Nhap user id: ");
	gets_s(user_id_temp);
	rewind(stdin);
	if (_stricmp(user_id_temp, acc.id) == 0)
	{
		printf("Day la account cua ban!!!\n");
		return;
	}
	for (int i = 0; i < user->n; i++)
	{
		if (_stricmp(user_id_temp, user->lst[i].id) == 0)
		{
			char user_role[6];
			printf("Ban muon doi user nay thanh: ");
			gets_s(user_role);
			rewind(stdin);
			if (_stricmp(user_role, "admin") == 0)
				user->lst[i].admin = 1;
			else
				user->lst[i].admin = 0;
			printf("Da thay doi quyen cua user!!!\n");
			return;
		}
	}
	printf("User %s khong ton tai\n", user_id_temp);
}

void AdminUpdateInfo(Data *user)
{
	char user_id_temp[50];
	rewind(stdin);
	printf("Nhap user id: ");
	gets_s(user_id_temp);
	rewind(stdin);
	for (int i = 0; i < user->n; i++)
	{
		if (_strcmpi(user_id_temp, user->lst[i].id) == 0)
		{
			UpdateInfo(&user->lst[i]);
			return;
		}
	}
	printf("User %s khong ton tai", user_id_temp);
}

int RemoveUser(Data *user, info acc)
{
	char remove_id[50];
	printf("Nhap vao user id muon xoa: ");
	rewind(stdin);
	gets_s(remove_id);
	rewind(stdin);
	Del_Space(remove_id);
	if (_stricmp(remove_id, acc.id) == 0)
	{
		return 2;
	}
	for (int i = 0; i < user->n; i++)
	{
		if (_stricmp(remove_id, user->lst[i].id) == 0)
		{
			for (int j = i; j < user->n - 1; j++)
			{
				user->lst[j] = user->lst[j+1];			
			}
			printf("Da xoa user %s\n", remove_id);
			user->n--;
			return 1;
		}
	}
	return 0;
}

void SearchCMND(Data user)
{
	int temp;
	printf("Nhap vao so CMND muon tim: ");
	scanf("%d", &temp);
	for (int i = 0; i < user.n; i++)
	{
		if (temp == user.lst[i].cmnd)
		{
			printf("User cua so cmnd %d la: %s\n", temp, user.lst[i].id);
			return;
		}
	}
	printf("Khong co user nao su dung so cmnd nay!\n");
}

void SearchName(Data user)
{
	char temp[Max];
	int flag=0;
	printf("Nhap vao ten muon search: ");
	rewind(stdin);
	gets_s(temp);
	rewind(stdin);
	Del_Space(temp);
	for (int i = 0; i < user.n; i++)
	{
		if (_strcmpi(temp, user.lst[i].name) == 0)
		{
			printf("Id cua user nay la: %s\n", user.lst[i].id);
			flag = 1;
		}
	}
	if (flag == 0)
	{
		printf("Khong co user nao ten: %s\n", temp);
	}
}

int ChonQuanLy()
{
	char s[10];
	printf("Quan ly user hay book?: ");
	rewind(stdin);
	gets_s(s);
	rewind(stdin);
	Del_Space(s);
	if (_strcmpi(s, "book") == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void InSach(Book_data bd)
{
	if (bd.n == 0)
	{
		printf("Chua co cuon sach nao trong thu vien\n");
	}
	else
	{
		printf("ISBN       \tName                 \t\tAuthor            \tYear\n");
		for (int i = 0; i < bd.n; i++)
		{
			printf("%d       \t%s        \t%s            \t%d\n", bd.book_lst->ISBN, bd.book_lst->name, bd.book_lst->author, bd.book_lst->year);
		}
	}
}

void NhapInfoSach(book* b)
{
	int valid = 0;
	do
	{
		printf("Nhap vao ma sach: ");
		scanf("%d", &b->ISBN);
		printf("Nhap vao ten sach: ");
		rewind(stdin);
		gets_s(b->name);
		rewind(stdin);
		printf("Nhap vao ten tac gia: ");
		gets_s(b->author);
		rewind(stdin);
		printf("Nhap vao nxb: ");
		gets_s(b->nxb);
		rewind(stdin);
		printf("Nhap vao nam san xuat: ");
		scanf("%d", &b->year);
		printf("Nhap vao the loai sach: ");
		rewind(stdin);
		gets_s(b->type);
		rewind(stdin);
		printf("Nhap vao so quyen sach: ");
		scanf("%d", &b->quantity);
		printf("Nhap vao gia tien: ");
		scanf("%lf", &b->cost);
		rewind(stdin);
		valid = Book_Validate(b);
		if (valid == 0)
			printf("Thong tin sach nhap vao khong hop le\n");
	} while (valid==0);
}

int checkName(char s[])
{
	char spe_char[] = "!@#$%^&*()-_+=\?;><.,][{}:";
	for (int i = 0; i < strlen(spe_char); i++)
	{
		if (strchr(s, spe_char[i]) != NULL)
		{
			return 0;
		}
	}
	return 1;
}

int Book_Validate(book *b)
{
	time_t s;
	tm *current_time;
	s = time(NULL);
	current_time = localtime(&s);
	if (b->year > (current_time->tm_year + 1900) || b->quantity < 0 || b->cost < 0)
	{
		//check nam xuat ban, so quyen sach nhap vao, gia tien
		printf("Nam xb khong hop le\n");
		return 0;
	}
	Del_Space(b->author);
	Del_Space(b->type);
	Del_Space(b->nxb);
	Del_Space(b->name);
	if (checkName(b->author) == 0|| checkName(b->type)==0 || checkName(b->nxb)==0)
	{
		//check ten tac gia va ten the loai, ten nxb
		return 0;
	}
	return 1;
}

void AddBook(Book_data* bd)
{
	book temp;
	NhapInfoSach(&temp);
	int available = 0;
	for (int i = 0; i < bd->n; i++)
	{
		if (temp.ISBN == bd->book_lst[i].ISBN && _stricmp(temp.name,bd->book_lst[i].name)==0)
		{
			printf("Ma sach nay da co trong thu vien -> tang so luong sach\n");
			bd->book_lst[i].quantity += temp.quantity;
			available = 1;
			break;
		}
	}
	if (available == 0)
	{
		bd->book_lst[bd->n] = temp;
		bd->n++;
		printf("Da add sach moi vao thu vien\n");
	}
}

int SearchBook_ISBN(Book_data* bd)
{
	if (bd->n == 0)
	{
		printf("Chua co cuon sach nao trong thu vien\n");
		return 0;
	}
	int temp;
	printf("Nhap vao ma ISBN muon search: ");
	scanf("%d", &temp);
	rewind(stdin);
	book temp_book;
	int search_flag=0;
	for (int i = 0; i < bd->n; i++)
	{
		if (temp == bd->book_lst[i].ISBN)
		{
			temp_book = bd->book_lst[i];
			search_flag = 1;
			break;
		}
	}
	if (search_flag == 0)
	{
		return 0;
	}
	else
	{
		printf("*************Da tim dc sach ban muon************\n");
		printf("Ma sach: %d\n", temp_book.ISBN);
		printf("Ten sach: %s\n", temp_book.name);
		printf("Tac gia: %s\n", temp_book.author);
		return 1;
	}
}

int SearchBook_name(Book_data bd)
{
	if (bd.n == 0)
	{
		printf("Chua co sach nao trong thu vien\n");
		return 0;
	}
	char name_temp[Max];
	printf("Nhap vao ten sach muon tim: ");
	rewind(stdin);
	gets_s(name_temp);
	rewind(stdin);
	Del_Space(name_temp);
	int name_search=0;
	book temp_book;
	for (int i = 0; i < bd.n; i++)
	{
		if (_stricmp(name_temp, bd.book_lst[i].name) == 0)
		{
			name_search = 1;
			temp_book = bd.book_lst[i];
			break;
		}
	}
	if (name_search == 0)
	{
		return 0;
	}
	else
	{
		printf("*************Da tim dc sach ban muon************\n");
		printf("Ma sach: %d\n", temp_book.ISBN);
		printf("Ten sach: %s\n", temp_book.name);
		printf("Tac gia: %s\n", temp_book.author);
		return 1;
	}
}

int Empty_Book_List(Book_data bd)
{
	return (bd.n == 0) ? 1 : 0;
}

void Modify_Book(Book_data* bd)
{
	if (Empty_Book_List(*bd) == 1)
	{
		printf("Chua co sach trong thu vien\n");
	}
	else
	{
		int temp_isbn;
		printf("Nhap vao ma so ISBN cua sach muon sua thong tin: ");
		scanf("%d", &temp_isbn);
		rewind(stdin);
		int searched = 0;
		int pos;
		for (int i = 0; i < bd->n; i++)
		{
			if (temp_isbn == bd->book_lst[i].ISBN)
			{
				pos = i;
				searched = 1;
				break;
			}
		}
		if (searched == 0)
		{
			printf("Khong tim dc sach\n");
		}
		else
		{
			NhapInfoSach(&bd->book_lst[pos]);
			printf("Da sua thong tin thanh cong\n");
		}
	}
}

int XoaPos(Book_data* bd, int pos)
{
	if (Empty_Book_List(*bd) == 1)
	{
		return 0;
	}
	for (int i = pos; i < bd->n-1; i++)
	{
		bd->book_lst[i] = bd->book_lst[i + 1];
	}
	bd->n--;
	return 1;
}

void Delete_book(Book_data* bd)
{
	if (Empty_Book_List(*bd) == 1)
	{
		printf("Khong co quyen sach nao trong thu vien\n");
	}
	else
	{
		int temp_isbn;
		printf("Nhap vao ma sach muon xoa: ");
		scanf("%d", &temp_isbn);
		rewind(stdin);
		int searched = 0;
		int pos;
		for (int i = 0; i < bd->n; i++)
		{
			if (temp_isbn == bd->book_lst[i].ISBN)
			{
				searched = 1;
				pos = i;
				break;
			}
		}
		if (searched == 0)
		{
			printf("Khong tim thay sach muon xoa\n");
		}
		else
		{
			XoaPos(bd, pos);
		}
	}
}

void MuonSach(Book_data* bd, hires_data *data_list,info user)
{
	hire_book temp;
	if (TaoPhieuMuon(bd, &temp, user) == 1)
	{
		data_list->lst[data_list->n++] = temp;
		printf("Phieu muon tao thanh cong!!\n");
	}
	else
	{
		printf("Khong thanh cong!!\n");
	}
}

int TaoPhieuMuon(Book_data* bd, hire_book* paper, info user)
{
	InSach(*bd);//in danh sach sach ra cho doc gia chon
	int isbn_hire;
	printf("Nhap vao ma sach ban muon muon: ");
	scanf("%d", &isbn_hire);
	rewind(stdin);
	//check xem sach do co trong thu vien khong
	int pos = -1;
	for (int i = 0; i < bd->n; i++)
	{
		if (isbn_hire == bd->book_lst[i].ISBN)
		{
			pos = i;
			break;
		}
	}
	if (pos == -1)
	{
		printf("Sach nay khong co trong thu vien\n");
		return 0;
	}
	else
	{
		FillIn(paper, user);
		//dien ma isbn
		paper->ISBN_list[paper->number++] = isbn_hire;
		return 1;
	}
}

int Nhuan(int* year)
{
	if ((*year % 100 != 0 && *year % 4 == 0) || (*year % 400 == 0))
	{
		return 1;
	}
	return 0;
}

int dayMax(int* month, int *year)
{
	int maxDay;
	switch (*month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		maxDay = 31;
		break;
	case 4: case 6: case 9: case 11:
		maxDay = 30;
		break;
	case 2:
		if (Nhuan(year) == 1)
		{
			maxDay = 29;
		}
		else
		{
			maxDay = 28;
		}
		break;
	}
	return maxDay;
}

void FillIn(hire_book* paper, info user)
{
	paper->reader_id = user.tag.Reader_id;
	//lay thoi gian vao thoi diem muon sach
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	paper->check_out.d = tm.tm_mday;//ngay muon sach
	paper->check_out.m = tm.tm_mon;//thang muon sach
	paper->check_out.y = tm.tm_year + 1900;//nam muon sach
	//tinh ngay tra sach du kien
	paper->ret_expect.y = tm.tm_year;
	int maxday = dayMax(&tm.tm_mon, &tm.tm_year);
	if ((tm.tm_mday + 7) > maxday)
	{
		paper->ret_expect.m = tm.tm_mon + 1;
		paper->ret_expect.d = 7 - (maxday - tm.tm_mday);
	}
	else
	{
		paper->ret_expect.m = tm.tm_mon;
		paper->ret_expect.d = tm.tm_mday + 7;
	}
}