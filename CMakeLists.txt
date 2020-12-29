cmake_minimum_required(VERSION 3.16)
project(ATMinCSP)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ATMinCSP main.cpp msg.h sender.h receiver.h dispatcher.h TemplateDispatcher.h atm_message.h atm_state_machine.h bank_state_machine.h ui_state_machine.h)