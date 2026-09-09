#include <iostream>
using namespace std;
#include <cstdlib>
#include <ctime>

int main()
{

    // tabuleiro
    char matriz[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int linha;
    int coluna;
    char jogador1 = 'X';
    char pcInteligente = 'O';
    char jogadorAtual;
    srand(time(0));

    cout << "\n\n";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            cout << " " << *(*(matriz + i) + j) << " ";
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

    // jogada

    for (int jogada = 0; jogada < 9; jogada++)
    { // limita o numero de jogada

        if (jogada % 2 == 0)
        {

            jogadorAtual = jogador1;

            cout << "\n\nJogador 1 (X):";
            cout << "\n\nQual a posicao que deseja realizar a jogada?\n";
            cout << "\nLinha (entre 1 e 3): \n";
            cin >> linha;
            cout << "\nColuna (entre 1 e 3): \n";
            cin >> coluna;
        }

        else
        {

            jogadorAtual = pcInteligente;
            cout << "\n\nBoot (O):";
            linha = (rand() % 3 + 1);
            coluna = (rand() % 3 + 1);
        }

        // verificar jogada
        while (linha < 1 || linha > 3 || coluna < 1 || coluna > 3 || *(*(matriz + (linha - 1)) + (coluna - 1)) != ' ')
        {

            if (linha < 1 || linha > 3 || coluna < 1 || coluna > 3)
            {

                cout << "\n\nPosicao invalida";
            }

            else if (*(*(matriz + (linha - 1)) + (coluna - 1)) != ' ')
            {
                cout << "\n\nPosicao ocupada!";
            }

            
            if (jogada % 2 == 0)
            {

                jogadorAtual = jogador1;

                cout << "\n\nJogador 1 (X):";
                cout << "\n\nQual a posicao que deseja realizar a jogada?\n";
                cout << "\nLinha (entre 1 e 3): \n";
                cin >> linha;
                cout << "\nColuna (entre 1 e 3): \n";
                cin >> coluna;
            }

            else
            {

                jogadorAtual = pcInteligente;
                cout << "\n\nBoot (O):";
                linha = (rand() % 3 + 1);
                coluna = (rand() % 3 + 1);
            }

            
        }

        *(*(matriz + (linha - 1)) + (coluna - 1)) = jogadorAtual;

        // verificar vencedor/ empate

        if (

            // linha
            (matriz[0][0] == jogadorAtual && matriz[0][1] == jogadorAtual && matriz[0][2] == jogadorAtual) ||
            (matriz[1][0] == jogadorAtual && matriz[1][1] == jogadorAtual && matriz[1][2] == jogadorAtual) ||
            (matriz[2][0] == jogadorAtual && matriz[2][1] == jogadorAtual && matriz[2][2] == jogadorAtual) ||

            // coluna
            (matriz[0][0] == jogadorAtual && matriz[1][0] == jogadorAtual && matriz[2][0] == jogadorAtual) ||
            (matriz[0][1] == jogadorAtual && matriz[1][1] == jogadorAtual && matriz[2][1] == jogadorAtual) ||
            (matriz[0][2] == jogadorAtual && matriz[1][2] == jogadorAtual && matriz[2][2] == jogadorAtual) ||

            // diagona principal e secundária
            (matriz[0][0] == jogadorAtual && matriz[1][1] == jogadorAtual && matriz[2][2] == jogadorAtual) ||
            (matriz[0][2] == jogadorAtual && matriz[1][1] == jogadorAtual && matriz[2][0] == jogadorAtual))
        {
            cout << "\nO jogador " << jogadorAtual << " venceu!!\n";
            break;
        }
        // empate
        if (jogada == 8)
        {

            cout << "Empate!";
            break;
        }

        // tabuleiro

        cout << "\n\n";

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {

                cout << " " << *(*(matriz + i) + j) << " ";
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

    return 0;
}