#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <list>
#include <string>

using namespace std;

// Cores para representar os elementos
#define RESET "\033[37m"   // Resetar para a cor padrão
#define CYAN "\033[36m"    // Ciano -> Arvores
#define YELLOW "\033[33m"  // Amarelo -> Macacos
#define BLUE "\033[34m"    // Azul -> Aguia
#define MAGENTA "\033[35m" // Magenta -> Tigre
#define GREEN "\033[32m"   // Verde -> Cobra
#define RED "\033[31m"     // Vermelho -> Morte

// Variáveis globais
int const linhaMatriz = 10;
int const colunaMatriz = 10;
int const numMonkeys = 4;

class Animal
{
private:
    string name;
    tuple<int, int> position;
public:
    // Construtor padrão
    Animal()
    {
    }

    // Construtor com parâmetros
    Animal(std::string n) : name(n)
    {
    }

    //Getter e Setter para Position
    string getName()
    {
        return name;
    }

    void setName(string n)
    {
        name = n;
    }

    //Getter e Setter para Position
    tuple<int, int> getPosition()
    {
        return position;
    }

    void setPosition(const tuple<int, int> &pos)
    {
        position = pos;
    }
};

// Classe Monkey (herda de Animal)
class Monkey : public Animal
{
    public:
    // Construtor padrão de Monkey
    Monkey()
    {
    }

    // Construtor com parâmetros específicos de Monkey
    Monkey(string n) : Animal(n)
    {
    }
};

// Classe Predator (herda de Animal)
class Predator : public Animal
{
private:

public:
    enum PredatorType
    {
        TI, // Tiger
        EA, // Eagle
        SN  // Snake
    };

    // Tipo do Predador
    PredatorType type;

    // Construtor padrão de Predator
    Predator()
    {
    }

    // Construtor com parâmetros específicos de Predator
    Predator(const string& n, PredatorType t) : Animal(n), type(t)
    {
    }

    static vector<Predator::PredatorType> getPredatorTypes()
    {
        return {Predator::PredatorType::TI, Predator::PredatorType::EA, Predator::PredatorType::SN};
    }

    static string predatorTypeToString(PredatorType type)
    {
        switch (type)
        {
        case SN:
            return "Snake";
        case TI:
            return "Tiger";
        case EA:
            return "Eagle";
        default:
            return "Valor inválido";
        }
    }
};

// Classe do Ambiente
class Environment
{
public:
    // Enumerador para os tipos de ambiente
    enum EnvironmentType
    {
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
    Environment()
    {
        this->type = GR;
    }

    // Função para Adicionar coordenadas
    static void addPos(Environment environment[linhaMatriz][colunaMatriz])
    {
        for (int i = 0; i < linhaMatriz; i++)
        {
            for (int j = 0; j < colunaMatriz; j++)
            {
                tuple<int, int> aux(i, j);
                environment[i][j].position = aux;
            }
        }
    }

    // Função para adicionar árvores ao ambiente
    static void addTree(Environment environment[linhaMatriz][colunaMatriz], EnvironmentType type, int num)
    {
        srand(time(nullptr)); // Configuração da semente do gerador de números aleatórios
        int it = num;
        while (it != 0)
        {
            int i = rand() % linhaMatriz, j = rand() % colunaMatriz;
            if (environment[i][j].type == GR)
            {
                environment[i][j].type = type;
                it--;
            }
        }
    }

