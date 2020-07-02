
BOARD_SEPOLICY_DIRS += device/genivi/sepolicy

DEVICE_PACKAGE_OVERLAYS += device/genivi/audio/overlay

PRODUCT_PACKAGES += genivi.audiorelay

PRODUCT_PACKAGES += audio.primary.genivi
PRODUCT_PROPERTY_OVERRIDES += ro.hardware.audio.primary=genivi

PRODUCT_PROPERTY_OVERRIDES += ro.aae.simulateMultiZoneAudio=true
