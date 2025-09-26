CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5`
LDFLAGS = `pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5` -lm

SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = Pastoral_Loves

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean