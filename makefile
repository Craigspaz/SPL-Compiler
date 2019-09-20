#DEBUG=-D
SRCDIR=./src
OBJDIR=./obj
INCDIR=./include
BINDIR=./bin

SRCS=$(SRCDIR)/Launch.c \
$(SRCDIR)/SyntaxCheck.c \
$(SRCDIR)/Translate.c

INCLUDE = $(addprefix -I,$(INCDIR))
OBJS=${SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o}
CFLAGS   = $(OPTS) $(INCLUDE) -g$(DEBUG)

TARGET = $(BINDIR)/Compile

all: $(TARGET)

$(TARGET): $(OBJS) 
	${CC} ${CFLAGS} -o $@ $(OBJS)

$(OBJS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
