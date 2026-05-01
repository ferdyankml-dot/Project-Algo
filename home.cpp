	#include <iostream>
	#include <iomanip>
	#include <fstream>
	#include <limits>
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

	// menu utaama
	void tampilMenu() {
		cout << endl;
		cout << "==========================================" << endl;
		cout << "     SISTEM DATA MAHASISWA SEDERHANA      " << endl;
		cout << "==========================================" << endl;
		cout << "1. tambah data mahasiswa" << endl;
		cout << "2. lihat data mahasiswa" << endl;
		cout << "3. hapus data mahasiswa" << endl;
		cout << "4. urutkan data mahasiswa" << endl;
		cout << "5. cari data mahasiswa" << endl;
		cout << "6. logout" << endl;
		cout << "------------------------------------------" << endl;
		cout << "pilih menu: ";
	}

	// untuk simpan file
	void simpanData() {
		ofstream file("data/data.txt");

		Mahasiswa *temp = head;
		while (temp != NULL) {
			file << temp->no << "|"
				 << temp->nim << "|"
				 << temp->nama << "|"
				 << temp->jenis_kelamin << "|"
				 << temp->domisili << "|"
				 << temp->email << "|"
				 << temp->nohp << "|"
				 << temp->ipk << endl;

			temp = temp->next;
		}

		file.close();
	}

	// proses memasukan data
	void loadData() {
		ifstream file("data/data.txt");

		while (!file.eof()) {
			Mahasiswa *baru = new Mahasiswa();

			file >> baru->no;
			file.ignore();

			getline(file, baru->nim, '|');
			getline(file, baru->nama, '|');

			file >> baru->jenis_kelamin;
			file.ignore();

			getline(file, baru->domisili, '|');
			getline(file, baru->email, '|');
			getline(file, baru->nohp, '|');

			file >> baru->ipk;
			file.ignore();

			if (file.fail()) break;

			baru->next = NULL;
			baru->prev = NULL;

			if (head == NULL) {
				head = tail = baru;
			} else {
				tail->next = baru;
				baru->prev = tail;
				tail = baru;
			}

			autoNo = baru->no + 1;
		}

		file.close();
	}

	// tambaha data
	void tambahData() {
		int jumlah;
		cout << "berapa data yang mau dimasukkan: ";
		cin >> jumlah;

		for (int i = 0; i < jumlah; i++) {
			cout << endl;
			cout << "=== data ke-" << i+1 << " ===" << endl;

			Mahasiswa *baru = new Mahasiswa();

			baru->no = autoNo++;

			cout << "nim: "; cin >> baru->nim;

			cout << "nama: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, baru->nama);

			cout << "jenis kelamin (L/P): "; cin >> baru->jenis_kelamin;

			cout << "domisili: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin, baru->domisili);

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
		}

		cout << endl;
		cout << "data berhasil ditambahkan" << endl;
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
			 << setw(5) << "JK"
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

		loadData(); // ambil data dari file

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
			else if (pilih == 6) {
				simpanData(); // simpan ke file
				cout << endl;
				cout << "trima kasih bolo sudah log out " << endl;
				return 0;
			} 
			else {
				cout << endl;
				cout << "menu tidak ada" << endl;
			}

		} while (pilih != 0);

		return 0;
	}
	
