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
		int nomer = 1;

		if (temp == NULL) {
			cout << endl;
			cout << "data masih kosong" << endl;
			return;
		}

		cout << endl;
		cout << "=====================================================================================================" << endl;
		cout << left << setw(5) << "No"
			 << setw(15) << "nim"
			 << setw(20) << "nama"
			 << setw(5) << "JK"
			 << setw(15) << "Domisili"
			 << setw(20) << "Email"
			 << setw(15) << "No Tlpn"
			 << setw(10) << "ipk" << endl;
		cout << "=====================================================================================================" << endl;

		while (temp != NULL) {
			cout << left << setw(5) << nomer//temp->no
				 << setw(15) << temp->nim
				 << setw(20) << temp->nama
				 << setw(5) << temp->jenis_kelamin
				 << setw(15) << temp->domisili 
				 << setw(20) << temp->email 
				 << setw(15) << temp->nohp
				 << setw(10) << temp->ipk << endl;

			temp = temp->next;
			nomer++;
		}

		cout << "=====================================================================================================" << endl;
	}



	void bubbleSortA();
	void bubbleSortD();
	void quickSortAsc(Mahasiswa* low, Mahasiswa* high);
	void quickSortDesc(Mahasiswa* low, Mahasiswa* high);
	bool kembali();
	void cariData();
	void hapusData();

	//fungsi quic sort asc
	Mahasiswa* partitionAsc(Mahasiswa* low, Mahasiswa* high) {
    string pivot = high->nim;
    Mahasiswa* i = low->prev;

    for (Mahasiswa* j = low; j != high; j = j->next) {
        if (j->nim <= pivot) {
            i = (i == NULL) ? low : i->next;

            // swap data
            swap(i->nim, j->nim);
            swap(i->nama, j->nama);
            swap(i->jenis_kelamin, j->jenis_kelamin);
            swap(i->domisili, j->domisili);
            swap(i->email, j->email);
            swap(i->nohp, j->nohp);
            swap(i->ipk, j->ipk);
        }
    }

    i = (i == NULL) ? low : i->next;

    // swap pivot
    swap(i->nim, high->nim);
    swap(i->nama, high->nama);
    swap(i->jenis_kelamin, high->jenis_kelamin);
    swap(i->domisili, high->domisili);
    swap(i->email, high->email);
    swap(i->nohp, high->nohp);
    swap(i->ipk, high->ipk);

    return i;
	}

	Mahasiswa* partitionDesc(Mahasiswa* low, Mahasiswa* high) {
    string pivot = high->nim;
    Mahasiswa* i = low->prev;

    for (Mahasiswa* j = low; j != high; j = j->next) {
        if (j->nim >= pivot) {  // <-- dibalik
            i = (i == NULL) ? low : i->next;

            // swap data
            swap(i->nim, j->nim);
            swap(i->nama, j->nama);
            swap(i->jenis_kelamin, j->jenis_kelamin);
            swap(i->domisili, j->domisili);
            swap(i->email, j->email);
            swap(i->nohp, j->nohp);
            swap(i->ipk, j->ipk);
        }
    }

    i = (i == NULL) ? low : i->next;

    // swap pivot
    swap(i->nim, high->nim);
    swap(i->nama, high->nama);
    swap(i->jenis_kelamin, high->jenis_kelamin);
    swap(i->domisili, high->domisili);
    swap(i->email, high->email);
    swap(i->nohp, high->nohp);
    swap(i->ipk, high->ipk);

    return i;
}


	Mahasiswa* getTail(Mahasiswa* head) {
    while (head != NULL && head->next != NULL)
        head = head->next;
    return head;
	}

	// main
	int main() {
		int pilih, pilih2, pilih3;

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
			else if (pilih == 3) {
                cout << endl;
                cout << "===== HAPUS DATA MAHASISWA =====" << endl;
                hapusData();
            }
            else if (pilih == 5) {
                cout << endl;
                cout << "===== CARI DATA MAHASISWA =====" << endl;
                cariData();
            }
			else if (pilih == 4) {
				do{
					cout << "\n==== URUTKAN DATA ====" << endl;
					cout << endl;
					cout << "Mau urutkan berdasarkan apa" << endl;
					cout << "1.askending\n";
					cout << "2.deskending\n";
					cout << "pilihan :";
					cin >> pilih2;
					cout << endl;

					if(pilih2 == 1){
							cout << "Menggunakan metode apa??" << endl;
							cout << "1.bubble sort\n";
							cout << "2.quik sort\n";
							cout << "pilih :";
							cin >> pilih3;
							cout << endl;

							switch(pilih3) {
								case 1: {
									bubbleSortA();
    								lihatData();
    								break;
								}
								case 2: {
									quickSortAsc(head, getTail(head));
									simpanData();
									lihatData();
									 break;
								}
								 default:{
                   				 cout << "Metode tidak ada!\n";
								 }
							}
						}
					else if(pilih2 == 2){
							cout << "Menggunakan metode apa??" << endl;
							cout << "1.bubble sort\n";
							cout << "2.quik sort\n";
							cout << "pilih :";
							cin >> pilih3;
							cout << endl;

							switch(pilih3) {
								case 1: {
									bubbleSortD();
									lihatData();
    								break;
								}
								case 2: {
									quickSortDesc(head, getTail(head));
									simpanData();
									lihatData();
									 break;
								}
								 default:
                   				 cout << "Metode tidak ada!\n";
							}
						}
					else{
						cout << "menu tidak ada!!\n";
					}
					
					if (kembali()) {
    				break;
					}

					}while(pilih2 != 0);
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

}

bool kembali() {
    char pilih;
    cout << "Kembali ke menu utama? (y/t): ";
    cin >> pilih;
    return (pilih == 'y');
}

void bubbleSortA() {
    if (head == NULL || head->next == NULL) {
        cout << "Data tidak cukup untuk diurutkan.\n";
        return;
    }

    bool tukar;

    do {
        tukar = false;
        Mahasiswa *temp = head;

        while (temp->next != NULL) {

            // urut berdasarkan NIM (ascending)
            if (temp->nim > temp->next->nim) {

                // simpan data node sekarang
                string nim = temp->nim;
                string nama = temp->nama;
                char jenis_kelamin = temp->jenis_kelamin;
                string domisili = temp->domisili;
                string email = temp->email;
                string nohp = temp->nohp;
                float ipk = temp->ipk;

                // pindahkan data next ke node sekarang
                temp->nim = temp->next->nim;
                temp->nama = temp->next->nama;
                temp->jenis_kelamin = temp->next->jenis_kelamin;
                temp->domisili = temp->next->domisili;
                temp->email = temp->next->email;
                temp->nohp = temp->next->nohp;
                temp->ipk = temp->next->ipk;

                // pindahkan data lama ke node next
                temp->next->nim = nim;
                temp->next->nama = nama;
                temp->next->jenis_kelamin = jenis_kelamin;
                temp->next->domisili = domisili;
                temp->next->email = email;
                temp->next->nohp = nohp;
                temp->next->ipk = ipk;

                tukar = true;
            }

            temp = temp->next;
        }

    } while (tukar);

    simpanData(); // supaya file ikut terurut
    cout << "Data berhasil diurutkan berdasarkan NIM (ascending).\n";
}
	
void bubbleSortD() {
    if (head == NULL || head->next == NULL) {
        cout << "Data tidak cukup untuk diurutkan.\n";
        return;
    }

    bool tukar;

    do {
        tukar = false;
        Mahasiswa *temp = head;

        while (temp->next != NULL) {

            // urut berdasarkan NIM (descending)
            if (temp->nim < temp->next->nim) {

                // simpan data node sekarang
                string nim = temp->nim;
                string nama = temp->nama;
                char jenis_kelamin = temp->jenis_kelamin;
                string domisili = temp->domisili;
                string email = temp->email;
                string nohp = temp->nohp;
                float ipk = temp->ipk;

                // pindahkan data next ke node sekarang
                temp->nim = temp->next->nim;
                temp->nama = temp->next->nama;
                temp->jenis_kelamin = temp->next->jenis_kelamin;
                temp->domisili = temp->next->domisili;
                temp->email = temp->next->email;
                temp->nohp = temp->next->nohp;
                temp->ipk = temp->next->ipk;

                // pindahkan data lama ke node next
                temp->next->nim = nim;
                temp->next->nama = nama;
                temp->next->jenis_kelamin = jenis_kelamin;
                temp->next->domisili = domisili;
                temp->next->email = email;
                temp->next->nohp = nohp;
                temp->next->ipk = ipk;

                tukar = true;
            }

            temp = temp->next;
        }

    } while (tukar);

    simpanData(); // supaya file ikut terurut
    cout << "Data berhasil diurutkan berdasarkan NIM (descending).\n";
}

void quickSortAsc(Mahasiswa* low, Mahasiswa* high) {
    if (high != NULL && low != high && low != high->next) {

        Mahasiswa* p = partitionAsc(low, high);

        quickSortAsc(low, p->prev);
        quickSortAsc(p->next, high);
    	}
	}

void quickSortDesc(Mahasiswa* low, Mahasiswa* high) {
    if (high != NULL && low != high && low != high->next) {

        Mahasiswa* p = partitionDesc(low, high);

        quickSortDesc(low, p->prev);
        quickSortDesc(p->next, high);
    }
}

void cariData() {
    if (head == NULL) {
        cout << "Data masih kosong." << endl;
        return;
    }

    int pilihan;
    string keyword;
    cout << "Cari berdasarkan:" << endl;
    cout << "1. NIM" << endl;
    cout << "2. Nama" << endl;
    cout << "Pilih: ";
    cin >> pilihan;
    cout << "Masukkan kata kunci: ";
    cin.ignore();
    getline(cin, keyword);

    Mahasiswa *temp = head;
    bool ditemukan = false;

    cout << endl;
    cout << "======================= HASIL PENCARIAN =======================" << endl;
    
    while (temp != NULL) {
        bool match = false;
        if (pilihan == 1 && temp->nim == keyword) match = true;
        else if (pilihan == 2 && temp->nama.find(keyword) != string::npos) match = true;

        if (match) {
            cout << "NIM           : " << temp->nim << endl;
            cout << "Nama          : " << temp->nama << endl;
            cout << "Jenis Kelamin : " << temp->jenis_kelamin << endl;
            cout << "Domisili      : " << temp->domisili << endl;
            cout << "IPK           : " << temp->ipk << endl;
            cout << "--------------------------------------------------------" << endl;
            ditemukan = true;
        }
        temp = temp->next;
    }

    if (!ditemukan) {
        cout << "Data tidak ditemukan." << endl;
    }
}


void hapusData() {
    if (head == NULL) {
        cout << "Data kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    string targetNim;
    cout << "Masukkan NIM mahasiswa yang akan dihapus: ";
    cin >> targetNim;

    Mahasiswa *temp = head;
    while (temp != NULL && temp->nim != targetNim) {
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << "Data dengan NIM " << targetNim << " tidak ditemukan." << endl;
        return;
    }

    // Jika node yang dihapus adalah head
    if (temp == head) {
        head = head->next;
        if (head != NULL) head->prev = NULL;
    } 
    // Jika node yang dihapus adalah tail
    else if (temp == tail) {
        tail = tail->prev;
        if (tail != NULL) tail->next = NULL;
    } 
    // Jika di tengah-tengah
    else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }

    delete temp;
    simpanData(); // Update file setelah hapus
    cout << "Data mahasiswa dengan NIM " << targetNim << " berhasil dihapus." << endl;
}