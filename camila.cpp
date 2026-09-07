#include <iostream>

int main(){

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
        }

        return 0;
}