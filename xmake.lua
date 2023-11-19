add_rules("mode.debug", "mode.release")

target("sqlitec")
    set_kind("binary")
    add_headerfiles("src/*.h")
    add_files("src/*.c")

-- target("test")
--     set_kind("binary")
--     -- add_headerfiles("src/*.h", "test/*.h")
--     add_files("src/bs_*.c", "test/*.c")
