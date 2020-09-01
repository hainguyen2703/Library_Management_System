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
	int option;
	Data user;
	info acc;
	//******************************************************************************
	if (GetData(file, &user) == 0)
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
						printf("3. Exit\n");
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
						default:
							break;
						}
					} while (action != 3);
				}
				else
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
			}
		} while (option != 0);//neu option = 0 thi exit chuong trinh
	}	
	//luu data vao file truoc khi exit
	if (SaveData(file, user) == 0)
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