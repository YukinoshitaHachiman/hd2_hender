#include "app_ui.h"
#include "audio_player.h"
#include "esp32_s3_szp.h"
#include "string.h"
#include <dirent.h>
#include "bt/ble_hidd_demo.h"
#include "esp_wifi.h"
#include "freertos/event_groups.h"
#include "esp_event.h"
#include <sys/stat.h>
#include <time.h>
#include <sys/time.h>
#include "esp_netif_sntp.h"
#include "esp_sntp.h"



LV_FONT_DECLARE(font_alipuhui20);

lv_obj_t * main_obj; // 主界面
lv_obj_t * main_text_label; // 主界面 欢迎语
lv_obj_t * icon_in_obj; // 应用界面


/*********************** super pig ****************************/
lv_obj_t * logo;

// 开机界面
void lv_gui_start(void)
{
    lvgl_port_lock(0);
    LV_IMG_DECLARE(super_earth);  // 声明图片
    logo = lv_img_create(lv_scr_act()); // 创建图片对象
    lv_img_set_src(logo, &super_earth); // 设置图片对象的图片源
    lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0); // 设置图片位置为屏幕正中心

    lvgl_port_unlock();
}




//第一个图标
static void icon_event_first(lv_event_t * e)
{   
    app_hid_ctrl_feiying500();
}

//第二个图标
static void icon_event_second(lv_event_t * e)
{
    app_hid_ctrl_bijibeibao();
}

//第三个图标
static void icon_event_third(lv_event_t * e)
 {
    app_hid_ctrl_guidaojiguang();
 }

//第四个图标
static void icon_event_fourth(lv_event_t * e)
{   
    app_hid_ctrl_shaojiehuojianpao();
}

//第五个图标
static void icon_event_fifth(lv_event_t * e)
{  
    app_hid_ctrl_shaojiejipao();
}

//第六个图标
static void icon_event_sixth(lv_event_t * e)
{   
    app_hid_ctrl_tujibing();
}


/******************************** 主界面  ******************************/

