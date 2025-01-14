/*

----------------------------------------- SCALE SIMULATOR ----------------------------------------

Simulador de balança utilizando ESP32, que envia dados randômicos de peso.
Destinado para teste de dispositivos de leitura de balanças, caso não haja uma balança física.

1) Funcionamento:

- O SCALE SIMULATOR aguarda solicitação do dispositivo externo para iniciar a transmissão de dados. 
- Este protocolo de comunicação utiliza:

  * 1 Stop Bit;
  * 8 Bits de dados;
  * Sem paridade.

- O envio dos dados é iniciado quando o dispositivo externo envia o comando de solicitação “ENQ”.
    ENQ = Caracter ASCII (05H, ou 0x05) enviado pelo dispositivo externo.

- Após receber o comando, o SCALE SIMULATOR enviará o seguinte pacote de dados:
  
    [STX][PPPPP][ETX] 
  
  onde:
  * STX = Caracter ASCII (02H, ou 0x02) – Início da transmissão;
  * PPPPP = 5 caracteres ASCII representando o peso em gramas (sem ponto decimal);
  * ETX = Caracter ASCII (03H, ou 0x03) – Término da transmissão.

2) Conexões:

     ESP32 SCALE SIMULATOR | Dispositivo externo (Outro ESP32)
              RX (16)      |    TX (17)
              TX (17)      |    RX (16)
              GND          |    GND

- IMPORTANTE: Certifique-se de compartilhar o mesmo GND.
- Caso haja uma balança real, deve ser utilizado um módulo RS232 para conversão TTL serial.

--------------------------------------------------------------------------------------------------

*/

#include <Arduino.h>

// Configuração dos pinos da Serial2 para comunicação RS232
#define RXD2 16 // Pino RX2 do ESP32
#define TXD2 17 // Pino TX2 do ESP32

void setup() {
  // Inicializa a comunicação Serial para debug
  Serial.begin(115200);
  
  // Inicializa a comunicação Serial2 para RS232
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  Serial.println("Balança iniciada! Aguardando comando ENQ...");
}

void loop() {
  // Verifica se há dados disponíveis na Serial2
  while (Serial2.available()) {
    // Lê o comando recebido
    char command = Serial2.read();

    // Se o comando for ENQ (0x05), processa a solicitação
    if (command == 0x05) {
      Serial.println("Comando ENQ recebido, enviando peso sem formatação...");

      // Gera um peso aleatório no formato [STX][PPPPP][ETX]
      int randomWeight = random(0, 10000); // Peso entre 0g e 10.000g (0kg a 10kg)
      String simulatedWeight = String(char(0x02)) + String(randomWeight) + String(char(0x03));

      // Envia o pacote pela Serial2
      Serial2.print(simulatedWeight);

      // Exibe o pacote enviado no Serial Monitor para debug
      Serial.println("Peso enviado: " + simulatedWeight);
    }

    // Aguarda brevemente para evitar sobrecarga
    vTaskDelay(pdMS_TO_TICKS(5));
  }
}