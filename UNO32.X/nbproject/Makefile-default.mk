#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/UNO32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/UNO32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=../ece118_files/ece118_base/AD.c ../ece118_files/ece118_base/BOARD.c ../ece118_files/ece118_base/ES_CheckEvents.c ../ece118_files/ece118_base/ES_Framework.c ../ece118_files/ece118_base/ES_KeyboardInput.c ../ece118_files/ece118_base/ES_LookupTables.c ../ece118_files/ece118_base/ES_PostList.c ../ece118_files/ece118_base/ES_Queue.c ../ece118_files/ece118_base/ES_TattleTale.c ../ece118_files/ece118_base/ES_Timers.c ../ece118_files/ece118_base/ES_TimerService.c ../ece118_files/ece118_base/IO_Ports.c ../ece118_files/ece118_base/LED.c ../ece118_files/ece118_base/pwm.c ../ece118_files/ece118_base/RC_Servo.c ../ece118_files/ece118_base/roach.c ../ece118_files/ece118_base/serial.c ../ece118_files/ece118_base/Stepper.c ../ece118_files/ece118_base/timers.c ../ece118_files/ece118_template/TemplateES_Main.c ../ece118_files/ece118_template/TemplateEventChecker.c ../ece118_files/ece118_template/TemplateService.c ../ece118_files/ece118_base/DC_Motors.c ../ece118_files/ece118_template/HSM_Top.c ../ece118_files/ece118_base/Weight_Sensor.c ../ece118_files/ece118_template/HSMSub_Operation.c ../ece118_files/ece118_template/HSMSub_Navigation.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/512026472/AD.o ${OBJECTDIR}/_ext/512026472/BOARD.o ${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o ${OBJECTDIR}/_ext/512026472/ES_Framework.o ${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o ${OBJECTDIR}/_ext/512026472/ES_LookupTables.o ${OBJECTDIR}/_ext/512026472/ES_PostList.o ${OBJECTDIR}/_ext/512026472/ES_Queue.o ${OBJECTDIR}/_ext/512026472/ES_TattleTale.o ${OBJECTDIR}/_ext/512026472/ES_Timers.o ${OBJECTDIR}/_ext/512026472/ES_TimerService.o ${OBJECTDIR}/_ext/512026472/IO_Ports.o ${OBJECTDIR}/_ext/512026472/LED.o ${OBJECTDIR}/_ext/512026472/pwm.o ${OBJECTDIR}/_ext/512026472/RC_Servo.o ${OBJECTDIR}/_ext/512026472/roach.o ${OBJECTDIR}/_ext/512026472/serial.o ${OBJECTDIR}/_ext/512026472/Stepper.o ${OBJECTDIR}/_ext/512026472/timers.o ${OBJECTDIR}/_ext/292653457/TemplateES_Main.o ${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o ${OBJECTDIR}/_ext/292653457/TemplateService.o ${OBJECTDIR}/_ext/512026472/DC_Motors.o ${OBJECTDIR}/_ext/292653457/HSM_Top.o ${OBJECTDIR}/_ext/512026472/Weight_Sensor.o ${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o ${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/512026472/AD.o.d ${OBJECTDIR}/_ext/512026472/BOARD.o.d ${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/512026472/ES_Framework.o.d ${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/512026472/ES_LookupTables.o.d ${OBJECTDIR}/_ext/512026472/ES_PostList.o.d ${OBJECTDIR}/_ext/512026472/ES_Queue.o.d ${OBJECTDIR}/_ext/512026472/ES_TattleTale.o.d ${OBJECTDIR}/_ext/512026472/ES_Timers.o.d ${OBJECTDIR}/_ext/512026472/ES_TimerService.o.d ${OBJECTDIR}/_ext/512026472/IO_Ports.o.d ${OBJECTDIR}/_ext/512026472/LED.o.d ${OBJECTDIR}/_ext/512026472/pwm.o.d ${OBJECTDIR}/_ext/512026472/RC_Servo.o.d ${OBJECTDIR}/_ext/512026472/roach.o.d ${OBJECTDIR}/_ext/512026472/serial.o.d ${OBJECTDIR}/_ext/512026472/Stepper.o.d ${OBJECTDIR}/_ext/512026472/timers.o.d ${OBJECTDIR}/_ext/292653457/TemplateES_Main.o.d ${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o.d ${OBJECTDIR}/_ext/292653457/TemplateService.o.d ${OBJECTDIR}/_ext/512026472/DC_Motors.o.d ${OBJECTDIR}/_ext/292653457/HSM_Top.o.d ${OBJECTDIR}/_ext/512026472/Weight_Sensor.o.d ${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o.d ${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/512026472/AD.o ${OBJECTDIR}/_ext/512026472/BOARD.o ${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o ${OBJECTDIR}/_ext/512026472/ES_Framework.o ${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o ${OBJECTDIR}/_ext/512026472/ES_LookupTables.o ${OBJECTDIR}/_ext/512026472/ES_PostList.o ${OBJECTDIR}/_ext/512026472/ES_Queue.o ${OBJECTDIR}/_ext/512026472/ES_TattleTale.o ${OBJECTDIR}/_ext/512026472/ES_Timers.o ${OBJECTDIR}/_ext/512026472/ES_TimerService.o ${OBJECTDIR}/_ext/512026472/IO_Ports.o ${OBJECTDIR}/_ext/512026472/LED.o ${OBJECTDIR}/_ext/512026472/pwm.o ${OBJECTDIR}/_ext/512026472/RC_Servo.o ${OBJECTDIR}/_ext/512026472/roach.o ${OBJECTDIR}/_ext/512026472/serial.o ${OBJECTDIR}/_ext/512026472/Stepper.o ${OBJECTDIR}/_ext/512026472/timers.o ${OBJECTDIR}/_ext/292653457/TemplateES_Main.o ${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o ${OBJECTDIR}/_ext/292653457/TemplateService.o ${OBJECTDIR}/_ext/512026472/DC_Motors.o ${OBJECTDIR}/_ext/292653457/HSM_Top.o ${OBJECTDIR}/_ext/512026472/Weight_Sensor.o ${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o ${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o

