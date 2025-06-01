#ifndef SUB_HSM_NAVIGATION_H  // <- This should be changed to your own guard on both
#define SUB_HSM_NAVIGATION_H  //    of these lines


/*******************************************************************************
 * PUBLIC #INCLUDES                                                            *
 ******************************************************************************/

#include "ES_Configure.h"   // defines ES_Event, INIT_EVENT, ENTRY_EVENT, and EXIT_EVENT

/*******************************************************************************
 * PUBLIC #DEFINES                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC TYPEDEFS                                                             *
 ******************************************************************************/


/*******************************************************************************
 * PUBLIC FUNCTION PROTOTYPES                                                  *
 ******************************************************************************/

uint8_t InitNavigationSubHSM(void);

ES_Event RunNavigationSubHSM(ES_Event ThisEvent);

#endif /* SUB_HSM_NAVIGATION_H */

