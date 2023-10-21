## Para encontrar o endereço IP do ESP32, você pode seguir os procedimentos abaixo:

1. Conexão e Configuração Wi-Fi:
   Certifique-se de ter substituído as variáveis `ssid` e `password` pelos detalhes corretos da sua rede Wi-Fi. O ESP32 precisa estar conectado à sua rede Wi-Fi para obter um endereço IP válido.

2. Upload do Código:
   Compile e faça o upload do código para o seu ESP32 usando a plataforma Arduino IDE ou uma IDE compatível.

3. Monitor Serial:
   Abra a janela do Monitor Serial (Serial Monitor) na velocidade de baud rate de 115200. Você verá as mensagens de depuração durante o processo de conexão.

4. Verificação de Conexão:
   O ESP32 tentará se conectar à rede Wi-Fi especificada. Verifique no Monitor Serial se a conexão foi estabelecida corretamente. Você verá a mensagem "Connecting to WiFi..." e, em seguida, "The IP address is: xxx.xxx.xxx.xxx" quando a conexão estiver bem-sucedida.

5. Endereço IP:
   O endereço IP do ESP32 é exibido na linha que começa com "The IP address is:" no Monitor Serial. Anote esse endereço, pois é o endereço IP local atribuído ao ESP32 na sua rede Wi-Fi.

6. Acesso ao ESP32:
   Com o endereço IP em mãos, você pode acessar o ESP32 em um navegador da web, digitando o endereço IP na barra de endereços. Isso permitirá que você se conecte ao servidor web hospedado no ESP32 ou a qualquer serviço que você tenha configurado para ser acessível através desse endereço IP.

Certifique-se de que o ESP32 permaneça conectado à sua rede Wi-Fi para que ele mantenha o mesmo endereço IP na rede. Se o ESP32 se desconectar ou a rede Wi-Fi for reiniciada, o endereço IP pode ser alterado e você precisará encontrar o novo endereço IP usando os mesmos procedimentos.
