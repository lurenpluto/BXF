: 从BXF_3RD处拉取Svg相关头文件和lib

set svg_ver=HEAD

:设置本地使用的svn工具，默认为tools下自带的svn.exe

set svn_tool=..\tools\svn_bin\svn.exe

:设置拉取三方库存放的本地目录

set third_dir=..\3rd
set third_lib_dir=..\3rd\lib
set third_inc_dir=..\3rd\inc

:创建三方库的目录

mkdir %third_dir%
mkdir %third_lib_dir%
mkdir %third_inc_dir%

:设置远程Url

set svg_url=https://github.com/lurenpluto/BXF_3RD/trunk/svg

:拉取Svg头文件

set svginc_url=%svg_url%/inc
set svg_inc=%third_inc_dir%\svg

%svn_tool% export --force -r %svg_ver% %svginc_url% %svg_inc%

:拉取Svg库文件

set svglib_url=%svg_url%/lib

%svn_tool% export --force -r %svg_ver% %svglib_url% %third_lib_dir%

pause