function OnSize(self, sizetype, width, height)
	if type_ == "min" then
		return
	end
	
	local objectTree = self:GetBindUIObjectTree()
	local rootObject = objectTree:GetRootObject()
	rootObject:SetObjPos(0, 0, width, height)
	
end

function OnClose(self)
	--UELoader的全局函数
	Quit()
end

function OnLoadingStateChange(self, isLoading, canGoBack, anGoForward)

end

function OnBeforeNavigation(self, frame, url, navigation_type, is_redirect)

	return 0, false, true, true
	
end

function OnBeforePopup(self, frame, targetUrl, targetFrameName)

	--XLMessageBox(targetUrl)
	local childBrowser = self:GetParent():GetObject("childbrowser")
	childBrowser:Navigate(targetUrl)
end