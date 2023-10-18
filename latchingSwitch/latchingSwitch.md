# Latching Switch

Um latching switch, ou interruptor de retenção, é um tipo de interruptor que mantém sua posição (ligado ou desligado) após ser acionado até que seja novamente pressionado para alternar seu estado.

## Descrição do código:

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
