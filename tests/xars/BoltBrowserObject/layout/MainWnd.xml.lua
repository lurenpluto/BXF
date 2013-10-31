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
	local objTree = self:GetBindUIObjectTree()
	local browser = objTree:GetUIObject("browser")
	browser:RegisterLuaFunction("testfunc",function(args)
		local format = "-result-\ncity:%s\nstreet:%s\npostcode:%s"
		local info = 
			string.format(format,
				args['city'],
				args['street'],
				args['postcode'])
		XLMessageBox(info)
		return {["result"]="bolt"}
	end)
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
	local format = "message:%s\ncity:%s\nstreet:%s\npostcode:%s"
	local info = 
		string.format(format,
			messageName,
			args['city'],
			args['street'],
			args['postcode'])
	XLMessageBox(info)

	self:CallJavascriptFunction('alert',{["name"]="bolt"},function(ret)
		XLMessageBox(ret['name'])
	end)
end

function GetFileAbsPath(relativePath)
     local pos1, pos2 = string.find(__document, "BoltBrowserObject")
     local root = string.sub(__document, 1, pos2);
     return root..relativePath
end

function CallJavascriptButton_MouseLeftDown(self)
	local objTree = self:GetOwner()
	local browser = objTree:GetUIObject("browser")
	browser:CallJavascriptFunction('alert',{["name"]="bolt"},function(ret)
		XLMessageBox(ret['name'])
	end)
end

function SendLuaMessage2JavascriptButton_MouseLeftDown(self)
	local objTree = self:GetOwner()
	local browser = objTree:GetUIObject("browser")
	browser:SendMessage('lua_message',{["name"]="bolt message"})
end









