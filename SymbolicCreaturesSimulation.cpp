#include <iostream>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include <list>
#include <string>
#include <cmath>
#include <map>
#include <iomanip>
#include <fstream>

using namespace std;

// Cores para representar os elementos
#define RESET "\033[37m"   // Resetar para a cor padrão
#define CYAN "\033[36m"    // Ciano -> Arvores
#define YELLOW "\033[33m"  // Amarelo -> Macacos
#define BLUE "\033[34m"    // Azul -> Aguia
#define MAGENTA "\033[35m" // Magenta -> Tigre
#define GREEN "\033[32m"   // Verde -> Cobra
#define RED "\033[31m"     // Vermelho -> Morte
#define BLACK "\033[30m"   // Preto -> quando macacos e predadores se encontram, mas não se veem

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
    Animal() : position(make_tuple(0, 0))
    {
    }

    // Construtor com parâmetros
    Animal(string n) : name(n), position(make_tuple(0, 0))
    {
    }

    virtual ~Animal() {}

    // Getter e Setter para Position
    string getName()
    {
        return name;
    }

    void setName(string n)
    {
        name = n;
    }

    // Getter e Setter para Position
    tuple<int, int> getPosition()
    {
        return position;
    }

    void setPosition(const tuple<int, int> &pos)
    {
        position = pos;
    }
};

// Classe Predator (herda de Animal)
class Predator : public Animal
{
private:
public:
    enum PredatorType
    {
        TI = 0, // Tiger
        EA = 1, // Eagle
        SN = 2  // Snake
    };

    // Tipo do Predador
    PredatorType type;

    // Construtor padrão de Predator
    Predator()
    {
    }

    // Construtor com parâmetros específicos de Predator
    Predator(const string &n, PredatorType t) : Animal(n), type(t)
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

// Classe Monkey (herda de Animal)
class Monkey : public Animal
{
private:
    vector<vector<float>> sinal;
    map<int, int> heardSignal;
    string filename; // Nome do arquivo a ser criado
    ofstream file;   // Arquivo de saída
    int printSignalCount = 0; // Contador para o número de vezes que a função printSignal foi chamada

public:
    // Construtor padrão de Monkey
    Monkey() : sinal(3, vector<float>(10))
    {
        filename = getName() + ".txt"; // Nome do arquivo é o nome do objeto seguido de ".txt"
        file.open(filename);           // Abre o arquivo para escrita

        // Preenchendo o vetor com números aleatórios entre 0 e 1
        for (int i = 0; i < 3; i++)
        {

            for (int j = 0; j < 10; j++)
            {
                sinal[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            }
        }
    }

    // Construtor com parâmetros específicos de Monkey
    Monkey(string n) : Animal(n), sinal(3, vector<float>(10))
    {
        setName(n); // Define o nome do objeto
        filename = getName() + ".txt"; // Nome do arquivo é o nome do objeto seguido de ".txt"
        file.open(filename);           // Abre o arquivo para escrita

        // Preenchendo o vetor com números aleatórios entre 0 e 1
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                sinal[i][j] = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
            }
        }
    }

    // Getter para o vetor sinal
    const vector<vector<float>> &getSinal() const
    {
        return sinal;
    }

