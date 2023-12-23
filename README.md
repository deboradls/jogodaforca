# Jogo da Forca
Este repositório contém a implementação de um jogo simples de Forca desenvolvido em linguagem C.

## Funcionamento
O jogo da Forca é um clássico jogo de palavras em que o jogador tenta adivinhar uma palavra, letra por letra, antes de esgotar o número máximo de tentativas permitidas.

### Passos do Jogo:
1. **Abertura**: Ao iniciar o jogo, o programa exibe uma abertura com o título "Jogo de Forca".
2. **Escolha da Dificuldade**: O jogador tem a opção de escolher a dificuldade do jogo (Fácil, Médio ou Difícil).
3. **Seleção da Palavra**: Uma palavra é selecionada aleatoriamente a partir de um arquivo de palavras fornecido (`palavras.txt`).
4. **Adivinhação da Palavra**: O jogador tem um número limitado de tentativas para adivinhar a palavra.
5. **Chutes e Verificação**: A cada chute, o jogador pode inserir uma letra como palpite. Se o palpite corresponder a uma letra da palavra secreta, a letra será revelada na sua posição correspondente na palavra. Caso contrário, o número de tentativas incorretas será contabilizado e uma parte do boneco da forca será desenhada.
6. **Fim do Jogo**: O jogo continua até que o jogador adivinhe a palavra corretamente ou até que as tentativas se esgotem.
