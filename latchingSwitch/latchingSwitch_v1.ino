//Latching Switch
 
const int buttonPin = 12; // Define o pino do botão
const int outputPin = 2;  // Define o pino da saída

// Variáveis para rastrear o estado do botão e da saída
int buttonState = 0;
int lastButtonState = HIGH;

// Variáveis para debounce
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

bool outputState = false; // Variável para rastrear o estado da saída (ligada ou desligada)

// Configura os pinos como entrada (botão) e saída
void setup() {
  pinMode(outputPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // INPUT_PULLUP ativa o resistor de pull-up interno
}

void loop() {
  // Lê o estado atual do botão
  int reading = digitalRead(buttonPin);

  // Verifica se houve mudança no estado do botão para debounce
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Verifica se passou o tempo de debounce
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // Verifica se o botão está pressionado (LOW)
      if (buttonState == LOW) {
        // Se o botão está pressionado, ligue a saída
        outputState = !outputState;
        digitalWrite(outputPin, outputState);
      }
    }
  }
  
  lastButtonState = reading; // Atualiza o estado anterior do botão para a próxima iteração
}
