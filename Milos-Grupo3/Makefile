# Makefile Simplificado
CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5`
LDFLAGS = `pkg-config --libs allegro-5 allegro_font-5 allegro_ttf-5 allegro_primitives-5 allegro_image-5` -lm


OBJDIR = obj
SOURCES = $(wildcard ./*.c)
OBJECTS = $(SOURCES: ./%.c=$(OBJDIR)/%.o)
TARGET = Pastoral_Loves

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

$(OBJDIR)/%.o: $(.)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean