#ifdef __cplusplus
extern "C" {
#endif

#include "ev3api.h"
  
/* タスク優先度 */
#define MAIN_PRIORITY    (TMIN_APP_TPRI + 1) /* メインタスク */
#define TRACER_PRIORITY  (TMIN_APP_TPRI + 2) /* ライントレースタスク */

/* タスク周期の定義 */
#define TRACER_PERIOD  (10 * 1000) /* ライントレースタスク:10msec周期 */


#ifndef STACK_SIZE
#define STACK_SIZE      (4096)
#endif /* STACK_SIZE */

#ifndef TOPPERS_MACRO_ONLY

extern void main_task(intptr_t exinf);
extern void tracer_task(intptr_t exinf);

#endif /* TOPPERS_MACRO_ONLY */

#include "spike/hub/button.h"

#ifdef __cplusplus
}
#endif
