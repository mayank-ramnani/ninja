#include "manifest.h"

manifest() {
	rule(
		compile,
		bind(command, {"clang", "-c", "in"_v, "-o", "out"_v, "-MD", "-MF", "depfile"_v}),
		bind(depfile, {"out"_v, ".d"}),
		bind(deps, {"gcc"})
	);

	rule(
		link_shared,
		bind(command, {"g++", "-shared", "in"_v, "-o", "out"_v})
	);

	rule(
		link,
		bind(command, {"g++", "in"_v, "-o", "out"_v})
	);

	rule(
		link_static,
		bind(command, {"llvm-lib", "in"_v, "-out:out"_v})
	);

	rule(
		phony,
		bind(command, {"echo", "phony target"})
	);

	auto build1 = build(
		list(str("cmake_object_order_depends_target_zlib")),
		list(),
		phony,
		list(),
		list(),
		list(str(".")),
		{

		}
	);

	auto build2 = build(
		list(str("CMakeFiles/zlib.dir/adler32.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/adler32.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build3 = build(
		list(str("CMakeFiles/zlib.dir/compress.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/compress.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build4 = build(
		list(str("CMakeFiles/zlib.dir/crc32.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/crc32.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build5 = build(
		list(str("CMakeFiles/zlib.dir/deflate.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/deflate.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build6 = build(
		list(str("CMakeFiles/zlib.dir/gzclose.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/gzclose.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build7 = build(
		list(str("CMakeFiles/zlib.dir/gzlib.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/gzlib.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build8 = build(
		list(str("CMakeFiles/zlib.dir/gzread.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/gzread.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build9 = build(
		list(str("CMakeFiles/zlib.dir/gzwrite.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/gzwrite.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build10 = build(
		list(str("CMakeFiles/zlib.dir/inflate.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/inflate.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build11 = build(
		list(str("CMakeFiles/zlib.dir/infback.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/infback.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build12 = build(
		list(str("CMakeFiles/zlib.dir/inftrees.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/inftrees.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build13 = build(
		list(str("CMakeFiles/zlib.dir/inffast.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/inffast.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build14 = build(
		list(str("CMakeFiles/zlib.dir/trees.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/trees.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build15 = build(
		list(str("CMakeFiles/zlib.dir/uncompr.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/uncompr.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build16 = build(
		list(str("CMakeFiles/zlib.dir/zutil.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/zutil.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build17 = build(
		list(str("CMakeFiles/zlib.dir/win32/zlib1.rc.res")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/win32/zlib1.rc")),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build18 = build(
		list(str("zlib.dll"), str("zlib.lib")),
		list(),
		link_shared,
		list(str("CMakeFiles/zlib.dir/adler32.c.obj"), str("CMakeFiles/zlib.dir/compress.c.obj"), str("CMakeFiles/zlib.dir/crc32.c.obj"), str("CMakeFiles/zlib.dir/deflate.c.obj"), str("CMakeFiles/zlib.dir/gzclose.c.obj"), str("CMakeFiles/zlib.dir/gzlib.c.obj"), str("CMakeFiles/zlib.dir/gzread.c.obj"), str("CMakeFiles/zlib.dir/gzwrite.c.obj"), str("CMakeFiles/zlib.dir/inflate.c.obj"), str("CMakeFiles/zlib.dir/infback.c.obj"), str("CMakeFiles/zlib.dir/inftrees.c.obj"), str("CMakeFiles/zlib.dir/inffast.c.obj"), str("CMakeFiles/zlib.dir/trees.c.obj"), str("CMakeFiles/zlib.dir/uncompr.c.obj"), str("CMakeFiles/zlib.dir/zutil.c.obj"), str("CMakeFiles/zlib.dir/win32/zlib1.rc.res")),
		list(),
		list(),
		{

		}
	);

	auto build19 = build(
		list(str("cmake_object_order_depends_target_zlibstatic")),
		list(),
		phony,
		list(),
		list(),
		list(str(".")),
		{

		}
	);

	auto build20 = build(
		list(str("CMakeFiles/zlibstatic.dir/adler32.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/adler32.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build21 = build(
		list(str("CMakeFiles/zlibstatic.dir/compress.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/compress.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build22 = build(
		list(str("CMakeFiles/zlibstatic.dir/crc32.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/crc32.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build23 = build(
		list(str("CMakeFiles/zlibstatic.dir/deflate.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/deflate.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build24 = build(
		list(str("CMakeFiles/zlibstatic.dir/gzclose.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/gzclose.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build25 = build(
		list(str("CMakeFiles/zlibstatic.dir/gzlib.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/gzlib.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build26 = build(
		list(str("CMakeFiles/zlibstatic.dir/gzread.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/gzread.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build27 = build(
		list(str("CMakeFiles/zlibstatic.dir/gzwrite.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/gzwrite.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build28 = build(
		list(str("CMakeFiles/zlibstatic.dir/inflate.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/inflate.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build29 = build(
		list(str("CMakeFiles/zlibstatic.dir/infback.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/infback.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build30 = build(
		list(str("CMakeFiles/zlibstatic.dir/inftrees.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/inftrees.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build31 = build(
		list(str("CMakeFiles/zlibstatic.dir/inffast.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/inffast.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build32 = build(
		list(str("CMakeFiles/zlibstatic.dir/trees.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/trees.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build33 = build(
		list(str("CMakeFiles/zlibstatic.dir/uncompr.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/uncompr.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build34 = build(
		list(str("CMakeFiles/zlibstatic.dir/zutil.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/zutil.c")),
		list(),
		list(str("cmake_object_order_depends_target_zlibstatic")),
		{

		}
	);

	auto build35 = build(
		list(str("zlibstatic.lib")),
		list(),
		link_static,
		list(str("CMakeFiles/zlibstatic.dir/adler32.c.obj"), str("CMakeFiles/zlibstatic.dir/compress.c.obj"), str("CMakeFiles/zlibstatic.dir/crc32.c.obj"), str("CMakeFiles/zlibstatic.dir/deflate.c.obj"), str("CMakeFiles/zlibstatic.dir/gzclose.c.obj"), str("CMakeFiles/zlibstatic.dir/gzlib.c.obj"), str("CMakeFiles/zlibstatic.dir/gzread.c.obj"), str("CMakeFiles/zlibstatic.dir/gzwrite.c.obj"), str("CMakeFiles/zlibstatic.dir/inflate.c.obj"), str("CMakeFiles/zlibstatic.dir/infback.c.obj"), str("CMakeFiles/zlibstatic.dir/inftrees.c.obj"), str("CMakeFiles/zlibstatic.dir/inffast.c.obj"), str("CMakeFiles/zlibstatic.dir/trees.c.obj"), str("CMakeFiles/zlibstatic.dir/uncompr.c.obj"), str("CMakeFiles/zlibstatic.dir/zutil.c.obj")),
		list(),
		list(),
		{

		}
	);

	auto build36 = build(
		list(str("cmake_object_order_depends_target_example")),
		list(),
		phony,
		list(),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build37 = build(
		list(str("CMakeFiles/example.dir/test/example.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/test/example.c")),
		list(),
		list(str("cmake_object_order_depends_target_example")),
		{

		}
	);

	auto build38 = build(
		list(str("example.exe")),
		list(),
		link,
		list(str("CMakeFiles/example.dir/test/example.c.obj")),
		list(str("zlib.lib")),
		list(str("zlib.dll")),
		{

		}
	);

	auto build39 = build(
		list(str("cmake_object_order_depends_target_minigzip")),
		list(),
		phony,
		list(),
		list(),
		list(str("cmake_object_order_depends_target_zlib")),
		{

		}
	);

	auto build40 = build(
		list(str("CMakeFiles/minigzip.dir/test/minigzip.c.obj")),
		list(),
		compile,
		list(str("C$:/Users/grace/SchoolProj/updated_team2/Zlib_test/zlib/test/minigzip.c")),
		list(),
		list(str("cmake_object_order_depends_target_minigzip")),
		{

		}
	);

	auto build41 = build(
		list(str("minigzip.exe")),
		list(),
		link,
		list(str("CMakeFiles/minigzip.dir/test/minigzip.c.obj")),
		list(str("zlib.lib")),
		list(str("zlib.dll")),
		{

		}
	);

	auto build42 = build(
		list(str("test")),
		list(),
		phony,
		list(str("CMakeFiles/test.util")),
		list(),
		list(),
		{

		}
	);

	auto build43 = build(
		list(str("edit_cache")),
		list(),
		phony,
		list(str("CMakeFiles/edit_cache.util")),
		list(),
		list(),
		{

		}
	);

	auto build44 = build(
		list(str("rebuild_cache")),
		list(),
		phony,
		list(str("CMakeFiles/rebuild_cache.util")),
		list(),
		list(),
		{

		}
	);

	auto build45 = build(
		list(str("list_install_components")),
		list(),
		phony,
		list(),
		list(),
		list(),
		{

		}
	);

	auto build46 = build(
		list(str("install")),
		list(),
		phony,
		list(str("CMakeFiles/install.util")),
		list(),
		list(),
		{

		}
	);

	auto build47 = build(
		list(str("install/local")),
		list(),
		phony,
		list(str("CMakeFiles/install/local.util")),
		list(),
		list(),
		{

		}
	);

	auto build48 = build(
		list(str("install/strip")),
		list(),
		phony,
		list(str("CMakeFiles/install/strip.util")),
		list(),
		list(),
		{

		}
	);

	auto build49 = build(
		list(str("example")),
		list(),
		phony,
		list(str("example.exe")),
		list(),
		list(),
		{

		}
	);

	auto build50 = build(
		list(str("minigzip")),
		list(),
		phony,
		list(str("minigzip.exe")),
		list(),
		list(),
		{

		}
	);

	auto build51 = build(
		list(str("zlib")),
		list(),
		phony,
		list(str("zlib.dll")),
		list(),
		list(),
		{

		}
	);

	auto build52 = build(
		list(str("zlibstatic")),
		list(),
		phony,
		list(str("zlibstatic.lib")),
		list(),
		list(),
		{

		}
	);

	auto build53 = build(
		list(str("all")),
		list(),
		phony,
		list(str("zlib.dll"), str("zlibstatic.lib"), str("example.exe"), str("minigzip.exe")),
		list(),
		list(),
		{

		}
	);

	new_pool(pool1, 1); // Default pool 1
	new_pool(pool2, 1); // Default pool 2
	new_pool(pool3, 1); // Default pool 3

	default(str("zlib.dll"), str("zlibstatic.lib"));

	ShadowDash({build1, build2, build3, build4, build5, build6, build7, build8, build9, build10, build11, build12, build13, build14, build15, build16, build17, build18, build19, build20, build21, build22, build23, build24, build25, build26, build27, build28, build29, build30, build31, build32, build33, build34, build35, build36, build37, build38, build39, build40, build41, build42, build43, build44, build45, build46, build47, build48, build49, build50, build51, build52, build53}, {pool1, pool2, pool3}, default_target);
}

int main() {
    manifest();
    return 0;
}
