# makefile for building Static Libary

#Ĭ�϶���debuginfo,optimize��GCC����WINDOWS��ȫ��һ��
debuginfo ?=1
optimize ?= 1

#Build with thread support.
threads ?= 1

#������� ==32��ָ������32λ�ĳ���==64������64λ����
buildbits ?= 0

# �����ֵ?=�Ǳ�ʾû�ж���͸�ֵ
AR        ?= ar

CC        ?= gcc
CXX       ?= g++
DLD       := $(CXX)
LD        := $(CXX)
RM        ?= rm -f
MKDIR     ?= mkdir -p
RMDIR     ?= rm -rf


INCLDIRS ?=
DEFFLAGS ?=

ifeq ($(buildbits),32)
CFLAGS += -m32
CCFLAGS += -m32
LDFLAGS  += -m32
endif
ifeq ($(buildbits),64)
CFLAGS += -m64
CCFLAGS += -m32
LDFLAGS  += -m64
endif

#ARFLAGS�����ⲿ�ж��壬����
ARFLAGS   = rsuv

#����ѡ��
#����ѡ��
CFLAGS += -W -Wall -Wpointer-arith 
CCFLAGS += -std=c++0x -W -Wall -Wpointer-arith 

#������Ż�
ifeq ($(optimize),1)
CFLAGS  += -O2
CCFLAGS += -O2
endif # optimize

#-ggdb������Կ��ش򿪺������ϢӦ�ú���-g,���ǲ���ʹ������������������
#�����Ҫ������Ϣ��linux�İ汾һ�㻹�Ǵ����˵�����Ϣ�����۰汾
ifeq ($(debuginfo),1)
  CFLAGS  += -ggdb
  CCFLAGS += -ggdb
endif # debuginfo

LIBARYS += -ldl

ifeq ($(threads),1)
  CFLAGS += -lpthread
  CCFLAGS += -lpthread
  LIBARYS += -lpthread -lrt
endif

DEFFLAGS += -D_GNU_SOURCE

C_FLIE   = $(wildcard ./*.c ) 
CPP_FILE = $(wildcard ./*.cpp )

O_CFILE   = $(patsubst ./%.c, ./%.o, $(C_FLIE))
O_CPPFILE = $(patsubst ./%.cpp, ./%.o, $(CPP_FILE))
#����������������
O_FILE  = $(O_CFILE) 

COMPILE.c  = $(CC)  $(CFLAGS)  $(DEFFLAGS) -c
COMPILE.cc = $(CXX) $(CCFLAGS) $(DEFFLAGS) -c

OUTFILE = libsqlite.a

.PHONY :all clean

all : $(OUTFILE) 

#���ʵ��GCC����
$(OUTFILE): $(O_FILE)
	$(AR) $(ARFLAGS) $(OUTFILE) $(O_FILE)
	
./%.o : ./%.c
	$(COMPILE.c) $(INCLDIRS) $< -o $@ 

#$(OUTFILE): $(O_FILE)
#	$(AR) $(ARFLAGS) $(OUTFILE) $(O_FILE)
#%.o : %.cpp
#	$(COMPILE.cc) $(INCLDIRS) $< -o $@ 

clean:
	$(RM)  $(OUTFILE) $(O_FILE)