    // Função para converter enum para string
    static string environmentTypeToString(EnvironmentType type)
    {
        switch (type)
        {
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

    // Função para imprimir o ambiente
static void printEnvironment(Environment environment[linhaMatriz][colunaMatriz])
{
    for (int i = 0; i < linhaMatriz; i++)
    {
        for (int j = 0; j < colunaMatriz; j++)
        {
            if (!environment[i][j].monkeyList.empty())
            {
                cout << YELLOW;
            }
            else if (!environment[i][j].predatorList.empty())
            {
                if (environment[i][j].predatorList.front().type == Predator::SN)
                {
                    cout << GREEN;
                }
                else if (environment[i][j].predatorList.front().type == Predator::TI)
                {
                    cout << MAGENTA;
                }
                else if (environment[i][j].predatorList.front().type == Predator::EA)
                {
                    cout << BLUE;
                }
            }
            else if (!environment[i][j].monkeyList.empty() && !environment[i][j].predatorList.empty())
            {
                cout << RED;
            }
            else
            {
                cout << RESET;
            }

            cout << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
        }
        cout << endl;
    }
    cout << endl;
}

    // Função para adicionar macacos no ambiente
    static void addMonkey(Environment environment[linhaMatriz][colunaMatriz], Monkey &monk)
    {
        srand(time(nullptr)); // Configuração da semente do gerador de números aleatórios
        int it = 1;
        while (it != 0)
        {
            int i = rand() % linhaMatriz, j = rand() % colunaMatriz;
            if (environment[i][j].type == GR && environment[i][j].monkeyList.empty())
            {
                environment[i][j].monkeyList.push_back(monk);
                monk.setPosition(environment[i][j].position);
                cout << monk.getName() << " added in position " << get<0>(monk.getPosition()) << ',' << get<1>(monk.getPosition()) << ".\n";
                it--;
            }
        }
    }

    static void addPredator(Environment environment[linhaMatriz][colunaMatriz], Predator &pred)
    {
        srand(time(nullptr)); // Configuração da semente do gerador de números aleatórios
        int it = 1;
        while (it != 0)
        {
            int i = rand() % linhaMatriz, j = rand() % colunaMatriz;
            if (environment[i][j].type == GR && environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty())
            {
                environment[i][j].predatorList.push_back(pred);
                pred.setPosition(environment[i][j].position);
                if (pred.type == Predator::EA)
                {
                    cout << "Eagle added in position " << get<0>(pred.getPosition()) << ',' << get<1>(pred.getPosition()) << ".\n";
                }
                else if (pred.type == Predator::TI)
                {
                    cout << "Tiger added in position " << get<0>(pred.getPosition()) << ',' << get<1>(pred.getPosition()) << ".\n";
                }
                else if (pred.type == Predator::SN)
                {
                    cout << "Snake added in position " << get<0>(pred.getPosition()) << ',' << get<1>(pred.getPosition()) << ".\n";
                }
                it--;
            }
        }
    }
};

// Classe das interações dos objetos
class Sobreviver
{
private:
    Environment environment[linhaMatriz][colunaMatriz];

public:
    Sobreviver(const Environment (&env)[linhaMatriz][colunaMatriz])
    {
        // Copiar os elementos do ambiente fornecido para o ambiente da classe Sobreviver
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                environment[i][j] = env[i][j];
            }
        }
    }

    Environment (*getEnvironment())[colunaMatriz]
    {
        return environment;
    }