    // Set para o vetor sinal
    void setSinal(const vector<vector<float>> &newSinal)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                sinal[i][j] = newSinal[i][j];
            }
        }
    }

    // Getter para o vetor sinal
    const map<int, int> &getHeardSignal() const
    {
        return heardSignal;
    }

    void setHeardSignal(const map<int, int> &newSinal)
    {
        heardSignal = newSinal;
    }

    void printSignal()
    {
        // Incrementa o contador de iterações toda vez que a função é chamada
        printSignalCount++;

        // Imprimir os sinais no arquivo
        file << "Iteration number: " << printSignalCount << "\n";

        for (size_t i = 0; i < sinal.size(); i++)
        {
            string predatorName = Predator::predatorTypeToString(static_cast<Predator::PredatorType>(i));
            file << getName() << " tell the signs to the predator " << predatorName << " is:" << endl;

            // Imprime os elementos do início até a metade do vetor
            for (size_t j = 0; j < sinal[i].size() / 2; j++)
            {
                file << "|Sig:(" << j << ") - Val:(" << std::fixed << std::setprecision(3) << sinal[i][j] << ")| ";
            }

            file << endl; // Quebra a linha após a primeira metade

            // Imprime a segunda metade dos elementos na próxima linha
            for (size_t j = sinal[i].size() / 2; j < sinal[i].size(); j++)
            {
                file << "|Sig:(" << j << ") - Val:(" << fixed << setprecision(3) << sinal[i][j] << ")| ";
            }

            file << endl; // Pula para a próxima linha após imprimir todos os elementos

            file << endl;
        }

        // Imprimir o maior sinal associado para cada animal
        for (size_t i = 0; i < sinal.size(); i++)
        {
            string predatorName = Predator::predatorTypeToString(static_cast<Predator::PredatorType>(i));
            float maxValue = 0;
            size_t maxSign = 0;

            for (size_t j = 0; j < sinal[i].size(); j++)
            {
                if (sinal[i][j] > maxValue)
                {
                    maxValue = sinal[i][j];
                    maxSign = j;
                }
            }

            cout << getName() << " has the highest index for the symbol " << maxSign << " with value "
            << fixed << setprecision(3) << maxValue << " for the predator " << predatorName << "." << endl;
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
    list<Monkey *> monkeyList;
    list<Predator *> predatorList;

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
            return "LT";
        default:
            return "Valor inválido";
        }
    }

    static void printEnvironment(Environment environment[linhaMatriz][colunaMatriz])
    {
        for (int i = 0; i < linhaMatriz; i++)
        {
            for (int j = 0; j < colunaMatriz; j++)
            {
                if (!environment[i][j].monkeyList.empty() && !environment[i][j].predatorList.empty())
                {
                    if (
                        (environment[i][j].type == Environment::GR || (environment[i][j].predatorList.front()->type == Predator::TI && environment[i][j].type == Environment::LT)) ||
                        (environment[i][j].predatorList.front()->type == Predator::EA && environment[i][j].type == Environment::HT) ||
                        (environment[i][j].predatorList.front()->type == Predator::SN && (environment[i][j].type == Environment::MT || environment[i][j].type == Environment::LT)))
                    {
                        cout << RED;
                    }
                    else
                    {
                        cout << BLACK;
                    }
                }
                else if (!environment[i][j].monkeyList.empty())
                {
                    cout << YELLOW;
                }
                else if (!environment[i][j].predatorList.empty())
                {
                    if (environment[i][j].predatorList.front()->type == Predator::SN)
                    {
                        cout << GREEN;
                    }
                    else if (environment[i][j].predatorList.front()->type == Predator::TI)
                    {
                        cout << MAGENTA;
                    }
                    else if (environment[i][j].predatorList.front()->type == Predator::EA)
                    {
                        cout << BLUE;
                    }
                }
                else if (environment[i][j].type != GR)
                {
                    cout << CYAN;
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
    static void addMonkey(Environment environment[linhaMatriz][colunaMatriz], Monkey *monk) // Recebe um ponteiro para Monkey
    {
        int it = 1;
        while (it != 0)
        {
            int i = rand() % linhaMatriz, j = rand() % colunaMatriz;
            if (environment[i][j].type == GR && environment[i][j].monkeyList.empty())
            {
                environment[i][j].monkeyList.push_back(monk);  // Adiciona o ponteiro na lista de monkeyList
                monk->setPosition(environment[i][j].position); // Define a posição do Monkey através do ponteiro
                cout << environment[i][j].monkeyList.back()->getName() << " added in position ("<< get<0>(environment[i][j].monkeyList.back()->getPosition()) << ','<< get<1>(environment[i][j].monkeyList.back()->getPosition())<< ").\n";
                //cout << "O endereco de memoria de " << environment[i][j].monkeyList.back()->getName() << " na funcao addMonkey e: " << environment[i][j].monkeyList.back() << endl;
                it--;
            }
        }
    }

    // Função para adicionar predadores no ambiente
    static void addPredator(Environment environment[linhaMatriz][colunaMatriz], Predator &pred) // Recebe o objeto Predator por referência
    {
        int it = 1;
        while (it != 0)
        {
            int i = rand() % linhaMatriz, j = rand() % colunaMatriz;
            if (environment[i][j].type == GR && environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty())
            {
                environment[i][j].predatorList.push_back(&pred); // Adiciona o ponteiro na lista de predatorList
                pred.setPosition(environment[i][j].position);    // Define a posição do Predator através do objeto
                if (pred.type == Predator::EA)
                {
                    cout << "Eagle added in position (" << get<0>(environment[i][j].predatorList.back()->getPosition()) << ',' << get<1>(environment[i][j].predatorList.back()->getPosition()) << ").\n";
                    //cout << "O endereco de memoria de " << environment[i][j].predatorList.back()->getName() << " na funcao addPredator e: " << environment[i][j].predatorList.back() << endl;
                }
                else if (pred.type == Predator::TI)
                {
                    cout << "Tiger added in position (" << get<0>(environment[i][j].predatorList.back()->getPosition()) << ',' << get<1>(environment[i][j].predatorList.back()->getPosition()) << ").\n";
                    //cout << "O endereco de memoria de " << environment[i][j].predatorList.back()->getName() << " na funcao addPredator e: " << environment[i][j].predatorList.back() << endl;
                }
                else if (pred.type == Predator::SN)
                {
                    cout << "Snake added in position (" << get<0>(environment[i][j].predatorList.back()->getPosition()) << ',' << get<1>(environment[i][j].predatorList.back()->getPosition()) << ").\n";
                    //cout << "O endereco de memoria de " << environment[i][j].predatorList.back()->getName() << " na funcao addPredator e: " << environment[i][j].predatorList.back() << endl;
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

    // Função de percepção do Macaco (Incompleto)
    void perception(Monkey *monk)
    {
        list<Environment *> securityOptions;   // Lista de opções seguras (arvores)
        list<Environment *> monkeyOptions;     // Lista de opções com macacos
        list<Environment *> noSecurityOptions; // Lista de opções com predadores
        int monkX = get<0>(monk->getPosition());
        int monkY = get<1>(monk->getPosition());

        tie(securityOptions, monkeyOptions, noSecurityOptions) = searchAreaMonkey(monk, securityOptions, monkeyOptions, noSecurityOptions);

        if (noSecurityOptions.empty())
        {
            cout << "Nothing important was noticed. " << monk->getName() << " random walking." << endl;
            randomWalk(monk);
        }
        else
        {
            cout << monk->getName() << " strategy walking." << endl;
            signalPredator(monkeyOptions, monk, noSecurityOptions.front());

            // Novo
            if ((environment[monkX][monkY].type == Environment::GR) ||
                (noSecurityOptions.front()->predatorList.front()->type == Predator::TI && environment[monkX][monkY].type != Environment::LT) ||
                (noSecurityOptions.front()->predatorList.front()->type == Predator::EA && environment[monkX][monkY].type != Environment::HT) ||
                (noSecurityOptions.front()->predatorList.front()->type == Predator::SN && (environment[monkX][monkY].type != Environment::MT)))
            {
                monkeyStrategyWalk(monk, securityOptions, noSecurityOptions.front());
            }
        }
    }

    tuple<list<Environment *>, list<Environment *>, list<Environment *>> searchAreaMonkey(
        Monkey *monk, list<Environment *> securityOptions, list<Environment *> monkeyOptions, list<Environment *> noSecurityOptions)
    {
        int raio = 1;
        int lmin = get<0>(monk->getPosition()) - raio;
        int lmax = get<0>(monk->getPosition()) + raio;
        int cmin = get<1>(monk->getPosition()) - raio;
        int cmax = get<1>(monk->getPosition()) + raio;

        cout << "Perception of " << monk->getName() << " in the position (" << get<0>(monk->getPosition()) << ","
             << get<1>(monk->getPosition()) << ") is: " << endl;

        for (int i = lmin; i <= lmax; i++)
        {
            for (int j = cmin; j <= cmax; j++)
            {
                if (i >= 0 && i < 10 && j >= 0 && j < 10 && monk->getPosition() != environment[i][j].position)
                {
                    if (environment[i][j].type != Environment::GR && environment[i][j].predatorList.empty())
                    {
                        securityOptions.push_back(&environment[i][j]);
                    }
                    else if (!environment[i][j].monkeyList.empty())
                    {
                        monkeyOptions.push_back(&environment[i][j]);
                    }
                    else if (!environment[i][j].predatorList.empty())
                    {
                        noSecurityOptions.push_back(&environment[i][j]);
                        cout << environment[i][j].predatorList.front()->getName() << " in the position (" << i << "," << j << "), add in no security list." << endl;
                    }
                }
            }
        }

        return make_tuple(securityOptions, monkeyOptions, noSecurityOptions);
    }

    void signalPredator(list<Environment *> monkeyOptions, Monkey *monkScreams, Environment *envPredator)
    {
        int monkScreamsX = get<0>(monkScreams->getPosition());
        int monkScreamsY = get<1>(monkScreams->getPosition());
        cout << monkScreams->getName() << " in the position (" << monkScreamsX << "," << monkScreamsY
        << ") scream signal of " << envPredator->predatorList.front()->getName()
        << " in the position (" << get<0>(envPredator->predatorList.front()->getPosition()) << ","
        << get<1>(envPredator->predatorList.front()->getPosition()) << ")." << endl;

        if (monkeyOptions.empty())
            return;

        vector<float> signalsMonk = monkScreams->getSinal()[envPredator->predatorList.front()->type];

        float posSignal = getPosicaoMaiorValor(signalsMonk);

        for (const auto &monkey : monkeyOptions)
        {
            Monkey *monkHear = monkey->monkeyList.front();
            vector<float> listSignal;
            bool safePlace = false;
            int monkHearX = get<0>(monkHear->getPosition());
            int monkHearY = get<1>(monkHear->getPosition());

            list<Environment *> securityOptions;   // Lista de opções seguras (arvores)
            list<Environment *> monkeyOptions;     // Lista de opções com macacos
            list<Environment *> noSecurityOptions; // Lista de opções com predadores

            cout << monkHear->getName() << " in the position (" << monkHearX << "," << monkHearY
            << ") heard the signal from " << envPredator->predatorList.front()->getName() << ".\n" << endl;

            tie(securityOptions, monkeyOptions, noSecurityOptions) = searchAreaMonkey(monkHear, securityOptions, monkeyOptions, noSecurityOptions);

            // Decifrar sinal
            for (size_t i = 0; i < 3; i++)
            {
                listSignal.push_back(monkey->monkeyList.front()->getSinal()[i][posSignal]);
            }

            int type = getPosicaoMaiorValor(listSignal);
            // mover para árvore ou lado oposto do grito

            // se ouviu e viu o predador, aumenta o sinal
            bool sawPredator = false;
            for (const auto &pred : noSecurityOptions)
            {
                if (pred->predatorList.front()->type == type)
                {
                    vector<vector<float>> novoSinal = monkHear->getSinal();
                    novoSinal[type][posSignal] = max(0.0f, monkHear->getSinal()[type][posSignal] + 0.1f);
                    monkHear->setSinal(novoSinal);
                    sawPredator = true;
                    monkHear->printSignal();
                }
            }

            // se ouviu e não viu o predador, guarda o sinal
            if (!sawPredator)
            {
                map<int, int> m_signal;
                m_signal.insert(make_pair(type, posSignal));
                monkHear->setHeardSignal(m_signal);
            }

            if (Predator::TI == type)
            {
                // Deve se proteger em MT
                for (const auto &op : securityOptions)
                {
                    if (op->type == Environment::MT)
                    {
                        moveTowardTree(monkHear, op);
                        safePlace = true;
                    }
                }
            }
            else if (Predator::EA == type)
            {
                // Deve se proteger em LT
                for (const auto &op : securityOptions)
                {
                    if (op->type == Environment::LT)
                    {
                        moveTowardTree(monkHear, op);
                        safePlace = true;
                    }
                }
            }
            else if (Predator::SN == type)
            {
                // Deve se proteger em HT
                for (const auto &op : securityOptions)
                {
                    if (op->type == Environment::HT)
                    {
                        moveTowardTree(monkHear, op);
                        safePlace = true;
                    }
                }
            }
            else if (!safePlace)
            {
                moveOppositePositionToPredator(monkHear, monkScreamsX, monkScreamsY);
            }

            Environment::printEnvironment(environment);
        }
    }

    size_t getPosicaoMaiorValor(const vector<float> &vetor)
    {
        if (vetor.empty())
        {
            // Lidar com o caso de vetor vazio, se necessário
            // Neste exemplo, retornamos um valor inválido
            return static_cast<size_t>(-1);
        }

        float maiorValor = vetor[0];  // Inicializa o maior valor como o primeiro elemento do vetor
        size_t posicaoMaiorValor = 0; // Inicializa a posição do maior valor como 0

        for (size_t i = 1; i < vetor.size(); i++)
        {
            if (vetor[i] > maiorValor)
            {
                maiorValor = vetor[i]; // Atualiza o maior valor, se um valor maior for encontrado
                posicaoMaiorValor = i; // Atualiza a posição do maior valor
            }
        }

        return posicaoMaiorValor;
    }

    // Função de percepção do Predador (Incompleto)
    void perception(Predator *pred)
    {
        int raio = 1;
        int lmin = get<0>(pred->getPosition()) - raio;
        int lmax = get<0>(pred->getPosition()) + raio;
        int cmin = get<1>(pred->getPosition()) - raio;
        int cmax = get<1>(pred->getPosition()) + raio;
        int predX = get<0>(pred->getPosition());
        int predY = get<1>(pred->getPosition());

        list<Environment *> targetOptions; // Lista de oções alvo (com macacos)

        cout << "Perception of " << pred->getName() << " in the position (" << get<0>(pred->getPosition()) << ","
             << get<1>(pred->getPosition()) << ") is: " << endl;

        for (int i = lmin; i <= lmax; i++)
        {
            for (int j = cmin; j <= cmax; j++)
            {
                if (i >= 0 && i < 10 && j >= 0 && j < 10 && pred->getPosition() != environment[i][j].position)
                {
                    if (!environment[i][j].monkeyList.empty())
                    {
                        // Predador consegue ver o macaco?
                        if (
                            (environment[predX][predY].type == Environment::GR) ||
                            (pred->type == Predator::TI && environment[predX][predY].type != Environment::LT) ||
                            (pred->type == Predator::EA && environment[predX][predY].type != Environment::HT) ||
                            (pred->type == Predator::SN && (environment[predX][predY].type != Environment::MT)))
                        {
                            targetOptions.push_back(&environment[i][j]);
                            cout << targetOptions.back()->monkeyList.front()->getName() << " in position (" << i << "," << j << ") add in target list." << endl;
                        }
                    }
                }
            }
        }

        if (targetOptions.empty())
        {
            cout << "Nothing important was noticed. " << pred->getName() << " random walking." << endl;
            randomWalk(pred);
        }
        else
        {
            cout << pred->getName() << " strategy walking." << endl;
            Monkey *targetMonkeyPtr = targetOptions.front()->monkeyList.front();
            predatorStrategyWalk(pred, targetMonkeyPtr);
        }
    }

    // Função de andar aleatória para macaco
    void randomWalk(Monkey *monk)
    {
        // Implemente o código da caminhada aleatória do Monkey
        int raio = 1;
        tuple<int, int> posM = monk->getPosition();

        for (int i = get<0>(posM) - raio; i <= get<0>(posM) + raio; i++)
        {
            for (int j = get<1>(posM) - raio; j <= get<1>(posM) + raio; j++)
            {
                if (i >= 0 && j >= 0 && i < 10 && j < 10 && i != j)
                {
                    if (environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty())
                    {
                        cout << "Position of " << monk->getName() << " before walk is (" << get<0>(monk->getPosition()) << ',' << get<1>(monk->getPosition()) << ").\n";

                        environment[get<0>(posM)][get<1>(posM)].monkeyList.pop_front();
                        monk->setPosition(environment[i][j].position);
                        environment[i][j].monkeyList.push_front(monk);

                        cout << "Position of " << monk->getName() << " after walk is (" << get<0>(monk->getPosition()) << ',' << get<1>(monk->getPosition()) << ").\n\n";
                        Environment::printEnvironment(environment);
                        return;
                    }
                }
            }
        }

        return;
    }

    // Função de andar aleatória para predador
    void randomWalk(Predator *pred)
    {
        // Implemente o código da caminhada aleatória do Monkey
        int raio = 1;
        tuple<int, int> posM = pred->getPosition();

        for (int i = get<0>(posM) - raio; i <= get<0>(posM) + raio; i++)
        {
            for (int j = get<1>(posM) - raio; j <= get<1>(posM) + raio; j++)
            {
                if (i >= 0 && j >= 0 && i < 10 && j < 10 && i != j)
                {
                    if (environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty())
                    {
                        cout << "Position of " << pred->getName() << " before walk is (" << get<0>(pred->getPosition()) << ',' << get<1>(pred->getPosition()) << ").\n";

                        environment[get<0>(posM)][get<1>(posM)].predatorList.pop_front();
                        pred->setPosition(environment[i][j].position);
                        environment[i][j].predatorList.push_front(pred);

                        cout << "Position of " << pred->getName() << " after walk is (" << get<0>(pred->getPosition()) << ',' << get<1>(pred->getPosition()) << ").\n\n";
                        Environment::printEnvironment(environment);
                        return;
                    }
                }
            }
        }

        return;
    }

    // Fugir do predador ao ir em direção à arvore ou direção oposta
    void monkeyStrategyWalk(Monkey *monk, list<Environment *> securityOptions, Environment *envPredator)
    {
        // Encontra um predador na lista de opções sem segurança
        int predX = get<0>(envPredator->position);
        int predY = get<1>(envPredator->position);
        bool safePlace = false;

        // Conferir qual é o tipo do predador
        Predator::PredatorType predType = envPredator->predatorList.front()->type;

        if (!securityOptions.empty())
        {

            if (predType == Predator::TI)
            {
                // Deve se proteger em MT
                for (const auto &op : securityOptions)
                {
                    if (op->type == Environment::MT)
                    {
                        moveTowardTree(monk, op);
                        safePlace = true;
                    }
                }
            }
            else if (predType == Predator::EA)
            {
                // Deve se proteger em LT
                for (const auto &op : securityOptions)
                {
                    if (op->type == Environment::LT)
                    {
                        moveTowardTree(monk, op);
                        safePlace = true;
                    }
                }
            }
            else if (predType == Predator::SN)
            {
                // Deve se proteger em HT
                for (const auto &op : securityOptions)
                {
                    if (op->type == Environment::HT)
                    {
                        moveTowardTree(monk, op);
                        safePlace = true;
                    }
                }
            }
            else if (!safePlace)
            {
                moveOppositePositionToPredator(monk, predX, predY);
            }
        }
        else
        {
            moveOppositePositionToPredator(monk, predX, predY);
        }

        Environment::printEnvironment(environment);
    }

    // Macaco move em direção à arvore
    void moveTowardTree(Monkey *monk, Environment *op)
    {
        // Armazena as coordenadas do macaco e da árvore
        int monkX = get<0>(monk->getPosition());
        int monkY = get<1>(monk->getPosition());
        int treeX = get<0>(op->position);
        int treeY = get<1>(op->position);

        // Calcula a diferença entre as coordenadas do macaco e da árvore
        int dx = treeX - monkX;
        int dy = treeY - monkY;

        // Limita o movimento a um raio de 1 em relação à posição atual do macaco
        dx = max(-1, min(dx, 1));
        dy = max(-1, min(dy, 1));

        // Calcula a nova posição para o macaco
        int x = (monkX + dx + 10) % 10;
        int y = (monkY + dy + 10) % 10;

        // Move o macaco para a nova posição
        environment[monkX][monkY].monkeyList.pop_front();
        monk->setPosition(environment[x][y].position);
        environment[x][y].monkeyList.push_front(monk);

        cout << monk->getName() << " move to type tree " << Environment::environmentTypeToString(op->type) <<
        " in the position (" << get<0>(op->position)<< "," << get<0>(op->position) << ").\n\n";
    }

    // Macaco vai em direção oposta ao predador
    void moveOppositePositionToPredator(Monkey *monk, int predX, int predY)
    {
        // Armazena as coordenadas do macaco
        int monkX = get<0>(monk->getPosition());
        int monkY = get<1>(monk->getPosition());

        // Calcula a diferença entre as coordenadas do macaco e do predador
        int dx = monkX - predX;
        int dy = monkY - predY;

        // Limita o movimento a um raio de 1 em relação à posição atual do macaco
        dx = max(-1, min(dx, 1));
        dy = max(-1, min(dy, 1));

        // Calcula a nova posição para o macaco
        int x = (monkX + dx + 10) % 10;
        int y = (monkY + dy + 10) % 10;

        // Move o macaco para a nova posição
        environment[monkX][monkY].monkeyList.pop_front();
        monk->setPosition(environment[x][y].position);
        environment[x][y].monkeyList.push_front(monk);

        cout << monk->getName() << " moving to the opposite side to position (" << get<0>(environment[x][y].position)
        << "," << get<1>(environment[x][y].position) << ").\n"<< endl;
    }

    // Função de andar não aleatória do predador (incompleta)
    // Está função vai receber a lista de alvos. Será escolhido um alvo aleatório e se mover para a lista de predadores da mesma função do seu alvo
    void predatorStrategyWalk(Predator *pred, Monkey *monk)
    {
        // Armazena as coordenadas do predador e do macaco
        int predX = get<0>(pred->getPosition());
        int predY = get<1>(pred->getPosition());
        int monkX = get<0>(monk->getPosition());
        int monkY = get<1>(monk->getPosition());

        // Calcula a diferença entre as coordenadas do macaco e do predador
        int dx = monkX - predX;
        int dy = monkY - predY;

        // Limita o movimento a um raio de 1 em relação à posição atual do predador
        dx = max(-1, min(dx, 1));
        dy = max(-1, min(dy, 1));

        // Calcula a nova posição para o predador
        int x = (predX + dx + 10) % 10;
        int y = (predY + dy + 10) % 10;

        // Move o predador para a nova posição
        environment[predX][predY].predatorList.pop_front();
        pred->setPosition(environment[x][y].position);
        environment[x][y].predatorList.push_front(pred);

        // Confere se existe macaco para ser atacado
        if (!environment[x][y].monkeyList.empty())
        {
            // Predador irá atacar apenas no ambiente que ele consegue visualizar
            if (
                (environment[x][y].type == Environment::GR ||
                (environment[x][y].predatorList.front()->type == Predator::TI && environment[x][y].type == Environment::LT) ||
                (environment[x][y].predatorList.front()->type == Predator::EA && environment[x][y].type == Environment::HT) ||
                (environment[x][y].predatorList.front()->type == Predator::SN && (environment[x][y].type == Environment::MT))))
            {
                cout << "Walking to position (" << get<0>(monk->getPosition()) << ',' << get<1>(monk->getPosition()) << ") and killed " << monk->getName() << ".\n";
                predatorAttack(pred, monk);
            }
            // Caso va para onde não consiga matar o macaco
            else{
                cout << "Walking to position (" << get<0>(monk->getPosition()) << ',' << get<1>(monk->getPosition()) << ") but not killed " << monk->getName() << ".\n" << endl;
            }
        }
        Environment::printEnvironment(environment);
    }

    // Se o predador atacar, deve abaixar o percentual do sinal no vetor de sinais do macaco
    void predatorAttack(Predator *pred, Monkey *monk)
    {
        // Inicializa o índice e valor máximo com o primeiro elemento do vetor sinal
        int maxSignalIndex = 0;
        float maxSignal = monk->getSinal()[0][0];
        tuple<int, int> posM = monk->getPosition();

        // Procura o predador com o sinal mais forte
        for (int signal = 0; signal < 10; signal++)
        {
            if (monk->getSinal()[pred->type][signal] > maxSignal)
            {
                maxSignalIndex = signal;
                maxSignal = monk->getSinal()[pred->type][signal];
            }
        }

        // Reduz o sinal do predador mais forte caso o macaco já tenha sido alertado
        if (!monk->getHeardSignal().empty())
        {
            for (const auto &signal : monk->getHeardSignal())
            {
                if (pred->type == signal.first)
                {
                    vector<vector<float>> novoSinal = monk->getSinal();
                    novoSinal[pred->type][maxSignalIndex] = max(0.0f, monk->getSinal()[pred->type][maxSignalIndex] - 0.1f);
                    monk->setSinal(novoSinal);
                    monk->printSignal();
                }
            }
        }

        cout << "Death - sign reset.\n\n";
        Environment::printEnvironment(environment);

        // Mover macaco morto para outro lugar -- reviver
        bool moveu = false;
        while (!moveu)
        {
            int i = rand() % linhaMatriz, j = rand() % colunaMatriz;
            if (i >= 0 && i < 10 && j >= 0 && j < 10 && environment[i][j].monkeyList.empty() && environment[i][j].predatorList.empty())
            {
                environment[get<0>(posM)][get<1>(posM)].monkeyList.pop_front();
                monk->setPosition(environment[i][j].position);
                environment[i][j].monkeyList.push_front(monk);
                moveu = true;
                cout << "New position of " << monk->getName() << " is (" << get<0>(monk->getPosition()) << ',' << get<1>(monk->getPosition()) << ").\n" << endl;
            }
        }
    }

    // Função para verificar se em todos os monkeys tem um sinal maior que 1 para cada animal
    bool verifySignal(list<Monkey *> monkeysList)
    {
        float tolerance = 1.0;
        for (Monkey *monkey : monkeysList)
        {
            const vector<vector<float>> &sinal = monkey->getSinal();

            // Verificar se existe ao menos um valor de índice j que seja igual ou maior que 1
            bool foundSignalForAllIndices = true;
            for (size_t i = 0; i < sinal.size(); i++)
            {
                string predatorName = Predator::predatorTypeToString(static_cast<Predator::PredatorType>(i));
                bool foundSignalForIndex = false;
                for (size_t j = 0; j < sinal[i].size(); j++)
                {
                    if (sinal[i][j] >= tolerance)
                    {
                        foundSignalForIndex = true;
                        cout << monkey->getName() << " tem o sinal " << j << " para o predador " << predatorName
                        << " com valor " << sinal[i][j] << " maior ou igual a tolerancia " << tolerance << ".\n";
                        break;
                    }
                }
                if (!foundSignalForIndex)
                {
                    foundSignalForAllIndices = false;
                    break;
                }
            }

            // Se não foi encontrado sinal com valor maior ou igual a 1 para algum índice i, retornar false
            if (!foundSignalForAllIndices)
                return false;
        }

        // Se todos os objetos têm pelo menos um sinal com valor maior ou igual a 1 para cada índice i, retornar true
        return true;
    }

};

int main()
{
    // Configurando a semente para geração de números aleatórios
    srand(time(nullptr));
    
    // Declarando uma matriz 10x10 de objetos Environment
    Environment environment[linhaMatriz][colunaMatriz];

    // Adicionando coordenadas
    Environment::addPos(environment);

    // Adicionando árvores
    Environment::addTree(environment, Environment::HT, 4);
    Environment::addTree(environment, Environment::MT, 4);
    Environment::addTree(environment, Environment::LT, 4);

    // Adicionando macacos
    list<Monkey *> monkeysList; // Lista de ponteiros para Monkey
    for (int i = 0; i < numMonkeys; i++)
    {
        Monkey *monkey = new Monkey("Monkey" + to_string(i + 1)); // Cria um novo Monkey na memória e armazena seu ponteiro
        monkeysList.push_back(monkey);                            // Adiciona o ponteiro para o Monkey na lista de ponteiros
        Environment::addMonkey(environment, monkey);              // Passa o ponteiro para a função addMonkey
        //cout << "O endereco de memoria de " << monkeysList.back()->getName() << " na funcao MAIN e: " << monkeysList.back() << endl;
        monkeysList.back()->printSignal(); // Imprime os sinais dos animeis
    }

    // Adicionando predadores
    list<Predator *> predatorsList; // Lista de ponteiros para Predator
    vector<Predator::PredatorType> predatorTypes = Predator::getPredatorTypes();
    for (const auto &type : predatorTypes)
    {
        Predator *predator = new Predator(Predator::predatorTypeToString(type), type); // Cria um novo Predator na memória e armazena seu ponteiro
        Environment::addPredator(environment, *predator);                              // Passa o objeto Predator por referência para a função addPredator
        predatorsList.push_back(predator);                                             // Adiciona o ponteiro para o Predator na lista de ponteiros
        //cout << "O endereco de memoria de " << predatorsList.back()->getName() << " na funcao MAIN e: " << predatorsList.back() << endl;
    }
    cout << endl;

    Sobreviver sobreviver = Sobreviver(environment);
    Environment::printEnvironment(sobreviver.getEnvironment()); // Imprimindo os tipos dos elementos da matriz

    bool verify = false;
    while(verify != true){
        for (auto &monkey : monkeysList)
        {
            sobreviver.perception(monkey);
        }

        for (auto &predator : predatorsList)
        {
            sobreviver.perception(predator);
        }

        verify = sobreviver.verifySignal(monkeysList);
    }

    return 0;
}