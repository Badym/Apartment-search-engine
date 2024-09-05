#include <iostream>
#include "klasy.h"
#include <sstream>
#include <fstream>

#define _CRTDBG_MAP_ALLOC
//int Mieszkanie_NA::licznik = 1;

check::~check() {
	_CrtDumpMemoryLeaks();
}




int intator() {
	std::string input;
	std::cin >> input;
	bool isDigits = true;
	for (char c : input) {
		if (!std::isdigit(c)) {
			isDigits = false;
			break;
		}
	}

	if (isDigits) {
		return std::stoi(input);
	}
	else {
		return 0;
	}
}
//////////////////////NA_WYNAJ////////////////////////////
NA_WYNAJ::NA_WYNAJ(std::string tr, int c, std::string m, std::string ul, int nl, int lp, int metr, int czyn) :Mieszkanie_NA(tr, c, m, ul, nl, lp, metr), czynsz(czyn)
{}

void NA_WYNAJ::wyswietl()
{
	Mieszkanie_NA::wyswietl();
}

bool NA_WYNAJ::zgodny(Preferencje A)
{
	return Mieszkanie_NA::zgodny(A);
}

void NA_WYNAJ::wyswietlszcz() {
	Mieszkanie_NA::wyswietlszcz();
	std::cout << "czynsz: " << czynsz;
}

int NA_WYNAJ::getcena() {
	return cena;
}

std::ostringstream NA_WYNAJ::getall() {
	std::ostringstream ss = Mieszkanie_NA::getall();
	ss << "\t" << czynsz;
	return ss;
}
void NA_WYNAJ::stworz() {
	Mieszkanie_NA::stworz();
	std::cout << "podaj wartosc czynszu" << std::endl;
	int odp = intator();
	typ_oferty = "wynajem";
	czynsz = odp;
}
//////////////////////NA_SPRZED////////////////////////////
NA_SPRZED::NA_SPRZED(std::string tr, int c, std::string m, std::string ul, int nl, int lp, int metr, std::string rat) :Mieszkanie_NA(tr, c, m, ul, nl, lp, metr), raty(rat)
{}

void NA_SPRZED::wyswietl()
{
	Mieszkanie_NA::wyswietl();
}

bool NA_SPRZED::zgodny(Preferencje A)
{
	return Mieszkanie_NA::zgodny(A);
}

void NA_SPRZED::wyswietlszcz() {
	Mieszkanie_NA::wyswietlszcz();
	std::cout << "raty: " << raty << std::endl;
}

int NA_SPRZED::getcena() {
	return cena;
}
std::ostringstream NA_SPRZED::getall() {
	std::ostringstream ss = Mieszkanie_NA::getall();
	ss << "\t" << raty;
	return ss;
}
void NA_SPRZED::stworz() {
	Mieszkanie_NA::stworz();
	std::cout << "raty?" << std::endl;
	std::cout << "1) Tak" << std::endl;
	std::cout << "2) Nie" << std::endl;
	int odp = intator();
	typ_oferty = "sprzedaz";
	if (odp == 1) {
		raty = "tak";
	}
	if (odp == 2) {
		raty = "nie";
	}
	else {
		std::cout << "raty zostaly ustawione na - NIE";
		raty = "nie";
	}
}
//////////////////////Mieszkanie_Na/////////////////////////
Mieszkanie_NA::Mieszkanie_NA(std::string tr, int c, std::string m, std::string ul, int nl, int lp, int metr) :typ_oferty(tr), cena(c), miasto(m), ulica(ul), nr_lokalu(nl), liczba_pokoi(lp), metraz(metr) //abs(A.metraz_p-metraz)<10
{}

std::ostream& operator<<(std::ostream& os, const Mieszkanie_NA& A) 
{
	os << A.typ_oferty << " \t " << A.miasto << "  \t " << A.ulica << "   \t " << A.nr_lokalu << "\t    CENA: " << A.cena << std::endl;
	return os;
}
std::ostringstream Mieszkanie_NA::getall() {
	std::ostringstream ss;
	ss << typ_oferty <<"\t" << cena << "\t" << miasto << "\t" << ulica << "\t" << nr_lokalu << "\t" << liczba_pokoi << "\t" << metraz;
	return ss;
}
void Mieszkanie_NA::wyswietl()
{
	std::cout << *this;
}

bool Mieszkanie_NA::zgodny(Preferencje A)
{
	if ((A.miasto_p == "-" or A.miasto_p == miasto) and (A.lpokoi_p == liczba_pokoi or A.lpokoi_p == 0) and (A.mincena <= cena) and (A.makscena == 0 or A.makscena >= cena) and (A.typ_oferty_p == "-" or A.typ_oferty_p == typ_oferty) and (A.metraz_p == metraz or A.metraz_p == 0 )) {
		return 1;
	}
	return 0;
}
void Mieszkanie_NA::wyswietlszcz() {
	system("cls");
	std::cout << std::endl;
	std::cout << "Mieszkanie na " << typ_oferty<<std::endl;
	std::cout << "Lokalizacja: " << miasto << " ul." << ulica << " " << nr_lokalu<<std::endl;
	std::cout << "liczba pokoi: " << liczba_pokoi << std::endl;
	std::cout << "metraz: " << metraz << std::endl;
	std::cout << "Cena: " << cena << std::endl;
}

int Mieszkanie_NA::getcena() {
	return cena;
}

void Mieszkanie_NA::stworz() {
	std::cout << "jaka cena?" << std::endl;
	int odp;
	std::string odp1;
	odp = intator();
	cena = odp;
	std::cout << "Miasto?" << std::endl;
	std::cin >> odp1;
	miasto=odp1;
	std::cout << "ulica?" << std::endl;
	std::cin >> odp1;
	ulica = odp1;
	std::cout << "numer lokalu?" << std::endl;
	odp = intator();
	nr_lokalu = odp;
	std::cout << "l. pokoi?" << std::endl;
	odp = intator();
	liczba_pokoi = odp;

}
//////////////////////ListaMieszkan////////////////////////

listaMieszkan::listaMieszkan(std::string nazwa_pliku,int ile) :ilosc(ile)
{
	lista_mieszk = new std::shared_ptr<Mieszkanie>[ilosc];
	//lista_mieszk = new Mieszkanie*[ilosc];
	zajete = 0;
	
	std::ifstream input_file(nazwa_pliku);
	std::string line;
	std::string typ_oferty, miasto, ulica,raty;
	int cena, pokoje, nr_loka, metraz,czynsz;

	while (std::getline(input_file, line)) {
		std::stringstream ss(line);

		ss >> typ_oferty >> cena >> miasto >> ulica >> nr_loka >> pokoje >> metraz;
		if (typ_oferty == "wynajem") {
			ss >> czynsz;
			if (zajete < ilosc) {
				//NA_WYNAJ tmpa(typ_oferty, cena, miasto, ulica, nr_loka, pokoje, metraz,czynsz);
				//tmpa.wyswietl();
				lista_mieszk[zajete] = std::make_shared<NA_WYNAJ>(typ_oferty, cena, miasto, ulica, nr_loka, pokoje, metraz, czynsz);
				//lista_mieszk[zajete] = new NA_WYNAJ(typ_oferty, cena, miasto, ulica, nr_loka, pokoje, metraz, czynsz);
				zajete++;
				//delete lista_mieszk[zajete];
			}
		}

		else if (zajete < ilosc) {
			ss >> raty;
			lista_mieszk[zajete] = std::make_shared<NA_SPRZED>(typ_oferty, cena, miasto, ulica, nr_loka, pokoje, metraz, raty);
			//lista_mieszk[zajete] = new NA_SPRZED(typ_oferty, cena, miasto, ulica, nr_loka, pokoje, metraz, raty);
			zajete++;
			//delete lista_mieszk[zajete];
			
		}
	}
	input_file.close();
	
}

int listaMieszkan::dl()
{
	return zajete;
}

listaMieszkan& listaMieszkan::operator+=(const std::shared_ptr<Mieszkanie>& a)
{
	if (zajete < ilosc)
	{
		lista_mieszk[zajete] = a;
		zajete++;
	}
	else
	{
		std::cout << "przepelnienie";
		exit(0);
	}
	return *this;
}
/*
void listaMieszkan::dodaj(std::shared_ptr<Mieszkanie>& a)
{
	if (zajete < ilosc) 
	{
		lista_mieszk[zajete] = a;
		zajete++;
	}
	else
	{
		std::cout << "przepelnienie";
	}

}*/

std::shared_ptr<Mieszkanie>& listaMieszkan::operator[](int a)
{
	if (a < ilosc and a <= zajete) {
		return lista_mieszk[a];
	}

	std::cout << std::endl << std::endl << std::endl << std::endl;
	std::cout << "OUT OF RANGE!" << std::endl << std::endl << std::endl;
	exit(0);
}

void listaMieszkan::wyswietl()
{
	
	for (int i = 0; i < zajete; i++) {
		if (lista_mieszk[i] == nullptr) {
			std::cout << "puste";
		}
		else {
			lista_mieszk[i]->wyswietl();
		}
		
	}
}

void listaMieszkan::pusta() {

	for (int i = 0; i < ilosc; i++) {
		lista_mieszk[i] = nullptr;
	}
	zajete = 0;
}

listaMieszkan::~listaMieszkan() 
{
	std::ofstream file("lista.txt");
	if (file.is_open()) {
		// Zapisanie argumentów listy do pliku
		for (int i = 0; i < zajete;i++) {
			file << lista_mieszk[i]->getall().str() << std::endl;
		}
		// Zamkniêcie pliku
		file.close();
	}





	delete[] lista_mieszk;
	//_CrtDumpMemoryLeaks();
}
void listaMieszkan::usun(int a) {
	for (int i = a; i < zajete - 1; i++) {
		lista_mieszk[i] = lista_mieszk[i + 1];
	}
	zajete--;
}


//////////////////////Preferencje////////////////////////
Preferencje::Preferencje(std::string mias, std::string typ_of, int lpo, int mincen, int maksce, int metr, std::string sort) :miasto_p(mias),typ_oferty_p(typ_of),lpokoi_p(lpo),mincena(mincen),makscena(maksce),metraz_p(metr),sortowanie(sort) {}


void Preferencje::setmiasto(std::string A)
{
	miasto_p = A;
}

void Preferencje::settypof(std::string A)
{
	typ_oferty_p = A;
}

void Preferencje::setlpok(int A)
{
	lpokoi_p = A;
}

void Preferencje::setmincen(int A)
{
	mincena = A;
}

void Preferencje::setmakscena(int A)
{
	makscena = A;
}

void Preferencje::setmetr(int A)
{
	metraz_p = A;
}

std::string Preferencje::getsort() {
	return sortowanie;
}
/*
void Preferencje::operator =(Preferencje B) {
	miasto_p = B.miasto_p;
	typ_oferty_p = B.typ_oferty_p;
	sortowanie = B.sortowanie;
	lpokoi_p = B.lpokoi_p;
	mincena = B.mincena;
	makscena = B.makscena;
	metraz_p = B.metraz_p;
}*/

//////////////////////Zgodnosc///////////////////////////
Zgodnosc::Zgodnosc(listaMieszkan& lis, Preferencje& A)
{
	for (int i = 0; i < lis.dl(); i++)
	{
		if (lis[i]->zgodny(A))
		{
			stos1.push(lis[i]);
		}
	}
}



void Zgodnosc::wyswietl() 
{
	if (stos1.size() == 0) {
		std::cout << "nie ma w Bazie takich mieszkan" << std::endl;
	}
	else {
		int dl = stos1.size();
		int licz = 1;
		while (dl>0) {
			std::cout << licz << ")  \t";
			stos1.front()->wyswietl();
			stos1.push(stos1.front());
			stos1.pop();
			dl -= 1;
			licz += 1;
		}

	}

}
int Zgodnosc::dl() const
{
	return stos1.size();
}

void Zgodnosc::pokaz(int a) 
{
	int dl = stos1.size();
	int licz = 1;
	while (dl > 0) {
		if (licz == a) {
			stos1.front()->wyswietlszcz();
		}
		stos1.push(stos1.front());
		stos1.pop();
		dl -= 1;
		licz += 1;
	}
}


//////////////////////SortowanieListy///////////////////////////
/*
	struct Node {
		Mieszkanie* AB;
		Node* left;
		Node* right;
	};
	Node* root;
*/

void SortowanieListy::dodaj(std::shared_ptr<Node>& B,std::shared_ptr<Mieszkanie>& A)
{
	if (B == nullptr) {
		B = std::make_shared<Node>();
		B->Mieszk = A;
		B->left = nullptr;
		B->right = nullptr;
	}
	else if (A->getcena() < (B->Mieszk)->getcena()) {
		dodaj(B->left, A);
	}
	else {
		dodaj(B->right, A);
	}
	
}

SortowanieListy::SortowanieListy() {
	root = nullptr;
}

void SortowanieListy::wczytaj(listaMieszkan& ABC) {
	for (int a = 0; a < ABC.dl(); a++) {
		dodaj(root, ABC[a]);
	}
}
void SortowanieListy::zamien(std::shared_ptr<Node> node, listaMieszkan& ABC) {
	/*
	if (node==nullptr) {
		
	}*/
	//node->AB->wyswietl();
	//std::cout << "bb1" << std::endl;
	if (node->left != nullptr) {
		//std::cout << "bb2" << std::endl;
		zamien(node->left, ABC);
	}
	
	ABC+=node->Mieszk;

	//ABC[ABC.dl()] = node->Mieszk;

	//ABC.push_back(node->AB);

	if (node->right != nullptr) {
		//std::cout << "bb3" << std::endl;
		zamien(node->right, ABC);
	}

}

///////////////////////////NR_1/////////////////////////////////
std::unique_ptr<Interfejs> Menu::strona(Preferencje& A, listaMieszkan& ABCD)
{
	system("cls");
	std::cout << "+------------Wyszukiwarka Mieszkan-------------+" << std::endl;
	std::cout << "|--------------------Menu----------------------|" << std::endl;
	std::cout << "|----------------------------------------------|" << std::endl;
	std::cout << "| 1) Wyswietl liste mieszkan                   |" << std::endl;
	std::cout << "| 2) Dostosuj Filtry                           |" << std::endl;
	std::cout << "| 3) Usun Filtry                               |" << std::endl;
	std::cout << "| 4) Ustaw Sortowanie                          |" << std::endl;
	std::cout << "| 5) Dodaj Mieszkanie                          |" << std::endl;
	std::cout << "| 6) Usun Mieszkanie                           |" << std::endl;
	std::cout << "| 7) Wyjscie                                   |" << std::endl;
	std::cout << "+----------------------------------------------+" << std::endl;
	std::cout << " Wpisz twoj wybor: ";
	int a;
	a = intator();

	switch (a) {
	case 1:
		return std::make_unique<Lista>();
		break;
	case 2:
		return std::make_unique<Filtry>();
	case 3:
		return std::make_unique<UsunFiltr>();
	case 4:
		return std::make_unique<Sortowanie>();
	case 5:
		return std::make_unique<Dodaj>();
	case 6:
		return std::make_unique<Usun>();
	case 7:
		return std::make_unique<Stop>();
	default:
		return std::make_unique<Menu>();
	}
}

std::unique_ptr<Interfejs> Lista::strona(Preferencje& A, listaMieszkan& ABCD)
{
	system("cls");
	std::cout << "+------------Wyszukiwarka Mieszkan-------------+" << std::endl;
	std::cout << "|--------------------Lista---------------------|" << std::endl;
	std::cout << "+----------------------------------------------+" << std::endl;
	int dl;


	Zgodnosc kolej(ABCD, A);
	kolej.wyswietl();
	dl=kolej.dl();
	

	std::cout << dl+1 <<") Wroc do Menu                              " << std::endl;


	int a=dl+2;
	while (a > dl+1) {

		std::cout << " Wpisz twoj wybor: ";
		a = intator();
		if (a <= dl and a>0) {
			std::cout << "                  INFORMACJE O MIESZKANIU " << std::endl;
			kolej.pokaz(a);
			std::cout << "Wpisz co kolwiek aby powrocic do menu" << std::endl;
			a = intator();
			return std::make_unique<Menu>();
		}

		if (a = dl + 1) {
			return std::make_unique<Menu>();
		}
		else {
			std::cout << "niepoprawny znak" << std::endl;
			a = dl + 2;
			//return std::make_unique<Lista>();
		}
		
	}
	
}

std::unique_ptr<Interfejs> Filtry::strona(Preferencje& A, listaMieszkan& ABCD) {
	system("cls");
	std::cout << "+------------Wyszukiwarka Mieszkan-------------+" << std::endl;
	std::cout << "|-------------Ustwanienia Filtrow--------------|" << std::endl;
	std::cout << "|-------------Co chesz ustawic?----------------|" << std::endl;
	std::cout << "|----------------------------------------------|" << std::endl;
	std::cout << "| 1) miasto                                    |" << std::endl;
	std::cout << "| 2) ilosc pokoi                               |" << std::endl;
	std::cout << "| 3) metraz                                    |" << std::endl;
	std::cout << "| 4) minimalna cena                            |" << std::endl;
	std::cout << "| 5) maksymalna cena                           |" << std::endl;
	std::cout << "| 6) typ oferty (sprzedaz / wynajem)           |" << std::endl;
	std::cout << "| 7) Wyjscie                                   |" << std::endl;
	std::cout << "+----------------------------------------------+" << std::endl;
	std::cout << " Wpisz twoj wybor: ";
	std::string b;
	int a;
	a = intator();
	std::string name;
	int number;
	switch (a) {
		
	case 1:
		system("cls");
		std::cout <<"Wpisz nazwe miasta: ";
		std::cin >> name;
		A.setmiasto(name);
		return std::make_unique<Filtry>();

	case 2:
		system("cls");
		std::cout << "Wpisz ilosc pokoi: ";
		std::cin >> number;
		A.setlpok(number);
		return std::make_unique<Filtry>();
	case 3:
		system("cls");
		std::cout << "Wpisz metraz(wyniki beda +/- 10m2): ";
		std::cin >> number;
		A.setmetr(number);
		return std::make_unique<Filtry>();
	case 4:
		system("cls");
		std::cout << "Wpisz minimalna cene: ";
		std::cin >> number;
		A.setmincen(number);
		return std::make_unique<Filtry>();
	case 5:
		system("cls");
		std::cout << "Wpisz maksymalna cene: ";
		std::cin >> number;
		A.setmakscena(number);
		return std::make_unique<Filtry>();
	case 6:
		system("cls");
		std::cout << "Wpisz typ oferty jaki Cie interesuje (sprzedaz lub wynajem): ";
		std::cin >> name;
		A.settypof(name);
		return std::make_unique<Filtry>();
	case 7:
		return std::make_unique<Menu>();
	default:
		system("cls");
		std::cout << "NIE POPRAWNA CYFRA "<<std::endl;
		std::cout << "wpisz jakas cyfre aby przejsc dalj" << std::endl;
		a = intator();
		return std::make_unique<Filtry>();
	}
}

