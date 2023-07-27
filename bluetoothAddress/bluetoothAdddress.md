### Para encontrar o endereço Bluetooth do ESP32, você pode seguir os procedimentos abaixo:

1. Configuração do Ambiente:
   - Certifique-se de ter o ambiente de desenvolvimento Arduino configurado corretamente para trabalhar com o ESP32. Se necessário, instale a placa ESP32 e as bibliotecas relevantes para suportar a comunicação Bluetooth.

2. Copiar o Código:
   - Copie o código fornecido neste repositório e cole-o em uma nova janela do Arduino IDE.

3. Upload do Código:
   - Conecte o ESP32 ao computador através de uma porta USB. Verifique se a placa e a porta corretas estão selecionadas na IDE Arduino. Em seguida, faça o upload do código para o ESP32 clicando no botão "Enviar" (seta para a direita) na parte superior da janela da IDE.

4. Abertura do Monitor Serial:
   - Após fazer o upload do código com sucesso, abra o Monitor Serial na IDE Arduino ou em qualquer outra ferramenta serial compatível com a comunicação do ESP32. Certifique-se de definir a velocidade de comunicação (baud rate) para 115200 bps.

5. Visualização do Endereço Bluetooth:
   - Assim que o ESP32 for inicializado, você verá uma mensagem "ESP32 Bluetooth Address:" seguida pelo endereço Bluetooth do ESP32, no formato "XX:XX:XX:XX:XX:XX", exibido no Monitor Serial.
  
<p align="center">
  <img src= "https://github.com/andresima0/Help-ESP32/assets/111400782/78ae37e0-6f2f-47c3-82b4-8fe3a3408c3f)" 
  alt= "BluetoothAddress" width="800">
</p>

Para mais informações, visite: https://techtutorialsx.com/2018/03/09/esp32-arduino-getting-the-bluetooth-device-address/
