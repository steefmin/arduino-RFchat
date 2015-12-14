#include <VirtualWire.h> // Download at https://www.pjrc.com/teensy/td_libs_VirtualWire.html

const int transmit_pin = 12;                            // connect to transmitter
const int receive_pin = 11;                             // connect to receiver
const int transmit_en_pin = 3;
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
int incomingByte = 0;

void setup()
{
        vw_set_tx_pin(transmit_pin);
        vw_set_rx_pin(receive_pin);
        vw_set_ptt_pin(transmit_en_pin);
        vw_set_ptt_inverted(true);                      // Required for DR3100
        vw_setup(2000);                                 // Bits per sec
        Serial.begin(9600);                             // Start serial monitor connection
        vw_rx_start();                                  // Start receiver
}
char msg[1] = {};
void loop() {
        // Send the serial input
        if (Serial.available() > 0) {
                incomingByte = Serial.read();
                Serial.write(incomingByte);
                char msg[1]={incomingByte};
                vw_send((uint8_t *)msg,1);
                vw_wait_tx();
        }
        // Read the received data
        vw_wait_rx_max(10);                             
        if (vw_get_message(buf, &buflen)){
                int i;
                for (i = 0; i < buflen; i++){
                    Serial.write(buf[i]);
                }     
    }
}
