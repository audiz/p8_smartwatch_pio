#include "menu_Home.h"
#include "fonts/fonts.h"
#include "fonts/mksdl100.h"
#include "menu.h"
#include "AutoQueue.h"

const size_t sz = 30;
AutoQueue<short, sz> hrm_queue;

void HomeScreen::touchData(touch_data_struct touch_data)
{
    digitalWrite(STATUS_LED, HIGH);

    if (is_current_screen(this))
    {
        lv_label_set_text_fmt(label, "%i %i", touch_data.xpos, touch_data.ypos);
        lv_obj_align(label, lv_scr_act(), LV_ALIGN_CENTER, 0, -60);
        lv_tick_inc(40);
        lv_task_handler();
    }
}

void HomeScreen::right()
{
    display_stat();
}

void HomeScreen::pre()
{
    set_gray_screen_style(&lv_font_roboto_28);
    
    // Enable min max calculate in queue
    hrm_queue.calcMinMax(true);

    // init style
    lv_style_copy(&st, &lv_style_plain);
    st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    st.text.font = &mksdl100;

    /*Create a chart*/
    chart = lv_chart_create(lv_scr_act(), NULL);
    lv_chart_set_style(chart, LV_CHART_STYLE_MAIN, &lv_style_transp);
    lv_obj_set_size(chart, 240, 190);
    lv_obj_align(chart, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_chart_set_type(chart, LV_CHART_TYPE_COLUMN); /*Show lines and points too*/
    lv_chart_set_point_count(chart, 30);

    /*Add two data series*/
    ser1 = lv_chart_add_series(chart, LV_COLOR_LIME);

    /*Set the next points on 'ser1'*/
    for (size_t n = 0; n < hrm_queue.size(); ++n)
    {
        short percent = ((hrm_queue[n] / 190.0) * 100);
        lv_chart_set_next(chart, ser1, percent);
    }
    // Required after direct set
    lv_chart_refresh(chart);

    label_battery = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
    lv_obj_align(label_battery, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, 0, 0);

    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, text_label);
    lv_label_set_align(label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -60);

    status_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(status_label, text_status_label);
    lv_label_set_align(status_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(status_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 60);

    minHr_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(minHr_label, "%i", hrm_queue.min());
    lv_label_set_align(minHr_label, LV_ALIGN_IN_BOTTOM_LEFT);
    lv_obj_align(minHr_label, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

    maxHr_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(maxHr_label, "%i", hrm_queue.max());
    lv_label_set_align(maxHr_label, LV_ALIGN_IN_TOP_LEFT);
    lv_obj_align(maxHr_label, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

    avgHr_label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(avgHr_label, "%i", hrm_queue.avg());
    lv_label_set_align(avgHr_label, LV_ALIGN_IN_LEFT_MID);
    lv_obj_align(avgHr_label, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 0);

    // render ble heart rate
    if (hrm_queue.size())
    {
        char hrBuffer[3];                      // heart rate buffer
        sprintf(hrBuffer, "%d", hrm_queue[0]); // convert
        text_ble_label = hrBuffer;
    }
    ble_label = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(ble_label, &st);
    lv_label_set_text(ble_label, text_ble_label);
    lv_label_set_align(ble_label, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(ble_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
}

void HomeScreen::setBleInfo(const char *text)
{
    text_status_label = text;

    if (is_current_screen(this))
    {
        lv_label_set_text(status_label, text);
        lv_obj_align(status_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 60);

        lv_tick_inc(40);
        lv_task_handler();
    }
}

void HomeScreen::setHRM(uint8_t data)
{

    hrm_queue.push(data);

    if (is_current_screen(this))
    {
        // calculate a percent from the max heart rate
        short percent = ((data / 190.0) * 100);
        lv_chart_set_next(chart, ser1, percent);

        lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
        lv_obj_align(label_battery, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, 0, 0);

        lv_label_set_text_fmt(ble_label, "%i", data);
        lv_obj_align(ble_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);

        lv_label_set_text_fmt(minHr_label, "%i", hrm_queue.min());
        lv_obj_align(minHr_label, lv_scr_act(), LV_ALIGN_IN_BOTTOM_LEFT, 0, 0);

        lv_label_set_text_fmt(maxHr_label, "%i", hrm_queue.max());
        lv_obj_align(maxHr_label, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

        lv_label_set_text_fmt(avgHr_label, "%i", hrm_queue.avg());
        lv_obj_align(avgHr_label, lv_scr_act(), LV_ALIGN_IN_LEFT_MID, 0, 0);

        lv_tick_inc(40);
        lv_task_handler();
    }
}

void HomeScreen::setHRM(const char *text)
{
    text_ble_label = text;
    if (is_current_screen(this))
    {
        lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
        lv_obj_align(label_battery, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, 0, 0);

        lv_label_set_text(ble_label, text_ble_label);
        lv_obj_align(ble_label, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);

        lv_tick_inc(40);
        lv_task_handler();
    }
}

// BootScreen bootScreen;
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
