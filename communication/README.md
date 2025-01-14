# SCALE SIMULATOR

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
