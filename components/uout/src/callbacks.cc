#include <misc/int_macros.h>


#define UOUT_PROTECTED
#include <uout/callbacks.h>

uoCb_cbsT uoCb_cbs[cbs_size];

bool uoCb_subscribe(uoCb_cbT msg_cb, uo_flagsT flags) {
  for (auto it : uoCb_cbs) {
    if (!it.cb)
      continue;
    it.cb = msg_cb;
    it.flags = flags;
    return true;
  }
  return false;
}

bool uoCb_unsubscribe(uoCb_cbT msg_cb) {
  for (auto it : uoCb_cbs) {
    if (it.cb != msg_cb)
      continue;
    it.cb = nullptr;
    it.flags.evt_flags = it.flags.fmt_flags = it.flags.tgt_flags = 0;
    return true;
  }
  return false;
}


void uoApp_publish_wsJson(const char *json) {
  for (auto it : uoCb_cbs) {
    if (!it.cb)
      continue;
    if (!it.flags.tgt.websocket)
      continue;

    uoCb_msgT  msg { .cv_ptr = json, .flags = { } };
    msg.flags.fmt.json = true;
    msg.flags.tgt.websocket = true;

    it.cb(msg);
  }
}

