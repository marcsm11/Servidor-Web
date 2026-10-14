#include <iostream>
#include <string>

using namespace std; // Evita haver d'escriure std:: a tot arreu

class SessioUsuari {
private:
    // ATRIBUTS PRIVATS (Només utilitzables des de dins de la classe)
    string nomUsuari;
    unsigned int tempsLlimitSegons; // Tipus sense signe (sempre >= 0)
    bool activa;

    // MÈTODE PRIVAT D'AJUDA
    // Com que és privat, només el pot cridar la pròpia classe (p. ex. el destructor)
    void tancarSessio() {
        activa = false;
    }

public:
    // ============================================================
    // CONSTRUCTORS
    // ============================================================

    // 1. Constructor per defecte
    // Es crida quan fem: SessioUsuari s1;
    SessioUsuari()
        : nomUsuari("convidat"), tempsLlimitSegons(300), activa(true) {
    }

    // 2. Constructor de 1 paràmetre
    // 'explicit' evita conversions implícites (p. ex. que un text es converteixi en sessió automàticament)
    // Es crida quan fem: SessioUsuari s2("Marc");
    explicit SessioUsuari(const string& nom)
        : nomUsuari(nom), tempsLlimitSegons(600), activa(true) {
    }

    // 3. Constructor complet amb validació d'invariant
    // Valida que el temps sigui > 0. Si és <= 0, assigna 60 segons per seguretat
    // Es crida quan fem: SessioUsuari s3("Anna", 1200);
    SessioUsuari(const string& nom, int temps)
        : nomUsuari(nom), tempsLlimitSegons(temps > 0 ? temps : 60), activa(true) {
    }

    // ============================================================
    // DESTRUCTOR (Símbol ~)
    // ============================================================
    // S'executa AUTOMÀTICAMENT quan l'objecte mor (en arribar a la clau '}')
    ~SessioUsuari() {
        if (activa) {
            tancarSessio(); // Cridem el mètode privat d'ajuda
            cout << "[AUDITORIA] La sessió de '" << nomUsuari
                << "' s'ha tancat automàticament en sortir d'àmbit.\n";
        }
    }

    // ============================================================
    // MÈTODES D'ENCAPSULACIÓ I NEGOCI
    // ============================================================

    // Retorna el nom de l'usuari. Marcat com a 'const' perquè NO modifica l'objecte
    string getNomUsuari() const {
        return nomUsuari;
    }

    // Retorna si la sessió està activa. Marcat com a 'const'
    bool isActiva() const {
        return activa;
    }

    // Amplia el temps de la sessió només si els segons són strictly positius (> 0)
    void ampliarTemps(int segons) {
        if (segons > 0) {
            tempsLlimitSegons += segons;
        }
    }
};

// ============================================================
// PROGRAMA PRINCIPAL DE PROVA
// ============================================================
int main() {
    cout << "--- Inici del programa ---\n\n";

    {
        // Obrim un bloc de codi intern (àmbit)
        cout << "Creant objectes dins del bloc...\n";

        SessioUsuari s1;                      // Usuari convidat, 300s
        SessioUsuari s2("Marc");              // Usuari Marc, 600s
        SessioUsuari s3("Anna", -50);        // Temps <= 0 -> s'assignen 60s

        s2.ampliarTemps(100);                 // Ara té 700s

        cout << "L'usuari s2 és: " << s2.getNomUsuari() << "\n";
        cout << "Sortint del bloc de codi...\n";
    }
    // <--- EN ARRIBAR A AQUESTA CLAU DE TANCAMENT,
    // s1, s2 i s3 surten d'àmbit i C++ executa AUTOMÀTICAMENT els seus destructors ~SessioUsuari()!

    cout << "\n--- Fi del programa ---\n";
    return 0;
}