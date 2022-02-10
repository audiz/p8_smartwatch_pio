#include "menu_Home.h"
#include "fonts/fonts.h"
#include "fonts/mksdl100.h"


void HomeScreen::touchData(touch_data_struct touch_data) {
    digitalWrite(STATUS_LED, HIGH);
    
    lv_label_set_text_fmt(label, "%X", touch_data.gesture);
    lv_obj_align(label, lv_scr_act(), LV_ALIGN_CENTER, 0, -60);
    lv_tick_inc(40);
    lv_task_handler();
}

void HomeScreen::right() {
    //display_notify();
}

void HomeScreen::pre()
{
    set_gray_screen_style(&lv_font_roboto_28);
    label_battery = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
    lv_obj_align(label_battery, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, 0, 0);

    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Heart Rate");
    lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -60);

    lv_style_copy(&st, &lv_style_plain);
    st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    st.text.font = &mksdl100;

    ble_label = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(ble_label, &st);
    lv_label_set_text(ble_label, "HRM");
    lv_label_set_align(ble_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(ble_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);

    status_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(status_label, "status_label");
    lv_label_set_align(status_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(status_label, NULL, LV_ALIGN_CENTER, 0, 60);
}

void HomeScreen::setBleInfo(const char *text)
{
    lv_label_set_text(status_label, text);
    lv_obj_align(status_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 60);
    lv_tick_inc(40);
    lv_task_handler();
}

void HomeScreen::setHRM(uint8_t data)
{
    lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
    lv_obj_align(label_battery, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, 0, 0);

    lv_label_set_text_fmt(ble_label, "%i", data);
    lv_obj_align(ble_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
    lv_tick_inc(40);
    lv_task_handler();
}

void HomeScreen::setHRM(const char *text)
{
    lv_label_set_text(ble_label, text);
    lv_obj_align(ble_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
    lv_tick_inc(40);
    lv_task_handler();
}

//BootScreen bootScreen;
/* Null, because instance will be initialized on demand. */
HomeScreen *HomeScreen::instance = 0;

HomeScreen *HomeScreen::getInstance()
{
    if (instance == 0)
    {
        instance = new HomeScreen();
    }

    return instance;
}

HomeScreen::HomeScreen()
{
}
