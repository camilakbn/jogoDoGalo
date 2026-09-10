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
// bot ficou com posicao ocpuada e nao repetiu, consertar isso
// tentar adicionar uma linha do ganhador
// ajeitar pra o X sempre começar primeiro

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

// AJEITAR O COMPUTADOR INTELIGENTE
void jogadaComputadorInteligente(char jogo[9], char pcInteligente, char jogador)
{
    int jaJogou = 0;

    int vitorias[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}};

    if (jaJogou == 0)
    {
        for (int i = 0; i < 9; i++)
        {
            if (jogo[i] == ' ')
            {
                jogo[i] = pcInteligente; // para simular a jogada
                for (int c = 0; c < 8; c++)
                {
                    if (jogo[vitorias[c][0]] != ' ' && jogo[vitorias[c][0]] == jogo[vitorias[c][1]] && jogo[vitorias[c][1]] == jogo[vitorias[c][2]])
                    {
                        return;
                    }
                }
                jogo[i] = ' '; // tira a simulação
            }
        }
    }

    if (jaJogou == 0)
    {
        for (int i = 0; i < 9; i++)
        {
            if (jogo[i] == ' ')
            {
                jogo[i] = jogador;
                for (int c = 0; c < 8; c++)
                {
                    if (jogo[vitorias[c][0]] != ' ' && jogo[vitorias[c][0]] == jogo[vitorias[c][1]] && jogo[vitorias[c][1]] == jogo[vitorias[c][2]])
                    {
                        jogo[i] = pcInteligente;
                        return;
                    }
                }
                jogo[i] = ' ';
            }
        }
    }

    if (jaJogou == 0)
    {
        if (jogo[4] == ' ')
        {
            jogo[4] = pcInteligente;
        }

        else if (jogo[0] == ' ')
        {
            jogo[0] = pcInteligente;
        }
        else if (jogo[2] == ' ')
        {
            jogo[2] = pcInteligente;
        }
        else if (jogo[5] == ' ')
        {
            jogo[5] = pcInteligente;
        }
        else if (jogo[8] == ' ')
        {
            jogo[8] = pcInteligente;
        }
        else
        {
            pcInteligente = (rand() % 9 + 1); // ver se isto está certo
        }
    }
}

