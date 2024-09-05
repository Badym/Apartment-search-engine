#ifndef klasy_H
#define klasy_H
#include <utility>
#include <iostream>
#include "klasy.h"
#include <vector>
#include <stack>
#include <memory>
#include <queue>


class Preferencje;
class Mieszkanie;

class check
{
	int a;
public:
	check(int b = 0) :a(b) {}
	~check();
};
struct Node {
	std::shared_ptr<Mieszkanie> Mieszk;
	std::shared_ptr<Node> left;
	std::shared_ptr<Node>  right;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Mieszkanie 
{

public:
	virtual void wyswietl()=0;
	virtual bool zgodny(Preferencje A)=0;
	virtual void wyswietlszcz() = 0;
	virtual int getcena() = 0;
	virtual std::ostringstream getall() = 0;
	virtual void stworz()=0;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Mieszkanie_NA
{
	protected:
	std::string typ_oferty;
	int cena;
	std::string miasto;
	std::string ulica;
	int nr_lokalu;
	int liczba_pokoi;
	int metraz;


public:
	Mieszkanie_NA(std::string tr = "-", int cena = 0, std::string miasto = "puste", std::string ul = "-", int nr_lokalu = 0, int liczba_pokoi = 0, int metr = 0);
	void wyswietl();
	void wyswietlszcz();
	bool zgodny(Preferencje A);
	int getcena();
	friend std::ostream& operator<<(std::ostream& os, const Mieszkanie_NA& A);
	std::ostringstream getall();
	void stworz();
};  
std::ostream& operator<<(std::ostream& os, const Mieszkanie_NA& A);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NA_SPRZED : public Mieszkanie,Mieszkanie_NA
{
	std::string raty;

public:

	NA_SPRZED(std::string tr = "-", int cena = 0, std::string miasto = "puste", std::string ul = "-", int nr_lokalu = 0, int liczba_pokoi = 0, int metr = 0, std::string raty=0);
	void wyswietl();
	void wyswietlszcz();
	bool zgodny(Preferencje A);
	int getcena();
	std::ostringstream getall();
	void stworz();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class NA_WYNAJ : public Mieszkanie,Mieszkanie_NA
{

	int czynsz;

public:

	NA_WYNAJ(std::string tr = "-", int cena = 0, std::string miasto = "puste", std::string ul = "-", int nr_lokalu = 0, int liczba_pokoi = 0, int metr = 0,int czynsz=0);
	void wyswietl();
	void wyswietlszcz();
	bool zgodny(Preferencje A);
	int getcena();
	std::ostringstream getall();
	void stworz();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class listaMieszkan
{
	std::shared_ptr<Mieszkanie>* lista_mieszk;
	int ilosc;
	int zajete;

public:
	void usun(int a);
	int dl();
	listaMieszkan(std::string nazwa_pliku, int ile = 0);
	void dodaj(std::shared_ptr<Mieszkanie>&);
	std::shared_ptr<Mieszkanie>& operator[](int a);
	void wyswietl();
	void pusta();
	~listaMieszkan();
	listaMieszkan& operator+=(const std::shared_ptr<Mieszkanie>& other);
};
//istaMieszkan& operator+=(const std::shared_ptr<Mieszkanie>& other);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Preferencje
{
	std::string miasto_p,typ_oferty_p,sortowanie;
	int lpokoi_p, mincena, makscena, metraz_p;

public:

	Preferencje(std::string mias="-", std::string typ_of="-", int lpo=0, int mince=0, int maksc=0, int metr=0,std::string sort="brak");
	friend bool Mieszkanie_NA::zgodny(Preferencje A); ////////////////////////////////////////////////////////////////////////////////////////do drzewa uml jakos
	void setmiasto(std::string A);
	void settypof(std::string A);
	void setlpok(int A);
	void setmincen(int A);
	void setmakscena(int A);
	void setmetr(int A);
	std::string getsort();
	void mias() {
		std::cout << miasto_p << " - ";
	}
	//void operator=(Preferencje B);

	//void zaok();


};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Zgodnosc
{
	std::queue <std::shared_ptr<Mieszkanie>> stos1;
	
public:

	Zgodnosc(listaMieszkan& lis, Preferencje& A); 
	void wyswietl();
	int dl() const;
	void pokaz(int a);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class SortowanieListy {
private:
	std::shared_ptr<Node> root;
public:
	void dodaj(std::shared_ptr<Node>& B,std::shared_ptr<Mieszkanie>& A);
	SortowanieListy();
	void wczytaj(listaMieszkan& ABC);
	void zamien(std::shared_ptr<Node> B, listaMieszkan& ABC);
	std::shared_ptr<Node> getroot() {
		return root;
	}
	//std::shared_ptr<Node> przesun(std::shared_ptr<Node> B);
};





int intator();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Interfejs
{
public:
	virtual std::unique_ptr<Interfejs> strona(Preferencje& A, listaMieszkan& ABCD) = 0;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Menu : public Interfejs
{
public:
	std::unique_ptr < Interfejs> strona(Preferencje& A, listaMieszkan& ABCD);
	
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Lista : public Interfejs
{
public:
	std::unique_ptr < Interfejs > strona(Preferencje& A, listaMieszkan& ABCD);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Filtry : public Interfejs
{
public:
	std::unique_ptr < Interfejs > strona(Preferencje& A, listaMieszkan& ABCD);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UsunFiltr : public Interfejs
{
public:
	std::unique_ptr < Interfejs > strona(Preferencje& A, listaMieszkan& ABCD);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Sortowanie : public Interfejs
{
public:
	std::unique_ptr<Interfejs> strona(Preferencje& A, listaMieszkan& ABCD) {
		SortowanieListy N;
		N.wczytaj(ABCD);
		ABCD.pusta();
		N.zamien(N.getroot(), ABCD);
		Sortowanie& operator+=(const int a,Sortowanie A);
		//N.zamien(N.getroot(), ABCD, 0);



		return std::make_unique<Menu>();
	}

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Usun : public Interfejs
{
public:
	std::unique_ptr < Interfejs > strona(Preferencje& A, listaMieszkan& ABCD);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Dodaj : public Interfejs
{
public:
	std::unique_ptr < Interfejs > strona(Preferencje& A, listaMieszkan& ABCD);
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Stop : public Interfejs
{
public:
	std::unique_ptr<Interfejs> strona(Preferencje& A, listaMieszkan& ABCD);

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif