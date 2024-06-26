#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct node {
    int PatientId;
    string PatientInfo;
    int PatientAge;
    int Degree;                                         // Hasta Bilgilerinin tutuldu�u lise yap�s�
    string Diagnosis;
    node* next;
    node* prev;
};

struct node2
{
    string Username;
    int Password;
    node2* next;                                   // Doktor Bilgilerinin tutuldu�u lise yap�s�
    node2* prev;
};

struct node3 {
    int SurgeryId;
    string StartSurgeryDate;
    string EndSurgeryDate;                          // Ameliyat Bilgilerinin tutuldu�u lise yap�s�
    node3* next;
    node3* prev;
};

node2 doctors[3] = {
    {"emirasili", 111},
    {"burcukosucu", 222},                           //  node2 listeindeli verileri tutan bir doctors dizisi
    {"fatmaakalin", 333}
};

node* basdugum = NULL;
node* tail = NULL;

node3* basdugum3 = NULL;                           // �ift y�nl� ba�l� listesyi �ift y�nl� dairesel  ba�l� liste yapmak i�in gerekli tan�mlamalar
node3* tail3 = NULL;

void convertToCircular() {
    if (basdugum == NULL)
    {
        // Hasta listesini �ift y�nl� dairesel ba�l� listeye �eviren fonksiyon
    }
    return;

    tail->next = basdugum;
    basdugum->prev = tail;
}

void convertToCircular3() {
    if (basdugum3 == NULL)
    {
        // Ameliyat listesini �ift y�nl� dairesel ba�l� listeye �eviren fonksiyon
    }
    return;

    tail3->next = basdugum3;
    basdugum3->prev = tail3;
}

int generateVerificationCode() {
    srand(time(nullptr));                           // 4 haneli do�rulama kodu olu�turan fonksiyon
    return rand() % 9000 + 1000;
}

void sendVerificationCode() {
    int verificationCode = generateVerificationCode();
    ofstream printCode("DogrulamaKodu.txt", ios::trunc);
    cout << "Dogrulama kodunuz gonderildi. Lutfen Dosyalarinizi kontrol edin." << endl;                 // Do�rulama kodunu dosyaya g�nderen fonksiyon
    printCode << "Do�rulama kodu: " << verificationCode << endl;
}


bool doctorLogin(node2* basdugum, string username, int password) {
    node2* temp = basdugum;
    do {
        if (temp->Username == username && temp->Password == password) {
            return true;
        }                               // Doktor giri�inde doktorlar�n bilgilerini kontrol edip giri� sa�layan fonksiyon

        temp = temp->next;
    } while (temp != basdugum);

    return false;
}


void dash() {
    for (int i = 0; i < 30; i++)
    {
        cout << "--";                                // tasar�m g�zelli�i i�in baz� yerlerde �izgi �ekmek i�in kulland�m
    }

}

struct node* addPatient(node* basdugum, int ID, string info, int age, int degree, string diagnosis) {
    struct node* nnode = new node();

    nnode->PatientId = ID;
    nnode->PatientInfo = info;
    nnode->PatientAge = age;                        // D��ar�dan girilen hasta bilgilerini listeye ekleyen fonksiyon
    nnode->Degree = degree;
    nnode->Diagnosis = diagnosis;

    if (basdugum == NULL) {
        nnode->next = NULL;                         // Basdugum nullptr ise yeni nnode u basugum yapar
        nnode->prev = NULL;
        basdugum = nnode;
    }
    else if (basdugum->next == NULL) {
        basdugum->next = nnode;
        nnode->prev = basdugum;                    // Basdugumun nexti nullptr ise yeni nnode u basdugumden sonraki d���me atar
        basdugum->prev = NULL;
        nnode->next = NULL;
    }
    else {
        node* iter = basdugum;
        while (iter->next != NULL)
        {
            iter = iter->next;                    // Dugumleri gezerek nullptr olan dugumu yakalar ve yeni nnode u oraya ekler
        }
        iter->next = nnode;
        nnode->prev = iter;
        nnode->next = NULL;
    }
    return basdugum;
}

