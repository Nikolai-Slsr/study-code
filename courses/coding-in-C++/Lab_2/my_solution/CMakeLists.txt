cmake_minimum_required(VERSION 3.10)
project(Lab2_MySolution)

# C++ Standard festlegen
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Ausführbare Datei für die SearchEngine ---
# Suche alle C++ Dateien im SearchEngine-Verzeichnis
file(GLOB SEARCH_ENGINE_SOURCES "SearchEngine/*.cpp")

# Erstelle ein Executable namens 'SearchEngineApp'
add_executable(SearchEngineApp ${SEARCH_ENGINE_SOURCES})

# Inkludiere das SearchEngine Verzeichnis, damit Header gefunden werden
target_include_directories(SearchEngineApp PRIVATE SearchEngine)


# --- 2. Ausführbare Datei für Section II (falls du den anderen Teil testen willst) ---
add_executable(Section_II Section_II.cpp)


# --- 3. Ausführbare Datei für Bank (falls vorhanden) ---
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/bank.cpp")
    add_executable(BankApp bank.cpp)
endif()
