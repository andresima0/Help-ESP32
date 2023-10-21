# Latching Switch - explicação de como tudo funciona

Um latching switch, ou interruptor de retenção, é um tipo de interruptor que mantém sua posição (ligado ou desligado) após ser acionado até que seja novamente pressionado para alternar seu estado.

https://github.com/andresima0/Help-ESP32/assets/111400782/938b4178-ede1-4d62-8c4e-660c78a8f6dd

# LatchingSwitch_v1
#### :thumbsup: O código disponibilizado é um excelente exemplo de latching switch, desenvolvido no intuito de resolver o mau funcionamento de acionamento que outros códigos genéricos estavam apresentando.

1. Declaração de variáveis:
   - `buttonPin` e `outputPin` são definidas para as GPIOs 12 e 2, respectivamente, que serão usadas como botão de pulso e saída.
   - `buttonState` mantém o estado atual do botão.
   - `lastButtonState` armazena o estado anterior do botão para detectar mudanças.
   - `lastDebounceTime` registra o momento da última mudança de estado do botão.
   - `debounceDelay` é o intervalo de tempo para o debounce (50 milissegundos).
   - `outputState` rastreia o estado atual da saída.

2. `setup()`:
   - Configura as GPIOs `outputPin` e `buttonPin`, definindo `outputPin` como saída e `buttonPin` com pull-up interno.

3. `loop()`:
   - Lê o estado atual do botão e armazena-o em `reading`.

   - Verifica se houve uma mudança no estado do botão usando a lógica de debounce. A ideia do debounce é evitar que ruídos elétricos ou vibrações no botão sejam interpretados como múltiplas pressões.
   
   - Se houve uma mudança no estado do botão e o debounce foi concluído, atualiza o `buttonState` para refletir o estado atual do botão.

   - Dentro do bloco condicional, verifica se o botão está pressionado (`buttonState == LOW`) e, se estiver, inverte o estado da saída (`outputState`) e liga ou desliga o pino de saída (`digitalWrite(outputPin, outputState)`).

   - O `lastButtonState` é atualizado para o valor atual de `reading`, para que ele possa ser usado na próxima iteração para detectar mudanças no estado do botão.

A principal razão para usar `millis()` em vez de `delay()` é que o `delay()` bloquearia o programa e impediria a detecção de mudanças no botão durante o atraso. Usando `millis()`, o código pode continuar monitorando o botão e responder a eventos em tempo real, enquanto ainda fornece uma função de debounce para garantir que apenas uma ação seja tomada quando o botão é pressionado, evitando falsos gatilhos devido a ruídos.

#
# LatchingSwitch_v2
Este código implementa um latching switch que, a cada pulso de botão, alterna entre três saídas (GPIOs 25, 26 e 27) em sequência, ligando uma saída e desligando a anterior. Aqui está uma explicação passo a passo do funcionamento do código:

1. Definição de pinos e variáveis:
   - `buttonPin`: Pino GPIO usado para o botão.
   - `outputPins[]`: Um array que contém os pinos GPIO das três saídas (25, 26 e 27).
   - `currentOutput`: Uma variável que rastreia a saída atual que está ligada.
   - `buttonState`: Variável que rastreia o estado atual do botão.
   - `lastButtonState`: Variável que rastreia o último estado do botão.
   - `lastDebounceTime`: Uma variável que rastreia o tempo do último debounce.
   - `debounceDelay`: O intervalo de tempo usado para debounce.
   - `outputState[]`: Um array que rastreia o estado atual de cada saída (ligada ou desligada).

2. Função `setup()`:
   - Configura os pinos das saídas e do botão, definindo as saídas como OUTPUT e o botão como INPUT_PULLUP. Isso ativa um resistor de pull-up interno para o botão.
   
3. Função `loop()`:
   - Lê o estado atual do botão.
   - Implementa um mecanismo de debounce para evitar respostas falsas do botão, garantindo que um pressionamento de botão seja válido apenas se o estado do botão permanecer estável por um determinado período de tempo.
   - Se o estado do botão for diferente do último estado registrado, atualiza o tempo do último debounce.
   - Se o tempo decorrido desde o último debounce for maior que o valor definido em `debounceDelay`, o código verifica se o estado do botão atual é diferente do estado do botão anterior.
   - Se o botão estiver pressionado (estado LOW) e for um novo pressionamento (diferente do estado anterior), o latching switch é acionado.
   - O código alterna o estado da saída atual (ligada ou desligada) usando a variável `outputState` e atualiza o pino da saída correspondente.
   - Desliga a saída anterior, garantindo que apenas uma saída esteja ligada por vez.
   - Atualiza a saída atual para a próxima na sequência (25, 26, 27) usando `currentOutput`.
   - O processo de latching switch é concluído e aguarda o próximo pressionamento de botão.

O código garante que apenas uma das saídas seja ligada por vez e que a transição entre elas seja feita a cada pressionamento do botão. Isso permite alternar entre as saídas 25, 26 e 27 sequencialmente. O código também inclui um mecanismo de debounce para evitar flutuações de sinal quando o botão é pressionado.

#
# LatchingSwitch_v3
#### Implementação de uma latching switch que envia sinais de status via Bluetooth BLE. :warning:Certifique-se de que os UUIDs correspondam ao que é esperado pelo aplicativo Bluetooth BLE.

1. Inclusão das bibliotecas BLE: O código começa incluindo as bibliotecas necessárias para a comunicação Bluetooth BLE, como `BLEDevice.h`, `BLEServer.h`, e `BLECharacteristic.h`.

2. Definição de pinos e variáveis: Os pinos GPIO usados para o botão (buttonPin) e saídas (outputPins) são definidos. Além disso, variáveis são declaradas para controlar o estado do botão, o estado de debounce, o estado das saídas e o índice da saída atual.

3. Definição de UUIDs: São definidos UUIDs para o serviço e a característica Bluetooth BLE, que são usados para identificar e distinguir os dispositivos Bluetooth.

4. Classe de Callbacks para a característica BLE: É criada uma classe chamada `MySwitchCallbacks` que herda da classe `BLECharacteristicCallbacks`. Essa classe é usada para lidar com as operações de escrita na característica BLE que controla o switch.

5. Função `setup()`: Nesta função, a configuração inicial é feita, incluindo a definição dos pinos de saída, configuração do botão como entrada, inicialização do dispositivo BLE com um nome e criação do servidor BLE e serviço. Além disso, é criada a característica BLE de Switch com as propriedades de leitura, escrita e notificação.

6. Função `loop()`: No loop principal, o código verifica o estado do botão. Ele implementa um mecanismo de debounce para evitar respostas falsas de pressionamento de botão. Quando o botão é pressionado (estado LOW), o sistema de latching switch é acionado.

   - A saída atual é alternada (ligada ou desligada).
   - A saída anterior é desligada.
   - O índice da saída atual é atualizado para a próxima saída.
   - O valor da característica BLE de Switch é atualizado com um número (1, 2 ou 3) para indicar a saída atual.
   - A notificação BLE é enviada para informar o status da saída ao aplicativo Bluetooth BLE conectado.
