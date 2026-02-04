.syntax unified
    .cpu cortex-m4
    .thumb

    .global _estack
    .global Reset_Handler

/* ========== Vector table ========== */
/* Sección especial que va al inicio de la FLASH */
    .section .isr_vector, "a", %progbits
    .type g_pfnVectors, %object
    .size g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
    .word _estack            /* 0x08000000: stack inicial */
    .word Reset_Handler      /* 0x08000004: reset handler */
    .word 0                  /* NMI_Handler */
    .word 0                  /* HardFault_Handler */
    .word 0                  /* MemManage_Handler */
    .word 0                  /* BusFault_Handler */
    .word 0                  /* UsageFault_Handler */
    .word 0                  /* Reserved */
    .word 0                  /* Reserved */
    .word 0                  /* Reserved */
    .word 0                  /* Reserved */
    .word 0                  /* SVC_Handler */
    .word 0                  /* DebugMon_Handler */
    .word 0                  /* Reserved */
    .word 0                  /* PendSV_Handler */
    .word 0                  /* SysTick_Handler */
    /* podemos dejar el resto de las IRQs como 0 por ahora */

    .text
    .thumb_func
Reset_Handler:
    /* Por simplicidad, en esta primera versión NO copiamos .data ni limpiamos .bss.
       Vamos directo a main(). Más adelante hacemos la versión completa. */

    bl main

Loop_Forever:
    b Loop_Forever