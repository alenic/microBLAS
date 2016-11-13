#            _                  ____  _        _    ____  
#  _ __ ___ (_) ___ _ __ ___   | __ )| |      / \  / ___| 
# | '_ ` _ \| |/ __| '__/ _ \  |  _ \| |     / _ \ \___ \ 
# | | | | | | | (__| | | (_) | | |_) | |___ / ___ \ ___) |
# |_| |_| |_|_|\___|_|  \___/  |____/|_____/_/   \_\____/ 
#
# Author: Alessandro Nicolosi
# 
#---------------------------------------------------------


include make.inc

# Filesystem
LOCAL_INCLUDE_PATH=./include
LOCAL_OBJ_PATH=./obj
LOCAL_LIB_PATH=./lib
LOCAL_TEST_PATH=./test

# Includes
LOCAL_INCLUDE_FILES = $(LOCAL_INCLUDE_PATH)/microBLAS.h



L_LIBFLAGS=-L$(LOCAL_LIB_PATH)
LOCAL_OBJECT_FILES=$(addprefix $(LOCAL_OBJ_PATH)/,$(LIB_OBJECTS))


default: all

all: dir lib_a lib_so test

dir:
	(test -d $(LOCAL_LIB_PATH) || mkdir -p $(LOCAL_LIB_PATH))
	(test -d $(LOCAL_OBJ_PATH) || mkdir -p $(LOCAL_OBJ_PATH))

$(LOCAL_OBJ_PATH)/%.o: src/%.c $(LOCAL_INCLUDE_FILES)
	$(CC) $(CFLAGS) -I$(LOCAL_INCLUDE_PATH) -o $@ -c $<

lib_a: $(LOCAL_LIB_PATH)/$(LIB_A_TARGET)

lib_so: $(LOCAL_LIB_PATH)/$(LIB_SO_TARGET)

# Build static library
$(LOCAL_LIB_PATH)/$(LIB_A_TARGET): $(addprefix $(LOCAL_OBJ_PATH)/,$(LIB_OBJECTS))
	rm -f $(LOCAL_LIB_PATH)/$(LIB_A_TARGET)
	ar -rv $(LOCAL_LIB_PATH)/$(LIB_A_TARGET) $(LOCAL_OBJECT_FILES)
	ranlib $(LOCAL_LIB_PATH)/$(LIB_A_TARGET)
	@echo "****************** Static lib: $(LIB_A_TARGET) [OK] ******************"

# Build dynamic library
$(LOCAL_LIB_PATH)/$(LIB_SO_TARGET): $(LOCAL_OBJECT_FILES)
	$(CC) -rdynamic -shared $(L_LIBFLAGS) -Wl,-soname,$(LIB_SO_TARGET).$(LIB_VERSION) -o $(LOCAL_LIB_PATH)/$(LIB_SO_TARGET) $(LOCAL_OBJECT_FILES)
	@echo "****************** Dynamic lib: $(LIB_SO_TARGET) [OK] ******************"

test: $(LOCAL_TEST_PATH)/$(EXECUTABLE)

test/$(EXECUTABLE): $(LOCAL_TEST_PATH)/*.c $(LOCAL_INCLUDE_FILES)
	$(CPP) $(CPPFLAGS) -o $(LOCAL_TEST_PATH)/$(EXECUTABLE) $(LOCAL_TEST_PATH)/*.c -I$(LOCAL_INCLUDE_PATH) -I$(GTEST_H) -L$(LOCAL_LIB_PATH) -lmicroBLAS $(GTEST_LIB) -lpthread
	@echo "****************** Test: $(EXECUTABLE) [OK] ******************"

# Clean
clean:
ifneq ($(LOCAL_OBJ_PATH),/)
	(test -d $(LOCAL_OBJ_PATH) && rm -fr $(LOCAL_OBJ_PATH) || true)
endif
ifneq ($(LOCAL_LIB_PATH),/)
	(test -d $(LOCAL_LIB_PATH) && rm -fr $(LOCAL_LIB_PATH) || true)
endif
	(test $(LOCAL_TEST_PATH)/$(EXECUTABLE) && rm $(LOCAL_TEST_PATH)/$(EXECUTABLE) || true)
	@echo "****************** Clean [OK] ******************"
	

.PHONY: clean
