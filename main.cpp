#include <iostream>
#include <cstring>

using namespace std;

void myStrcpy(char *&dest, const char *source) {
    if (source == nullptr) {
        dest = nullptr;
        return;
    }

    int size = (int) strlen(source);
    dest = new char[size + 1];

    for (int i = 0; i < size; i++) {
        dest[i] = source[i];
    }
    dest[size] = '\0';
}

class Consultatie {

private:
    char *numePacient;
    char *diagnostic;
    int varstaPacient;

public:
    //constructor de initializare
    Consultatie() {
        numePacient = nullptr;
        diagnostic = nullptr;
        varstaPacient = 0;
    }

    //constructor de copiere
    Consultatie(const Consultatie &c) {
        myStrcpy(this->numePacient, c.getNumePacient());
        myStrcpy(this->diagnostic, c.getDiagnostic());
        this->varstaPacient = c.getVarstaPacient();
    }

    //operatorul =
    Consultatie &operator=(const Consultatie &c) {
        if (this != &c) {
            delete[]this->numePacient;
            delete[]this->diagnostic;
            myStrcpy(this->numePacient, c.getNumePacient());
            myStrcpy(this->diagnostic, c.getDiagnostic());
            this->varstaPacient = c.getVarstaPacient();
        }
        return (*this);
    }

    //supraincarcare >>
    friend std::istream &operator>>(std::istream &is, Consultatie &s) {
        char buf[100];
        int nr = 0;

        cout << "Introduceti nume pacient:";
        is >> buf;
        s.setNumePacient(buf);

        cout << "Introduceti diagnostic:";
        is >> buf;
        s.setDiagnostic(buf);

        cout << "Introduceti varsta:";
        is >> nr;
        s.setVarstaPacient(nr);

        cout << '\n';
        return is;
    }

    //supraincarcare <<
    friend std::ostream &operator<<(std::ostream &os, const Consultatie &s) {
        if (!s.numePacient || !s.diagnostic) {
            os << "Nu este initializat\n";
            return os;
        }

        os << "Nume Pacient: " << s.numePacient << '\n' << "Diagnostic: " << s.diagnostic << '\n' << "Varsta: "
           << s.varstaPacient << '\n';

        return os;
    }

    //get si set pentru numele pacientului, diagnosticul si varsta
    [[nodiscard]] char *getNumePacient() const {
        return numePacient;
    }

    void setNumePacient(const char *pNumePacient) {
        delete[] this->numePacient;
        myStrcpy(this->numePacient, pNumePacient);
    }

    [[nodiscard]] char *getDiagnostic() const {
        return diagnostic;
    }

    void setDiagnostic(const char *pDiagnostic) {
        delete[]this->diagnostic;
        myStrcpy(this->diagnostic, pDiagnostic);
    }

    [[nodiscard]] int getVarstaPacient() const {
        return varstaPacient;
    }

    void setVarstaPacient(int pVarstaPacient) {
        varstaPacient = pVarstaPacient;
    }

    //operatorul ==
    bool operator==(const Consultatie &aux) const {
        return strcmp(aux.getNumePacient(), this->numePacient) == 0 &&
               strcmp(aux.getDiagnostic(), this->diagnostic) == 0 &&
               aux.getVarstaPacient() == this->varstaPacient;
    }

    //operatorul !=
    bool operator!=(const Consultatie &aux) const {
        return !this->operator==(aux);
    }

    //destructor
    ~Consultatie() {
        delete[] numePacient;
        delete[] diagnostic;
        varstaPacient = 0;
    }

};

class Medic {

private:
    char *nume;
    char *specialitate;

public:
    //constructor initializare
    Medic() {
        nume = nullptr;
        specialitate = nullptr;
    }

//    Medic(const char *pNume, const char *pSpecialitate) {
//        this->setNume(pNume);
//        this->setSpecialitate(pSpecialitate);
//    }

    //constructor de copiere
    Medic(const Medic &c) {
        this->setNume(c.getNume());
        this->setSpecialitate(c.getSpecialitate());
    }

    //get si set pentru nume si specialitate
    char *getNume() const {
        return nume;
    }

    void setNume(const char *pNume) {
        delete[]this->nume;
        myStrcpy(this->nume, pNume);
    }

    [[nodiscard]] char *getSpecialitate() const {
        return specialitate;
    }

    void setSpecialitate(const char *pSpecialitate) {
        delete[]this->specialitate;
        myStrcpy(this->specialitate, pSpecialitate);
    }

    //operatorul =
    Medic &operator=(const Medic &m) {
        if (this != &m) {
            delete[]this->nume;
            delete[]this->specialitate;
            myStrcpy(this->nume, m.getNume());
            myStrcpy(this->specialitate, m.getSpecialitate());
        }
        return (*this);
    }

    //supraincarcare >>
    friend std::istream &operator>>(std::istream &is, Medic &m) {
        char buf[100];

        cout << "\nIntroduceti nume medic:";
        is >> buf;
        m.setNume(buf);

        cout << "Introduceti specialitatea:";
        is >> buf;
        m.setSpecialitate(buf);

        return is;
    }

    //supraincarcare <<
    friend std::ostream &operator<<(std::ostream &os, const Medic &m) {
        if (!m.nume || !m.specialitate) {
            os << "Nu este initializat\n";
            return os;
        }

        os << "\nNume Medic: " << m.nume << '\n' << "Specialitate: " << m.specialitate << '\n';

        return os;
    }

