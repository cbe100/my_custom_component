#include "esphome.h"
#include <WiFi.h>
#include "esp_wpa2.h"  // Include WPA2 support

class CustomEAPAuth : public Component {
 public:
  void setup() override {
    // WPA2 Enterprise credentials
    const char *ssid = "Wistronwlan";
    const char *identity = "P236007";
    const char *username = "P236007";
    const char *password = "Lastna@WPH24";

    WiFi.disconnect(true);  // Disconnect if already connected
    WiFi.mode(WIFI_STA);

    esp_wifi_sta_wpa2_ent_set_identity((uint8_t *)identity, strlen(identity));
    esp_wifi_sta_wpa2_ent_set_username((uint8_t *)username, strlen(username));
    esp_wifi_sta_wpa2_ent_set_password((uint8_t *)password, strlen(password));
    esp_wifi_sta_wpa2_ent_enable();

    WiFi.begin(ssid);
  }
};
