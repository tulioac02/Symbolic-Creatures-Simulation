//Codigo para testes
#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <list>

using namespace std;

// Cores para representar os elementos
#define RESET "\033[0m"     // Resetar para a cor padrão
#define CYAN "\033[36m"     // Ciano -> Arvores
#define YELLOW "\033[33m"   // Amarelo -> Macacos
#define BLUE "\033[34m"     // Azul -> Aguia
#define MAGENTA "\033[35m"  // Magenta -> Tigre
#define GREEN "\033[32m"    // Verde -> Cobra
#define RED "\033[31m"      // Vermelho -> Morte

//Declaração antecipada de nvironment
class Environment;

// Classe abstrata Animal
class Animal {
public:
    tuple<int, int> position; // Tupla de inteiros para a posição
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

    void perception(Environment environment[10][10]) {
        // Implemente o código da percepção do Monkey
        cout << "Position of monkey is " << get<0>(this->position) << ',' << get<1>(this->position) << ".\n"; 
        for(int i = get<0>(this->position); i< get<0>(this->position)+3; i++){
            for(int j = get<1>(this->position); j < get<1>(this->position)+3; j++){
                cout << "Perception of position " << i << ',' << j << endl;
            }
        }
    }

    void randomWalk() override {
        // Implemente o código da caminhada aleatória do Monkey
        cout << "Monkey " << name << " is walking randomly." << endl;
    }
};

// Classe Predator (herda de Animal)
class Predator : public Animal {
public:
    enum predatorType {
        TI, // Tiger
        EA, // Eagle
        SN  // Snake
    };

    int strength; // Força do Predator]
    predatorType type;

    // Construtor

    Predator(predatorType t) {
        this->type = t;
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

    void perception(Environment environment[10][10]){
        // Implemente o código da percepção do Predator
        cout << "Predator with strength " << strength << " perceives its surroundings." << endl;
    }

    void randomWalk() override {
        // Implemente o código da caminhada aleatória do Predator
        cout << "Predator with strength " << strength << " is walking randomly." << endl;
    }
};

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
    list<Monkey> monkeyList;
    list<Predator> predatorList;

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
                    if(!environment[i][j].monkeyList.empty()){
                        cout << YELLOW << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                        << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
                    else if(environment[i][j].predatorList.front().type == Predator::SN){
                        cout << GREEN << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                        << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
                    else if(environment[i][j].predatorList.front().type == Predator::TI){
                        cout << MAGENTA << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                        << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
                    else if(environment[i][j].predatorList.front().type == Predator::EA){
                        cout << BLUE << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                        << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
                    else{
                        cout << RESET << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                        << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
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

    // Função para adicionar macacos no ambiente
    static void addMonkey(Environment environment[10][10], int l, int c, Monkey m) {
        srand(time(nullptr)); // Configuração da semente do gerador de números aleatórios
        int it = 1;
        while(it != 0){
            int i = rand() % l, j = rand() % c;
            if(environment[i][j].type == GR && environment[i][j].monkeyList.empty()){
                environment[i][j].monkeyList.push_back(m);
                m.position = environment[i][j].position;
                cout << "Monkey added in position " << get<0>(m.position) << ',' << get<1>(m.position) << ".\n";
                it--;
            }
        }
    }

    static void addPredator(Environment environment[10][10], int l, int c, Predator p) {
        srand(time(nullptr)); // Configuração da semente do gerador de números aleatórios
        int it = 1;
        while(it != 0){
            int i = rand() % l, j = rand() % c;
            if(environment[i][j].type == GR && environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty()){
                environment[i][j].predatorList.push_back(p);
                p.position = environment[i][j].position;
                if(p.type == Predator::EA){
                    cout << "Eagle added in position " << get<0>(p.position) << ',' << get<1>(p.position) << ".\n";
                }
                else if(p.type == Predator::TI){
                    cout << "Tiger added in position " << get<0>(p.position) << ',' << get<1>(p.position) << ".\n";
                }
                else if(p.type == Predator::SN){
                    cout << "Snake added in position " << get<0>(p.position) << ',' << get<1>(p.position) << ".\n";
                }
                it--;
            }
        }
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

    //Adicionando macacos
    Monkey monkey01, monkey02, monkey03, monkey04; // Alocação estatica do objeto Monkey
    Environment::addMonkey(environment, l, c, monkey01);
    Environment::addMonkey(environment, l, c, monkey02);
    Environment::addMonkey(environment, l, c, monkey03);
    Environment::addMonkey(environment, l, c, monkey04);

    //Adicionando predadores
    Predator snake(Predator::SN), eagle(Predator::EA), tiger(Predator::TI);
    Environment::addPredator(environment, l, c, snake);
    Environment::addPredator(environment, l, c, eagle);
    Environment::addPredator(environment, l, c, tiger);
    cout << endl;
    
    // Imprimindo os tipos dos elementos da matriz
    Environment::printEnvironment(environment, l, c);
    cout << endl;

    monkey01.perception(environment);
    return 0;
}