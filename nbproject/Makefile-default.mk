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
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=code/Src/Event.c code/Src/LTE.c code/Src/Modbus.c code/Src/adc.c code/Src/device_config.c code/Src/eusart1.c code/Src/eusart2.c code/Src/interrupt_manager.c code/Src/mcc.c code/Src/multi_timer.c code/Src/pFunc.c code/Src/pin_manager.c code/Src/tmr0.c code/Src/main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/code/Src/Event.p1 ${OBJECTDIR}/code/Src/LTE.p1 ${OBJECTDIR}/code/Src/Modbus.p1 ${OBJECTDIR}/code/Src/adc.p1 ${OBJECTDIR}/code/Src/device_config.p1 ${OBJECTDIR}/code/Src/eusart1.p1 ${OBJECTDIR}/code/Src/eusart2.p1 ${OBJECTDIR}/code/Src/interrupt_manager.p1 ${OBJECTDIR}/code/Src/mcc.p1 ${OBJECTDIR}/code/Src/multi_timer.p1 ${OBJECTDIR}/code/Src/pFunc.p1 ${OBJECTDIR}/code/Src/pin_manager.p1 ${OBJECTDIR}/code/Src/tmr0.p1 ${OBJECTDIR}/code/Src/main.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/code/Src/Event.p1.d ${OBJECTDIR}/code/Src/LTE.p1.d ${OBJECTDIR}/code/Src/Modbus.p1.d ${OBJECTDIR}/code/Src/adc.p1.d ${OBJECTDIR}/code/Src/device_config.p1.d ${OBJECTDIR}/code/Src/eusart1.p1.d ${OBJECTDIR}/code/Src/eusart2.p1.d ${OBJECTDIR}/code/Src/interrupt_manager.p1.d ${OBJECTDIR}/code/Src/mcc.p1.d ${OBJECTDIR}/code/Src/multi_timer.p1.d ${OBJECTDIR}/code/Src/pFunc.p1.d ${OBJECTDIR}/code/Src/pin_manager.p1.d ${OBJECTDIR}/code/Src/tmr0.p1.d ${OBJECTDIR}/code/Src/main.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/code/Src/Event.p1 ${OBJECTDIR}/code/Src/LTE.p1 ${OBJECTDIR}/code/Src/Modbus.p1 ${OBJECTDIR}/code/Src/adc.p1 ${OBJECTDIR}/code/Src/device_config.p1 ${OBJECTDIR}/code/Src/eusart1.p1 ${OBJECTDIR}/code/Src/eusart2.p1 ${OBJECTDIR}/code/Src/interrupt_manager.p1 ${OBJECTDIR}/code/Src/mcc.p1 ${OBJECTDIR}/code/Src/multi_timer.p1 ${OBJECTDIR}/code/Src/pFunc.p1 ${OBJECTDIR}/code/Src/pin_manager.p1 ${OBJECTDIR}/code/Src/tmr0.p1 ${OBJECTDIR}/code/Src/main.p1

