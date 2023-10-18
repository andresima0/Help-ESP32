// Latching switch que, a cada pulso de botão, alterna entre três saídas (GPIOs 25, 26 e 27) em sequência, ligando uma e desligando a anterior.

/*Foi utilizado uma array outputPins para armazenar as três GPIOs de saída (2, 4 e 5). 
O interruptor de latching alterna entre essas saídas em sequência a cada pulso do botão.
A função toggleOutput() é responsável por alternar a saída atual e avançar para a próxima saída em sequência. 
Um atraso (toggleDelay) é usado para evitar trocas rápidas e indesejadas das saídas. A saída atual é controlada pela variável currentOutput.*/

const int buttonPin = 12;
const int outputPins[] = {25, 26, 27};
int currentOutput = 0;
int buttonState = 0;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool outputState[] = {false, false, false};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  int reading = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // Se o botão está pressionado, alterne a saída
        outputState[currentOutput] = !outputState[currentOutput];
        digitalWrite(outputPins[currentOutput], outputState[currentOutput]);

        // Desligue a saída anterior
        int previousOutput = (currentOutput + 2) % 3;
        outputState[previousOutput] = false;
        digitalWrite(outputPins[previousOutput], outputState[previousOutput]);

        // Atualize a saída atual para a próxima
        currentOutput = (currentOutput + 1) % 3;
      }
    }
  }

  lastButtonState = reading;
}
