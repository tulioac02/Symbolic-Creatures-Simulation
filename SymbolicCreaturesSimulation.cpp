#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>

using namespace std;

// Cores para representar os elementos
#define RESET "\033[0m"     // Resetar para a cor padrão
#define RED "\033[31m"      // Vermelho
#define GREEN "\033[32m"    // Verde
#define YELLOW "\033[33m"   // Amarelo
#define BLUE "\033[34m"     // Azul
#define MAGENTA "\033[35m"  // Magenta
#define CYAN "\033[36m"     // Ciano

// Classe do Ambiente
class Environment {
public:
    // Enumerador para os tipos de ambiente
    enum EnvironmentType {
        GR, // Grass
        HT, // High Tree
        MT, // Medium Tree
        LT  // Low Tree
    };
    
    // Atributos do ambiente
    EnvironmentType type;
    tuple<int, int> position;
    //Monkey* monkey = new Monkey();
    //Predator predator;


    // Construtor da classe Environment
    Environment(){
        this->type = GR;
    }


    // Função para Adicionar coordenadas
    static void addPos(Environment environment[10][10], int l, int c){
        for(int i=0; i<l; i++){
            for(int j=0; j<c; j++){
                tuple<int, int> aux(i, j);
                environment[i][j].position = aux;
            }
        } 
    }

    // Função para adicionar árvores ao ambiente
    static void addTree(Environment environment[10][10], int l, int c, EnvironmentType type, int num){
        srand(time(nullptr)); // Configuração da semente do gerador de números aleatórios
        int it = num;
        while(it != 0){
            int i = rand() % l, j = rand() % c;
            if(environment[i][j].type == GR){
                environment[i][j].type = type;
                it--;
            }
        }
    }

    //Função para converter enum para string
    static string environmentTypeToString(EnvironmentType type) {
        switch (type) {
            case GR:
                return "GR";
            case HT:
                return "HT";
            case MT:
                return "MT";
            case LT:
                return "ST";
            default:
                return "Valor inválido";
        }
    }

    //Função para imprimir o ambiente
    static void printEnvironment(Environment environment[10][10], int l, int c){
        for(int i=0; i<l; i++){
            for(int j=0; j<c; j++){
                if(environment[i][j].type == GR){
                    cout << GREEN << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                    << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                }
                else if(environment[i][j].type == HT ){
                    cout << CYAN << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                    << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                }
                else if(environment[i][j].type == MT){
                    cout << CYAN << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                    << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                }
                else if(environment[i][j].type == LT){
                    cout << CYAN << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                    << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                }
            }
            cout << endl;
        } 
    }

    /*static void processMonkey(Monkey* monkey) {
        // Processar o objeto Monkey
        // ...
    }*/
};

// Classe abstrata Animal
class Animal {
public:
    tuple<int, int> position; // Tupla de inteiros para a posição

    virtual void perception() = 0; // Função abstrata para percepção
    virtual void randomWalk() = 0; // Função abstrata para caminhada aleatória

    virtual ~Animal() {}  // Destrutor virtual
};

// Classe Monkey (herda de Animal)
class Monkey : public Animal {
private:
    string name; // Nome do Monkey

public:
    // Construtor
    Monkey() {
        
    }

    // Destrutor
    ~Monkey() override {}

    // Getter para o nome
    string getName() const {
        return name;
    }

    // Setter para o nome
    void setName(const string& n) {
        name = n;
    }

    void perception() override {
        // Implemente o código da percepção do Monkey
        cout << "Monkey " << name << " perceives its surroundings." << endl;
    }

    void randomWalk() override {
        // Implemente o código da caminhada aleatória do Monkey
        cout << "Monkey " << name << " is walking randomly." << endl;
    }
};

// Classe Predator (herda de Animal)
class Predator : public Animal {
private:
    int strength; // Força do Predator

public:
    // Construtor
    Predator() {
        
    }

    // Destrutor
    ~Predator() override {}

    // Getter para a força
    int getStrength() const {
        return strength;
    }

    // Setter para a força
    void setStrength(int s) {
        strength = s;
    }

    void perception() override {
        // Implemente o código da percepção do Predator
        cout << "Predator with strength " << strength << " perceives its surroundings." << endl;
    }

    void randomWalk() override {
        // Implemente o código da caminhada aleatória do Predator
        cout << "Predator with strength " << strength << " is walking randomly." << endl;
    }
};

int main() {
    // Declarando uma matriz 10x10 de objetos Environment
    const int l = 10, c = 10;
    Environment environment[l][c];

    //Adicionando coordenadas
    Environment::addPos(environment, l, c);

    //Adicionando arvores
    Environment::addTree(environment, l, c, Environment::HT, 4);
    Environment::addTree(environment, l, c, Environment::MT, 4);
    Environment::addTree(environment, l, c, Environment::LT, 4);

    // Imprimindo os tipos dos elementos da matriz
    Environment::printEnvironment(environment, l, c);
    
    Monkey* monkey = new Monkey(); // Alocação dinâmica do objeto Monkey
    //Environment::processMonkey(monkey); // Chamada da função estática passando o ponteiro do objeto
    delete monkey; // Liberar memória alocada para o objeto Monkey

    /*Predator* predator = new Predator();

    monkey->perception();
    monkey->randomWalk();
    cout << "Monkey name: " << monkey->getName() << endl;

    predator->perception();
    predator->randomWalk();
    cout << "Predator strength: " << predator->getStrength() << endl;
   
    delete[] predator;*/
    //delete[] monkey;

    return 0;
}
