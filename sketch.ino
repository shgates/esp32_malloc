
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

char c;
int idx = 0;
const int buf_len = 50;
char buf[buf_len];
static volatile uint8_t flag = 0;
int tam = 0;
char *msg_ptr = NULL;

void xTaskListenAndSend(void *parameter) {
  while (1) {
    if (Serial.available() > 0) {
      if (idx == 0) {
        Serial.println("Escutando mensagem...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
      
      c = Serial.read();

      if (idx < buf_len - 1) {
        buf[idx] = c;
        idx++;
      }

      if (c == '\n') {
        buf[idx - 1] = '\0';
        Serial.println("Armazenando mensagem na heap...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
      
        msg_ptr = (char*)pvPortMalloc(idx * sizeof(char));
        memcpy(msg_ptr, buf, idx);

        tam = idx;
        idx = 0;

        memset(buf, 0, buf_len);
        Serial.println("Notificando...");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        flag = 1;
      }
    }
 
  }
}

void xTaskReceiveMessage(void *parameter) {
  while (1) {
    if(flag) {
      Serial.println("Recebi a mensagem...");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      Serial.print("Mensagem recebida: ");
      for(int i=0; i < tam; i++) {
        Serial.print(msg_ptr[i]);
      }
      Serial.println();
      Serial.println("Memoria heap liberada");
      vPortFree(msg_ptr);
      flag = 0;
    }
   vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Serial.println("Hello, ESP32!");

  xTaskCreatePinnedToCore(xTaskListenAndSend,
                          "Task listen and send a message",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);

  xTaskCreatePinnedToCore(xTaskReceiveMessage,
                          "Task receive message",
                          1024,
                          NULL,
                          1,
                          NULL,
                          app_cpu);
}

void loop() {}
