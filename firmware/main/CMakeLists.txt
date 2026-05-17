idf_component_register(SRCS "app_main.c" "telemetry.c"
                       INCLUDE_DIRS "."
                       REQUIRES sensors motor_control tinyml_engine)