int main()
{

    char mostrarJogo[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    int linha, coluna;
    char jogador1 = 'X';
    char jogador2 = 'O';
    char jogadorAtual = ' ';
    char vencedor = ' ';
    string nomeJogador1 = "";
    string nomeJogador2 = "";
    string nomeJogador = "";
    int escolha;
    int finalJogo;
    int opcao;
    int posicao = 0;
    int nivelBoot;
    char pcInteligente = 'O';
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
                jogador1 = 'X';
                boot = 'O';

                cout << "Insira o nome do primeiro jogador: ";
                getline(cin >> ws, nomeJogador1);

                cout << "Insira o nome do segundo jogador: ";
                getline(cin >> ws, nomeJogador2);

                /*do
                {
                    //CONSERTAR ISSO
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

                cout << nomeJogador1 << " sera '" << jogador1 << "' e " << nomeJogador2 << " sera '" << jogador2 << "'\n\n";
                cout << "Aqui esta o jogo da velha:\n";
                mostrarTabuleiro(mostrarJogo); // apenas mostra o tabuleiro
                cout << "\n\n";

                for (int i = 0; i < 9; i++) // entro no loop do char jogo[9]
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

                        // validação da jogada
                        if (posicao < 1 || posicao > 9)
                        {
                            cout << "\nPosicao invalida, escolha outra posicao!\n";
                        }

                        else if (jogo[posicao - 1] != ' ')
                        {
                            cout << "\nPosicao ocupada, escolha outra posicao!\n";
                        }

                    } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] != ' ');

                    *(jogo + (posicao - 1)) = jogadorAtual; // salvo a jogada
                    // a jogada só pode ser salva fora do while, pra ele não salvar mais de uma resposta

                    cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n";
                    mostrarTabuleiroAtt(jogo); // mostra o tabuleiro atualizado com o vetor jogo

                    // verificar vencedor
                    for (int j = 0; j < 8; j++)
                    {
                        if (jogo[vitorias[j][0]] != ' ' && jogo[vitorias[j][0]] == jogo[vitorias[j][1]] && jogo[vitorias[j][1]] == jogo[vitorias[j][2]])
                        /*explicação do loop:
                        a primeira parte verifica se o campo está vazio -> jogo[vitorias[j][0]] != ' '
                        a segunda parte depois do primeiro && significa:
                        o que está na posição 0 é igual ao que está na posição 1?
                        e o que está na posição 1 é igual ao que está na posição 2?"
                        se der falso ele pula pra o 1 do loop
                        se der vddeiro significa que as 3 posicoes estão preenchidas
                        com X ou 0*/
                        {
                            vencedor = jogo[vitorias[j][0]];
                            break;
                            // salva o jogador que ganhou e dá break pra ele não fazer o loop todo
                        }
                    } // fim do verificar o vencedor

                    if (vencedor != ' ')
                    {
                        break;
                        // se o vencedor for diferente de vazio, para esse loop
                        // pq no anterior apenas para o outro loop do for c = 8
                        // e esse para o loop do for i = 9
                    }
                } // fim do loop de jogo[9]

                if (vencedor == jogador1)
                {
                    cout << "\n\n"
                         << nomeJogador1 << " venceu!\n\n";

                    mostrarTabuleiroAtt(jogo);

                    guardarJogador(nomeJogador1, 1, 1, 0, 0); // partida, vitoria, derrota, empate
                    guardarJogador(nomeJogador2, 1, 0, 1, 0);
                    break;
                }
                else if (vencedor == jogador2)
                {
                    cout << "\n\n"
                         << nomeJogador2 << " venceu!\n\n";

                    mostrarTabuleiroAtt(jogo);

                    guardarJogador(nomeJogador1, 1, 0, 1, 0);
                    guardarJogador(nomeJogador2, 1, 1, 0, 0);
                    break;
                }
                else
                {
                    // tentar fazer ele parar quando o jogo já der empate
                    cout << "\n\nEmpate!\n\n";

                    mostrarTabuleiroAtt(jogo);

                    guardarJogador(nomeJogador1, 1, 0, 0, 1);
                    guardarJogador(nomeJogador2, 1, 0, 0, 1);
                    break;
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

                        // essa parte é pra limpar as variáveis, pq os valores delas estão salvos da opção 1
                        char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                        vencedor = ' ';
                        jogador1 = 'X';
                        boot = 'O';

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << "O jogador sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(mostrarJogo);

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
                                        cout << "\n\nBoot (O):";
                                        posicao = (rand() % 9 + 1);
                                        /*o modulo de 9 sempre vai ser de 0 a 8
                                        pq mais 1? pq quando usa o ponteiro usa com -1
                                        pq o usuario sempre vai colocar 1 acima (pq o vetor é 0 based)*/
                                        if (jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O')
                                        {
                                            cout << "\nO computador escolheu uma posicao ocupada!\n";
                                        }
                                    } while (jogo[posicao - 1] != ' '); //o boot só sai quando escolher uma opção vazia
                                }

                                if (posicao < 1 || posicao > 9)
                                {
                                    cout << "\nPosicao invalida, escolha outra posicao!\n";
                                }

                                else if (jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O')
                                {
                                    cout << "\nPosicao ocupada, escolha outra posicao!\n";
                                }

                            } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O');

                            *(jogo + (posicao - 1)) = jogadorAtual;

                            cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n";
                            mostrarTabuleiroAtt(jogo);

                            for (int c = 0; c < 8; c++)
                            {
                                if (jogo[vitorias[c][0]] != ' ' && jogo[vitorias[c][0]] == jogo[vitorias[c][1]] && jogo[vitorias[c][1]] == jogo[vitorias[c][2]])
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
                            cout << "\n\n"
                                 << nomeJogador1 << " venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 1, 0, 0);
                            break;
                        }
                        else if (vencedor == boot)
                        {
                            cout << "\n\n"
                                 << "O computador venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 1, 0);
                            break;
                        }
                        else
                        {
                            cout << "\n\nEmpate!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 0, 1);
                            break;
                        }
                    }
                    else if (nivelBoot == 2)
                    {
                        cout << "Bem-vindo ao nivel normal!\n";

                        char jogo[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
                        vencedor = ' ';
                        jogador1 = 'X';
                        boot = 'O';

                        cout << "Insira o nome do jogador: ";
                        getline(cin >> ws, nomeJogador1);

                        cout << "O jogador sera o 'X' e o computador sera o 'O'\n\n";
                        cout << "Aqui esta o jogo da velha:\n";
                        mostrarTabuleiro(mostrarJogo);

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
                                    cout << "\n\nJogada do computador: \n";
                                    jogadorAtual = pcInteligente;
                                    jogadaComputadorInteligente(jogo, pcInteligente, jogador1);
                                }

                                if (posicao < 1 || posicao > 9)
                                {
                                    cout << "\nPosicao invalida, escolha outra posicao!\n";
                                }

                                else if (jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O')
                                {
                                    cout << "\nPosicao ocupada, escolha outra posicao!\n";
                                }

                            } while (posicao < 1 || posicao > 9 || jogo[posicao - 1] == 'X' || jogo[posicao - 1] == 'O');

                            *(jogo + (posicao - 1)) = jogadorAtual;

                            cout << "\n\n\n\n\nAtualizacao do jogo da velha:\n";
                            mostrarTabuleiroAtt(jogo);

                            for (int c = 0; c < 8; c++)
                            {
                                if (jogo[vitorias[c][0]] != ' ' && jogo[vitorias[c][0]] == jogo[vitorias[c][1]] && jogo[vitorias[c][1]] == jogo[vitorias[c][2]])
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
                            cout << "\n\n"
                                 << nomeJogador1 << " venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 1, 0, 0);
                            break;
                        }
                        else if (vencedor == pcInteligente)
                        {
                            cout << "\n\n"
                                 << "O computador venceu!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 1, 0);
                            break;
                        }
                        else
                        {
                            cout << "\n\nEmpate!\n\n";

                            mostrarTabuleiroAtt(jogo);

                            guardarJogador(nomeJogador1, 1, 0, 0, 1);
                            break;
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

        cout << "\n\nDeseja sair do jogo?\n1 - Sim\n2 - Nao\n";
        cin >> finalJogo;
    } while (finalJogo == 2);

    cout << "\n\nObrigada por jogar conosco!\n\n";
    cout << "Copyrights © 2026 - Camila, Betania, Sarah";

    return 0;
}