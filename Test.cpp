#include "NhapXuat.h"

int main()
{
	char file[] = "Book.dat";
	FILE *fp;
	fp = fopen(file, "wb");
	fclose(fp);
}