    void setEnvironment(const Environment (&env)[linhaMatriz][colunaMatriz])
    {
        // Copiar os elementos do ambiente fornecido para o ambiente da classe Sobreviver
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                environment[i][j] = env[i][j];
            }
        }
    }

    //Função de percepção do Macaco (Incompleto)
    void perception(Monkey &monk)
    {
        int raio = 1;
        int lmin = get<0>(monk.getPosition()) - raio;
        int lmax = get<0>(monk.getPosition()) + raio;
        int cmin = get<1>(monk.getPosition()) - raio;
        int cmax = get<1>(monk.getPosition()) + raio;

        list<Environment*> securityOptions; // Lista de opções seguras (arvores)
        list<Environment*> neutralOptions; // Lista de oções neutras (sem predador e sem arvores)
        list<Environment*> noSecurityOptions; // Lista de opções com predadores

        cout << "Perception of " << monk.getName() << " in the position (" << get<0>(monk.getPosition()) << ","
        << get<1>(monk.getPosition()) << ") is: " << endl;

        for (int i = lmin; i <= lmax; i++)
        {
            for (int j = cmin; j <= cmax; j++)
            {
                if (i >= 0 && i < 10 && j >= 0 && j < 10 && monk.getPosition() != environment[i][j].position)
                {
                    if(environment[i][j].type != Environment::GR){
                        securityOptions.push_back(&environment[i][j]);
                        cout << "Security position (" << i << "," << j << ") add in security list." << endl; 
                    }
                    if(environment[i][j].predatorList.empty()){
                        neutralOptions.push_back(&environment[i][j]);
                        cout << "Neutral position (" << i << "," << j << ") add in neutral list." << endl; 
                    }
                    else{
                        noSecurityOptions.push_back(&environment[i][j]);
                        cout << "No security position (" << i << "," << j << ") add in no security list." << endl;
                    }
                }
            }
        }

        if(noSecurityOptions.empty()){
            randomWalk(monk);
        }
        else{
            monkeyStrategyWalk(securityOptions);
        }
    }


    //Função de percepção do Predador (Incompleto)
    void perception(Predator &pred)
    {
        int raio = 1;
        int lmin = get<0>(pred.getPosition()) - raio;
        int lmax = get<0>(pred.getPosition()) + raio;
        int cmin = get<1>(pred.getPosition()) - raio;
        int cmax = get<1>(pred.getPosition()) + raio;

        list<Environment*> neutralOptions; // Lista de oções neutras (sem macacos)
        list<Environment*> targetOptions; // Lista de oções alvo (com macacos)

        cout << "Perception of " << pred.getName() << " in the position (" << get<0>(pred.getPosition()) << ","
        << get<1>(pred.getPosition()) << ") is: " << endl;

        for (int i = lmin; i <= lmax; i++)
        {
            for (int j = cmin; j <= cmax; j++)
            {
                if (i >= 0 && i < 10 && j >= 0 && j < 10 && pred.getPosition() != environment[i][j].position)
                {
                    if (environment[i][j].monkeyList.empty())
                    {
                        neutralOptions.push_back(&environment[i][j]);
                        cout << "Neutral position (" << i << "," << j << ") add in neutral list." << endl; 
                    }
                    else if(!environment[i][j].monkeyList.empty()){
                        targetOptions.push_back(&environment[i][j]);
                        cout << "Target position (" << i << "," << j << ") add in target list." << endl; 
                    }
                }
            }
        }

        if(targetOptions.empty()){
            randomWalk(pred);
        }
        else{
            predatorStrategyWalk(targetOptions);
        }
    }

    //Função de andar aleatória para macaco
    void randomWalk(Monkey &monk)
    {
        // Implemente o código da caminhada aleatória do Monkey
        int raio = 1;
        tuple<int, int> posM = monk.getPosition();

        for (int i = get<0>(posM) - raio; i <= get<0>(posM) + raio; i++)
        {
            for (int j = get<1>(posM) - raio; j <= get<1>(posM) + raio; j++)
            {
                if (i >= 0 && j >= 0 && i < 10 && j < 10 && i != j)
                {
                    if (environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty())
                    {
                        cout << "Position of " << monk.getName() << " before walk is " << get<0>(monk.getPosition()) << ',' << get<1>(monk.getPosition()) << ".\n";

                        environment[get<0>(posM)][get<1>(posM)].monkeyList.pop_front();
                        monk.setPosition(environment[i][j].position);
                        environment[i][j].monkeyList.push_front(monk);

                        cout << "Position of " << monk.getName() << " after walk is " << get<0>(monk.getPosition()) << ',' << get<1>(monk.getPosition()) << ".\n\n";
                        Environment::printEnvironment(environment);
                        return;
                    }
                }
            }
        }

        return;
    }

    //Função de andar aleatória para predador
    void randomWalk(Predator &pred)
    {
        // Implemente o código da caminhada aleatória do Monkey
        int raio = 1;
        tuple<int, int> posM = pred.getPosition();

        for (int i = get<0>(posM) - raio; i <= get<0>(posM) + raio; i++)
        {
            for (int j = get<1>(posM) - raio; j <= get<1>(posM) + raio; j++)
            {
                if (i >= 0 && j >= 0 && i < 10 && j < 10 && i != j)
                {
                    if (environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty())
                    {
                        cout << "Position of " << pred.getName() << " before walk is " << get<0>(pred.getPosition()) << ',' << get<1>(pred.getPosition()) << ".\n";

                        environment[get<0>(posM)][get<1>(posM)].predatorList.pop_front();
                        pred.setPosition(environment[i][j].position);
                        environment[i][j].predatorList.push_front(pred);

                        cout << "Position of " << pred.getName() << " after walk is " << get<0>(pred.getPosition()) << ',' << get<1>(pred.getPosition()) << ".\n\n";
                        Environment::printEnvironment(environment);
                        return;
                    }
                }
            }
        }

        return;
    }

    //Função de andar não aleatória do macaco (incompleta)
    /*Está função vai receber a lista de caminhos não seguros, dessa forma, vai se mover para a direção oposta
    de um pretador identificado ou para uma árvore que o proteja*/
    void monkeyStrategyWalk(list<Environment*> options){
        cout << "Action to implement.\n\n";
    }

    //Função de andar não aleatória do predador (incompleta)
    /*Está função vai receber a lista de alvos. Será escolhido um alvo aleatório e se mover para a lista
    de predadores da mesma função do seu alvo*/
    void predatorStrategyWalk(list<Environment*> options){
        cout << "Action to implement.\n\n";
    }
};

int main()
{
    // Declarando uma matriz 10x10 de objetos Environment
    Environment environment[linhaMatriz][colunaMatriz];

    // Adicionando coordenadas
    Environment::addPos(environment);

    // Adicionando árvores
    Environment::addTree(environment, Environment::HT, 4);
    Environment::addTree(environment, Environment::MT, 4);
    Environment::addTree(environment, Environment::LT, 4);

    // Adicionando macacos
    list<Monkey> monkeysList;
    for (int i = 0; i < numMonkeys; i++)
    {
        Monkey monkey("Monkey" + to_string(i+1));
        Environment::addMonkey(environment, monkey);
        monkeysList.push_back(monkey);
    }

    // Adicionando predadores
    list<Predator> predatorsList;
    vector<Predator::PredatorType> predatorTypes = Predator::getPredatorTypes();
    for (const auto& type : predatorTypes)
    {
        Predator predador(Predator::predatorTypeToString(type), type);
        Environment::addPredator(environment, predador);
        predatorsList.push_back(predador);
    }
    cout << endl;

    Sobreviver sobreviver = Sobreviver(environment);
    Environment::printEnvironment(sobreviver.getEnvironment());     // Imprimindo os tipos dos elementos da matriz


    for (auto &monkey : monkeysList)
    {
        //sobreviver.randomWalk(monkey);
        sobreviver.perception(monkey);
    }

    for (auto &predator : predatorsList)
    {
        //sobreviver.randomWalk(predator);
        sobreviver.perception(predator);
    }

    return 0;
}