void lv_main_page(void)
{
    lvgl_port_lock(0);
    
    app_hid_ctrl();//开启蓝牙HID控制

    lv_obj_del(logo); // 删除开机logo
    // 创建主界面基本对象
    lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), 0); // 修改背景为黑色

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 10);  
    lv_style_set_bg_opa( &style, LV_OPA_COVER );
    lv_style_set_bg_color(&style, lv_color_hex(0x000000));
    //lv_style_set_bg_grad_color( &style, lv_color_hex( 0x00BF00 ) );
    lv_style_set_bg_grad_dir( &style, LV_GRAD_DIR_VER );
    lv_style_set_border_width(&style, 0);
    lv_style_set_pad_all(&style, 0);
    lv_style_set_width(&style, 320);  
    lv_style_set_height(&style, 240); 

    main_obj = lv_obj_create(lv_scr_act());
    lv_obj_add_style(main_obj, &style, 0);



    // 显示右上角符号
    lv_obj_t * sylbom_label = lv_label_create(main_obj);
    lv_obj_set_style_text_font(sylbom_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(sylbom_label, lv_color_hex(0xffffff), 0);
    lv_label_set_text(sylbom_label, LV_SYMBOL_BLUETOOTH" ");
    //lv_label_set_text(sylbom_label, LV_SYMBOL_BLUETOOTH" "LV_SYMBOL_WIFI);
    lv_obj_align_to(sylbom_label, main_obj, LV_ALIGN_TOP_RIGHT, -25, 10);

    lv_obj_t * robot_img = lv_img_create(main_obj);
    LV_IMG_DECLARE(robot);
    lv_img_set_src(robot_img, &robot);
    lv_obj_set_pos(robot_img, 295, 10);
    


    // 显示左上角标语
    main_text_label = lv_label_create(main_obj);
    lv_obj_set_style_text_font(main_text_label, &font_alipuhui20, 0);
    lv_label_set_long_mode(main_text_label, LV_LABEL_LONG_SCROLL_CIRCULAR);     /*Circular scroll*/
    lv_obj_set_width(main_text_label, 280);
    lv_label_set_text(main_text_label, "超级地球是投注"); 

    lv_obj_align_to(main_text_label, main_obj, LV_ALIGN_TOP_LEFT, 8, 5);

    // 设置应用图标style
    static lv_style_t btn_style;
    lv_style_init(&btn_style);
    lv_style_set_radius(&btn_style, 16);  
    lv_style_set_bg_opa( &btn_style, LV_OPA_COVER );
    lv_style_set_text_color(&btn_style, lv_color_hex(0x000000)); 
    lv_style_set_border_width(&btn_style, 0);
    lv_style_set_pad_all(&btn_style, 5);
    lv_style_set_width(&btn_style, 80);  
    lv_style_set_height(&btn_style, 80); 

    // 创建第1个应用图标
    lv_obj_t *icon1 = lv_btn_create(main_obj);
    lv_obj_add_style(icon1, &btn_style, 0);
    lv_obj_set_style_bg_color(icon1, lv_color_hex(0x000000), 0);
    lv_obj_set_pos(icon1, 15, 50);
    lv_obj_add_event_cb(icon1, icon_event_first, LV_EVENT_CLICKED, NULL);

    lv_obj_t * img1 = lv_img_create(icon1);
    LV_IMG_DECLARE(wdsss);
    lv_img_set_src(img1, &wdsss);
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);

    // 创建第2个应用图标
    lv_obj_t *icon2 = lv_btn_create(main_obj);
    lv_obj_add_style(icon2, &btn_style, 0);
    lv_obj_set_style_bg_color(icon2, lv_color_hex(0x000000), 0);
    lv_obj_set_pos(icon2, 120, 50);
    lv_obj_add_event_cb(icon2, icon_event_second, LV_EVENT_CLICKED, NULL);

    lv_obj_t * img2 = lv_img_create(icon2);
    LV_IMG_DECLARE(bjbb);
    lv_img_set_src(img2, &bjbb);
    //lv_obj_set_pos(img2, 120, 50);
    lv_obj_align(img2, LV_ALIGN_CENTER, 0, 0);

    // 创建第3个应用图标
    lv_obj_t *icon3 = lv_btn_create(main_obj);
    lv_obj_add_style(icon3, &btn_style, 0);
    lv_obj_set_style_bg_color(icon3, lv_color_hex(0x000000), 0);
    lv_obj_set_pos(icon3, 225, 50);
    lv_obj_add_event_cb(icon3, icon_event_third, LV_EVENT_CLICKED, NULL);

    lv_obj_t * img3 = lv_img_create(icon3);
    LV_IMG_DECLARE(gdjg);
    lv_img_set_src(img3, &gdjg);
    lv_obj_align(img3, LV_ALIGN_CENTER, 0, 0);

    // 创建第4个应用图标
    lv_obj_t *icon4 = lv_btn_create(main_obj);
    lv_obj_add_style(icon4, &btn_style, 0);
    lv_obj_set_style_bg_color(icon4, lv_color_hex(0x000000), 0);
    lv_obj_set_pos(icon4, 15, 147);
    lv_obj_add_event_cb(icon4, icon_event_fourth, LV_EVENT_CLICKED, NULL);

    lv_obj_t * img4 = lv_img_create(icon4);
    LV_IMG_DECLARE(sjhjp);
    lv_img_set_src(img4, &sjhjp);
    lv_obj_align(img4, LV_ALIGN_CENTER, 0, 0);

    // 创建第5个应用图标
    lv_obj_t *icon5 = lv_btn_create(main_obj);
    lv_obj_add_style(icon5, &btn_style, 0);
    lv_obj_set_style_bg_color(icon5, lv_color_hex(0x000000), 0);
    lv_obj_set_pos(icon5, 120, 147);
    lv_obj_add_event_cb(icon5, icon_event_fifth, LV_EVENT_CLICKED, NULL);

    lv_obj_t * img5 = lv_img_create(icon5);
    LV_IMG_DECLARE(sjjp);
    lv_img_set_src(img5, &sjjp);
    lv_obj_align(img5, LV_ALIGN_CENTER, 0, 0);

    // 创建第6个应用图标
    lv_obj_t *icon6 = lv_btn_create(main_obj);
    lv_obj_add_style(icon6, &btn_style, 0);
    lv_obj_set_style_bg_color(icon6, lv_color_hex(0x000000), 0);
    lv_obj_set_pos(icon6, 225, 147);
    lv_obj_add_event_cb(icon6, icon_event_sixth, LV_EVENT_CLICKED, NULL);

    lv_obj_t * img6 = lv_img_create(icon6);
    LV_IMG_DECLARE(tjb);
    lv_img_set_src(img6, &tjb);
    lv_obj_align(img6, LV_ALIGN_CENTER, 0, 0);

    lvgl_port_unlock();
}