# Source Files
SOURCEFILES=../ece118_files/ece118_base/AD.c ../ece118_files/ece118_base/BOARD.c ../ece118_files/ece118_base/ES_CheckEvents.c ../ece118_files/ece118_base/ES_Framework.c ../ece118_files/ece118_base/ES_KeyboardInput.c ../ece118_files/ece118_base/ES_LookupTables.c ../ece118_files/ece118_base/ES_PostList.c ../ece118_files/ece118_base/ES_Queue.c ../ece118_files/ece118_base/ES_TattleTale.c ../ece118_files/ece118_base/ES_Timers.c ../ece118_files/ece118_base/ES_TimerService.c ../ece118_files/ece118_base/IO_Ports.c ../ece118_files/ece118_base/LED.c ../ece118_files/ece118_base/pwm.c ../ece118_files/ece118_base/RC_Servo.c ../ece118_files/ece118_base/roach.c ../ece118_files/ece118_base/serial.c ../ece118_files/ece118_base/Stepper.c ../ece118_files/ece118_base/timers.c ../ece118_files/ece118_template/TemplateES_Main.c ../ece118_files/ece118_template/TemplateEventChecker.c ../ece118_files/ece118_template/TemplateService.c ../ece118_files/ece118_base/DC_Motors.c ../ece118_files/ece118_template/HSM_Top.c ../ece118_files/ece118_base/Weight_Sensor.c ../ece118_files/ece118_template/HSMSub_Operation.c ../ece118_files/ece118_template/HSMSub_Navigation.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/UNO32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/512026472/AD.o: ../ece118_files/ece118_base/AD.c  .generated_files/flags/default/ad12b8b7f3821416598441714806888a03770929 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/AD.o.d" -o ${OBJECTDIR}/_ext/512026472/AD.o ../ece118_files/ece118_base/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/BOARD.o: ../ece118_files/ece118_base/BOARD.c  .generated_files/flags/default/3f7f6b358767be4ddb0e87f4d2eec46ce34bd165 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/BOARD.o.d" -o ${OBJECTDIR}/_ext/512026472/BOARD.o ../ece118_files/ece118_base/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o: ../ece118_files/ece118_base/ES_CheckEvents.c  .generated_files/flags/default/31d8fd3dbab54dec7566c215e521069bac676989 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o ../ece118_files/ece118_base/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_Framework.o: ../ece118_files/ece118_base/ES_Framework.c  .generated_files/flags/default/8c65a63ee0f663b456676f57a6c65c8eac57f477 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_Framework.o ../ece118_files/ece118_base/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o: ../ece118_files/ece118_base/ES_KeyboardInput.c  .generated_files/flags/default/9a0933619762c64ed1d32ea04191505801434d35 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o ../ece118_files/ece118_base/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_LookupTables.o: ../ece118_files/ece118_base/ES_LookupTables.c  .generated_files/flags/default/e075562fde5c074372adc694b86ef75bc124fe0c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_LookupTables.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_LookupTables.o ../ece118_files/ece118_base/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_PostList.o: ../ece118_files/ece118_base/ES_PostList.c  .generated_files/flags/default/19e78e97a36680770a886eb98a5ce4c690b69389 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_PostList.o ../ece118_files/ece118_base/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_Queue.o: ../ece118_files/ece118_base/ES_Queue.c  .generated_files/flags/default/55c0e09f37f063e8a670d4786c2720980c19fdea .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_Queue.o ../ece118_files/ece118_base/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_TattleTale.o: ../ece118_files/ece118_base/ES_TattleTale.c  .generated_files/flags/default/f021238b598536da23d6cceb3410d0dd5c7030f7 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_TattleTale.o ../ece118_files/ece118_base/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_Timers.o: ../ece118_files/ece118_base/ES_Timers.c  .generated_files/flags/default/64bc3dcd645f272b1e614b17c76223d35609ccd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_Timers.o ../ece118_files/ece118_base/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_TimerService.o: ../ece118_files/ece118_base/ES_TimerService.c  .generated_files/flags/default/7ee1dff1fdec66e19fb89c49d1952e5b30ce3076 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_TimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_TimerService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_TimerService.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_TimerService.o ../ece118_files/ece118_base/ES_TimerService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/IO_Ports.o: ../ece118_files/ece118_base/IO_Ports.c  .generated_files/flags/default/58a481f7415b112c33924a3321c19f6d4fcbc56a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/512026472/IO_Ports.o ../ece118_files/ece118_base/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/LED.o: ../ece118_files/ece118_base/LED.c  .generated_files/flags/default/ee0cf971101b3772594d2481b740cbfc30300c3e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/LED.o.d" -o ${OBJECTDIR}/_ext/512026472/LED.o ../ece118_files/ece118_base/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/pwm.o: ../ece118_files/ece118_base/pwm.c  .generated_files/flags/default/ccac5e46c4b1027a7ffbd2429deb784f6c8cb6cc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/pwm.o.d" -o ${OBJECTDIR}/_ext/512026472/pwm.o ../ece118_files/ece118_base/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/RC_Servo.o: ../ece118_files/ece118_base/RC_Servo.c  .generated_files/flags/default/fa82fccc0de79c4a11953d299b81b18499f2300a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/512026472/RC_Servo.o ../ece118_files/ece118_base/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/roach.o: ../ece118_files/ece118_base/roach.c  .generated_files/flags/default/7b1b4e3944f39e8e6730af73f8f0ed50d0fa83bc .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/roach.o.d" -o ${OBJECTDIR}/_ext/512026472/roach.o ../ece118_files/ece118_base/roach.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/serial.o: ../ece118_files/ece118_base/serial.c  .generated_files/flags/default/7b6a4552e489c734fe5b0d9ba871fcbb971deccd .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/serial.o.d" -o ${OBJECTDIR}/_ext/512026472/serial.o ../ece118_files/ece118_base/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/Stepper.o: ../ece118_files/ece118_base/Stepper.c  .generated_files/flags/default/c8a6be38baf233a781d369770bc1f80add3c3bdf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/Stepper.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/Stepper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/Stepper.o.d" -o ${OBJECTDIR}/_ext/512026472/Stepper.o ../ece118_files/ece118_base/Stepper.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/timers.o: ../ece118_files/ece118_base/timers.c  .generated_files/flags/default/f2aac7c07bce9c0d5ed31f4da69e3bf6d0da9fd5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/timers.o.d" -o ${OBJECTDIR}/_ext/512026472/timers.o ../ece118_files/ece118_base/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/TemplateES_Main.o: ../ece118_files/ece118_template/TemplateES_Main.c  .generated_files/flags/default/687543e51bfc9de199e37f4f2b8835247f777a69 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/TemplateES_Main.o.d" -o ${OBJECTDIR}/_ext/292653457/TemplateES_Main.o ../ece118_files/ece118_template/TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o: ../ece118_files/ece118_template/TemplateEventChecker.c  .generated_files/flags/default/dcc68083e99b75d6d8d53f5d6c58b5b368011ab4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o.d" -o ${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o ../ece118_files/ece118_template/TemplateEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/TemplateService.o: ../ece118_files/ece118_template/TemplateService.c  .generated_files/flags/default/605837028508f4f47da223bef4d97881b7c88104 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/TemplateService.o.d" -o ${OBJECTDIR}/_ext/292653457/TemplateService.o ../ece118_files/ece118_template/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/DC_Motors.o: ../ece118_files/ece118_base/DC_Motors.c  .generated_files/flags/default/8e6b741ebd53eaff831998bac846e0a7f2f3d7c8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/DC_Motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/DC_Motors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/DC_Motors.o.d" -o ${OBJECTDIR}/_ext/512026472/DC_Motors.o ../ece118_files/ece118_base/DC_Motors.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/HSM_Top.o: ../ece118_files/ece118_template/HSM_Top.c  .generated_files/flags/default/6eee9b475af3b1e34166e99b66f1adb7d74ef24f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSM_Top.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSM_Top.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/HSM_Top.o.d" -o ${OBJECTDIR}/_ext/292653457/HSM_Top.o ../ece118_files/ece118_template/HSM_Top.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/Weight_Sensor.o: ../ece118_files/ece118_base/Weight_Sensor.c  .generated_files/flags/default/312fc384bcb63526ab612c2d4627db6a1767e416 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/Weight_Sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/Weight_Sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/Weight_Sensor.o.d" -o ${OBJECTDIR}/_ext/512026472/Weight_Sensor.o ../ece118_files/ece118_base/Weight_Sensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o: ../ece118_files/ece118_template/HSMSub_Operation.c  .generated_files/flags/default/24b403e8d2eebc4cb505d230282630990e50433a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o.d" -o ${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o ../ece118_files/ece118_template/HSMSub_Operation.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o: ../ece118_files/ece118_template/HSMSub_Navigation.c  .generated_files/flags/default/f232dfa2c86c84b0e6825895ac89771b32bd3bbf .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o.d" -o ${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o ../ece118_files/ece118_template/HSMSub_Navigation.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/512026472/AD.o: ../ece118_files/ece118_base/AD.c  .generated_files/flags/default/d0e01de492a0582ffcdc5254e43a67789c9cbab4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/AD.o.d" -o ${OBJECTDIR}/_ext/512026472/AD.o ../ece118_files/ece118_base/AD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/BOARD.o: ../ece118_files/ece118_base/BOARD.c  .generated_files/flags/default/3e236e1cfe1cdf64adcd2f971361876acc3efd9a .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/BOARD.o.d" -o ${OBJECTDIR}/_ext/512026472/BOARD.o ../ece118_files/ece118_base/BOARD.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o: ../ece118_files/ece118_base/ES_CheckEvents.c  .generated_files/flags/default/9ecab5de86c06c58cf44a802e75eb6d0c27fb829 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_CheckEvents.o ../ece118_files/ece118_base/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_Framework.o: ../ece118_files/ece118_base/ES_Framework.c  .generated_files/flags/default/83c6f6a8fbc1c8faa8a52fec7d683699db125fef .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_Framework.o ../ece118_files/ece118_base/ES_Framework.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o: ../ece118_files/ece118_base/ES_KeyboardInput.c  .generated_files/flags/default/fbedce2b09c7bec32c45fa48027f91b18c4d44d2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_KeyboardInput.o ../ece118_files/ece118_base/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_LookupTables.o: ../ece118_files/ece118_base/ES_LookupTables.c  .generated_files/flags/default/90f1e471f9f0d4ebf6aecc24a08df24163422f96 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_LookupTables.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_LookupTables.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_LookupTables.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_LookupTables.o ../ece118_files/ece118_base/ES_LookupTables.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_PostList.o: ../ece118_files/ece118_base/ES_PostList.c  .generated_files/flags/default/2922f92eade2eaee0d643e94a8eab46b9ad0061b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_PostList.o ../ece118_files/ece118_base/ES_PostList.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_Queue.o: ../ece118_files/ece118_base/ES_Queue.c  .generated_files/flags/default/a25c31dae1d36034c243ef2d14b7ed77d1377901 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_Queue.o ../ece118_files/ece118_base/ES_Queue.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_TattleTale.o: ../ece118_files/ece118_base/ES_TattleTale.c  .generated_files/flags/default/19c10738a45f94ca52ba5186775d25469c3f8b02 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_TattleTale.o ../ece118_files/ece118_base/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_Timers.o: ../ece118_files/ece118_base/ES_Timers.c  .generated_files/flags/default/540761a11a1676c7b0e3f3ff0035f072fea2a42f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_Timers.o ../ece118_files/ece118_base/ES_Timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/ES_TimerService.o: ../ece118_files/ece118_base/ES_TimerService.c  .generated_files/flags/default/809429b239683cf3633a4e12146e26fb6ca04a6d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_TimerService.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/ES_TimerService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/ES_TimerService.o.d" -o ${OBJECTDIR}/_ext/512026472/ES_TimerService.o ../ece118_files/ece118_base/ES_TimerService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/IO_Ports.o: ../ece118_files/ece118_base/IO_Ports.c  .generated_files/flags/default/7d5d10dc3ba8f00b85e2cfd86c4cff36867cc08c .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/512026472/IO_Ports.o ../ece118_files/ece118_base/IO_Ports.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/LED.o: ../ece118_files/ece118_base/LED.c  .generated_files/flags/default/c3cca941f31d528a266905020c788df74ef21586 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/LED.o.d" -o ${OBJECTDIR}/_ext/512026472/LED.o ../ece118_files/ece118_base/LED.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/pwm.o: ../ece118_files/ece118_base/pwm.c  .generated_files/flags/default/16d2e9b01a75a345aa0eea038fbcbc617246bde6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/pwm.o.d" -o ${OBJECTDIR}/_ext/512026472/pwm.o ../ece118_files/ece118_base/pwm.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/RC_Servo.o: ../ece118_files/ece118_base/RC_Servo.c  .generated_files/flags/default/4580201ebd11739ac28a05a16a97c9cfa65e6b1e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/512026472/RC_Servo.o ../ece118_files/ece118_base/RC_Servo.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/roach.o: ../ece118_files/ece118_base/roach.c  .generated_files/flags/default/7fa4ee96134e4438a5d2b7f6aef9ce58be257c92 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/roach.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/roach.o.d" -o ${OBJECTDIR}/_ext/512026472/roach.o ../ece118_files/ece118_base/roach.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/serial.o: ../ece118_files/ece118_base/serial.c  .generated_files/flags/default/feb0ae63c6088e303e548e11b64bf6d3ce1ee81 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/serial.o.d" -o ${OBJECTDIR}/_ext/512026472/serial.o ../ece118_files/ece118_base/serial.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/Stepper.o: ../ece118_files/ece118_base/Stepper.c  .generated_files/flags/default/68d0d002f607703857eeb49fe693c0df66d0bf02 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/Stepper.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/Stepper.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/Stepper.o.d" -o ${OBJECTDIR}/_ext/512026472/Stepper.o ../ece118_files/ece118_base/Stepper.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/timers.o: ../ece118_files/ece118_base/timers.c  .generated_files/flags/default/aa607148efb2cc970e5b9784c9be4d321765c7d2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/timers.o.d" -o ${OBJECTDIR}/_ext/512026472/timers.o ../ece118_files/ece118_base/timers.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/TemplateES_Main.o: ../ece118_files/ece118_template/TemplateES_Main.c  .generated_files/flags/default/b2cd326e9a01edcd674fb4f94ad5a79c784c2f58 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/TemplateES_Main.o.d" -o ${OBJECTDIR}/_ext/292653457/TemplateES_Main.o ../ece118_files/ece118_template/TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o: ../ece118_files/ece118_template/TemplateEventChecker.c  .generated_files/flags/default/29d05b3a5d4bc0c34a1eb760a6d854c4818cb1b2 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o.d" -o ${OBJECTDIR}/_ext/292653457/TemplateEventChecker.o ../ece118_files/ece118_template/TemplateEventChecker.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/TemplateService.o: ../ece118_files/ece118_template/TemplateService.c  .generated_files/flags/default/9c04f5ac1c88e9917ba40d3fce44ea8c319824ee .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateService.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/TemplateService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/TemplateService.o.d" -o ${OBJECTDIR}/_ext/292653457/TemplateService.o ../ece118_files/ece118_template/TemplateService.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/DC_Motors.o: ../ece118_files/ece118_base/DC_Motors.c  .generated_files/flags/default/7a9a457e0e290a3605f791f79496500603d9520b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/DC_Motors.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/DC_Motors.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/DC_Motors.o.d" -o ${OBJECTDIR}/_ext/512026472/DC_Motors.o ../ece118_files/ece118_base/DC_Motors.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/HSM_Top.o: ../ece118_files/ece118_template/HSM_Top.c  .generated_files/flags/default/14e8fe806218ab624a36f2c67be4569bcc9cc245 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSM_Top.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSM_Top.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/HSM_Top.o.d" -o ${OBJECTDIR}/_ext/292653457/HSM_Top.o ../ece118_files/ece118_template/HSM_Top.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/512026472/Weight_Sensor.o: ../ece118_files/ece118_base/Weight_Sensor.c  .generated_files/flags/default/57160abb19555963d3875ad3aaf975672889ed5d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/512026472" 
	@${RM} ${OBJECTDIR}/_ext/512026472/Weight_Sensor.o.d 
	@${RM} ${OBJECTDIR}/_ext/512026472/Weight_Sensor.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/512026472/Weight_Sensor.o.d" -o ${OBJECTDIR}/_ext/512026472/Weight_Sensor.o ../ece118_files/ece118_base/Weight_Sensor.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o: ../ece118_files/ece118_template/HSMSub_Operation.c  .generated_files/flags/default/f2820304b1b965fc899b97b45d5e734eda3a6b44 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o.d" -o ${OBJECTDIR}/_ext/292653457/HSMSub_Operation.o ../ece118_files/ece118_template/HSMSub_Operation.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o: ../ece118_files/ece118_template/HSMSub_Navigation.c  .generated_files/flags/default/a889e9814cc97def1b11842fcc51f3a5fe52db7e .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/_ext/292653457" 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o.d 
	@${RM} ${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"../ece118_files/ece118_base" -I"../ece118_files/ece118_template" -MP -MMD -MF "${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o.d" -o ${OBJECTDIR}/_ext/292653457/HSMSub_Navigation.o ../ece118_files/ece118_template/HSMSub_Navigation.c    -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/UNO32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/UNO32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=4096,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
${DISTDIR}/UNO32.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o ${DISTDIR}/UNO32.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)    $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=4096,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,${DISTDIR}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}/xc32-bin2hex ${DISTDIR}/UNO32.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
