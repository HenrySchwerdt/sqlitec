add_rules("mode.debug", "mode.release")
add_rules("mode.debug", "mode.release")

target("sqlitec")
    set_kind("binary")
    add_headerfiles("src/*.h")
    add_files("src/*.c")

target("test")
    set_kind("binary")
    add_files("test/*.c")
    add_files("src/*.c")
    remove_files("src/main.c")

