
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
		switch (select)
		{
		case 1: {
			connectDB();
			int check = 0;
			if (trangthaidangnhap == 1) {
				cout << "-----------------------------------" << endl;
				cout << "Mot tai khoan dang duoc dang nhap!" << endl;
				cout << "-----------------------------------" << endl;
				break;
			}
			char taikhoan[50];
			char matkhau[50];
		
			fflush(stdin);
			cout << "Nhap tai khoan:";
			cin >> taikhoan;
			cout << "Nhap mat khau:";
			cin >> matkhau;
			const char *sqlSelect = "SELECT taiKhoan,matKhau FROM Nguoidung;";
			char **results = NULL;
			int rows, columns;
			sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else
			{
	
				for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
				{
					for (int colCtr = 0; colCtr < columns; ++colCtr)
					{
						check = 0;
						int cellPosition = (rowCtr * columns) + colCtr;
						if (strcmp(taikhoan, results[cellPosition]) == 0) {
							if (strcmp(matkhau, results[cellPosition + 1]) == 0) {
								cout << "-----------------------" << endl;
								cout << "Dang nhap thanh cong" << endl;
								cout << "-----------------------" << endl;
								trangthaidangnhap = 1;
								setTaikhoan(taikhoan);
								setMatkhau(matkhau);
								dissConnectDB();
								check = 1;
								break;
							}
						}
						
						
					}
					if (check == 1) break;
					
				}
				if (check == 1) break;
				cout << "-----------------------" << endl;
				cout << "Sai ten dang nhap hoac mat khau" << endl;
				cout << "-----------------------" << endl;
			}
			sqlite3_free_table(results);
			
			break;
		}
		case 2: {
			connectDB();
			fflush(stdin);
			char taikhoan[50];
			char matkhau[50];
			char diachi[50];
			char hoten[50];
			
			char s[50];


			cout << "----------------" << endl;
			cout << "Dang ky tai khoan moi:" << endl;
			cout << "Nhap tai khoan can dang ky:";
			cin >> taikhoan;
			cout << "Nhap mat khau:";
			cin >> matkhau;
			fflush(stdin);
			cout << "Nhap ho ten:";
			cin.getline(hoten, 50);
			cin.getline(hoten, 50);
			fflush(stdin);
			cout << "Nhap dia chi:";
			cin.getline(diachi, 50);
			//const char *sqlInsert = "INSERT INTO Nguoidung VALUES('taikhoan', 'matkhau','ho ten','diachi');";
			char sqlinsert[] = "INSERT INTO Nguoidung VALUES('";
			char *sqlInsert = sqlinsert;

			char p[] = "'";
			char c[] = ",";
			char ngoac[] = ")";
		
			char champhay []= ";";
	
			strcat(sqlInsert, taikhoan);
			strcat(sqlInsert, p);
			strcat(sqlInsert, c);
			strcat(sqlInsert, p);
			strcat(sqlInsert, matkhau);
			strcat(sqlInsert, p);
			strcat(sqlInsert, c);
			strcat(sqlInsert, p);
			strcat(sqlInsert, hoten);
			strcat(sqlInsert, p);
			strcat(sqlInsert, c);
			strcat(sqlInsert, p);
			strcat(sqlInsert, diachi);			
			strcat(sqlInsert, p);
			strcat(sqlInsert, ngoac);
			strcat(sqlInsert, champhay);
			rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
				break;
			}
			else
			{
				cout << "---------------------------" << endl;
				cout << "Tai khoan da duoc dang ky" << endl;
				cout << "----------------------------" << endl;
			}

			dissConnectDB();
			break;
		}
		case 3: {
			trangthaidangnhap = 0;
			cout << "-----------------------" << endl;
			cout << "Da dang xuat thanh cong" << endl;
			cout << "-----------------------" << endl;
			break;
		}
		case 4: {
			if (trangthaidangnhap == 0) {
				cout << "-------------------------" << endl;
				cout << "Ban chua dang nhap tai khoan" << endl;
				cout << "-------------------------" << endl;
				break;
			}
			int check1 = 0, check2 = 0;
			connectDB();
			char taikhoan[50];
			cout << "Nhap tai khoan can AddFriend:";
			cin >> taikhoan;
			char sql[] = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan=";
			char p[] = "'";
			char cp[] = ";";
			strcat(sql, p);
			strcat(sql, taikhoan);
			strcat(sql, p);
			strcat(sql, cp);
			char **results = NULL;
			int rows, columns;
			sqlite3_get_table(db, sql, &results, &rows, &columns, &error);
			if (rows < 1) {
				cout << "--------------------" << endl;
				cout << "Tai khoan nay ko ton tai" << endl;
				cout << "--------------------" << endl;
				break;

			}
			
			char sql2[] = "SELECT * FROM Trangthai WHERE nguoiDung1=";
			char nguoidung2[] = " nguoiDung2=";
			char phay[] = ",";
			char ngoac[] = ")";
			char banbe[] = "ban be";
			char And[] = " AND ";
			strcat(sql2, p);
			strcat(sql2, getTaikhoan());
			strcat(sql2, p);
			strcat(sql2, And);
			strcat(sql2, nguoidung2);
			strcat(sql2, p);
			strcat(sql2, taikhoan );
			strcat(sql2, p);
			strcat(sql2, cp);
			sqlite3_get_table(db, sql2, &results, &rows, &columns, &error);
		
			if (rows == 1) {
				check1 = 1;
				
				
				char sql3[] = "UPDATE Trangthai SET trangThai='ban be' WHERE nguoiDung1=";
				strcat(sql3, p);
				strcat(sql3, getTaikhoan());
				strcat(sql3, p);
				strcat(sql3, And);
				strcat(sql3, nguoidung2);
				strcat(sql3, p);
				strcat(sql3, taikhoan);
				strcat(sql3, p);
				strcat(sql3, cp);
				rc = sqlite3_exec(db, sql3, NULL, NULL, &error);
				if (rc)
				{
					cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
					sqlite3_free(error);
					break;
				}

			}

			char sql4[] = "SELECT nguoiDung1,nguoiDung2 FROM Trangthai WHERE nguoiDung1=";
			strcat(sql4, p);
			strcat(sql4, taikhoan);
			strcat(sql4, p);
			strcat(sql4, And);
			strcat(sql4, nguoidung2);
			strcat(sql4, p);
			strcat(sql4, getTaikhoan());
			strcat(sql4, p);
			strcat(sql4, cp);
			sqlite3_get_table(db, sql4, &results, &rows, &columns, &error);
			if (rows == 1) {
				check2 = 1;
	
				char sql5[] = "UPDATE Trangthai SET trangThai='ban be' WHERE nguoiDung1=";
				strcat(sql5, p);
				strcat(sql5, taikhoan );
				strcat(sql5, p);
				strcat(sql5, And);
				strcat(sql5, nguoidung2);
				strcat(sql5, p);
				strcat(sql5, getTaikhoan());
				strcat(sql5, p);
				strcat(sql5, cp);
				rc = sqlite3_exec(db, sql5, NULL, NULL, &error);
				if (rc)
				{
					cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
					sqlite3_free(error);
					break;
				}

			}
		
			if (check1 == 0) {
				char sqlInsert1[] = "INSERT INTO Trangthai VALUES('";
				strcat(sqlInsert1, getTaikhoan());

				strcat(sqlInsert1, p);
				strcat(sqlInsert1, phay);
				strcat(sqlInsert1, p);
				strcat(sqlInsert1, taikhoan);
				strcat(sqlInsert1, p);
				strcat(sqlInsert1, phay);
				strcat(sqlInsert1, p);
				strcat(sqlInsert1, banbe);
				strcat(sqlInsert1, p);
				strcat(sqlInsert1, ngoac);
				strcat(sqlInsert1, cp);
				rc = sqlite3_exec(db, sqlInsert1, NULL, NULL, &error);
				if (rc)
				{
					
					cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
					sqlite3_free(error);
					break;
				}

			}
			if (check2 == 0) {
				char sqlInsert2[] = "INSERT INTO Trangthai VALUES('";
				strcat(sqlInsert2, taikhoan);
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, phay);
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, getTaikhoan());
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, phay);
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, banbe);
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, ngoac);
				strcat(sqlInsert2, cp);
				rc = sqlite3_exec(db, sqlInsert2, NULL, NULL, &error);
				if (rc)
				{
					cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
					sqlite3_free(error);
					break;
				}
			}
			
			cout << "---------------------------" << endl;
			cout << "AddFriend thanh cong" << endl;
			cout << "---------------------------" << endl;
			dissConnectDB();
			break;
		}
		case 5: {
			if (trangthaidangnhap == 0) {
				cout << "-------------------------" << endl;
				cout << "Ban chua dang nhap tai khoan" << endl;
				cout << "-------------------------" << endl;
				break;
			}
			int check1 = 0, check2 = 0;
			connectDB();
			char taikhoan[50];
			cout << "Nhap tai khoan can Block:";
			cin >> taikhoan;
			char sql[] = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan=";
			char p[] = "'";
			char cp[] = ";";
			strcat(sql, p);
			strcat(sql, taikhoan);
			strcat(sql, p);
			strcat(sql, cp);
			char **results = NULL;
			int rows, columns;
			sqlite3_get_table(db, sql, &results, &rows, &columns, &error);
			if (rows < 1) {
				cout << "--------------------" << endl;
				cout << "Tai khoan nay ko ton tai" << endl;
				cout << "--------------------" << endl;
				break;
				
			}		
			sqlite3_free_table(results);
			char sql2[] = "SELECT nguoiDung1,nguoiDung2 FROM Trangthai WHERE nguoiDung1=";
			char nguoidung2[] = "nguoiDung2=";
			char phay[] = ",";
			char ngoac[] = ")";
			char block[] = "block";
			char And[] = " AND ";
			strcat(sql2, p);
			strcat(sql2, getTaikhoan());
			strcat(sql2, p);
			strcat(sql2, And);
			strcat(sql2, nguoidung2);
			strcat(sql2, p);
			strcat(sql2, taikhoan);
			strcat(sql2, p);
			strcat(sql2, cp);
			sqlite3_get_table(db, sql2, &results, &rows, &columns, &error);
			if (rows == 1) {
				check1 = 1;
				sqlite3_free_table(results);
				char sql3[] = "UPDATE Trangthai SET trangThai='block' WHERE nguoiDung1=";
				strcat(sql3, p);
				strcat(sql3, getTaikhoan());
				strcat(sql3, p);
				strcat(sql3, And);
				strcat(sql3, nguoidung2);
				strcat(sql3, p);
				strcat(sql3, taikhoan);
				strcat(sql3, p);
				strcat(sql3, cp);
				rc = sqlite3_exec(db, sql3, NULL, NULL, &error);
				if (rc)
				{
					cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
					sqlite3_free(error);
					break;
				}
				
			}
			
			char sql4[] = "SELECT nguoiDung1,nguoiDung2 FROM Trangthai WHERE nguoiDung1=";
			strcat(sql4, p);
			strcat(sql4, taikhoan);
			strcat(sql4, p);
			strcat(sql4, And);
			strcat(sql4, nguoidung2);
			strcat(sql4, p);
			strcat(sql4, getTaikhoan());
			strcat(sql4, p);
			strcat(sql4, cp);
			sqlite3_get_table(db, sql4, &results, &rows, &columns, &error);
			if (rows == 1) {
				sqlite3_free_table(results);
				check2 = 1;
				char sql5[] = "UPDATE Trangthai SET trangThai='block' WHERE nguoiDung1=";
				strcat(sql5, p);
				strcat(sql5,taikhoan );
				strcat(sql5, p);
				strcat(sql5, And);
				strcat(sql5, nguoidung2);
				strcat(sql5, p);
				strcat(sql5, getTaikhoan());
				strcat(sql5, p);
				strcat(sql5, cp);
				rc = sqlite3_exec(db, sql5, NULL, NULL, &error);
				if (rc)
				{
					cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
					sqlite3_free(error);
					break;
				}
				
			}
			
			if (check1 == 0) {
				char sqlInsert1[] = "INSERT INTO Trangthai VALUES('";
				strcat(sqlInsert1, getTaikhoan());
				strcat(sqlInsert1, p);
				strcat(sqlInsert1, phay);
				strcat(sqlInsert1, p);
				strcat(sqlInsert1, taikhoan);
				strcat(sqlInsert1, p);
				strcat(sqlInsert1, phay);
				strcat(sqlInsert1, p);
				strcat(sqlInsert1, block);
				strcat(sqlInsert1, p);
				strcat(sqlInsert1, ngoac);
				strcat(sqlInsert1, cp);
				rc = sqlite3_exec(db, sqlInsert1, NULL, NULL, &error);
				if (rc)
				{
					cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
					sqlite3_free(error);
					break;
				}
			
			}
			if (check2 == 0) {
				char sqlInsert2[] = "INSERT INTO Trangthai VALUES('";
				strcat(sqlInsert2, taikhoan);
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, phay);
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, getTaikhoan());
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, phay);
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, block);
				strcat(sqlInsert2, p);
				strcat(sqlInsert2, ngoac);
				strcat(sqlInsert2, cp);
				rc = sqlite3_exec(db, sqlInsert2, NULL, NULL, &error);
				if (rc)
				{
					cerr << "Error executing SQLite3 statement: " << sqlite3_errmsg(db) << endl << endl;
					sqlite3_free(error);
					break;
				}
			}
			cout << "---------------------------" << endl;
			cout << "Block thanh cong" << endl;
			cout << "---------------------------" << endl;
			dissConnectDB();
			break;
		}
		case 6: {
			if (trangthaidangnhap == 0) {
				cout << "-------------------------" << endl;
				cout << "Ban chua dang nhap tai khoan" << endl;
				cout << "-------------------------" << endl;
				break;
			}
			connectDB();
			char taikhoan[50];
			cout << "Nhap tai khoan ban muon gui tin nhan den:";
			cin >> taikhoan;
			char sql[] = "SELECT taiKhoan FROM Nguoidung WHERE taiKhoan=";
			char p[] = "'";
			char cp[] = ";";
			char phay[] = ",";
			char ngoac[] = ")";
			char And[] = " AND ";
			char Or[] = " OR ";
			char trangthai[] = " trangThai='block';";
			char noidung[100];
			char nguoidung2[] = " nguoiDung2= ";
			char nguoidung1[] = " nguoiDung1= ";
			
			strcat(sql, p);
			strcat(sql, taikhoan);
			strcat(sql, p);
			strcat(sql, cp);
			char **results = NULL;
			int rows, columns;
			sqlite3_get_table(db, sql, &results, &rows, &columns, &error);
			if (rows < 1) {
				cout << "--------------------" << endl;
				cout << "Tai khoan nay ko ton tai" << endl;
				cout << "--------------------" << endl;
				break;

			}
			/*SELECT *	FROM Trangthai
			WHERE (nguoiDung1 = 'duy'   AND   nguoiDung2 = 'yen' OR nguoiDung1 = 'yen' And nguoiDung2 = 'duy')  And trangThai = 'block'*/
			char sqlBlock[] = "SELECT * FROM Trangthai WHERE (nguoiDung1='";
			strcat(sqlBlock, getTaikhoan());
			strcat(sqlBlock, p);
			strcat(sqlBlock,And);
			strcat(sqlBlock, nguoidung2);
			strcat(sqlBlock, p);
			strcat(sqlBlock, taikhoan);
			strcat(sqlBlock, p);
			strcat(sqlBlock,  Or);
			strcat(sqlBlock, nguoidung1);
			strcat(sqlBlock, p);
			strcat(sqlBlock, taikhoan);
			strcat(sqlBlock, p);
			strcat(sqlBlock, And);
			strcat(sqlBlock, nguoidung2);
			strcat(sqlBlock, p);
			strcat(sqlBlock, getTaikhoan());
			strcat(sqlBlock, p);
			strcat(sqlBlock, ngoac);
			strcat(sqlBlock, And);
			strcat(sqlBlock, trangthai);
			sqlite3_get_table(db, sqlBlock, &results, &rows, &columns, &error);
			rc = sqlite3_exec(db, sqlBlock, NULL, NULL, &error);
			
			if (rows >= 1) {
				cout << "--------------------------------------------" << endl;
				cout << "khong the nhan tin cho tai khoan bi Block" << endl;
				cout << "--------------------------------------------" << endl;
				break;
			}
			
			fflush(stdin);
			cout << "nhap noi dung tin nhan:";	
			cin.getline(noidung, 100);
			cin.getline(noidung, 100);
			char sqlInsert[] = "INSERT INTO Messenger VALUES('";
			strcat(sqlInsert, getTaikhoan());
			strcat(sqlInsert, p);
			strcat(sqlInsert, phay);
			strcat(sqlInsert, p);
			strcat(sqlInsert, taikhoan);
			strcat(sqlInsert, p);
			strcat(sqlInsert, phay);
			strcat(sqlInsert, p);
			strcat(sqlInsert, noidung);
			strcat(sqlInsert, p);
			strcat(sqlInsert, ngoac);
			strcat(sqlInsert, cp);
			rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
			if (rc) {
				cout << "chua gui dc tin nhan" << endl;
				break;
			}
			else {
				cout << "--------------------" << endl;
				cout << "Da gui tin nhan" << endl;
				cout << "--------------------" << endl;
			}
			dissConnectDB();
			break;
		}
		case 7: {
			if (trangthaidangnhap == 0) {
				cout << "------------------" << endl;
				cout << "Chua dang nhap" << endl;
				cout << "------------------" << endl;
				break;
			}
			connectDB();
			char sql[] = "SELECT * FROM Messenger WHERE nguoiDung1='";
			char p[] = "'";
			char cp[] = ";";
			strcat(sql, getTaikhoan());
			strcat(sql, p);
			strcat(sql, cp);
			char **results = NULL;
			int rows, columns;
			sqlite3_get_table(db, sql, &results, &rows, &columns, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else
			{
				// Display Table
				for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
				{
					for (int colCtr = 0; colCtr < columns; ++colCtr)
					{
						// Determine Cell Position
						int cellPosition = (rowCtr * columns) + colCtr;

						// Display Cell Value
						cout.width(12);
						cout.setf(ios::left);

						cout << results[cellPosition] << " ";
					}

					// End Line
					cout << endl;

					// Display Separator For Header
					if (0 == rowCtr)
					{
						for (int colCtr = 0; colCtr < columns; ++colCtr)
						{
							cout.width(12);
							cout.setf(ios::left);
							cout << "~~~~~~~~~~~~ ";
						}
						cout << endl;
					}
				}
			}
			sqlite3_free_table(results);
			break;
		}
		case 8: {
			if (trangthaidangnhap == 0) {
				cout << "-----------------------" << endl;
				cout << "Chua dang nhap" << endl;
				cout << "------------------------" << endl;
				break;

			}
			connectDB();
			char nguoidung1[] = " nguoiDung1 ";
			char nguoidung2[] = " nguoiDung2 ";
			char And[] = " AND ";
			char trangthai[] = " trangThai='ban be'; ";
			char p[] = "'";
			char s[] = " ";
			char sql[] = "SELECT nguoiDung2 FROM Trangthai WHERE nguoiDung1='";
			strcat(sql, getTaikhoan());
			strcat(sql, p);
			strcat(sql, And);
			strcat(sql, trangthai);
			char **results = NULL;
			int rows, columns;
			sqlite3_get_table(db, sql, &results, &rows, &columns, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
				sqlite3_free(error);
			}
			else
			{
				// Display Table
				cout << "----------------------------" << endl;
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

						cout << results[cellPosition] << " ";
					}

					// End Line
					cout << endl;

					
				}
			}
			sqlite3_free_table(results);
			char sql2[] = "SELECT nguoiDung1 FROM Trangthai WHERE nguoiDung2='";
			strcat(sql2, getTaikhoan());
			strcat(sql2, p);
			strcat(sql2, And);
			strcat(sql2, trangthai);
			
			sqlite3_get_table(db, sql2, &results, &rows, &columns, &error);
			if (rc)
			{
				cerr << "Error executing SQLite3 query: " << sqlite3_errmsg(db) << endl << endl;
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

						cout << results[cellPosition] << " ";
					}

					// End Line
					cout << endl;
					

				}
			}
			cout << "-----------------------" << endl;
			dissConnectDB();
			break;
		}
		case 9: {
			break;
		}

		}

	} while (select!=9);
}

Nguoidung::~Nguoidung()
{
}
