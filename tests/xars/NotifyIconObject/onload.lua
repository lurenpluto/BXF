local templateMananger = XLGetObject("Xunlei.UIEngine.TemplateManager")

local objectTreeTemplate = templateMananger:GetTemplate("NotifyIcon.Tree","ObjectTreeTemplate")
if objectTreeTemplate then
	local uiObjectTree = objectTreeTemplate:CreateInstance("SysTray")
end