SOURCE_PATHS += \
    $(BASE_PATH)/mcu \
	$(BASE_PATH)/mcu/core \
	$(BASE_PATH)/mcu/flash \
	$(BASE_PATH)/mcu/gpio \
	$(BASE_PATH)/mcu/pwr \
	$(BASE_PATH)/mcu/rcc \
	$(BASE_PATH)/mcu/utility \
	$(BASE_PATH)/startup


ifneq ($(filter ADC,$(MCU_EXCLUDES)),)
SYMBOLS += EXCLUDE_ADC
else
SOURCE_PATHS += $(BASE_PATH)/mcu/adc
endif


ifneq ($(filter DMA,$(MCU_EXCLUDES)),)
SYMBOLS += EXCLUDE_DMA
else
SOURCE_PATHS += $(BASE_PATH)/mcu/dma
endif


ifneq ($(filter QUADSPI,$(MCU_EXCLUDES)),)
SYMBOLS += EXCLUDE_QUADSPI
else
SOURCE_PATHS += $(BASE_PATH)/mcu/quadspi
endif


ifneq ($(filter SDMMC,$(MCU_EXCLUDES)),)
SYMBOLS += EXCLUDE_SDMMC
else
SOURCE_PATHS += $(BASE_PATH)/mcu/sdmmc
endif


ifneq ($(filter SPI,$(MCU_EXCLUDES)),)
SYMBOLS += EXCLUDE_SPI
else
SOURCE_PATHS += $(BASE_PATH)/mcu/spi
endif


ifneq ($(filter TIMER,$(MCU_EXCLUDES)),)
SYMBOLS += EXCLUDE_TIMER
else
SOURCE_PATHS += $(BASE_PATH)/mcu/timer
endif


ifneq ($(filter UART,$(MCU_EXCLUDES)),)
SYMBOLS += EXCLUDE_UART
else
SOURCE_PATHS += $(BASE_PATH)/mcu/uart
endif


ifneq ($(filter USB,$(MCU_EXCLUDES)),)
SYMBOLS += EXCLUDE_USB
else
SOURCE_PATHS += $(BASE_PATH)/mcu/usb
endif
