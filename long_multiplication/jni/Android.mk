LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := main.c
LOCAL_MODULE := long_multiplication
LOCAL_CFLAGS := -std=c99 -Wall
include $(BUILD_EXECUTABLE)
