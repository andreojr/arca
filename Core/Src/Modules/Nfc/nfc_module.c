#include "nfc_module.h"
#include "pn532.h"
#include "pn532_stm32f4.h"
#include "stm32f4xx_hal.h"
#include <stdio.h>

extern SPI_HandleTypeDef hspi1;

static PN532 pn532;
volatile uint8_t nfc_card_ready = 0;

static void on_card_detected(const uint8_t *uid, uint8_t uid_len)
{
    printf("Cartão detectado (%d bytes): ", uid_len);
    for (int i = 0; i < uid_len; i++) {
        printf("%02X ", uid[i]);
    }
    printf("\r\n");

    /* TODO: montar pacote e enviar via CC1101 */
}

void NFC_Module_Init(void)
{
    NFC_SetCardCallback(on_card_detected);
    NFC_Begin(&pn532);
}

void NFC_Module_Process(void)
{
    if (nfc_card_ready) {
        NFC_HandleCardEvent(&pn532);
    }
}

void NFC_Module_IRQ(void)
{
    nfc_card_ready = 1;
}