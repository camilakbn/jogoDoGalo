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

// add um timer ou uma matriz ao lado da matriz ou uma matriz so no inicio
// parar o empate antes da ultima jogada
// bot ficou com posicao ocupada e nao repetiu, consertar isso
// tentar adicionar uma linha do ganhador
// ajeitar pra o X sempre começar primeiro

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

void jogadaComputadorInteligente(char jogo[3][3], char pcInteligente, char jogador)
{
    int jaJogou = 0;

    if (jaJogou == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (jogo[i][j] == ' ')
                {
                    jogo[i][j] = pcInteligente;
                    if ((jogo[i][0] == pcInteligente && jogo[i][1] == pcInteligente && jogo[i][2] == pcInteligente) ||
                        (jogo[0][j] == pcInteligente && jogo[1][j] == pcInteligente && jogo[2][j] == pcInteligente) ||
                        (jogo[0][0] == pcInteligente && jogo[1][1] == pcInteligente && jogo[2][2] == pcInteligente) ||
                        (jogo[0][2] == pcInteligente && jogo[1][1] == pcInteligente && jogo[2][0] == pcInteligente))
                    {
                        jaJogou = 1;
                        break;
                    }
                    jogo[i][j] = ' ';
                }
            }
            if (jaJogou == 1)
                break;
        }
    }

    if (jaJogou == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (jogo[i][j] == ' ')
                {
                    jogo[i][j] = jogador;
                    if ((jogo[i][0] == jogador && jogo[i][1] == jogador && jogo[i][2] == jogador) ||
                        (jogo[0][j] == jogador && jogo[1][j] == jogador && jogo[2][j] == jogador) ||
                        (jogo[0][0] == jogador && jogo[1][1] == jogador && jogo[2][2] == jogador) ||
                        (jogo[0][2] == jogador && jogo[1][1] == jogador && jogo[2][0] == jogador))
                    {
                        jogo[i][j] = pcInteligente;
                        jaJogou = 1;
                        break;
                    }
                    jogo[i][j] = ' ';
                }
            }
            if (jaJogou == 1)
            {
                break;
            }
        }
    }

    if (jaJogou == 0 && jogo[1][1] == ' ')
    {
        jogo[1][1] = pcInteligente;
        jaJogou = 1;
    }

    if (jaJogou == 0 && jogo[0][0] == ' ')
    {
        jogo[0][0] = pcInteligente;
        jaJogou = 1;
    }
    if (jaJogou == 0 && jogo[0][2] == ' ')
    {
        jogo[0][2] = pcInteligente;
        jaJogou = 1;
    }
    if (jaJogou == 0 && jogo[2][0] == ' ')
    {
        jogo[2][0] = pcInteligente;
        jaJogou = 1;
    }
    if (jaJogou == 0 && jogo[2][2] == ' ')
    {
        jogo[2][2] = pcInteligente;
        jaJogou = 1;
    }

    if (jaJogou == 0)
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (jogo[i][j] == ' ')
                {
                    jogo[i][j] = pcInteligente;
                    jaJogou = 1;
                    break;
                }
            }
            if (jaJogou == 1)
            {
                break;
            }
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
    int escolha;
    int finalJogo;
    int opcao;
    char posicao;
    int nivelBoot;
    char pcInteligente = 'O';
    char boot = 'O';
    srand(time(0));

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

                char jogo[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

                cout << "Insira o nome do primeiro jogador: ";
                getline(cin >> ws, nomeJogador1);

                cout << "Insira o nome do segundo jogador: ";
                getline(cin >> ws, nomeJogador2);

                /*do
                {
                    //CONSERTAR ISSO E O JOGADOR INTELIGENTE
                    cout << nomeJogador1 << ", voce quer ser 'X ou 'O'?\nDigite: 1 - 'X'\n2 - 'O'";
                    cin >> escolha;
                    if (escolha == 1)
                    {
                        jogador1 = 'X';
                        jogador2 = 'O';
                    }
                    else
                    {
                        jogador1 = 'O';
                        jogador2 = 'X';
                    }
                } while (escolha < 1 || escolha > 2);*/

                cout << nomeJogador1 << " sera " << jogador1 << " e " << nomeJogador2 << " sera " << jogador2 << "\n\n";
                cout << "Aqui esta o jogo da velha:\n";
                mostrarTabuleiro(jogo);

                for (int jogada = 0; jogada < 9; jogada++)
                {

                    if (jogada % 2 == 0)
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

                    cout << "qual a posicao que deseja realizar a jogada? ";
                    cout << "Escolha a linha (entre 1 e 3): ";
                    cin >> linha;
                    cout << "Escolha a coluna (entre 1 e 3): ";
                    cin >> coluna;

                    // 1 funcao
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
                    }
                    // ate aqui

                    *(*(jogo + (linha - 1)) + (coluna - 1)) = jogadorAtual;

                    cout << "\n";
                    mostrarTabuleiro(jogo);

                    // 1 funcao vencedor
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
                            cout << "\n\n"
                                 << nomeJogador1 << " venceu!\n\n";

                            mostrarTabuleiro(jogo);

                            guardarJogador(nomeJogador1, 1, 1, 0, 0);
                            guardarJogador(nomeJogador2, 1, 0, 1, 0);
                            break;
                        }
                        else if (jogadorAtual == jogador2)
                        {
                            cout << "\n\n"
                                 << nomeJogador2 << " venceu!\n\n";

                            mostrarTabuleiro(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 1, 0);
                            guardarJogador(nomeJogador2, 1, 1, 0, 0);
                            break;
                        }
                    }
                    // ate aqui

                    // 1 funcao empate
                    if (jogada == 8)
                    {

                        cout << "\n\nEmpate!\n\n";

                        mostrarTabuleiro(jogo);

                        guardarJogador(nomeJogador1, 1, 0, 0, 1);
                        guardarJogador(nomeJogador2, 1, 0, 0, 1);
                        break;
                    }
                    // ate aqui
                }
            }
            else if (opcao == 2)
            {
                do
                {
                    cout << "Voce escolheu a opcao de jogar contra o computador\nVoce pode escolher entre dois niveis\n1 - Facil\n2 - Normal\nEscolha um: ";
                    cin >> nivelBoot;
                    if (nivelBoot == 1)
                    {
                        cout << "Bem-vindo ao nivel facil!\n";

                        // add codigo

                        char jogo[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << "O jogador sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(jogo);

                        // add codigo
                        for (int jogada = 0; jogada < 9; jogada++)
                        {

                            if (jogada % 2 == 0)
                            {
                                jogadorAtual = jogador1;
                                cout << "\n\n"
                                     << nomeJogador1 << ", qual a posicao que deseja realizar a jogada? ";
                                cout << "Escolha a linha (entre 1 e 3): ";
                                cin >> linha;
                                cout << "Escolha a coluna (entre 1 e 3): ";
                                cin >> coluna;
                            }

                            else
                            {
                                cout << "\n\nJogada do computador: \n";
                                jogadorAtual = boot;
                                cout << "\n\nBoot (O):";
                                linha = (rand() % 3 + 1);
                                coluna = (rand() % 3 + 1);
                            }

                            // 1 funcao
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
                            }
                            // ate aqui

                            *(*(jogo + (linha - 1)) + (coluna - 1)) = jogadorAtual;

                            cout << "\n";
                            mostrarTabuleiro(jogo);

                            // 1 funcao vencedor
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

                                    mostrarTabuleiro(jogo);

                                    guardarJogador(nomeJogador1, 1, 1, 0, 0);
                                    break;
                                }
                                else if (jogadorAtual == boot)
                                {
                                    cout << "\nO computador venceu!\n";

                                    mostrarTabuleiro(jogo);

                                    guardarJogador(nomeJogador1, 1, 0, 1, 0);
                                    break;
                                }
                            }
                            // ate aqui

                            // 1 funcao empate
                            if (jogada == 8)
                            {

                                cout << "\n\nEmpate!\n";

                                mostrarTabuleiro(jogo);

                                guardarJogador(nomeJogador1, 1, 0, 0, 1);
                                break;
                            }
                            // ate aqui
                        }
                    }
                    else if (nivelBoot == 2)
                    {
                        cout << "Bem-vindo ao nivel normal!\n";

                        char jogo[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << "O jogador sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(jogo);

                        for (int jogada = 0; jogada < 9; jogada++)
                        {

                            if (jogada % 2 == 0)
                            {
                                jogadorAtual = jogador1;
                                cout << "\n\n"
                                     << nomeJogador1 << ", qual a posicao que deseja realizar a jogada? ";
                                cout << "Escolha a linha (entre 1 e 3): ";
                                cin >> linha;
                                cout << "Escolha a coluna (entre 1 e 3): ";
                                cin >> coluna;

                                // 1 funcao
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
                                }
                                // ate aqui

                                *(*(jogo + (linha - 1)) + (coluna - 1)) = jogadorAtual;
                            }

                            else
                            {
                                cout << "\n\nJogada do computador: \n";
                                jogadorAtual = pcInteligente;
                                jogadaComputadorInteligente(jogo, pcInteligente, jogador1);
                            }

                            cout << "\n";
                            mostrarTabuleiro(jogo);

                            // 1 funcao vencedor
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

                                    mostrarTabuleiro(jogo);

                                    guardarJogador(nomeJogador1, 1, 1, 0, 0);
                                    break;
                                }
                                else if (jogadorAtual == pcInteligente)
                                {
                                    cout << "\nO computador venceu!\n";

                                    mostrarTabuleiro(jogo);

                                    guardarJogador(nomeJogador1, 1, 0, 1, 0);
                                    break;
                                }
                            }
                            // ate aqui

                            // 1 funcao empate
                            if (jogada == 8)
                            {

                                cout << "\n\nEmpate!\n";

                                mostrarTabuleiro(jogo);

                                guardarJogador(nomeJogador1, 1, 0, 0, 1);
                                break;
                            }
                            // ate aqui
                        }
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
                    break;
                }
                else
                {
                    mostrarJogador(ficheiro, nomeJogador, numPartidas,
                                   vitorias, derrotas, empates);
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