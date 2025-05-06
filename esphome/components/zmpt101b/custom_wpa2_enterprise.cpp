// File: custom_wpa2_enterprise.cpp
#include "esphome.h"
#include <WiFi.h>
#include "esp_eap_client.h"

class CustomWPA2Enterprise : public Component {
public:
  void setup() override {
    const char *ssid = "Wistronwlan";
    const char *EAP_IDENTITY = "P236007";
    const char *EAP_PASSWORD = "Lastna@WPH24";

    IPAddress local_IP(10, 45, 52, 111);
    IPAddress gateway(10, 45, 52, 1);
    IPAddress subnet(255, 255, 255, 0);

    WiFi.mode(WIFI_STA);

    esp_eap_client_set_identity((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
    esp_eap_client_set_username((uint8_t *)EAP_IDENTITY, strlen(EAP_IDENTITY));
    esp_eap_client_set_password((uint8_t *)EAP_PASSWORD, strlen(EAP_PASSWORD));
    esp_eap_client_set_ttls_phase2_method(ESP_EAP_TTLS_PHASE2_EAP);
    esp_wifi_sta_enterprise_enable();

    WiFi.config(local_IP, gateway, subnet);
    WiFi.begin(ssid);
  }

  void loop() override {
    // Optionally, handle reconnections or other tasks in the loop
    if (WiFi.status() != WL_CONNECTED) {
      ESP_LOGD("custom_wpa2_enterprise", "Disconnected from Wi-Fi, attempting to reconnect...");
      WiFi.reconnect();
    }
  }
};
