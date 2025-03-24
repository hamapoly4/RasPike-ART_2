
#ifdef __cplusplus
extern "C" {
#endif

#include "ev3api.h"
  
/* タスク優先度 */
#define MAIN_PRIORITY   (TMIN_APP_TPRI + 1) // メインタスク
#define SUB_PRIORITY    (TMIN_APP_TPRI + 2) // サブタスク

/* タスク周期の定義 */
#define SUB_PERIOD  (10 * 1000) // サブタスク:10msec周期


#ifndef STACK_SIZE
#define STACK_SIZE      (4096)
#endif /* STACK_SIZE */

#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void sub_task(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#ifdef __cplusplus
}
#endif