    //destructor
    ~Medic() {
        delete[] nume;
        delete[] specialitate;
    }
};

void meniuMedic(int &nrMedici, Medic *&vMedic) {
    bool deschis = true;
    int tasta = -1;

    do {
        cout << "3) pentru adaugarea unui medic\n";
        cout << "4) pentru afisarea tuturor medicilor\n";
        cout << "Orice alta tasta pentru oprirea rularii medicilor\n"
                "Tasta:";

        cin >> tasta;
        switch (tasta) {
            case 3: {
                nrMedici++;
                auto *aux = new Medic[nrMedici];
                for (int index = 0; index < nrMedici - 1; index++)
                    aux[index] = vMedic[index];
                cin >> aux[nrMedici - 1];
                delete[] vMedic;
                vMedic = aux;
                cout << "Am adaugat medicul!\n";
            }
                break;

            case 4: {
                for (int index = 0; index < nrMedici; index++) {
                    cout << vMedic[index] << '\n';
                }
            }
                break;

            default:
                cout << "Se inchide meniul!\n";
                deschis = false;
                break;
        }
    } while (deschis);
}

void meniuConsultatie(int &nrPacienti, Consultatie *&vConsultatie) {

    bool deschis = true;
    int tasta = -1;

    do {
        cout << "3) pentru adaugarea unei consultatii\n";
        cout << "4) pentru eliminarea unei consultatii\n";
        cout << "5) pentru afisarea tuturor consultatiilor\n";
        cout << "6) pentru modificarea diagnosticului dintr-o consultatie\n";
        cout << "Orice alta tasta pentru oprirea rularii consultatiilor\n"
                "Tasta:";

        cin >> tasta;
        switch (tasta) {
            case 3: {
                nrPacienti++;
                auto *aux = new Consultatie[nrPacienti];
                for (int index = 0; index < nrPacienti - 1; index++)
                    aux[index] = vConsultatie[index];
                cin >> aux[nrPacienti - 1];
                delete[] vConsultatie;
                vConsultatie = aux;
                cout << "Am adaugat pacientul!\n";
            }
                break;

            case 4: {
                char numePacient[30];
                bool ok = false;
                cout << "Numele pacientului eliminat: ";
                cin.get();
                cin.getline(numePacient, 30);

                for (int index = 0; index < nrPacienti; index++)
                    if (strcmp(vConsultatie[index].getNumePacient(), numePacient) == 0)
                        ok = true;

                if (!ok) {
                    cout << "Nu exista pacient cu acest nume\n";
                    break;
                }

                auto *aux = new Consultatie[nrPacienti - 1];
                int k = 0;
                for (int index = 0; index < nrPacienti; index++)
                    if (strcmp(vConsultatie[index].getNumePacient(), numePacient) != 0) {
                        aux[k++] = vConsultatie[index];
                    }
                delete[] vConsultatie;
                vConsultatie = aux;
                nrPacienti--;
                cout << "Pacientul cu numele " << numePacient << " a fost eliminat\n";
            }
                break;

            case 5: {
                for (int index = 0; index < nrPacienti; index++) {
                    cout << vConsultatie[index] << '\n';
                }
            }
                break;

            case 6: {
                bool ok = false;
                char nume2Pacient[30];
                cout << "Numele pacientului:";
                cin.get();
                cin.getline(nume2Pacient, 30);

                for (int index = 0; index < nrPacienti; index++)
                    if (strcmp(vConsultatie[index].getNumePacient(), nume2Pacient) == 0)
                        ok = true;

                if (!ok) {
                    cout << "Nu exista niciun pacient cu acest nume" << endl;
                    break;
                }

                for (int index = 0; index < nrPacienti; index++)
                    if (strcmp(vConsultatie[index].getNumePacient(), nume2Pacient) == 0) {
                        char diagnostic_nou[40];
                        cout << "Noul diagnostic:";
                        cin.getline(diagnostic_nou, 40);
                        vConsultatie[index].setDiagnostic(diagnostic_nou);
                        cout << "Diagnostic modificat!\n";
                    }
            }
                break;
            default:
                cout << "Se inchide meniul!\n";
                deschis = false;
                break;
        }

    } while (deschis);
}

void meniuAfisare() {
    cout << "\n"
            "Proiect realizat de Manolache Diana-Elena\n"
            "Grupa 133\n\n"
            "MENIU\n";

    int nrPacienti = 0, nrMedici = 0;

    Consultatie *vConsultatie = nullptr;
    Medic *vMedic = nullptr;

    int tasta = -1;
    do {

        cout << "1) Apasati 1 pentru consultatii\n"
                "2) Apasati 2 pentru medici\n"
                "Apasati orice alta tasta pentru a termina meniul\n"
                "Tasta:";

        cin >> tasta;
        switch (tasta) {
            case 1:
                meniuConsultatie(nrPacienti, vConsultatie);
                break;
            case 2:
                meniuMedic(nrMedici, vMedic);
                break;
            default:
                cout << "Tasta gresita!\n";
        }
    } while (1 <= tasta && tasta <= 2);

}

int main() {
    meniuAfisare();
    return 0;
}