std::unique_ptr < Interfejs > UsunFiltr::strona(Preferencje& A, listaMieszkan& ABCD) {
	system("cls");
	std::cout << "+------------Wyszukiwarka Mieszkan-------------+" << std::endl;
	std::cout << "|---------------Usuwanie Filtrow---------------|" << std::endl;
	std::cout << "|------Czy na pewno chcesz usunac filtry?------|" << std::endl;
	std::cout << "|----------------------------------------------|" << std::endl;
	std::cout << "| 1) TAK                                       |" << std::endl;
	std::cout << "| 2) NIE                                       |" << std::endl;
	std::cout << "+----------------------------------------------+" << std::endl;
	std::cout << " Wpisz twoj wybor: ";
	std::string a;
	while (true) {

		std::cin >> a;
		if (a == "1") {
			Preferencje B;
			A = B;
			return std::make_unique<Menu>();
		}
		if (a == "2") {
			return std::make_unique<Menu>();
		}
		else {
			std::cout << "zla odpowiedz wybierz jeszcze raz:" << std::endl;
			
		}
	}
}

std::unique_ptr<Interfejs> Stop::strona(Preferencje& A, listaMieszkan& ABCD) {
	system("cls");
	std::cout << "+------------Wyszukiwarka Mieszkan-------------+" << std::endl;
	std::cout << "|--------Dziekujemy za uzywanie naszej---------|" << std::endl;
	std::cout << "+------------------aplikacji-------------------+" << std::endl;
	return nullptr;
}

std::unique_ptr<Interfejs> Usun::strona(Preferencje& A, listaMieszkan& ABCD) {
	system("cls");
	std::cout << "+------------Wyszukiwarka Mieszkan-------------+" << std::endl;
	std::cout << "|----------------usun Mieszkanie---------------|" << std::endl;
	std::cout << "+----------------------------------------------+" << std::endl;
	std::cout << "+------Wybierz mieszkanie do usuniecia---------+" << std::endl;
	int dl;
	Preferencje AA;
	Zgodnosc kolej(ABCD, AA);
	kolej.wyswietl();
	dl = kolej.dl();
	std::cout << dl + 1 << ") Wroc do Menu                              " << std::endl;

	int a = dl + 2;
	while (a > dl + 1) {
		std::cout << " Wpisz twoj wybor: ";
		a = intator();
		if (a <= dl and a != 0) {
			ABCD.usun(a-1);
			return std::make_unique<Menu>();
		}

		if (a = dl + 1) {
			return std::make_unique<Menu>();
		}
		else {
			std::cout << "niepoprawny znak" << std::endl;
			a = dl + 2;
			return std::make_unique<Lista>();
		}

	}
}

std::unique_ptr<Interfejs> Dodaj::strona(Preferencje& A, listaMieszkan& ABCD) {
	system("cls");
	std::cout << "+------------Wyszukiwarka Mieszkan-------------+" << std::endl;
	std::cout << "|---------------dodaj Mieszkanie---------------|" << std::endl;
	std::cout << "+----------------------------------------------+" << std::endl;
	std::cout << "Wybierz typ mieszkania" << std::endl;
	std::cout << "1)Na wynajem" << std::endl;
	std::cout << "2)Na sprzedaz" << std::endl;
	std::cout << "3)wyjdz" << std::endl;
	int odp = intator();
	std::shared_ptr<Mieszkanie> X;
	if (odp == 1) {
		X = std::make_shared<NA_WYNAJ>("wynajem", 0, "puste", "-", 0, 0, 0, 0);
		X->stworz();
	}
	if (odp == 2) {
		X = std::make_shared<NA_SPRZED>("sprzedaz", 0, "puste", "-", 0, 0, 0, "-");
		X->stworz();
	}
	if (odp == 3) {
		return std::make_unique<Menu>();
	}
	ABCD += X;
	return std::make_unique<Menu>();
}









