#include "orxpm.h"
#include "union/includes.inl"

extern "C" {

void orxPM_Init() {
    #include "union/init_calls.inl"
}

void orxPM_Exit() {
    #include "union/exit_calls.inl"
}

void orxPM_Run() {
    #include "union/run_calls.inl"
}

void orxPM_Bootstrap() {
    #include "union/bootstrap_calls.inl"
}

}

