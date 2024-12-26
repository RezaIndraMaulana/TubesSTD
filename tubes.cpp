#include "tubes.h"

void createVertex(string newVertexID, adrVertex &v){
    v = new vertex;
    idVertex(v) = newVertexID;
    nextVertex(v) = NULL;
    firstEdge(v) = NULL;
};

void initGraph(graph &G) {
    firstVertex(G) = NULL;
};

void addVertex(graph &G, string newVertexID) {
    adrVertex v, temp;
    createVertex(newVertexID, v);
    if (firstVertex(G) == NULL) {
        firstVertex(G) = v;
    } else {
        temp = firstVertex(G);
        while (nextVertex(temp) != NULL) {
            temp = nextVertex(temp);
        }
        nextVertex(temp) = v;
    }
};

void createEdge(string tujuan, int price, adrEdge &e) {
    e = new edge;
    destVertexID(e) = tujuan;
    price(e) = price;
    nextEdge(e) = NULL;
};

void addEdge(graph &G, string asal, string tujuan, int price) {
    adrVertex v = firstVertex(G);
    while (v != NULL && idVertex(v) != asal) {
        v = nextVertex(v);
    }
    if (v != NULL) {
        adrEdge e;
        createEdge(tujuan, price, e);
        if (firstEdge(v) == NULL) {
            firstEdge(v) = e;
        } else {
            adrEdge temp = firstEdge(v);
            while (nextEdge(temp) != NULL) {
                temp = nextEdge(temp);
            }
            nextEdge(temp) = e;
        }
    }

    v = firstVertex(G);
    while (v != NULL && idVertex(v) != tujuan) {
        v = nextVertex(v);
    }
    if (v != NULL) {
        adrEdge e;
        createEdge(asal, price, e);
        if (firstEdge(v) == NULL) {
            firstEdge(v) = e;
        } else {
            adrEdge temp = firstEdge(v);
            while (nextEdge(temp) != NULL) {
                temp = nextEdge(temp);
            }
            nextEdge(temp) = e;
        }
    }
}

void Menu(){
    cout << "Selamat datang di Rekomendasi Jalur Transportasi" << endl;
    cout << "Menu : " << endl;
    cout << "1. Melihat Semua Rute beserta Harga Transportasi" << endl;
    cout << "2. Melihat Semua Halte (Vertex) Transportasi" << endl;
    cout << "3. Melihat Rute dengan Detail Edge (Harga)" << endl;
    cout << "4. Mencari Rute Termurah" << endl;
    cout << "5. Mencari Rute Termahal" << endl;
    cout << "6. Membuat Halte Baru" << endl;
    cout << "7. Membuat Rute Halte baru dari Halte yang sudah ada" << endl;
    cout << "8. Hapus Halte" << endl;
    cout << "9. Hapus Rute" << endl;
    cout << "0. Keluar" << endl;
};

void showVertex(graph &G){
    adrVertex v = firstVertex(G);
    while (v != NULL) {
        cout << "Halte : " << idVertex(v) << endl;
        v = nextVertex(v);
    }
};

void showEdge(graph &G){
    adrVertex v = firstVertex(G);
    while (v != NULL) {
        cout << "Rute dari " << idVertex(v) << " ke:" << endl;
        adrEdge e = firstEdge(v);
        if(e == NULL){
            cout << "Tidak ada rute";
        } else {
                while (e != NULL) {
                cout << destVertexID(e) << " Harga : Rp" << price(e) << endl;
                e = nextEdge(e);
            }
        }
        v = nextVertex(v);
        cout << "" << endl;
    }
};

void showAll(graph &G){
    adrVertex v = firstVertex(G);
    if (v == NULL) {
        cout << "Graph kosong, tidak ada rute yang tersedia." << endl;
        return;
    }

    while (v != NULL) {
        cout << "Halte: " << idVertex(v) << endl;
        adrEdge e = firstEdge(v);
        if (e == NULL) {
            cout << "  Tidak ada rute dari halte ini." << endl;
        } else {
            cout << "  Rute ke:" << endl;
            while (e != NULL) {
                cout << "    " << destVertexID(e) << " Harga: Rp" << price(e) << ")" << endl;
                e = nextEdge(e);
            }
        }
        v = nextVertex(v);
        cout << "" << endl;
    }
}

adrVertex cariHalte(graph &G, string tempat) {
    adrVertex current = firstVertex(G);
    while (current != NULL && idVertex(current) != tempat) {
        current = nextVertex(current);
    }
    return current;
}

