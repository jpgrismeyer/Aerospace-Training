/* Memoria física del micro */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
    RAM   (rwx): ORIGIN = 0x20000000, LENGTH = 128K
}

/* Stack pointer inicial: tope de la RAM */
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* Colocación de secciones */
SECTIONS
{
    /* --- Vector de interrupciones al inicio de FLASH --- */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    /* --- Código y constantes en FLASH --- */
    .text :
    {
        *(.text*)         /* código */
        *(.rodata*)       /* datos const */
        *(.glue_7)
        *(.glue_7t)
        *(.eh_frame*)
    } > FLASH

    /* --- Variables con valor inicial en RAM --- */
    .data : 
    {
        *(.data*)
    } > RAM AT > FLASH

    /* --- Variables sin inicializar en RAM (se ponen a 0 al arranque real) --- */
    .bss :
    {
        *(.bss*)
        *(COMMON)
    } > RAM
}