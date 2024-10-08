#include <DHT.h> //para usar el DHt
#include <LiquidCrystal.h> // Para la pantalla LCD

#define DHTPIN 10 //pin del DHT
#define DHTTYPE DHT11 //modelo de dth que en este caso es el dht11
#define LDR_PIN A0 // pin del ldr
#define FAN_PIN 6  //pin del transistor, que controla al venti, el 6 por que es un pin PWM
#define LED_ON_PIN 8   // Pin para LED de Encendido del venti
#define LED_OFF_PIN 7  // Pin para LED de Apagado del venti
#define LED_STATUS 9  // Pin para LED de Apagado del venti



DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


 int fanSpeed = 0; //variable para la velocidad 
 float tempUmbral = 35.0;  // Umbral de temperatura
 float humedUmbral = 100.0; // Umbral de humedad
 bool systemOn = true;     // Estado del sistema

void setup() {


  pinMode(FAN_PIN, OUTPUT);
  pinMode(LED_ON_PIN, OUTPUT); //Led para marcar como encendido el ventilador
  pinMode(LED_OFF_PIN, OUTPUT); //Led para marcar como apagado el ventilador 
  digitalWrite(FAN_PIN, LOW); 
  digitalWrite(LED_ON_PIN, LOW); 
  digitalWrite(LED_OFF_PIN, HIGH); // LED de Apagado inicialmente encendido
  pinMode(LED_STATUS, OUTPUT);
  digitalWrite(LED_STATUS, HIGH); // El sistema inicia encendido
 
  dht.begin();
  Serial.begin(9600);
  
  
  lcd.begin(16, 2);

}

void loop() {

//variables de temperatura, humedad y luz

float temperatura = dht.readTemperature();
float humedad = dht.readHumidity();
int luz = analogRead(LDR_PIN);
  // Leer datos de los sensores
  
// Muestra los valores en la pantalla LCD
  lcd.clear();
  lcd.setCursor(0, 0); // Fila 0, columna 0
  lcd.print("T: ");
  lcd.print(temperatura);
  lcd.print(" C");

  lcd.setCursor(0, 1); // Fila 1, columna 0
  lcd.print("H: ");
  lcd.print(humedad);
  lcd.print(" %");

  lcd.setCursor(9, 1); // Fila 1, columna 9
  lcd.print("L: ");
  lcd.print(luz);

  // Enviar datos por UART al Monitor Serial
  Serial.print("T:"); Serial.print(temperatura);
  Serial.print(" H:"); Serial.print(humedad);
  Serial.print(" L:"); Serial.print(luz); Serial.print("\r"); // Carácter de retorno de carro

   // Control del ventilador (PWM)
  controlFan(temperatura, humedad);
  verificarErrores(temperatura, humedad);

  delay(1000); // Esperar un segundo antes de la siguiente lectura
}

void verificarErrores(float temp, float hume){

    // Verificar si hay errores en la lectura
  if (isnan(temp) || isnan(hume)) {
        digitalWrite(LED_STATUS, LOW);
    delay(1000);
    return;
  }else{
       digitalWrite(LED_STATUS, HIGH);
}
}
void controlFan(float tempe, float humed) {

// Controlar el ventilador y calcular la velocidad
  if (tempe > tempUmbral) {
    fanSpeed = map(tempe, tempUmbral, tempUmbral + 20, 128, 255); // Aumentar velocidad según temperatura
  } else if (humed > humedUmbral) {
    fanSpeed = map(humed, humedUmbral, humedUmbral + 20, 128, 255); // Aumentar velocidad según humedad
  } else {
    fanSpeed = 0; // Apagar el ventilador si no se exceden los umbrales
  }

  // Controlar LEDs y mostrar estado del ventilador
  if (fanSpeed > 0) {
 
    digitalWrite(LED_ON_PIN, HIGH);    // Enciende el LED de Encendido
    digitalWrite(LED_OFF_PIN, LOW);     // Apaga el LED de Apagado
  } else {
    digitalWrite(LED_ON_PIN, LOW);     // Apaga el LED de Encendido
    digitalWrite(LED_OFF_PIN, HIGH);    // Enciende el LED de Apagado
  }
}

void serialEvent() {
    // Escuchar comandos UART desde la computadora
  if (Serial.available()) {
    String command = Serial.readStringUntil('\r');
    processCommand(command);
  }
}

void processCommand(String command) {
  // Procesar comandos de la computadora
  if (command.startsWith("SET TEMP ")) {
    tempUmbral = command.substring(9).toFloat();
    Serial.println("Umbral de temperatura actualizado");
  } else if (command.startsWith("SET HUM ")) {
    humedUmbral = command.substring(8).toFloat();
    Serial.println("Umbral de humedad actualizado");
  } else if (command == "SYSTEM ON") {
    systemOn = true;
    digitalWrite(LED_STATUS, HIGH);
    Serial.println("Sistema encendido");
  } else if (command == "SYSTEM OFF") {
    systemOn = false;
    digitalWrite(LED_STATUS, LOW);
    Serial.println("Sistema apagado");
  } else {
    Serial.println("Comando no reconocido");
  }
}
