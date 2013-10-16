:设置拉取的sdk的具体版本，默认为最新版

set sdk_ver=HEAD



:设置拉取vs2003orvs2008的sdk，默认为2008

if "%1" == "2003" (set sdk_vs_ver=2003) else (set sdk_vs_ver=2008)



:设置拉取开发版sdk还是发布版sdk，默认为开发版

if "%2" == "pr" (set sdk_dev_ver=pr) else (set sdk_dev_ver=dev)



:设置sdk的远程url，默认为从主干拉取

set sdk_url=https://github.com/lurenpluto/BOLT_SDK/trunk

set sdk_vs_url=%sdk_url%/boltsdk_%sdk_vs_ver%



:设置本地使用的svn工具，默认为tools下自带的svn.exe

set svn_tool=..\tools\svn_bin\svn.exe



:设置拉取sdk存放的本地目录

set local_dir=..\bolt

set local_bin_dir=..\bin



:创建bolt sdk的目录

mkdir %local_dir%

mkdir %local_dir%\include

mkdir %lcoal_dir%\lib



:拉取sdk的include头文件

set sdk_inc_url=%sdk_vs_url%/include

set sdk_inc=%local_dir%\include



%svn_tool% export --force -r %sdk_ver% %sdk_inc_url% %sdk_inc%

:拉取sdk的lib

set sdk_lib_url=%sdk_vs_url%/dev/%sdk_dev_ver%/lib

set sdk_lib=%local_dir%\lib



%svn_tool% export --force -r %sdk_ver% %sdk_lib_url% %sdk_lib%

:创建bin的相关目录

mkdir %local_bin_dir%

mkdir %local_bin_dir%\Debug

mkdir %local_bin_dir%\Release

mkdir %local_bin_dir%\ProductRelease



:拉取UEloader等辅助工具

set sdk_dll_url=%sdk_vs_url%/tools

set sdk_dll=%local_bin_dir%\Debug



%svn_tool% export --force -r %sdk_ver% %sdk_dll_url% %sdk_dll%



:拉取辅助dll

set sdk_dll_url=%sdk_vs_url%/bin

set sdk_dll=%local_bin_dir%\Debug


%svn_tool% export --depth infinity --force -r %sdk_ver% %sdk_dll_url% %sdk_dll%



:拉取sdk的dll

set sdk_dll_url=%sdk_vs_url%/dev/%sdk_dev_ver%/bin

set sdk_dll=%local_bin_dir%\Debug


%svn_tool% export --force -r %sdk_ver% %sdk_dll_url% %sdk_dll%




xcopy /Y /E %local_bin_dir%\Debug %local_bin_dir%\Release

xcopy /Y /E %local_bin_dir%\Debug %local_bin_dir%\ProductRelease



:拷贝BOLT引擎的扩展配置表

call .\copy_extconfig.bat



:创建3rd目录
mkdir ..\3rd
mkdir ..\3rd\inc
mkdir ..\3rd\lib

pause