struct node3* addSurgery(node3* basdugum, int ID, string startDate, string endDate) {
    struct node3* nnode = new node3();

    nnode->SurgeryId = ID;
    nnode->StartSurgeryDate = startDate;                // Ameliyat bilgilerini listeye ekleyen fonksiyon
    nnode->EndSurgeryDate = endDate;

    if (basdugum == NULL) {
        nnode->next = NULL;
        nnode->prev = NULL;                             // Basdugum nullptr ise yeni nnode u basugum yapar
        basdugum = nnode;
    }
    else if (basdugum->next == NULL) {
        basdugum->next = nnode;
        nnode->prev = basdugum;                         // Basdugumun nexti nullptr ise yeni nnode u basdugumden sonraki d���me atar
        basdugum->prev = NULL;
        nnode->next = NULL;
    }
    else {
        node3* iter = basdugum;
        while (iter->next != NULL)
        {
            iter = iter->next;                          // Dugumleri gezerek nullptr olan dugumu yakalar ve yeni nnode u oraya ekler
        }
        iter->next = nnode;
        nnode->prev = iter;
        nnode->next = NULL;
    }
    return basdugum;
}

struct node* deletePatient(node* basdugum, int deleteID) {
    struct node* nnode = new node();
    if (basdugum == NULL)
    {                                                                               // D��ar�dan girilen ID numaras�na sahip hastay� silen fonksiyon
        cout << "Hasta yok";
    }                                                                               // Hasta yoksa hasta yok yazar
    else if (basdugum->next == NULL && basdugum->PatientId == deleteID)
    {
        delete basdugum;
        basdugum = NULL;                                                            // Basugumun nexti null sa ve silinecek hasta ilk s�radaysa basdugumu siler
    }
    else {
        if (basdugum->PatientId == deleteID)
        {
            node* temp = basdugum->next;
            temp->prev = basdugum;
            delete basdugum;                                                        // Silinecek hasta ilk s�radaysa 2. s�radaki hastay� basdugum yapar ve basdugumu siler
            temp->prev = NULL;
            basdugum = temp;
        }
        else {
            node* iter = basdugum;
            while (iter->next != NULL && iter->next->PatientId != deleteID)
            {
                iter = iter->next;                                                  // Silinecek hastay� bulmak i�in listeyi dola��r
            }
            if (iter->PatientId != deleteID && iter->next == NULL)
            {
                cout << "Boyle Bir Hasta Numarasi Yok" << endl;                      // Girilen ID'ye sahip hasta yoksa hastay� bulamaz
                return basdugum;
            }
            else if (iter->next->PatientId == deleteID && iter->next->next == NULL)
            {
                node* temp = iter->next;
                temp->prev = iter;
                delete temp;                                                        // Silinecek hasta 2. s�radaysa ve 3. s�radaki nullptr ise 2. s�radakini siler
                iter->next = NULL;
            }
            else {
                node* stemp = iter->next->next;
                node* deletepatient = iter->next;
                delete deletepatient;                                               // Silinecek ID ye sahip hastay� bulur ve siler
                iter->next = stemp;
                stemp->prev = iter;
            }

        }

    }

    return basdugum;
}

struct node3* deleteSurgery(node3* basdugum, int deleteID) {                      // D��ar�dan girilen ID numaras�na sahip ameliyat� silen fonksiyon
    if (basdugum == NULL) {
        cout << "Ameliyat Yok" << endl;                                             // Ameliyat yoksa ameliyat yok yazar
        return basdugum;
    }

    if (basdugum->SurgeryId == deleteID) {
        node3* temp = basdugum->next;
        delete basdugum;
        if (temp != NULL) {                                                          // Silinecek hasta ilk s�radaysa 2. s�radaki hastay� basdugum yapar ve basdugumu siler
            temp->prev = NULL;
        }
        return temp;
    }

    node3* iter = basdugum;
    while (iter != NULL && iter->SurgeryId != deleteID) {                           // Silinecek ameliyat� bulmak i�in listeyi dola��r
        iter = iter->next;
    }

