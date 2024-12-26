#include "tubes.h"

int main()
{
    graph G;
    initGraph(G);

    addVertex(G, "Halte_Bojongsoang");
    addVertex(G, "Halte_Kiaracondong");
    addVertex(G, "Halte_Pasteur");
    addVertex(G, "Halte_Majalaya");
    addVertex(G, "Halte_Alun-Alun_Bandung");

    addEdge(G, "Halte_Bojongsoang", "Halte_Kiaracondong", 5000);
    addEdge(G, "Halte_Kiaracondong", "Halte_Pasteur", 7000);
    addEdge(G, "Halte_Pasteur", "Halte_Majalaya", 50000);
    addEdge(G, "Halte_Majalaya", "Halte_Alun-Alun_Bandung", 9000);
    addEdge(G, "Halte_Alun-Alun_Bandung", "Halte_Bojongsoang", 12000);

    int pilihan;

    Menu();
    cout << endl;
    cout << "Pilih Menu : ";
    cin >> pilihan;

    while (pilihan != 0) {
        switch (pilihan) {
        case 1:
            cout << "Menampilkan semua rute:" << endl;
            showAll(G);
            break;
        case 2:
            cout << "Menampilkan semua kota:" << endl;
            showVertex(G);
            break;
        case 3:
            cout << "Menampilkan detail rute dengan harga:" << endl;
            showEdge(G);
            break;
        case 4: {
            string awal, tujuan;
            cout << "Masukkan halte awal: ";
            cin >> awal;
            cout << "Masukkan halte tujuan: ";
            cin >> tujuan;
            pencarianRuteTermurah(G, awal, tujuan);
            break;
        }
        case 5: {
            string awal, tujuan;
            cout << "Masukah halte awal: ";
            cin >> awal;
            cout << "Masukan halte tujuan: ";
            cin >> tujuan;
            pencarianRuteTermahal(G, awal, tujuan);
            break;
        }
        case 6: {
            string halte;
            adrVertex cari;
            adrVertex h = firstVertex(G);

            do {
                cout << "Masukan Nama Halte: ";
                cin >> halte;
                cari = cariHalte(G, halte);
                if (cari != NULL) {
                    cout << "Halte yang anda input sudah terdaftar dalam rute. Silakan masukkan nama halte lain." << endl;
                }
                h = nextVertex(h);
            } while (cari != NULL && h != NULL);

            if (h == NULL){
                cout << "Terlalu banyak kesalahan silahkan cek kembali informasi rute pada menu nomor 1." << endl;
            }else{
                addVertex(G, halte);
                cout << "Halte baru berhasil didaftarkan." << endl;
            }
            break;
        }
        case 7: {
            string halteAwal, halteAkhir;
            int hargaRute;
            cout << "Masukan rute halte yang akan diperbarui ";
            cout << "Masukan halte awal: ";
            cin >> halteAwal;
            adrVertex cari = cariHalte(G,halteAwal);
            if (cari == NULL){
                cout << "halte awal belum terdaftar." << endl;
                cout << "Silahkan lihat informasi rute atau daftar kan halte terlebih dahulu" << endl;
                break;
            }
            cout << "Masukan halte akhir: ";
            cin >> halteAkhir;
            adrVertex cariAkhir = cariHalte(G,halteAkhir);
            if (cariAkhir == NULL){
                cout << "halte tujuan belum terdaftar." << endl;
                cout << "Silahkan lihat informasi rute atau daftar kan halte terlebih dahulu" << endl;
                break;
            }
            cout << "Masukan harga rute: ";
            cin >> hargaRute;

            deleteHalteDanRute(G, halteAwal, halteAkhir);
            addVertex(G, halteAwal);
            addEdge(G, halteAwal, halteAkhir, hargaRute);
            break;
        }
        case 8:{
            string halte;
            cout << "Masukan nama halte yang akan di hapus: ";
            cin >> halte;
            adrVertex P = cariHalte(G,halte);
            if (P != NULL){
                deleteHalteDoang(G, halte);
                cout << "Halte dengan nama " << halte << " telah berhasil di hapus." << endl;
            }else{
                cout << "Halte tidak ditemukan." << endl;
            }
            break;
        }
        case 9:{
            string halte1;
            cout << " Masukan rute halte yang akan dihapus: ";
            cin >> halte1;
            adrVertex P = cariHalte(G, halte1);
            if (P != NULL){
                deleteRuteDoang(P);
            }else{
                cout << "Tidak terdapat rute" << endl;
            }
            break;
        }
        default:
            cout << "Pilihan tidak valid, coba lagi." << endl;
            break;
        }
        cout << "------------------------------------------" << endl;
        Menu();
        cout << "Pilih Menu : ";
        cin >> pilihan;
    }
    cout << endl;
    cout << "Terimakasih telah menggunakan program halte kami ^_^";

    return 0;
}
