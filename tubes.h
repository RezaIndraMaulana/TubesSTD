#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <iostream>
#define firstVertex(G) G.firstVertex
#define firstEdge(V) V->firstEdge
#define nextVertex(V) V->nextVertex
#define nextEdge(E) E->nextEdge
#define idVertex(V) V->idVertex
#define destVertexID(E) E->destVertexID
#define price(E) E->price
using namespace std;
const int MAX_VERTEX = 15;

typedef struct vertex *adrVertex;
typedef struct edge *adrEdge;

struct vertex {
    string idVertex;
    adrVertex nextVertex;
    adrEdge firstEdge;
};

struct edge {
    string destVertexID;
    int price;
    adrEdge nextEdge;
};

struct graph {
    adrVertex firstVertex;
};

void createVertex(string newVertexID, adrVertex &v); //sudah
void initGraph(graph &G); //sudah
void addVertex(graph &G, string newVertexID); //sudah
void createEdge(string tujuan, int price, adrEdge &e); //sudah
void addEdge(graph &G, string cariTujuan, string tujuan, int price); //sudah
void Menu(); // sudah
void showVertex(graph &G); //sudah
void showEdge(graph &G); //sudah
void showAll(graph &G); //sudah

void pencarianRuteTermurah(graph &G, string tAwal, string tTujuan); //sudah
void pencarianRuteTermahal(graph &G, string tAwal, string tTujuan); //sudeh
adrVertex cariHalte(graph &G, string tempat); //sudah
adrEdge cariEdge(graph &G, string &awal, string &akhir); //sudah
void perbaruiRute(adrEdge e, int harga); //sudah
void updateRoute(graph &G, string &halteAwal, string &halteAkhir, int hargaBaru);
void deleteHalteDanRute(graph &G, string asal, string tujuan); //sudah
void deleteHalteDoang(graph &G,string halte); //sudah
void deleteRuteDoang(adrVertex P);//sudah

#endif // TUBES_H_INCLUDED
