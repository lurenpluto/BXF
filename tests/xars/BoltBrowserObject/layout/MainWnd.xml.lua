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

function OnCreate(self)

end

function OnLoadingStateChange(self, isLoading, canGoBack, anGoForward)

end

function OnBeforeNavigation(self, frame, url, navigation_type, is_redirect)

	return 0, false, true, true
	
end

function OnBeforePopup(self, frame, targetUrl, targetFrameName)
	local childBrowser = self:GetParent():GetObject("childbrowser")
	childBrowser:Navigate(targetUrl)
end

function OnJavaScriptMessageReceived(self,messageName,args)
	XLMessageBox(messageName)
	XLMessageBox(args['city']['date'])
end

function GetFileAbsPath(relativePath)
     local pos1, pos2 = string.find(__document, "BoltBrowserObject")
     local root = string.sub(__document, 1, pos2);
     return root..relativePath
end
