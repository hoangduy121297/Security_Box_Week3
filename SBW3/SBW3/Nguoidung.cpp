
#include "stdafx.h"
#include "Nguoidung.h"
#include "sqlite3.h"
#include<iostream>
#include <string.h>
#include<stdio.h>
using namespace std;
Nguoidung::Nguoidung()
{
	
}
void Nguoidung::setTaikhoan(char *taikhoan) {
	this->taiKhoan = taikhoan;
}

void Nguoidung::setMatkhau(char* matkhau) {
	this->matKhau = matkhau;
}


char* Nguoidung::getTaikhoan() {
	return taiKhoan;
}

char* Nguoidung::getMatkhau() {
	return matKhau;
}





void Nguoidung::connectDB() {
	
	rc = sqlite3_open("MyDb.db", &db);
}

void Nguoidung::dissConnectDB() {
	sqlite3_close(db);
}

void Nguoidung::Menu() {
	int trangthaidangnhap = 0;
	int select;
	do {
		cout << "chon cac chuc nang sau:" << endl;
		cout << "1.Dang nhap" << endl;
		cout << "2.Dang ky" << endl;
		cout << "3.Dang xuat" << endl;
		cout << "4.Add Friend" << endl;
		cout << "5.Block" << endl;
		cout << "6.Gui tin nhan" << endl;
		cout << "7.Xem tin nhan da gui" << endl;
		cout << "8.Danh sach ban be" << endl;
		cout << "9.Exit" << endl;
		cout << "Ban chon chuc nang:";
		cin >> select;
		switch (select) {
		case 1: {
			if (trangthaidangnhap == 1) {
				cout << "-----------------------" << endl;
				cout << "Ban da dang nhap roi" << endl;
				cout << "-----------------------" << endl;
				break;
			}
			char taikhoan[50];
			char matkhau[50];
			cout << "Nhap tai khoan:";
			cin >> taikhoan;
			cout << "Nhap mat khau:";
			cin >> matkhau;
			string sqlSelect = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan=";
			string tk = taikhoan;
			string mk = matkhau;
			sqlSelect = sqlSelect + "'" + tk + "'" + " AND matKhau='" + mk + "';";
			connectDB();

			rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			if (rows == 1) {
				cout << "-----------------------" << endl;
				cout << "Ban da dang nhap thanh cong" << endl;
				cout << "-----------------------" << endl;
				trangthaidangnhap = 1;
				setTaikhoan(taikhoan);


			}
			else {
				cout << "-----------------------" << endl;
				cout << "Tai khoan hoac mat khau sai" << endl;
				cout << "-----------------------" << endl;
			}

			break;
		}
		case 2: {
			char taikhoan[50];
			char matkhau[50];
			char hoten[50];
			char diachi[50];
			cout << "Nhap tai khoan can dang ky:";
			cin >> taikhoan;
			cout << "Nhap mat khau can dang ky:";
			cin >> matkhau;
			cin.ignore();
			cout << "Nhap ho ten:";
			cin.getline(hoten, 50);
			cout << "Nhap dia chi:";
			cin.getline(diachi, 50);
			connectDB();
			string sqlInsert = "INSERT INTO Nguoidung VALUES('" + (string)taikhoan + "','" + (string)matkhau + "','" + (string)hoten + "','" + (string)diachi + "');";
			rc = sqlite3_get_table(db, sqlInsert.c_str(), &results, &rows, &columns, &error);
			if (rc)
			{
				cout << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else {
				cout << "------------------------" << endl;
				cout << "Dang ky thanh cong" << endl;
				cout << "------------------------" << endl;
			}
			dissConnectDB();
			break;
		}
		case 3: {
			trangthaidangnhap = 0;
			char tk[] = "";
			char mk[] = "";
			setTaikhoan(tk);
			setMatkhau(mk);
			break;
		}
		case 4: {
			if (trangthaidangnhap == 0) {
				cout << "------------------------" << endl;
				cout << "Ban chua dang nhap" << endl;
				cout << "------------------------" << endl;
				break;
			}
			char taikhoan[50];
			cout << "Nhap chinh xac TAI KHOAN can AddFriend:";
			cin >> taikhoan;
			connectDB();
			//KIEM TRA XEM TAI KHOAN CAN ADDFRIEND CO TON TAI KO
			string sql = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan='" + (string)taikhoan + "';";
			rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &error);
			if (rc)
			{
				cout << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else if (rows == 0) {
				cout << "----------------------------" << endl;
				cout << "Nguoi dung nay khong ton tai" << endl;
				cout << "----------------------------" << endl;
				break;
			}
			//NEU TAI KHOAN CAN ADDFRIEND TON TAI THI TIEN HANH LAM CAC BUOC DUOI
			else if (rows == 1) {
				//KIEM TRA XEM TAI KHOAN CAN ADDFRIEND DA CO TRONG BANG TRANG THAI VOI TAI KHOAN DANG NHAP HAY CHUA NEU CO THI TIEN HANH UPDATE THANH BAN BE
				string sqlSelect = "SELECT nguoiDung1,nguoiDung2 FROM Trangthai WHERE nguoiDung1='"+(string)getTaikhoan()+"' AND nguoiDung2='"+(string)taikhoan+"';";
				rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
				//NEU 2 TAI KHOAN NAY DA CO TRONG 1 HANG CUA BANG TRANG THAI THI TIEN HANH UPDATE
				if (rows == 1) {
					string sqlUpdate1 = "UPDATE Trangthai SET trangThai='banbe' WHERE nguoiDung1='" + (string)getTaikhoan() + "' AND nguoiDung2='" + (string)taikhoan + "';";
					rc = sqlite3_exec(db, sqlUpdate1.c_str(), NULL, NULL, &error);
					if (rc) {
						cout << "AddFriend that bai";
						break;
					}
					string sqlUpdate2= "UPDATE Trangthai SET trangThai='banbe' WHERE nguoiDung2='" + (string)getTaikhoan() + "' AND nguoiDung1='" + (string)taikhoan + "';";
					rc = sqlite3_exec(db, sqlUpdate2.c_str(), NULL, NULL, &error);
					if (rc) {
						cout << "AddFriend that bai";
						break;
					}
					cout << "----------------------" << endl;
					cout << "AddFriend thanh cong" << endl;
					cout << "----------------------" << endl;
				}
				//NEU 2 TAI KHOAN NAY CHUA CO TRONG BANG TRANGTHAI THI TIEN HANH INSERT VOI TRANG THAI LA BAN BE
				else if (rows == 0) {
					string sqlInsert1 = "INSERT INTO Trangthai VALUES('" + (string)getTaikhoan() + "','" + (string)taikhoan + "','ban be');";
					rc = sqlite3_exec(db, sqlInsert1.c_str(), NULL, NULL, &error);
					if (rc) {
						cout << "AddFriend that bai";
						break;
					}
					string sqlInsert2 = "INSERT INTO Trangthai VALUES('" + (string)taikhoan + "','" + (string)getTaikhoan() + "','ban be');";
					rc = sqlite3_exec(db, sqlInsert2.c_str(), NULL, NULL, &error);
					if (rc) {
						cout << "AddFriend that bai";
						break;
					}
					cout << "-----------------------" << endl;
					cout << "AddFriend thanh cong" << endl;
					cout << "-----------------------" << endl;
				}
				dissConnectDB();
			}
			break;
		}
		case 5: {
			if (trangthaidangnhap == 0) {
				cout << "------------------------" << endl;
				cout << "Ban chua dang nhap" << endl;
				cout << "------------------------" << endl;
				break;
			}
			char taikhoan[50];
			cout << "Nhap chinh xac TAI KHOAN can Block:";
			cin >> taikhoan;
			connectDB();
			//KIEM TRA XEM TAI KHOAN CAN ADDFRIEND CO TON TAI KO
			string sql = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan='" + (string)taikhoan + "';";
			rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &error);
			if (rc)
			{
				cout << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else if (rows == 0) {
				cout << "----------------------------" << endl;
				cout << "Nguoi dung nay khong ton tai" << endl;
				cout << "----------------------------" << endl;
				break;
			}
			//NEU TAI KHOAN CAN BLOCK TON TAI THI TIEN HANH LAM CAC BUOC DUOI
			else if (rows == 1) {
				//KIEM TRA XEM TAI KHOAN CAN BLOCK DA CO TRONG BANG TRANG THAI VOI TAI KHOAN DANG NHAP HAY CHUA NEU CO THI TIEN HANH UPDATE THANH BAN BE
				string sqlSelect = "SELECT nguoiDung1,nguoiDung2 FROM Trangthai WHERE nguoiDung1='" + (string)getTaikhoan() + "' AND nguoiDung2='" + (string)taikhoan + "';";
				rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
				//NEU 2 TAI KHOAN NAY DA CO TRONG 1 HANG CUA BANG TRANG THAI THI TIEN HANH UPDATE
				if (rows == 1) {
					string sqlUpdate1 = "UPDATE Trangthai SET trangThai='block' WHERE nguoiDung1='" + (string)getTaikhoan() + "' AND nguoiDung2='" + (string)taikhoan + "';";
					rc = sqlite3_exec(db, sqlUpdate1.c_str(), NULL, NULL, &error);
					if (rc) {
						cout << "Block that bai";
						break;
					}
					string sqlUpdate2 = "UPDATE Trangthai SET trangThai='block' WHERE nguoiDung2='" + (string)getTaikhoan() + "' AND nguoiDung1='" + (string)taikhoan + "';";
					rc = sqlite3_exec(db, sqlUpdate2.c_str(), NULL, NULL, &error);
					if (rc) {
						cout << "block that bai";
						break;
					}
					cout << "----------------------" << endl;
					cout << "Block thanh cong" << endl;
					cout << "----------------------" << endl;
				}
				//NEU 2 TAI KHOAN NAY CHUA CO TRONG BANG TRANGTHAI THI TIEN HANH INSERT VOI TRANG THAI LA BAN BE
				else if (rows == 0) {
					string sqlInsert1 = "INSERT INTO Trangthai VALUES('" + (string)getTaikhoan() + "','" + (string)taikhoan + "','block');";
					rc = sqlite3_exec(db, sqlInsert1.c_str(), NULL, NULL, &error);
					if (rc) {
						cout << "Block that bai";
						break;
					}
					string sqlInsert2 = "INSERT INTO Trangthai VALUES('" + (string)taikhoan + "','" + (string)getTaikhoan() + "','block');";
					rc = sqlite3_exec(db, sqlInsert2.c_str(), NULL, NULL, &error);
					if (rc) {
						cout << "Block that bai";
						break;
					}
					cout << "-----------------------" << endl;
					cout << "Block thanh cong" << endl;
					cout << "-----------------------" << endl;
				}
				dissConnectDB();
			}
			break;
		}
		case 6: {
			if (trangthaidangnhap == 0) {
				cout << "------------------------" << endl;
				cout << "Ban chua dang nhap" << endl;
				cout << "------------------------" << endl;
				break;
			}
			char taikhoan[50];
			cout << "Nhap tai khoan can gui TIN NHAN:";
			cin >> taikhoan;
			connectDB();
			//KIEM TRA XEM TAI KHOAN CAN GUI TIN NHAN CO TON TAI KO
			string sql = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan='" + (string)taikhoan + "';";
			rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &error);
			if (rc)
			{
				cout << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else if (rows == 0) {
				cout << "----------------------------" << endl;
				cout << "Nguoi dung nay khong ton tai" << endl;
				cout << "----------------------------" << endl;
				break;
			}
			string noidung;
			cout << "nhap noi dung tin nhan can gui di:";
			cin.ignore();
			
			getline(cin, noidung);
			string sqlMess = "INSERT INTO Messenger VALUES('"+(string)getTaikhoan()+"','"+(string)taikhoan+"','"+noidung+"');";
			
			rc = sqlite3_exec(db, sqlMess.c_str(), NULL, NULL, &error);
			if (rc) {
				cout << "-----------------------------" << endl;
				cout << "Chua gui duoc tin nhan:" << sqlite3_errmsg(db) << endl;
				cout << "-----------------------------" << endl;
				break;
			}
			else {
				cout << "-----------------------------" << endl;
				cout << "Gui tin nhan thanh cong" << endl;
				cout << "-----------------------------" << endl;
			}
			dissConnectDB();
			break;
		}
		case 7: {
			if (trangthaidangnhap == 0) {
				cout << "------------------------" << endl;
				cout << "Ban chua dang nhap" << endl;
				cout << "------------------------" << endl;
				break;
			}
			connectDB();
			string sqlSelect = "SELECT * FROM MESSENGER WHERE nguoiDung1='" + (string)getTaikhoan() + "';";
			rc = sqlite3_get_table(db, sqlSelect.c_str(), &results, &rows, &columns, &error);
			if (rc) {
				cerr << "Loi ko lay duoc data: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else
			{
				// Display Table
				
				for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
				{
					for (int colCtr = 0; colCtr < columns; ++colCtr)
					{
						// Determine Cell Position
						int cellPosition = (rowCtr * columns) + colCtr;

						// Display Cell Value
						cout.width(12);
						cout.setf(ios::left);
						if (colCtr == 0) {
							cout << "Nguoi gui:";
						}
						if (colCtr == 1) {
							cout << "Nguoi nhan:";
						}
						if (colCtr == 2) {
							cout << "Noi dung tin nhan:";
						}
						cout << results[cellPosition] <<endl;
					}

					// End Line
					cout << endl;

					
				}
			}
			dissConnectDB();
			
			break;
		}
		case 8: {
			string sql = "SELECT nguoiDung2 FROM Trangthai WHERE nguoiDung1='"+(string)getTaikhoan()+"' AND "+ "trangThai='banbe';";
			connectDB();
			rc = sqlite3_get_table(db, sql.c_str(), &results, &rows, &columns, &error);
			if (rc) {
				cerr << "Loi ko lay duoc data: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else
			{
				// Display Table
				cout << "Danh sach ban be:" << endl;
				for (int rowCtr = 1; rowCtr <= rows; ++rowCtr)
				{
					for (int colCtr = 0; colCtr < columns; ++colCtr)
					{
						// Determine Cell Position
						int cellPosition = (rowCtr * columns) + colCtr;

						// Display Cell Value
						cout.width(12);
						cout.setf(ios::left);
						
						cout << results[cellPosition] << endl;
					}

					// End Line
					cout << endl;


				}
			}
			break;
		}
		} 
	}while (select != 9);
}
Nguoidung::~Nguoidung()
{
};
