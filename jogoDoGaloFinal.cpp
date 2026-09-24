#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

/*grupo 3: camila, betânia, sarah
ordem de apresentação: 4º grupo
tema: jogo do galo (jogo da velha)
entrega do código: 11/09
apresentação: 16/09*/

void mostrarTabuleiroAtt(char jogo[9])
{
    cout << " " << jogo[0] << " | " << jogo[1] << " | " << jogo[2] << "\n";
    cout << "---+---+---\n";
    cout << " " << jogo[3] << " | " << jogo[4] << " | " << jogo[5] << "\n";
    cout << "---+---+---\n";
    cout << " " << jogo[6] << " | " << jogo[7] << " | " << jogo[8] << "\n";
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

void guardarJogador(string nomeJogador, int partida, int vitoria, int derrota, int empate)
{
    string nomes[100];
    int partidas[100], vitorias[100], derrotas[100], empates[100];
    int total = 0;

    ifstream entrada("jogoDoGalo.txt");
    if (entrada.is_open())       
    {
        while (getline(entrada, nomes[total]))
        {
            entrada >> partidas[total] >> vitorias[total] >> derrotas[total] >> empates[total];
            entrada >> ws;
            total++;
        }
        entrada.close();
    }

    int encontrado = 0;
    for (int i = 0; i < total; i++)
    {
        if (nomes[i] == nomeJogador)
        {
            partidas[i] = partidas[i] + 1;
            vitorias[i] = vitorias[i] + vitoria;
            derrotas[i] = derrotas[i] + derrota;
            empates[i] = empates[i] + empate;
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0)
    {
        nomes[total] = nomeJogador;
        partidas[total] = 1;
        vitorias[total] = vitoria;
        derrotas[total] = derrota;
        empates[total] = empate;
        total++;
    }

    ofstream saida("jogoDoGalo.txt");
    if (saida.is_open())
    {
        for (int i = 0; i < total; i++)
        {
            saida << nomes[i] << endl;
            saida << partidas[i] << " " << vitorias[i] << " " << derrotas[i] << " " << empates[i] << endl;
        }
        saida.close();
    }
}

bool mostrarJogador(ifstream &ficheiro, string &nomeJogador, int &numPartidas,
                    int &vitorias, int &derrotas, int &empates)
{
    if (!ficheiro.is_open())
    {
        cout << "Erro ao abrir ficheiro\n";
        return false;
    }
    else
    {
        cout << "Estatisticas: \n";

        while (getline(ficheiro, nomeJogador) && (ficheiro >> numPartidas >> vitorias >> derrotas >> empates))
        {
            cout << "Jogador -> " << nomeJogador << ": Partidas: " << numPartidas
                 << " | Vitorias: " << vitorias << " | Derrotas: " << derrotas
                 << " | Empates: " << empates << endl;

            ficheiro >> ws;
        }

        ficheiro.close();
        return true;
    }
}

bool verificarPosicao(char jogo[9], int posicao)
{
    if (posicao < 1 || posicao > 9)
    {
        cout << "\nPosicao invalida, escolha outra posicao!\n";
        return false;
    }

    else if (jogo[posicao - 1] != ' ')
    {
        cout << "\nPosicao ocupada, escolha outra posicao!\n";
        return false;
    }
    return true;
}

bool verificarPosicaoPc(char jogo[9], int posicao)
{
    int i;
    if (posicao < 1 || posicao > 9)
    {
        cout << "\nPosicao invalida, escolha outra posicao!\n";
        return false;
    }

    else if (jogo[posicao - 1] != ' ' && i % 2 == 0)
    {
        cout << "\nPosicao ocupada, escolha outra posicao!\n";
        return false;
    }
    return true;
}

void vitoriasEmpates(char jogo[9], int vitorias[8][3], char &vencedor, int &bloqueadas, int &empate)
{
    vencedor = ' ';
    bloqueadas = 0;
    empate = 0;

    for (int j = 0; j < 8; j++)
    {
        if (jogo[vitorias[j][0]] != ' ' && jogo[vitorias[j][0]] == jogo[vitorias[j][1]] && jogo[vitorias[j][1]] == jogo[vitorias[j][2]])
        {
            vencedor = jogo[vitorias[j][0]];
            break;
        }
    }

    for (int j = 0; j < 8; j++)
    {
        if ((jogo[vitorias[j][0]] == 'X' ||
             jogo[vitorias[j][1]] == 'X' ||
             jogo[vitorias[j][2]] == 'X') &&

            (jogo[vitorias[j][0]] == 'O' ||
             jogo[vitorias[j][1]] == 'O' ||
             jogo[vitorias[j][2]] == 'O'))
        {
            bloqueadas++;
        }
    }

    if (bloqueadas == 8)
    {
        empate = 1;
    }
}

void verificarVitoriaJogadores(char vencedor, char jogador1, char jogador2, string nomeJogador1, string nomeJogador2, char jogo[9])
{
    if (vencedor == jogador1)
    {
        cout << "\n\n"
             << nomeJogador1 << " venceu!\n\n";

        mostrarTabuleiroAtt(jogo);

        guardarJogador(nomeJogador1, 1, 1, 0, 0);
        guardarJogador(nomeJogador2, 1, 0, 1, 0);
        return;
    }
    else if (vencedor == jogador2)
    {
        cout << "\n\n"
             << nomeJogador2 << " venceu!\n\n";

        mostrarTabuleiroAtt(jogo);

        guardarJogador(nomeJogador1, 1, 0, 1, 0);
        guardarJogador(nomeJogador2, 1, 1, 0, 0);
        return;
    }
    else
    {
        cout << "\n\nEmpate!\n\n";

        mostrarTabuleiroAtt(jogo);

        guardarJogador(nomeJogador1, 1, 0, 0, 1);
        guardarJogador(nomeJogador2, 1, 0, 0, 1);
        return;
    }
}

void verificarVitoriasBoot(char vencedor, char jogador1, char boot, string nomeJogador1, char jogo[9])
{
    if (vencedor == jogador1)
    {
        cout << "\n\n"
             << nomeJogador1 << " venceu!\n\n";

        mostrarTabuleiroAtt(jogo);

        guardarJogador(nomeJogador1, 1, 1, 0, 0);
        return;
    }
    else if (vencedor == boot)
    {
        cout << "\n\n"
             << "O computador venceu!\n\n";

        mostrarTabuleiroAtt(jogo);

        guardarJogador(nomeJogador1, 1, 0, 1, 0);
        return;
    }
    else
    {
        cout << "\n\nEmpate!\n\n";

        mostrarTabuleiroAtt(jogo);

        guardarJogador(nomeJogador1, 1, 0, 0, 1);
        return;
    }
}

int jogadaComputadorInteligente(char jogo[9], char boot, char jogador, int jaJogou)
{

    if (jaJogou == 0)
    {
        int posicaoDesejada;
        if (jogo[4] == ' ')
        {
            posicaoDesejada = 5;
        }

        else if (jogo[0] == ' ')
        {
            posicaoDesejada = 1;
        }
        return posicaoDesejada;
    }

    int vitorias[8][3] = {
                          {0, 1, 2},
                          {3, 4, 5},
                          {6, 7, 8},
                          {0, 3, 6},
                          {1, 4, 7},
                          {2, 5, 8},
                          {0, 4, 8},
                          {2, 4, 6}};

    for (int c = 0; c < 8; c++)
    {

        if (jogo[vitorias[c][0]] == ' ' && (jogo[vitorias[c][1]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == boot)
        {
            return vitorias[c][0] + 1;
        }
        else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == ' ' && jogo[vitorias[c][0]] == boot)
        {
            return vitorias[c][1] + 1;
        }
        else if (jogo[vitorias[c][0]] == (jogo[vitorias[c][1]] && jogo[vitorias[c][2]] == ' ') && jogo[vitorias[c][1]] == boot)
        {
            return vitorias[c][2] + 1;
        }
    }

    for (int c = 0; c < 8; c++)
    {

        if (jogo[vitorias[c][0]] == ' ' && (jogo[vitorias[c][1]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == jogador)
        {
            return vitorias[c][0] + 1;
        }
        else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == ' ' && jogo[vitorias[c][0]] == jogador)
        {
            return vitorias[c][1] + 1;
        }
        else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][1]]) && jogo[vitorias[c][2]] == ' ' && jogo[vitorias[c][1]] == jogador)
        {
            return vitorias[c][2] + 1;
        }
    }

    int posicao;
    do
    {
        posicao = (rand() % 9);
    } while (jogo[posicao] != ' ');
    return posicao + 1;
}

