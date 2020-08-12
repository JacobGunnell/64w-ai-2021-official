#include "GUI.h"

static lv_obj_t *preloader;
static lv_obj_t *mbox;

static lv_res_t gui_mbox_destroy(lv_obj_t *, const char *);


void gui_loading_start()
{
  preloader = lv_preload_create(lv_scr_act(), NULL);
  lv_obj_set_size(preloader, 100, 100);
  lv_obj_align(preloader, NULL, LV_ALIGN_CENTER, 0, 0);
}

void gui_loading_stop()
{
  lv_obj_del(preloader);
}

void gui_error(string msg)
{
  mbox = lv_mbox_create(lv_scr_act(), NULL);
  lv_mbox_set_text(mbox, msg.c_str());
  static const char *btn_str[] = {"Close", ""};
  lv_mbox_add_btns(mbox, btn_str, NULL);
  lv_mbox_set_action(mbox, gui_mbox_destroy);
}

void gui_main()
{
  // TODO
}


static lv_res_t gui_mbox_destroy(lv_obj_t *obj, const char *c)
{
  lv_obj_del(lv_mbox_get_from_btn(obj));
  return LV_RES_OK;
}
