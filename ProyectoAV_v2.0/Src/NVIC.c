/*
 * NVIC.c
 *
 *  Created on: Oct 31, 2024
 *      Author: joshu
 */
#include "NVIC.h"

void NVIC_Enable(uint32_t irq_num, uint8_t priority) {
    if (irq_num >= 84) {
        // El número de interrupción es inválido, dado que el microcontrolador solo tiene 84 interrupciones
        return;
    }

    // Calcular el índice del registro ISER y el bit correspondiente
    uint32_t iser_index = irq_num / 32;
    uint32_t iser_bit = irq_num % 32;

    // Activar la interrupción correspondiente en NVIC_ISER
    NVIC->ISER[iser_index] = (1 << iser_bit);

    // Configurar la prioridad en el registro NVIC_IPR
    NVIC->IP[irq_num] = (priority & 0xF) << 4; // La prioridad usa 4 bits más significativos

    // La función no limpia en ICER, pero si quieres limpiar el bit usa:
    // NVIC->ICER[iser_index] = (1 << iser_bit); // Esto es opcional si necesitas desactivar
}

/*
void NVIC_ClearPending(uint32_t irq_num) {
    if (irq_num >= 84) {
        // El número de interrupción es inválido, dado que el microcontrolador solo tiene 84 interrupciones
        return;
    }

    // Calcular el índice del registro ICPR y el bit correspondiente
    uint32_t icpr_index = irq_num / 32;
    uint32_t icpr_bit = irq_num % 32;

    // Limpiar el estado pendiente de la interrupción correspondiente en NVIC_ICPR
    NVIC->ICPR[icpr_index] = (1 << icpr_bit);
}
*/
