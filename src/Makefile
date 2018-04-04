# C compiler
CC:= mipsel-openwrt-linux-gcc
# path where the toolchain is
TOOLCHAIN_ROOT_DIR:= /home/max/source/staging_dir/target-mipsel_24kc_musl
#path where the omega_includes and omega_libs folder are
OMEGA_DIR:= /home/max/omega

# additional includes from toolchain
INCLUDE_DIRS:=$(TOOLCHAIN_ROOT_DIR)/usr/include
LIB_DIRS:=$(TOOLCHAIN_ROOT_DIR)/usr/lib

#links to link against
LDFLAGS_LIB:= -loniondebug -lonionspi -lugpio
LDFLAGS_PROGRAM = -lili9225
CFLAGS:= -O3 -ggdb -g -Wall -Wextra
IFLAGS:= -I $(INCLUDE_DIRS) -I $(OMEGA_DIR)/omega_includes

LIBRARY_SOURCES:= ILI9225.c DefaultFonts.c
PROGRAM_SOURCES = main.c
EXECUTABLE:= displayTest
LIB_NAME:= libili9225.so

export STAGING_DIR="$TOOLCHAIN_ROOT_DIR/staging_dir/"

.PHONY : library program all clean all

#compile the libwiiclassic.so
library:
	$(CC) -o $(LIB_NAME) -shared -fPIC $(CLFAGS) $(IFLAGS) -L $(LIB_DIRS) -L $(OMEGA_DIR)/omega_libs $(LIBRARY_SOURCES) $(LDFLAGS_LIB)

program:
	$(CC) -o $(EXECUTABLE) $(CFLAGS) $(IFLAGS) -L $(LIB_DIRS) -L $(OMEGA_DIR)/omega_libs -L. $(PROGRAM_SOURCES) $(LDFLAGS_PROGRAM) $(LDFLAGS_LIB)

all: | library program

upload: | all
	sshpass -p "onioneer" scp $(EXECUTABLE) root@192.168.1.202:/root/.
	#upload .so file to /usr/lib so that lib is found by executable
	sshpass -p "onioneer" scp $(LIB_NAME) root@192.168.1.202:/usr/lib/.

clean:
	rm -rf $(EXECUTABLE)
	rm -rf $(LIB_NAME)