void pencarianRuteTermurah(graph &G, string tAwal, string tTujuan) {
    adrVertex Awal = cariHalte(G, tAwal);
    adrVertex Akhir = cariHalte(G, tTujuan);

    if (Awal == NULL || Akhir == NULL) {
        cout << "Error: Tempat awal atau akhir tidak ditemukan." << endl;
        return;
    }

    //buat inisiasi doang
    int harga[MAX_VERTEX];
    bool visited[MAX_VERTEX];
    adrVertex vertexArray[MAX_VERTEX];
    int predecessor[MAX_VERTEX];
    int idxAwal = -1, idxAkhir = -1;

    int jumlahVertex = 0;
    adrVertex current = firstVertex(G);
    while (current != NULL) {
        vertexArray[jumlahVertex] = current;
        harga[jumlahVertex] = INT_MAX;
        visited[jumlahVertex] = false;
        predecessor[jumlahVertex] = -1;
        if (current == Awal) idxAwal = jumlahVertex;
        if (current == Akhir) idxAkhir = jumlahVertex;
        jumlahVertex++;
        current = nextVertex(current);
    }

    harga[idxAwal] = 0;

    //buat ngecek harga terkecil
    for (int i = 0; i < jumlahVertex; ++i) {
        int minHarga = INT_MAX;
        int idxMin = -1;

        for (int j = 0; j < jumlahVertex; ++j) {
            if (!visited[j] && harga[j] < minHarga) {
                minHarga = harga[j];
                idxMin = j;
            }
        }

        if (idxMin == -1) break;
        visited[idxMin] = true;

        //buat ngecek tetangga ( edge )
        adrEdge edge = firstEdge(vertexArray[idxMin]);
        while (edge != NULL) {
            int idxTetangga = -1;
            for (int k = 0; k < jumlahVertex; ++k) {
                if (idVertex(vertexArray[k]) == destVertexID(edge)) {
                    idxTetangga = k;
                    break;
                }
            }

            //buat update harganya buat total nanti
            if (idxTetangga != -1 && !visited[idxTetangga]) {
                int hargaBaru = harga[idxMin] + price(edge);
                if (hargaBaru < harga[idxTetangga]) {
                    harga[idxTetangga] = hargaBaru;
                    predecessor[idxTetangga] = idxMin;
                }
            }
            edge = nextEdge(edge);
        }
    }

    if (harga[idxAkhir] == INT_MAX) {
        cout << "Tidak ada rute dari " << tAwal << " ke " << tTujuan << "." << endl;
    } else {
        cout << "Rute Termurah dari " << tAwal << " ke " << tTujuan << " melalui jalan berikut:" << endl;

        //nyari rute mana aja tadi yang ditemuin
        int path[MAX_VERTEX];
        int pathIdx = 0;
        for (int idx = idxAkhir; idx != -1; idx = predecessor[idx]) {
            path[pathIdx++] = idx;
        }


        //nampilin rutenya
        for (int i = pathIdx - 1; i >= 0; --i) {
            cout << idVertex(vertexArray[path[i]]);
            if (i > 0) cout << " - ";
        }
        cout << endl;

        cout << "Dengan total harga = Rp" << harga[idxAkhir] << "." << endl;
    }
}

//persis kek diatas tapi ini maxHarga aj
void pencarianRuteTermahal(graph &G, string tAwal, string tTujuan) {
    adrVertex Awal = cariHalte(G, tAwal);
    adrVertex Akhir = cariHalte(G, tTujuan);

    if (Awal == NULL || Akhir == NULL) {
        cout << "Error: Tempat awal atau akhir tidak ditemukan." << endl;
        return;
    }

    //inisiasi doang
    int harga[MAX_VERTEX];
    bool visited[MAX_VERTEX];
    adrVertex vertexArray[MAX_VERTEX];
    int predecessor[MAX_VERTEX];
    int idxAwal = -1, idxAkhir = -1;

    int jumlahVertex = 0;
    adrVertex current = firstVertex(G);
    while (current != NULL) {
        vertexArray[jumlahVertex] = current;
        harga[jumlahVertex] = INT_MIN;
        visited[jumlahVertex] = false;
        predecessor[jumlahVertex] = -1;
        if (current == Awal) idxAwal = jumlahVertex;
        if (current == Akhir) idxAkhir = jumlahVertex;
        jumlahVertex++;
        current = nextVertex(current);
    }

    harga[idxAwal] = 0;

    //buat ngecek maxHarga
    for (int i = 0; i < jumlahVertex; ++i) {
        int maxHarga = INT_MIN;
        int idxMax = -1;

        for (int j = 0; j < jumlahVertex; ++j) {
            if (!visited[j] && harga[j] > maxHarga) {
                maxHarga = harga[j];
                idxMax = j;
            }
        }

        if (idxMax == -1) break;
        visited[idxMax] = true;

        //mencari tetangga ( edge )
        adrEdge edge = firstEdge(vertexArray[idxMax]);
        while (edge != NULL) {
            int idxTetangga = -1;
            for (int k = 0; k < jumlahVertex; ++k) {
                if (idVertex(vertexArray[k]) == destVertexID(edge)) {
                    idxTetangga = k;
                    break;
                }
            }

            //update harga
            if (idxTetangga != -1 && !visited[idxTetangga]) {
                int hargaBaru = harga[idxMax] + price(edge);
                if (hargaBaru > harga[idxTetangga]) {
                    harga[idxTetangga] = hargaBaru;
                    predecessor[idxTetangga] = idxMax;
                }
            }
            edge = nextEdge(edge);
        }
    }

    if (harga[idxAkhir] == INT_MIN) {
        cout << "Tidak ada rute dari " << tAwal << " ke " << tTujuan << "." << endl;
    } else {
        cout << "Rute Termahal dari " << tAwal << " ke " << tTujuan << " melalui jalan berikut:" << endl;

        int path[MAX_VERTEX];
        int pathIdx = 0;
        for (int idx = idxAkhir; idx != -1; idx = predecessor[idx]) {
            path[pathIdx++] = idx;
        }

        for (int i = pathIdx - 1; i >= 0; --i) {
            cout << idVertex(vertexArray[path[i]]);
            if (i > 0) cout << " - ";
        }
        cout << endl;

        cout << "Dengan total harga = Rp" << harga[idxAkhir] << "." << endl;
    }
}

