README
Space Shooter em C 🚀
Um jogo simples desenvolvido em C, onde o jogador controla uma nave e deve derrotar os inimigos, desviando dos tiros inimigos e sobrevivendo pelo maior tempo possível.

📋 Descrição
O jogo é composto por uma matriz onde:
O jogador se move horizontalmente e pode atirar nos inimigos.
Inimigos são distribuídos em posições específicas e atiram com uma certa frequência e chance aleatória.
O jogador deve evitar os tiros inimigos e tentar destruir o máximo de inimigos possível para ganhar pontos.

🎮 Funcionalidades
Movimentação: Controla a nave usando as teclas A e D para mover-se para esquerda e direita.
Disparo: Pressione a barra de espaço (SPACE) para atirar nos inimigos.
Tiros Inimigos: Os inimigos atiram periodicamente, e o jogador perde vida se for atingido.
Pontuação: Cada inimigo derrotado soma 1 ponto à pontuação do jogador.
Sistema de vidas: O jogador começa com 3 vidas. Ao perder todas, o jogo termina com um Game Over.

🛠️ Estrutura do Código
SpaceShooter.c: Contém a lógica principal do jogo.
struct Estado: Armazena a posição do jogador, inimigos, tiros e status do jogo.
Movimentação e Tiro:
Função moverTiro: Move o tiro do jogador e verifica colisões.
Função atirarInimigos: Controla a chance de cada inimigo disparar.
Função verificarColisao: Checa colisões entre tiros e jogadores.
Thread: Usa uma thread para controlar o movimento do tiro do jogador em tempo real.

💾 Requisitos para Compilação
Sistema operacional: Windows (necessário por conta da biblioteca windows.h)
Compilador: GCC ou MinGW para compilar código em C.
Biblioteca conio.h: Para entrada de teclado não-bloqueante.
Como Compilar e Executar
Instale o MinGW (caso ainda não tenha):
Guia de instalação do MinGW
Clone o repositório:
bash
Copiar código
git clone https://github.com/seu_usuario/seu_repositorio.git
cd seu_repositorio
Compile o projeto:
bash
Copiar código
gcc main.c -o space_shooter.exe -lpthread
Execute o jogo:
bash
Copiar código
./space_shooter.exe

📦 Estrutura do Projeto
bash
Copiar código
/seu_repositorio
│
├── main.c           # Código principal do jogo
└── README.md        # Este arquivo de documentação

📋 Controles
A: Move a nave para a esquerda
D: Move a nave para a direita
SPACE: Dispara um tiro
Q: Sai do jogo

🛡️ Regras
O jogador possui 3 vidas. Ao perder todas, o jogo acaba com Game Over.
Cada inimigo destruído adiciona 1 ponto à pontuação.
Inimigos atiram de forma aleatória com 20% de chance a cada ciclo.
O jogador deve evitar ser atingido pelos tiros inimigos para sobreviver.

🐞 Possíveis Melhorias
Adicionar níveis de dificuldade progressivos.
Implementar movimentação vertical para os inimigos.
Adicionar efeitos sonoros e melhorias visuais.
Incluir um menu inicial e opção de reinício.

Feito com ❤️ por Bruno Budano RA: 221240062, Daniel Clemente RA 221240781 e Gabriel Andrade RA: 221240757.
