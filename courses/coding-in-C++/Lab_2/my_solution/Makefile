CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./SearchEngine

# Finde alle .cpp Dateien im SearchEngine Ordner
SE_SRCS = $(wildcard SearchEngine/*.cpp)
SE_OBJS = $(SE_SRCS:.cpp=.o)

# Basis-Ziele
TARGETS = SearchEngineApp Section_II

# Füge BankApp nur hinzu, wenn bank.cpp existiert
# ifneq ("$(wildcard bank.cpp)","")
#     TARGETS += BankApp
# endif

.PHONY: all clean

all: $(TARGETS)

# Kompiliert die SearchEngineApp
SearchEngineApp: $(SE_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Kompiliert Section_II
Section_II: Section_II.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Kompiliert BankApp (falls bank.cpp da ist)
BankApp: bank.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

# Allgemeine Regel für .o Dateien (Objekt-Dateien für den schnelleren Build)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f SearchEngineApp Section_II BankApp SearchEngine/*.o