adrEdge cariEdge(graph &G, string &awal, string &akhir) {
    adrVertex v = cariHalte(G, awal);
    if (v != NULL) {
        adrEdge e = firstEdge(v);
        while (e != NULL) {
            if (destVertexID(e) == akhir) {
                return e;
            }
            e = nextEdge(e);
        }
    }
    return NULL;
}

void perbaruiRute(adrEdge e, int harga) {
    if (e != NULL) {
        price(e) = harga;
    }
}

void deleteHalteDanRute(graph &G, string asal, string tujuan){
    adrVertex P = firstVertex(G);
    adrVertex temp = NULL;
    while (P != NULL && idVertex(P) != asal){
        temp = P;
        P = nextVertex(P);
    }
    if (P != NULL){
        adrEdge e = firstEdge(P);
        while(e != NULL && destVertexID(e) != tujuan){
            adrEdge next = nextEdge(e);
            nextEdge(e) = NULL;
            destVertexID(e) = " ";
            price(e) = NULL;
            e = next;
        }
        if (temp != NULL){
            nextVertex(temp) = nextVertex(P);
        }else{
            firstVertex(G) = nextVertex(P);
        }
        nextVertex(P) = NULL;
        idVertex(P) = "";
        firstEdge(P) = NULL;
        P = NULL;
    }else{
        cout << "Tidak terdapat nama halte tersebut dalam informasi rute." << endl;
        cout << "Silahkan cek kembali informasi rute." << endl;
    }


};

//void deleteHalteDoang(graph &G, string halte) {
//    adrVertex v = firstVertex(G);
//    while (v != NULL) {
//        adrEdge prev = NULL;
//        adrEdge e = firstEdge(v);
//        while (e != NULL) {
//            if (destVertexID(e) == halte) {
//                if (prev == NULL) {
//                    firstEdge(v) = nextEdge(e);
//                } else {
//                    nextEdge(prev) = nextEdge(e);
//                }
//                adrEdge temp = e;
//                e = nextEdge(e);
//                delete temp;
//            } else {
//                prev = e;
//                e = nextEdge(e);
//            }
//        }
//        v = nextVertex(v);
//    }
//
//    adrVertex P = firstVertex(G);
//    adrVertex temp = NULL;
//    while (P != NULL && idVertex(P) != halte) {
//        temp = P;
//        P = nextVertex(P);
//    }
//    if (P != NULL) {
//        if (temp != NULL) {
//            nextVertex(temp) = nextVertex(P);
//        } else {
//            firstVertex(G) = nextVertex(P);
//        }
//        nextVertex(P) = NULL;
//        idVertex(P) = "";
//        firstEdge(P) = NULL;
//        delete P;
//    }
//}

void deleteHalteDoang(graph &G, string halte) {
    adrVertex v = firstVertex(G);
    while (v != NULL) {
        adrEdge prev = NULL;
        adrEdge e = firstEdge(v);
        while (e != NULL) {
            if (destVertexID(e) == halte) {
                if (prev == NULL) {
                    firstEdge(v) = nextEdge(e);
                } else {
                    nextEdge(prev) = nextEdge(e);
                }
                adrEdge temp = e;
                e = nextEdge(e);
                delete temp;
            } else {
                prev = e;
                e = nextEdge(e);
            }
        }
        v = nextVertex(v);
    }

    adrVertex P = firstVertex(G);
    adrVertex temp = NULL;
    while (P != NULL && idVertex(P) != halte) {
        temp = P;
        P = nextVertex(P);
    }
    if (P != NULL) {
        if (temp != NULL) {
            nextVertex(temp) = nextVertex(P);
        } else {
            firstVertex(G) = nextVertex(P);
        }
        nextVertex(P) = NULL;
        idVertex(P) = "";
        firstEdge(P) = NULL;
        P = NULL;
    }
}

void deleteRuteDoang(adrVertex P){
    adrEdge e = firstEdge(P);
    while (e != NULL){
        adrEdge next = nextEdge(e);
        nextEdge(e) = NULL;
        destVertexID(e) = " ";
        price(e) = 0;
        e = next;
    }
    firstEdge(P) = NULL;
};


