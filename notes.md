P8 Smartwatch with ANT+ HRM measurement for Platform IO


ATCWatch 
https://github.com/atc1441/ATCwatch/tree/master/ATCwatch

SoftDevice with ant+
https://githublab.com/repository/adafruit/Adafruit_nRF52_Bootloader
https://judepereira.com/blog/tag/adafruit/
https://www.thisisant.com/developer/components/nrf52832/#tab_protocol_stacks_tab
https://www.thisisant.com/my-ant/join-adopter
https://download.csdn.net/download/u010438192/11246797
https://github.com/orrmany/Adafruit_nRF52_Arduino.git#develop-ant-plus-ble
https://devzone.nordicsemi.com/guides/short-range-guides/b/getting-started/posts/adjustment-of-ram-and-flash-memory

sudo apt install gcc-arm-none-eabi
pip install intelhex
make BOARD=feather_nrf52832 all

https://blogarak.wordpress.com/2020/03/15/s340-softdevice-adafruit-nrf52840-express-feather/
https://judepereira.com/blog/nrf52840-flash-s340/
https://devzone.nordicsemi.com/guides/short-range-guides/b/getting-started/posts/adjustment-of-ram-and-flash-memory
SoftDevice | Version | Minimum RAM | Start FLASH start
S132 | 6.1.1 | 0x20001628 | 0x26000
S332 | 6.1.1 | 0x20002000 | 0x30000

https://devzone.nordicsemi.com/f/nordic-q-a/1171/how-do-i-access-softdevice-version-string
https://devzone.nordicsemi.com/f/nordic-q-a/68500/--sd-req-for-the-latest-version-of-the-132-softdevice

|s132_nrf52_6.1.1|0x00B7|
|s332_nrf52_6.1.1|0x00BA|

-DBLE_STACK_SUPPORT_REQD -DSOFTDEVICE_PRESENT
"float_flags": "-mfloat-abi=hard -mfpu=fpv4-sp-d16 -DCONFIG_NFCT_PINS_AS_GPIOS -DNRF52 -DS332 -DNRF51_S332",

https://www.codetd.com/en/article/12564031


LVGL 6.1 chart styles

https://docs.lvgl.io/6.1/object-types/chart.html?highlight=chart#styles