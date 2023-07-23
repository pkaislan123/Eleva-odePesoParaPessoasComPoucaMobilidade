/*
 * Código: Controle de Motor com Fim de Curso e Parada de Emergência
 * Autor: Aislan Silva Costa
 * Data: 22/07/2023
 * 
 * Whatsapp: (38) 9 9941-6698
 * E-mail: comprasaislan@gmail.com
 * Site: https://titaniwm.netlify.app/
 * 
 * Resumo:
 * O código implementa o controle de um motor usando um Arduino Nano e um driver L293D, 
 * juntamente com três botões (SUBIR, DESCER e PARADA) 
 * e duas chaves fim de curso (CIMA e BAIXO). 
 * 
 * O objetivo do código é permitir que o motor se mova nos sentidos de subida e descida apenas se as condições corretas forem atendidas, 
 * ou seja, o botão correspondente estiver pressionado e a chave fim de curso oposta estiver em estado HIGH. 
 * Além disso, o motor é interrompido imediatamente se o botão de parada for acionado ou quando atingir uma das chaves fim de curso. 
 * O status do sistema é exibido no monitor serial para fins de depuração e simulação. 
 * O código também incorpora uma função de segurança que desliga o motor caso ocorra uma mudança inesperada no estado das chaves fim de curso durante o movimento.
 * 
 * 
 * 
 */




// Definição dos pinos dos botões e chaves fim de curso
const int botaoSubirPin = 2;
const int botaoDescerPin = 3;
const int botaoParadaPin = 4;
const int chaveCimaPin = 5;
const int chaveBaixoPin = 6;

// Definição dos pinos do driver L293D
const int motorENA = 9;
const int motorIN1 = 10;
const int motorIN2 = 11;

// Variável para guardar o estado anterior das chaves fim de curso
bool chaveCimaAnterior = HIGH;
bool chaveBaixoAnterior = HIGH;

// Variável para guardar o estado atual do motor
bool motorLigado = false;

int intervaloObstrucaoFimCurso = 5000;

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
  pinMode(botaoSubirPin, INPUT_PULLUP);
  pinMode(botaoDescerPin, INPUT_PULLUP);
  pinMode(botaoParadaPin, INPUT_PULLUP);
  pinMode(chaveCimaPin, INPUT_PULLUP);
  pinMode(chaveBaixoPin, INPUT_PULLUP);

  pinMode(motorENA, OUTPUT);
  pinMode(motorIN1, OUTPUT);
  pinMode(motorIN2, OUTPUT);

  // Desliga o motor no início
  desligarMotor();
}

void loop() {
  // Verifica se o botão SUBIR foi pressionado e se a chave fim de curso CIMA está aberta (estado HIGH)
  if (digitalRead(botaoSubirPin) == LOW) {
    if ( digitalRead(chaveCimaPin) == HIGH) {
      Serial.println("SUBIR acionado - Movendo para CIMA");
      ligarMotorSentidoCima();
      delay(intervaloObstrucaoFimCurso);
    }
  }

  // Verifica se o botão DESCER foi pressionado e se a chave fim de curso BAIXO está aberta (estado HIGH)
  if (digitalRead(botaoDescerPin) == LOW) {
    if ( digitalRead(chaveBaixoPin) == HIGH) {
      Serial.println("DESCER acionado - Movendo para BAIXO");
      ligarMotorSentidoBaixo();
      delay(intervaloObstrucaoFimCurso);
    }
  }

  // Verifica se o botão PARADA foi pressionado para desligar o motor
  if (digitalRead(botaoParadaPin) == LOW && motorLigado) {
    desligarMotor();
    Serial.println("PARADA acionado - Motor interrompido");
  }

  // Verifica se a chave fim de curso CIMA mudou de estado para desligar o motor (caso ele esteja se movendo para cima)
  if (digitalRead(chaveCimaPin) != chaveCimaAnterior && motorLigado) {
    desligarMotor();
    Serial.println("Chave CIMA acionada - Motor interrompido");
  }

  // Verifica se a chave fim de curso BAIXO mudou de estado para desligar o motor (caso ele esteja se movendo para baixo)
  if (digitalRead(chaveBaixoPin) != chaveBaixoAnterior && motorLigado) {
    desligarMotor();
    Serial.println("Chave BAIXO acionada - Motor interrompido");
  }

  // Atualiza o estado anterior das chaves fim de curso
  chaveCimaAnterior = digitalRead(chaveCimaPin);
  chaveBaixoAnterior = digitalRead(chaveBaixoPin);

  delay(200); // Pequeno delay para evitar a leitura errática dos botões
}

// Função para ligar o motor no sentido de subida
void ligarMotorSentidoCima() {
  digitalWrite(motorIN1, HIGH);
  digitalWrite(motorIN2, LOW);
  analogWrite(motorENA, 255); // Velocidade máxima, caso seu motor seja controlado por PWM
  motorLigado = true;
}

// Função para ligar o motor no sentido de descida
void ligarMotorSentidoBaixo() {
  digitalWrite(motorIN1, LOW);
  digitalWrite(motorIN2, HIGH);
  analogWrite(motorENA, 255); // Velocidade máxima, caso seu motor seja controlado por PWM
  motorLigado = true;
}

// Função para desligar o motor
void desligarMotor() {
  digitalWrite(motorIN1, LOW);
  digitalWrite(motorIN2, LOW);
  analogWrite(motorENA, 0);
  motorLigado = false;
}
