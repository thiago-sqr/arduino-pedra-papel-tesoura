// Definição dos pinos dos botões
const int botaoPedra1 = 2;
const int botaoPapel1 = 3;
const int botaoTesoura1 = 4;

const int botaoPedra2 = 5;
const int botaoPapel2 = 6;
const int botaoTesoura2 = 7;

// Definição dos pinos dos LEDs
const int ledJogador1 = 8;
const int ledJogador2 = 9;

// Variáveis para armazenar as jogadas
int jogada1 = -1;
int jogada2 = -1;

void setup() {
  // Configura os botões como entrada com pullup interno
  pinMode(botaoPedra1, INPUT_PULLUP);
  pinMode(botaoPapel1, INPUT_PULLUP);
  pinMode(botaoTesoura1, INPUT_PULLUP);

  pinMode(botaoPedra2, INPUT_PULLUP);
  pinMode(botaoPapel2, INPUT_PULLUP);
  pinMode(botaoTesoura2, INPUT_PULLUP);

  // Configura os LEDs como saída
  pinMode(ledJogador1, OUTPUT);
  pinMode(ledJogador2, OUTPUT);

  // Inicializa os LEDs desligados
  digitalWrite(ledJogador1, LOW);
  digitalWrite(ledJogador2, LOW);
}

void loop() {
  // Leitura das jogadas
  jogada1 = lerJogada(botaoPedra1, botaoPapel1, botaoTesoura1);
  jogada2 = lerJogada(botaoPedra2, botaoPapel2, botaoTesoura2);

  // Só verifica o resultado se ambos os jogadores tiverem feito uma jogada
  if (jogada1 != -1 && jogada2 != -1) {
    int resultado = verificarResultado(jogada1, jogada2);
    mostrarResultado(resultado);
    delay(1000); // Aguarda 2 segundos antes de reiniciar
    resetarJogo(); // Reseta as jogadas para a próxima rodada
  }
}

int lerJogada(int pedraPin, int papelPin, int tesouraPin) {
  if (digitalRead(pedraPin) == HIGH) return 0;  // Pedra
  if (digitalRead(papelPin) == HIGH) return 1;  // Papel
  if (digitalRead(tesouraPin) == HIGH) return 2; // Tesoura
  return -1;  // Nenhuma jogada
}

int verificarResultado(int jogada1, int jogada2) {
  // Se for empate
  if (jogada1 == jogada2) return 0;
  
  // Verifica se o jogador 1 venceu
  if ((jogada1 == 0 && jogada2 == 2) ||  // Pedra vence Tesoura
      (jogada1 == 1 && jogada2 == 0) ||  // Papel vence Pedra
      (jogada1 == 2 && jogada2 == 1)) {  // Tesoura vence Papel
    return 1;
  }
  
  // Caso contrário, jogador 2 venceu
  return 2;
}

void mostrarResultado(int resultado) {
  // Desliga ambos os LEDs primeiro
  digitalWrite(ledJogador1, LOW);
  digitalWrite(ledJogador2, LOW);

  // Jogador 1 venceu
  if (resultado == 1) {
    digitalWrite(ledJogador1, HIGH);
  }
  // Jogador 2 venceu
  else if (resultado == 2) {
    digitalWrite(ledJogador2, HIGH);
  }
}

void resetarJogo() {
  jogada1 = -1;
  jogada2 = -1;
  digitalWrite(ledJogador1, LOW);
  digitalWrite(ledJogador2, LOW);
}