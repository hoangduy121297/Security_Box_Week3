#pragma once
#include<string>
#include "sqlite3.h"
using namespace std;
class Nguoidung
{
private:

	char *taiKhoan;

	char *matKhau;

	char* hoTen;

	char* diaChi;

	char* gioiTinh;

	sqlite3 *db;

	int rc;

	char *error;

public:

	Nguoidung();

	void setTaikhoan(char*);

	void setMatkhau(char*);


	char* getTaikhoan();

	char* getMatkhau();

	
	
	void connectDB();

	void dissConnectDB();

	void Menu();
	

	~Nguoidung();
};