    if (iter == NULL) {
        cout << "B�yle bir ameliyat numarasi yok" << endl;                          // Girilen ID'ye sahip ameliyat yoksa ameliyat� bulamaz
        return basdugum;
    }

    if (iter->next == NULL) {
        iter->prev->next = NULL;
        delete iter;
    }
    else {
        node3* stemp = iter->next->next;
        delete iter->next;                                                          // Silinecek ID ye sahip ameliyat� bulur ve siler
        iter->next = stemp;
        if (stemp != NULL) {
            stemp->prev = iter;
        }
    }
    return basdugum;
}


void printPatient(node* basdugum) {
    if (basdugum == NULL) {
        cout << "Hasta Yok" << endl;
    }
    node* temp = basdugum;
    while (temp != NULL) {

        cout << "Hasta Numarasi: " << temp->PatientId
            << " Hasta Ad Soyad: " << temp->PatientInfo
            << " Hasta Yasi: " << temp->PatientAge              // Hasta bilgilerini yazan fonksiyon
            << " Hastalik Derecesi: "
            << temp->Degree << " Teshis: "
            << temp->Diagnosis << endl;
        temp = temp->next;
    }
}

void printSurgery(node3* basdugum, node* patient) {
    if (basdugum == NULL) {
        cout << "Ameliyat Yok" << endl;
    }
    node3* temp = basdugum;
    while (temp != NULL) {
        node* iter = patient;
        while (iter != NULL) {
            if (iter->PatientId == temp->SurgeryId) {
                cout << "ID: " << temp->SurgeryId;
                cout << " Hasta Ad Soyad: " << iter->PatientInfo;
                cout << " Hasta Yasi: " << iter->PatientAge;
                cout << " Hastalik Derecesi: " << iter->Degree;                  // Ameliyat bilgilerini yazan fonksiyon
                cout << " Teshis: " << iter->Diagnosis;
                cout << " Baslangic Zamani: " << temp->StartSurgeryDate;
                cout << " Bitis Zamani: " << temp->EndSurgeryDate;
                cout << endl;
                break;
            }
            iter = iter->next;
        }
        temp = temp->next;
    }
}

void calculateFee(node3* basdugum, node* hasta, int ID, string insurance) {                // Ameliyat �cretini hesaplayan fonksiyon
    int fee;
    if (basdugum == NULL)
    {
        cout << "Hesaplanacak Ameliyat Yok" << endl;                                    // Ameliyat yoksa hesaplamaz
    }
    else {
        node* iter = hasta;
        node3* temp = basdugum;
        while (temp != NULL)
        {
            if (temp->SurgeryId == ID)                                            // D��ardan girilen ID ye sahip hastan�n ameliyat �cretini hesaplamak i�in kontrol eder
            {
                cout << "Ucret Hesaplaniyor!!" << endl;
                while (iter != NULL) {
                    if (iter->PatientId == ID) {                                // Ameliyar �creti hesaplanacak hastan�n bilgilerini yazmak i�in kontrol
                        break;
                    }
                    iter = iter->next;
                }
                if (iter != NULL) {
                    if (insurance == "emekli")
                    {
                        fee = 3000;
                    }
                    else if (insurance == "ogrenci")                          // Hastan�n sigorta tipine g�re �cret belirleme
                    {
                        fee = 4500;
                    }
                    else if (insurance == "calisan")
                    {
                        fee = 5000;
                    }
                    else {
                        cout << "Sigortaniz bulunmamaktadir." << endl;
                        fee = 15000;                                                    // Ameliyat �crei hesaplanan hastay� ve �creti yazar
                    }
                    cout << "ID: " << temp->SurgeryId << " Hasta Ad Soyad: " << iter->PatientInfo << " Hesaplanan Ameliyat Ucreti: " << fee << " TL'dir." << endl;
                }
                else {
                    cout << "Hasta bulunamadi!" << endl;
                }
                break;
            }
            temp = temp->next;
        }
    }
}