# Source Files
SOURCEFILES=code/Src/Event.c code/Src/LTE.c code/Src/Modbus.c code/Src/adc.c code/Src/device_config.c code/Src/eusart1.c code/Src/eusart2.c code/Src/interrupt_manager.c code/Src/mcc.c code/Src/multi_timer.c code/Src/pFunc.c code/Src/pin_manager.c code/Src/tmr0.c code/Src/main.c



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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F25K22
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/code/Src/Event.p1: code/Src/Event.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/Event.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/Event.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/Event.p1 code/Src/Event.c 
	@-${MV} ${OBJECTDIR}/code/Src/Event.d ${OBJECTDIR}/code/Src/Event.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/Event.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/LTE.p1: code/Src/LTE.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/LTE.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/LTE.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/LTE.p1 code/Src/LTE.c 
	@-${MV} ${OBJECTDIR}/code/Src/LTE.d ${OBJECTDIR}/code/Src/LTE.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/LTE.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/Modbus.p1: code/Src/Modbus.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/Modbus.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/Modbus.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/Modbus.p1 code/Src/Modbus.c 
	@-${MV} ${OBJECTDIR}/code/Src/Modbus.d ${OBJECTDIR}/code/Src/Modbus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/Modbus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/adc.p1: code/Src/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/adc.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/adc.p1 code/Src/adc.c 
	@-${MV} ${OBJECTDIR}/code/Src/adc.d ${OBJECTDIR}/code/Src/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/device_config.p1: code/Src/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/device_config.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/device_config.p1 code/Src/device_config.c 
	@-${MV} ${OBJECTDIR}/code/Src/device_config.d ${OBJECTDIR}/code/Src/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/eusart1.p1: code/Src/eusart1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/eusart1.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/eusart1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/eusart1.p1 code/Src/eusart1.c 
	@-${MV} ${OBJECTDIR}/code/Src/eusart1.d ${OBJECTDIR}/code/Src/eusart1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/eusart1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/eusart2.p1: code/Src/eusart2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/eusart2.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/eusart2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/eusart2.p1 code/Src/eusart2.c 
	@-${MV} ${OBJECTDIR}/code/Src/eusart2.d ${OBJECTDIR}/code/Src/eusart2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/eusart2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/interrupt_manager.p1: code/Src/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/interrupt_manager.p1 code/Src/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/code/Src/interrupt_manager.d ${OBJECTDIR}/code/Src/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/mcc.p1: code/Src/mcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/mcc.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/mcc.p1 code/Src/mcc.c 
	@-${MV} ${OBJECTDIR}/code/Src/mcc.d ${OBJECTDIR}/code/Src/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/multi_timer.p1: code/Src/multi_timer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/multi_timer.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/multi_timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/multi_timer.p1 code/Src/multi_timer.c 
	@-${MV} ${OBJECTDIR}/code/Src/multi_timer.d ${OBJECTDIR}/code/Src/multi_timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/multi_timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/pFunc.p1: code/Src/pFunc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/pFunc.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/pFunc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/pFunc.p1 code/Src/pFunc.c 
	@-${MV} ${OBJECTDIR}/code/Src/pFunc.d ${OBJECTDIR}/code/Src/pFunc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/pFunc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/pin_manager.p1: code/Src/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/pin_manager.p1 code/Src/pin_manager.c 
	@-${MV} ${OBJECTDIR}/code/Src/pin_manager.d ${OBJECTDIR}/code/Src/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/tmr0.p1: code/Src/tmr0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/tmr0.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/tmr0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/tmr0.p1 code/Src/tmr0.c 
	@-${MV} ${OBJECTDIR}/code/Src/tmr0.d ${OBJECTDIR}/code/Src/tmr0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/tmr0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/main.p1: code/Src/main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/main.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/main.p1 code/Src/main.c 
	@-${MV} ${OBJECTDIR}/code/Src/main.d ${OBJECTDIR}/code/Src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/code/Src/Event.p1: code/Src/Event.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/Event.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/Event.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/Event.p1 code/Src/Event.c 
	@-${MV} ${OBJECTDIR}/code/Src/Event.d ${OBJECTDIR}/code/Src/Event.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/Event.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/LTE.p1: code/Src/LTE.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/LTE.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/LTE.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/LTE.p1 code/Src/LTE.c 
	@-${MV} ${OBJECTDIR}/code/Src/LTE.d ${OBJECTDIR}/code/Src/LTE.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/LTE.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/Modbus.p1: code/Src/Modbus.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/Modbus.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/Modbus.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/Modbus.p1 code/Src/Modbus.c 
	@-${MV} ${OBJECTDIR}/code/Src/Modbus.d ${OBJECTDIR}/code/Src/Modbus.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/Modbus.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/adc.p1: code/Src/adc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/adc.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/adc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/adc.p1 code/Src/adc.c 
	@-${MV} ${OBJECTDIR}/code/Src/adc.d ${OBJECTDIR}/code/Src/adc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/adc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/device_config.p1: code/Src/device_config.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/device_config.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/device_config.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/device_config.p1 code/Src/device_config.c 
	@-${MV} ${OBJECTDIR}/code/Src/device_config.d ${OBJECTDIR}/code/Src/device_config.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/device_config.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/eusart1.p1: code/Src/eusart1.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/eusart1.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/eusart1.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/eusart1.p1 code/Src/eusart1.c 
	@-${MV} ${OBJECTDIR}/code/Src/eusart1.d ${OBJECTDIR}/code/Src/eusart1.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/eusart1.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/eusart2.p1: code/Src/eusart2.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/eusart2.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/eusart2.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/eusart2.p1 code/Src/eusart2.c 
	@-${MV} ${OBJECTDIR}/code/Src/eusart2.d ${OBJECTDIR}/code/Src/eusart2.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/eusart2.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/interrupt_manager.p1: code/Src/interrupt_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/interrupt_manager.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/interrupt_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/interrupt_manager.p1 code/Src/interrupt_manager.c 
	@-${MV} ${OBJECTDIR}/code/Src/interrupt_manager.d ${OBJECTDIR}/code/Src/interrupt_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/interrupt_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/mcc.p1: code/Src/mcc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/mcc.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/mcc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/mcc.p1 code/Src/mcc.c 
	@-${MV} ${OBJECTDIR}/code/Src/mcc.d ${OBJECTDIR}/code/Src/mcc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/mcc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/multi_timer.p1: code/Src/multi_timer.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/multi_timer.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/multi_timer.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/multi_timer.p1 code/Src/multi_timer.c 
	@-${MV} ${OBJECTDIR}/code/Src/multi_timer.d ${OBJECTDIR}/code/Src/multi_timer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/multi_timer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/pFunc.p1: code/Src/pFunc.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/pFunc.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/pFunc.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/pFunc.p1 code/Src/pFunc.c 
	@-${MV} ${OBJECTDIR}/code/Src/pFunc.d ${OBJECTDIR}/code/Src/pFunc.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/pFunc.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/pin_manager.p1: code/Src/pin_manager.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/pin_manager.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/pin_manager.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/pin_manager.p1 code/Src/pin_manager.c 
	@-${MV} ${OBJECTDIR}/code/Src/pin_manager.d ${OBJECTDIR}/code/Src/pin_manager.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/pin_manager.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/tmr0.p1: code/Src/tmr0.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/tmr0.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/tmr0.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/tmr0.p1 code/Src/tmr0.c 
	@-${MV} ${OBJECTDIR}/code/Src/tmr0.d ${OBJECTDIR}/code/Src/tmr0.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/tmr0.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/code/Src/main.p1: code/Src/main.c  nbproject/Makefile-${CND_CONF}.mk 
	@${MKDIR} "${OBJECTDIR}/code/Src" 
	@${RM} ${OBJECTDIR}/code/Src/main.p1.d 
	@${RM} ${OBJECTDIR}/code/Src/main.p1 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -DXPRJ_default=$(CND_CONF)  -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits $(COMPARISON_BUILD)  -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     -o ${OBJECTDIR}/code/Src/main.p1 code/Src/main.c 
	@-${MV} ${OBJECTDIR}/code/Src/main.d ${OBJECTDIR}/code/Src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/code/Src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

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
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto        $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -fno-short-double -fno-short-float -memi=wordwrite -O0 -fasmfile -maddrqual=ignore -xassembler-with-cpp -I"code/Inc" -mwarn=-3 -Wa,-a -msummary=+psect,+class,+mem,-hex,-file  -ginhx32 -Wl,--data-init -mno-keep-startup -mno-download -mdefault-config-bits -std=c99 -gdwarf-3 -mstack=compiled:auto:auto:auto     $(COMPARISON_BUILD) -Wl,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -o dist/${CND_CONF}/${IMAGE_TYPE}/Remote_Generator.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
