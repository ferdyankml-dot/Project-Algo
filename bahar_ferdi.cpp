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

	// menu uatama
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

	// menu simpan data
	void simpanData() {
		ofstream file("data.txt");

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

	// load
	void loadData() {
		ifstream file("data.txt");

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

	// menu tambah data ya ges
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

	// menu lihat data
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

	// cari  sequential
	void cariData() {
		string cari;
		cout << "masukkan nim yang dicari: ";
		cin >> cari;

		Mahasiswa *temp = head;
		bool ketemu = false;

		while (temp != NULL) {
			if (temp->nim == cari) {
				cout << endl;
				cout << "data ditemukan!" << endl;
				cout << "nim   : " << temp->nim << endl;
				cout << "nama  : " << temp->nama << endl;
				cout << "ipk   : " << temp->ipk << endl;
				ketemu = true;
				break;
			}
			temp = temp->next;
		}

		if (!ketemu) {
			cout << endl;
			cout << "data tidak ditemukan" << endl;
		}
	}

	// main
	int main() {
		int pilih;

		loadData();

		do {
			tampilMenu();
			cin >> pilih;

			if (pilih == 1) {
				tambahData();
			} 
			else if (pilih == 2) {
				lihatData();
			} 
			else if (pilih == 3) {
				cariData();
			}
			else if (pilih == 6) {
				simpanData();
				cout << endl;
				cout << "terima kasih sudah logout mase jangan balik lagi ya" << endl;
			} 
			else {
				cout << endl;
				cout << "menu tidak ada" << endl;
			}

		} while (pilih != 4);

		return 0;
	}
