: ��BXF_3RD����ȡSvg���ͷ�ļ���lib

set svg_ver=HEAD

:���ñ���ʹ�õ�svn���ߣ�Ĭ��Ϊtools���Դ���svn.exe

set svn_tool=..\tools\svn_bin\svn.exe

:������ȡ�������ŵı���Ŀ¼

set third_dir=..\3rd
set third_lib_dir=..\3rd\lib
set third_inc_dir=..\3rd\inc

:�����������Ŀ¼

mkdir %third_dir%
mkdir %third_lib_dir%
mkdir %third_inc_dir%

:����Զ��Url

set svg_url=https://github.com/lurenpluto/BXF_3RD/trunk/svg

:��ȡSvgͷ�ļ�

set svginc_url=%svg_url%/inc
set svg_inc=%third_inc_dir%\svg

%svn_tool% export --force -r %svg_ver% %svginc_url% %svg_inc%

:��ȡSvg���ļ�

set svglib_url=%svg_url%/lib

%svn_tool% export --force -r %svg_ver% %svglib_url% %third_lib_dir%

:��ȡ�����������ļ�

set thirdlib_url=https://github.com/lurenpluto/BXF_3RD/trunk/3rd_lib

%svn_tool% export --force -r %svg_ver% %thirdlib_url% %third_lib_dir%

pause