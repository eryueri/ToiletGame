add_library(TG
Card.cc
CardSet.cc
Player.cc
Application.cc)

target_precompile_headers(TG
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/pch.hh)