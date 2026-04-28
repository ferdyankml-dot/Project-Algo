	#include <iostream>
	#include <iomanip>
	using namespace std;

			struct Mahasiswa {
				int no;
				string nim, nama, domisili, email, nohp;
				char jenis_kelamin;
				float ipk;

				Mahasiswa *prev;
				Mahasiswa *next;
			};

			Mahasiswa *head = NULL, *tail = NULL;
			int autoNo = 1;

			// menu 
			void tampilMenu() {
				cout << endl;
				cout << "==========================================" << endl;
				cout << "     SISTEM DATA MAHASISWA SEDERHANA      " << endl;
				cout << "==========================================" << endl;
				cout << "1. tambah data mahasiswa" << endl;
				cout << "2. lihat data mahasiswa" << endl;
				cout << "0. logout" << endl;
				cout << "------------------------------------------" << endl;
				cout << "pilih menu: ";
			}

			// tambah data 
			void tambahData() {
				Mahasiswa *baru = new Mahasiswa();

				baru->no = autoNo++;

				cout << "nim: "; cin >> baru->nim;
				cout << "nama: "; cin.ignore(); getline(cin, baru->nama);
				cout << "jenis kelamin (L/P): "; cin >> baru->jenis_kelamin;
				cout << "domisili: "; cin.ignore(); getline(cin, baru->domisili);
				cout << "email: "; cin >> baru->email;
				cout << "no hp: "; cin >> baru->nohp;
				cout << "ipk: "; cin >> baru->ipk;

				baru->next = NULL;
				baru->prev = NULL;

				if (head == NULL) {
					head = tail = baru;
				} else {
					tail->next = baru;
					baru->prev = tail;
					tail = baru;
				}

				cout << endl;
				cout << "data berhasil ditambahkan!" << endl;
			}

			// lihat data
			void lihatData() {
				Mahasiswa *temp = head;

				if (temp == NULL) {
					cout << endl;
					cout << "data masih kosong" << endl;
					return;
				}

				cout << endl;
				cout << "==============================================================" << endl;
				cout << left << setw(5) << "No"
					 << setw(15) << "nim"
					 << setw(20) << "nama"
					 << setw(5) << "jenis kelamin"
					 << setw(10) << "ipk" << endl;
				cout << "==============================================================" << endl;

				while (temp != NULL) {
					cout << left << setw(5) << temp->no
						 << setw(15) << temp->nim
						 << setw(20) << temp->nama
						 << setw(5) << temp->jenis_kelamin
						 << setw(10) << temp->ipk << endl;

					temp = temp->next;
				}

				cout << "==============================================================" << endl;
			}

			// main
			int main() {
				int pilih;

				do {
					tampilMenu();
					cin >> pilih;

					if (pilih == 1) {
						cout << endl;
						cout << "===== INPUT DATA MAHASISWA =====" << endl;
						tambahData();
					} 
					else if (pilih == 2) {
						cout << endl;
						cout << "===== DATA MAHASISWA =====" << endl;
						lihatData();
					} 
					else if (pilih == 0) {
						cout << endl;
						cout << "trima kasih bolo " << endl;
					} 
					else {
						cout << endl;
						cout << "mFenu tidak ada" << endl;
					}

				} while (pilih != 0);

				return 0;
			}