void calculatePriority(node* basdugum) {                    // Ameliyat �nceli�ini belirleyen fonksiyon
    int priority;
    if (basdugum == NULL)
    {
        cout << "Hesaplanacak Ameliyat Yok" << endl;             // Ameliyat yoksa ameliyat yok yazar
    }
    else
    {
        node* temp = basdugum;
        while (temp->next != basdugum)
        {
            priority = temp->PatientAge * temp->Degree;                 // Ameliyat �nceli�ini hastan�n ya�� ve derecesine g�re belirler ve ekrana yazar
            cout << "ID: " << temp->PatientId << " Hasta Ad Soyad: " << temp->PatientInfo << " Hesaplanan Oncelik Degeri " << priority << "'dir" << endl;
            temp = temp->next;
            if (temp == tail)
            {
                break;
            }
        }
    }

}

struct Survey {
    vector<int> temizlik;
    vector<int> personelDavranisi;
    vector<int> mahremiyet;
    vector<int> hizmetler;
    vector<int> tavsiye;
    vector<int> tercih;
    vector<int> doktorSure;
    vector<int> doktorBilgilendirme;
};

void makeSurvey(Survey& survey) {

    cout << "-----------Genel Hizmet-----------" << endl;

    cout << "Hastane genel olarak temizdi." << endl;
    cout << "1 - Tamamen Katiliyorum, 2 - Katiliyorum, 3 - Kararsizim, 4 - Katilmiyorum, 5 - Tamamen Katilmiyorum" << endl;
    int cevap;
    cin >> cevap;
    survey.temizlik.push_back(cevap);

    cout << "Hastane personelinin bana karsi davranislari nezaket kurallarina uygundu." << endl;
    cout << "1 - Tamamen Katiliyorum, 2 - Katiliyorum, 3 - Kararsizim, 4 - Katilmiyorum, 5 - Tamamen Katilmiyorum" << endl;
    int cevap2;
    cin >> cevap2;
    survey.personelDavranisi.push_back(cevap2);

    cout << "Kisisel mahremiyetime ozen gosterildi." << endl;
    cout << "1 - Tamamen Katiliyorum, 2 - Katiliyorum, 3 - Kararsizim, 4 - Katilmiyorum, 5 - Tamamen Katilmiyorum" << endl;
    int cevap3;
    cin >> cevap3;
    survey.mahremiyet.push_back(cevap3);

    cout << "Hastanenin sunmus oldugu hizmetler beklentilerimi karsiladi." << endl;
    cout << "1 - Tamamen Katiliyorum, 2 - Katiliyorum, 3 - Kararsizim, 4 - Katilmiyorum, 5 - Tamamen Katilmiyorum" << endl;
    int cevap4;
    cin >> cevap4;
    survey.hizmetler.push_back(cevap4);

    cout << "Bu hastaneyi aileme ve arkadaslarima tavsiye ederim." << endl;
    cout << "1 - Tamamen Katiliyorum, 2 - Katiliyorum, 3 - Kararsizim, 4 - Katilmiyorum, 5 - Tamamen Katilmiyorum" << endl;
    int cevap5;
    cin >> cevap5;
    survey.tavsiye.push_back(cevap5);

    cout << "Bu hastaneyi tekrar tercih ederim." << endl;
    cout << "1 - Tamamen Katiliyorum, 2 - Katiliyorum, 3 - Kararsizim, 4 - Katilmiyorum, 5 - Tamamen Katilmiyorum" << endl;
    int cevap6;
    cin >> cevap6;
    survey.tercih.push_back(cevap6);

    cout << "-----------Doktor Hizmeti-----------" << endl;

    cout << "Doktorumun bana ayirdigi sure yeterliydi." << endl;
    cout << "1 - Tamamen Katiliyorum, 2 - Katiliyorum, 3 - Kararsizim, 4 - Katilmiyorum, 5 - Tamamen Katilmiyorum" << endl;
    int cevap7;
    cin >> cevap7;
    survey.doktorSure.push_back(cevap7);

    cout << "Doktorum tarafindan hastaligim ve tedavim ile ilgili yeterli bilgilendirme yapildi." << endl;
    cout << "1 - Tamamen Katiliyorum, 2 - Katiliyorum, 3 - Kararsizim, 4 - Katilmiyorum, 5 - Tamamen Katilmiyorum" << endl;
    int cevap8;
    cin >> cevap8;
    survey.doktorBilgilendirme.push_back(cevap8);

}

