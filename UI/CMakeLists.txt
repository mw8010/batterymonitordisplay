SET(SOURCES ui_Screen1.c
    ui.c
    ui_comp_hook.c
    ui_helpers.c
    ui_img_batterie_bg_png.c
    ui_img_indicator_bg_png.c
    ui_img_charge_trans_png.c
    ui_img_charge_png.c
    ui_img_blitz_png.c
    fonts/ui_font_Top.c
    fonts/ui_font_battery.c
    fonts/ui_font_button.c
    fonts/ui_font_labelAmp.c
    fonts/ui_font_sidebar.c)

add_library(ui ${SOURCES})
