:������ȡ��sdk�ľ���汾��Ĭ��Ϊ���°�

set sdk_ver=HEAD



:������ȡvs2003orvs2008��sdk��Ĭ��Ϊ2008

if "%1" == "2003" (set sdk_vs_ver=2003) else (set sdk_vs_ver=2008)



:������ȡ������sdk���Ƿ�����sdk��Ĭ��Ϊ������

if "%2" == "pr" (set sdk_dev_ver=pr) else (set sdk_dev_ver=dev)



:����sdk��Զ��url��Ĭ��Ϊ��������ȡ

set sdk_url=https://github.com/lurenpluto/BOLT_SDK/trunk

set sdk_vs_url=%sdk_url%/boltsdk_%sdk_vs_ver%



:���ñ���ʹ�õ�svn���ߣ�Ĭ��Ϊtools���Դ���svn.exe

set svn_tool=..\tools\svn_bin\svn.exe



:������ȡsdk��ŵı���Ŀ¼

set local_dir=..\bolt

set local_bin_dir=..\bin



:����bolt sdk��Ŀ¼

mkdir %local_dir%

mkdir %local_dir%\include

mkdir %lcoal_dir%\lib



:��ȡsdk��includeͷ�ļ�

set sdk_inc_url=%sdk_vs_url%/include

set sdk_inc=%local_dir%\include



%svn_tool% export --force -r %sdk_ver% %sdk_inc_url% %sdk_inc%

:��ȡsdk��lib

set sdk_lib_url=%sdk_vs_url%/dev/%sdk_dev_ver%/lib

set sdk_lib=%local_dir%\lib



%svn_tool% export --force -r %sdk_ver% %sdk_lib_url% %sdk_lib%

:����bin�����Ŀ¼

mkdir %local_bin_dir%

mkdir %local_bin_dir%\Debug

mkdir %local_bin_dir%\Release

mkdir %local_bin_dir%\ProductRelease



:��ȡUEloader�ȸ�������

set sdk_dll_url=%sdk_vs_url%/tools

set sdk_dll=%local_bin_dir%\Debug



%svn_tool% export --force -r %sdk_ver% %sdk_dll_url% %sdk_dll%



:��ȡ����dll

set sdk_dll_url=%sdk_vs_url%/bin

set sdk_dll=%local_bin_dir%\Debug


%svn_tool% export --depth infinity --force -r %sdk_ver% %sdk_dll_url% %sdk_dll%



:��ȡsdk��dll

set sdk_dll_url=%sdk_vs_url%/dev/%sdk_dev_ver%/bin

set sdk_dll=%local_bin_dir%\Debug


%svn_tool% export --force -r %sdk_ver% %sdk_dll_url% %sdk_dll%




xcopy /Y /E %local_bin_dir%\Debug %local_bin_dir%\Release

xcopy /Y /E %local_bin_dir%\Debug %local_bin_dir%\ProductRelease



:����BOLT�������չ���ñ�

call .\copy_extconfig.bat

:��ȡSvg����ļ�

call .\update_svg.bat

pause