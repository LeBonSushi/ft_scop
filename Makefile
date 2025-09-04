NAME = ft_scop
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++20 -Ilibs/glad/include -Iincludes -Ilibs
LIBS = -lglfw -lGL -lm -ldl -lpthread -lX11 -lXrandr -lXinerama -lXcursor

SRCDIR = srcs
OBJDIR = objs

SOURCES = main.cpp \
		Application.cpp \
		WindowManager.cpp \
		Camera.cpp

GLAD_SRC = libs/glad/src/glad.c
OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o) $(OBJDIR)/glad.o

all: $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/glad.o: $(GLAD_SRC) | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
