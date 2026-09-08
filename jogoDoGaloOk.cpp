#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*grupo 3: camila, betânia, sarah
ordem de apresentação: 4º grupo
tema: jogo do galo (jogo da velha)
entrega do código: 11/09
apresentação: 16/09*/

void guardarJogador(ofstream &ficheiro, string nomeJogador, int numPartidas,
                    int vitorias, int derrotas, int empates)
{
    ficheiro << nomeJogador << " " << numPartidas << " "
             << vitorias << " " << derrotas << " " << empates << endl;
}

bool mostrarJogador(ifstream &ficheiro, string &nomeJogador, int &numPartidas,
                    int &vitorias, int &derrotas, int &empates)
{
    return bool(ficheiro >> nomeJogador >> numPartidas >> vitorias >> derrotas >> empates);
}

void mostrarTabuleiro(char jogo[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            cout << " " << *(*(jogo + i) + j) << " ";
            if (j < 2)
            {
                cout << "|";
            }
        }

        if (i < 2)
        {
            cout << "\n---+---+---\n";
        }
    }
}

int main()
{

    int linha, coluna;
    char jogador1 = 'X';
    char jogador2 = 'O';
    char jogadorAtual;
    string nomeJogador1 = "";
    string nomeJogador2 = "";
    string nomeJogador = "";
    int numPartidasJ1 = 0;
    int numPartidasJ2 = 0;
    int vitoriasJ1 = 0;
    int vitoriasJ2 = 0;
    int derrotasJ1 = 0;
    int derrotasJ2 = 0;
    int empatesJ1 = 0;
    int empatesJ2 = 0;
    int finalJogo;
    int opcao;
    char posicao;
    int nivelBoot;

    do
    {

        do
        {
            cout << "Bem vindo ao Jogo do Galo!\n\n";
            cout << "Escolha entre as opcoes: \n";
            cout << "1 - Jogador vs Jogador\n";
            cout << "2 - Jogador vs Computador\n";
            cout << "3 - Estatisticas\n";
            cout << "4 - Sair" << endl;
            cin >> opcao;

            if (opcao == 1)
            {

                char jogo[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

                cout << "Insira o nome do primeiro jogador: ";
                getline(cin >> ws, nomeJogador1);

                cout << "Insira o nome do segundo jogador: ";
                getline(cin >> ws, nomeJogador2);

                cout << "O jogador 1 sera o 'X' e o jogador 2 sera o 'O'\n\n";
                cout << "Aqui esta o jogo da velha:\n";
                mostrarTabuleiro(jogo);

                for (int jogada = 0; jogada < 9; jogada++)
                {

                    if (jogada % 2 == 0)
                    {
                        jogadorAtual = jogador1; // descobrir como colocar o nome do jogador
                        cout << "\n\n"
                             << nomeJogador1 << ", ";
                    }

                    else
                    {

                        jogadorAtual = jogador2;
                        cout << "\n\n"
                             << nomeJogador2 << ", ";
                    }

                    cout << "qual a posicao que deseja realizar a jogada? ";
                    cout << "Escolha a linha (entre 1 e 3): ";
                    cin >> linha;
                    cout << "Escolha a coluna (entre 1 e 3): ";
                    cin >> coluna;

                    while (linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || *(*(jogo + (linha - 1)) + (coluna - 1)) != ' ')
                    {

                        if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3)
                        {

                            cout << "\n\nPosicao invalida! Escolha outra posicao!";
                        }

                        else if (*(*(jogo + (linha - 1)) + (coluna - 1)) != ' ')
                        {
                            cout << "\n\nPosicao ocupada! Escolha outra posicao!";
                        }

                        cout << "\n\nQual a posicao que deseja realizar a jogada?";
                        cout << "Escolha a linha (entre 1 e 3):";
                        cin >> linha;
                        cout << "Escolha a coluna (entre 1 e 3): \n";
                        cin >> coluna;
                        // descobrir como tirar esse codigo repetido
                    }

                    *(*(jogo + (linha - 1)) + (coluna - 1)) = jogadorAtual;

                    if (
                        (jogo[0][0] == jogadorAtual && jogo[0][1] == jogadorAtual && jogo[0][2] == jogadorAtual) ||
                        (jogo[1][0] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[1][2] == jogadorAtual) ||
                        (jogo[2][0] == jogadorAtual && jogo[2][1] == jogadorAtual && jogo[2][2] == jogadorAtual) ||

                        (jogo[0][0] == jogadorAtual && jogo[1][0] == jogadorAtual && jogo[2][0] == jogadorAtual) ||
                        (jogo[0][1] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[2][1] == jogadorAtual) ||
                        (jogo[0][2] == jogadorAtual && jogo[1][2] == jogadorAtual && jogo[2][2] == jogadorAtual) ||

                        (jogo[0][0] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[2][2] == jogadorAtual) ||
                        (jogo[0][2] == jogadorAtual && jogo[1][1] == jogadorAtual && jogo[2][0] == jogadorAtual))
                    {
                        if (jogadorAtual == jogador1)
                        {
                            cout << "\n"
                                 << nomeJogador1 << " venceu!\n";
                            numPartidasJ1++;
                            vitoriasJ1++;
                            numPartidasJ2++;
                            derrotasJ2++;
                        }
                        else if (jogadorAtual == jogador2)
                        {
                            cout << "\n"
                                 << nomeJogador2 << " venceu!\n";
                            numPartidasJ2++;
                            vitoriasJ2++;
                            numPartidasJ1++;
                            derrotasJ1++;
                        }

                        ofstream ficheiro("jogoDoGalo.txt", ios::app);
                        if (ficheiro.is_open())
                        {
                            guardarJogador(ficheiro, nomeJogador1, numPartidasJ1, vitoriasJ1, derrotasJ1, empatesJ1);
                            guardarJogador(ficheiro, nomeJogador2, numPartidasJ2, vitoriasJ2, derrotasJ2, empatesJ2);
                            ficheiro.close();
                        }
                        break;
                    }

                    if (jogada == 8)
                    {

                        cout << "Empate!\n";
                        numPartidasJ1++;
                        numPartidasJ2++;
                        empatesJ1++;
                        empatesJ2++;

                        ofstream ficheiro("jogoDoGalo.txt", ios::app);
                        if (ficheiro.is_open())
                        {
                            guardarJogador(ficheiro, nomeJogador1, numPartidasJ1, vitoriasJ1, derrotasJ1, empatesJ1);
                            guardarJogador(ficheiro, nomeJogador2, numPartidasJ2, vitoriasJ2, derrotasJ2, empatesJ2);
                            ficheiro.close();
                        }
                        mostrarTabuleiro(jogo);
                        break;
                    }

                    cout << "\n\n";
                    mostrarTabuleiro(jogo);
                }
            }
            else if (opcao == 2)
            {
                do
                {
                    cout << "Voce escolheu a opcao de jogar contra o computador\nVoce pode escolher entre dois niveis\n1 - Facil\n2 - Dificil\nEscolha um: ";
                    cin >> nivelBoot;
                    if (nivelBoot == 1){
                        cout << "Bem-vindo ao nivel facil!\n";
                        //add codigo
                    }
                    else if(nivelBoot == 2){
                        cout << "Bem-vindo ao nivel dificil!\n";
                        //add codigo
                    }
                    else{
                        cout << "Escolha invalida!\n\n";
                    }
                } while (nivelBoot < 1 || nivelBoot > 2);
            }
            else if (opcao == 3)
            {
                ifstream ficheiro("jogoDoGalo.txt");
                int numPartidas;
                int vitorias;
                int derrotas;
                int empates;

                if (!ficheiro.is_open())
                {
                    cout << "Erro ao abrir ficheiro\n";
                    return 1;
                }
                else
                {
                    cout << "Estatisticas: \n";

                    while (ficheiro >> nomeJogador >> numPartidas >> vitorias >> derrotas >> empates)
                    {
                        cout << "Jogador -> " << nomeJogador << ": Partidas: " << numPartidas << " | Vitorias: " << vitorias << " | Derrotas: " << derrotas << " | Empates: " << empates << endl;
                    }
                    ficheiro.close();
                }
            }
            else
            {
                break;
            }
        } while (opcao < 1 || opcao > 4);

        cout << "\n\nDeseja voltar ao menu inicial?\n1 - Sim\n2 - Nao\n";
        cin >> finalJogo;

    } while (finalJogo == 1);

    return 0;
}