LOCAL_PATH := $(call my-dir)

########################################

include $(CLEAR_VARS)
LOCAL_MODULE := CalculateJni

FILE_LIST := $(wildcard $(LOCAL_PATH)/trio_com_jniexceptionhandler_Calculate.cpp)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_CFLAGS := -g
LOCAL_LDLIBS := -llog -landroid
LOCAL_LDLIBS += -ldl   # 添加系统库
LOCAL_LDLIBS += -latomic #  fix error for armeabi: undefined reference to '__atomic_fetch_add_4'
include $(BUILD_SHARED_LIBRARY)

########################################

include $(CLEAR_VARS)
LOCAL_MODULE := CalculateJni2

FILE_LIST := $(wildcard $(LOCAL_PATH)/trio_com_jniexceptionhandler_Calculate2.cpp)

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
LOCAL_CFLAGS := -g
LOCAL_LDLIBS := -llog -landroid
LOCAL_LDLIBS += -ldl   # 添加系统库
LOCAL_LDLIBS += -latomic #  fix error for armeabi: undefined reference to '__atomic_fetch_add_4'
include $(BUILD_SHARED_LIBRARY)
