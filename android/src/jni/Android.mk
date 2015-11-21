#traverse the directory and all the subdirectories
define walk
  $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))
endef

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := game

LOCAL_CFLAGS += -std=c++11 -fexceptions -frtti

LOCAL_C_INCLUDES := $(LOCAL_PATH)/src

ALL_SOURCES := $(call walk, $(LOCAL_PATH)/src/common)
ALL_SOURCES += $(call walk, $(LOCAL_PATH)/src/android)
ALL_SOURCES += $(call walk, $(LOCAL_PATH)/src/orxpm)
ALL_SOURCES += $(call walk, $(LOCAL_PATH)/src/lib)

FILE_LIST := $(filter %.c %.cpp, $(ALL_SOURCES))
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_STATIC_LIBRARIES := orx

LOCAL_ARM_MODE := arm

include $(BUILD_SHARED_LIBRARY)

$(call import-module,lib/static/android)

