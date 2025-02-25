// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 8.3.11
// Project name: Lcars

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////
void ON1_Animation(lv_obj_t * TargetObject, int delay);


// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
lv_obj_t * ui_Screen1;
lv_obj_t * ui_Background;
lv_obj_t * ui_Top_Right;
lv_obj_t * ui_Label1;
lv_obj_t * ui_Center;
lv_obj_t * ui_batterie;
lv_obj_t * ui_Slider2;
lv_obj_t * ui_Current1;
lv_obj_t * ui_Current;
lv_obj_t * ui_labelAmp;
lv_obj_t * ui_Label6;
lv_obj_t * ui_grpVersorger;
lv_obj_t * ui_Container2;
lv_obj_t * ui_Panel8;
lv_obj_t * ui_Panel9;
lv_obj_t * ui_Panel10;
lv_obj_t * ui_Panel11;
lv_obj_t * ui_ueberschriftmain;
lv_obj_t * ui_statsmain;
lv_obj_t * ui_voltagemain;
lv_obj_t * ui_Label7;
lv_obj_t * ui_lblvoltagemain;
lv_obj_t * ui_Label9;
lv_obj_t * ui_capacitymain;
lv_obj_t * ui_Label8;
lv_obj_t * ui_lblcapacitymain;
lv_obj_t * ui_Label10;
lv_obj_t * ui_tempmain;
lv_obj_t * ui_Label11;
lv_obj_t * ui_lbltempmain;
lv_obj_t * ui_Label12;
lv_obj_t * ui_remainmain;
lv_obj_t * ui_Label13;
lv_obj_t * ui_lblrmainmain;
lv_obj_t * ui_Label14;
lv_obj_t * ui_grpMotor;
lv_obj_t * ui_Container3;
lv_obj_t * ui_Panel13;
lv_obj_t * ui_Panel14;
lv_obj_t * ui_Panel15;
lv_obj_t * ui_Panel16;
lv_obj_t * ui_ueberschriftmotor;
lv_obj_t * ui_statsmotor;
lv_obj_t * ui_voltagemaschine1;
lv_obj_t * ui_Panel17;
lv_obj_t * ui_ueberschriftmain3;
lv_obj_t * ui_Label31;
lv_obj_t * ui_lblvoltagemotor1;
lv_obj_t * ui_Label32;
lv_obj_t * ui_tempmaschine1;
lv_obj_t * ui_Label33;
lv_obj_t * ui_lbltempmotor1;
lv_obj_t * ui_Label34;
lv_obj_t * ui_voltagemaschine2;
lv_obj_t * ui_Label35;
lv_obj_t * ui_lblvoltagemotor2;
lv_obj_t * ui_Label36;
lv_obj_t * ui_tempmaschine2;
lv_obj_t * ui_Label37;
lv_obj_t * ui_lbltempmotor2;
lv_obj_t * ui_Label38;
lv_obj_t * ui_grpBug;
lv_obj_t * ui_Container4;
lv_obj_t * ui_Panel12;
lv_obj_t * ui_Panel18;
lv_obj_t * ui_Panel19;
lv_obj_t * ui_Panel20;
lv_obj_t * ui_ueberschriftbug;
lv_obj_t * ui_statsbug;
lv_obj_t * ui_voltagebug;
lv_obj_t * ui_Panel21;
lv_obj_t * ui_ueberschriftmain4;
lv_obj_t * ui_Label15;
lv_obj_t * ui_lblvoltagebug;
lv_obj_t * ui_Label16;
lv_obj_t * ui_tempbug;
lv_obj_t * ui_Label17;
lv_obj_t * ui_lbltempbug;
lv_obj_t * ui_Label18;
lv_obj_t * ui_Container1;
lv_obj_t * ui_Panel6;
lv_obj_t * ui_Panel2;
lv_obj_t * ui_Panel7;
lv_obj_t * ui_buttons;
void ui_event_btnbug(lv_event_t * e);
lv_obj_t * ui_btnbug;
lv_obj_t * ui_Label4;
void ui_event_btnmotor(lv_event_t * e);
lv_obj_t * ui_btnmotor;
lv_obj_t * ui_Label3;
void ui_event_btnmain(lv_event_t * e);
lv_obj_t * ui_btnmain;
lv_obj_t * ui_Label5;
lv_obj_t * ui_Panel4;
lv_obj_t * ui_Label2;
lv_obj_t * ui_Panel1;
lv_obj_t * ui_lblTime;
lv_obj_t * ui_Panel3;
lv_obj_t * ui_imgchargetrans;
lv_obj_t * ui_imgcharge;
lv_obj_t * ui_Panel5;
lv_obj_t * ui_Image1;
lv_obj_t * ui_socmain;
// CUSTOM VARIABLES

// EVENTS
lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////
void ON1_Animation(lv_obj_t * TargetObject, int delay)
{
    ui_anim_user_data_t * PropertyAnimation_0_user_data = lv_mem_alloc(sizeof(ui_anim_user_data_t));
    PropertyAnimation_0_user_data->target = TargetObject;
    PropertyAnimation_0_user_data->val = -1;
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, 500);
    lv_anim_set_user_data(&PropertyAnimation_0, PropertyAnimation_0_user_data);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
    lv_anim_set_values(&PropertyAnimation_0, 0, 255);
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
    lv_anim_set_deleted_cb(&PropertyAnimation_0, _ui_anim_callback_free_user_data);
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply(&PropertyAnimation_0, false);
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_opacity);
    lv_anim_start(&PropertyAnimation_0);

}

///////////////////// FUNCTIONS ////////////////////
void ui_event_btnbug(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        ON1_Animation(ui_grpBug, 0);
        _ui_state_modify(ui_btnmotor, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_btnbug, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_btnmain, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_btnmain, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_btnmotor, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_btnbug, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_grpBug, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_grpMotor, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_grpVersorger, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_btnmotor(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        ON1_Animation(ui_grpMotor, 0);
        _ui_state_modify(ui_btnmain, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_btnbug, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_btnmotor, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_btnmain, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_btnbug, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_btnmotor, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_grpBug, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_grpMotor, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_grpVersorger, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_btnmain(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        ON1_Animation(ui_grpVersorger, 0);
        _ui_state_modify(ui_btnmain, LV_STATE_CHECKED, _UI_MODIFY_STATE_ADD);
        _ui_state_modify(ui_btnmotor, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
        _ui_state_modify(ui_btnbug, LV_STATE_CHECKED, _UI_MODIFY_STATE_REMOVE);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_btnmain, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_btnmotor, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_btnbug, LV_OBJ_FLAG_CLICKABLE, _UI_MODIFY_FLAG_ADD);
    }
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_grpBug, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_grpMotor, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_grpVersorger, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_Screen1);
}
