#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <list>

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
public:
    Animal() {}
};


// Classe Monkey (herda de Animal)
class Monkey : public Animal
{
private:
    tuple<int, int> position; // Nome do Monkey

public:
    // Construtor
    Monkey()
    {
    }

    tuple<int, int> getPosition() const
    {
        return position;
    }

    void setPosition(const tuple<int, int> &pos)
    {
        position = pos;
    }
};

// Classe Predator (herda de Animal)
class Predator : Animal
{
public:
    enum predatorType
    {
        TI, // Tiger
        EA, // Eagle
        SN  // Snake
    };

    int strength; // Força do Predator]
    predatorType type;
    tuple<int, int> position;

    // Construtor

    Predator(predatorType t)
    {
        this->type = t;
    }

    static std::vector<Predator::predatorType> getPredatorTypes()
    {
        return {Predator::predatorType::TI, Predator::predatorType::EA, Predator::predatorType::SN};
    }

    // Getter para a força
    int getStrength() const
    {
        return strength;
    }

    // Setter para a força
    void setStrength(int s)
    {
        strength = s;
    }

    // Getter para a posição
    tuple<int, int> getPosition() const
    {
        return position;
    }

    // Setter para a posição
    void setPosition(const tuple<int, int> &pos)
    {
        position = pos;
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
                if (environment[i][j].type == GR)
                {
                    if (!environment[i][j].monkeyList.empty())
                    {
                        cout << YELLOW << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                             << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
                    else if (environment[i][j].predatorList.front().type == Predator::SN)
                    {
                        cout << GREEN << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                             << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
                    else if (environment[i][j].predatorList.front().type == Predator::TI)
                    {
                        cout << MAGENTA << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                             << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
                    else if (environment[i][j].predatorList.front().type == Predator::EA)
                    {
                        cout << BLUE << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                             << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
                    else
                    {
                        cout << RESET << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                             << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                    }
                }
                else if (environment[i][j].type == HT)
                {
                    cout << CYAN << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                         << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                }
                else if (environment[i][j].type == MT)
                {
                    cout << CYAN << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                         << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                }
                else if (environment[i][j].type == LT)
                {
                    cout << CYAN << "|" << Environment::environmentTypeToString(environment[i][j].type) << " ("
                         << get<0>(environment[i][j].position) << "," << get<1>(environment[i][j].position) << ")| " << RESET;
                }
            }
            cout << endl;
        }
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
                cout << "Monkey added in position " << get<0>(monk.getPosition()) << ',' << get<1>(monk.getPosition()) << ".\n";
                it--;
            }
        }
    }

    static void addPredator(Environment environment[linhaMatriz][colunaMatriz], Predator &p)
    {
        srand(time(nullptr)); // Configuração da semente do gerador de números aleatórios
        int it = 1;
        while (it != 0)
        {
            int i = rand() % linhaMatriz, j = rand() % colunaMatriz;
            if (environment[i][j].type == GR && environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty())
            {
                environment[i][j].predatorList.push_back(p);
                p.position = environment[i][j].position;
                if (p.type == Predator::EA)
                {
                    cout << "Eagle added in position " << get<0>(p.position) << ',' << get<1>(p.position) << ".\n";
                }
                else if (p.type == Predator::TI)
                {
                    cout << "Tiger added in position " << get<0>(p.position) << ',' << get<1>(p.position) << ".\n";
                }
                else if (p.type == Predator::SN)
                {
                    cout << "Snake added in position " << get<0>(p.position) << ',' << get<1>(p.position) << ".\n";
                }
                it--;
            }
        }
    }
};

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

    void perception(Monkey &monk)
    {
        // Implemente o código da percepção do Monkey
        int raio = 3;
        tuple<int, int> posM = monk.getPosition();

        int lmin = get<0>(posM) - raio;
        int lmax = get<0>(posM) + raio;
        int cmin = get<1>(posM) - raio;
        int cmax = get<1>(posM) + raio;

        for (int i = lmin; i <= lmax; i++)
        {
            for (int j = cmin; j <= cmax; j++)
            {
                if (i >= 0 && i < 10 && j >= 0 && j < 10)
                {
                    if (!environment[i][j].predatorList.empty())
                    {
                        randomWalk(monk);
                    }
                }
            }
        }
    }

    void perception(Predator &predator)
    {
        // Implemente o código da percepção do Monkey
        int raio = 3;
        tuple<int, int> posM = predator.getPosition();

        int lmin = get<0>(posM) - raio;
        int lmax = get<0>(posM) + raio;
        int cmin = get<1>(posM) - raio;
        int cmax = get<1>(posM) + raio;

        for (int i = lmin; i <= lmax; i++)
        {
            for (int j = cmin; j <= cmax; j++)
            {
                if (i >= 0 && i < 10 && j >= 0 && j < 10)
                {
                    if (!environment[i][j].monkeyList.empty())
                    {
                        randomWalk(predator);
                    }
                }
            }
        }
    }

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
                        cout << "Position of befor walk monkey is " << get<0>(monk.getPosition()) << ',' << get<1>(monk.getPosition()) << ".\n";

                        environment[get<0>(posM)][get<1>(posM)].monkeyList.pop_front();
                        monk.setPosition(environment[i][j].position);
                        environment[i][j].monkeyList.push_front(monk);

                        cout << "Position of after walk monkey is " << get<0>(monk.getPosition()) << ',' << get<1>(monk.getPosition()) << ".\n";
                        Environment::printEnvironment(environment);
                        return;
                    }
                }
            }
        }

        return;
    }

    void randomWalk(Predator &predator)
    {
        // Implemente o código da caminhada aleatória do Monkey
        int raio = 1;
        tuple<int, int> posM = predator.getPosition();

        for (int i = get<0>(posM) - raio; i <= get<0>(posM) + raio; i++)
        {
            for (int j = get<1>(posM) - raio; j <= get<1>(posM) + raio; j++)
            {
                if (i >= 0 && j >= 0 && i < 10 && j < 10 && i != j)
                {
                    if (environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty())
                    {
                        cout << "Position of befor walk predator is " << get<0>(predator.getPosition()) << ',' << get<1>(predator.getPosition()) << ".\n";

                        environment[get<0>(posM)][get<1>(posM)].predatorList.pop_front();
                        predator.setPosition(environment[i][j].position);
                        environment[i][j].predatorList.push_front(predator);

                        cout << "Position of after walk predator is " << get<0>(predator.getPosition()) << ',' << get<1>(predator.getPosition()) << ".\n";
                        Environment::printEnvironment(environment);
                        return;
                    }
                }
            }
        }

        return;
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
    list<Monkey> monkeyList;
    for (int i = 0; i < numMonkeys; i++)
    {
        Monkey monkey;
        Environment::addMonkey(environment, monkey);
        monkeyList.push_back(monkey);
    }

    // Adicionando predadores
    list<Predator> predatorList;
    std::vector<Predator::predatorType> predatorTypes = Predator::getPredatorTypes();
    for (const auto& type : predatorTypes)
    {
        Predator predador(type);
        Environment::addPredator(environment, predador);
        predatorList.push_back(predador);
    }
    cout << endl;


    Sobreviver sobreviver = Sobreviver(environment);
    Environment::printEnvironment(sobreviver.getEnvironment());     // Imprimindo os tipos dos elementos da matriz
    
    cout << endl;

    for (auto &monkey : monkeyList)
    {
        sobreviver.randomWalk(monkey);
        sobreviver.perception(monkey);
    }

    for (auto &predator : predatorList)
    {
        sobreviver.randomWalk(predator);
        sobreviver.perception(predator);
    }

    return 0;
}