int jogadaComputadorDificil(char jogo[9], char boot, char jogador, int jaJogou)
{

    int possibilidades[4] = {1, 3, 7, 9};
    int posicoes[4] = {2, 4, 6, 8};
    int posicaoDesejada;

    if (jaJogou == 0)
    {
        if (jogo[4] == ' ')
        {
            posicaoDesejada = 5;
        }

        else
        {
            posicaoDesejada = possibilidades[(rand() % 5)];
        }
        return posicaoDesejada;
    }

    else
    {

        int vitorias[8][3] = {
                              {0, 1, 2},
                              {3, 4, 5},
                              {6, 7, 8},
                              {0, 3, 6},
                              {1, 4, 7},
                              {2, 5, 8},
                              {0, 4, 8},
                              {2, 4, 6}};

        for (int c = 0; c < 8; c++) 
        {
            posicaoDesejada = -1;

            if (jogo[vitorias[c][0]] == ' ' && (jogo[vitorias[c][1]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == boot)
            {
                return vitorias[c][0] + 1;
            }
            else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == ' ' && jogo[vitorias[c][0]] == boot)
            {
                return vitorias[c][1] + 1;
            }
            else if (jogo[vitorias[c][0]] == (jogo[vitorias[c][1]] && jogo[vitorias[c][2]] == ' ') && jogo[vitorias[c][1]] == boot)
            {
                return vitorias[c][2] + 1;
            }
        }

        for (int c = 0; c < 8; c++) 
        {

            if (jogo[vitorias[c][0]] == ' ' && (jogo[vitorias[c][1]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == jogador)
            {
                return vitorias[c][0] + 1;
            }
            else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][2]]) && jogo[vitorias[c][1]] == ' ' && jogo[vitorias[c][0]] == jogador)
            {
                return vitorias[c][1] + 1;
            }
            else if ((jogo[vitorias[c][0]] == jogo[vitorias[c][1]]) && jogo[vitorias[c][2]] == ' ' && jogo[vitorias[c][1]] == jogador)
            {
                return vitorias[c][2] + 1;
            }
        }

        if (jogo[0] == jogador && jogo[8] == jogador && jogo[4] == boot)
        {
            posicaoDesejada = posicoes[(rand() % 5)];
        }
        else if (jogo[2] == jogador && jogo[6] == jogador && jogo[4] == boot)
        {
            posicaoDesejada = posicoes[(rand() % 5)];
        }
        else if (jogo[4] == jogador && jogo[8] == jogador && jogo[0] == boot)
        {
            int pontas[2] = {2, 6};
            posicaoDesejada = pontas[(rand() % 3)];
        }
        else if (jogo[4] == jogador && jogo[6] == jogador && jogo[2] == boot)
        {
            int pontas[2] = {0, 8};
            posicaoDesejada = pontas[(rand() % 3)];
        }
        else if (jogo[0] == jogador && jogo[4] == jogador && jogo[8] == boot)
        {
            int pontas[2] = {2, 6};
            posicaoDesejada = pontas[(rand() % 3)];
        }
        else if (jogo[2] == jogador && jogo[4] == jogador && jogo[6] == boot)
        {
            int pontas[2] = {0, 8};
            posicaoDesejada = pontas[(rand() % 3)];
        }

        if (jogo[posicaoDesejada] != ' ' || posicaoDesejada == -1)
        {
            do
            {
                posicaoDesejada = (rand() % 9);
            } while (jogo[posicaoDesejada] != ' ');
        }

        return posicaoDesejada + 1;
    }
}

