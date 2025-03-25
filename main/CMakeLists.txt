idf_component_register(SRCS "esp32_s3_szp.c" "main.c" "app_ui.c"
                       
                       SRCS "assets/robot.c"
                       SRCS "assets/wdsss.c"
                       SRCS "assets/bjbb.c"
                       SRCS "assets/gdjg.c"
                       SRCS "assets/sjhjp.c"
                       SRCS "assets/sjjp.c"
                       SRCS "assets/tjb.c"
                       SRCS "assets/super_earth.c"

                       SRCS "assets/font_alipuhui20.c"
                       SRCS "bt/ble_hidd_demo.c" "bt/esp_hidd_prf_api.c" "bt/hid_dev.c" "bt/hid_device_le_prf.c"
                       EMBED_FILES "sword.pcm"
                       INCLUDE_DIRS "."
                       INCLUDE_DIRS "bt")

# spiffs_create_partition_image(storage ../spiffs FLASH_IN_PROJECT)
target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-unused-const-variable)