void printSurvey(const Survey& survey) {

    string username;

    ofstream printSurvey("AnketSonucu.txt", ios::trunc);

    printSurvey << "            Genel Hizmet            " << "\n\n";

    printSurvey << "Hastane genel olarak temizdi: ";
    for (int cevap : survey.temizlik) {
        printSurvey << cevap << " ";
    }
    printSurvey << endl;

    printSurvey << "Hastane personelinin bana karsi davranislari nezaket kurallarina uygundu: ";
    for (int cevap2 : survey.personelDavranisi) {
        printSurvey << cevap2 << " ";
    }
    printSurvey << endl;

    printSurvey << "Kisisel mahremiyetime ozen gosterildi: ";
    for (int cevap3 : survey.mahremiyet) {
        printSurvey << cevap3 << " ";
    }
    printSurvey << endl;

    printSurvey << "Hastanenin sunmus oldugu hizmetler beklentilerimi karsiladi: ";
    for (int cevap4 : survey.hizmetler) {
        printSurvey << cevap4 << " ";
    }
    printSurvey << endl;

    printSurvey << "Bu hastaneyi aileme ve arkadaslarima tavsiye ederim: ";
    for (int cevap5 : survey.tavsiye) {
        printSurvey << cevap5 << " ";
    }
    printSurvey << endl;

    printSurvey << "Bu hastaneyi tekrar tercih ederim: ";
    for (int cevap6 : survey.tercih) {
        printSurvey << cevap6 << " ";
    }
    printSurvey << endl;

    dash();

    printSurvey << endl << "            Doktor Hizmeti            " << "\n\n";

    do
    {
        cout << endl << "Hizmet aldiginiz doktorun adini giriniz: "; cin >> username;
        if (username == "emirasili" || username == "burcukosucu" || username == "fatmaakalin") {
            printSurvey << "Doktor Adi: " << username << endl;
            break;
        }
        else
        {
            cout << "Hastanemizde boyle bir doktor bulunmamaktadir. Lutfen doktor adini dogru girdiginizden emin olun";
        }

    } while (username != "emirasili" || username != "burcukosucu" || username != "fatmaakalin");


    printSurvey << "Doktorumun bana ayirdigi sure yeterliydi: ";
    for (int cevap7 : survey.doktorSure) {
        printSurvey << cevap7 << " ";
    }
    printSurvey << endl;

    printSurvey << "Doktorum tarafindan hastaligim ve tedavim ile ilgili yeterli bilgilendirme yapildi: ";
    for (int cevap8 : survey.doktorBilgilendirme) {
        printSurvey << cevap8 << " ";
    }
    printSurvey << endl;

    printSurvey.close();
}