int main()
{

    char mostrarJogo[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    int linha, coluna, nivelBoot, escolha, jaJogou, finalJogo, opcao, bloqueadas = 0, empate = 0, posicao = 0;
    char jogador1 = 'X';
    char jogador2 = 'O';
    char jogadorAtual = ' ';
    char vencedor = ' ';
    string nomeJogador1 = "";
    string nomeJogador2 = "";
    string nomeJogador = "";
    char boot = 'O';
    srand(time(0));
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

        do
        {
            cout << "=========BEM VINDO AO JOGO DO GALO=========\n\n";
            cout << "Escolha entre as opcoes: \n";
            cout << "1 - Jogador vs Jogador\n";
            cout << "2 - Jogador vs Computador\n";
            cout << "3 - Estatisticas\n";
            cout << "4 - Sair" << endl;
            cin >> opcao;

            if (opcao == 1)
            {

                char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                vencedor = ' ';

                cout << "Insira o nome do primeiro jogador: ";
                getline(cin >> ws, nomeJogador1);

                cout << "Insira o nome do segundo jogador: ";
                getline(cin >> ws, nomeJogador2);

                cout << nomeJogador1 << " sera '" << jogador1 << "' e " << nomeJogador2 << " sera '" << jogador2 << "'\n\n";
                cout << "Aqui esta o jogo da velha:\n";
                mostrarTabuleiro(mostrarJogo);
                cout << "\n\n";

                empate = 0;

                for (int i = 0; i < 9; i++)
                {
                    do
                    {
                        if (i % 2 == 0)
                        {
                            jogadorAtual = jogador1;
                            cout << "\n\n"
                                 << nomeJogador1 << ", ";
                        }
                        else
                        {
                            jogadorAtual = jogador2;
                            cout << "\n\n"
                                 << nomeJogador2 << ", ";
                        }

                        cout << "escolha uma posicao do jogo da velha: ";
                        cin >> posicao;

                        verificarPosicao(jogo, posicao);

                    } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] != ' ');

                    *(jogo + (posicao - 1)) = jogadorAtual;

                    cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n\n";
                    mostrarTabuleiroAtt(jogo);
                    cout << "\n\nPosicoes: \n\n";
                    mostrarTabuleiro(mostrarJogo);

                    vitoriasEmpates(jogo, vitorias, vencedor, bloqueadas, empate);

                    if (vencedor != ' ' || empate == 1)
                    {
                        break;
                    }
                }

                verificarVitoriaJogadores(vencedor, jogador1, jogador2, nomeJogador1, nomeJogador2, jogo);
                break;
            }

            else if (opcao == 2)
            {
                do
                {
                    cout << "Voce escolheu a opcao de jogar contra o computador\nVoce pode escolher entre dois niveis\n1 - Facil\n2 - Normal\n3 - Dificil\nEscolha um: ";
                    cin >> nivelBoot;
                    if (nivelBoot == 1)
                    {
                        cout << "Bem-vindo ao nivel facil!\n";
                        char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                        vencedor = ' ';

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << "O jogador sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(mostrarJogo);

                        empate = 0;

                        for (int i = 0; i < 9; i++)
                        {
                            do
                            {
                                if (i % 2 == 0)
                                {
                                    jogadorAtual = jogador1;
                                    cout << "\n\n"
                                         << nomeJogador1 << ", escolha uma posicao do jogo da velha: ";
                                    cin >> posicao;
                                }
                                else
                                {
                                    do
                                    {
                                        cout << "\n\nJogada do computador: \n";
                                        jogadorAtual = boot;
                                        posicao = (rand() % 9 + 1);
                                        if (jogo[posicao - 1] != ' ') 
                                        {
                                            cout << "\nO computador escolheu uma posicao ocupada!\n";
                                        }
                                    } while (jogo[posicao - 1] != ' ');
                                }

                                verificarPosicao(jogo, posicao);

                            } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] != ' ');

                            *(jogo + (posicao - 1)) = jogadorAtual;

                            cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n\n";
                            mostrarTabuleiroAtt(jogo);
                            cout << "\n\nPosicoes: \n\n";
                            mostrarTabuleiro(mostrarJogo);

                            vitoriasEmpates(jogo, vitorias, vencedor, bloqueadas, empate);

                            if (vencedor != ' ' || empate == 1)
                            {
                                break;
                            }
                        }

                        verificarVitoriasBoot(vencedor, jogador1, boot, nomeJogador1, jogo);
                        break;
                    }
                    else if (nivelBoot == 2)
                    {
                        cout << "Bem-vindo ao nivel normal!\n";

                        char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                        vencedor = ' ';

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << nomeJogador1 << " sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(mostrarJogo);
                        empate = 0;
                        jaJogou = 0;

                        for (int i = 0; i < 9; i++)
                        {
                            do
                            {
                                if (i % 2 == 0)
                                {
                                    jogadorAtual = jogador1;
                                    cout << "\n\n"
                                         << nomeJogador1 << ", escolha uma posicao do jogo da velha: ";
                                    cin >> posicao;
                                }
                                else
                                {
                                    cout << "\n\nJogada do computador... \n";
                                    jogadorAtual = boot;

                                    posicao = jogadaComputadorInteligente(jogo, boot, jogador1, jaJogou);
                                    jaJogou = 1;
                                }

                                verificarPosicaoPc(jogo, posicao);

                            } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] != ' ');

                            *(jogo + (posicao - 1)) = jogadorAtual;

                            cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n\n";
                            mostrarTabuleiroAtt(jogo);
                            cout << "\n\nPosicoes: \n\n";
                            mostrarTabuleiro(mostrarJogo);

                            vitoriasEmpates(jogo, vitorias, vencedor, bloqueadas, empate);

                            if (vencedor != ' ' || empate == 1)
                            {
                                break;
                            }
                        }

                        verificarVitoriasBoot(vencedor, jogador1, boot, nomeJogador1, jogo);
                        break;
                    }
                    else if (nivelBoot == 3) 
                    {
                        cout << "Bem-vindo ao nivel dificil!\n";

                        char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                        vencedor = ' ';

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << nomeJogador1 << " sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(mostrarJogo);

                        empate = 0;
                        jaJogou = 0;

                        for (int i = 0; i < 9; i++)
                        {
                            do
                            {
                                if (i % 2 == 0)
                                {
                                    jogadorAtual = jogador1;
                                    cout << "\n\n"
                                         << nomeJogador1 << ", escolha uma posicao do jogo da velha: ";
                                    cin >> posicao;
                                }
                                else
                                {
                                    cout << "\n\nJogada do computador... \n";
                                    jogadorAtual = boot;

                                    posicao = jogadaComputadorDificil(jogo, boot, jogador1, jaJogou);
                                    jaJogou = 1;
                                }

                                verificarPosicaoPc(jogo, posicao);

                            } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] != ' ');

                            *(jogo + (posicao - 1)) = jogadorAtual;

                            cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n\n";
                            mostrarTabuleiroAtt(jogo);
                            cout << "\n\nPosicoes: \n\n";
                            mostrarTabuleiro(mostrarJogo);

                            vitoriasEmpates(jogo, vitorias, vencedor, bloqueadas, empate);

                            if (vencedor != ' ' || empate == 1)
                            {
                                break;
                            }
                        }

                        verificarVitoriasBoot(vencedor, jogador1, boot, nomeJogador1, jogo);
                        break;
                    }
                } while (nivelBoot < 1 || nivelBoot > 3);
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
                    break;
                }
                else
                {
                    mostrarJogador(ficheiro, nomeJogador, numPartidas,
                                   vitorias, derrotas, empates);
                }
            }
            else if(opcao == 4)
            {
                break;
            }
        } while (opcao < 1 || opcao > 4);

        cout << "\n\nDeseja sair do jogo?\n1 - Sim\n2 - Nao\n";
        cin >> finalJogo;
    } while (finalJogo == 2);

    cout << "\n\nObrigada por jogar conosco!\n\n";
    cout << "Copyrights © 2026 - Camila, Betania, Sarah";

    return 0;
}