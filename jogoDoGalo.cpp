#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*grupo 3: camila, betânia, sarah
ordem de apresentação: 4º grupo
tema: jogo do galo (jogo da velha)
entrega do código: 11/09
apresentação: 16/09*/

fstream ficheiro("jogoDoGalo.txt", ios::in | ios::out | ios::app); // ONDE COLOCAR ISSO, ANTES OU DEPOIS DO MAIN, OU
// DENTRO DA FUNÇÃO

void guardarJogador(ofstream &ficheiro, string nomeJogador, int numPartidas,
                    int vitorias, int derrotas, int empates)
{
    ficheiro << "Nome: " << nomeJogador << "\nNumero de partidas: " << numPartidas << "\nVitorias: " << vitorias << "\nDerrotas: " << derrotas << "\nEmpates: " << empates << endl;
}

bool mostrarJogador(ifstream &ficheiro, string &nomeJogador, int &numPartidas,
                    int &vitorias, int &derrotas, int &empates)
{
    return bool(ficheiro >> nomeJogador >> numPartidas >> vitorias >> derrotas >> empates);
}

int main()
{
    ofstream ficheiro("jogoDoGalo.txt");

    int finalJogo;
    int opcao;
    string jogador1 = "";
    string jogador2 = "";
    int jogo[3][3] = {{1, 2, 3},
                      {4, 5, 6},
                      {7, 8, 9}};

    if (!ficheiro.is_open())
    {
        cout << "Erro ao abrir ficheiro";
        return 1;
    }

    do
    {

        do
        {
            cout << "Bem vindo ao Jogo do Galo!\n\n";
            cout << "Escolha entre as opcoes: \n";
            cout << "1 - Jogador vs Jogador\n";
            cout << "2 - Jogador vs Computador\n";
            cout << "3 - Estatisticas" << endl;
            cin >> opcao;

            if (opcao == 1)
            {
                //receber o espaço do int
                cout << "Insira o nome do primeiro jogador: ";
                getline(cin >> ws, jogador1);

                cout << "Insira o nome do segundo jogador: ";
                getline(cin >> ws, jogador2);

                cout << "O jogador 1 sera o 'X' e o jogador 2 sera o 'O'\n\n";
                cout << "Aqui esta o jogo da velha:\n";
                cout << "| " << jogo[0][0] << " | " << jogo[0][1] << " | " << jogo[0][2] << " |\n";
                cout << " ___________\n";
                cout << "| " << jogo[1][0] << " | " << jogo[1][1] << " | " << jogo[1][2] << " |\n";
                cout << " ___________\n";
                cout << "| " << jogo[2][0] << " | " << jogo[2][1] << " | " << jogo[2][2] << " |\n";
                cout << " ___________\n\n";
                cout << "Voces terao que escolher uma posicao de acordo com os numeros mostrados!\n";
            }
            else if (opcao == 2)
            {
            }
            else
            {
                ifstream in("jogoDoGalo.txt");
                string nomeJogador;
                int numPartidas;
                int vitorias;
                int derrotas;
                int empates;
                while (in >> nomeJogador >> numPartidas >> vitorias >> derrotas >> empates)
                {
                    cout << nomeJogador << "->" << numPartidas << "->" << vitorias << "->" << derrotas << "->" << empates << endl;
                }
                in.close();
            }
        } while (opcao < 1 || opcao > 3);

        cout << "\nDeseja iniciar uma nova partida?\n1 - Sim\n2 - Nao\n";
        cin >> finalJogo;

    } while (finalJogo == 1);

    ficheiro << jogador1 << endl;
    ficheiro.close();

    /*
        int qtd;
        int posicao = 0;
        char jogo[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
        char jogador1 = 'X';
        char jogador2 = 'O';
        char vencedor = ' ';

        int vitorias[8][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},
            {0, 4, 8},
            {2, 4, 6}};

        do
        {
            std::cout << "Bem vindo ao jogo da velha! Escolha a quantidade de jogadores: ";
            std::cin >> qtd;
        } while (qtd != 1 && qtd != 2);

        if (qtd == 1)
        {
            std::cout << "Em breve iremos adicionar esta funcionalidade, para voce poder jogar contra o computador!";
            std::cout << "Volte ao menu do jogo por favor!";
        }
        else if (qtd == 2)
        {
            std::cout << "Escolheu 2 jogadores, preparem-se!\n";
            std::cout << "O jogador 1 sera o 'X' e o jogador 2 sera o 'O'\n\n";
            std::cout << "Aqui esta o jogo da velha:\n";
            std::cout << "| " << jogo[0] << " | " << jogo[1] << " | " << jogo[2] << " |\n";
            std::cout << " ___________\n";
            std::cout << "| " << jogo[3] << " | " << jogo[4] << " | " << jogo[5] << " |\n";
            std::cout << " ___________\n";
            std::cout << "| " << jogo[6] << " | " << jogo[7] << " | " << jogo[8] << " |\n";
            std::cout << " ___________\n\n";
            std::cout << "Voces terao que escolher uma posicao de acordo com os numeros mostrados!\n";

            do
            {
                for (int i = 0; i < 9; i++)
                {
                    if (i % 2 == 0)
                    {
                        std::cout << "Jogador 1, escolha uma posicao do jogo da velha: ";
                        std::cin >> posicao;
                        jogo[posicao - 1] = jogador1;
                    }
                    else
                    {
                        std::cout << "Jogador 2, escolha uma posicao do jogo da velha: ";
                        std::cin >> posicao;
                        jogo[posicao - 1] = jogador2;
                    }

                    for (int d = 0; d < 6; d++)
                    {
                        std::cout << "\n";
                    }

                    std::cout << "Atualizacao do jogo da velha:\n";
                    std::cout << "| " << jogo[0] << " | " << jogo[1] << " | " << jogo[2] << " |\n";
                    std::cout << " ___________\n";
                    std::cout << "| " << jogo[3] << " | " << jogo[4] << " | " << jogo[5] << " |\n";
                    std::cout << " ___________\n";
                    std::cout << "| " << jogo[6] << " | " << jogo[7] << " | " << jogo[8] << " |\n";
                    std::cout << " ___________\n\n";

                    for (int c = 0; c < 8; c++)
                    {
                        if (jogo[vitorias[c][0]] == jogo[vitorias[c][1]] && jogo[vitorias[c][1]] == jogo[vitorias[c][2]])
                        {
                            vencedor = jogo[vitorias[c][0]];
                            break;
                        }
                    }

                    if (vencedor != ' ')
                    {
                        break;
                    }
                }

                if (vencedor == jogador1)
                {
                    std::cout << "O jogador 1 venceu!";
                }
                else if (vencedor == jogador2)
                {
                    std::cout << "O jogador 2 venceu!";
                }
                else
                {
                    std::cout << "Os dois perderam!";
                }
            } while (posicao < 1 || posicao > 9);
        }*/

    return 0;
}