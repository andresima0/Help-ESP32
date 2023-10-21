## Para encontrar o endereço MAC do ESP32, siga as seguintes etapas:

1. Conecte o seu ESP32 ao computador via USB.

2. Abra a Arduino IDE e crie um novo sketch.

3. Copie e cole o código fornecido na área de trabalho do sketch.

<p align="center">
  <img src= https://github.com/andresima0/Help---ESP32/assets/111400782/152a8779-c251-4f36-862f-aea2f01a666c)" 
  alt= "MacAddress" width="700">
</p>

4. Verifique se a velocidade de comunicação serial está configurada como 9600 baud. Você pode ajustar a velocidade no campo "Serial.begin(9600)".

5. Compile o código clicando no botão "Verify" na parte superior da janela da Arduino IDE.

6. Faça o upload do código para o ESP32 clicando no botão "Upload".

7. Abra o monitor serial na Arduino IDE clicando no ícone na parte superior direita da janela ou indo para "Tools" -> "Serial Monitor". Verifique se a velocidade do monitor serial está configurada como 9600 baud.

8. Aguarde o ESP32 iniciar, e em seguida clique no botão 'EN' (reset) do ESP32. Você verá uma saída no monitor serial. O endereço MAC do ESP32 será exibido como "ESP32 MAC Address: XX:XX:XX:XX:XX:XX".

O endereço MAC do ESP32 é uma sequência única de seis pares de caracteres hexadecimais, separados por dois pontos.

Certifique-se de que seu ESP32 esteja conectado corretamente e que a velocidade de comunicação serial esteja configurada corretamente para ver a saída correta no monitor serial.