int main() {

    struct node2* doctor1 = new node2();
    struct node2* doctor2 = new node2();                   // Doktor dudumleri olu�turulur
    struct node2* doctor3 = new node2();

    doctor1->Username = "emirasili";
    doctor2->Username = "burcukosucu";                      // Doktorlar�n kullan�c� ad� sisteme tan�mlan�r
    doctor3->Username = "fatmaakalin";

    doctor1->Password = 111;
    doctor2->Password = 222;                                // Doktorlar�n �ifresi sisteme tan�mlan�r
    doctor3->Password = 333;

    doctor1->prev = doctor3;
    doctor1->next = doctor2;
    doctor2->prev = doctor1;
    doctor2->next = doctor3;                                // Doktor bilgileri �ift y�nl� dairesel ba�l� liste yap�s�nda tutulur
    doctor3->prev = doctor2;
    doctor3->next = doctor1;

    node* root = NULL;
    node3* root2 = NULL;

    Survey survey;

    int choice;
    int secim;                                    // Kullan�c�dan al�nacak bilgilerin de�i�kene tan�mlanmas�
    int secim2;

    string username;
    int password;

menu:
    dash();
    cout << endl << "Hastane Otomasyon Uygulamasina Hosgeldiniz!!" << endl;
    cout << "Doktor girisi icin 1'e, Hasta girisi icin 2'ye, Degerlendirme Anketi icin 3'e ve Cikis icin 4'e basiniz" << endl;         // Doktor ve hasta giri�ini kontrol eder ve se�ilen giri�i sa�lar
    dash();
    cin >> choice;

    if (choice == 1)
    {
        cout << endl << "Doktor girisi sayfasina yonlendiriliyorsunuz" << endl;
        cout << "Doktor girisi icin kullanici adi giriniz: "; cin >> username;
        cout << "Doktor girisi icin sifrenizi giriniz: "; cin >> password;                  // Doktor giri�i i�in doktorlar�n kullan�c� ad� ve �ifresini kontrol edip giri� sa�lar

        if (doctorLogin(doctor1, username, password) || doctorLogin(doctor2, username, password) || doctorLogin(doctor3, username, password)) {
            do
            {
                cout << "1- Hasta ekle" << endl;
                cout << "2- ID Bilgisini Kullanarak Hasta Sil" << endl;
                cout << "3- Hasta Detaylarini Getir" << endl;
                cout << "4- Ameliyat Ekle" << endl;
                cout << "5- Ameliyat Sil" << endl;
                cout << "6- Ameliyat Detaylarini Getir" << endl;
                cout << "7- ID'ye Gore Ameliyat Ucretini Hesapla" << endl;
                cout << "8- Ana Menuye Don" << endl;
                cout << "9- Cikis" << endl;

                cout << "Secim Yapiniz: ";
                cin >> secim;

                int ID;
                string info;
                int age;
                int degree;
                string diagnosis;
                string startDate;
                string endDate;
                string insurance;

                switch (secim)
                {
                case 1:
                    cout << "Hasta Numarasi giriniz: "; cin >> ID;
                    cout << "Hasta Ad Soyad giriniz: "; cin >> info;
                    cout << "Hastanin Yasini giriniz: "; cin >> age;
                    cout << "Hastanin Hastalik Derecesini 1 ila 10 arasinda kodlayiniz: "; cin >> degree;
                    cout << "Hastanin Teshisini giriniz: "; cin >> diagnosis;
                    root = addPatient(root, ID, info, age, degree, diagnosis);
                    break;
                case 2:
                    cout << "Silmek Istediginiz Hastanin ID'sini Giriniz: "; cin >> ID;
                    deletePatient(root, ID);
                    break;
                case 3:
                    printPatient(root);
                    break;
                case 4:
                    cout << "Eklemek Istediginiz Ameliyatin ID'sini giriniz: "; cin >> ID;
                    cout << "Ameliyatin Baslangic Zamanini giriniz: "; cin >> startDate;
                    cout << "Ameliyatin Bitis Zamanini giriniz: "; cin >> endDate;
                    root2 = addSurgery(root2, ID, startDate, endDate);
                    cout << "Ameliyat Ekleniyor.. " << endl;
                    break;
                case 5:
                    cout << "Silmek Istediginiz Ameliyatin ID'sini Giriniz: "; cin >> ID;
                    deleteSurgery(root2, ID);
                    break;
                case 6:
                    printSurgery(root2, root);
                    break;
                case 7:
                    cout << "Hesaplamak Istediginiz Hastanin Ameliyat Ucreti Icin ID Giriniz: "; cin >> ID;
                    cout << "Hastaya Ait Sigorta Turunu Giriniz(emekli - ogrenci - calisan): "; cin >> insurance;
                    calculateFee(root2, root, ID, insurance);
                    break;
                case 8:
                    goto menu;
                    break;
                case 9:
                    system("cls");
                    cout << "Cikis yapildi";
                    break;
                default:
                    break;
                }

            } while (secim != 9);

        }
        else {
            cout << "Hatali kullanici adi veya sifre." << endl;
            cout << "Sifremi unuttum? (E/H): ";                         // Doktor giri�inde kullan�c� ad� ve �ifre hatal�ysa �ifremi unuttum k�sm�na atar
            string forgotPassword;
            int verificationCode;
            int code;
            cin >> forgotPassword;

            do
            {
                if (forgotPassword == "e" || forgotPassword == "E")
                {
                    sendVerificationCode();                                 // E�er �ifremi unuttum se�ilirse do�rulama kodu olu�turulur ve kod dosyaya yazd�r�l�r
                    ifstream readFile("DogrulamaKodu.txt", ios::app);
                    string satir;
                    while (getline(readFile, satir)) {
                        size_t found = satir.find("Do�rulama kodu: ");
                        if (found != string::npos) {                              // Dosyaya yazd�r�lan do�rulama kodu dosyadan okunur ve verificationCode de�i�kenine atan�r
                            string kodStr = satir.substr(found + 16);
                            stringstream(kodStr) >> verificationCode;

                            cout << "Dogrulama kodunu giriniz: "; cin >> code;          // Kullan�ca g�nderilen do�rulama kodunu kullan�can girmesi istenir
                            if (code == verificationCode)
                            {
                                cout << "Dogrulama basarili.";
                                for (int i = 0; i < 3; ++i) {
                                    if (doctors[i].Username == username) {              // Kullan�c�n�n girdi�in kod do�rulama koduna e�itse ilgili doktorun �ifresi ekrana yazar
                                        cout << "Sifreniz: " << doctors[i].Password << "'dir" << endl;
                                        goto menu;                                     // Ekrana yazan �ifre ile sisteme tekrar giri� yapmas� i�in doktor giri� k�sm�na g�nderilir                                  
                                    }
                                }
                                return true;
                            }
                            else
                            {
                                cout << "Yanlis Dogrulama Kodu. Lutfen tekrar deneyin.";        // Do�rulama kodu yanl��sa do�rulama kodu yanl�� yazar
                                return false;
                            }

                        }
                    }
                }
                else if (forgotPassword == "h" || forgotPassword == "H")
                {
                    goto menu;
                }
                else
                {
                    cout << "Yanlis secim girdiniz. Lutfen tekrar deneyin" << endl;
                }

            } while (forgotPassword != "e" || forgotPassword != "E" || forgotPassword != "h" || forgotPassword != "H");





        }
    }
    else if (choice == 2)
    {
        cout << "Hasta girisi sayfasina yonlendiriliyorsunuz" << endl;          // Hasta giri�i se�ildiyse buraya y�nlendirilir
        do
        {
            cout << "1- Hastane Doktorlarini Yazdir" << endl;
            cout << "2- Tum Hastalari Yazdir" << endl;
            cout << "3- Ameliyat Hastalarini Yazdir" << endl;
            cout << "4- Tum Hastalarin Oncelik Puanlarini Yazdir" << endl;
            cout << "5- Ana Menuye Don" << endl;
            cout << "6- Cikis" << endl;

            cout << "Secim Yapiniz: ";
            cin >> secim2;

            switch (secim2)
            {
            case 1:
                cout << "Dr. " << doctor1->Username << endl;
                cout << "Doc. Dt. " << doctor2->Username << endl;
                cout << "Prof. Dr." << doctor3->Username << endl;
                break;
            case 2:
                convertToCircular();
                printPatient(root);
                break;
            case 3:
                convertToCircular3();
                printSurgery(root2, root);
                break;
            case 4:
                convertToCircular();
                calculatePriority(root);
                break;
            case 5:
                goto menu;
                break;
            case 6:
                system("cls");
                cout << "Cikis yapildi";
                break;
            default:
                break;
            }

        } while (secim2 != 6);
    }
    else if (choice == 3)
    {
        makeSurvey(survey);

        printSurvey(survey);
        cout << "Degerlendirme anketiniz hastane yonetimine gonderildi. Anketi yaptiginiz icin tesekkurler";
        goto menu;
    }
    else if (choice == 4)
    {
        system("cls");
        cout << "Cikis yapildi";
    }
    else
    {
        cout << "Gecersiz secim. Lutfen tekrar deneyin." << endl;
    }

}




